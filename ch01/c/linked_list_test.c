#include <assert.h>

#include "linked_list.c"

int main() {
    struct linked_list* l = ll_new();
    char* c;
    assert(ll_push_left(l, "a") == 0);
    assert(ll_push_left(l, "b") == 0);
    assert(ll_push_left(l, "c") == 0);
    assert(ll_pop_left(l, &c) == 0);
    assert('c' == *c);
    free(c);
    assert(ll_pop_left(l, &c) == 0);
    assert('b' == *c);
    free(c);
    assert(ll_pop_left(l, &c) == 0);
    assert('a' == *c);
    free(c);
    ll_free_all(l);
    return 0;
}