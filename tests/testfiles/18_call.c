int test() {
    putchar(67);
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
    int a = 18,b=1,c=1,d=1,e=1,f=1;
    return calc(27)*test()+a+b+c+d+e+f+test()+ultrafunc(1,2,3,4,5,6);
}
