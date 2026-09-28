#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define TBL_SIZE 128
#define WORD_MAX_LEN 10001

typedef struct hash_node_s
{
    char *val;
    int len_bucket;
    struct hash_node_s *next;
} hash_node_t;

int naive_hash_fn(char *str) {
    int sum_str = 0, i = 0;

    while (str[i])
    sum_str += str[i++];

    return sum_str;
}

int is_valid_bucket(char *head_val, char *val){
    char letters[26] = {0};
    int i = 0;

    if (strlen(head_val) != strlen(val)) return 0;

    // Count the occurence of each letter in both words
    while (head_val[i])
    letters[head_val[i++] - 'a'] += 1;

    i = 0;

    while (val[i]){
        if (letters[val[i] - 'a'] == 0) return 0; 
        letters[val[i++] - 'a'] += 1;
    }

    for (i = 0; i < 26; i++)
    if(letters[i] % 2) return 0;
    
    return 1;

}

// Return number of anagram groups

void add_node(hash_node_t *table[], char *val, int *no_of_anag_grp) {
    int key;
    hash_node_t *head, *new_node;
    
    key = naive_hash_fn(val) % TBL_SIZE;

    new_node = calloc(1, sizeof(*new_node));
    new_node->next = NULL;
    new_node->len_bucket = 1;
    new_node->val = val;

    // Find bucket to place val. Key from naive_hash may not yield valid bucket placement
    // so traverse table until you find valid placement or empty bucket
    while (1)
    {
        if(!table[key] || is_valid_bucket(table[key]->val, val))
        break;

        key = (key + 1) % TBL_SIZE;
    }

    if (!table[key]) {
        table[key] = new_node;

        (*no_of_anag_grp)++;
        return;
    }
    

    // Add new node atop linked list
    head = table[key];
    table[key] = new_node;
    new_node->next = head;
    new_node->len_bucket += head->len_bucket;

    return;    
}


void create_groups(hash_node_t *table[], char ***groups_arr, int *group_sizes) {
    int i = 0, j = 0, k = 0;
    char **tmp_arr = NULL;
    hash_node_t *head = NULL;

    // TIP: Maybe track the keys(idxs) with buckets so you don't do full table scan
    for (i = 0; i < TBL_SIZE; i++)
    {
        head = table[i];
        if (!head) continue;

        tmp_arr = calloc(head->len_bucket, sizeof(*tmp_arr));
        group_sizes[k] = head->len_bucket;

        j = 0;

        // Populate groups
        while (head)
        {
            tmp_arr[j++] = head->val;
            head = head->next;
        }

        // Add group to array of groups
        groups_arr[k++] = tmp_arr;
        
    }
    
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char*** groupAnagrams(char** strs, int strsSize, int* returnSize, int** returnColumnSizes) {
    
    hash_node_t *tbl[TBL_SIZE] = {NULL};
    char ***groups = NULL;
    int *group_sizes = NULL, i = 0, j = 0;
    *returnSize = 0;


    for (i = 0; i < strsSize; i++) add_node(tbl, strs[i], returnSize);
    
    groups = calloc((*returnSize), sizeof(*groups));
    
    
    group_sizes = calloc((*returnSize), sizeof(*group_sizes));
    
    create_groups(tbl, groups, group_sizes);
    *returnColumnSizes = group_sizes;
    

    return groups;
    
}

int main(void) {
    // char *strs[] = {"eat","tea","tan","ate","nat","bat"};
    // char *strs[] = {"a", "a", "ab"};

    char *strs[] = {"a"};
    int strsSize = 1;

    int returnSize = 0;
    int *returnColumnSize = NULL;

    char ***group_anag = NULL;

    group_anag = groupAnagrams(strs, strsSize, &returnSize, &returnColumnSize);
    printf("%d %d\n", returnSize, returnColumnSize[0]);
    
    for (int i = 0; i < returnSize; i++)
    {
        printf("[");
        for (int j = 0; j < returnColumnSize[i]; j++) printf("\"%s\",", group_anag[i][j]);
        printf("]\n");
    }
    

}