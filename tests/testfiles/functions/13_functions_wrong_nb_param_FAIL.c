int hi (int a, int b, int c, int p) {
    a = b * c + p%b;
    return a;

}

int main(){
    int b = hi(2);
    return b;
}