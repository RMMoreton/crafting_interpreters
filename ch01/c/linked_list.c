#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"

/*
 * Get the node at the given index. May return the dummy node.
 */
struct _node* ll_node_at(struct linked_list* l, uint8_t i) {
    struct _node* n;
    if (NULL == l || i > l->len) {
        return NULL;
    }
    // Iterate to the correct node starting at either the head or the tail,
    // whichever is closer.
    if (i <= (l->len+1) / 2) {
        n = l->head;
        for (; i > 0; i--) {
            n = n->next;
        }
    } else {
        n = l->tail;
        i = l->len - i;
        for (; i > 0; i--) {
            n = n->prev;
        }
    }
    return n;
}

struct linked_list* ll_new() {
    struct linked_list* l;
    struct _node* n;
    l = (struct linked_list*)malloc(sizeof(struct linked_list));
    if (NULL == l) {
        return NULL;
    }
    n = (struct _node*)malloc(sizeof(struct _node));
    if (NULL == n) {
        free(l);
        return NULL;
    }
    n->next = NULL;
    n->prev = NULL;
    n->data = NULL;
    l->head = n;
    l->tail = n;
    l->len = 0;
    return l;
}

int ll_push_left(struct linked_list* l, char* s) {
    return ll_push_at(l, s, 0);
}

int ll_push_right(struct linked_list* l, char* s) {
    return ll_push_at(l, s, l->len);
}

int ll_push_at(struct linked_list* l, char* s, uint8_t i) {
    struct _node* n, *n_at;
    if (NULL == l) {
        // TODO: return a meaningful error.
        return -1;
    }
    if (NULL == s) {
        // TODO: return a meaningful error.
        return -1;
    }
    // Can we fit a new node?
    if (l->len == UINT8_MAX) {
        // TODO: return a meaningful error.
        return -1;
    }
    // Can we push a node at the requested position?
    if (i < 0 || i > l->len) {
        // TODO: return a meaningful error.
        return -1;
    }
    // Make a new node.
    n = (struct _node*)malloc(sizeof(struct _node));
    if (NULL == n) {
        // TODO: return a meaningful error.
        return -1;
    }
    // Set up the node.
    n->data = strdup(s);
    if (NULL == n->data) {
        // We don't allow pushing NULL data, so this must be a malloc failure.
        free(n);
        // TODO: return a meaningful error.
        return -1;
    }
    // Push the node into the list.
    n_at = ll_node_at(l, i);
    n->next = n_at;
    n->prev = n_at->prev;
    n_at->prev = n;
    if (0 == i) {
        l->head = n;
    }
    if (l->len == i) {
        l->tail = n;
    }
    l->len = l->len + 1;
    return 0;
}

int ll_pop_left(struct linked_list* l, char** s) {
    return ll_pop_at(l, s, 0);
}

int ll_pop_right(struct linked_list* l, char** s) {
    return ll_pop_at(l, s, l->len - 1);
}

int ll_pop_at(struct linked_list* l, char** s, uint8_t i) {
    struct _node* n;
    if (NULL == l) {
        // TODO: return a meaningful error.
        return -1;
    }
    if (i < 0 || i >= l->len) {
        // TODO: return a meaningful error.
        return -1;
    }
    n = ll_node_at(l, i);
    // Fix references around the node and the head/tail.
    if (NULL != n->prev) {
        n->prev->next = n->next;
    } else {
        l->head = n->next;
    }
    if (NULL != n->next) {
        n->next->prev = n->prev;
    } else {
        l->tail = n->prev;
    }
    l->len = l->len - 1;
    // Put the data into s or free it.
    if (NULL != s) {
        *s = n->data;
    } else {
        // It shouldn't be possible to put NULL into a node's data, but...
        if (NULL != n->data) {
            free(n->data);
        }
    }
    // Free the node and we're done!
    free(n);
    return 0;
}

int ll_free_all(struct linked_list *l) {
    struct _node* n, *nt;
    if (NULL == l) {
        // TODO: return a meaningful error.
        return -1;
    }
    n = l->head;
    while (NULL != n) {
        if (NULL != n->data) {
            free(n->data);
        }
        nt = n->next;
        free(n);
        n = nt;
    }
    free(l);
    return 0;
}
