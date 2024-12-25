#include <stddef.h>
#include <stdio.h>
#include <limits.h>
#include "fheap.h"
#define panic(msg) do { fprintf(stderr, "%s\n", msg); exit(1); } while (0)

size_t match_prefix(char *prefix, char *exam) {
    while (*prefix != '\0') {
        if (*prefix != *exam)
            return 0;
        prefix++;
        exam++;
    }
    return 1;
}

int main(void) {
    char command[128];
    long int a, b;
    struct Node root;
    fh_InitNode(&root, LONG_MAX);
    while (scanf("%s %ld %ld", command, &a, &b) > 0) {
        if (match_prefix("insert", command)) {
        } else if (match_prefix("delete", command)) {
        } else if (match_prefix("decrease", command)) {
        } else if (match_prefix("extract-min", command)) {
        } else if (match_prefix("exit", command)) {
        } else
            return 1;
    }
}
