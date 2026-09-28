#include <stdio.h>

/**
 * Finds the length of the longest substring containing no repeated characters.
 *
 * Intuition:
 * We maintain a sliding window [lPtr, rPtr] that always contains unique
 * characters.
 *
 * - rPtr expands the window by adding one character at a time.
 * - checker[] keeps track of how many times each character occurs in the
 *   current window.
 * - If adding s[rPtr] creates a duplicate, we shrink the window from the
 *   left by moving lPtr forward until the duplicate is removed.
 * - After restoring the "all unique" property, the current window length is
 *   rPtr - lPtr + 1. We update maxVal if this is the longest window seen.
 *
 * Because each character is added to and removed from the window at most once,
 * the algorithm runs in O(n) time. The checker array has a fixed size of 256,
 * so the auxiliary space is O(1).
 *
 * @param s Null-terminated string to search.
 * @return Length of the longest substring with all unique characters.
 */
int lengthOfLongestSubstring(char* s) {
    // checker[c] stores the number of occurrences of character c
    // in the current sliding window.
    unsigned char checker[256] = {0};

    int maxVal = 0;
    int lPtr = 0;
    int rPtr = 0;

    while (s[rPtr]) {
        // Expand the window by adding the character at rPtr.
        checker[s[rPtr]]++;

        // If this character is now duplicated, shrink the window
        // from the left until all characters are unique again.
        while (checker[s[rPtr]] > 1) {
            checker[s[lPtr]]--;
            lPtr++;
        }

        // The current window [lPtr, rPtr] contains only unique characters.
        int currLen = rPtr - lPtr + 1;
        maxVal = currLen > maxVal ? currLen : maxVal;

        // Move the right pointer to expand the window on the next iteration.
        rPtr++;
    }

    return maxVal;
}


int main(void) {
    printf("%d\n", lengthOfLongestSubstring("bbbbb"));
    // return 1;
}