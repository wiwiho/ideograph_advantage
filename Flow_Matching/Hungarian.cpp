int c[maxn][maxn]; //hungarian algorithm in O(n^3)
                   //1 base
int lx[maxn], ly[maxn], mx[maxn], my[maxn];
bool vx[maxn], vy[maxn];
int slack[maxn];
int tot;
bool dfs(int n, bool ch) {
  if (vx[n]) return false;
  vx[n] = 1;
  for (int v = 1;v <= tot;v++) {
    slack[v] = min(slack[v], lx[n] + ly[v] - c[n][v]);
    if (lx[n] + ly[v] - c[n][v] > 0) continue;
    vy[v] = 1;
    if (!my[v] || dfs(my[v], ch)) {
      if (ch) mx[n] = v, my[v] = n;
      return true;
    }
  }
  return false;
}
int main() {
  for (int i = 1;i <= n;i++) {
    for (int j = 1;j <= n;j++) vx[j] = vy[j] = 0;
    for (int j = 1;j <= n;j++) slack[j] = 1<<30; 
    if (dfs(i, 1)) continue;
    bool aug = 0;
    while (!aug) {
      for (int j = 1;j <= n;j++) {
        if (!vy[j] && slack[j] == 0) { 
          vy[j] = 1;
          if (dfs(my[j], 0)) {
            aug = 1;
            break;
          }
        }
      }
      if (aug) break;
      int delta = 1<<30;
      for (int j = 1;j <= n;j++) {
        if (!vy[j]) delta = min(delta, slack[j]);
      }
      for (int j = 1;j <= n;j++) {
        if (vx[j]) lx[j] -= delta;
        if (vy[j]) ly[j] += delta;
        else {
          slack[j] -= delta;
          if (slack[j] == 0 && !my[j]) aug = 1; 
        }
      }
    }
    for (int j = 1;j <= n;j++) vx[j] = vy[j] = 0;
    dfs(i, 1);
  }
}    
