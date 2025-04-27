<#
.SYNOPSIS
  Export all source files under src\ into a Word doc with darker, syntax-highlighted code blocks,
  automatically handling an existing output file.

.DESCRIPTION
  Scans the "src" directory (relative to wherever you run this script),
  emits each file’s base name as a "## filename" header + a fenced code block,
  deletes any existing $OutDoc before invoking Pandoc with the "zenburn" style.

.PARAMETER SrcDir
  The directory to scan (default: "src").

.PARAMETER OutDoc
  The name of the output .docx file (default: "code-export.docx").

.PARAMETER Highlight
  Pandoc highlight style (default: "zenburn" → darker background).
#>

param(
    [string]$SrcDir    = "src",
    [string]$OutDoc    = "code-export.docx",
    [string]$Highlight = "zenburn"
)

# ensure Pandoc is available
if (-not (Get-Command pandoc -ErrorAction SilentlyContinue)) {
    Write-Error "Pandoc not found. Install it from https://pandoc.org/installing.html"
    exit 1
}

# if output exists, try to remove it
if (Test-Path $OutDoc) {
    try {
        Remove-Item $OutDoc -Force -ErrorAction Stop
    }
    catch {
        Write-Warning "Cannot overwrite '$OutDoc'. It may be open in another application. Please close it and rerun."
        exit 1
    }
}

# build and pipe Markdown into Pandoc
$mdStream = Get-ChildItem -Path $SrcDir -Recurse -File -Include *.cpp,*.hpp,*.c,*.h |
    Sort-Object FullName |
    ForEach-Object {
        # only the file name, not full path
        "## $($_.Name)"
        '```cpp'
        Get-Content $_ | ForEach-Object { "    $_" }
        '```'
        ''
    }

# run Pandoc
$mdStream | pandoc -f markdown -t docx `
                  --highlight-style="$Highlight" `
                  -o "$OutDoc"

if ($LASTEXITCODE -eq 0) {
    Write-Host "✅ Generated '$OutDoc' with style '$Highlight'"
} else {
    Write-Error "Pandoc failed (exit code $LASTEXITCODE)."
    exit $LASTEXITCODE
}
