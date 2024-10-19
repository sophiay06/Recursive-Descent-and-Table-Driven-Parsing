#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "recursiveDescentParser.h"
#include "tableDrivenParser.h"
#define FAILED NULL
extern char *nextTerminal;

// Main function to use both parsers
int main() {
    char input[256];  // Buffer for user input

    // Local parsing table declaration
    int parsingTable[NUM_NONTERMINALS][NUM_TERMINALS];
    initializeParsingTable(parsingTable);  // Initialize the parsing table once

    printf("Enter input to test (type 'quit' to quit):\n");

    while (1) {
        printf("> ");
        fgets(input, 256, stdin);  // Read input

        // Remove the newline character from input (if present)
        input[strcspn(input, "\n")] = '\0';

        // Check if the input is "quit"
        if (strcmp(input, "quit") == 0) {
            break;  // Exit on "quit"
        }

        // Print "Testing <input>"
        printf("Testing \"%s\"\n", input);  // Use cleaned input for printing

        // === First Parser: Recursive Descent Parser ===
        printf("\n--- Recursive Descent Parser ---\n");
        TREE parseTree = parseInput(input);  // Start parsing using recursive descent parser
        if (parseTree != FAILED) {
            printTree(parseTree, 0);
            printf("Parse successful!\n");
        } else {
            printf("Parse failed.\n");
        }

        // === Second Parser: Table-Driven Parser ===
        // Reinitialize the input for the table-driven parser by adding '$'
        strcat(input, "$");  // Append end marker '$'

        printf("\n--- Table-Driven Parser ---\n");
        ParseTreeNode *parseTreeRoot = parse(input, 'E', parsingTable);  // Use the updated parse function
        if (parseTreeRoot) {
            printf("Parse successful!\n");
            printParseTree(parseTreeRoot, 0);  // Print the parse tree using the table-driven approach
        } else {
            printf("Parse failed.\n");
        }
    }

    printf("Bye!\n");
    return 0;
}