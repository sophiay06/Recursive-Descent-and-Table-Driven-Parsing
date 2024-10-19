#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "tableDrivenParser.h"

#define NUM_PRODUCTIONS 26
Production productions[NUM_PRODUCTIONS] = {
    {'E', "TU"},      // E -> T U
    {'U', "+E"},      // U -> + E
    {'U', "-E"},      // U -> - E
    {'U', "e"},       // U -> ε
    {'T', "FG"},      // T -> F G
    {'G', "*T"},      // G -> * T
    {'G', "/T"},      // G -> / T
    {'G', "e"},       // G -> ε
    {'F', "+F"},      // F -> + F
    {'F', "-F"},      // F -> - F
    {'F', "A"},       // F -> A
    {'A', "(E)"},     // A -> ( E )
    {'A', "N"},       // A -> N
    {'N', "DM"},      // N -> D M
    {'M', "N"},       // M -> N
    {'M', "e"},       // M -> ε
    {'D', "0"},       // D -> 0
    {'D', "1"},       // D -> 1
    {'D', "2"},       // D -> 2
    {'D', "3"},       // D -> 3
    {'D', "4"},       // D -> 4
    {'D', "5"},       // D -> 5
    {'D', "6"},       // D -> 6
    {'D', "7"},       // D -> 7
    {'D', "8"},       // D -> 8
    {'D', "9"},       // D -> 9
};

// Parsing table
void initializeParsingTable(int parsingTable[NUM_NONTERMINALS][NUM_TERMINALS]) {
    // Initialize all entries to -1 (no rule)
    for (int i = 0; i < NUM_NONTERMINALS; i++) {
        for (int j = 0; j < NUM_TERMINALS; j++) {
            parsingTable[i][j] = -1;
        }
    }

    // E → T U
    parsingTable[0][0] = 0; // E → T U (for '0'-'9')
    parsingTable[0][5] = 0; // E → T U (for '(')
    parsingTable[0][1] = 0; // E → T U (for '+')
    parsingTable[0][2] = 0; // E → T U (for '-')

    // U → + T U | - T U | ε
    parsingTable[1][1] = 1; // U → + T U (for '+')
    parsingTable[1][2] = 2; // U → - T U (for '-')
    parsingTable[1][6] = 3; // U → ε (for ')')
    parsingTable[1][7] = 3; // U → ε (for end of input)

    // T → F G
    parsingTable[2][0] = 4; // T → F G (for '0'-'9')
    parsingTable[2][5] = 4; // T → F G (for '(')
    parsingTable[2][1] = 4; // T → F G (for '+')
    parsingTable[2][2] = 4; // T → F G (for '-')

    // G → * T | / T | ε
    parsingTable[3][3] = 5; // G → * T (for '*')
    parsingTable[3][4] = 6; // G → / T (for '/')
    parsingTable[3][1] = 7; // G → ε (for '+')
    parsingTable[3][2] = 7; // G → ε (for '-')
    parsingTable[3][6] = 7; // G → ε (for ')')
    parsingTable[3][7] = 7; // G → ε (for end of input)

    // F → + F | - F | A
    parsingTable[4][1] = 8;  // F → + F (for '+')
    parsingTable[4][2] = 9;  // F → - F (for '-')
    parsingTable[4][0] = 10; // F → A (for '0'-'9')
    parsingTable[4][5] = 10; // F → A (for '(')

    // A → ( E ) | N
    parsingTable[5][5] = 11; // A → ( E ) (for '(')
    parsingTable[5][0] = 12; // A → N (for '0'-'9')

    // N → D M
    parsingTable[6][0] = 13; // N → D M (for '0'-'9')

    // M → N | ε
    parsingTable[7][0] = 14; // M → N (for '0'-'9')
    // Adding the following lines to handle epsilon for M
    parsingTable[7][2] = 15; // M → ε (for '-')
    parsingTable[7][1] = 15; // M → ε (for '+')
    parsingTable[7][3] = 15; // M → ε (for '*')
    parsingTable[7][4] = 15; // M → ε (for '/')
    parsingTable[7][5] = 15; // M → ε (for '(')
    parsingTable[7][6] = 15; // M → ε (for ')')
    parsingTable[7][7] = 15; // M → ε (for end of input)

    // D → 0 | 1 | 2 | ... | 9
    parsingTable[8][0] = 16; // D → '0'-'9'
    parsingTable[8][1] = 17; // D → '0'-'9'
    parsingTable[8][2] = 18; // D → '0'-'9'
    parsingTable[8][3] = 19; // D → '0'-'9'
    parsingTable[8][4] = 20; // D → '0'-'9'
    parsingTable[8][5] = 21; // D → '0'-'9'
    parsingTable[8][6] = 22; // D → '0'-'9'
    parsingTable[8][7] = 23; // D → '0'-'9'
    parsingTable[8][8] = 24; // D → '0'-'9'
    parsingTable[8][9] = 25; // D → '0'-'9'
}

