#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

// function to see if valid position
bool isValid(int x, int y, int rows, int cols, std::vector<std::string> map)
{
    return (x >= 0 && x < rows && y >= 0 && y < cols && map[x][y] != '#');
}

int BFS(vector<string> grid, pair<int, int> start, pair<int, int> finish) {
    int numRows = grid.size();
    int numCols = grid[0].size();

    vector<vector<bool>> visited(numRows, vector<bool>(numCols, false));
    queue<pair<pair<int, int>, int>> q;
    q.push({start, 0});
    visited[start.first][start.second] = true;

    int dx[] = {-3, -2, -1, 1, 2, 3, 0, 0, 0, 0 ,0 ,0};
    int dy[] = {0, 0, 0, 0, 0, 0, -3, -2, -1, 1 ,2 ,3};

    while (!q.empty()) {
        pair<pair<int, int>, int> curr = q.front();
        q.pop();

        if (curr.first == finish) {
            //return {curr.second , visited};
            //return curr.second;
            

            return curr.second;
        }

        for (int i = 0; i < 12; ++i) {
            int newRow = curr.first.first + dx[i];
            int newCol = curr.first.second + dy[i];

            if (isValid(newRow, newCol, numRows, numCols, grid) && !visited[newRow][newCol]) {
                q.push({{newRow, newCol}, curr.second + 1});
                visited[newRow][newCol] = true;
            }
        }
    }
    //return {-1 , visited};
    return -1;
}

