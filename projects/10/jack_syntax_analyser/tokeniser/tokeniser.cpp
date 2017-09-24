#include "tokeniser.h"

std::string JackTokeniser::st_symbol_list = "(){}[].,;+-*/&|<>=~";
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

void JackTokeniser::init() {
    in_stream = 0;
    current_line = "";
    line_cursor = 0;
    token = "";
    is_last_line = false;
    is_end_of_input = false;
}

JackTokeniser::JackTokeniser() { init(); }

JackTokeniser::JackTokeniser(const char* filename) {
    init();
    in_stream = new std::ifstream();
    in_stream->open(filename);
    if (!in_stream->is_open()) {
        std::cerr << "Could not open " << filename << "\n";
        exit(1);
    }
    advance();
}

JackTokeniser::JackTokeniser(std::ifstream* input_stream) {
    init();
    in_stream = input_stream;
    advance();
}

JackTokeniser::~JackTokeniser() {
    in_stream->close();
    delete in_stream;
}

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
    line_cursor = current_line.find_first_not_of(" \n\r\t", line_cursor);
    if (is_last_line && line_cursor == std::string::npos) {
        is_end_of_input = true;
        return;
    }
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
            line_cursor = current_line.find_first_not_of(" \t", next);
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
            line_cursor = current_line.find_first_not_of(" \t", line_cursor);
        } else if (st_symbol_list.find(current_line.at(line_cursor)) !=
                   std::string::npos) {
            // SYMBOL Handling
            token = current_line.substr(line_cursor++, 1);
            token_type = JackTokenType::SYMBOL;
            line_cursor = current_line.find_first_not_of(" \t", line_cursor);
        } else if (st_ident_start_list.find(current_line.at(line_cursor)) !=
                   std::string::npos) {
            size_t next =
                current_line.find_first_not_of(st_ident_char_list, line_cursor);
            size_t offset = (next == std::string::npos) ? std::string::npos
                                                        : (next - line_cursor);
            token = current_line.substr(line_cursor, offset);
            token_type =
                isKeyword() ? JackTokenType::KEYWORD : JackTokenType::IDENT;
            line_cursor = current_line.find_first_not_of(" \t", next);
        } else {
            std::cerr << "Could not handle character : "
                      << current_line.at(line_cursor)
                      << " in : " << current_line << "\n";
            exit(1);
        }
    }

    return;
}

char JackTokeniser::peek() const { return current_line.at(line_cursor); }

bool JackTokeniser::hasMoreTokens() const { return !is_end_of_input; }

JackTokenType JackTokeniser::getTokenType() const { return token_type; }

std::string JackTokeniser::getToken() const { return token; }

std::string JackTokeniser::xmlOutput() const {
    std::ostringstream return_stream;

    switch (token_type) {
        case JackTokenType::KEYWORD: {
            return_stream << "<keyword> ";
            return_stream << token;
            return_stream << " </keyword>\n";
            break;
        }
        case JackTokenType::SYMBOL: {
            return_stream << "<symbol> ";
            return_stream << token;
            return_stream << " </symbol>\n";
            break;
        }
        case JackTokenType::IDENT: {
            return_stream << "<identifier> ";
            return_stream << token;
            return_stream << " </identifier>\n";
            break;
        }
        case JackTokenType::INT_CONST: {
            return_stream << "<integerConstant> ";
            return_stream << token;
            return_stream << " </integerConstant>\n";
            break;
        }
        case JackTokenType::STRING_CONST: {
            return_stream << "<stringConstant> ";
            return_stream << token;
            return_stream << " </stringConstant>\n";
            break;
        }
        default: {
            std::cerr << "xmlOutput error : doesn't know this "
                         "JackTokenType !!\n";
            exit(1);
        }
    }
    return return_stream.str();
}

void JackTokeniser::showState() const {
    std::cerr << "State of Tokenizer : "
              << "line : '" << current_line << "'\n"
              << "token : '" << token << "'\n"
              << "cursor : " << line_cursor << "\n"
              << "char under cursor : '" << current_line.at(line_cursor)
              << "'\n"
              << "-----------------------------------\n";
    return;
}

JackKeyword JackTokeniser::keyWord() const {
    if (token_type != JackTokenType::KEYWORD) {
        return JackKeyword::NOT_KEYWORD;
    } else {
        return token_keyword;
    }
}

char JackTokeniser::symbol() const {
    if (token_type != JackTokenType::SYMBOL) {
        return '\0';
    } else {
        return token.c_str()[0];
    }
}

std::string JackTokeniser::identifier() const {
    if (token_type != JackTokenType::IDENT) {
        return "";
    } else {
        return token;
    }
}

