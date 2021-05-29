#include<string>
#include"Memory.h"

using namespace std;

#ifndef ALU_H
#define ALU_H

class ALU
{
    public:
    string fun;
    int out,in1,in2;
    int Hi=0;
    int Lo=0;
    
    ALU(string Fun,int Out,int In1,int In2);
    int execute();
};

#endif