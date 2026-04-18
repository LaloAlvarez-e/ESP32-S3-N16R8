Set-StrictMode -Version 2.0

function Get-Esp32RepositoryRoot {
    return [System.IO.Path]::GetFullPath((Join-Path $PSScriptRoot "..\.."))
}

function Resolve-Esp32Path {
    param(
        [Parameter(Mandatory = $true)]
        [string]$BasePath,

        [Parameter(Mandatory = $true)]
        [string]$PathValue
    )

    if ([System.IO.Path]::IsPathRooted($PathValue)) {
        return [System.IO.Path]::GetFullPath($PathValue)
    }

    return [System.IO.Path]::GetFullPath((Join-Path $BasePath $PathValue))
}

function Get-Esp32IdfPath {
    param(
        [string]$IdfPath = ""
    )

    $repositoryRoot = Get-Esp32RepositoryRoot
    $resolvedIdfPath = ""

    if (-not [string]::IsNullOrWhiteSpace($IdfPath)) {
        $resolvedIdfPath = Resolve-Esp32Path -BasePath $repositoryRoot -PathValue $IdfPath
    }
    elseif (-not [string]::IsNullOrWhiteSpace($env:IDF_PATH)) {
        $resolvedIdfPath = [System.IO.Path]::GetFullPath($env:IDF_PATH)
    }

    if ([string]::IsNullOrWhiteSpace($resolvedIdfPath)) {
        throw "IDF_PATH is not set. Configure the ESP-IDF extension environment or pass -IdfPath explicitly."
    }

    if (-not (Test-Path $resolvedIdfPath)) {
        throw "The resolved IDF_PATH does not exist: $resolvedIdfPath"
    }

    return $resolvedIdfPath
}

function Import-Esp32IdfEnvironment {
    param(
        [string]$IdfPath = ""
    )

    $resolvedIdfPath = Get-Esp32IdfPath -IdfPath $IdfPath
    $exportScriptPath = Join-Path $resolvedIdfPath "export.ps1"

    if (-not (Test-Path $exportScriptPath)) {
        throw "The ESP-IDF export script was not found at $exportScriptPath"
    }

    $previousErrorActionPreference = $ErrorActionPreference

    try {
        $ErrorActionPreference = "Continue"
        . $exportScriptPath
    }
    finally {
        $ErrorActionPreference = $previousErrorActionPreference
    }

    return $resolvedIdfPath
}

function Resolve-Esp32ExecutablePath {
    param(
        [Parameter(Mandatory = $true)]
        [string]$ExecutableName,

        [string]$ConfiguredPath = ""
    )

    $repositoryRoot = Get-Esp32RepositoryRoot
    $resolvedExecutablePath = ""

    function Get-ResolvedCommandPath {
        param(
            [Parameter(Mandatory = $true)]
            [System.Management.Automation.CommandInfo]$CommandInfo
        )

        $resolvedCommandPath = ""

        if (-not [string]::IsNullOrWhiteSpace($CommandInfo.Source)) {
            $resolvedCommandPath = $CommandInfo.Source
        }
        elseif (($CommandInfo | Get-Member -Name Path -ErrorAction SilentlyContinue) -and
                (-not [string]::IsNullOrWhiteSpace($CommandInfo.Path))) {
            $resolvedCommandPath = $CommandInfo.Path
        }
        elseif (-not [string]::IsNullOrWhiteSpace($CommandInfo.Name)) {
            $resolvedCommandPath = $CommandInfo.Name
        }

        return $resolvedCommandPath
    }

    if (-not [string]::IsNullOrWhiteSpace($ConfiguredPath)) {
        if ([System.IO.Path]::IsPathRooted($ConfiguredPath) -or
            ($ConfiguredPath.Contains("\\")) -or
            ($ConfiguredPath.Contains("/"))) {
            $resolvedExecutablePath = Resolve-Esp32Path -BasePath $repositoryRoot -PathValue $ConfiguredPath

            if (-not (Test-Path $resolvedExecutablePath)) {
                throw "The configured executable path does not exist: $resolvedExecutablePath"
            }
        }
        else {
            $commandInfo = Get-Command $ConfiguredPath -ErrorAction SilentlyContinue

            if ($null -ne $commandInfo) {
                $resolvedExecutablePath = Get-ResolvedCommandPath -CommandInfo $commandInfo
            }
        }
    }

    if ([string]::IsNullOrWhiteSpace($resolvedExecutablePath)) {
        $commandInfo = Get-Command $ExecutableName -ErrorAction SilentlyContinue

        if ($null -ne $commandInfo) {
            $resolvedExecutablePath = Get-ResolvedCommandPath -CommandInfo $commandInfo
        }
    }

    if ([string]::IsNullOrWhiteSpace($resolvedExecutablePath)) {
        throw "Unable to resolve executable '$ExecutableName'. Add it to PATH or configure an explicit path in .vscode/settings.json."
    }

    return $resolvedExecutablePath
}

