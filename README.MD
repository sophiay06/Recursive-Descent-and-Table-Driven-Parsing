# Recursive Descent and Table-Driven Parsing
This project implements parsers for arithmetic expressions using two different techniques: recursive-descent parsing 
and table-driven parsing. It demonstrates how to apply formal models of context-free grammars to create parsers that 
generate parse trees and validate the syntax of input strings.

## Features
1. Recursive-Descent Parser
- Implements a recursive-descent parser for arithmetic expressions using a predefined grammar.
- Handles expressions with parentheses for precedence control.
- Prompts the user for input strings, parses them, and prints the resulting parse tree or an error message if the input 
is invalid.
2. Table-Driven Parser
- Implements a table-driven parser using an explicit parsing table based on the same grammar.
- Demonstrates the separation of grammar definitions from parsing logic, making it adaptable to other grammars.
- Accepts user input, attempts parsing, and prints the parse tree or reports syntax errors.
3. Parse Tree Printing
- Produces a hierarchical, indented parse tree showing the structure of parsed expressions.
- Supports recursion for printing subtrees with appropriate indentation to reflect the grammar hierarchy.

## Build and Run Instructions
- **Build**: Use gcc with C99 standards and necessary flags:
```
gcc -std=c99 -Wall -Werror -o EXECUTABLE *.c
```
- **Run**: Execute the program using the compiled executable:
```
./EXECUTABLE
```
## How it Works
This project offers a hands-on understanding of formal grammar parsing, showcasing both recursive and table-driven 
approaches. It emphasizes the differences between parsing techniques and highlights how context-free grammars can be 
applied to real-world parsing scenarios.