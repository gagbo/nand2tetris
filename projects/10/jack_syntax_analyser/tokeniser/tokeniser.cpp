#include "tokeniser.h"

std::string JackTokeniser::delimiterList = "(){};.=+-*/\"";
std::string JackTokeniser::commentList = "// /** /*";

JackTokeniser::JackTokeniser() {
    in_stream = 0;
    token = "";
    isEOInput = false;
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

bool JackTokeniser::hasMoreTokens() { return !isEOInput; }

JackTokenType JackTokeniser::getTokenType() { return tokenType; }

std::string JackTokeniser::keyWord() {
    if (tokenType != JackTokenType::KEYWORD) {
        return "";
    } else {
        return token;
    }
}

char JackTokeniser::symbol() {
    if (tokenType != JackTokenType::SYMBOL) {
        return '\0';
    } else {
        return token.c_str()[0];
    }
}

std::string JackTokeniser::identifier() {
    if (tokenType != JackTokenType::IDENT) {
        return "";
    } else {
        return token;
    }
}

int JackTokeniser::intVal() {
    if (tokenType != JackTokenType::INT_CONST) {
        return -999999999;
    } else {
        return std::stoi(token);
    }
}

std::string JackTokeniser::stringVal() {
    if (tokenType != JackTokenType::STRING_CONST) {
        return "";
    } else {
        return token;
    }
}
