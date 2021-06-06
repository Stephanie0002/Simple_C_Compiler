//sample:input n numbers,then print the sum of them;
int n;
int a[10];
int main()
{
	n = 3;
	if (n > 10) 
		return 1;
	int s;
	int i;
	i = 0;
	s = i;
	while (i < n) { 
		a[i] = i;
		s = s + a[i]; 
		i=i+1;
	} 
	int newline;
	newline = 10;
	return s;
}
