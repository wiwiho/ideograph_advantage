ll ifloor(ll a, ll b){
	return a / b - (a % b && (a < 0) ^ (b < 0));
}
ll iceil(ll a, ll b){
	return a / b + (a % b && (a < 0) ^ (b > 0));
}
