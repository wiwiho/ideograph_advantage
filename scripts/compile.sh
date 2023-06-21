#!/usr/bin/env bash

set -e

if [[ ! -f main.tex ]]; then
    echo "Please execute the script at ideograph_advantage/"
    exit 1
fi

echo "Check unused files"
scripts/check_usage.sh
echo "Compile main.tex..."
texfot latexmk -xelatex main.tex
echo "Done"

