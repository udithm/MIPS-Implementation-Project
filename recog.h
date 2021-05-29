//#include<bits/stdc++.h>
#include<vector>
#include<utility>
#include<string>
#include<iostream>
#include"Memory.h"
#include"Register.h"
#include"ALU.h"

#ifndef RECOG_H
#define RECOG_H
using namespace std;

class Recog
{
    public:
    int* return_ptr; 
    int label;
    Memory* M;
    Register* R;
    string sub;
    vector<pair<string,int>>p;
    vector<string> vec;
    Recog(string ,vector<string> ,Memory* ,Register* );
    Recog(){}
    int func();
    int atoi(string s);
    int get_return_val();
    int getLabel();
    void setLabel(int i);
};

#endif