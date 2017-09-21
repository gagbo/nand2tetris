#include "tokeniser.h"

std::string JackTokeniser::st_symbol_list = "(){}[];.=+-*/";
std::string JackTokeniser::st_ident_start_list =
    "abcedefg"
    "hijklmno"
    "pqrstuvw"
    "xyzABCDE"
    "FGHIJKLM"
    "NOPQRSTU"
    "VWXYZ_";
std::string JackTokeniser::st_ident_char_list =
    "abcedefg"
    "hijklmno"
    "pqrstuvw"
    "xyzABCDE"
    "FGHIJKLM"
    "NOPQRSTU"
    "VWXYZ_"
    "1234567890";
std::string JackTokeniser::st_comment_list = "//\n/*";
std::string JackTokeniser::st_delimiter_list = "(){};.=+-*/\" \r\t\n";

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
              /* This is the zone where a State Machine implementation could be
               * helpful, for now we'll just run the cases without higher level
               * designs
               * in mind
               */
        // TODO : Put these if blocks in private methods
        // If the first char is a digit (forcement INT_CONST)
        if (std::isdigit(current_line.at(line_cursor))) {
            size_t next =
                current_line.find_first_not_of("0123456789", line_cursor);
            size_t offset = (next == std::string::npos) ? std::string::npos
                                                        : (next - line_cursor);
            token = current_line.substr(line_cursor, offset);
            token_type = JackTokenType::INT_CONST;
            line_cursor = next;
        } else if (current_line.at(line_cursor) == '"') {
            // STRING_CONST handling
            line_cursor++;  // Eat the opening "
            size_t next = current_line.find("\"", line_cursor);
            size_t offset = (next == std::string::npos)
                                ? std::string::npos
                                : (next - line_cursor - 1);
            token = current_line.substr(line_cursor, offset);
            token_type = JackTokenType::STRING_CONST;
            line_cursor = next;
            line_cursor++;  // Eat the closing "
        } else if (st_symbol_list.find(current_line.at(line_cursor)) !=
                   std::string::npos) {
            // SYMBOL Handling
            token = current_line.substr(line_cursor++, 1);
            token_type = JackTokenType::SYMBOL;
        } else if (st_ident_start_list.find(current_line.at(line_cursor)) !=
                   std::string::npos) {
            size_t next =
                current_line.find_first_not_of(st_ident_char_list, line_cursor);
            size_t offset = (next == std::string::npos) ? std::string::npos
                                                        : (next - line_cursor);
            token = current_line.substr(line_cursor, offset);
            // TODO: Analyse token to give KEYWORD or IDENT JackTokenType
            // TODO: Create private methods to check for each keyword type
            /* TODO: Nest all call to individual KEYWORD check in a bigger
             * private method
             */
            line_cursor = next;
        } else {
            std::cerr << "Could not handle character : "
                      << current_line.at(line_cursor)
                      << " in : " << current_line << "\n";
            exit(1);
        }
    }

    // At this point, the line_cursor should be set on the char after the token
    if (is_last_line && (line_cursor == std::string::npos ||
                         line_cursor >= current_line.size())) {
        is_end_of_input = true;
    }
}

bool JackTokeniser::hasMoreTokens() { return !is_end_of_input; }

JackTokenType JackTokeniser::getTokenType() { return token_type; }

JackKeyword JackTokeniser::keyWord() {
    if (token_type != JackTokenType::KEYWORD) {
        return JackKeyword::NOT_KEYWORD;
    } else {
        return token_keyword;
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
