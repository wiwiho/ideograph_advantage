void reorder_poly(vector<Pt>& pnts){
    int mn = 0;
    for(int i = 1; i < (int)pnts.size(); i++){
        if(pnts[i].Y < pnts[mn].Y || (pnts[i].Y == pnts[mn].Y && pnts[i].X < pnts[mn].X)) 
            mn = i;
    }
    rotate(pnts.begin(), pnts.begin() + mn, pnts.end());
}

vector<Pt> minkowski(vector<Pt> P, vector<Pt> Q){
    reorder_poly(P);
    reorder_poly(Q);
    int psz = P.size();
    int qsz = Q.size();
    P.eb(P[0]);
    P.eb(P[1]);
    Q.eb(Q[0]);
    Q.eb(Q[1]);
    vector<Pt> ans;
    int i = 0, j = 0;
    while(i < psz || j < qsz){
        ans.eb(P[i] + Q[j]);
        int t = sgn(cross(P[i + 1] - P[i], Q[j + 1] - Q[j]));
        if(t >= 0) i++;
        if(t <= 0) j++;
    }
    return ans;
}
