/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#define TBL_SIZE 1024
#define NULL (void *) 0

typedef struct hash_node_s
{
    int val;
    int idx;
    struct hash_node_s *next;
} hash_node_t;

void add_node(hash_node_t *table[], int val, int idx) {
    int key;
    hash_node_t *head, *new_node;
    
    key = (val % TBL_SIZE) >= 0 ? (val % TBL_SIZE) : -(val % TBL_SIZE);

    new_node = malloc(sizeof(*new_node));
    new_node->next = NULL;
    new_node->idx = idx;
    new_node->val = val;

    if (!table[key]) {
        table[key] = new_node;
        return;
    }
    head = table[key];
    while (head->next) head = head->next;

    head->next = new_node;
    return;    
}

hash_node_t *isValPresent(hash_node_t *table[], int val) {
    int key;
    hash_node_t *bckt_head;

    key = (val % TBL_SIZE) >= 0 ? (val % TBL_SIZE) : -(val % TBL_SIZE);

    bckt_head = table[key];
    if (!bckt_head) return NULL;

    while (bckt_head)
    {
        if (bckt_head->val == val){
            return bckt_head;
        }
        bckt_head = bckt_head->next;
    }
    return NULL;
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    int i = 0, *ret_arr;
    ret_arr = malloc(sizeof(int) * 2);
    *returnSize = 2;

    hash_node_t *tbl[TBL_SIZE] = {NULL}, *scnd_node = NULL;

    for (i = 0; i < numsSize; i++)
    {
        scnd_node = isValPresent(tbl, target - nums[i]);
        if (scnd_node && scnd_node->idx != i)
        {
         ret_arr[0] = i;
         ret_arr[1] = scnd_node->idx;
         break;
        }
        else add_node(tbl, nums[i], i);
        
    }
    return ret_arr;
}