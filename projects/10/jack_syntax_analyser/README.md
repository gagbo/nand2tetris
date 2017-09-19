# Jack Syntax Analyser ToDo list

## Makefile
- Use CMake to start with very small projects

## Tokeniser
- Parse the tokens
    - Create a token virtual class
    - How to check if a given token is in the right case ?
    - How to raise exceptions ?
- Check the grammar
    - How many rules to implement ?
        - Given by specification
    - Use terminal and non-terminal rules hierarchy
    - API using a `isValid` method to check recursively through grammar rules ?
- Write to xml for the tests
