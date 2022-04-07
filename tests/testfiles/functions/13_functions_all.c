void print_int(int x)
{
    if (x < 0)
    {
        putchar('-');
        x = -x;
    }
    if (x / 10 != 0)
        print_int(x / 10);
    putchar(x % 10 + '0');
}

char addchar(char a, char b)
{
    return a+b;
}

int addint(int a, int b)
{
    return a+b;
}

int mulint(int a, int b)
{
    return a*b;
}

char mulchar(char a, char b)
{
    return a*b;
}

int power(int a, char p)
{
    int n = 1;
    while (p>0) {
        n = n * a;
        p -= 1;
    }
    return n;
}

int sqrt(int a) {
    int n = 0;
    while (a>=(n+1)*(n+1)) {
        n += 1;
    }
    return n;
}

int main()
{
    char c, d;
    int a = 32, b = 27, n = 35, p = 28;
    char e;
    print_int('c'+'c'+'c'+'c');
    putchar(10);
    print_int(c = 'c'+'c'+'c'+'c');
    putchar(10);
    print_int((d=192)+(e=28));
    putchar(10);
    print_int(d+e+d);
    putchar(10);
    print_int(addchar(127,127));
    putchar(10);
    print_int(addchar(n,p));
    putchar(10);
    print_int(addint(mulint(a,b), 23));
    putchar(10);
    print_int(addint(23, mulchar(a,b)));
    putchar(10);
    print_int(addchar(mulchar(a,b), 23));
    putchar(10);
    print_int(power(8,4));
    putchar(10);
    print_int(sqrt(100));
    putchar(10);
    print_int(sqrt(99));
    putchar(10);
    print_int(sqrt(a*b*c*d*e));
    putchar(10);
    return 0;
}