#include <iostream>
#include <vector>
#include "Maps.cpp"
#include "BFS.h"
#include "Dijkstra.cpp"
#include <chrono>
using Clock = std::chrono::steady_clock;
using std::chrono::nanoseconds;
using std::chrono::time_point;
using std::chrono::duration_cast;
using namespace std;


int main() {
  //test stuff
   /* std::pair<int, int> start(0, 0);
    std::pair<int, int> end(4, 9);
    int x  = BFS(GetMaps(3), start, end);
    std::cout<< x << std::endl;
    */


    float end_time = 0;
    std::cout<<"Welcome to CUE, here we help calculate your best shot for a game of golf."<<std::endl;
    std::cout<<"By Evangeline Liu and Cooper Engebretson" <<std::endl;
    std::cout<<std::endl;
    std::cout<<"Select map!(Enter a number)"<<std::endl;
    std::cout<<std::endl;
    std::cout<<"Map 1:"<<std::endl;
    for (const auto& row : GetMaps(1)) {
        for (char c : row) {
            std::cout << c << " ";
        }
        std::cout << std::endl;
    }
    std::cout<<std::endl;
    std::cout<<"Map 2:"<<std::endl;
    for (const auto& row : GetMaps(2)) {
        for (char c : row) {
            std::cout << c << " ";
        }
        std::cout << std::endl;
    }
    std::cout<<std::endl;
    std::cout<<"Map 3:"<<std::endl;
    for (const auto& row : GetMaps(3)) {
        for (char c : row) {
            std::cout << c << " ";
        }
        std::cout << std::endl;
    }
  
    std::cout<<std::endl;
    std::cout<<"Map 4:"<<std::endl;
    for (const auto& row : GetMaps(4)) {
        for (char c : row) {
            std::cout << c << " ";
        }
        std::cout << std::endl;
    }
    std::cout<<std::endl;
    std::cout<<"Map 5:"<<std::endl;
    for (const auto& row : GetMaps(5)) {
        for (char c : row) {
            std::cout << c << " ";
        }
        std::cout << std::endl;
    }
    std::cout<<std::endl;
    std::cout<<"Map 6:"<<std::endl;
    for (const auto& row : GetMaps(6)) {
        for (char c : row) {
            std::cout << c << " ";
        }
        std::cout << std::endl;
    }
    std::cout<<std::endl;
    std::cout<<"Map 7:"<<std::endl;
    for (const auto& row : GetMaps(7)) {
        for (char c : row) {
            std::cout << c << " ";
        }
        std::cout << std::endl;
    }
    int MapSelection;
    std::cin >> MapSelection;
    std::cout<<std::endl;
    std::cout<<"Select Algorithm, 1 for BFS and 2 for Dijkstra"<<std::endl;
    int Algorithm;
    std::cin>>Algorithm;
    time_point<Clock> start = Clock::now();
    if (Algorithm == 1){
        if (MapSelection == 1){
            std::pair<int, int> start(0, 0);
            std::pair<int, int> end(4, 4);
            int x  = BFS(GetMaps(MapSelection), start, end);
            std::cout<<"Completed in " <<x << " Moves"<<std::endl;
        }
        if (MapSelection == 2){
            std::pair<int, int> start(0, 0);
            std::pair<int, int> end(4, 4);
            int x  = BFS(GetMaps(MapSelection), start, end);
            std::cout<<"Completed in " <<x << " Moves"<<std::endl;
        }
        if (MapSelection == 3){
            std::pair<int, int> start(0, 0);
            std::pair<int, int> end(4, 9);
            int x  = BFS(GetMaps(MapSelection), start, end);
            std::cout<<"Completed in " <<x << " Moves"<<std::endl;
        }
        if (MapSelection == 4){
            std::pair<int, int> start(0, 0);
            std::pair<int, int> end(4, 9);
            int x  = BFS(GetMaps(MapSelection), start, end);
            std::cout<<"Completed in " <<x << " Moves"<<std::endl;
        }
        if (MapSelection == 5){
            std::pair<int, int> start(0, 0);
            std::pair<int, int> end(0, 5);
            int x  = BFS(GetMaps(MapSelection), start, end);
            std::cout<<"Completed in " <<x << " Moves"<<std::endl;
        }
        if (MapSelection == 6){
            std::pair<int, int> start(0, 0);
            std::pair<int, int> end(4, 9);
            int x  = BFS(GetMaps(MapSelection), start, end);
            std::cout<<"Completed in " <<x << " Moves"<<std::endl;
        }
        if (MapSelection == 7){
            std::pair<int, int> start(0, 0);
            std::pair<int, int> end(4, 9);
            int x  = BFS(GetMaps(MapSelection), start, end);
            if (x == -1){
                std::cout<<"There is no path"<<std::endl;
            }
            else {
                std::cout << "Completed in " << x << " Moves" << std::endl;
            }
        }

    }
    if (Algorithm == 2){
      graph temp = graph(GetMaps(MapSelection));
      temp.Mapping_Out();
      // distance travelled in outputed in the dijkstra.cpp
      list<coords> answer = temp.Shortest_Path();
      temp.Print_Map();
      answer.pop_back();
      if(temp.start == answer.back()){
          cout << "There is no possible solution" << endl;
      }else{
      answer.push_back(temp.end);
      cout<<"Completed in " << answer.size()-1-temp.counter << " Moves"<<std::endl;
      float temper = temp.least_dist[temp.end].second;
      cout<<"Distance Travelled: " << temper << " Moves"<<std::endl;
      // this is for the specific shots given and after rolling down or up hill included
      for (auto it = answer.begin(); it != answer.end(); ++it) {
        cout << it->first << ", " << it->second << " ";
        if(temp.map_board[it->second][it->first] == '>' || temp.map_board[it->second][it->first] == '<'){
            ++it;
            cout << "rolls to " << it->first << ", " << it->second << endl;
        }else{
            cout << endl;
        }

      }
      }
        
    
    }
    time_point<Clock> end = Clock::now();
    nanoseconds diff = duration_cast<nanoseconds>(end - start);
    end_time = diff.count();
    cout << "Execution Time: " << end_time/100000 << " ms"<< endl;
    return 0;
}
