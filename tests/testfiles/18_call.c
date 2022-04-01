int test() {
    int a = 26;
    return a*3;
}
int calc(int i) {
    return i*3;
}
int ultrafunc(int i, int j, int k, int l, int m, int n) {
    return i+j+k+l+m+n;
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
    return calc(27)*test()+a+b+c+d+e+f+test()+ultrafunc(1,2,3,4,5,6);
}
