int main(){
    int a =5;
    {
        int b=8;
    }
    a=33;
    if(a==33){
        a=2;
        
    }
    if(a==3){ 
        int c=3;
    } 
    return a;
}