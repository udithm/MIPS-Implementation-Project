#include"recog.h"

Recog::Recog(string Sub,vector<string> Vec,Memory* m,Register* r)
{
    sub=Sub;
    vec=Vec;
    M=m;
    R=r;
    *(this->return_ptr)=0;
}

int Recog::func()
{
    *return_ptr = 0;
    if(sub.length() == 2)
    {
        if(sub.compare("li")==0)
        {
            int in_reg=stoi(this->vec[1].substr(2,1));
            char x=vec[1].at(1);
            int v =stoi(vec[2]);
            R->reg_update(v,x,in_reg);
        }
        else if(sub.compare("lw")==0)
        {
            int in_reg=stoi(this->vec[1].substr(2,1));
            char x=vec[1].at(1);
            if(vec[2].at(0)!='(')
            {
                int j=0;
                for(int i=0;vec[2].at(i)!='(';i++){
                    j++;
                }
                int imm=stoi(this->vec[2].substr(0,j));
                char y=vec[2].at(j+2);
                int in_reg2=stoi(this->vec[2].substr(j+3,1));
                int reg_val=R->get_reg_index(y,in_reg2);
                int val=stoi(M->get_mem_data_index(imm+reg_val));
                R->reg_update(val,x,in_reg);
            }
            else{
                char y=vec[2].at(1);
                int in_reg2=stoi(this->vec[2].substr(3,1));
                int reg_val=R->get_reg_index(y,in_reg2);
                int val=stoi(M->get_mem_data_index(reg_val));
                R->reg_update(val,x,in_reg);
            }
        }
        else if(sub.compare("sw")==0)
        {
            int in_reg=stoi(this->vec[1].substr(2,1));
            char x=vec[1].at(1);
            if(vec[2].at(0)!='('){
                int j=0;
                for(int i=0;vec[2].at(i)!='(';i++){
                    j++;
                }
                int imm=stoi(this->vec[2].substr(0,j));
                char y=vec[2].at(j+2);
                int in_reg2=stoi(this->vec[2].substr(j+3,1));
                int reg_val=R->get_reg_index(y,in_reg2);
                int val=R->get_reg_index(x,in_reg);
                M->update_mem_data(to_string(val),imm+reg_val);
            }
            else{
                char y=vec[2].at(1);
                int in_reg2=stoi(this->vec[2].substr(3,1));
                int reg_val=R->get_reg_index(y,in_reg2);
                int val=R->get_reg_index(x,in_reg);
                M->update_mem_data(to_string(val),reg_val);
            }
        }
        else 
        {
            goto final;
        }
    }
    else if(sub.length() == 3)
    {
        if(sub.compare("add")==0)
        {
            int in_reg_out=stoi(this->vec[1].substr(2,1));
            char out=vec[1].at(1);
            int in_reg_in1=stoi(this->vec[2].substr(2,1));
            
            char in1=vec[2].at(1);
            
            int val1=R->get_reg_index(in1,in_reg_in1);

            int in_reg_in2=stoi(this->vec[3].substr(2,1));
            char in2=vec[3].at(1);
            int val2=R->get_reg_index(in2,in_reg_in2);
            
            int val_out;
            ALU alu(sub,val_out,in1,in2);
            alu.execute();
            R->reg_update(val_out,out,in_reg_out);
        }
        else if(sub.compare("sub")==0)
        {
            int in_reg_out=stoi(this->vec[1].substr(2,1));
            char out=vec[1].at(1);
            
            int in_reg_in1=stoi(this->vec[2].substr(2,1));
            char in1=vec[2].at(1);
            int val1=R->get_reg_index(in1,in_reg_in1);

            int in_reg_in2=stoi(this->vec[3].substr(2,1));
            char in2=vec[3].at(1);
            int val2=R->get_reg_index(in2,in_reg_in2);

            int val_out;
            ALU alu(sub,val_out,in1,in2);
            alu.execute();
            R->reg_update(val_out,out,in_reg_out);
        }
        else if(sub.compare("mul")==0)
        {
            int in_reg_out=stoi(this->vec[1].substr(2,1));
            char out=vec[1].at(1);
            
            int in_reg_in1=stoi(this->vec[2].substr(2,1));
            char in1=vec[2].at(1);
            int val1=R->get_reg_index(in1,in_reg_in1);
        
            int in_reg_in2=stoi(this->vec[3].substr(2,1));
            char in2=vec[3].at(1);
            int val2=R->get_reg_index(in2,in_reg_in2);
        
            int val_out;
            ALU alu(sub,val_out,val1,val2);
            val_out=alu.execute();
            R->reg_update(val_out,out,in_reg_out);
        }
        else if(sub.compare("div")==0)
        {
            int in_reg1=stoi(this->vec[1].substr(2,1));
            char in1=vec[1].at(1);
            int val1=R->get_reg_index(in1,in_reg1);

            int in_reg2=stoi(this->vec[2].substr(2,1));
            char in2 = vec[2].at(1);
            int val2 = R->get_reg_index(in2,in_reg2);

            int dummy_out;
            ALU alu(sub,dummy_out,val1,val2);
            alu.execute();
            M->update_MFHI(alu.Hi);
            M->update_MFLO(alu.Lo);
        }
        else if(sub.compare("beq")==0)
        {
            int in_reg_in1=stoi(this->vec[1].substr(2,1));
            char in1=vec[1].at(1);
            int val1=R->get_reg_index(in1,in_reg_in1);

            int in_reg_in2=stoi(this->vec[2].substr(2,1));
            char in2=vec[2].at(1);
            int val2=R->get_reg_index(in2,in_reg_in2);
            string in_reg_in3=this->vec[3];

            if(val1==val2)
            {
                for(int i=0;i<M->p.size();i++)
                {
                    if(M->p.at(i).first.compare(in_reg_in3)==0)
                    {
                        this->setLabel(M->p.at(i).second);
                    }
                }
                *return_ptr = 1;
            }
            return *return_ptr;
        }
        else if(sub.compare("bne")==0)
        {
            int in_reg_in1=stoi(this->vec[1].substr(2,1));
            char in1=vec[1].at(1);
            int val1=R->get_reg_index(in1,in_reg_in1);

            int in_reg_in2=stoi(this->vec[2].substr(2,1));
            char in2=vec[2].at(1);
            int val2=R->get_reg_index(in2,in_reg_in2);

            string in_reg_in3=this->vec[3];

            if(val1!=val2)
            {
                for(int i=0;i<M->p.size();i++)
                {
                    if(M->p.at(i).first.compare(in_reg_in3)==0)
                    {
                        this->setLabel(M->p.at(i).second);
                        cout << "BNE label" << this->getLabel();
                    }
                }
                *return_ptr = 1;
            }
            return *return_ptr;
        }
        else if(sub.compare("bgt")==0)
        {
            int in_reg_in1=stoi(this->vec[1].substr(2,1));
            char in1=vec[1].at(1);
            int val1=R->get_reg_index(in1,in_reg_in1);

            int in_reg_in2=stoi(this->vec[2].substr(2,1));
            char in2=vec[2].at(1);
            int val2=R->get_reg_index(in2,in_reg_in2);

            string in_reg_in3=this->vec[3];

            if(val1>val2)
            {
                for(int i=0;i<M->p.size();i++)
                {
                    if(M->p.at(i).first.compare(in_reg_in3)==0)
                    {
                        this->setLabel((M->p.at(i).second));
                    }
                }
                *return_ptr = 1;
            }
            else{
                *return_ptr=0;
            }
            return *return_ptr;
        }
        else if(sub.compare("blt")==0)
        {
            int in_reg_in1=stoi(this->vec[1].substr(2,1));
            char in1=vec[1].at(1);
            int val1=R->get_reg_index(in1,in_reg_in1);

            int in_reg_in2=stoi(this->vec[2].substr(2,1));
            char in2=vec[2].at(1);
            int val2=R->get_reg_index(in2,in_reg_in2);

            string in_reg_in3=this->vec[3];

            if(val1<val2)
            {
                for(int i=0;i<M->p.size();i++)
                {
                    if(M->p.at(i).first.compare(in_reg_in3)==0)
                    {
                        label=M->p.at(i).second;
                    }
                }
                *return_ptr = 1;
            }
            return *return_ptr;
        }
        else 
        {
            goto final;
        }
    }
    else if(sub.length() == 4)
    {
        if(sub.compare("addi")==0)
        {
            int in_reg_out=stoi(this->vec[1].substr(2,1));
            char out=vec[1].at(1);

            int in_reg_in1=stoi(this->vec[2].substr(2,1));
            char in1=vec[2].at(1);
            int val1=R->get_reg_index(in1,in_reg_in1);

            int val2=stoi(this->vec[3]);
            int val_out;
            ALU alu("add",val_out,val1,val2);
            val_out=alu.execute();
            R->reg_update(val_out,out,in_reg_out);
        }
        else if(sub.compare("subi")==0)
        {
            int in_reg_out=stoi(this->vec[1].substr(2,1));
            char out=vec[1].at(1);
            
            int in_reg_in1=stoi(this->vec[2].substr(2,1));
            char in1=vec[2].at(1);
            int val1=R->get_reg_index(in1,in_reg_in1);

            int val2=stoi(this->vec[3]);

            int val_out;
            ALU alu("sub",val_out,val1,val2);
            val_out=alu.execute();
            R->reg_update(val_out,out,in_reg_out);
        }
        else if(sub.compare("mfhi")==0){
            int in_reg_out=stoi(this->vec[1].substr(2,1));
            char out=vec[1].at(1);

            R->reg_update(M->MFHI,out,in_reg_out);
        }
        else if(sub.compare("mflo")==0){
            int in_reg_out=stoi(this->vec[1].substr(2,1));
            char out=vec[1].at(1);

            R->reg_update(M->MFLO,out,in_reg_out);
        }
        else 
        {
            goto final;
        }
    }
    else
    {
        final:
            cout<<"Function not found"<<endl;
    }
}

int Recog::get_return_val()
{
    return *return_ptr;
}

int Recog::getLabel()
{
    return this->label;
}

void Recog::setLabel(int i)
{
    this->label = i;
}
