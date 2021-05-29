/*INPUT FOR THE PROGRAM
li $t7,9
li $t2,1
addi $t1,$t7,0
loop:
subi $t1,$t1,1
mul $t7,$t7,$t1
bgt $t1,$t2,loop
end:
*/

#include<vector>
#include<string>
#include<iostream>
#include"instr.h"
#include"Memory.h"
#include"recog.h"
#include"Register.h"
#include"ALU.h"

using namespace std;

int main()
{
    int no_of_cycles=0;
    int pc=0;
    string str;
    Memory* M = new Memory();
    Register* R = new Register();
    vector<string>mem;
    int return_val;
    while(cin)
    {
        getline(cin,str);
        if(str=="\0")
        {
            break;
        }
        mem.push_back(str);
    }
    for(int i=0;i<mem.size();i++)
    {
        int k3=mem.at(i).find(':');
        Instruction ins(mem.at(i),M,R);
        pc=4*i;
        //cout<<"PC: "<<pc<<endl;
        if(k3==string::npos)
        {
            ins.Read();
            return_val=ins.get_sub();
            no_of_cycles+=1;
        }
        else
        {
            string sub = mem.at(i).substr(0,mem.at(i).length()-1);
            pair<string,int>pa;
            pa.first = sub;
            pa.second = i;
            M->p.push_back(pa);
        }
        
        if(return_val!=0)
        {
            i=ins.rec.getLabel();
        }
    }
    cout<<R->t[7]<<endl;
    cout<<"Total no.of cycles for this Program to execute: "<<no_of_cycles<<endl;
    cout<<"PC: "<<pc<<endl;

    return 0;
}