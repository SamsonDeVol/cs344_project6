// allocator.h

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef ALLOCATOR_H
#define ALLOCATOR_H
#define ALIGNMENT 16   // Must be power of 2
#define GET_PAD(x) ((ALIGNMENT - 1) - ((x) - 1) & (ALIGNMENT - 1))

#define PADDED_SIZE(x) ((x) + GET_PAD(x))


struct block {
    int in_use;
    int size;
    struct block *next;
};

int myalloc(int s);

#endif
