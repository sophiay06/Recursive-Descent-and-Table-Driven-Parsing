#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tree.h"
#define FAILED NULL
extern char *nextTerminal;

// Helper functions
bool lookahead(char c) {
    return *nextTerminal == c;
}

bool match(char c) {
    if (lookahead(c)) {
        nextTerminal++;
        return true;
    }
    return false;
}

// Function to create a node with no children
TREE makeNode0(char x) {
    TREE node = (TREE)malloc(sizeof(struct NODE));
    node->label = x;
    node->leftmostChild = NULL;
    node->rightSibling = NULL;
    return node;
}

// Function to create a node with one child
TREE makeNode1(char x, TREE t) {
    TREE node = makeNode0(x);
    node->leftmostChild = t;
    return node;
}

// Function to create a node with two children
TREE makeNode2(char x, TREE t1, TREE t2) {
    TREE node = makeNode1(x, t1);
    t1->rightSibling = t2;
    return node;
}

// Function to print the parse tree
void printTree(TREE tree, int depth) {
    if (tree == NULL) return;
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
    if (tree->label == 'e') {
        printf("ε\n");  // Print ε for epsilon
    } else {
        printf("%c\n", tree->label);  // Print node label (digit or operator)
    }

    printTree(tree->leftmostChild, depth + 1); // Recursively print children
    printTree(tree->rightSibling, depth); // Recursively print siblings
}