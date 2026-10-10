#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define LOWER_ALPHA_LEN 26

/**
 * Determines whether s2 contains a permutation of s1 as a substring.
 *
 * Algorithm Kind:
 *     Fixed-Size Sliding Window + Frequency Counting
 *
 * Intuition:
 *
 * A permutation of s1 must contain exactly the same characters as s1
 * with exactly the same frequencies, but the characters may appear in
 * a different order.
 *
 * For example:
 *
 *     s1 = "ab"
 *
 *     Valid permutations:
 *         "ab"
 *         "ba"
 *
 * Therefore, instead of generating permutations, we can compare the
 * frequency of each character.
 *
 * `alpha_hash` stores the frequency of each lowercase letter in s1.
 *
 * `hsh_check` stores the frequency of each lowercase letter in the
 * current window of s2.
 *
 * Since every permutation of s1 has exactly the same length as s1,
 * the solution uses a fixed-size sliding window whose size is
 * `strlen(s1)`.
 *
 * ---------------------------------------------------------------
 * Sliding Window:
 *
 * `lP` represents the left boundary of the window and `rP` represents
 * the right boundary.
 *
 * While the window is smaller than the length of s1, characters are
 * simply added to `hsh_check`.
 *
 * Once the window reaches the required size:
 *
 *     1. Add the new character at `rP`.
 *     2. Compare the frequency arrays.
 *     3. If they are identical, the current window is a permutation
 *        of s1, so return true.
 *     4. Remove the character at `lP`.
 *     5. Move both pointers forward.
 *
 * This keeps the window size constant.
 *
 * ---------------------------------------------------------------
 * Why frequency comparison works:
 *
 * Suppose:
 *
 *     s1 = "ab"
 *     current window = "ba"
 *
 * Both have the same frequencies:
 *
 *     a -> 1
 *     b -> 1
 *
 * Therefore, even though their ordering differs, the window is a
 * permutation of s1.
 *
 * `memcmp()` compares all 26 frequency values to determine whether
 * the two frequency arrays are identical.
 *
 * ---------------------------------------------------------------
 * Time Complexity:
 *
 * Let n = length of s1 and m = length of s2.
 *
 * Building `alpha_hash` takes O(n).
 *
 * Each character of s2 enters the sliding window once and leaves it
 * at most once, giving O(m) window processing.
 *
 * However, `memcmp()` compares all 26 entries whenever the window
 * reaches the required size. Since the alphabet size is fixed at 26,
 * each comparison is O(26), which is effectively O(1).
 *
 * Therefore:
 *
 *     O(n + m)
 *
 * Because the alphabet contains a fixed 26 lowercase letters.
 *
 * ---------------------------------------------------------------
 * Space Complexity:
 *
 * Both frequency arrays contain exactly 26 integers:
 *
 *     alpha_hash -> O(26)
 *     hsh_check  -> O(26)
 *
 * Since the alphabet size is fixed:
 *
 *     O(1)
 *
 * auxiliary space.
 */
bool checkInclusion(char* s1, char* s2) {
    int alpha_hash[LOWER_ALPHA_LEN] = {0};
    int hsh_check[LOWER_ALPHA_LEN] = {0};

    int i = 0, lP = 0, rP = 0;

    //Count number of occurences for each letter of s1
    for (i = 0; s1[i]; i++) alpha_hash[s1[i] - 'a']++;

    while (s2[rP])
    {
        if (rP - lP < i - 1) {
            hsh_check[s2[rP] - 'a']++; // Add current window items to hash
            rP++;
            continue; // Window not large enough
        }

        hsh_check[s2[rP] - 'a']++;
        if(memcmp(alpha_hash, hsh_check, sizeof(*hsh_check) * LOWER_ALPHA_LEN) == 0) return true;
        
        hsh_check[s2[lP] - 'a']--; 
        rP++; lP++;
    }
    return false;
}

int main(void){
    printf("%d\n", checkInclusion("horse", "ros"));
}
