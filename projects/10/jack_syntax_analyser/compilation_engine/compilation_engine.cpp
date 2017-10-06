#include "compilation_engine.h"

JackCompilationEngine::JackCompilationEngine()
    : tokeniser(NULL), out_stream(NULL), code_writer(NULL) {
    std::cerr
        << "The Jack Compilation Engine is not supposed to be instantiated"
           "without arguments !\n";
    exit(1);
}

JackCompilationEngine::JackCompilationEngine(std::string input_filename) {
    tokeniser = NULL;
    out_stream = NULL;
    code_writer = NULL;
    class_table.Clear();
    inner_table.SetParent(class_table);
    unique_label = 0;
    std::string output_filename = input_filename;
    output_filename.replace(output_filename.end() - 4, output_filename.end(),
                            "vm");
    tokeniser = new JackTokeniser(input_filename.c_str());
    out_stream = new std::ofstream(output_filename.c_str());
    code_writer = new VmWriter(out_stream);
    std::cerr << "Compilation Engine instantiated for " << input_filename
              << "\n";
}

JackCompilationEngine::~JackCompilationEngine() {
    class_table.Clear();
    inner_table.Clear();
    delete tokeniser;
    if (out_stream != NULL && out_stream->is_open()) {
        out_stream->flush();
        out_stream->close();
    }
    delete out_stream;
    delete code_writer;
}

bool JackCompilationEngine::start() { return compileClass(); }

bool JackCompilationEngine::testAndEatIdent() {
    if (tokeniser->getTokenType() != JackTokenType::IDENT) {
        return false;
    } else {
        *out_stream << tokeniser->xmlOutput();
        tokeniser->advance();
        return true;
    }
}

bool JackCompilationEngine::testAndEatIdent(SymbolEntry& hash_entry) {
    if (tokeniser->getTokenType() != JackTokenType::IDENT) {
        return false;
    } else {
        std::get<0>(hash_entry) = tokeniser->getToken();
        tokeniser->advance();
        return true;
    }
}

bool JackCompilationEngine::testAndEatIdent(std::string& hash_key) {
    if (tokeniser->getTokenType() != JackTokenType::IDENT) {
        return false;
    } else {
        hash_key = tokeniser->getToken();
        tokeniser->advance();
        return true;
    }
}

bool JackCompilationEngine::testAndEatSymbol(char expected_char) {
    if (tokeniser->symbol() != expected_char) {
        return false;
    } else {
        *out_stream << tokeniser->xmlOutput();
        tokeniser->advance();
        return true;
    }
}

bool JackCompilationEngine::testAndEatKeyword(
    std::vector<JackKeyword> expected_keywords) {
    auto result = std::find(expected_keywords.begin(), expected_keywords.end(),
                            tokeniser->keyWord());

    if (result == expected_keywords.end()) {
        return false;
    } else {
        *out_stream << tokeniser->xmlOutput();
        tokeniser->advance();
        return true;
    }
}

bool JackCompilationEngine::testAndEatType() {
    /* We test first for the 3 valid keywords int char and boolean
     * and if it's not good, look for an identifier (class name)
     */
    std::vector<JackKeyword> valid_types = {
        JackKeyword::INT_, JackKeyword::CHAR_, JackKeyword::BOOLEAN_};
    if (testAndEatKeyword(valid_types)) {
        return true;
    } else {
        return testAndEatIdent();
    }
}

bool JackCompilationEngine::testAndEatType(SymbolEntry& hash_entry) {
    /* We test first for the 3 valid keywords int char and boolean
     * and if it's not good, look for an identifier (class name)
     */
    std::vector<JackKeyword> valid_types = {
        JackKeyword::INT_, JackKeyword::CHAR_, JackKeyword::BOOLEAN_};
    if (tokeniser->keyWord() == JackKeyword::INT_ ||
        tokeniser->keyWord() == JackKeyword::CHAR_ ||
        tokeniser->keyWord() == JackKeyword::BOOLEAN_) {
        std::get<0>(hash_entry) == tokeniser->getToken();
        tokeniser->advance();
        return true;
    } else {
        return testAndEatIdent(hash_entry);
    }
}

