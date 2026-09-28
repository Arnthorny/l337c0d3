#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>


#define TBL_SIZE 100003
// #define TBL_SIZE 16384
#define WORD_MAX_LEN 10001

typedef struct hash_node_s
{
    char *val;
    int len_bucket;
    struct hash_node_s *next;
} hash_node_t;

uint32_t hash_int_array_fnv1a(char *str) {
    int arr[26] = {0}, i = 0;
    size_t len = 26;
    
    while (str[i])
    arr[str[i++] - 'a'] += 1;
    
    
    // FNV-1a constants for 32-bit hashes
    uint32_t hash = 2166136261U; 
    const uint32_t FNV_PRIME = 16777619U;

    for (size_t i = 0; i < len; i++) {
        // Option A: Hash element as a raw 32-bit integer block
        hash ^= (uint32_t)arr[i];
        hash *= FNV_PRIME;
    }

    return hash;
}


void add_node(hash_node_t *table[], char *val, int *no_of_anag_grp) {
    unsigned key;
    hash_node_t *head, *new_node;
    
    // key = hash_int_array_fnv1a(val) & (TBL_SIZE - 1);
    key = hash_int_array_fnv1a(val) % TBL_SIZE;

    new_node = calloc(1, sizeof(*new_node));
    new_node->next = NULL;
    new_node->len_bucket = 1;
    new_node->val = val;

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
    char *strs[] = {"obtuseness","chill"};

    // char *strs[] = {"a"};
    int strsSize = 2;

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