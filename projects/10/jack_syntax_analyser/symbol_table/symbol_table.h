#ifndef _SYMBOLTABLE_SYMBOLTABLE_H
#define _SYMBOLTABLE_SYMBOLTABLE_H

#include <map>
#include <string>
#include <tuple>

enum struct JackVariableKind : int { FIELD, STATIC, ARGUMENT, LOCAL };

static const char* KindStrings[] = {"field", "static", "argument", "local"};

inline const char* getTextForKind(int enumVal) { return KindStrings[enumVal]; }

typedef std::tuple<std::string, JackVariableKind, int> SymbolEntry;

#endif /* ifndef _SYMBOLTABLE_SYMBOLTABLE_H */
