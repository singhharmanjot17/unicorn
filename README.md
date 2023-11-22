# C90 (ANSI) to MIPS 1 Compiler

### Introduction

- This is a university project for the 5th semester Compiler Design class for Manipal Institute Of technology , Bengaluru.
- This is a (non fully featured) compiler written in C++ for ANSI C89/C90 to MIPS 1 (ABI Compliant)
- It uses Flex for lexical analysis, and Bison (3.3.2) for parsing to an AST.
- The target environment is Ubuntu 16, however a lot of the features may work on Unix based systems such as MacOS (exempt features are mentioned below).
- The compiler conforms to this specification: http://port70.net/~nsz/c/c89/c89-draft.html
- The project conforms to this specification: https://github.com/LangProc/langproc-2018-cw
- It assumes the input C is perfectly valid, well-formed, pre-processed C90. It performs some minimal optimization and error checking but do not rely on it for anything useful.
- Also includes a basic C to Python translator

### Usage

Make the project:  
`make clean`  
`make bin/c_compiler`

To compile a C file into MIPS, simply run  
`bin/c_compiler -S <source-file.c> -o <dest-file.s>`

To translate from C to Python (limitations described below), simply run  
`bin/c_compiler --translate <source-file.c> -o <dest-file.py>`

### Features

You will see these things printed to the console when running the compiler:

- The input C code printed in canonical form. This is to ensure the parser correctly read and converted the C code into an AST. It can be found in `bin/printC.c`
- The 3 address code intermediate language. It can be found in `bin/intermediateLanguage.txt`
- The MIPS code generated
- The translated Python (if running with the `--translate` flag)

##### Compiler:

The compiler does not support the full range of C90 features due to time constraints we had with the project, however we encourage anyone to improve/finish the compiler (hence the MIT License).

Some things the compiler fully supports:

- Functions with unlimited arguments
- Variables of `int` type
- Arithmetic and logical expressions
- If else and switch statements
- Operators
- For, while, and do while loops
- Arrays
- Char literals
- Sizeof (kind of)
- Pointers, addressing and dereferencing

Some things the compiler does not support:

- Structs and Unions
- Enums (started, never finished)
- Strings
- Multithreading
- Goto
- Macros and other preprocessing directives
- Comma operator (for sequencing within expressions)
- The old K&R style of declaring functions
- Variable-length arrays
- Const
- Pointer arithmetic
- Non int primitives
- Typedef

##### C to Python translator:

Some things the translator supports:

- Local and global integer variables (non nested scopes)
- Functions (definition and invocation) with integer arguments and void/integer return type
- Explicit support for main special functionality
- If, else, while, return, and sequences
- Decimal integer constants
- Integer arithmetic
- &&, ||, <, and ==
- Assignment as a direct expression statement

Some things the translator does not support:

- Variable shadowing
- Most other things not listed in support section above

### Testbench

The testbench runs unit tests to test the C to Python translator and the compiler itself. The compiler-specific unit tests only (have been confirmed to) run on Linux, with `mips-linux-gnu-gcc` and `qemu-mips` installed.

The compiler tests can be run using:

`test/compiler/src/runTests.sh`

and the C to Python translator tests can be run using:

`test/pythonTranslator/src/runTests.sh`

You will see a `pythonTranslator` folder in `test/compiler/tests`. These were generated by a tool, `devtools/translatorToCompilerTests.sh`, that converts C to Python translator tests into compiler tests.

You can see the results in the `log` folder in `test/compiler` and `test/pythonTranslator/log` folders.

The compiler currently passes 172/177 tests

The creators of this project are:

https://github.com/singhharmanjot17
