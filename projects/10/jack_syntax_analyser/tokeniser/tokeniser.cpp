#include "tokeniser.h"

std::string JackTokeniser::symbolList = "(){};.=+-*/\"";
std::string JackTokeniser::commentList = "// /*";
std::string JackTokeniser::delimiterList = "(){};.=+-*/\" \r\t\n";

JackTokeniser::JackTokeniser() {
    in_stream = 0;
    current_line = "";
    line_cursor = 0;
    token = "";
    is_last_line = false;
    is_end_of_input = false;
}

JackTokeniser::JackTokeniser(std::string filename) {
    JackTokeniser();
    in_stream->open(filename.c_str());
}

JackTokeniser::JackTokeniser(std::ifstream* input_stream) {
    JackTokeniser();
    in_stream = input_stream;
}

JackTokeniser::~JackTokeniser() { in_stream->close(); }

void JackTokeniser::readNewLine() {
    std::getline(*in_stream, current_line);
    if (!in_stream->good()) {
        is_last_line = true;
        return;
    }

    line_cursor = current_line.find_first_not_of(" \n\r\t");
    return;
}
void JackTokeniser::advance() {
    // TODO: Handle multi-line comments. There needs to be another attribute
    // for this
    // Check for comment or end of line
    line_cursor = current_line.find_first_not_of(" \n\r\t");
    if (line_cursor == std::string::npos ||
        current_line.substr(line_cursor, 2) == "//" ||
        current_line.substr(line_cursor, 2) == "/*") {
        readNewLine();
        advance();
    } else {  // Otherwise parse the token
        // Cas ou on a un chiffre (forcement INT_CONST)
        // Cas ou on a un symbole (find_first_of(symbolList) - line_cursor = 1)
        /* Cas ou on a une lettre ou un _ (refaire un token avec tous les
         * delimiteurs - DONE delimiterList)
         */
    }

    // At this point, the line_cursor should be set on the char after the token
    if (is_last_line && line_cursor >= current_line.size()) {
        is_end_of_input = true;
    }
}

bool JackTokeniser::hasMoreTokens() { return !is_end_of_input; }

JackTokenType JackTokeniser::getTokenType() { return token_type; }

std::string JackTokeniser::keyWord() {
    if (token_type != JackTokenType::KEYWORD) {
        return "";
    } else {
        return token;
    }
}

char JackTokeniser::symbol() {
    if (token_type != JackTokenType::SYMBOL) {
        return '\0';
    } else {
        return token.c_str()[0];
    }
}

std::string JackTokeniser::identifier() {
    if (token_type != JackTokenType::IDENT) {
        return "";
    } else {
        return token;
    }
}

int JackTokeniser::intVal() {
    if (token_type != JackTokenType::INT_CONST) {
        return -999999999;
    } else {
        return std::stoi(token);
    }
}

std::string JackTokeniser::stringVal() {
    if (token_type != JackTokenType::STRING_CONST) {
        return "";
    } else {
        return token;
    }
}
