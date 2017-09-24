#ifndef _GRAMMARENGINE_GRAMMARENGINE_H_
#define _GRAMMARENGINE_GRAMMARENGINE_H_ value
#include <algorithm>
#include <vector>
#include "tokeniser/tokeniser.h"

class JackGrammarEngine {
 public:
    /** Empty Constructor */
    JackGrammarEngine();
    /** Constructor taking a jack filename
     * Call compileClass() afterwards
     */
    JackGrammarEngine(std::string input_filename);

    ~JackGrammarEngine();

    JackTokeniser* getTokeniser() { return tokeniser; }

 protected:
    JackTokeniser* tokeniser;
    std::ofstream* out_stream;

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
#endif /* ifndef _GRAMMARENGINE_GRAMMARENGINE_H_ */
