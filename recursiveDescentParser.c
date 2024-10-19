#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "recursiveDescentParser.h"

#define FAILED NULL
char *nextTerminal;

TREE E() {
    TREE t = T();
    if (t == FAILED) return FAILED;

    TREE u = U();
    if (u == FAILED) return FAILED;

    return makeNode2('E', t, u); // E → T U
}

TREE U() {
    if (lookahead('+')) {
        match('+');
        TREE e = E();
        if (e == FAILED) return FAILED;
        return makeNode2('U', makeNode0('+'), e); // U → + E
    } else if (lookahead('-')) {
        match('-');
        TREE e = E();
        if (e == FAILED) return FAILED;
        return makeNode2('U', makeNode0('-'), e); // U → - E
    } else {
        return makeNode1('U', makeNode0('e')); // U → ϵ (epsilon production)
    }
}

TREE T() {
    TREE f = F();
    if (f == FAILED) return FAILED;

    TREE g = G();
    if (g == FAILED) return FAILED;

    return makeNode2('T', f, g); // T → F G
}

TREE G() {
    if (lookahead('*')) {
        match('*');
        TREE t = T();
        if (t == FAILED) return FAILED;
        return makeNode2('G', makeNode0('*'), t); // G → * T
    } else if (lookahead('/')) {
        match('/');
        TREE t = T();
        if (t == FAILED) return FAILED;
        return makeNode2('G', makeNode0('/'), t); // G → / T
    } else {
        return makeNode1('G', makeNode0('e')); // G → ϵ
    }
}

TREE F() {
    if (lookahead('+')) {
        match('+');
        TREE f = F();
        if (f == FAILED) return FAILED;
        return makeNode2('F', makeNode0('+'), f); // F → + F
    } else if (lookahead('-')) {
        match('-');
        TREE f = F();  // Recursively parse the next F
        if (f == FAILED) return FAILED;
        return makeNode2('F', makeNode0('-'), f); // F → - F
    } else {
        TREE a = A();  // Correctly call A() here instead of directly N()
        if (a == FAILED) return FAILED;
        return makeNode1('F', a); // F → A
    }
}

TREE A() {
    if (lookahead('(')) {
        match('(');
        TREE e = E();
        if (e == FAILED) return FAILED;
        if (!match(')')) return FAILED;
        return makeNode2('A', makeNode0('('), makeNode1('E', e)); // A → ( E )
    } else {
        TREE n = N();
        if (n == FAILED) return FAILED;
        return makeNode1('A', n); // A → N
    }
}

TREE N() {
    TREE d = D();  // Parse the digit
    if (d == FAILED) return FAILED;

    TREE m = M();  // Parse any following digits
    if (m == FAILED) return FAILED;

    return makeNode2('N', d, m);  // N → D M
}


TREE M() {
    TREE n = N();
    if (n != FAILED) {
        return makeNode1('M', n); // M → N (another digit sequence)
    } else {
        return makeNode1('M', makeNode0('e')); // M → ε (epsilon)
    }
}

TREE D() {
    if (lookahead('0') || lookahead('1') || lookahead('2') || lookahead('3') ||
        lookahead('4') || lookahead('5') || lookahead('6') || lookahead('7') ||
        lookahead('8') || lookahead('9')) {
        char digit = *nextTerminal;
        match(digit);
        TREE digitNode = makeNode0(digit); // Create a node for the digit
        return makeNode1('D', digitNode);  // Wrap it inside a 'D' node
        } else {
            return FAILED;
        }
}

// Function to start the recursive descent parse
TREE parseInput(char *input) {
    nextTerminal = input;  // Initialize the lookahead pointer to the start of the input
    TREE parseTree = E();  // Start parsing from the top-level non-terminal (E)

    // Check if parsing succeeded and the entire input is consumed
    if (parseTree != FAILED && *nextTerminal == '\0') {
        printf("Parse successful!\n");
        return parseTree;
    } else {
        printf("Parse failed.\n");
        return FAILED;
    }
}