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
    void ReturnVoid();
    void IntConst(int int_const);
    void KeywordConst(JackKeyword keyword);
    void Op(char operation);
    void UnaryOp(char operation);

 protected:
    std::ofstream& out_stream;
};
#endif /* ifndef _COMPILATIONENGINE_VMWRITER_H_ */
