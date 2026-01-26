#!/bin/bash

OUTPUT=./output/main.c
INPUTS=""

for FILE in ./input/*
do
    INPUTS=$INPUTS' "'$FILE'"'
done

./snapshot/lopc $OUTPUT $INPUTS