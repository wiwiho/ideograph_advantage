struct PAM { // 1-base
    int sz, tot, last, n;
    // make a new node with len = l.
    int node(int l) {  
        sz++;
        fill(ch[sz].begin(), ch[sz].end(), 0);
        len[sz] = l;
        fail[sz] = 0;
        cnt[sz] = 0;
        dep[sz] = 0;
        return sz;
    }
    // initialize
    void clear() { 
        sz = -1;
        last = 0;
        s[tot = 0] = '$';
        node(0);
        node(-1);
        fail[0] = 1;
    }

    // find the maximum palidrome suffix
    int getfail(int x) {
        while (s[tot - len[x] - 1] != s[tot]) x = fail[x];
        return x;
    }

    vector<int> len, fail, cnt, dep, dif, slink;
    vector<vector<int>> ch;
    vector<char> s;
    vector<mint> dp, g;

    PAM(int N) : n(N+5), len(n), fail(n), cnt(n), dep(n), 
        dif(n), slink(n), ch(n, vector<int>(26)), s(n),
        dp(n), g(n) {
        clear();
        dp[0] = 1;
    }

    // make the automaton
    void insert(char c) {
        s[++tot] = c;
        int now = getfail(last);
        if (!ch[now][c - 'a']) {
            int x = node(len[now] + 2);
            fail[x] = ch[getfail(fail[now])][c - 'a'];
            dep[x] = dep[fail[x]] + 1;
            ch[now][c - 'a'] = x;
            dif[x] = len[x] - len[fail[x]];
            if (dif[x] == dif[fail[x]])
                slink[x] = slink[fail[x]];
            else
                slink[x] = fail[x];
        }
        last = ch[now][c - 'a'];
        cnt[last]++;

        for(int x = last; x > 1; x = slink[x]){
            g[x] = dp[tot - len[slink[x]] - dif[x]];
            if(dif[x] == dif[fail[x]]) 
                // change below
                g[x] += g[fail[x]];
            if(tot % 2 == 0)  dp[tot] += g[x];
        }
    }
};
