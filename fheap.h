#ifndef FHEAP_H
#define FHEAP_H


#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

struct Node;

struct Node {
    struct Node *slibing;
    struct Node *children;
    long int value;
    size_t degree;
    unsigned char cut; // 0 or 1 or 2
};

void fh_InitNode(struct Node *node, const long int value);

/**
 * @brief merge two linked list
 * @param head_a start of first sorted linked list
 * @param tail_a end of first sorted linked list
 * @param head_b start of second sorted linked list
 * @param tail_b end of second sorted linked list
 * @param cmp compare function
 * @warning tail must be present(NULL)
 * @return merged linked list
 */
struct Node *merge(struct Node *head_a, const struct Node *tail_a, struct Node *head_b, const struct Node *tail_b,
                   const int cmp(struct Node *a, struct Node *b));

/**
 * @brief merge sort
 * @param head start of linked list
 * @param tail end of linked list
 * @param cmp compare function
 * @warning tail must be present(NULL)
 */
void fh_MergeSort(struct Node **head, struct Node *tail, const int cmp(struct Node *a, struct Node *b));

/**
 * @brief compare by value of node
 * @param a node a
 * @param b node b
 * @return 1 if a>b, 0 if a==b, -1 if a<b
 */
const int fh_CmpByValue(struct Node *a, struct Node *b);

/**
 * @brief consolidate children and children's children
 * @param parent parent node
 * @return 1 if a consolidation is performed, 0 otherwise
 */
int fh_Consolidate(struct Node *parent);

struct SearchTrace {
    size_t depth;
    struct Node *ancestors[8 * sizeof(size_t)];
};

/**
 * @brief insert a value
 * @param parent parent Node
 * @param value value to insert
 */
void fh_Insert(struct Node *parent, long int value);

/**
 * @brief search for a value
 * @param parent parent Node
 * @param value value to search for
 * @param trace trace, only valid on found
 * @warning result must be initialized
 * @return NULL if not found, pointer to that node if found
 */
struct Node *fh_Search(struct Node *parent, const long int value, struct SearchTrace *trace);

/**
 * @brief fdelete a node
 * @param trace trace
 * @param target target node
 */
void fh_Delete(const struct SearchTrace *trace, struct Node *target);

/**
 * @param trace trace
 * @param target target to decrease
 * @param value value to decrease
 */
void fh_Decrease(const struct SearchTrace *trace, struct Node *target, long int value);

/**
 * @brief print level order
 * @param root root node
 */
void fh_PrintLevelOrder(const struct Node *root);

#endif
