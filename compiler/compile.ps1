$OUTPUT = "./output/main.c"
$INPUTS = @()

Get-ChildItem -Path "./input/*" | ForEach-Object {
    $INPUTS += $_.FullName
}

./snapshot/lopc $OUTPUT $INPUTS
