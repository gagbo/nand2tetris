#ifndef _TOKENISER_TOKENISER_H
#define _TOKENISER_TOKENISER_H

#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>

/** enum for the Jack token types */
enum struct JackTokenType : int {
    KEYWORD,
    SYMBOL,
    IDENT,
    INT_CONST,
    STRING_CONST
};

/** enum for the different Jack Keywords */
enum struct JackKeyword : int {
    NOT_KEYWORD,
    CLASS_,
    CONSTRUCTOR_,
    FUNCTION_,
    METHOD_,
    FIELD_,
    STATIC_,
    VAR_,
    INT_,
    CHAR_,
    BOOLEAN_,
    VOID_,
    TRUE_,
    FALSE_,
    NULL_,
    THIS_,
    LET_,
    DO_,
    IF_,
    ELSE_,
    WHILE_,
    RETURN_
};

/** Tokeniser objects for Jack files */
class JackTokeniser {
 public:
    /** Default constructor */
    JackTokeniser();
    /** Constructor with only the file name */
    JackTokeniser(const char* filename);
    /** Constructor giving directly the input file stream to use */
    JackTokeniser(std::ifstream* input_stream);

    /** Destructor
     * Handles closing the in_stream
     */
    ~JackTokeniser();

    /** String containing every symbol for the tokeniser */
    static std::string st_symbol_list;

    /** String containing every possible char to start an identifier */
    static std::string st_ident_start_list;

    /** String containing every possible char inside an identifier */
    static std::string st_ident_char_list;

    /** String containing Space separated comment delimiters for the
     * tokeniser
     */
    static std::string st_comment_list;

    /** String containing all possible delimiters for tokens */
    static std::string st_delimiter_list;

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

    /** Return next token's first char without moving the token
     * It is useful for the LL(2) exception in the Jack Grammar
     */
    char peek() const;

    /** Tell if there are tokens left */
    bool hasMoreTokens() const;

    /** Tell the current token type */
    JackTokenType getTokenType() const;

    /** Access the current token */
    std::string getToken() const;

    /** Show the current line and position of tokeniser */
    void showState() const;

    /** Return the string to output in xml format */
    std::string xmlOutput() const;

    /** Return the value of the token if it is the right type */
    JackKeyword keyWord() const;

    /** Return the value of the token if it is the right type */
    char symbol() const;

    /** Return the value of the token if it is the right type */
    std::string identifier() const;

    /** Return the value of the token if it is the right type */
    int intVal() const;

    /** Return the value of the token if it is the right type */
    std::string stringVal() const;

 protected:
    /** input file stream associated to the tokeniser */
    std::ifstream* in_stream;
    /** current line */
    std::string current_line;
    /** cursor in current line
     * It is always placed at the char starting the next token
     * in a line. If current_line.at(line_cursor) is \r or \n, EOL
     * This behaviour (handled by advance() enables peek() */
    size_t line_cursor;
    /** current token */
    std::string token;
    /** current token type */
    JackTokenType token_type;
    /** keyword type specialisation */
    JackKeyword token_keyword;
    /** Are we at the end ? */
    bool is_end_of_input;
    /** Are we parsing the last line ? */
    bool is_last_line;

 private:
    void init();
    /** Checks if token is a keyword */
    bool isKeyword();
    /** Checks if token is keyword CLASS
     * Side effect : Sets JackKeyword if true
     */
    bool isCLASS();
    /** Checks if token is keyword CONSTRUCTOR
     * Side effect : Sets JackKeyword if true
     */
    bool isCONSTRUCTOR();
    /** Checks if token is keyword FUNCTION
     * Side effect : Sets JackKeyword if true
     */
    bool isFUNCTION();
    /** Checks if token is keyword METHOD
     * Side effect : Sets JackKeyword if true
     */
    bool isMETHOD();
    /** Checks if token is keyword FIELD
     * Side effect : Sets JackKeyword if true
     */
    bool isFIELD();
    /** Checks if token is keyword STATIC
     * Side effect : Sets JackKeyword if true
     */
    bool isSTATIC();
    /** Checks if token is keyword VAR
     * Side effect : Sets JackKeyword if true
     */
    bool isVAR();
    /** Checks if token is keyword INT
     * Side effect : Sets JackKeyword if true
     */
    bool isINT();
    /** Checks if token is keyword CHAR
     * Side effect : Sets JackKeyword if true
     */
    bool isCHAR();
    /** Checks if token is keyword BOOLEAN
     * Side effect : Sets JackKeyword if true
     */
    bool isBOOLEAN();
    /** Checks if token is keyword VOID
     * Side effect : Sets JackKeyword if true
     */
    bool isVOID();
    /** Checks if token is keyword TRUE
     * Side effect : Sets JackKeyword if true
     */
    bool isTRUE();
    /** Checks if token is keyword FALSE
     * Side effect : Sets JackKeyword if true
     */
    bool isFALSE();
    /** Checks if token is keyword NULL
     * Side effect : Sets JackKeyword if true
     */
    bool isNULL();
    /** Checks if token is keyword THIS
     * Side effect : Sets JackKeyword if true
     */
    bool isTHIS();
    /** Checks if token is keyword LET
     * Side effect : Sets JackKeyword if true
     */
    bool isLET();
    /** Checks if token is keyword DO
     * Side effect : Sets JackKeyword if true
     */
    bool isDO();
    /** Checks if token is keyword IF
     * Side effect : Sets JackKeyword if true
     */
    bool isIF();
    /** Checks if token is keyword ELSE
     * Side effect : Sets JackKeyword if true
     */
    bool isELSE();
    /** Checks if token is keyword WHILE
     * Side effect : Sets JackKeyword if true
     */
    bool isWHILE();
    /** Checks if token is keyword RETURN
     * Side effect : Sets JackKeyword if true
     */
    bool isRETURN();
};

#endif /* ifndef _TOKENISER_TOKENISER_H */
