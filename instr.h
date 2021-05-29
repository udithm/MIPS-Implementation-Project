#ifndef INSTR_H
#define INSTR_H
#include"recog.h"
#include"Memory.h"
#include"Register.h"

using namespace std;


class Instruction
{
    public:
    vector<string> vec;
    string str;
    Memory* M  = new Memory();
    Register* R = new Register();
    Recog rec;
    string sub;
    Instruction(string Str,Memory* m,Register* r);
    void Read();  
    void identify();
    int get_sub();
};

#endif