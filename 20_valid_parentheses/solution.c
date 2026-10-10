#include <stdbool.h>
#include <stdio.h>

#define PSEUDO_STACK_SZ 10001

bool isValid(char* s) {
    int s_idx = -1, i = 0;

    char stck[PSEUDO_STACK_SZ] = {0};

    while(s[i]) {
        
        if (s[i] == '[' || s[i] == '(' || s[i] == '{') stck[++s_idx] = s[i];
        else {
                if (s_idx == -1) return false;

                if ((s[i] == ']' && stck[s_idx] != '[') 
                || (s[i] == ')' && stck[s_idx] != '(' )
                || (s[i] == '}' && stck[s_idx] != '{')
            )
            {
                return false;
            }
            s_idx--;
        }
        i++;
    }
    return s_idx == -1 ? true : false;
}

int main(void) {
    printf("%d\n", isValid("{[]}"));
}