$OUTPUT = "./output/main.c"
$INPUTS = @()

Get-ChildItem -Path "./input/*" | ForEach-Object {
    $INPUTS += $_.FullName
}

Write-Host ./snapshot/lopc $OUTPUT $INPUTS
./snapshot/lopc $OUTPUT $INPUTS