#include <stdio.h>
#include <string.h>


char *strndup(const char *s, size_t n);
// #define NULL (void *)0

char* longestCommonPrefix(char** strs, int strsSize) {
    int i = 0, j = 0;

    char *first_str = strs[0];
    int common_length = strlen(first_str);
    int match_count = 0;

    for (i = 1; i < strsSize; i++)
    {
        for (j = 0; j < common_length && strs[i][j]; j++)
        {
            if (first_str[j] == strs[i][j]) match_count++;
            else break;
        }

        if (match_count == 0) return "";

        common_length = match_count;
        match_count = 0;
    }
    return strndup(first_str, common_length);
}


int main(void) {
    char *strs[] = {"cir", "car"};

    printf("%s\n", longestCommonPrefix(strs, 2));
}
