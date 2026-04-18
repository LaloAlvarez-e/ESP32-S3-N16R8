[CmdletBinding(PositionalBinding = $false)]
param(
    [string]$ProjectDir = "hello_world_project",
    [string]$IdfPath = "",
    [string]$Port = "",
    [string]$Baud = "",
    [Parameter(Position = 0, ValueFromRemainingArguments = $true)]
    [string[]]$IdfArguments
)

$ErrorActionPreference = "Stop"

. (Join-Path $PSScriptRoot "common.ps1")

if (($null -eq $IdfArguments) -or (0 -eq $IdfArguments.Count)) {
    throw "Provide one or more idf.py arguments such as build, flash, or monitor."
}

$repositoryRoot = Get-Esp32RepositoryRoot
$resolvedProjectDir = Resolve-Esp32Path -BasePath $repositoryRoot -PathValue $ProjectDir

Import-Esp32IdfEnvironment -IdfPath $IdfPath | Out-Null

$idfExecutablePath = Resolve-Esp32ExecutablePath -ExecutableName "idf.py"
$idfCommandArguments = @()
$requiresSerialPort = $false

foreach ($idfArgument in $IdfArguments) {
    if ($idfArgument -in @("flash", "monitor", "erase-flash", "app-flash", "bootloader-flash", "partition-table-flash")) {
        $requiresSerialPort = $true
        break
    }
}

$resolvedSerialPort = Resolve-Esp32SerialPort -Port $Port -AutoDetectWhenMissing $requiresSerialPort

if (-not [string]::IsNullOrWhiteSpace($resolvedSerialPort)) {
    $idfCommandArguments += @("-p", $resolvedSerialPort)
}

if (-not [string]::IsNullOrWhiteSpace($Baud)) {
    $idfCommandArguments += @("-b", $Baud)
}

$idfCommandArguments += $IdfArguments

Push-Location $resolvedProjectDir

try {
    & $idfExecutablePath @idfCommandArguments
}
finally {
    Pop-Location
}