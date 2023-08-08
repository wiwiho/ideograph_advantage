void reorder_poly(vector<pdd>& pnts){
	int mn = 0;
	for(int i = 1; i < (int)pnts.size(); i++)
		if(pnts[i].Y < pnts[mn].Y || (pnts[i].Y == pnts[mn].Y && pnts[i].X < pnts[mn].X)) 
			mn = i;
	rotate(pnts.begin(), pnts.begin() + mn, pnts.end());
}

vector<pdd> minkowski(vector<pdd> P, vector<pdd> Q){
	reorder_poly(P);
	reorder_poly(Q);
	int psz = P.size();
	int qsz = Q.size();
	P.pb(P[0]); P.pb(P[1]); Q.pb(Q[0]); Q.pb(Q[1]);
	vector<pdd> ans;
	int i = 0, j = 0;
	while(i < psz || j < qsz){
		ans.pb(P[i] + Q[j]);
		int t = sgn(cross(P[i + 1] - P[i], Q[j + 1] - Q[j]));
		if(t >= 0) i++;
		if(t <= 0) j++;
	}
	return ans;
}
