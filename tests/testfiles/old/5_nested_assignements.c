int main() {
   int c = 15;
   int b;
   int a = b = c;
   a;
   c = 12;
   a = c;
   c = b = 14;
   return a;
}
