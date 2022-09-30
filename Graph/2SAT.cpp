struct SAT{ // 1-based 
    int n;
    vector<vector<int>> g, rg;
    bool ok = true;
    vector<bool> ans;
    
    void init(int _n){
        n = _n;
        g.resize(2 * n + 1);
        rg.resize(2 * n + 1);
        ans.resize(n + 1);
    }
    int neg(int v){
        return v <= n ? v + n : v - n;
    }
    void addEdge(int u, int v){
        g[u].eb(v);
        rg[v].eb(u);
    }
    void addClause(int a, int b){
        addEdge(a, b);
        addEdge(neg(b), neg(a));
    }
    void build(){
        vector<bool> vst(n + 1);
        vector<int> tmp, scc(n + 1, -1);
        int cnt = 1;
        function<void(int)> dfs = [&](int now){
            vst[now] = true;
            for(int i : rg[now]){
                if(vst[i]) continue;
                dfs(i);
            }
            tmp.pb(now);
        };
        for(int i = 1; i <= 2 * n; i++){
            if(!vst[i]) dfs(i);
        }
        reverse(iter(tmp));
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
        for(int i = 1; i <= n; i++){
            if(scc[i] == scc[neg(i)]){
                ok = false;
                return;
            }
            if(scc[i] < scc[neg(i)]) ans[i] = true;
            else ans[i] = false;
        }
    }

};
