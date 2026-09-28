#include <stdlib.h>
#include <stdio.h>

#define MAX_NUM 10000
#define FREQ_ARR_SIZE ((MAX_NUM *2) + 1)
#define FAUX_HASH_TBL_SIZE 450

typedef struct faux_hash_node_s
{
    int val;
    struct faux_hash_node_s *next;
} faux_hash_node_t;

void add_node(faux_hash_node_t *table[], int val, int key) {
    faux_hash_node_t *head, *new_node;
    
    // key = hash_int_array_fnv1a(val) & (TBL_SIZE - 1);
    // key = val > 0 ? val : MAX_NUM - val;

    new_node = calloc(1, sizeof(*new_node));
    new_node->next = NULL;
    new_node->val = val;

    if (!table[key]) {
        table[key] = new_node;
        return;
    }
    

    // Add new node atop linked list
    head = table[key];
    table[key] = new_node;
    new_node->next = head;

    return;    
}

int *create_k_arr(int k, faux_hash_node_t *f_tbl[], int *k_arr_size) {
    int i, track_k_arr = 0;
    faux_hash_node_t *tmp_head;
    
    int *ret_arr = calloc(k, sizeof(*ret_arr));

    for (i = FAUX_HASH_TBL_SIZE - 1; i >= 0 && k > 0; i--)
    {
        tmp_head = f_tbl[i];
        if (!tmp_head) continue;

        ret_arr[track_k_arr++] = tmp_head->val;
        k--;

        while (tmp_head->next && k > 0)
        {
            tmp_head = tmp_head->next;
            ret_arr[track_k_arr++] = tmp_head->val;
            k--;
        }
    }
    
    *k_arr_size = track_k_arr;
    return ret_arr;
}




/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* topKFrequent(int* nums, int numsSize, int k, int* returnSize) {
 int freq_arr[FREQ_ARR_SIZE] = {0}, i, val, idx, freq_val;
 faux_hash_node_t *f_tbl[FAUX_HASH_TBL_SIZE] = {NULL};

 int *ret_array = NULL;

 for (i = 0; i < numsSize; i++)
 {
    val = nums[i];

    // Account for negative numbers. -1 goes to index 10001 (MAX_NUM=10000)
    idx = val >= 0 ? val : MAX_NUM - val;
    freq_arr[idx] += 1;
}
 

 for (i = 0; i < FREQ_ARR_SIZE; i++)
 {
    freq_val = freq_arr[i];

    if (freq_val == 0) continue;
    
    // Remember negative numbers
    val = i <= MAX_NUM ? i : MAX_NUM - i;
    printf("%d->%d\n", freq_val, val);

    add_node(f_tbl, val, freq_val);
 }


 
 ret_array = create_k_arr(k, f_tbl, returnSize);

 return ret_array;
}


int main(void) {
    int nums[] = {-1, -1}, numsSize = 2;
    int k = 1, retSize = 0, i;

    int *retArr = topKFrequent(nums, numsSize, k, &retSize);

    printf("[");
    for (int i = 0; i < retSize; i++) printf("%d,", retArr[i]);
    printf("]\n");

}