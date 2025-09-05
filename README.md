# Expression-Evaluation-System
A C program that implements infix to postfix conversion and expression evaluation using stack data structures. The system handles complex mathematical expressions with support for various operators, parentheses, and number formats.
Features
Infix to Postfix Conversion: Converts standard mathematical expressions to postfix notation

Expression Evaluation: Computes the result of postfix expressions using stack operations

Multi-digit Support: Handles numbers with multiple digits seamlessly

Decimal Numbers: Supports floating-point arithmetic with decimal values

Negative Numbers: Properly processes negative values in expressions

Parentheses Handling: Correctly manages nested parentheses and operator precedence

Power Operations: Implements exponentiation with proper precedence

Interactive Interface: User-friendly menu system with color-coded output

Error Handling: Comprehensive validation for invalid expressions and characters

Technical Implementation
Stack data structure using linked lists

Operator precedence hierarchy (^ > */% > +-)

Efficient memory management with proper allocation and deallocation

Robust input parsing for both spaced and non-spaced expressions

Support for all basic arithmetic operations: +, -, *, /, %, ^

Example Expressions
Basic: 2+3*4 → 2 3 4 * + = 14.0

With parentheses: (5+3)*2 → 5 3 + 2 * = 16.0

Decimals: 10.5/2.0 → 10.5 2.0 / = 5.25

Negative numbers: -5+3 → -5 3 + = -2.0

Power operations: 2^3+1 → 2 3 ^ 1 + = 9.0
