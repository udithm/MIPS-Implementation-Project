#ifndef memory
#define memory
#include<vector>
#include<string>

using namespace std; 


class Memory{
    typedef vector<string> vec;
    
    public:
    vec mem_data;
    vec mem_ins;
    vector<pair<string,int>> p;
    
    int MFHI=0;
    int MFLO=0;
    Memory(){
            for(int i=0;i<1000;i++){
                mem_data.push_back("0");   
            }
            for(int i=0;i<1000;i++){
                mem_ins.push_back("0");   
            }
    }

    void update_mem_data(string s,int in);
    void add_mem_data(string s);
    string get_mem_data_index(int in); 

    void update_mem_ins(string s,int in);
    void add_mem_ins(string s);
    string get_mem_ins_index(int in);

    void update_MFHI(int x);
    int get_MFHI();

    void update_MFLO(int x);
    int get_MFLO();
};
#endif
