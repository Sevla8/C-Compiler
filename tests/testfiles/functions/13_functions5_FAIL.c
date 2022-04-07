void hi () {

}

int hello (int x){
    x = 10;
    return x;
}

int main(){
    return hello (hi());
}