#!/usr/bin/env bash

set -e

if [[ ! -f main.tex ]]; then
    echo "Please execute the script at ideograph_advantage/"
    exit 1
fi

scripts/check.sh
echo "Compile main.tex..."
xelatex -halt-on-error main.tex > /dev/null
echo "Compile main.tex..."
xelatex -halt-on-error main.tex > /dev/null
echo "Done"

