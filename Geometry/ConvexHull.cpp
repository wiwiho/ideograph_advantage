vector<int> getConvexHull(vector<pdd>& pts){
	vector<int> id(SZ(pts));
	iota(iter(id), 0);
	sort(iter(id), [&](int x, int y){ return pts[x] < pts[y]; });
	vector<int> hull;
	for(int tt = 0; tt < 2; tt++){
		int sz = SZ(hull);
		for(int j : id){
			pdd p = pts[j];
			while(SZ(hull) - sz >= 2 && ori(pts[hull.end()[-2]], pts[hull.back()], p) <= 0)
				hull.pop_back();
			hull.pb(j);
		}
		hull.pop_back();
		reverse(iter(id));
	}
	return hull;
}
