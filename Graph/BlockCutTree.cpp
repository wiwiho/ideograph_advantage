struct BlockCutTree{
    vector<vector<int>> tree; // 1-based
    vector<int> node;
    vector<int> type; // 0:square, 1:circle

    bool iscut(int v){
        return type[node[v]] == 1;
    }

    vector<int> getbcc(int v){
        if(!iscut(v)) return {node[v]};
        vector<int> ans;
        for(int i : tree[node[v]]) 
            ans.pb(i);
        return ans;
    }
    
    void build(int n, vector<vector<int>>& g){
        tree.resize(2 * n + 1);
        type.resize(2 * n + 1);
        node.resize(n + 1, -1);
        vector<int> in(n + 1);
        vector<int> low(n + 1);
        stack<int> st;
        
        int ts = 1;
        int bcc = 1;
        auto addv = [&](int id, int v){
            if(node[v] == -1){
                node[v] = id;
                return;
            }
            if(type[node[v]] == 0){
                int o = node[v];
                node[v] = bcc++;
                type[node[v]] = 1;
                tree[o].pb(node[v]);
                tree[node[v]].pb(o);
            }
            tree[id].pb(node[v]);
            tree[node[v]].pb(id);
        };
        function<void(int, int)> dfs = [&](int now, int p){
            in[now] = low[now] = ts++;
            st.push(now);
            int child = 0;
            for(int i : g[now]){
                if(i == p) continue;
                if(in[i]){
                    low[now] = min(low[now], in[i]);
                    continue;
                }
                child++;
                dfs(i, now);
                low[now] = min(low[now], low[i]);
                
                if(low[i] >= in[now]){
                    int nowid = bcc++;
                    while(true){
                        int x = st.top();
                        st.pop();
                        addv(nowid, x);
                        if(x == i) break;
                    }
                    addv(nowid, now);
                }
            }
            if(child == 0 && now == p) addv(bcc++, now);
        };
        dfs(1, 1);
    }
};
