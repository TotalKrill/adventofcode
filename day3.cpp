/**
 * @file day1.cpp
 * @brief  AdventofCode 1
 * @author Kristoffer Ödmark
 * @version 0.1
 * @date 2015-12-05
 */

#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char *args[]){

    int count = 0;

    string str;
    ifstream in("input3");
    getline(in, str);

    int maxsize = str.length();
    cout << "Size of array is: " << 2*maxsize << "x" << 2*maxsize << endl;
    int size = 1024;
    int houses[size][size];
    for(int hx=0; hx < size; hx++)
    {
        for(int hy =0; hy < size; hy++)
        {
            houses[hx][hy] = 0;
        }
    }

    int x = 512;
    int y = 512;
    int roboy = 512;
    int robox = 512;


    houses[512][512] = 2;
    count=1; // first house gets present

    string teststr ="^>v<";
    int i=0;
    for (char& c : str)
    {

        if (i%2==0)
        {
            switch(c)
            {
                case '<':
                    x--;
                    break;
                case '>':
                    x++;
                    break;
                case '^':
                    y++;
                    break;
                case 'v':
                    y--;
                    break;
                default:
                    break;
            }
            houses[x][y] = houses[x][y] + 1;

            if(houses[x][y] == 1)
                count++;

        }
        else
        {
            switch(c)
            {
                case '<':
                    robox--;
                    break;
                case '>':
                    robox++;
                    break;
                case '^':
                    roboy++;
                    break;
                case 'v':
                    roboy--;
                    break;
                default:
                    break;

            }
            houses[robox][roboy] = houses[robox][roboy] +1;
            if(houses[robox][roboy] == 1)
                count++;
        }
        i++;
        printf("santa: %i,%i there is %i presents there\n", x, y, houses[x][y]);
        printf("robot: %i,%i there is %i presents there\n", robox, roboy, houses[robox][roboy]);
    }

    cout << count << endl;
    return 0;
}
