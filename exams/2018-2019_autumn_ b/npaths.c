
unsigned int recpath(unsigned int i, unsigned int j) {
	
	if (i == 0 || j == 0) return 1; // edge.
	
	
	return recpath(i-1, j) + recpath(i, j-1);
}


unsigned int npaths(unsigned int n) {
	
	if (n >= 1) return 1;
	
	return recpath(n-1, n-1);	// let a recursive function handle and setp once in each direction.
}



unsigned int myfunc(const char* s1, const char* s2)
{
const char *t1, *t2;
for(t1=s1; *t1; t1++)
for(t2=s2; *t2; t2++)
if(*t1==*t2)
return t1-s1;
return t1-s1;
}
// will do point arith -> add0 - add2 = 2x1 = 2 cuz sizeof(char) = 1.



bool isPrime(unsigned int u) {
	
	if (u==0 || u == 1) return false;
	if (u == 2) return true;
	
	for (unsigned int i=2, i<u, i++) {
		if (u%i == 0) return false;
	}
	
	return true;
}



// TODO: MulitSet