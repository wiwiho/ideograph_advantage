#!/usr/bin/env bash

if [[ ! -f main.tex ]]; then
    echo "Please execute the script at ideograph_advantage/"
    exit 1
fi

IFS=$'\n'
files=($(tree -fi))

for file in "${files[@]}"; do
    if [[ ! "$file" =~ .cpp$ ]] && [[ ! "$file" =~ .tex$ ]] && [[ ! "$file" =~ rc$ ]]; then
        continue
    fi
    if [[ "$file" = "./main.tex" ]]; then
        continue
    fi
    cat main.tex | grep "${file:2}" > /dev/null
    if [[ $? -ne 0 ]]; then
        echo "Warning: file $file is not in main.tex"
    fi
done
