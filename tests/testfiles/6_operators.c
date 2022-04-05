int main() {
   int c = 15;
   int b;
   int a = b = c;
   a = (b+4)*(c+8);
   a = c*7+5;
   a = a + a * 6;
   return a;
}