int getNonTerminalIndex(char nonTerminal) {
    switch (nonTerminal) {
        case 'E': return 0;
        case 'U': return 1;
        case 'T': return 2;
        case 'G': return 3;
        case 'F': return 4;
        case 'A': return 5;
        case 'N': return 6;  // Add N
        case 'M': return 7;  // Add M
        case 'D': return 8;  // Add D
        default: return -1;
    }
}

int getTerminalIndex(char terminal) {
    if (terminal >= '0' && terminal <= '9') {
        //printf("Mapping digit %c to terminal index 0\n", terminal);
        return 0;  // Map all digits '0'-'9' to index 0
    }
    // Handle other terminals like '+', '-', etc.
    switch (terminal) {
        case '+': return 1;
        case '-': return 2;
        case '*': return 3;
        case '/': return 4;
        case '(': return 5;
        case ')': return 6;
        case '$': return 7;  // End of input marker
        default: return -1;  // Invalid terminal
    }
}

bool isNonTerminal(char symbol) {
    return symbol == 'E' || symbol == 'U' || symbol == 'T' || symbol == 'G' ||
           symbol == 'F' || symbol == 'A' || symbol == 'N' || symbol == 'M' || symbol == 'D';
}

bool isTerminal(char symbol) {
    return symbol == '+' || symbol == '-' || //(symbol >= '0' && symbol <= '9') ||
           symbol == '*' || symbol == '/' || symbol == '(' || symbol == ')' || symbol == '$';
}

void pushProductionToStack(const char *production, int *top, char *stack) {
    for (int i = strlen(production) - 1; i >= 0; i--) {
        if (production[i] != 'e') {
            stack[(*top)++] = production[i];
            //printf("Pushed %c to stack\n", production[i]);
        }
    }
}

bool handleEpsilonForM(char **lookahead) {
    if (**lookahead == '\0' || strchr("+-*/()", **lookahead)) {
        //printf("M can derive ε, so proceeding with parse.\n");
        return true;
    }
    return false;
}

bool handleEpsilonForU(char **lookahead) {
    if (**lookahead == '\0' || **lookahead == ')') {
        //printf("U can derive ε, so proceeding with parse.\n");
        return true;
    }
    return false;
}

bool handleEpsilonForG(char **lookahead) {
    if (**lookahead == '+' || **lookahead == '-' || **lookahead == ')' || **lookahead == '\0') {
        //printf("G can derive ε, so proceeding with parse.\n");
        return true;
    }
    return false;
}

bool handleDigitD(char **lookahead) {
    if (**lookahead >= '0' && **lookahead <= '9') {
        //printf("Matched digit %c\n", **lookahead);
        (*lookahead)++;  // Move the lookahead pointer to the next character
        return true;
    }
    //printf("Error: Unexpected symbol %c for D\n", **lookahead);
    return false;
}

// Function to create a new tree node
ParseTreeNode* createNode(char symbol) {
    ParseTreeNode *newNode = (ParseTreeNode *)malloc(sizeof(ParseTreeNode));
    newNode->symbol = symbol;
    newNode->child = NULL;
    newNode->sibling = NULL;
    return newNode;
}

