
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}
vector<string> split(string data, string token)
{
    vector<string> output;
    size_t pos = string::npos;
    do
    {
        pos = data.find(token);
        output.push_back(data.substr(0, pos));
        if (string::npos != pos)
            data = data.substr(pos + token.size());
    } while (string::npos != pos);
    return output;
}

class Reg
{
    public:
        uint16_t value;
        string name;
        bool is_set;
        Reg(string name){
            this->name = name;
            this->is_set = false;
            this->value = 0;
        }

        void set_value(uint16_t value)
        {
            this->value = value;
            this->is_set = true;
        }
};
size_t find_reg(vector<Reg> &regs, string regname)
{

    for (size_t j =0; j < regs.size(); j++){
        if(regs[j].name == regname)
        {
            return j;
        }
    }
    return -1;
}
bool unset_all(vector<Reg> &regs)
{
    for (size_t j =0; j < regs.size(); j++){
        regs[j].value = 0;
        regs[j].is_set = false;
    }
    return true;
}

bool all_set(vector<Reg> &regs)
{
    for (size_t j =0; j < regs.size(); j++){
        if(regs[j].is_set == false)
        {
            return false;
        }
    }
    return true;
}

void do_operations(vector<string> &op_list, vector<Reg> &registers){

    while(!all_set(registers)){
        for(size_t i = 0; i < op_list.size(); i++){
            vector<string> vec = split(op_list[i], " ");


            Reg &r0 = registers[find_reg(registers, vec.back())];
            if(!r0.is_set){

                if(vec[1] == "->")
                {

                    if(is_number(vec[0])){
                        int value = stoi(vec[0]);
                        r0.set_value(value);
                    }
                    else
                    {
                        Reg &r1 = registers[find_reg(registers, vec[0])];
                        if(r1.is_set && !r0.is_set)
                        {
                            r0.set_value(r1.value);
                        }
                    }

                }
                else if(vec[1] == "AND")
                {
                    Reg r1(" ");
                    Reg r2(" ");
                    if(is_number(vec[0]))
                    {
                        r1.set_value(stoi(vec[0]));
                        r2 = registers[find_reg(registers, vec[2])];
                    }
                    else
                    {
                        r1 = registers[find_reg(registers, vec[0])];
                        r2 = registers[find_reg(registers, vec[2])];
                    }
                    if (r1.is_set && r2.is_set && !r0.is_set)
                    {
                        r0.set_value((r1.value & r2.value));
                    }
                }

                else if( vec[1] == "OR")
                {
                    Reg &r1 = registers[find_reg(registers, vec[0])];
                    Reg &r2 = registers[find_reg(registers, vec[2])];
                    if (r1.is_set && r2.is_set && !r0.is_set)
                    {
                        r0.set_value((r1.value | r2.value));
                    }

                }


                else if( vec[1] == "LSHIFT")
                {
                    Reg &r1 = registers[find_reg(registers, vec[0])];
                    if (r1.is_set  && !r0.is_set)
                    {
                        r0.set_value(r1.value << stoi(vec[2]) );
                    }

                }

                else if( vec[1] == "RSHIFT")
                {
                    Reg &r1 = registers[find_reg(registers, vec[0])];
                    if (r1.is_set  && !r0.is_set)
                    {
                        r0.set_value(r1.value >> stoi(vec[2]) );
                    }

                }

                else if( vec[0] == "NOT")
                {
                    Reg &r1 = registers[find_reg(registers, vec[1])];
                    if (r1.is_set && !r0.is_set)
                    {
                        r0.set_value(~r1.value);
                    }

                }
            }
        }
    }
}



int main()
{
    ifstream in("input7");

    //ifstream in("test");
    string line;
    vector<Reg> registers;
    vector<string> op_list;

    while(getline(in, line))
    {

        op_list.push_back(line);
    }
    // first enumerate registers
    for(size_t i = 0; i < op_list.size(); i++){

        string regname = split(op_list[i], " ").back();
        bool exists = false;
        for (size_t j =0; j < registers.size(); j++){
            if(registers[j].name == regname)
            {
                cout << regname + " already exists" << endl;
                exists = true;
            }
        }
        if(!exists)
        {
            cout << "added " + regname + " as register" << endl;
            registers.push_back(Reg(regname));
        }

    }


    //try their operations
    do_operations(op_list, registers);
    uint16_t override_value = registers[find_reg(registers, "a")].value;
    unset_all(registers);
    registers[find_reg(registers,"b")].set_value(override_value);

    do_operations(op_list, registers);



    for (size_t j =0; j < registers.size(); j++){
        cout << registers[j].name +": " << registers[j].value << endl;
    }

    cout << "Register a is " << registers[find_reg(registers,"a")].value << endl;

    return 0;
}
