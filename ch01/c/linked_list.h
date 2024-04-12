#include <stdint.h>

struct _node {
    struct _node* prev;
    struct _node* next;
    char* data;
};

struct linked_list {
    struct _node* head;
    struct _node* tail;
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
 * Push a string onto the back of the linked list. The string is copied into
 * newly allocated space, so the caller can destroy their copy if they want.
 */
int ll_push_right(struct linked_list* l, char* s);

/*
 * Push a string at a position of the linked list. The string is copied into
 * newly allocated space, so the caller can destroy their copy if they want.
 */
int ll_push_at(struct linked_list* l, char* s, uint8_t i);

/*
 * Pop a string from the front of the linked list. Callers must `free()` the
 * resulting char*.
 */
int ll_pop_left(struct linked_list* l, char** s);

/*
 * Pop a string from the back of the linked list. Callers must `free()` the
 * resulting char*.
 */
int ll_pop_right(struct linked_list* l, char** s);

/*
 * Pop a string at a position of the linked list. Callers must `free()` the
 * resulting char*.
 */
int ll_pop_at(struct linked_list* l, char** s, uint8_t i);

/*
 * Free all storage that the linked list owns. Keep in mind that the
 * linked_list relinquishes ownership of strings that are popped out.
 */
int ll_free(struct linked_list* l);
