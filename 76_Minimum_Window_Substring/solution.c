#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MAX_ASCII 256

char* minWindow(char* s, char* t) {
    int i = 0, lP = 0, rP = 0;

    /*
     * t_dict stores the number of times each character is required
     * by t.
     *
     * temp_dict stores the number of times each required character
     * currently occurs inside the sliding window [lP, rP].
     *
     * The arrays are indexed using the character's ASCII value.
     */
    int t_dict[MAX_ASCII] = {0}, temp_dict[MAX_ASCII] = {0};
    
    /*
     * have:
     *     Number of distinct characters whose required frequencies
     *     have been satisfied in the current window.
     *
     * need:
     *     Number of distinct characters that must be satisfied.
     *
     * found:
     *     Indicates whether at least one valid window has been found.
     */
    int have = 0, need = 0, found = 0;

    /*
     * r_min stores information about the smallest valid window found:
     *
     * r_min[0] -> starting index
     * r_min[1] -> ending index
     * r_min[2] -> length of the window
     *
     * INT_MAX ensures that the first valid window will be
     * smaller than the initial value.
     */
    int r_min[3] = {0, 0, INT_MAX};

    /*
     * Stores the length of the current window if it is smaller
     * than the best window found so far.
     */
    int tmp_min = 0;

    /*
     * Pointer to the dynamically allocated result string.
     */
    char *ans = NULL;

    /*
     * If t is longer than s, s cannot possibly contain all
     * characters required by t.
     */
    if(strlen(t) > strlen(s)) return "";

    /*
     * Build the frequency table for t.
     *
     * need is incremented only when a character appears for
     * the first time.
     *
     * Example:
     *
     * t = "AABC"
     *
     * t_dict['A'] = 2
     * t_dict['B'] = 1
     * t_dict['C'] = 1
     * need = 3
     */
    for (i = 0; t[i]; i++) {
        if (t_dict[t[i]] == 0) need++;
        t_dict[t[i]]++;
    }

    /*
     * Expand the sliding window by moving rP from left to right.
     */
    while (s[rP])
    {
        /*
         * Only characters that are required by t need to be
         * tracked in the current window.
         */
        if(t_dict[s[rP]] != 0) {
            temp_dict[s[rP]] += 1;

            /*
             * A character becomes satisfied when its frequency
             * in the current window reaches the frequency
             * required by t.
             *
             * We do not increment have for extra occurrences.
             *
             * Example:
             *
             * t requires 2 A's:
             *
             * temp_dict['A'] = 1 -> not satisfied
             * temp_dict['A'] = 2 -> satisfied, have++
             * temp_dict['A'] = 3 -> still one satisfied character
             */
            if(t_dict[s[rP]] == temp_dict[s[rP]]) have++;
        }

        /*
         * When have == need, every distinct character required
         * by t has reached its required frequency.
         *
         * Therefore, the current window is valid.
         *
         * We now try to shrink the window from the left to find
         * the smallest valid window.
         */
        while (have == need)
        {
            /*
             * At least one valid window exists.
             */
            found = 1;

            /*
             * Calculate the length of the current valid window
             * and compare it with the best window found so far.
             */
            tmp_min = (rP - lP + 1) < r_min[2] ? (rP - lP + 1) : r_min[2];

            /*
             * If the current window is smaller, save its
             * starting index, ending index, and length.
             */
            if (r_min[2] != tmp_min){
                r_min[0] = lP; r_min[1] = rP; r_min[2] = tmp_min;
            }

            /*
             * Remove the character at the left edge of the
             * current window.
             *
             * Only required characters affect the validity
             * of the window.
             */
            if (t_dict[s[lP]] != 0)
            {
                temp_dict[s[lP]] -= 1;

                /*
                 * If removing this character causes its frequency
                 * to fall below the required frequency, the window
                 * is no longer valid.
                 *
                 * Therefore, decrement have.
                 */
                if(temp_dict[s[lP]] < t_dict[s[lP]]) have--;

            }

            /*
             * Move the left boundary to the right, shrinking
             * the window.
             */
            lP++;
        }

        /*
         * Expand the window by moving the right boundary right.
         */
        rP++;
    }

    /*
     * If no valid window was found, return an empty string.
     */
    if (!found) return "";

    /*
     * Allocate enough memory for the smallest window plus
     * one byte for the null terminator.
     */
    ans = calloc((r_min[1] - r_min[0] + 1) + 1, sizeof(*ans));

    /*
     * Copy the smallest window from s into ans.
     */
    strncpy(ans, &(s[r_min[0]]), (r_min[1] - r_min[0] + 1));

    /*
     * ans is null-terminated because calloc initialized the
     * allocated memory to zero and one extra byte was allocated.
     */
    return ans;
}

int main(void) {
    printf("%s\n", minWindow("a", "b"));
}