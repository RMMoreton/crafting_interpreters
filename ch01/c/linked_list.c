#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"

struct linked_list* ll_new() {
    struct linked_list* l = (struct linked_list*) malloc(sizeof(struct linked_list));
    l->head = NULL;
    l->len = 0;
    return l;
}

int ll_push_left(struct linked_list* l, char* s) {
    struct _node* n;
    if (NULL == l) {
        // TODO: return a meaningful error.
        return -1;
    }
    // Can we fit a new node?
    if (l->len >= UINT8_MAX) {
        // TODO: return a meaningful error.
        return -1;
    }
    // Make a new node.
    n = (struct _node*) malloc(sizeof(struct _node));
    if (NULL == n) {
        // TODO: return a meaningful error.
        return -1;
    }
    // Set up the node.
    n->data = strdup(s);
    if (NULL == n->data) {
        free(n);
        // TODO: return a meaningful error.
        return -1;
    }
    n->prev = NULL;
    n->next = l->head;
    // Push it into the list and we're done.
    if (NULL != n->next) {
        n->next->prev = n;
    }
    l->head = n;
    l->len = l->len + 1;
    return 0;
}

int ll_pop_left(struct linked_list* l, char** s) {
    struct _node* n;
    if (NULL == l || NULL == l->head) {
        // TODO: return a meaningful error.
        return -1;
    }
    // Get a temp reference to the head node.
    n = l->head;
    // Remove it from the list.
    l->head = l->head->next;
    l->len = l->len - 1;
    // Remove the new head's `prev`, if necessary.
    if (NULL != l->head) {
        l->head->prev = NULL;
    }
    // Put the data into s if possible, else free it.
    if (NULL != s) {
        *s = n->data;
    } else {
        free(n->data);
    }
    // Free the node and we're done.
    free(n);
    return 0;
}

int ll_free_all(struct linked_list* l) {
    if (NULL == l) {
        // TODO: return a meaningful error.
        return -1;
    }
    while(l->len > 0) {
        ll_pop_left(l, NULL);
    }
    free(l);
    return 0;
}
