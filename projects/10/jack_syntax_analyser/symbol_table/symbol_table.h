/* Copyright 2017 Gerry Agbobada
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of version 3 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef _SYMBOLTABLE_SYMBOLTABLE_H
#define _SYMBOLTABLE_SYMBOLTABLE_H

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <tuple>

enum struct JackVariableKind : int { FIELD, STATIC, ARGUMENT, LOCAL, NONE };

static const char* KindStrings[] = {"this", "static", "argument", "local", ""};

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
    JackVariableTable() : p_parent_scope(NULL) { var_map.clear(); }
    JackVariableTable(JackVariableTable* p_parent_scope)
        : p_parent_scope(p_parent_scope) {
        var_map.clear();
    }
    ~JackVariableTable() { ; }

    // Insert / Clear operations
    bool Insert(std::string var_name, SymbolEntry var_tuple);
    bool Insert(std::string var_name, std::string var_type,
                JackVariableKind var_kind);
    void Clear();

    // Setter
    void SetParent(const JackVariableTable& parent_scope);

    // Accessors
    std::string GetVmOutput(std::string var_key) const;
    JackVariableKind GetKindOf(std::string var_key) const;
    std::string GetTypeOf(std::string var_key) const;
    int GetIndexOf(std::string var_key) const;
    inline int FieldCount() const { return field_count; }

    // Lookup function
    bool IsSymbol(std::string var_key) const;

 protected:
    const JackVariableTable* p_parent_scope;
    JackSymbolTable var_map;
    int field_count;
    int static_count;
    int local_count;
    int argument_count;

 private:
    int* VarCount(JackVariableKind);
};

#endif /* ifndef _SYMBOLTABLE_SYMBOLTABLE_H */
