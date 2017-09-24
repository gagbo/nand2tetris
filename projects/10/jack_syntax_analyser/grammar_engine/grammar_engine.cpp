#include "grammar_engine.h"

JackGrammarEngine::JackGrammarEngine() : tokeniser(NULL), out_stream(NULL) {
    std::cerr << "The Jack Grammar Engine is not supposed to be instantiated"
                 "without arguments !\n";
    exit(1);
}

JackGrammarEngine::JackGrammarEngine(std::string input_filename) {
    tokeniser = NULL;
    out_stream = NULL;
    std::string output_filename = input_filename;
    output_filename.replace(output_filename.end() - 4, output_filename.end(),
                            "xml");
    tokeniser = new JackTokeniser(input_filename.c_str());
    out_stream = new std::ofstream(output_filename.c_str());
    std::cerr << "Grammar Engine instantiated for " << input_filename << "\n";
}

JackGrammarEngine::~JackGrammarEngine() {
    delete tokeniser;
    if (!out_stream && out_stream->is_open()) {
        // TODO : syn the ofstream to file
        out_stream->close();
    }
    delete out_stream;
}

bool JackGrammarEngine::start() { return compileClass(); }

bool JackGrammarEngine::testAndEatIdent() {
    if (tokeniser->getTokenType() != JackTokenType::IDENT) {
        std::cerr << "Expected Identifier :\n";
        tokeniser->showState();
        return false;
    } else {
        *out_stream << tokeniser->xmlOutput();
        tokeniser->advance();
        return true;
    }
}

bool JackGrammarEngine::testAndEatSymbol(char expected_char) {
    if (tokeniser->symbol() != expected_char) {
        std::cerr << "Expected " << expected_char << "\n";
        tokeniser->showState();
        return false;
    } else {
        *out_stream << tokeniser->xmlOutput();
        tokeniser->advance();
        return true;
    }
}

bool JackGrammarEngine::testAndEatKeyword(
    std::vector<JackKeyword> expected_keywords) {
    auto result = std::find(expected_keywords.begin(), expected_keywords.end(),
                            tokeniser->keyWord());
    if (result == expected_keywords.end()) {
        std::cerr << "Expected another keyword\n";
        tokeniser->showState();
        return false;
    } else {
        *out_stream << tokeniser->xmlOutput();
        tokeniser->advance();
        return true;
    }
}

bool JackGrammarEngine::testAndEatType() {
    /* We test first for the 3 valid keywords int char and boolean
     * and if it's not good, look for an identifier
     */
    std::vector<JackKeyword> valid_types = {
        JackKeyword::INT_, JackKeyword::CHAR_, JackKeyword::BOOLEAN_};
    if (testAndEatKeyword(valid_types)) {
        return true;
    } else {
        return testAndEatIdent();
    }
}

bool JackGrammarEngine::compileClass() {
    if (tokeniser->keyWord() != JackKeyword::CLASS_) {
        std::cerr << "Expected class keyword\n";
        tokeniser->showState();
        return false;
    } else {
        *out_stream << "<class>\n";
        *out_stream << tokeniser->xmlOutput();
        tokeniser->advance();
        if (!testAndEatIdent()) {
            return false;
        }
        if (!testAndEatSymbol('{')) {
            return false;
        }
        while (compileClassVarDec()) {
            compileClassVarDec();
        }
        while (compileSubroutine()) {
            compileSubroutine();
        }
        if (!testAndEatSymbol('}')) {
            return false;
        }
        *out_stream << "</class>\n";
        return true;
    }
}

bool JackGrammarEngine::compileClassVarDec() {
    if (tokeniser->keyWord() != JackKeyword::STATIC_ &&
        tokeniser->keyWord() != JackKeyword::FIELD_) {
        return false;
    } else {
        *out_stream << "<classVarDec>\n";
        *out_stream << tokeniser->xmlOutput();
        tokeniser->advance();
        if (!testAndEatType()) {
            return false;
        }
        if (!testAndEatIdent()) {
            return false;
        }
        // Read the remaining varNames
        while (testAndEatSymbol(',')) {
            testAndEatIdent();
        }

        if (!testAndEatSymbol(';')) {
            return false;
        }
        *out_stream << "</classVarDec>\n";
        return true;
    }
}

bool JackGrammarEngine::compileSubroutine() {
    // constructor;function;method
    if (tokeniser->keyWord() != JackKeyword::CONSTRUCTOR_ &&
        tokeniser->keyWord() != JackKeyword::FUNCTION_ &&
        tokeniser->keyWord() != JackKeyword::METHOD_) {
        return false;
    } else {
        *out_stream << "<subroutineDec>\n";
        *out_stream << tokeniser->xmlOutput();
        tokeniser->advance();
        // void or type
        if (!testAndEatKeyword({JackKeyword::VOID_})) {
            if (!testAndEatType()) {
                return false;
            }
        }
        // subroutineName
        if (!testAndEatIdent()) {
            return false;
        }
        // Symbol and parameter list
        if (!testAndEatSymbol('(')) {
            return false;
        }
        compileParameterList();
        if (!testAndEatSymbol(')')) {
            return false;
        }

        *out_stream << "<subroutineBody>\n";

        if (!testAndEatSymbol('{')) {
            return false;
        }

        while (compileVarDec()) {
            compileVarDec();
        }

        compileStatements();

        if (!testAndEatSymbol('}')) {
            return false;
        }

        *out_stream << "</subroutineBody>\n";
        *out_stream << "</subroutineDec>\n";
        return true;
    }
}

