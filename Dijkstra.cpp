#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <utility>
#include <math.h>
#include <list>

using namespace std;

// things to remember
typedef pair<int,int> coords;
pair<coords,float>* coords_distance;


class graph{

public:

    // to coord, to from coord, distance
    map<coords,pair<coords,float>> least_dist;

    // queue of things to travel and do
    queue<pair<coords,float>> temp;

    // string of the actual map
    std::vector<std::string> map_board;

    // starting position and ending position
    coords start;
    coords end;

    // for the end
    int counter = 0;

    // declaration
    graph(std::vector<std::string> map_board){
        this->map_board = map_board;
        for(int i = 0; i < map_board.size(); i++){
            for(int j = 0; j < map_board[0].size(); j++){

                //  when reading strings it is backwards y,x way
                if(map_board[i][j] == 'e'){
                    end = make_pair(j,i);
                }
                if(map_board[i][j] == 's'){
                    start = make_pair(j,i);
                }

            }
        }
    }

    bool check_straights(coords &to, coords &from){
        // all this done to check which one is greater so I can travel to it
        int x_to = to.first;
        int y_to = to.second;

        int x_from = from.first;
        int y_from = from.second;

        int x_temp = 0;
        int x_temp_end = 0;

        if( x_to > x_from){
            x_temp = x_from;
            x_temp_end = x_to;
        }else{
            x_temp = x_to;
            x_temp_end = x_from;
        }

        int y_temp = 0;
        int y_temp_end = 0;
        if( y_to > y_from){
            y_temp = y_from;
            y_temp_end = y_to;
        }else{
            y_temp = y_to;
            y_temp_end = y_from;
        }
        // in case its y or x changing its different
        if(x_temp_end == x_temp){
            for(int i = y_temp; i <= y_temp_end; i++){
                if(!(map_board[i][x_temp] == '.' || map_board[i][x_temp] == 'e'|| map_board[i][x_temp] == 's'|| map_board[i][x_temp] == '>'|| map_board[i][x_temp] == '<')){
                    return false;
                }
                // stuff for uphill and downhill
                if(map_board[i][x_temp] == '>'){
                    x_temp_end++;
                }
                if(map_board[i][x_temp] == '<'){
                    x_temp_end--;
                }
            }
        }else{
            for(int i = x_temp; i <= x_temp_end; i++){
                if(!(map_board[y_temp][i] == '.' || map_board[y_temp][i] == 'e'|| map_board[y_temp][i] == 's'|| map_board[y_temp][i] == '>'|| map_board[y_temp][i] == '<')){
                    return false;
                }
                // stuff for up hill and down hill
                if(map_board[y_temp][i] == '>'){
                    y_temp_end++;
                }
                if(map_board[y_temp][i] == '<'){
                    y_temp_end--;
                }
            }
        }



        return true;
    }

    bool check_diagonals(coords to, coords from){
        // similar to straights
        int x_to = to.first;
        int y_to = to.second;

        int x_from = from.first;
        int y_from = from.second;

        int x_temp = 0;
        int x_temp_end = 0;
        if( x_to > x_from){
            x_temp = x_from;
            x_temp_end = x_to;
        }else{
            x_temp = x_to;
            x_temp_end = x_from;
        }

        int y_temp = 0;
        int y_temp_end = 0;
        if( y_to > y_from){
            y_temp = y_from;
            y_temp_end = y_to;
        }else{
            y_temp = y_to;
            y_temp_end = y_from;
        }
        // specifically for the 2,2 since its a special case for checking points
        if(abs(x_to - x_from) == 2 && abs(y_to - y_from == 2)){
            // check diagonal if not empty return false
            vector<int> x_list = {0,2,2,1,1,1};
            vector<int> y_list = {1,2,1,1,2,0};
            for(int x = 0; x < 6; x++){
                // we don't take diagonals for uphill or downhill
                if(map_board[y_temp + y_list[x]][x_temp + x_list[x]] != '.' || map_board[y_temp + y_list[x]][x_temp + x_list[x]] != 'e'){
                    return false;
                }

            }

        }else{
            // if not a 2,2
            for(int i = x_temp; i <= x_temp_end; i++){
                for(int j = y_temp; j <= y_temp_end; j++){

                    // check if i,j coord is empty, if not return false
                    if(!(map_board[j][i] == '.' || map_board[j][i] == 'e' || map_board[j][i] == 's')){
                        return false;
                    }

                }
            }

        }
        return true;
    }

