#include <stdint.h>

struct _node {
    struct _node* prev;
    struct _node* next;
    char* data;
};

struct linked_list {
    struct _node* head;
    uint8_t len;
};

/*
 * Allocate a new `struct linked_list`, initialize it, and return a pointer to
 * it.
 */
struct linked_list* ll_new();

/*
 * Push a string onto the front of the linked list. The string is copied into
 * newly allocated space, so the caller can destroy their copy if they want.
 */
int ll_push_left(struct linked_list* l, char* s);

/*
 * Pop a string from the front of the linked list. Callers must `free()` the
 * returned char*.
 */
int ll_pop_left(struct linked_list* l, char** s);

/*
 * Free all storage that the linked list owns. Keep in mind that the
 * linked_list relinquishes ownership of strings that are popped out.
 */
int ll_free(struct linked_list* l);
