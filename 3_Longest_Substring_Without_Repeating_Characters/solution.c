#include <string.h>

int lengthOfLongestSubstring(char* s) {
    unsigned char checker[256] = {0};
    int i = 0, maxVal = 0, j = 0, currCnt;

    while (s[i]) {
        currCnt = 0;

        for (j = i; s[j]; j++) {
            if (checker[s[j]] != 0) break;
            checker[s[j]] = 1;
            currCnt++;
        }
        maxVal = currCnt > maxVal ? currCnt : maxVal;
        memset(checker, 0, sizeof(checker));
        i++;
    }
    return maxVal;
}