#ifndef _GRAMMARENGINE_GRAMMARENGINE_H_
#define _GRAMMARENGINE_GRAMMARENGINE_H_ value
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
    /** compileClass Method */
    void compileClass();
    /** compileClassVarDec Method */
    void compileClassVarDec();
    /** compileSubroutine Method */
    void compileSubroutine();
    /** compileParameterList Method */
    void compileParameterList();
    /** compileVarDec Method */
    void compileVarDec();
    /** compileStatements Method */
    void compileStatements();
    /** compileDo Method */
    void compileDo();
    /** compileLet Method */
    void compileLet();
    /** compileWhile Method */
    void compileWhile();
    /** compileReturn Method */
    void compileReturn();
    /** compileIf Method */
    void compileIf();
    /** compileExpression Method */
    void compileExpression();
    /** compileTerm Method */
    void compileTerm();
    /** compileExpressionList Method */
    void compileExpressionList();
};
#endif /* ifndef _GRAMMARENGINE_GRAMMARENGINE_H_ */
