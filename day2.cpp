/**
 * @file day2.cpp
 * @brief
 * @author Kristoffer Ödmark
 * @version 0.1
 * @date 2015-12-05
 */
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

vector<string> split(string data, string token)
{
    vector<string> output;
    int pos = string::npos;
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
    ifstream in("input2");
    int papersquarefeet = 0;
    int ribbon = 0;
    string line;
    while(getline(in, line))
    {
        vector<string> dimensions = split(line, "x");
        int width = stoi(dimensions[1]);
        int height = stoi(dimensions[2]);
        int length = stoi(dimensions[0]);

        int cubic  = width*length*height;
        int perimeter = 0;
        int lw = width*length;
        int wh = width *height;
        int hl = height *length;

        int smallest = 0;
        if( lw <= wh && lw <= hl)
            smallest = lw;
        if( wh <= lw && wh <= hl)
            smallest = wh;
        if( hl <= lw && hl <= wh)
            smallest = hl;
        papersquarefeet = papersquarefeet + 2*wh+2*hl+2*lw + smallest;

        if(width >= height && width >= length)
            perimeter = (height+length) *2;
        if(height >=width && height >= length)
            perimeter =  (width + length) *2;
        if(length >=width && length >= height)
            perimeter =  (width + height) *2;

        ribbon += perimeter + cubic;

    }
    cout << "Total square feet of paper: " << papersquarefeet <<endl;
    cout << "Total ribbon: " << ribbon <<endl;
    return 0;
}

