[CmdletBinding()]
param(
    [string]$ProjectDir = "hello_world_project",
    [string]$ElfPath = "",
    [string]$IdfPath = "",
    [string]$GdbPath = "",
    [string]$TargetAddress = "localhost:3333",
    [string]$BreakpointSymbol = "app_main"
)

$ErrorActionPreference = "Stop"

. (Join-Path $PSScriptRoot "common.ps1")

if ((-not [string]::IsNullOrWhiteSpace($IdfPath)) -or
    (-not [string]::IsNullOrWhiteSpace($env:IDF_PATH))) {
    Import-Esp32IdfEnvironment -IdfPath $IdfPath | Out-Null
}

$resolvedElfPath = Get-Esp32ProjectElfPath -ProjectDir $ProjectDir -ElfPath $ElfPath

if (-not (Test-Path $resolvedElfPath)) {
    throw "The ELF file was not found: $resolvedElfPath"
}

$resolvedGdbPath = Resolve-Esp32ExecutablePath -ExecutableName "xtensa-esp32s3-elf-gdb" -ConfiguredPath $GdbPath
$gdbArguments = @(
    "--quiet",
    $resolvedElfPath,
    "-ex", "set pagination off",
    "-ex", "set remotetimeout 10",
    "-ex", "target extended-remote $TargetAddress",
    "-ex", "monitor reset halt",
    "-ex", "load"
)

if (-not [string]::IsNullOrWhiteSpace($BreakpointSymbol)) {
    $gdbArguments += @("-ex", "thb $BreakpointSymbol")
}

$gdbArguments += @("-ex", "continue")

& $resolvedGdbPath @gdbArguments