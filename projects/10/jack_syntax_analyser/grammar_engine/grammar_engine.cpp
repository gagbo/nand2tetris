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
    tokeniser->advance();
}

JackGrammarEngine::~JackGrammarEngine() {
    delete tokeniser;
    if (!out_stream && out_stream->is_open()) {
        // TODO : syn the ofstream to file
        out_stream->close();
    }
    delete out_stream;
}

bool JackGrammarEngine::compileClass() {
    if (tokeniser->keyWord() != JackKeyword::CLASS_) {
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
        // TODO: Missing classVarDec* avec while
        // TODO: Missing subroutineDec* with while
        if (!testAndEatSymbol('}')) {
            return false;
        }
        *out_stream << "</class>\n";
        return true;
    }
}

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
