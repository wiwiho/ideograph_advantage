int ifloor(int a,int b){
	return a / b - (a % b && (a < 0) ^ (b < 0));
}
int iceil(int a,int b){
	return a / b + (a % b && (a < 0) ^ (b > 0));
}
