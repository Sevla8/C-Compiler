#include<stdio.h>

int power(int a, char p)
{
    int n = 1;
    while (p>0) {
        n = n * a;
        p -= 1;
    }
    return n;
}

int main() {
	int a = 2;
    return power(a, 7); 
}