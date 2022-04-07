int hi (int a, int b, int c, int p) {
    a = b * c + p%b;

}

int main(){
    int b = hi(2,3,4,5);
    return b;
}