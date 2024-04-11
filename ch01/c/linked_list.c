#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"

struct _node *ll_node_at(struct linked_list *l, uint8_t i) {
    struct _node *n;
    if (NULL == l || i >= l->len) {
        return NULL;
    }
    if (i <= l->len / 2) {
        n = l->head;
        while (i-- > 0) {
            n = n->next;
        }
    } else {
        n = l->tail;
        while (i++ < l->len-1) {
            n = n->prev;
        }
    }
    return n;
}

struct linked_list* ll_new() {
    struct linked_list *l = (struct linked_list *) malloc(sizeof(struct linked_list));
    if (NULL == l) {
        return NULL;
    }
    l->head = NULL;
    l->tail = NULL;
    l->len = 0;
    return l;
}

int ll_push_left(struct linked_list *l, char *s) {
    return ll_push_at(l, s, 0);
}

int ll_push_right(struct linked_list *l, char *s) {
    return ll_push_at(l, s, l->len);
}

int ll_push_at(struct linked_list *l, char *s, uint8_t i) {
    struct _node *n, *n_at;
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
    n = (struct _node *) malloc(sizeof(struct _node));
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
    // We're either pushing at head, tail, or somewhere in the middle.
    if (0 == i) {
        // Push to the head of the list (maybe update tail, too!).
        n->next = l->head;
        n->prev = NULL;
        if (NULL != l->head) {
            l->head->prev = n;
        } else {
            l->tail = n;
        }
        l->head = n;
    } else if (l->len == i) {
        // Push to the tail of the list (maybe update head, too!).
        n->next = NULL;
        n->prev = l->tail;
        if (NULL != l->tail) {
            l->tail->next = n;
        } else {
            l->head = n;
        }
        l->tail = n;
    } else {
        // Push somewhere in the middle.
        n_at = ll_node_at(l, i);
        if (NULL == n_at) {
            // This shouldn't be possible - we did bounds checking above.
            // TODO: return a meaningful error (if possible??).
            free(n->data);
            free(n);
            return -1;
        }
        n->prev = n_at->prev;
        n_at->prev = n;
        n->next = n_at;
    }
    l->len = l->len + 1;
    return 0;
}

int ll_pop_left(struct linked_list *l, char **s) {
    struct _node *n;
    if (NULL == l || NULL == l->head) {
        // TODO: return a meaningful error.
        return -1;
    }
    // Get a temp reference to the head node.
    n = l->head;
    // Remove it from the list.
    l->head = l->head->next;
    l->len = l->len - 1;
    // Remove the new head's `prev` or the list's tail.
    if (NULL != l->head) {
        l->head->prev = NULL;
    } else {
        l->tail = NULL;
    }
    // Put the data into s if possible, else free it.
    if (NULL != s) {
        *s = n->data;
    } else {
        // It shouldn't be possible to put NULL into a node's data, but...
        if (NULL != n->data) {
            free(n->data);
        }
    }
    // Free the node and we're done.
    free(n);
    return 0;
}

int ll_pop_right(struct linked_list *l, char **s) {
    struct _node *n;
    if (NULL == l || NULL == l->tail) {
        // TODO: return a meaningful error.
        return -1;
    }
    // Get a temp reference to the tail node.
    n = l->tail;
    // Remove it from the list.
    l->tail = l->tail->prev;
    l->len = l->len - 1;
    // Remove the new tail's `next` or the list's head.
    if (NULL != l->tail) {
        l->tail->next = NULL;
    } else {
        l->head = NULL;
    }
    // Put the data into s if possible, else free it.
    if (NULL != s) {
        *s = n->data;
    } else {
        // It shouldn't be possible to put NULL into a node's data, but...
        if (NULL != n->data) {
            free(n->data);
        }
    }
    // Free the node and we're done.
    free(n);
    return 0;
}

int ll_free_all(struct linked_list *l) {
    struct _node *n, *nt;
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

int ll_print(struct linked_list *l) {
    struct _node *n;
    uint8_t i = 0;
    if (NULL == l) {
        // TODO: return a meaningful error.
        return -1;
    }
    n = l->head;
    printf("List:\n");
    while (NULL != n) {
        printf(" %d: %s\n", i++, n->data);
        n = n->next;
    }
    return 0;
}
