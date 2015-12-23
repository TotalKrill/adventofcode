
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool lights[1000][1000];
int  ledlights[1000][1000];

void toggle(int startx, int starty, int stopx, int stopy)
{
    for(int i = startx; i <= stopx; i++){
        for (int j = starty; j <= stopy; j++){
            if(lights[i][j])
                lights[i][j] = false;
            else
                lights[i][j] = true;
        }
    }

}

void setlights(int startx, int starty, int stopx, int stopy, bool onoff)
{
    for(int i = startx; i <= stopx; i++){
        for (int j = starty; j <= stopy; j++){
            lights[i][j] = onoff;
        }
    }
}

typedef struct{
    int startx, starty, stopx, stopy;
} positions;

void change_level(positions pos, int levelchange){
    for(int i = pos.startx; i <= pos.stopx; i++){
        for (int j = pos.starty; j <= pos.stopy; j++){
            ledlights[i][j] = ledlights[i][j] + levelchange;
            //cout << ledlights[i][j] << endl;
            if(ledlights[i][j] < 0)
                ledlights[i][j] = 0;
        }
    }
}


positions get_positions(string input, string searchstr){

            size_t pos;
            size_t throughpos;

            string startstr;
            string stopstr;

            positions retpos = {0,0,0,0};

            static const string throughstr = " through ";

            pos = input.find(searchstr);
            if(pos != string::npos){
                throughpos = input.find(throughstr);
                startstr = input.substr(pos+searchstr.length(), throughpos-pos-searchstr.length());
                stopstr = input.substr(throughpos+throughstr.length());
                pos = startstr.find(",");
                size_t stoppos = stopstr.find(",");
/*
                cout << input << endl;
                cout << "start: " +startstr << endl;
                cout << "stop: " +stopstr << endl;


                cout << searchstr << endl;
                cout << "startx: " + startstr.substr(0, pos) + "\n"<< endl;
                cout << "starty: " + startstr.substr(pos+1) + "\n"<< endl;
                cout << "stopx: " + stopstr.substr(0, stoppos) + "\n"<< endl;
                cout << "stopy: " + stopstr.substr(stoppos+1) + "\n"<< endl;
*/

                retpos.startx = stoi(startstr.substr(0, pos));
                retpos.starty = stoi(startstr.substr(pos+1));
                retpos.stopx = stoi(stopstr.substr(0, stoppos));
                retpos.stopy = stoi(stopstr.substr(stoppos+1));
            }

            return retpos;
}

int main()
{
    ifstream in("input6");
    //ifstream in("test");
    string line;

    for(int i = 0; i < 1000; i++){
        for (int j = 0; j < 1000; j++){
            lights[i][j] = false;
            ledlights[i][j] = 0;
        }
    }

    while(getline(in, line))
    {
        static const string offstr = "off";
        static const string onstr = "on";
        static const string togglestr = "toggle";

        positions pos = {0,0,0,0};
        if(line.find(offstr) != string::npos){
            pos = get_positions(line,offstr);
            setlights(pos.startx, pos.starty, pos.stopx, pos.stopy, false);
            change_level(pos, -1);
        }
        if(line.find(onstr) != string::npos){
            pos = get_positions(line,onstr);
            setlights(pos.startx, pos.starty, pos.stopx, pos.stopy, true);
            change_level(pos,1);
        }
        if(line.find(togglestr) != string::npos){
            pos = get_positions(line,togglestr);
            toggle(pos.startx, pos.starty, pos.stopx, pos.stopy);
            change_level(pos,2);
        }

    }

    int lightson = 0;
    int brightness = 0;

    for(int i = 0; i <= 999; i++){
        for (int j = 0; j <= 999; j++){
            if(lights[i][j]){
                lightson++;
            }
            brightness += ledlights[i][j];
        }
    }


        cout << lightson << " lights is on" << endl;
        cout << brightness << " is the total brightness" << endl;
}
