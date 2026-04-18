[CmdletBinding()]
param(
    [string]$IdfPath = "",
    [string]$OpenOcdPath = "",
    [string]$OpenOcdScripts = "",
    [string]$OpenOcdConfig = "board/esp32s3-builtin.cfg",
    [string]$AdapterSpeedKHz = "",
    [switch]$ResumeTargetAfterStartup
)

$ErrorActionPreference = "Stop"

$liveAttachReadyMarker = "ESP32_LIVE_ATTACH_READY"

. (Join-Path $PSScriptRoot "common.ps1")

if ((-not [string]::IsNullOrWhiteSpace($IdfPath)) -or
    (-not [string]::IsNullOrWhiteSpace($env:IDF_PATH))) {
    Import-Esp32IdfEnvironment -IdfPath $IdfPath | Out-Null
}

$resolvedOpenOcdPath = Resolve-Esp32ExecutablePath -ExecutableName "openocd" -ConfiguredPath $OpenOcdPath
$resolvedOpenOcdScripts = Get-Esp32OpenOcdScriptsPath -OpenOcdScripts $OpenOcdScripts -OpenOcdExecutablePath $resolvedOpenOcdPath

Clear-Esp32StaleOpenOcdListeners

$openOcdArguments = @(
    "-s",
    $resolvedOpenOcdScripts,
    "-f",
    $OpenOcdConfig
)

if (-not [string]::IsNullOrWhiteSpace($AdapterSpeedKHz)) {
    $openOcdArguments += @(
        "-c",
        "adapter speed $AdapterSpeedKHz"
    )
}

if ($true -eq $ResumeTargetAfterStartup.IsPresent) {
    $openOcdArguments += @(
        "-c",
        "init",
        "-c",
        "reset run",
        "-c",
        "echo $liveAttachReadyMarker"
    )
}

& $resolvedOpenOcdPath @openOcdArguments