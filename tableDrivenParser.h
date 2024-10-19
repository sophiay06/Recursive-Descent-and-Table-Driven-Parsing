#ifndef _tableDrivenParser_h
#define _tableDrivenParser_h

#include "tree.h"
#define NUM_NONTERMINALS 9
#define NUM_TERMINALS 10

// ParseTreeNode structure to represent nodes in the parse tree
typedef struct ParseTreeNode {
    char symbol;                 // Symbol stored in the node
    struct ParseTreeNode *child; // Pointer to the first child
    struct ParseTreeNode *sibling; // Pointer to the next sibling
} ParseTreeNode;

// Table-driven parser function and helper functions
typedef struct {
    char lhs;        // Left-hand side of the production
    char rhs[10];    // Right-hand side of the production
} Production;

// Function prototypes for table-driven parsing
void initializeParsingTable(int parsingTable[NUM_NONTERMINALS][NUM_TERMINALS]);
ParseTreeNode* parse(char *input, char startSymbol, int parsingTable[NUM_NONTERMINALS][NUM_TERMINALS]);
ParseTreeNode* createNode(char symbol);
int getNonTerminalIndex(char nonTerminal);
int getTerminalIndex(char terminal);
bool isNonTerminal(char symbol);
bool isTerminal(char symbol);
void pushProductionToStack(const char *production, int *top, char *stack);
bool handleEpsilonForM( char **lookahead);
bool handleEpsilonForU( char **lookahead);
bool handleEpsilonForG( char **lookahead);
bool handleDigitD( char **lookahead);
void printParseTree(ParseTreeNode *root, int depth);
void addChild(ParseTreeNode *parent, ParseTreeNode *child);
#endif