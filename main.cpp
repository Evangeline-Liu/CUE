#include <iostream>
#include <vector>
#include "Maps.h"
#include "BFS.h"
using namespace std;


int main() {
  //test stuff
   /* std::pair<int, int> start(0, 0);
    std::pair<int, int> end(4, 9);
    int x  = BFS(GetMaps(3), start, end);
    std::cout<< x << std::endl;
*/
    std::cout<<"Welcome to CUE, the golf map shortest path algorithm"<<std::endl;
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
    int MapSelection;
    std::cin >> MapSelection;
    std::cout<<std::endl;
    std::cout<<"Select Algorithm, 1 for BFS and 2 for Dijkstra"<<std::endl;
    int Algorithm;
    std::cin>>Algorithm;
    if (Algorithm == 1){
        std::pair<int, int> start(0, 0);
        std::pair<int, int> end(4, 9);
        int x  = BFS(GetMaps(MapSelection), start, end);
        std::cout<<"Completed in " <<x << " Moves"<<std::endl;
    }
    if (Algorithm == 2){
      graph temp = graph(MapSelection);
      temp.Mapping_Out();
      list<coords> answer = temp.Shortest_Path();
      cout<<"Completed in " << answer.size()-1-temp.counter << " Moves"<<std::endl;
      
      /*
      cout << "Specific Shots Taken:" << endl;
      for (auto it = answer.begin(); it != answer.end(); ++it) {
          cout << it->first << ", " << it->second << endl;
      }
      */

    return 0;
    }
}
