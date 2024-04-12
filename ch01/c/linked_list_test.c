#include <assert.h>
#include <stdio.h>

#include "linked_list.c"

int main() {
    char* s;
    struct linked_list* l = ll_new();
    ll_push_left(l, "a");
    ll_push_left(l, "b");
    ll_push_right(l, "c");
    ll_push_right(l, "d");
    ll_push_right(l, "e");
    ll_push_right(l, "f");
    ll_push_right(l, "g");
    ll_pop_at(l, &s, 5);
    free(s);
    ll_pop_at(l, &s, 2);
    free(s);
    ll_pop_right(l, &s);
    free(s);
    while (l->len > 0) {
        ll_pop_left(l, &s);
        free(s);
    }
    ll_free_all(l);
}