function Get-Esp32OpenOcdScriptsPath {
    param(
        [string]$OpenOcdScripts = "",

        [string]$OpenOcdExecutablePath = ""
    )

    $repositoryRoot = Get-Esp32RepositoryRoot
    $resolvedOpenOcdScripts = ""

    if (-not [string]::IsNullOrWhiteSpace($OpenOcdScripts)) {
        $resolvedOpenOcdScripts = Resolve-Esp32Path -BasePath $repositoryRoot -PathValue $OpenOcdScripts
    }
    elseif (-not [string]::IsNullOrWhiteSpace($env:OPENOCD_SCRIPTS)) {
        $resolvedOpenOcdScripts = [System.IO.Path]::GetFullPath($env:OPENOCD_SCRIPTS)
    }
    elseif (-not [string]::IsNullOrWhiteSpace($OpenOcdExecutablePath)) {
        $openOcdBinDirectory = Split-Path -Parent $OpenOcdExecutablePath
        $openOcdRootDirectory = Split-Path -Parent $openOcdBinDirectory
        $openOcdScriptsCandidates = @(
            (Join-Path $openOcdRootDirectory "share\openocd\scripts"),
            (Join-Path $openOcdRootDirectory "scripts")
        )

        foreach ($candidatePath in $openOcdScriptsCandidates) {
            if (Test-Path $candidatePath) {
                $resolvedOpenOcdScripts = [System.IO.Path]::GetFullPath($candidatePath)
                break
            }
        }
    }

    if ([string]::IsNullOrWhiteSpace($resolvedOpenOcdScripts)) {
        throw "OpenOCD scripts were not resolved. Configure OPENOCD_SCRIPTS or set esp32Project.openOcdScripts in .vscode/settings.json."
    }

    if (-not (Test-Path $resolvedOpenOcdScripts)) {
        throw "The resolved OpenOCD scripts path does not exist: $resolvedOpenOcdScripts"
    }

    return $resolvedOpenOcdScripts
}

function Get-Esp32ListeningTcpConnections {
    param(
        [Parameter(Mandatory = $true)]
        [int[]]$Ports
    )

    $getNetTcpConnectionCommand = Get-Command Get-NetTCPConnection -ErrorAction SilentlyContinue

    if ($null -eq $getNetTcpConnectionCommand) {
        return @()
    }

    $connectionTable = @{}

    foreach ($port in $Ports) {
        $tcpConnections = @(Get-NetTCPConnection -State Listen -LocalPort $port -ErrorAction SilentlyContinue)

        foreach ($tcpConnection in $tcpConnections) {
            $connectionKey = ("{0}:{1}" -f $tcpConnection.LocalPort, $tcpConnection.OwningProcess)
            $connectionTable[$connectionKey] = $tcpConnection
        }
    }

    return @($connectionTable.Values | Sort-Object LocalPort, OwningProcess)
}

