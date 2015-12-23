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

class Dist{
    public:
        string from;
        string to;
        int dist;
        Dist(string loc1, string loc2, int dist){
            this->from =  loc1;
            this->to = loc2;
            this->dist = dist;
        }
};

class Route{
    public:
        vector<string> stops;
        Route(string start){
            stops.push_back(start);
            total_length = 0;
        }
        void add_stop(string loc)
        {
            stops.push_back(loc);
        }
        void print_route(){
            for(size_t i = 0; i < stops.size(); i++)
            {
                cout << stops[i];
                if(i < stops.size()-1)
                    cout << " -> ";
                else
                    cout << endl;
            }

        }

        bool visits_all(vector<string> &locs){
            if(stops.size() == locs.size())
                return true;
            return false;
        }

        bool stop_exists(string stop){
            // check if stop already is in route
            for(size_t i = 0; i < stops.size(); i++)
            {
                if(stops[i] == stop)
                    return true;
            }
            return false;
        }

        int length(){
            return total_length;
        }
        void add_length(int len){
            total_length += len;
        }

        private:
            int total_length;
};

vector<Route> branch(Route route, vector<Dist> &dists, vector<string> &locs)
{
    vector<Route> branches;
    for( size_t i = 0; i < dists.size(); i++){
        if(route.stops.back() == dists[i].from && !route.stop_exists(dists[i].to))
        {
            branches.push_back(route);
        }
    }
    return branches;
}

int get_distance(vector<Dist> &dists, string to, string from){
    for( size_t i = 0; i < dists.size(); i++){
        if(from == dists[i].to && to  == dists[i].from)
            return dists[i].dist;
     }
    // return -1 to tell that no distance exists
    return -1;
}
int main()
{
    ifstream in("test");
    string line;
    vector<Dist> distances;
    vector<string> locations;
    vector<Route> routes;

    while(getline(in, line))
    {
        vector<string> vec = split(line, " ");
        for (int i : {0,2}){
            bool exists = false;

            for (size_t j =0; j < locations.size(); j++){
                if(locations[j] == vec[i])
                {
                    exists = true;
                }
            }
            if(!exists)
            {
                cout << "Added " + vec[i] + " as start location" << endl;
                locations.push_back(vec[i]);
            }
        }
        // have all distances and locations
        // can go both directions
        distances.push_back(Dist(vec[0],vec[2], stoi(vec.back())));
        distances.push_back(Dist(vec[2],vec[0], stoi(vec.back())));
    }

    // generate a start in each location
    for(size_t i =0; i< locations.size(); i++) {
        routes.push_back(Route(locations[i]));
    }
    for(size_t i =0; i< routes.size(); i++) {

        bool extra_route = false;
        for( size_t j = 0; j < distances.size(); j++){

            if(routes[i].stops.back() == distances[j].from &&
                    !routes[i].stop_exists(distances[j].to))
            {
                extra_route = true;
                //cout << distances[j].to << " does no exist on route:" << endl;
                routes.push_back(routes[i]);
                routes.back().add_stop(distances[j].to);
                routes.back().add_length(distances[j].dist);

            }
        }
    }
    cout << "routes:" << endl;
    for(size_t i =0; i< routes.size(); i++) {
        routes[i].print_route();
    }
}
