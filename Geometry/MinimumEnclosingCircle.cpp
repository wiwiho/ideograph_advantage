using NumType = ld;
pair<Pt, ld> MinimumEnclosingCircle(vector<Pt> &pts){
	random_shuffle(iter(pts));
	Pt c = pts[0];
	ld r = 0;
	for(int i = 1; i < SZ(pts); i++){
		if(abs(pts[i] - c) <= r) continue;
		c = pts[i]; r = 0;
		for(int j = 0; j < i; j++){
			if(abs(pts[j] - c) <= r) continue;
			c = (pts[i] + pts[j]) / 2;
			r = abs(pts[i] - c);
			for(int k = 0; k < j; k++){
				if(abs(pts[k] - c) > r)
					c = circumcenter(pts[i], pts[j], pts[k]);
			}
		}
	}
	return {c, r};
}