    void Mapping_Out(){
        // creates and runs the algorithm
        // array list algorithm type
        least_dist[make_pair(0,0)] = make_pair(make_pair(0,0),0);
        temp.push(make_pair(make_pair(start.first,start.second),0));

        // while possible moves
        while(!temp.empty()){
            pair<coords,float> temp_point = temp.front();
            float distance = temp.front().second;
            temp.pop();

            int x = temp_point.first.first;
            int y = temp_point.first.second;
            coords from = make_pair(x,y);
            // of all possible moves 25
            vector<int> dx = {3, 2, 2, 2, 1, 1, 1, 0, 0, 0, -3, -2, -2, -2, -1, -1, -1, 0, 0, 0, -2, 2, -1, 1, -2, 2, -1, 1};
            vector<int> dy = {0, 2, 1, 0, 2, 1, 0, 3, 2, 1, 0, -2, -1, 0, -2, -1, 0, -3, -2, -1, 2, -2, 2, -2, 1, -1, 1, -1};

            for(int i = 0; i < 25; i++){
                int nx = x + dx[i];
                int ny = y + dy[i];
                coords to = make_pair(nx,ny);

                // check if in graph
                if(!(ny < map_board.size() && nx < map_board[0].size() && nx >= 0 && ny >= 0)){
                    continue;
                }

                // check if open
                if(!(map_board[ny][nx] == 'e' || map_board[ny][nx] == 's' || map_board[ny][nx] == '.' || map_board[ny][nx] == '>' || map_board[ny][nx] == '<')){
                    continue;
                }

                // check if possible diagonal
                if( nx-x != 0 && ny-y != 0){
                    if(!check_diagonals(to,from)){
                        continue;
                    }
                }


                // check normal spaces
                // should change and fix so they can find if it exists
                if(!check_straights(to,from)){
                    continue;
                }

                // have to check again since it moved
                if(!(map_board[ny][nx] == 'e' || map_board[ny][nx] == 's' || map_board[ny][nx] == '.' || map_board[ny][nx] == '>' || map_board[ny][nx] == '<')){
                    continue;
                }


                // if it ends on a > or <
                coords compare = to;
                if(map_board[ny][nx] == '>'){
                    while (map_board[compare.second][compare.first] == '>'){
                        compare.first += 1;
                    }

                }
                if(map_board[ny][nx] == '<'){
                    while (map_board[compare.second][compare.first] == '<'){
                        compare.first -= 1;
                    }

                }

                float dist_calc = sqrt(pow(dx[i],2)+pow(dy[i],2))+distance;

                // what if least_dist doesn't exist?
                if (least_dist.find(to) == least_dist.end() && least_dist.find(compare) == least_dist.end()){
                    least_dist[to] = make_pair(from, dist_calc);
                    if(map_board[ny][nx] == '>' || map_board[ny][nx] == '<') {

                        least_dist[compare] = make_pair(to, dist_calc);
                        if(map_board[compare.second][compare.first] != 'e'){
                            temp.push(make_pair(compare, dist_calc));
                        }

                    }else{
                        if(map_board[ny][nx] != 'e'){
                            temp.push(make_pair(to, dist_calc));
                        }

                    }

                }else{
                    // at least one of them has to be greater than the prexisting
                    if (least_dist[to].second > dist_calc || least_dist[compare].second > dist_calc ) {

                        least_dist[to] = make_pair(from, dist_calc);
                        if(map_board[ny][nx] == '>' || map_board[ny][nx] == '<') {

                                if(least_dist[compare].second > dist_calc) {

                                    least_dist[compare] = make_pair(to, dist_calc);
                                    if (map_board[compare.second][compare.first] != 'e') {
                                        temp.push(make_pair(compare, dist_calc));
                                    }
                                }

                        }else{
                            // if end no need to run it in the algorithm
                            if(map_board[ny][nx] != 'e'){
                                temp.push(make_pair(to, dist_calc));
                            }
                        }
                    }
                }

            }

        }

    }

    list<coords> Shortest_Path(){

        list<coords> returne;
        returne.push_back(end);
        float temper = least_dist[end].second;

        coords temp_coord = least_dist[end].first;
        returne.push_back(temp_coord);
        temper = least_dist[temp_coord].second;
        if(map_board[temp_coord.second][temp_coord.first] == '>' || map_board[temp_coord.second][temp_coord.first] == '<'){
            counter++;
        }
        while(temper != 0){

            temp_coord = least_dist[temp_coord].first;
            returne.push_back(temp_coord);
            if(map_board[temp_coord.second][temp_coord.first] == '>' || map_board[temp_coord.second][temp_coord.first] == '<'){
                counter++;
                counter++;
            }
            temper = least_dist[temp_coord].second;

        }

        returne.reverse();

        return returne;
    }

    // print out map with shots on it
    void Print_Map(){
        list<coords> answer = this->Shortest_Path();
        for (auto it = answer.begin(); it != answer.end(); ++it) {
            if(map_board[it->second][it->first] != '>' && map_board[it->second][it->first] != '<'){
                map_board[it->second][it->first] = 'o';
            }
        }

        for(int j = 0; j < map_board.size(); j++) {
            for (int i = 0; i < map_board[0].size(); i++) {

                    cout << map_board[j][i] << " ";


            }
            cout << endl;
        }
    }


};


/*
int main() {
    // test maps
    std::vector<std::string> Map1 = {
            "s.#.e",
            "..#..",
            "..#..",
            "..#..",
            "....."
    };
    std::vector<std::string> Map2 = {
            "s.#..",
            "..#..",
            "#....",
            "#..#.",
            "...#e"
    };
    std::vector<std::string> Map3 = {
            "s...#..#..",
            "...#......",
            "..#..#..#.",
            ".#..#....#",
            "...#..#..e"
    };

    std::vector<std::string> Map4 = {
            "s>>>>>>e"
    };


    // everything to run it
    graph temp = graph(Map4);
    temp.Mapping_Out();

    list<coords> answer = temp.Shortest_Path();
    cout << "Number of Shots: " << answer.size()-1-temp.counter << endl;
    cout << "Shots Taken:" << endl;
    for (auto it = answer.begin(); it != answer.end(); ++it) {
        cout << it->first << ", " << it->second << endl;
    }
    temp.Print_Map();

    return 0;
}
*/

