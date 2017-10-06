#include "vm_writer.h"

void VmWriter::Do(std::string function_name, int function_args) {
    out_stream << "call " << function_name << " " << function_args << "\n";
    out_stream << "pop temp 0\n";
}

void VmWriter::Let(const JackVariableTable& var_table, std::string var_name) {
    out_stream << "pop " << var_table.GetVmOutput(var_name) << "\n";
}

void VmWriter::ReturnVoid() {
    out_stream << "push constant 0\n"
                  "return\n";
}

void VmWriter::IntConst(int int_const) {
    out_stream << "push constant " << int_const << "\n";
}

void VmWriter::Op(char operation) {
    switch (operation) {
        case ('-'):
            out_stream << "sub\n";
            break;
        case ('*'):
            out_stream << "call Math.multiply 2\n";
            break;
        case ('/'):
            out_stream << "call Math.divide 2\n";
            break;
        case ('&'):
            out_stream << "and\n";
            break;
        case ('|'):
            out_stream << "or\n";
            break;
        case ('<'):
            out_stream << "lt\n";
            break;
        case ('>'):
            out_stream << "gt\n";
            break;
        case ('='):
            out_stream << "eq\n";
            break;
        case ('+'):
            out_stream << "add\n";
            break;
        default:
            std::cerr << "codeWriter Op : " << operation << "not found\n";
            exit(1);
    }
}

void VmWriter::UnaryOp(char operation) {
    switch (operation) {
        case ('-'):
            out_stream << "neg\n";
            break;
        case ('~'):
            out_stream << "not\n";
            break;
        default:
            std::cerr << "codeWriter UnaryOp : " << operation << "not found\n";
            exit(1);
    }
}
void VmWriter::KeywordConst(JackKeyword keyword) {
    switch (keyword) {
        case (JackKeyword::TRUE_):
            out_stream << "push constant 1\n"
                          "neg\n";
            break;
        case (JackKeyword::FALSE_):
            out_stream << "push constant 0\n";
            break;
        case (JackKeyword::NULL_):
            out_stream << "push constant 0\n";
            break;
        case (JackKeyword::THIS_):
            out_stream << "push pointer 0\n";
            break;
        default:
            std::cerr << "VmWriter KeywordConst error !\n";
            exit(1);
    }
}
