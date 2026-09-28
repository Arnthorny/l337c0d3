int scoreOfString(char* s) {
 int i = 0, total = 0;
 char curr = 0, next = 0;
 
 for (i = 0; s[i + 1]; i++)
 {
    curr = s[i];
    next = s[i + 1];
    total += (curr - next) >= 0 ? (curr - next) : -(curr - next);
 }
 return total;
}