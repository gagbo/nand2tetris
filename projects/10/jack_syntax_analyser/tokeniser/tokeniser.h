#ifndef _TOKENISER_TOKENISER_H
#define _TOKENISER_TOKENISER_H

#define TOKEN_BUFFER_SIZE 100
#include <fstream>
#include <iostream>

/** enum for the Jack token types */
enum struct JackTokenType : int {
    KEYWORD,
    SYMBOL,
    IDENT,
    INT_CONST,
    STRING_CONST
};

/** Tokeniser objects for Jack files */
class JackTokeniser {
 public:
    /** Default constructor */
    JackTokeniser();
    /** Constructor with only the file name */
    JackTokeniser(std::string filename);
    /** Constructor giving directly the input file stream to use */
    JackTokeniser(std::ifstream* input_stream);

    /** Destructor
     * Handles closing the in_stream
     */
    ~JackTokeniser();

    /** String containing every delimiter for the tokeniser */
    static std::string symbolList;

    /** String containing Space separated comment delimiters for the tokeniser
     */
    static std::string commentList;

    /** String containing all possible delimiters for tokens */
    static std::string delimiterList;

    /** Reads the next input line into current_line
     * Side effect : advances in_stream one line in the stream
     * Side effect : resets line_cursor to the first non whitespace
     * Side effect : updates the value ot is_last_line
     */
    void readNewLine();

    /** Advance to the next meaningful token
     * Side effect : updates the value of is_end_of_input
     */
    void advance();

    /** Return next token and come back to current position
     * It is useful for the LL(2) exception in the Jack Grammar
     */
    std::string peek();

    /** Tell if there are tokens left */
    bool hasMoreTokens();

    /** Tell the current token type */
    JackTokenType getTokenType();

    /** Return the value of the token if it is the right type */
    std::string keyWord();

    /** Return the value of the token if it is the right type */
    char symbol();

    /** Return the value of the token if it is the right type */
    std::string identifier();

    /** Return the value of the token if it is the right type */
    int intVal();

    /** Return the value of the token if it is the right type */
    std::string stringVal();

 protected:
    /** input file stream associated to the tokeniser */
    std::ifstream* in_stream;
    /** current line */
    std::string current_line;
    /** cursor in current line */
    size_t line_cursor;
    /** current token */
    std::string token;
    /** current token type */
    JackTokenType token_type;
    /** Are we at the end ? */
    bool is_end_of_input;
    /** Are we parsing the last line ? */
    bool is_last_line;
};

#endif /* ifndef _TOKENISER_TOKENISER_H */
