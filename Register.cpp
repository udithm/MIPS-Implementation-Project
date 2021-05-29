#include "Register.h"

void Register::reg_update(int value,char x,int in){
    if(in>=0 && in<8){
        if(x=='s'){
            s[in]=value;
        }
        if(x=='t'){
            t[in]=value;
        }
    }
}

int Register::get_reg_index(char x,int in){
    if(in>=0 && in<8){
        if(x=='s'){
            return Register::s[in];
        }
        if(x=='t'){
            return Register::t[in];
        }
    }
    return 0;
}