#include <assert.h>

#include "linked_list.c"

void main() {
    LinkedList* l = NULL;
    char* c;
    assert(Push(&l, "a") == 0);
    assert(Push(&l, "b") == 0);
    assert(Push(&l, "c") == 0);
    assert(Pop(&l, &c) == 0);
    assert('c' == *c);
    assert(Pop(&l, &c) == 0);
    assert('b' == *c);
    assert(Pop(&l, &c) == 0);
    assert('a' == *c);
    FreeAll(&l);
}