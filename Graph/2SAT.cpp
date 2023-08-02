struct SAT{ // 0-based, [n, 2n) is neg of [0, n)
    int n;
    vector<vector<int>> g, rg;
    bool ok = true;
    vector<bool> ans;

    void init(int _n){
        n = _n;
        g.resize(2 * n);
        rg.resize(2 * n);
        ans.resize(n);
    }
    int neg(int v){
        return v < n ? v + n : v - n;
    }
    void addEdge(int u, int v){
        g[u].pb(v);
        rg[v].pb(u);
    }
    void addClause(int a, int b){
        addEdge(neg(a), b);
        addEdge(neg(b), a);
    }
    void build(){
        vector<bool> vst(2 * n, false);
        vector<int> tmp, scc(2 * n, -1);
        int cnt = 1;
        function<void(int)> dfs = [&](int now){
            vst[now] = true;
            for(int i : rg[now]){
                if(vst[i]) continue;
                dfs(i);
            }
            tmp.pb(now);
        };
        for(int i = 0; i < 2 * n; i++){
            if(!vst[i]) dfs(i);
        }
        reverse(all(tmp));
        function<void(int, int)> dfs2 = [&](int now, int id){
            scc[now] = id;
            for(int i : g[now]){
                if(scc[i] != -1) continue;
                dfs2(i, id);
            }
        };
        for(int i : tmp){
            if(scc[i] == -1) dfs2(i, cnt++);
        }
        debug(scc);
        for(int i = 0; i < n; i++){
            if(scc[i] == scc[neg(i)]){
                ok = false;
                return;
            }
            if(scc[i] < scc[neg(i)]) ans[i] = true;
            else ans[i] = false;
        }
    }

};
