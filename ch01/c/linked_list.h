#include <stdint.h>

typedef struct {
    void* head;
    // This list cannot get very long.
    uint8_t len;
} LinkedList;

int Push(LinkedList** l, char* s);
int Pop(LinkedList** l, char** s);
int FreeAll(LinkedList** l);
