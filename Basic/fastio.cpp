char readchar() {
  const int N = 1<<20;
  static char buf[N];
  static char *p = buf , *end = buf;
  if(p == end) {
    if((end = buf + fread(buf , 1 , N , stdin)) == buf) return EOF;
    p = buf;
  }
  return *p++;
}

const int buf_size = 524288;
struct Writer {
  char buf[buf_size]; int size = 0, ret;
  void flush() { ret = write(1, buf, size); size = 0; }
  void _flush(int sz) { if (sz + size > buf_size) flush(); }
  void write_char(char c) { _flush(1); buf[size++] = c; }
  void write_int(int x) {
    const int len = 20;
    _flush(len); int ptr = 0;
    if (x < 0) buf[size++] = '-', x = -x;
    if (x == 0) buf[size + (ptr++)] = '0';
    else for (; x; x /= 10) buf[size + (ptr++)] = '0' + x % 10;
    reverse(buf + size, buf + size + ptr);
    size += ptr;
  }
}; // remember to call flush
