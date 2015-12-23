/**
 * @file day4.cpp
 * @brief  A
 * @author Kristoffer Ödmark
 * @version 0.1
 * @date 2015-12-05
 */
#include <iostream>
#include <string>

#include "md5.h"
using namespace std;

bool checkhash(string h)
{
//    cout << h << endl;
    if(h.substr(0,6).compare("000000") == 0)
        return true;
    return false;
}

int main(int argc, char *argv[])
{
    string input = "ckczppom";
    int i=0;
    string teststring = input;
    while(!checkhash(md5(teststring)))
    {
        i++;
        teststring = input + to_string(i);
        //cout << teststring + " --> ";
    }

    printf("Found hash after %i iterations\n", i);

    return 0;
}
