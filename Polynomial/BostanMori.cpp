NTT<262144, 998244353, 3> ntt;
// Finds the k-th coefficient of P / Q in O(d log d log k)
// size of NTT has to > 2 * d
ll BostanMori(vector<ll> P, vector<ll> Q, long long k) {
    int d = max((int)P.size(), (int)Q.size() - 1);
    P.resize(d, 0);
    Q.resize(d + 1, 0); 
    int sz = (2 * d + 1 == 1 ? 2 : (1 << (__lg(2 * d) + 1)));
    while(k) {
        vector<ll> Qneg(sz);
        for(int i = 0; i < (int)Q.size(); i++){
            Qneg[i] = Q[i] * ((i & 1) ? -1 : 1);
            if(Qneg[i] < 0) Qneg[i] += mod;
        }
        ntt(Qneg, sz, false);

        vector<ll> U(sz), V(sz);
        for(int i = 0; i < (int)P.size(); i++)
            U[i] = P[i];
        for(int i = 0; i < (int)Q.size(); i++)
            V[i] = Q[i];

        ntt(U, sz, false);
        ntt(V, sz, false);
        for(int i = 0; i < sz; i++)
            U[i] = U[i] * Qneg[i] % mod;
        for(int i = 0; i < sz; i++)
            V[i] = V[i] * Qneg[i] % mod;
        ntt(U, sz, true);
        ntt(V, sz, true);

        for(int i = k & 1; i <= 2 * d - 1; i += 2)
            P[i >> 1] = U[i];
        for(int i = 0; i <= 2 * d; i += 2)
            Q[i >> 1] = V[i];
        k >>= 1;
    }
    return P[0] * ntt.minv(Q[0]) % mod;
}


