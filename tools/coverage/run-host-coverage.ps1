[CmdletBinding()]
param(
    [string]$BuildDir = "build/host-coverage",
    [string]$ReportDir = "build/coverage",
    [ValidateSet("Debug", "RelWithDebInfo", "Release")]
    [string]$Configuration = "Debug",
    [string]$Generator = "Visual Studio 17 2022",
    [string]$Architecture = "x64",
    [switch]$Clean
)

$ErrorActionPreference = "Stop"

function Resolve-RepositoryPath {
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

$repositoryRoot = [System.IO.Path]::GetFullPath((Join-Path $PSScriptRoot "..\.."))
$resolvedBuildDir = Resolve-RepositoryPath -BasePath $repositoryRoot -PathValue $BuildDir
$resolvedReportDir = Resolve-RepositoryPath -BasePath $repositoryRoot -PathValue $ReportDir
$htmlReportDir = Join-Path $resolvedReportDir "html"
$coverageXmlPath = Join-Path $resolvedReportDir "coverage.xml"

$openCppCoverageCommand = Get-Command "OpenCppCoverage.exe" -ErrorAction SilentlyContinue
if ($null -eq $openCppCoverageCommand) {
    throw "OpenCppCoverage.exe was not found on PATH. Install OpenCppCoverage before running the coverage tool."
}

foreach ($commandName in @("cmake", "ctest")) {
    if ($null -eq (Get-Command $commandName -ErrorAction SilentlyContinue)) {
        throw "$commandName was not found on PATH. Install the required build tools before running the coverage tool."
    }
}

if ($Clean) {
    foreach ($pathToRemove in @($resolvedBuildDir, $resolvedReportDir)) {
        if (Test-Path $pathToRemove) {
            Remove-Item -Path $pathToRemove -Recurse -Force
        }
    }
}

New-Item -ItemType Directory -Path $resolvedBuildDir -Force | Out-Null
New-Item -ItemType Directory -Path $resolvedReportDir -Force | Out-Null

if (Test-Path $htmlReportDir) {
    Remove-Item -Path $htmlReportDir -Recurse -Force
}

if (Test-Path $coverageXmlPath) {
    Remove-Item -Path $coverageXmlPath -Force
}

Write-Host "Configuring host-side coverage build..."
& cmake -S $repositoryRoot -B $resolvedBuildDir -G $Generator -A $Architecture -DBUILD_TESTING=ON

Write-Host "Building host-side tests for coverage..."
& cmake --build $resolvedBuildDir --config $Configuration --parallel

$productionSourceRoots = @(
    "common_utils",
    "common_os",
    "common_driver",
    "sample_project"
)

$testSourceRoots = @(
    "common_utils\test",
    "common_os\test",
    "common_driver\test",
    "sample_project\test"
)

$coverageArguments = @(
    "--working_dir", $repositoryRoot,
    "--cover_children"
)

foreach ($sourceRoot in $productionSourceRoots) {
    $coverageArguments += @("--sources", (Join-Path (Join-Path $repositoryRoot $sourceRoot) "*"))
}

foreach ($testSourceRoot in $testSourceRoots) {
    $coverageArguments += @("--excluded_sources", (Join-Path (Join-Path $repositoryRoot $testSourceRoot) "*"))
}

if ($Configuration -ne "Debug") {
    $coverageArguments += "--optimized_build"
}

$coverageArguments += @(
    "--export_type", "html:$htmlReportDir",
    "--export_type", "cobertura:$coverageXmlPath",
    "--",
    "ctest",
    "--test-dir", $resolvedBuildDir,
    "-C", $Configuration,
    "--output-on-failure"
)

Write-Host "Running host-side coverage collection..."
& $openCppCoverageCommand.Source @coverageArguments

if (-not (Test-Path $coverageXmlPath)) {
    throw "OpenCppCoverage did not create the Cobertura report at $coverageXmlPath."
}

[xml]$coverageDocument = Get-Content -Path $coverageXmlPath
$coveredLineCount = [int]$coverageDocument.coverage."lines-covered"
$validLineCount = [int]$coverageDocument.coverage."lines-valid"

if ($validLineCount -gt 0) {
    $lineCoveragePercent = ($coveredLineCount / [double]$validLineCount) * 100.0
}
else {
    $lineCoveragePercent = 0.0
}

Write-Host (("Production line coverage: {0:N2}% ({1}/{2})" -f $lineCoveragePercent, $coveredLineCount, $validLineCount))
Write-Host "HTML report: $(Join-Path $htmlReportDir 'index.html')"
Write-Host "Cobertura report: $coverageXmlPath"