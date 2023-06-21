#!/usr/bin/env bash

if [[ ! -f main.tex ]]; then
    echo "Please execute the script at ideograph_advantage/"
    exit 1
fi

check_file(){
    file=$1
    if [[ "$file" = "./main.tex" ]]; then
        return
    fi
    cat main.tex | grep "${file:2}" > /dev/null
    if [[ $? -ne 0 ]]; then
        echo "Warning: file $file is not in main.tex"
    fi
}

PATTERN='.*(.cpp|.tex|rc)'
find . -regextype posix-egrep -regex "$PATTERN" | while read file; do
    check_file "$file"
done

