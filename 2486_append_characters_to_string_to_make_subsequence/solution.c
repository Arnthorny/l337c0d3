
int appendCharacters(char* s, char* t) {
    int j = 0, i;

    for (i = 0; s[i]; i++)
    {
        if (t[j] && (t[j] == s[i])) j++;
        
    }
    
    return strlen(t) - j;
}