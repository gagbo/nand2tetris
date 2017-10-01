#ifndef _COMPILATIONENGINE_COMPILATIONENGINE_H_
#define _COMPILATIONENGINE_COMPILATIONENGINE_H_
#include <algorithm>
#include <string>
#include <vector>
#include "symbol_table/symbol_table.h"
#include "tokeniser/tokeniser.h"

class JackCompilationEngine {
 public:
    /** Empty Constructor */
    JackCompilationEngine();
    /** Constructor taking a jack filename
     * Call compileClass() afterwards
     */
    JackCompilationEngine(std::string input_filename);

    /** Starts the file parsing for the given instance */
    bool start();

    /** Destructor */
    ~JackCompilationEngine();

    /** Access the tokeniser member
     * This should only be used to debug the Grammar Engine
     */
    JackTokeniser* getTokeniser() { return tokeniser; }

 protected:
    /** tokeniser instance to parse the input file */
    JackTokeniser* tokeniser;
    /** Output File Stream for writing */
    std::ofstream* out_stream;
    /** Class level symbol table */
    JackSymbolTable class_table;
    /** Subroutine level symbol table */
    JackSymbolTable inner_table;
    /** Label counter for uniqueness */
    int unique_label;

 private:
    /** Use the tokeniser to test for Ident and output it on out_stream */
    bool testAndEatIdent();
    /** Use the tokeniser to test for Symbol and output it on out_stream */
    bool testAndEatSymbol(char expected_char);
    /** Use the tokeniser to test for particular keyword and output it on
     * out_stream */
    bool testAndEatKeyword(std::vector<JackKeyword> expected_keywords);
    /** Use the tokeniser to test for Ident and output it on out_stream */
    bool testAndEatType();
    /** compileClass Method */
    bool compileClass();
    /** compileClassVarDec Method */
    bool compileClassVarDec();
    /** compileSubroutine Method */
    bool compileSubroutine();
    /** compileParameterList Method */
    bool compileParameterList();
    /** compileVarDec Method */
    bool compileVarDec();
    /** compileStatements Method */
    bool compileStatements();
    /** compileDo Method */
    bool compileDo();
    /** compileLet Method */
    bool compileLet();
    /** compileWhile Method */
    bool compileWhile();
    /** compileReturn Method */
    bool compileReturn();
    /** compileIf Method */
    bool compileIf();
    /** compileExpression Method */
    bool compileExpression();
    /** compileTerm Method */
    bool compileTerm();
    /** compileExpressionList Method */
    bool compileExpressionList();
};
#endif /* ifndef _COMPILATIONENGINE_COMPILATIONENGINE_H_ */
