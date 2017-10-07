#include "vm_writer.h"

void VmWriter::Do(std::string function_name, int function_args) {
    out_stream << "call " << function_name << " " << function_args << "\n";
    out_stream << "pop temp 0\n";
}

void VmWriter::Let(const JackVariableTable& var_table, std::string var_name) {
    out_stream << "pop " << var_table.GetVmOutput(var_name) << "\n";
}

void VmWriter::Push(const JackVariableTable& var_table, std::string var_name) {
    out_stream << "push " << var_table.GetVmOutput(var_name) << "\n";
}

void VmWriter::LetArray() {
    out_stream << "pop temp 3\n"
                  "pop pointer 1\n"
                  "push temp 3\n"
                  "pop that 0\n";
}

void VmWriter::Return() { out_stream << "return\n"; }

void VmWriter::ReturnVoid() {
    out_stream << "push constant 0\n"
                  "return\n";
}

void VmWriter::ReturnThis() {
    out_stream << "push pointer 0\n"
                  "return\n";
}

void VmWriter::IntConst(int int_const) {
    out_stream << "push constant " << int_const << "\n";
}

void VmWriter::StringConst(std::string string_const) {
    int len = string_const.length();
    out_stream << "push constant " << len << "\n";
    out_stream << "call String.new 1\n";
    out_stream << "pop temp 1\n";
    for (int i = 0; i < len; ++i) {
        char to_append = string_const[i];
        out_stream << "push temp 1\n"
                      "push constant "
                   << +to_append << "\n"
                                    "call String.appendChar 2\n"
                                    "pop temp 0\n";
    }
    out_stream << "push temp 1\n";

    out_stream << "push temp 1\n";
    out_stream << "call Memory.deAlloc 1\n"
                  "pop temp 0\n";
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

void VmWriter::ArrayAccess() {
    out_stream << "pop pointer 1\n"
                  "push that 0\n";
}

void VmWriter::SubroutineCall(std::string name, int args) {
    out_stream << "call " << name << " " << args << "\n";
}

void VmWriter::Function(std::string name, int args) {
    out_stream << "function " << name << " " << args << "\n";
}

void VmWriter::Constructor(int field_count) {
    out_stream << "push constant " << field_count << "\n";
    out_stream << "call Memory.alloc 1\n";
    out_stream << "pop pointer 0\n";
}

void VmWriter::Method() {
    out_stream << "push argument 0\n";
    out_stream << "pop pointer 0\n";
}

void VmWriter::IfFirstPart(int label1) {
    out_stream << "not\n"
                  "if-goto "
               << "Label" << label1 << "\n";
}

void VmWriter::IfMidPart(int label2, int label1) {
    out_stream << "goto "
               << "Label" << label2 << "\n"
               << "label "
               << "Label" << label1 << "\n";
}

void VmWriter::Label(int label) {
    out_stream << "label "
               << "Label" << label << "\n";
}

void VmWriter::Goto(int label) {
    out_stream << "goto "
               << "Label" << label << "\n";
}

void VmWriter::IfGoto(int label) {
    out_stream << "if-goto "
               << "Label" << label << "\n";
}

void VmWriter::Add() { out_stream << "add\n"; }
