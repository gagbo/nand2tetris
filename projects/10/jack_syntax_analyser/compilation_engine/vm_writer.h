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
#ifndef _COMPILATIONENGINE_VMWRITER_H_
#define _COMPILATIONENGINE_VMWRITER_H_

#include <fstream>
#include <iostream>
#include "symbol_table/symbol_table.h"
#include "tokeniser/tokeniser.h"

/** Module that actually writes stuff */
class VmWriter {
 public:
    VmWriter(std::ofstream* o_s) : out_stream(*o_s) { ; }
    ~VmWriter() { ; }

    void Do(std::string function_name, int function_args);
    void Let(const JackVariableTable& var_table, std::string var_name);
    void Push(const JackVariableTable& var_table, std::string var_name);
    void LetArray();
    void Return();
    void ReturnVoid();
    void ReturnThis();
    void IntConst(int int_const);
    void StringConst(std::string string_const);
    void KeywordConst(JackKeyword keyword);
    void Op(char operation);
    void UnaryOp(char operation);
    void ArrayAccess();
    void SubroutineCall(std::string name, int args);
    void Function(std::string name, int local);
    void Constructor(int field_count);
    void Method();

    void IfFirstPart(int label1);
    void IfMidPart(int label2, int label1);
    void Label(int label);
    void Goto(int label);
    void IfGoto(int label);
    void Add();

 protected:
    std::ofstream& out_stream;
};
#endif /* ifndef _COMPILATIONENGINE_VMWRITER_H_ */
