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

    pair<pair<int,int>,bool> count_hilly(coords to, coords from){

        pair<pair<int,int>,bool> returnie = make_pair(make_pair(0,0),true);
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

        if(x_temp_end == x_temp){
            for(int i = y_temp; i <= y_temp_end; i++){
                if(map_board[i][x_temp] == '#' ){
                    returnie.second = false;
                }

                if(map_board[i][x_temp] == '>' ){
                    returnie.first.first += 1;
                }
                if(map_board[i][x_temp] == '<' ){
                    returnie.first.first -= 1;
                }
            }
        }else{
            for(int i = x_temp; i <= x_temp_end; i++){
                if(map_board[i][x_temp] == '#' ){
                    returnie.second = false;
                }
                if(map_board[y_temp][i] == '>'){
                    returnie.first.first += 1;
                }
                if(map_board[y_temp][i] == '<'){
                    returnie.first.first -= 1;
                }
            }
        }

        return returnie;
    }

    bool check_straights(coords to, coords from){
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

        if(x_temp_end == x_temp){
            for(int i = y_temp; i <= y_temp_end; i++){
                if(!(map_board[i][x_temp] == '.' || map_board[i][x_temp] == 'e'|| map_board[i][x_temp] == 's')){
                    return false;
                }
            }
        }else{
            for(int i = x_temp; i <= x_temp_end; i++){
                if(!(map_board[y_temp][i] == '.' || map_board[y_temp][i] == 'e'|| map_board[y_temp][i] == 's')){
                    return false;
                }
            }
        }



        return true;
    }

    bool check_diagonals(coords to, coords from){
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

        if(abs(x_to - x_from) == 2 && abs(y_to - y_from == 2)){
            // check diagonal if not empty return false
            vector<int> x_list = {0,2,2,1,1,1};
            vector<int> y_list = {1,2,1,1,2,0};
            for(int x = 0; x < 6; x++){

                if(map_board[y_temp + y_list[x]][x_temp + x_list[x]] != '.' || map_board[y_temp + y_list[x]][x_temp + x_list[x]] != 'e'){
                    return false;
                }

            }

        }else{


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

        least_dist[make_pair(0,0)] = make_pair(make_pair(0,0),0);
        temp.push(make_pair(make_pair(start.first,start.second),0));

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
                if(!(map_board[ny][nx] == 'e' || map_board[ny][nx] == 's' || map_board[ny][nx] == '.')){
                    // check if >> or  << uphill or downhill
                    // run separate code

                    if(map_board[ny][nx] == '>'){
                        float dist_calc = sqrt(pow(dx[i],2)+pow(dy[i],2))+distance;
                        if (least_dist.find(to) == least_dist.end()){
                            least_dist[to] = make_pair(from, dist_calc);
                            to.first = to.first+1;
                            temp.push(make_pair(to, dist_calc));
                        }else {
                            if (least_dist[to].second > dist_calc) {
                                least_dist[to] = make_pair(from, dist_calc);
                                to.first = to.first+1;
                                temp.push(make_pair(to, dist_calc));
                            }
                        }
                    }
                    if(map_board[ny][nx] == '<'){
                        float dist_calc = sqrt(pow(dx[i],2)+pow(dy[i],2))+distance;
                        if (least_dist.find(to) == least_dist.end()){
                            least_dist[to] = make_pair(from, dist_calc);
                            to.first = to.first-1;
                            temp.push(make_pair(to, dist_calc));
                        }else {
                            if (least_dist[to].second > dist_calc) {
                                least_dist[to] = make_pair(from, dist_calc);
                                to.first = to.first-1;
                                temp.push(make_pair(to, dist_calc));
                            }
                        }
                    }
                    // just skipie always
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
                    // there are blocks and you should see if its >> or <<
                    pair<pair<int,int>,bool> holding = count_hilly(to,from);
                    if(holding.second){
                        float dist_calc = sqrt(pow(dx[i],2)+pow(dy[i],2))+distance;

                        // what if least_dist doesn't exist?
                        if (least_dist.find(to) == least_dist.end()){
                            least_dist[to] = make_pair(from, dist_calc);
                            to.first += holding.first.first;
                            to.second += holding.first.second;
                            temp.push(make_pair(to, dist_calc));
                        }else {
                            if (least_dist[to].second > dist_calc) {
                                least_dist[to] = make_pair(from, dist_calc);
                                to.first += holding.first.first;
                                to.second += holding.first.second;
                                temp.push(make_pair(to, dist_calc));
                            }
                        }
                    }
                    continue;
                }


                float dist_calc = sqrt(pow(dx[i],2)+pow(dy[i],2))+distance;

                // what if least_dist doesn't exist?
                if (least_dist.find(to) == least_dist.end()){
                    least_dist[to] = make_pair(from, dist_calc);
                    temp.push(make_pair(to, dist_calc));
                }else {
                    if (least_dist[to].second > dist_calc) {
                        least_dist[to] = make_pair(from, dist_calc);
                        temp.push(make_pair(to, dist_calc));
                    }
                }

            }

        }

    }

    list<coords> Shortest_Path(){

        list<coords> returne;
        returne.push_back(end);
        float temper = least_dist[end].second;
        cout << "Distance Traveled: "<<temper << endl;

        coords temp_coord = least_dist[end].first;
        returne.push_back(temp_coord);
        temper = least_dist[temp_coord].second;

        while(temper != 0){

            temp_coord = least_dist[temp_coord].first;
            returne.push_back(temp_coord);
            temper = least_dist[temp_coord].second;

        }

        returne.reverse();
        return returne;
    }


};




int main() {

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

    graph temp = graph(Map3);
    temp.Mapping_Out();

    list<coords> answer = temp.Shortest_Path();
    cout << "Number of Shots: " << answer.size()-1 << endl;
    cout << "Shots Taken:" << endl;
    for (auto it = answer.begin(); it != answer.end(); ++it) {
        cout << it->first << ", " << it->second << endl;
    }

    return 0;
}
