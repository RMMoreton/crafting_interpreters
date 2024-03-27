#include <stdint.h>
#include <stdlib.h>

#include "linked_list.h"

struct node {
    struct node* prev;
    struct node* next;
    char* data;
};

int Push(LinkedList** l, char* s) {
    // Keep track of whether we need to free the list before returning an
    // error.
    int newly_created = 0;
    struct node* n;
    // Make a new list if we need to.
    if (NULL == l) {
        // TODO: return a meaningful error.
        return -1;
    }
    if (NULL == *l) {
        *l = (LinkedList*)malloc(sizeof(LinkedList));
        if (NULL == l) {
            // TODO: return a meaningful error.
            return -1;
        }
        (*l)->head = NULL;
        (*l)->len = 0;
        newly_created = 1;
    }
    // Can we fit a new node?
    if ((*l)->len >= UINT8_MAX) {
        // TODO: return a meaningful error.
        return -1;
    }
    // Make a new node.
    n = (struct node*) malloc(sizeof(struct node*));
    if (NULL == n) {
        if (newly_created) {
            free(*l);
        }
        // TODO: return a meaningful error.
        return -1;
    }
    // Set up the node.
    n->prev = NULL;
    n->next = (struct node*)((*l)->head);
    n->data = s;
    // Push it into the list and we're done.
    if (NULL != n->next) {
        n->next->prev = n;
    }
    (*l)->head = n;
    (*l)->len++;
    return 0;
}

int Pop(LinkedList** l, char** s) {
    struct node* n;
    if (NULL == l || NULL == *l || NULL == (*l)->head) {
        // TODO: return a meaningful error.
        return -1;
    }
    // Get a temp reference to the head node.
    n = (struct node*)((*l)->head);
    // Remove it from the list.
    (*l)->head = n->next;
    (*l)->len--;
    // Remove the new head's `prev`, if necessary.
    if (NULL != n->next) {
        n->next->prev = NULL;
    }
    // Put the data into s, if possible.
    if (NULL != s) {
        *s = n->data;
    }
    free(n);
    return 0;
}

int FreeAll(LinkedList** l) {
    if (NULL == l || NULL == *l) {
        // TODO: return a meaningful error.
        return -1;
    }
    for (int i = 0; i < (*l)->len; i++) {
        Pop(l, NULL);
    }
    free(*l);
    *l = NULL;
    return 0;
}
