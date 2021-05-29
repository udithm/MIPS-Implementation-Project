#include"ALU.h"
using namespace std;

ALU::ALU(string Fun,int Out,int In1,int In2)
{
    fun = Fun;
    out = Out;
    in1 = In1;
    in2 = In2;
}

int ALU::execute()
{
    if(fun.find("add")==0)
    {
        return out = in1 + in2;
    }
    else if(fun.find("sub")==0)
    {
        return out = in1 - in2;
    }
    else if(fun.compare("mul")==0)
    {
        return out = in1 * in2;
    }
    else if(fun.compare("div")==0)
    {
        Lo = in1/in2;
        Hi = in1%in2;
        return 1;
    }
    return 0;
}

