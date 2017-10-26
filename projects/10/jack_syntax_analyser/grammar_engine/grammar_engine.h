/* Copyright 2017 Gerry Agbobada
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of version 3 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef _GRAMMARENGINE_GRAMMARENGINE_H_
#define _GRAMMARENGINE_GRAMMARENGINE_H_
#include <algorithm>
#include <string>
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

    /** Starts the file parsing for the given instance */
    bool start();

    /** Destructor */
    ~JackGrammarEngine();

    /** Access the tokeniser member
     * This should only be used to debug the Grammar Engine
     */
    JackTokeniser* getTokeniser() { return tokeniser; }

 protected:
    /** tokeniser instance to parse the input file */
    JackTokeniser* tokeniser;
    /** Output File Stream for writing */
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