function Clear-Esp32StaleOpenOcdListeners {
    param(
        [int[]]$Ports = @(3333, 4444, 6666)
    )

    $listenerConnections = @(Get-Esp32ListeningTcpConnections -Ports $Ports)

    if (0 -eq $listenerConnections.Count) {
        return
    }

    $openOcdProcessIds = @()

    foreach ($listenerConnection in $listenerConnections) {
        $processId = [int]$listenerConnection.OwningProcess

        if ($openOcdProcessIds -contains $processId) {
            continue
        }

        $process = Get-Process -Id $processId -ErrorAction SilentlyContinue

        if (($null -ne $process) -and ("openocd" -ieq $process.ProcessName)) {
            $openOcdProcessIds += $processId
        }
    }

    if (0 -lt $openOcdProcessIds.Count) {
        Write-Host ("Stopping stale OpenOCD process IDs: {0}" -f (($openOcdProcessIds | Sort-Object) -join ", "))
        Stop-Process -Id $openOcdProcessIds -Force -ErrorAction Stop
        Wait-Process -Id $openOcdProcessIds -Timeout 5 -ErrorAction SilentlyContinue
    }

    $remainingConnections = @(Get-Esp32ListeningTcpConnections -Ports $Ports)

    if (0 -eq $remainingConnections.Count) {
        return
    }

    $remainingConnectionDescriptions = @()

    foreach ($remainingConnection in $remainingConnections) {
        $processId = [int]$remainingConnection.OwningProcess
        $process = Get-Process -Id $processId -ErrorAction SilentlyContinue
        $processName = "unknown"

        if ($null -ne $process) {
            $processName = $process.ProcessName
        }

        $remainingConnectionDescriptions += ("port {0} -> {1} (PID {2})" -f $remainingConnection.LocalPort, $processName, $processId)
    }

    throw ("OpenOCD debug ports are already in use: {0}" -f ($remainingConnectionDescriptions -join "; "))
}

function Get-Esp32AvailableSerialPorts {
    $portTable = @{}
    $portNames = [System.IO.Ports.SerialPort]::GetPortNames()

    foreach ($portName in $portNames) {
        $normalizedPortName = $portName.Trim().ToUpperInvariant()

        if (-not [string]::IsNullOrWhiteSpace($normalizedPortName)) {
            $portTable[$normalizedPortName] = [PSCustomObject]@{
                DeviceId = $normalizedPortName
                Name = $normalizedPortName
            }
        }
    }

    try {
        $pnpPorts = Get-CimInstance Win32_PnPEntity -ErrorAction Stop |
            Where-Object { (-not [string]::IsNullOrWhiteSpace($_.Name)) -and ($_.Name -match '\((COM\d+)\)') }

        foreach ($pnpPort in $pnpPorts) {
            $normalizedPortName = $matches[1].Trim().ToUpperInvariant()

            $portTable[$normalizedPortName] = [PSCustomObject]@{
                DeviceId = $normalizedPortName
                Name = $pnpPort.Name
            }
        }
    }
    catch {
    }

    return @($portTable.Values | Sort-Object @{ Expression = {
        if ($_.DeviceId -match '(\d+)$') {
            return [int]$matches[1]
        }

        return [int]::MaxValue
    } }, @{ Expression = { $_.DeviceId } })
}

function Resolve-Esp32SerialPort {
    param(
        [string]$Port = "",

        [bool]$AutoDetectWhenMissing = $false
    )

    $normalizedPort = $Port.Trim()
    $useAutoDetection = $false

    if ([string]::IsNullOrWhiteSpace($normalizedPort)) {
        $useAutoDetection = $AutoDetectWhenMissing
    }
    elseif ("AUTO" -ieq $normalizedPort) {
        $useAutoDetection = $true
    }

    if (-not $useAutoDetection) {
        return $normalizedPort
    }

    $availablePorts = @(Get-Esp32AvailableSerialPorts)

    if (0 -eq $availablePorts.Count) {
        throw "No serial ports were detected. Connect the board and rerun tools/esp32/list-serial-ports.ps1."
    }

    if (1 -ne $availablePorts.Count) {
        $availablePortList = ($availablePorts | ForEach-Object { $_.DeviceId }) -join ", "
        throw "Automatic serial-port selection requires exactly one detected port, but found: $availablePortList. Update esp32Project.serialPort in .vscode/settings.json or pass -Port explicitly."
    }

    return $availablePorts[0].DeviceId
}

function Get-Esp32ProjectElfPath {
    param(
        [Parameter(Mandatory = $true)]
        [string]$ProjectDir,

        [string]$ElfPath = ""
    )

    $repositoryRoot = Get-Esp32RepositoryRoot

    if (-not [string]::IsNullOrWhiteSpace($ElfPath)) {
        return Resolve-Esp32Path -BasePath $repositoryRoot -PathValue $ElfPath
    }

    $resolvedProjectDir = Resolve-Esp32Path -BasePath $repositoryRoot -PathValue $ProjectDir
    $projectName = Split-Path -Path $resolvedProjectDir -Leaf

    return (Join-Path $resolvedProjectDir (Join-Path "build" ($projectName + ".elf")))
}