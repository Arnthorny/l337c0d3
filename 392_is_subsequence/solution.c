#include <stdbool.h>

bool isSubsequence(char* s, char* t) {
    int j = 0, i;

    for (i = 0; t[i]; i++)
    {
        if (s[j] && (s[j] == t[i])) j++;
        
    }
    if(s[j] == '\0') return true;
    
    return false;
}