bool JackCompilationEngine::compileClass() {
    // Simple test because we need to write xml tag before token
    if (tokeniser->keyWord() != JackKeyword::CLASS_) {
        return false;
    } else {
        class_table.Clear();
        tokeniser->advance();
        if (!testAndEatIdent(class_name)) {
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
        return true;
    }
}

bool JackCompilationEngine::compileClassVarDec() {
    // Simple test because we need to write xml tag before token
    if (tokeniser->keyWord() != JackKeyword::STATIC_ &&
        tokeniser->keyWord() != JackKeyword::FIELD_) {
        return false;
    } else {
        SymbolEntry new_var;
        std::string new_var_key;
        switch (tokeniser->keyWord()) {
            case JackKeyword::STATIC_:
                std::get<1>(new_var) = JackVariableKind::STATIC;
                break;
            case JackKeyword::FIELD_:
                std::get<1>(new_var) = JackVariableKind::FIELD;
                break;
            default:
                break;
        }
        tokeniser->advance();
        if (!testAndEatType(new_var)) {
            return false;
        }
        if (!testAndEatIdent(new_var_key)) {
            return false;
        } else {
            class_table.Insert(new_var_key, new_var);
        }
        // Read the remaining varNames
        while (testAndEatSymbol(',')) {
            testAndEatIdent(new_var_key);
            class_table.Insert(new_var_key, new_var);
        }

        if (!testAndEatSymbol(';')) {
            return false;
        }
        return true;
    }
}

bool JackCompilationEngine::compileSubroutine() {
    // constructor;function;method
    // Simple test because we need to write xml tag before token
    if (tokeniser->keyWord() != JackKeyword::CONSTRUCTOR_ &&
        tokeniser->keyWord() != JackKeyword::FUNCTION_ &&
        tokeniser->keyWord() != JackKeyword::METHOD_) {
        return false;
    } else {
        inner_table.Clear();
        JackKeyword subroutine_type = tokeniser->keyWord();
        std::string subroutine_name;
        /* bool subroutine_is_void; */
        tokeniser->advance();
        // void or type
        if (tokeniser->keyWord() != JackKeyword::VOID_) {
            /* subroutine_is_void = false; */
            if (!testAndEatType()) {
                return false;
            }
        } else {
            /* subroutine_is_void = true; */
            tokeniser->advance();
        }
        // subroutineName
        if (!testAndEatIdent(subroutine_name)) {
            return false;
        }
        // Symbol and parameter list
        if (!testAndEatSymbol('(')) {
            return false;
        }
        compileParameterList(subroutine_type);
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

bool JackCompilationEngine::compileParameterList(JackKeyword subroutine_type) {
    SymbolEntry new_var;
    std::get<1>(new_var) = JackVariableKind::ARGUMENT;
    std::string new_var_key;
    if (subroutine_type == JackKeyword::METHOD_) {
        inner_table.Insert("this", class_name, JackVariableKind::ARGUMENT);
    }
    if (testAndEatType(new_var)) {
        if (!testAndEatIdent(new_var_key)) {
            return false;
        }
        inner_table.Insert(new_var_key, new_var);
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
        inner_table.Insert(new_var_key, new_var);
    }

    return true;
}

bool JackCompilationEngine::compileVarDec() {
    // Simple test because we need to write xml tag before token
    if (tokeniser->keyWord() != JackKeyword::VAR_) {
        return false;
    } else {
        SymbolEntry new_var;
        std::get<1>(new_var) = JackVariableKind::LOCAL;
        std::string new_var_key;

        tokeniser->advance();

        if (!testAndEatType(new_var)) {
            return false;
        }

        if (!testAndEatIdent(new_var_key)) {
            return false;
        }
        inner_table.Insert(new_var_key, new_var);

        // Read the remaining varNames
        while (testAndEatSymbol(',')) {
            testAndEatIdent(new_var);
            inner_table.Insert(new_var_key, new_var);
        }

        if (!testAndEatSymbol(';')) {
            return false;
        }

        return true;
    }
}

bool JackCompilationEngine::compileStatements() {
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

bool JackCompilationEngine::compileDo() {
    // Simple test because we need to write xml tag before token
    if (tokeniser->keyWord() != JackKeyword::DO_) {
        return false;
    } else {
        tokeniser->advance();

        std::string function_name;
        int function_args = 0;
        if (!testAndEatIdent(function_name)) {
            return false;
        }

        // Test if it's a class.subRoutine call
        if (testAndEatSymbol('.')) {
            function_name += ".";
            std::string sub_name;
            if (!testAndEatIdent(sub_name)) {
                return false;
            }
            function_name += sub_name;
        }

        if (!testAndEatSymbol('(')) {
            return false;
        }

        if (!compileExpressionList(function_args)) {
            return false;
        }

        if (!testAndEatSymbol(')')) {
            return false;
        }

        if (!testAndEatSymbol(';')) {
            return false;
        }

        code_writer->Do(function_name, function_args);

        return true;
    }
}

bool JackCompilationEngine::compileWhile() {
    // Simple test because we need to write xml tag before token
    if (tokeniser->keyWord() != JackKeyword::WHILE_) {
        return false;
    } else {
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

bool JackCompilationEngine::compileLet() {
    // Simple test because we need to write xml tag before token
    if (tokeniser->keyWord() != JackKeyword::LET_) {
        return false;
    } else {
        tokeniser->advance();

        std::string target;
        if (!testAndEatIdent(target)) {
            return false;
        }

        // Test if it's an Array call
        if (testAndEatSymbol('[')) {
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

        code_writer->Let(inner_table, target);
        return true;
    }
}

bool JackCompilationEngine::compileIf() {
    // Simple test because we need to write xml tag before token
    if (tokeniser->keyWord() != JackKeyword::IF_) {
        return false;
    } else {
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

bool JackCompilationEngine::compileReturn() {
    // Simple test because we need to write xml tag before token
    if (tokeniser->keyWord() != JackKeyword::RETURN_) {
        return false;
    } else {
        tokeniser->advance();

        if (tokeniser->symbol() == ';') {
            code_writer->ReturnVoid();
            tokeniser->advance();
            return true;
        }

        compileExpression();

        if (!testAndEatSymbol(';')) {
            return false;
        }

        return true;
    }
}

bool JackCompilationEngine::compileTerm() {
    if (tokeniser->symbol() == '-' || tokeniser->symbol() == '~') {
        char unary_op = tokeniser->symbol();
        tokeniser->advance();
        if (!compileTerm()) {
            return false;
        }
        code_writer->UnaryOp(unary_op);
        return true;
    } else {
        if (tokeniser->getTokenType() == JackTokenType::INT_CONST) {
            code_writer->IntConst(tokeniser->intVal());
            tokeniser->advance();
            return true;
        } else if (tokeniser->getTokenType() == JackTokenType::STRING_CONST) {
            // Handle the creation on the fly of strings
            tokeniser->advance();
            return true;
        } else if (tokeniser->keyWord() == JackKeyword::TRUE_ ||
                   tokeniser->keyWord() == JackKeyword::FALSE_ ||
                   tokeniser->keyWord() == JackKeyword::NULL_ ||
                   tokeniser->keyWord() == JackKeyword::THIS_) {
            code_writer->KeywordConst(tokeniser->keyWord());
            tokeniser->advance();
            return true;
        } else if (tokeniser->getTokenType() == JackTokenType::IDENT) {
            /* This case should handle :
             *   - varName
             *   - varName[expr]
             *   - subroutineCall
             */
            tokeniser->advance();
            if (testAndEatSymbol('[')) {  // varName[expr]
                if (!compileExpression()) {
                    return false;
                }
                if (!testAndEatSymbol(']')) {
                    return false;
                }
            } else if (testAndEatSymbol('.')) {  // subroutineCall with .
                if (!testAndEatIdent()) {
                    return false;
                }

                if (!testAndEatSymbol('(')) {
                    return false;
                }

                int temp;
                if (!compileExpressionList(temp)) {
                    return false;
                }

                if (!testAndEatSymbol(')')) {
                    return false;
                }
            } else if (testAndEatSymbol('(')) {  // subroutineCall no .
                int temp;
                if (!compileExpressionList(temp)) {
                    return false;
                }

                if (!testAndEatSymbol(')')) {
                    return false;
                }
            }
            /* Else we already ate the varName and nothing
             * else to do
             */
            return true;
        } else if (tokeniser->symbol() == '(') {  // (expr)
            tokeniser->advance();
            if (!compileExpression()) {
                return false;
            }
            if (!testAndEatSymbol(')')) {
                std::cerr << "Term -> ( -> expr -> expecting )\n";
                tokeniser->showState();
                *out_stream << std::endl;
                exit(1);
            }
            return true;
        }
    }
    return false;
}

bool JackCompilationEngine::compileExpression() {
    if (!compileTerm()) {
        return false;
    }

    while (std::string("-*/&|<>=+").find(tokeniser->symbol()) !=
           std::string::npos) {
        char operation = tokeniser->symbol();
        tokeniser->advance();
        if (!compileTerm()) {
            std::cerr << "Term -> op -> expecting term\n";
            tokeniser->showState();
            *out_stream << std::endl;
            exit(1);
        }
        code_writer->Op(operation);
    }
    return true;
}

bool JackCompilationEngine::compileExpressionList(int& function_args) {
    *out_stream << "<expressionList>\n";
    if (tokeniser->symbol() == ')') {
        *out_stream << "</expressionList>\n";
        return true;
    }

    while (compileExpression()) {
        function_args++;
        if (!testAndEatSymbol(',')) {
            if (tokeniser->symbol() == ')') {
                *out_stream << "</expressionList>\n";
                return true;
            } else {
                return false;
            }
        }
    }
    return false;
}
