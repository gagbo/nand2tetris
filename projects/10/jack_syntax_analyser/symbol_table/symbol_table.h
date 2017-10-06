#ifndef _SYMBOLTABLE_SYMBOLTABLE_H
#define _SYMBOLTABLE_SYMBOLTABLE_H

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <tuple>

enum struct JackVariableKind : int { FIELD, STATIC, ARGUMENT, LOCAL, NONE };

static const char* KindStrings[] = {"field", "static", "argument", "local", ""};

inline const char* getTextForKind(JackVariableKind enumVal) {
    return KindStrings[static_cast<int>(enumVal)];
}

// Tuple of symbol entry. (
// type - int, Class, bool...- ,
// kind -local, field // static...- ,
// count - 0++ -
// )
// The tuples will be added in a map indexed by the identifier. This is
// the implementation of the symbol table.
typedef std::tuple<std::string, JackVariableKind, int> SymbolEntry;

typedef std::map<std::string, SymbolEntry> JackSymbolTable;

// A class to encapsulate counters and methods for JackSymbolTables
class JackVariableTable {
 public:
    JackVariableTable() { var_map.clear(); }
    ~JackVariableTable() { ; }

    // Insert / Clear operations
    bool Insert(std::string var_name, SymbolEntry var_tuple);
    bool Insert(std::string var_name, std::string var_type,
                JackVariableKind var_kind);
    void Clear();

    // Accessors
    std::string GetVmOutput(std::string var_key,
                            JackVariableTable* p_parent_scope = NULL) const;
    JackVariableKind GetKindOf(std::string var_key) const;
    std::string GetTypeOf(std::string var_key) const;
    int GetIndexOf(std::string var_key) const;

 protected:
    JackSymbolTable var_map;
    int field_count;
    int static_count;
    int local_count;
    int argument_count;

 private:
    int* VarCount(JackVariableKind);
};

#endif /* ifndef _SYMBOLTABLE_SYMBOLTABLE_H */
