#ifndef BFS_H
#define BFS_H

#include <vector>
#include <string>
#include <queue>
#include <utility>
#include "Maps.h"
#include "iostream"
// Declare the BFS function
int BFS(std::vector<std::string> grid, std::pair<int, int> start, std::pair<int, int> finish);
bool isValid(int x, int y, int rows, int cols, std::vector<std::string> map, int& hills);
#endif // BFS_H
