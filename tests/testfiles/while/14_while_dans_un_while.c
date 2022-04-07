int main(){
    int x = 10;
    int iter = 0;
    int y = 10;
    while (x > 0)
    {
        x = x - 1;
        while (y > 0){
            y = y -1;
        }
        iter = iter + 1;
    }
    return iter;
}