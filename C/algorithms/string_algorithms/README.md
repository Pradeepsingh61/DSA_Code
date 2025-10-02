# Boyer-Moore String Matching Algorithm

## Overview
The Boyer-Moore algorithm is one of the most efficient string matching algorithms, especially for large texts with small patterns. It can achieve sublinear time complexity in the best case by intelligently skipping characters during the search process.

## Algorithm Features
- **Time Complexity**: O(n/m) best case, O(n*m) worst case
- **Space Complexity**: O(σ + m) where σ is alphabet size
- **Two Heuristics**: Bad Character and Good Suffix
- **Practical Efficiency**: Used in text editors, grep, and search engines

## Implementation Details

### Bad Character Heuristic
- Preprocesses the pattern to find the rightmost occurrence of each character
- When a mismatch occurs, shifts the pattern based on the mismatched character
- Allows skipping multiple characters at once

### Good Suffix Heuristic
- Preprocesses the pattern to find the rightmost occurrence of each suffix
- When a mismatch occurs after matching a suffix, shifts based on suffix alignment
- More complex but provides better performance guarantees

## Code Structure
- `computeBadCharacterTable()`: Builds bad character preprocessing table
- `computeGoodSuffixTable()`: Builds good suffix preprocessing table
- `boyerMooreSearch()`: Main search function returning first occurrence
- `boyerMooreSearchAll()`: Enhanced function finding all occurrences
- `demonstrateBoyerMoore()`: Test cases demonstrating algorithm behavior

## Compilation and Execution
```bash
# Compile the program
gcc -o boyer_moore boyer_moore.c

# Run the program
./boyer_moore
```

## Program Modes
1. **Interactive Mode**: Enter your own text and pattern
2. **Demonstration Mode**: Run predefined test cases

## Test Cases Included
1. Simple pattern matching
2. Multiple occurrences
3. Pattern not found
4. Pattern at beginning of text
5. Pattern at end of text

## Educational Value
This implementation demonstrates:
- Advanced string processing techniques
- Preprocessing optimization strategies
- Memory management in C
- Algorithm analysis concepts
- Real-world application of computer science theory

## Applications
- Text editors (Find functionality)
- Search engines
- Bioinformatics (DNA sequence matching)
- Data mining
- Network intrusion detection

## Author
**Abhijit** - Hacktoberfest 2025 Contribution

## Contributing
Feel free to contribute improvements, optimizations, or additional test cases!