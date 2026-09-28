#include <stdbool.h>
#include <string.h>
#include <stdio.h>

/**
 * Checks whether a character is an alphanumeric character.
 *
 * Intuition:
 * A valid character is one that belongs to one of three ranges:
 *   - '0' to '9'
 *   - 'a' to 'z'
 *   - 'A' to 'Z'
 *
 * This is used to ignore spaces, punctuation, and other non-alphanumeric
 * characters when checking whether a string is a palindrome.
 */
bool isValidAlphaNumeric(char c) {
    if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) return true;
    return false;
}

/**
 * Converts an uppercase alphabetic character to lowercase.
 *
 * Intuition:
 * In ASCII, uppercase and lowercase letters have the same relative
 * position in their respective ranges. Therefore, the difference
 * between 'A' and 'a' can be added to an uppercase character to
 * obtain its lowercase equivalent.
 *
 * If the character is already lowercase or is not a letter, it is
 * returned unchanged.
 */
char toLowerCase(char c) {
    if (c >= 'A' && c <= 'Z') return (c - 'A') + 'a'; 
    return c;
}

/**
 * Determines whether a string is a palindrome while ignoring
 * non-alphanumeric characters and letter case.
 *
 * Intuition:
 * Use two pointers:
 *   - lPtr starts at the beginning of the string.
 *   - rPtr starts at the end of the string.
 *
 * At each step:
 *   1. Move lPtr forward until it points to an alphanumeric character.
 *   2. Move rPtr backward until it points to an alphanumeric character.
 *   3. Convert both characters to lowercase and compare them.
 *   4. If they differ, the string cannot be a palindrome.
 *   5. If they match, move both pointers toward the center.
 *
 * This works because a palindrome reads the same from both directions.
 * Non-alphanumeric characters do not participate in the comparison,
 * and converting both characters to lowercase makes the comparison
 * case-insensitive.
 *
 * The process stops when the two pointers meet or cross, meaning every
 * relevant pair of characters has been successfully compared.
 *
 * Time Complexity: O(n)
 *   Each pointer moves through the string at most once.
 *
 * Space Complexity: O(1)
 *   Only a constant amount of additional memory is used.
 */
bool isPalindrome(char* s) {
    int lPtr = 0, rPtr = strlen(s) - 1;

    while (lPtr < rPtr)
    {
        if (!isValidAlphaNumeric(s[lPtr])) {
            lPtr++; continue;
        }

        if (!isValidAlphaNumeric(s[rPtr])) {
            rPtr--; continue;
        }

        if(toLowerCase(s[lPtr]) != toLowerCase(s[rPtr])) {
            return false;
            }
        lPtr++;
        rPtr--;
    }

    return true;
}
int main (void) {
    printf("%d\n", isPalindrome("0P"));
}