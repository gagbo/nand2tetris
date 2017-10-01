#ifndef _SYMBOLTABLE_SYMBOLTABLE_H
#define _SYMBOLTABLE_SYMBOLTABLE_H

#include <map>
#include <string>
#include <tuple>

enum struct JackVariableKind : int { FIELD, STATIC, ARGUMENT, LOCAL };

static const char* KindStrings[] = {"field", "static", "argument", "local"};

inline const char* getTextForKind(int enumVal) { return KindStrings[enumVal]; }

// Tuple of symbol entry. (
// type - int, Class, bool...- ,
// kind -local, field // static...- ,
// count - 0++ -
// )
// The tuples will be added in a map indexed by the identifier. This is
// the implementation of the symbol table.
typedef std::tuple<std::string, JackVariableKind, int> SymbolEntry;

typedef std::map<std::string, SymbolEntry> JackSymbolTable;

#endif /* ifndef _SYMBOLTABLE_SYMBOLTABLE_H */
