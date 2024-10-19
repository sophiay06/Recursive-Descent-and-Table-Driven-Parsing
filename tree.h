#ifndef _tree_h
#define _tree_h
#include <stdbool.h>

typedef struct NODE *TREE;
struct NODE {
    char label;
    TREE leftmostChild, rightSibling;
};

// Helper functions
bool lookahead(char c);
bool match(char expected);
void printTree(TREE tree, int depth);

// Function prototypes for creating nodes
TREE makeNode0(char x);
TREE makeNode1(char x, TREE t);
TREE makeNode2(char x, TREE t1, TREE t2);
#endif