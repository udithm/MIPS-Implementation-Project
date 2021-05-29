#include "Memory.h"
#include<iostream>

using namespace std;

void Memory::update_mem_data(string s,int in){
    if(in>=0 && in<Memory::mem_data.size()){
        Memory::mem_data[in]=s;
    }
}

void Memory::add_mem_data(string s){
    Memory::mem_data.push_back(s);
}

string Memory::get_mem_data_index(int in){
    cout<<in<<endl;
    cout<<mem_data.at(in)<<endl; 
    return mem_data.at(in); 
}

void Memory::update_mem_ins(string s,int in){
    if(in>=0 && in<Memory::mem_ins.size()){
        Memory::mem_ins[in]=s;
    }
}

void Memory::add_mem_ins(string s){
    Memory::mem_ins.push_back(s);
}

string Memory::get_mem_ins_index(int in){
    return Memory::mem_ins.at(in); 
}

void Memory::update_MFHI(int x){
    Memory::MFHI=x;
}

int Memory::get_MFHI(){
    return Memory::MFHI;
}

void Memory::update_MFLO(int x){
    Memory::MFLO=x;
}

int Memory::get_MFLO(){
    return Memory::MFLO;
}


