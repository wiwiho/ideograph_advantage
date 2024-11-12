ICPC codebook used by team fruit_advantages from National Taiwan University

Compile: `scripts/compile.sh`

Partial hash:

- Scope hash: If a line ends with `// SCOPE HASH`, `SCOPE HASH` will be replaced with the hash value of the region from this line to the line containing the matching right bracket of the **last** left bracket on this line.
- Part hash: If a line is equal to `// == PART HASH ==`, `PART HASH` will be replaced with the hash value of the region from this line to the next `// == PART HASH ==` or end of file.


