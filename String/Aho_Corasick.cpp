const int SIGMA = 26;
struct AC_Automaton {
  // child: trie, next: automaton
  vector<vector<int>> child, next;
  vector<int> fail, cnt, ord;
  int total = 0;
  int newnode() {
    return total++;
  }
  void init(int len) {  // len >= 1 + total len
    child.assign(len, vector<int>(26, -1));
    next.assign(len, vector<int>(26, -1));
    fail.assign(len, -1); cnt.assign(len, 0);
    ord.clear();
    newnode(); 
  }
  int input(string &s) {
    int cur = 0;
    for (char c : s) {
      if (child[cur][c - 'A'] == -1)
        child[cur][c - 'A'] = newnode();
      cur = child[cur][c - 'A'];
    }
    return cur; // return the end node of string
  }
  void make_fl() {
    queue<int> q;
    q.push(0), fail[0] = -1;
    while(!q.empty()) {
      int R = q.front();
      q.pop(); ord.pb(R);
      for (int i = 0; i < SIGMA; i++)
        if (child[R][i] != -1) {
          int X = next[R][i] = child[R][i], Z = fail[R];
          while (Z != -1 && child[Z][i] == -1) 
            Z = fail[Z];
          fail[X] = Z != -1 ? child[Z][i] : 0;
          q.push(X);
        }
        else next[R][i] = R ? next[fail[R]][i] : 0;
    }
  }
  void solve() {
    for (int i : ord | views::reverse)
      if (i) cnt[fail[i]] += cnt[i];
  }
}; 
