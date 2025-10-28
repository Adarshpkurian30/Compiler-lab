# Compiler Lab - KTU S7 BTech CSE

This repository contains implementations of various experiments for the Compiler Design Lab course as per the KTU (Kerala Technological University) S7 BTech Computer Science and Engineering curriculum.

## About
The codes are written with influences from lab instructors, online resources, and collaborative learning with peers. Each experiment demonstrates key concepts in compiler design and construction.

## Experiments

### 1. Lexical Analyzer
Implementation of a lexical analyzer (tokenizer) that identifies and categorizes tokens from source code.
- **File:** `exp1_lexical_analyzer.c`
- **Concepts:** Tokenization, pattern matching, symbol recognition

### 2. First and Follow Sets
Program to compute FIRST and FOLLOW sets for a given grammar.
- **File:** `exp2_first_follow.c`
- **Concepts:** Grammar analysis, predictive parsing preparation

### 3. Recursive Descent Parser
Implementation of a recursive descent parser for a simple grammar.
- **File:** `exp3_recursive_descent_parser.c`
- **Concepts:** Top-down parsing, LL parsing

### 4. Shift-Reduce Parser
Implementation of a shift-reduce parser using bottom-up parsing technique.
- **File:** `exp4_shift_reduce_parser.c`
- **Concepts:** Bottom-up parsing, LR parsing

### 5. Operator Precedence Parser
Parser based on operator precedence relations.
- **File:** `exp5_operator_precedence_parser.c`
- **Concepts:** Operator grammar, precedence relations

### 6. Code Optimization
Implementation of basic code optimization techniques.
- **File:** `exp6_code_optimization.c`
- **Concepts:** Constant folding, dead code elimination

### 7. Code Generation
Generation of intermediate code (Three Address Code).
- **File:** `exp7_code_generation.c`
- **Concepts:** Three address code, intermediate representation

### 8. Symbol Table Management
Implementation of symbol table with insert, search, and display operations.
- **File:** `exp8_symbol_table.c`
- **Concepts:** Hash table, symbol management

## How to Compile and Run

Each program can be compiled using GCC:

```bash
gcc exp1_lexical_analyzer.c -o exp1
./exp1
```

For all experiments:
```bash
# Compile
gcc exp<number>_<name>.c -o exp<number>

# Run
./exp<number>
```

## Requirements
- GCC compiler
- Basic understanding of compiler design concepts
- C programming knowledge

## Structure
```
Compiler-lab/
├── README.md
├── exp1_lexical_analyzer.c
├── exp2_first_follow.c
├── exp3_recursive_descent_parser.c
├── exp4_shift_reduce_parser.c
├── exp5_operator_precedence_parser.c
├── exp6_code_optimization.c
├── exp7_code_generation.c
└── exp8_symbol_table.c
```

## Contributing
Feel free to contribute by:
- Improving existing implementations
- Adding more test cases
- Fixing bugs
- Adding documentation

## Acknowledgments
- Lab instructors for guidance
- Online resources and compiler design textbooks
- Peers and friends for collaborative learning

## License
This repository is for educational purposes.