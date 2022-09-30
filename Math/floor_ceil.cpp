int floor_div(int a,int b){
	return a/b-(a%b&&a<0^b<0);
}
int ceil_div(int a,int b){
	return a/b+(a%b&&a<0^b>0);
}
