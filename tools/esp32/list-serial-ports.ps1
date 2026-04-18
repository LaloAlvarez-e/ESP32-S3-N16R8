[CmdletBinding()]
param()

$ErrorActionPreference = "Stop"

. (Join-Path $PSScriptRoot "common.ps1")

$availablePorts = @(Get-Esp32AvailableSerialPorts)

if (0 -eq $availablePorts.Count) {
    Write-Output "No serial ports detected."
}
else {
    $availablePorts | Format-Table DeviceId, Name -AutoSize
}