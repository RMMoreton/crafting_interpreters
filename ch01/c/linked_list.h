#include <stdint.h>

struct _node {
    struct _node* prev;
    struct _node* next;
    char* data;
};

struct linked_list {
    struct _node* head;
    struct _node* tail;
    size_t len;
};

/*
 * Error codes that the various ll_* functions return.
 */
typedef enum _ll_errors {
    LLE_OK,
    LLE_INDEX,
    LLE_NULL_ARGUMENT,
    LLE_SIZE,
    LLE_SYSTEM,
} LLE;

/*
 * Allocate a new `struct linked_list`, initialize it, and return a pointer to
 * it. This may return NULL if allocation of the list fails.
 */
struct linked_list* ll_new();

/*
 * Push a string onto the front of the linked list. The string is copied into
 * newly allocated space, so the caller can destroy their copy if they want.
 */
LLE ll_push_left(struct linked_list* l, char* s);

/*
 * Push a string onto the back of the linked list. The string is copied into
 * newly allocated space, so the caller can destroy their copy if they want.
 */
LLE ll_push_right(struct linked_list* l, char* s);

/*
 * Push a string at a position of the linked list. The string is copied into
 * newly allocated space, so the caller can destroy their copy if they want.
 */
LLE ll_push_at(struct linked_list* l, char* s, size_t i);

/*
 * Pop a string from the front of the linked list. Callers must `free()` the
 * resulting char*.
 */
LLE ll_pop_left(struct linked_list* l, char** s);

/*
 * Pop a string from the back of the linked list. Callers must `free()` the
 * resulting char*.
 */
LLE ll_pop_right(struct linked_list* l, char** s);

/*
 * Pop a string at a position of the linked list. Callers must `free()` the
 * resulting char*.
 */
LLE ll_pop_at(struct linked_list* l, char** s, size_t i);

/*
 * Free all storage that the linked list owns. Keep in mind that the
 * linked_list relinquishes ownership of strings that are popped out.
 */
LLE ll_free(struct linked_list* l);