// Function to add a child node to a parent node
void addChild(ParseTreeNode *parent, ParseTreeNode *child) {
    if (!parent->child) {
        parent->child = child;
    } else {
        ParseTreeNode *current = parent->child;
        while (current->sibling) {
            current = current->sibling;
        }
        current->sibling = child;
    }
}

// Function to print the parse tree recursively
void printParseTree(ParseTreeNode *root, int depth) {
    if (!root) return;

    // Print current node with indentation based on depth
    for (int i = 0; i < depth; i++) printf("  ");
    if (root->symbol == 'e') {
        printf("ε\n");  // Print ε for epsilon
    } else {
        printf("%c\n", root->symbol);  // Print node label (digit or operator)
    }

    printParseTree(root->child, depth + 1);
    printParseTree(root->sibling, depth);
}

// Modified parse function to handle epsilon nodes and build the parse tree
ParseTreeNode* parse(char *input, char startSymbol, int parsingTable[NUM_NONTERMINALS][NUM_TERMINALS]) {
    char stack[256];
    int top = 0;
    stack[top++] = '$';
    stack[top++] = startSymbol;

    ParseTreeNode *nodeStack[256]; // Stack to maintain tree nodes
    ParseTreeNode *root = createNode(startSymbol); // Create root node
    nodeStack[top - 1] = root;

    char *lookahead = input;

    while (top > 0) {
        char topSymbol = stack[--top];
        ParseTreeNode *currentNode = nodeStack[top];

        if (topSymbol == '$' && *lookahead == '\0') {
            return root;  // Return root of the parse tree
        }

        if (isTerminal(topSymbol)) {
            if (*lookahead == topSymbol) {
                lookahead++;
            } else {
                return NULL;
            }
        } else if (isNonTerminal(topSymbol)) {
            if (topSymbol == 'D') {
                // Directly match a digit for D
                if (*lookahead >= '0' && *lookahead <= '9') {
                    ParseTreeNode *digitNode = createNode(*lookahead);
                    addChild(currentNode, digitNode);  // Add digit as a child to D
                    lookahead++;  // Move to the next character in the input
                    continue;  // Continue to the next symbol
                } else {
                    printf("Error: Expected digit, found %c\n", *lookahead);
                    return NULL;
                }
            }

            // Check for epsilon handling
            if ((topSymbol == 'M' && handleEpsilonForM(&lookahead)) ||
                (topSymbol == 'U' && handleEpsilonForU(&lookahead)) ||
                (topSymbol == 'G' && handleEpsilonForG(&lookahead))) {
                ParseTreeNode *epsilonNode = createNode('e');
                addChild(currentNode, epsilonNode);
                continue;
            }

            // Get the production index from the parsing table
            int productionIndex = parsingTable[getNonTerminalIndex(topSymbol)][getTerminalIndex(*lookahead)];
            if (productionIndex == -1) {
                printf("Error: No rule for %c with lookahead %c\n", topSymbol, *lookahead);
                return NULL;
            }

            Production prod = productions[productionIndex];

            // Create nodes for the RHS symbols and link them to the current node
            ParseTreeNode *lastNode = NULL;
            for (int i = strlen(prod.rhs) - 1; i >= 0; i--) {
                if (prod.rhs[i] != 'e') {
                    stack[top] = prod.rhs[i];  // Push the production symbols to the stack
                    nodeStack[top] = createNode(prod.rhs[i]); // Create a new tree node
                    if (lastNode) {
                        nodeStack[top]->sibling = lastNode; // Link siblings
                    }
                    lastNode = nodeStack[top];
                    top++;
                } else {
                    // Handle epsilon production: Create a node for 'ε'
                    ParseTreeNode *epsilonNode = createNode('e');
                    if (lastNode) {
                        epsilonNode->sibling = lastNode; // Link epsilon to the previous sibling
                    }
                    lastNode = epsilonNode;
                }
            }
            addChild(currentNode, lastNode);  // Add the linked list of nodes as children
        }
    }

    return *lookahead == '\0' ? root : NULL;
}
