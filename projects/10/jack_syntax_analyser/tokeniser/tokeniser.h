#ifndef _TOKENISER_TOKENISER_H
#define _TOKENISER_TOKENISER_H

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
    static std::string delimiterList;

    /** String containing Space separated comment delimiters for the tokeniser
     */
    static std::string commentList;

    /** Advance to the next token */
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
    /** current token */
    std::string token;
    /** current token type */
    JackTokenType tokenType;
    /** Are we at the end ? */
    bool isEOInput;
};

#endif /* ifndef _TOKENISER_TOKENISER_H */
