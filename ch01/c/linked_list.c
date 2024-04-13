#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"

/*
 * Get the node at the given index. May return the dummy node.
 */
struct _node* ll_node_at(struct linked_list* l, size_t i) {
    struct _node* n;
    if (l == NULL || i > l->len) {
        return NULL;
    }
    // Iterate to the correct node starting at either the head or the tail,
    // whichever is closer.
    if (i <= (l->len+1) / 2) {
        n = l->head->next;
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
    struct _node* n;
    struct linked_list* l;

    n = (struct _node*)malloc(2 * sizeof(struct _node));
    if (n == NULL) {
        return NULL;
    }
    n[0].prev = NULL;
    n[0].next = n + 1;
    n[0].data = NULL;
    n[1].prev = n;
    n[1].next = NULL;
    n[1].data = NULL;

    l = (struct linked_list*)malloc(sizeof(struct linked_list));
    if (l == NULL) {
        free(n);
        return NULL;
    }
    l->len = 0;
    l->head = n;
    l->tail = n + 1;
    return l;
}

LLE ll_push_left(struct linked_list* l, char* s) {
    return ll_push_at(l, s, 0);
}

LLE ll_push_right(struct linked_list* l, char* s) {
    return ll_push_at(l, s, l->len);
}

LLE ll_push_at(struct linked_list* l, char* s, size_t i) {
    struct _node* n, *n_at;
    if (l == NULL || s == NULL) {
        return LLE_NULL_ARGUMENT;
    }
    if (l->len == SIZE_MAX) {
        return LLE_SIZE;
    }
    if (i < 0 || i > l->len) {
        return LLE_INDEX;
    }
    n = (struct _node*)malloc(sizeof(struct _node));
    if (n == NULL) {
        return LLE_SYSTEM;
    }
    n->data = strdup(s);
    if (n->data == NULL) {
        // We don't allow pushing NULL data, so this must be a malloc failure.
        free(n);
        return LLE_SYSTEM;
    }
    n_at = ll_node_at(l, i);
    n->prev = n_at->prev;
    n->next = n_at;
    // n_at->prev is non-null because of the dummy nodes and how we implement
    // the lookup.
    n_at->prev->next = n;
    n_at->prev = n;
    l->len++;
    return LLE_OK;
}

LLE ll_pop_left(struct linked_list* l, char** s) {
    return ll_pop_at(l, s, 0);
}

LLE ll_pop_right(struct linked_list* l, char** s) {
    return ll_pop_at(l, s, l->len - 1);
}

LLE ll_pop_at(struct linked_list* l, char** s, size_t i) {
    struct _node* n;
    if (l == NULL) {
        return LLE_NULL_ARGUMENT;
    }
    if (i < 0 || i >= l->len) {
        return LLE_INDEX;
    }
    n = ll_node_at(l, i);
    n->prev->next = n->next;
    n->next->prev = n->prev;
    l->len--;
    if (s != NULL) {
        *s = n->data;
    } else {
        // It shouldn't be possible to put NULL into a node's data, but...
        if (n->data != NULL) {
            free(n->data);
        }
    }
    free(n);
    return LLE_OK;
}

LLE ll_free_all(struct linked_list *l) {
    struct _node* n;
    if (l == NULL) {
        return LLE_NULL_ARGUMENT;
    }
    n = l->head->next;
    while (n != l->tail) {
        if (n->data != NULL) {
            free(n->data);
        }
        n = n->next;
        free(n->prev);
    }
    // Also frees l->tail since we allocated them together
    free(l->head);
    free(l);
    return LLE_OK;
}
