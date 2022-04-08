#include<stdio.h>


int powerrec(int a, char p, int n)
{
	if (p==0) {
		return n;
	} else {
		return powerrec(a, p-1, n*a);
	}
}

int power(int a, char p)
{
    return powerrec(a, p, 1);
}

int main() {
	int a = 2;
    return power(a, 7); 
}