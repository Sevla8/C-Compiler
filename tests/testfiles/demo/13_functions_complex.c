int hi (int a, int b, int c, int p) {
    a = b * c + p%b;
    return a * p * c;
}

int hello (int c){
    int b = hi (10,20,1,2) - c;
    return b;
}

int main(){
    int b = hello (2);
    return b;
}