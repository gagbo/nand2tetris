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
    if (!out_stream && out_stream->is_open()) out_stream->close();
    delete out_stream;
}

void JackGrammarEngine::compileClass() {
    if (tokeniser->keyWord() != JackKeyword::CLASS_) {
        return;
    } else {
    }
    return;
}
