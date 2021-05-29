//finds out the function part of the given instruction.

#include<bits/stdc++.h>
#include"instr.h"

using namespace std;


Instruction::Instruction(string Str,Memory* m,Register* r)
{
    this->str = Str;
    this->M=m;
    this->R=r;
}

void Instruction::Read()
{   
    int j=0;
    for(int i=0;i<str.length();i++)
    {
        int k1=str.find(' ');
        int k2=str.find(',');
        int k3=str.find(':');
        if(k1!=string::npos || k2!=string::npos)
        {
            if(str[i]==' ')
            {
                string str1=str.substr(j,i-j);
                vec.push_back(str1);
                j=i;       
            }
            else if(str[i]==',')
            {
                string str1=str.substr(j+1,i-j-1);
                vec.push_back(str1);
                j=i;
            }
            else if(i==str.length()-1)
            {
                string str1 = str.substr(j+1,i);
                vec.push_back(str1);
            }
        }
        else
        {
            cout<<"wrong format"<<endl;    
            break;
        }

    }
}

int Instruction::get_sub()
{
    string sub1 = "";
    sub1 = sub1 + vec.at(0);
    this->rec=Recog(sub1,vec,M,R);
    rec.func();
    return *(rec.return_ptr);
}