#include <assert.h>
#include <stdio.h>

#include "linked_list.c"

int main() {
    struct _node *n;
    struct linked_list *l = ll_new();
    ll_print(l);
    ll_push_left(l, "a");
    ll_print(l);
    ll_push_left(l, "b");
    ll_print(l);
    ll_push_right(l, "c");
    ll_print(l);
    ll_push_right(l, "d");
    ll_print(l);
    ll_push_right(l, "e");
    ll_print(l);
    ll_push_right(l, "f");
    ll_print(l);
    ll_push_right(l, "g");
    ll_print(l);
    for (uint8_t i = 0; i < l->len; i++) {
        n = ll_node_at(l, i);
        printf("%s\n", n->data);
    }
    ll_free_all(l);
}