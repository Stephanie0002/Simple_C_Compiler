int a[5];
int main(){
	a[0] = 1;
	a[1] = 2;
	a[2] = 3;
	a[3] = 4;
	a[4] = 5;
	int cnt;
	cnt = 4;
	int sum;
	sum = 0;
	while( cnt > 1 ){
		sum = sum + a[cnt];
		cnt = cnt - 1;
	}
	return sum;
}