bool JackGrammarEngine::compileParameterList() {
    *out_stream << "<parameterList>\n";
    if (testAndEatType()) {
        if (!testAndEatIdent()) {
            return false;
        }
    }

    // Read the remaining parameters
    // If there's a comma, we have to have a parameter
    while (testAndEatSymbol(',')) {
        if (!testAndEatType()) {
            return false;
        }
        if (!testAndEatIdent()) {
            return false;
        }
    }
    *out_stream << "</parameterList>\n";

    return true;
}

bool JackGrammarEngine::compileVarDec() {
    if (tokeniser->keyWord() != JackKeyword::VAR_) {
        return false;
    } else {
        *out_stream << "<varDec>\n";
        *out_stream << tokeniser->xmlOutput();
        tokeniser->advance();

        if (!testAndEatType()) {
            return false;
        }

        if (!testAndEatIdent()) {
            return false;
        }

        // Read the remaining varNames
        while (testAndEatSymbol(',')) {
            testAndEatIdent();
        }

        if (!testAndEatSymbol(';')) {
            return false;
        }

        *out_stream << "</varDec>\n";
        return true;
    }
}

bool JackGrammarEngine::compileStatements() {
    bool foundStatement = false;
    *out_stream << "<statements>\n";
    do {
        foundStatement = false;
        if (compileLet()) {
            foundStatement = true;
            continue;
        } else if (compileDo()) {
            foundStatement = true;
            continue;
        } else if (compileWhile()) {
            foundStatement = true;
            continue;
        } else if (compileReturn()) {
            foundStatement = true;
            continue;
        } else if (compileIf()) {
            foundStatement = true;
            continue;
        }
    } while (foundStatement);

    *out_stream << "</statements>\n";
    return true;
}

bool JackGrammarEngine::compileDo() {
    if (tokeniser->keyWord() != JackKeyword::DO_) {
        return false;
    } else {
        *out_stream << "<doStatement>\n";
        *out_stream << tokeniser->xmlOutput();
        tokeniser->advance();

        if (!testAndEatIdent()) {
            return false;
        }

        // Test if it's a class.subRoutine call
        if (testAndEatSymbol('.')) {
            if (!testAndEatIdent()) {
                return false;
            }
        }

        if (!testAndEatSymbol('(')) {
            return false;
        }

        if (!compileExpressionList()) {
            return false;
        }

        if (!testAndEatSymbol(')')) {
            return false;
        }

        if (!testAndEatSymbol(';')) {
            return false;
        }

        *out_stream << "</doStatement>\n";
        return true;
    }
}

bool JackGrammarEngine::compileWhile() {
    if (tokeniser->keyWord() != JackKeyword::WHILE_) {
        return false;
    } else {
        *out_stream << "<whileStatement>\n";
        *out_stream << tokeniser->xmlOutput();
        tokeniser->advance();

        if (!testAndEatSymbol('(')) {
            return false;
        }

        if (!compileExpression()) {
            return false;
        }

        if (!testAndEatSymbol(')')) {
            return false;
        }

        if (!testAndEatSymbol('{')) {
            return false;
        }

        compileStatements();

        if (!testAndEatSymbol('}')) {
            return false;
        }

        *out_stream << "</whileStatement>\n";
        return true;
    }
}

bool JackGrammarEngine::compileLet() {
    if (tokeniser->keyWord() != JackKeyword::LET_) {
        return false;
    } else {
        *out_stream << "<letStatement>\n";
        *out_stream << tokeniser->xmlOutput();
        tokeniser->advance();

        if (!testAndEatIdent()) {
            return false;
        }

        // Test if it's an Array call
        if (testAndEatSymbol('[')) {
            if (!testAndEatIdent()) {
                return false;
            }
            if (!compileExpression()) {
                return false;
            }
            if (!testAndEatSymbol(']')) {
                return false;
            }
        }

        if (!testAndEatSymbol('=')) {
            return false;
        }

        if (!compileExpression()) {
            return false;
        }

        if (!testAndEatSymbol(';')) {
            return false;
        }

        *out_stream << "</letStatement>\n";
        return true;
    }
}

bool JackGrammarEngine::compileIf() {
    if (tokeniser->keyWord() != JackKeyword::IF_) {
        return false;
    } else {
        *out_stream << "<ifStatement>\n";
        *out_stream << tokeniser->xmlOutput();
        tokeniser->advance();

        if (!testAndEatSymbol('(')) {
            return false;
        }

        if (!compileExpression()) {
            return false;
        }

        if (!testAndEatSymbol(')')) {
            return false;
        }

        if (!testAndEatSymbol('{')) {
            return false;
        }

        compileStatements();

        if (!testAndEatSymbol('}')) {
            return false;
        }

        // Test if there's an else bloc :
        if (testAndEatKeyword({JackKeyword::ELSE_})) {
            if (!testAndEatSymbol('{')) {
                return false;
            }

            compileStatements();

            if (!testAndEatSymbol('}')) {
                return false;
            }
        }

        *out_stream << "</ifStatement>\n";
        return true;
    }
}

bool JackGrammarEngine::compileReturn() {
    if (tokeniser->keyWord() != JackKeyword::RETURN_) {
        return false;
    } else {
        *out_stream << "<returnStatement>\n";
        *out_stream << tokeniser->xmlOutput();
        tokeniser->advance();

        compileExpression();

        if (!testAndEatSymbol(';')) {
            return false;
        }

        *out_stream << "</returnStatement>\n";
        return true;
    }
}

bool JackGrammarEngine::compileTerm() { return false; }
bool JackGrammarEngine::compileExpression() { return false; }
bool JackGrammarEngine::compileExpressionList() { return false; }
