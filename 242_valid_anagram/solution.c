#include <stdbool.h>

/**
 * Anagrams have exact same number of letters and letter repetitions
 * Thus incrementing the count of given letter present in a word
 * should be exactly cancelled out by decrementing the count of that letter
 * in its anagram word. Thus all letters should have a count of zero at the end.
 */

bool isAnagram(char* s, char* t) {
    int count_arr[26] = {0}, i = 0;

    while (*s || *t)
    {
        if(*s) {
            count_arr[*s - 'a']--;
            (*s++);
        }
        if(*t) {
            count_arr[*t - 'a']++;
            (*t++);
        }
    }
    for (i = 0; i < 26; i++)
    {
        if ((count_arr[i] != 0)) return false;
    }
    return true;   
    
        
}