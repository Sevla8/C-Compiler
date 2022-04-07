

int hello (int c){
    return c - 2;
}

int main(){
    int b = hello (2) + hello (4) + hello (2) + hello (1);
    return b;
}