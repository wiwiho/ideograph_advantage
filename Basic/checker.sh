#!/usr/bin/env bash
set -e
while :; do
    python3 gen.py > test.txt
    diff <(./a.exe < test.txt) <(./b.exe < test.txt)
done
