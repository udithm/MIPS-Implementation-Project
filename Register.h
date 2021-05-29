#ifndef reg
#define reg
#include<iostream>

using namespace std;

class Register{
    public:
        int t[8];
        int s[8];
        
        Register(){
            for(int i = 0; i < 8; i++){
                t[i] = 0;
                s[i] = 0;
            }
        }

        void reg_update(int value,char x,int in);
        int get_reg_index(char x,int in);
};
#endif
