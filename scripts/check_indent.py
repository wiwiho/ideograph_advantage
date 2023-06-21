import sys

if len(sys.argv) != 2:
    print("Usage: python check_indent.py <file>")
    exit(0)

filename = sys.argv[1]
tab = False
space = False
minlength = 0
with open(filename) as f:
    for line in f:
        length = 0
        for i in range(len(line)):
            if line[i] != ' ' and line[i] != '\t':
                length = i
                break
            elif line[i] == ' ':
                space = True
            else:
                tab = True
        if length == 0:
            continue
        if minlength == 0 or length < minlength:
            minlength = length

RED = '\033[0;31m'
NC = '\033[0m'
if tab and space:
    print(f"{RED}{filename}: mix{NC}")
elif tab:
    print(f"{filename}: tab")
else:
    if minlength != 0 and minlength != 2:
        print(f"{RED}", end='')
    print(f"{filename}: space width {minlength}{NC}")
