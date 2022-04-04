int test() {
    int a = 26;
    return a*3;
}
int calc(int i) {
    return i*3;
}
int ultrafunc(int i, int j, int k, int l, int m, int n, int o, int p, int q, int r, int s) {
    return i-j+k+l-m+n+o+p-q+r+s;
}
int extrafunc(int i, int j, int k, int l, int m, int n, int o, int p) {
    return i-j+k+l-m+n+o+p;
}
int main(){
    putchar(72);
    putchar(101);
    putchar(108);
    putchar(108);
    putchar(111);
    putchar(32);
    putchar(119);
    putchar(111);
    putchar(114);
    putchar(108);
    putchar(100);
    putchar(33);
    putchar(10);
    int a = 18,b=1,c=1,d=1,e=1,f=1;
    return calc(27)*test()+a+b+c+d+e+f+test()+extrafunc(1,2,3,4,5,6,7,8)+ultrafunc(1,2,3,4,5,6,7,8,9,10,11)+ultrafunc(1,2,3,4,5,6,7,8,9,10,11);
}
