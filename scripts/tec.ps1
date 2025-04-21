param (
    [Parameter(Mandatory=$true)]
    [string]$EZFile
)

# Get full path and base name
$fullPath = Resolve-Path $EZFile
$baseName = [System.IO.Path]::GetFileNameWithoutExtension($fullPath)
$asmFile = "$baseName.asm"
$objFile = "$baseName.obj"
$exeFile = "$baseName.exe"

# Step 1: Convert .EZ to .asm using your .tec processor
Write-Host "Processing $EZFile with .tec..."
.\tec $EZFile > $asmFile

if (-not (Test-Path $asmFile)) {
    Write-Error "Failed to generate $asmFile"
    exit 1
}

# Step 2: Assemble with ml64
Write-Host "Assembling $asmFile..."
ml64.exe /c /Fo $objFile $asmFile

if (-not (Test-Path $objFile)) {
    Write-Error "Assembly failed"
    exit 1
}

# Step 3: Link with link.exe
Write-Host "Linking $objFile..."
link.exe /SUBSYSTEM:CONSOLE /OUT:$exeFile $objFile

if (-not (Test-Path $exeFile)) {
    Write-Error "Linking failed"
    exit 1
}

# Step 4: Run the executable
Write-Host "Running $exeFile..."
Start-Process -Wait -FilePath ".\$exeFile"
