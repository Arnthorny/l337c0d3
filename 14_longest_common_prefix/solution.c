typedef struct word_s
{
  struct word_s *next[128]; /* 128 to cover all alphabets including other chars */
  int value;
} word_t;


#define MAX_NO_WORDS 120001
#define LONGEST_WORD 64
#define NULL (void *)0

int check_trie(word_t *c_node, char *word, int idx) 
{
	int val;
	unsigned c;

	/* Is there a val > 0 at end of word. If yes, word in trie */
	if (word[idx] == '\0' && c_node) return c_node->value;

	if (!c_node) return -1;

	c = word[idx];
	val = check_trie(c_node->next[c], word, idx + 1);

	return val;

}

word_t *insert_in_trie(word_t **root, char *word, word_t pool[],
		int value, int *pool_idx, int idx)
{
	unsigned c;
	word_t *c_node;

	c = word[idx];

	if (*root == NULL) 
	{
		*root = &pool[*pool_idx];
		*pool_idx = *pool_idx + 1; 
	}
	c_node = *root;

	if (word[idx + 1] == '\0')
	{
		c_node->value = value;
		return c_node;
	}

	c_node->next[idx] = insert_in_trie(&(c_node->next[c]), word, pool,
			value, pool_idx, idx + 1);

	return c_node;
}

char* longestCommonPrefix(char** strs, int strsSize) {
    word_t root = {0};
    int i = 0;

    static char all_words[LONGEST_WORD][MAX_NO_WORDS] = {0};
	static word_t trie_pool[MAX_NO_WORDS] = {0};
	int n_words = 0, pool_idx = 0;

    char comm_pref[201] = {0} ;

    for (i = 0; i < strsSize; i++)
    {
        insert_in_trie(&root, strs[i], trie_pool, i, &pool_idx, 0);
    }
    
}