#define TBL_SIZE 1024
#define NULL (void *) 0

typedef struct hash_node_s
{
    int val;
    struct hash_node_s *next;
} hash_node_t;

void add_node(hash_node_t *table[], int val) {
    int key;
    hash_node_t *head, *new_node;
    
    key = (val % TBL_SIZE) >= 0 ? (val % TBL_SIZE) : -(val % TBL_SIZE);

    new_node = malloc(sizeof(*new_node));
    new_node->next = NULL;
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

char isValPresent(hash_node_t *table[], int val) {
    int key;
    hash_node_t *bckt_head;

    key = (val % TBL_SIZE) >= 0 ? (val % TBL_SIZE) : -(val % TBL_SIZE);

    bckt_head = table[key];
    if (!bckt_head) return 0;

    while (bckt_head)
    {
        if (bckt_head->val == val){
            return 1;
        }
        bckt_head = bckt_head->next;
    }
    return 0;
}



char containsDuplicate(int* nums, int numsSize) {
    int i = 0, *ret_arr;
    
    hash_node_t *tbl[TBL_SIZE] = {NULL};

    for (i = 0; i < numsSize; i++)
    {
        if (isValPresent(tbl, nums[i])) return 1;
        else add_node(tbl, nums[i]);
        
    }
    return 0;   
}