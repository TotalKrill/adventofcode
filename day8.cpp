/**
 * @file day8.cpp
 * @brief
 * @author Kristoffer Ödmark
 * @version 0.1
 * @date 2015-12-23
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

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

string remove_escapes(string line)
{
    static string bckslash = "\\\\";
    static string quote = "\\\"";
    static string hexa ="\\x";
    line.erase(0,1);
    line.erase(line.length()-1);

    size_t pos = line.find(bckslash);
    while(pos != string::npos){
        line.erase(pos,2);
        //line.insert(pos,"\\");
        line.insert(pos,"0");
        pos = line.find(bckslash);
    }
    pos = line.find(quote);
    while(pos != string::npos){
        line.erase(pos,2);
        //line.insert(pos,"\"");
        line.insert(pos,"0");
        pos = line.find(quote);
    }
    pos = line.find(hexa);
    while(pos != string::npos){
        line.erase(pos,4);
        line.insert(pos,"X");
        pos = line.find(hexa);
    }
    return line;
}
string line_encode(string line)
{
    static string bckslash = "\\";
    static string quote = "\"";
    vector<size_t> slashpos(0);
    size_t pos = line.find(bckslash, 0);

    if(pos != string::npos){
        while(pos != string::npos){
            slashpos.push_back(pos);
            pos = line.find(bckslash,pos+1);
        }

        for(size_t i = 0; i < slashpos.size(); i++){
            line.insert(slashpos[i],bckslash);
        }
    }
    pos = line.find(quote);
    while(pos != string::npos){
        line.insert(pos,"\\");
        pos = line.find(quote,pos+2);
    }

    line.insert(0,"\"");
    line.append("\"");
    return line;

}


int main()
{
    ifstream in("input8");
    string line;
    vector<string> op_list;
    int code = 0;
    int mem = 0;
    int encode = 0;
    while(getline(in, line))
    {
        cout << line << endl;
        code += line.length();
        mem += remove_escapes(line).length();
        encode += line_encode(line).length();
        cout << remove_escapes(line) << endl;
        cout << line_encode(line) << endl;

        op_list.push_back(line);
    }
    cout << "actaul - parsed: " << code - mem<< endl;
    cout << "encoded - actual: "<< encode - code << endl;


}
