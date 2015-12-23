/**
 * @file day9.cpp
 * @brief
 *
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


int main()
{
    //ifstream in("dayx");
    ifstream in("test");
    string line;
    vector<string> op_list;

    while(getline(in, line))
    {
        op_list.push_back(line);
    }
    cout << op_list.size() << endl;


}

