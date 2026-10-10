#include <stdio.h>

/**
 * Finds the length of the longest substring that can be converted
 * into a string containing the same character by replacing at most
 * `k` characters.
 *
 * Intuition:
 *
 * The solution considers each unique character in the string as the
 * character that we want the current window to consist of.
 *
 * For a chosen character, [lPtr, rPtr] represents a sliding window.
 * Every character different from the chosen character requires one
 * replacement.
 *
 * `tmp_k` tracks the number of replacements still available:
 *
 *     - When s[rPtr] is different from the chosen character,
 *       `tmp_k` is decremented.
 *     - When the number of required replacements becomes negative,
 *       the left pointer is moved forward until the window becomes
 *       valid again.
 *
 * The length of every valid window is:
 *
 *     rPtr - lPtr + 1
 *
 * and `cur_max` stores the longest valid window for the current
 * chosen character.
 *
 * `all_max` stores the largest result found across all unique
 * characters.
 *
 * ---------------------------------------------------------------
 * Example:
 *
 *     s = "AABABBA", k = 1
 *
 *     If 'A' is the chosen character:
 *
 *         "AABA"
 *
 *     contains one 'B', so replacing that 'B' with 'A' gives:
 *
 *         "AAAA"
 *
 *     Therefore, the window length is 4.
 *
 * The algorithm repeats this process for each distinct character
 * found in the string.
 *
 * ---------------------------------------------------------------
 * Why the sliding window works:
 *
 * For a fixed target character, a window is valid when the number
 * of characters that differ from that target is <= k.
 *
 * When a new character enters the window, it may consume one of
 * the available replacements. If more than k replacements are
 * required, the left side of the window is moved forward until
 * the number of required replacements is valid again.
 *
 * ---------------------------------------------------------------
 * Time Complexity:
 *
 * Let n be the length of `s` and U be the number of unique
 * characters.
 *
 * The first loop that gathers unique characters takes O(n).
 *
 * The sliding-window process scans the string once for each unique
 * character, giving O(U * n).
 *
 * Since the input consists of uppercase English letters, U <= 26,
 * so this is effectively O(26n), which simplifies to:
 *
 *     O(n)
 *
 * for this particular problem.
 *
 * ---------------------------------------------------------------
 * Space Complexity:
 *
 * `uniq_letters` contains at most 26 characters, while the
 * remaining variables use constant space.
 *
 * Therefore:
 *
 *     O(1)
 *
 * auxiliary space.
 */
int characterReplacement(char* s, int k) {
    char uniq_letters[26] = {0};
    int uniq_l_cnt = 0, i = 0, j = 0;
    int lPtr = 0, rPtr = 0, cur_max = 0, tmp_k = 0, all_max = 0, tmp_len = 0;

    // Gather all unique letters
    for (i = 0; s[i]; i++)
    {
        if(uniq_letters[s[i] - 'A'] == 0) uniq_l_cnt++;
        uniq_letters[s[i] - 'A'] = s[i];
    }

    for (j = 0; j < uniq_l_cnt; j++)
    {
        lPtr = 0;
        rPtr = 0;
        cur_max = 0;
        tmp_k = k;

        while (s[rPtr])
        {
            while (tmp_k < 0) {
                if(s[lPtr] != uniq_letters[j]) {
                    tmp_k++; lPtr++;
                    break;
                }
                lPtr++;
                
            }
            tmp_len = rPtr - lPtr + 1;

            if(s[rPtr] != uniq_letters[j]) tmp_k--;

            if(tmp_k >= 0) cur_max = cur_max > tmp_len ? cur_max : tmp_len;
            rPtr++;
        }
        all_max = all_max > cur_max ? all_max : cur_max;
    }       
    return all_max;
}


int main(void) {
    char *s = "ABBB";
    int k = 2;


    printf("%d\n", characterReplacement(s, k));
}