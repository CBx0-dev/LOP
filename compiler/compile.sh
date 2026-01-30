#!/bin/bash

OUTPUT=./output/main.c
INPUTS=()

for FILE in ./input/*
do
    INPUTS+=("$FILE")
done

echo ./snapshot/lopc "$OUTPUT" "${INPUTS[@]}"
./snapshot/lopc "$OUTPUT" "${INPUTS[@]}"