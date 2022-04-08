#include<stdio.h>

int main() {
    char c = getchar();
	int a = 8;
	int b;
	if (c=='y') {
		int a = 7;
		b = a;
	} else {
		b = a;
	}
    return b; 
}