int JackTokeniser::intVal() const {
    if (token_type != JackTokenType::INT_CONST) {
        return std::numeric_limits<int>::min();
    } else {
        return std::stoi(token);
    }
}

std::string JackTokeniser::stringVal() const {
    if (token_type != JackTokenType::STRING_CONST) {
        return "";
    } else {
        return token;
    }
}

bool JackTokeniser::isKeyword() {
    if (isCLASS()) {
        return true;
    } else if (isCONSTRUCTOR()) {
        return true;
    } else if (isFUNCTION()) {
        return true;
    } else if (isMETHOD()) {
        return true;
    } else if (isFIELD()) {
        return true;
    } else if (isSTATIC()) {
        return true;
    } else if (isVAR()) {
        return true;
    } else if (isINT()) {
        return true;
    } else if (isCHAR()) {
        return true;
    } else if (isBOOLEAN()) {
        return true;
    } else if (isVOID()) {
        return true;
    } else if (isTRUE()) {
        return true;
    } else if (isFALSE()) {
        return true;
    } else if (isNULL()) {
        return true;
    } else if (isTHIS()) {
        return true;
    } else if (isLET()) {
        return true;
    } else if (isDO()) {
        return true;
    } else if (isIF()) {
        return true;
    } else if (isELSE()) {
        return true;
    } else if (isWHILE()) {
        return true;
    } else if (isRETURN()) {
        return true;
    } else {
        return false;
    }
}

bool JackTokeniser::isCLASS() {
    if (token == "class") {
        token_keyword = JackKeyword::CLASS_;
        return true;
    }
    return false;
}

bool JackTokeniser::isCONSTRUCTOR() {
    if (token == "constructor") {
        token_keyword = JackKeyword::CONSTRUCTOR_;
        return true;
    }
    return false;
}

bool JackTokeniser::isFUNCTION() {
    if (token == "function") {
        token_keyword = JackKeyword::FUNCTION_;
        return true;
    }
    return false;
}

bool JackTokeniser::isMETHOD() {
    if (token == "method") {
        token_keyword = JackKeyword::METHOD_;
        return true;
    }
    return false;
}

bool JackTokeniser::isFIELD() {
    if (token == "field") {
        token_keyword = JackKeyword::FIELD_;
        return true;
    }
    return false;
}

bool JackTokeniser::isSTATIC() {
    if (token == "static") {
        token_keyword = JackKeyword::STATIC_;
        return true;
    }
    return false;
}

bool JackTokeniser::isVAR() {
    if (token == "var") {
        token_keyword = JackKeyword::VAR_;
        return true;
    }
    return false;
}

bool JackTokeniser::isINT() {
    if (token == "int") {
        token_keyword = JackKeyword::INT_;
        return true;
    }
    return false;
}

bool JackTokeniser::isCHAR() {
    if (token == "char") {
        token_keyword = JackKeyword::CHAR_;
        return true;
    }
    return false;
}

bool JackTokeniser::isBOOLEAN() {
    if (token == "boolean") {
        token_keyword = JackKeyword::BOOLEAN_;
        return true;
    }
    return false;
}

bool JackTokeniser::isVOID() {
    if (token == "void") {
        token_keyword = JackKeyword::VOID_;
        return true;
    }
    return false;
}

bool JackTokeniser::isTRUE() {
    if (token == "true") {
        token_keyword = JackKeyword::TRUE_;
        return true;
    }
    return false;
}

bool JackTokeniser::isFALSE() {
    if (token == "false") {
        token_keyword = JackKeyword::FALSE_;
        return true;
    }
    return false;
}

bool JackTokeniser::isNULL() {
    if (token == "null") {
        token_keyword = JackKeyword::NULL_;
        return true;
    }
    return false;
}

bool JackTokeniser::isTHIS() {
    if (token == "this") {
        token_keyword = JackKeyword::THIS_;
        return true;
    }
    return false;
}

bool JackTokeniser::isLET() {
    if (token == "let") {
        token_keyword = JackKeyword::LET_;
        return true;
    }
    return false;
}

bool JackTokeniser::isDO() {
    if (token == "do") {
        token_keyword = JackKeyword::DO_;
        return true;
    }
    return false;
}

bool JackTokeniser::isIF() {
    if (token == "if") {
        token_keyword = JackKeyword::IF_;
        return true;
    }
    return false;
}

bool JackTokeniser::isELSE() {
    if (token == "else") {
        token_keyword = JackKeyword::ELSE_;
        return true;
    }
    return false;
}

bool JackTokeniser::isWHILE() {
    if (token == "while") {
        token_keyword = JackKeyword::WHILE_;
        return true;
    }
    return false;
}

bool JackTokeniser::isRETURN() {
    if (token == "return") {
        token_keyword = JackKeyword::RETURN_;
        return true;
    }
    return false;
}
