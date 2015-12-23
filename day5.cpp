/**
 * @file day5.cpp
 * @brief  :e
 * @author Kristoffer Ödmark
 * @version 0.1
 * @date 2015-12-06
 */
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


bool containsforbidden(string line)
{
    static string naughtystr[4] = {"ab", "cd", "pq", "xy"};
    for(int i =0; i < 4; i++)
    {
        if(line.find(naughtystr[i]) != ::string::npos)
        {
            return true;
        }
    }
    return false;
}

bool containsdouble(string line)
{
    for(int i =0; i < (int)line.length() - 1 ; i++)
    {
        if(line[i] == line[i+1])
        {
            return true;
        }
    }
    return false;
}
bool containsgap(string line)
{
    for(int i =0; i < (int)line.length() - 2 ; i++)
    {
        if(line[i] == line[i+2])
        {
            return true;
        }
    }
    return false;
}

int nrofvowels(string line)
{
    static char vowels[5] = {'a', 'e', 'i', 'o', 'u'};
    int vowel = 0;
    for(int i =0; i < (int)line.length(); i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if(line[i] == vowels[j])
                vowel++;
        }
    }
    return vowel;
}

bool patternrepeat(string line)
{
    for(int i =0; i < (int)line.length()-1; i++)
    {
        string copyline = line;
        string pattern = copyline.substr(i,2);
        // replace with "" instead not very secure
        string overlapremoved = copyline.replace(i,2," ");
        //cout << overlapremoved << endl;
        if(overlapremoved.find(pattern) != string::npos)
            return true;
    }
    return false;
}


int main()
{
    ifstream in("input5");
    string line;

    int nice = 0;
    while(getline(in, line))
    {
        //task1 if(containsdouble(line) && !containsforbidden(line) && nrofvowels(line) >=3)
        if(containsgap(line) && patternrepeat(line))
        {
            cout <<  line +" is nice!" << endl;
            nice++;
        }
        else
        {
            cout <<  line + " is naughty!" << endl;
        }
    }
    cout << nice << endl;
    return 0;
}



