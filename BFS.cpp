#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include "algorithm"
using namespace std;

// function to see if valid position
bool isValid(int x, int y, int rows, int cols, std::vector<std::string> map, int dx, int dy)
{
    if (x < 0 || x >= rows || y < 0 || y >= cols) {
        return false;
    }
    if (map[x][y] == '#') {
        return false;
    }
    int steps = max(abs(dx) , abs(dy));
    for (int step = 1; step < steps; ++step) {
        int newX = x - (dx / steps) * step;
        int newY = y - (dy / steps) * step;
        if (map[newX][newY] == '#')
            return false;
    }
    return true;
}

int BFS(vector<string> grid, pair<int, int> start, pair<int, int> finish) {
    int numRows = grid.size();
    int numCols = grid[0].size();

    vector<vector<bool>> visited(numRows, vector<bool>(numCols, false));
    vector<vector<pair<int, int>>> parent(numRows, vector<pair<int, int>>(numCols, {-1, -1}));

    queue<pair<int, int>> q;
    q.push(start);
    visited[start.first][start.second] = true;

    int dx[] = {-3, -2, -1, 1, 2, 3, 0, 0, 0, 0 ,0 ,0};
    int dy[] = {0, 0, 0, 0, 0, 0, -3, -2, -1, 1 ,2 ,3};

    while (!q.empty()) {
        pair<int, int> curr = q.front();
        q.pop();
        if (curr == finish) {
            vector<pair<int, int>> shortestPath;
            pair<int, int> cell = finish;
            while (cell != start) {
                shortestPath.push_back(cell);
                cell = parent[cell.first][cell.second];
            }
            shortestPath.push_back(start);
            for (int i = 0; i < numRows; ++i) {
                for (int j = 0; j < numCols; ++j) {
                    if (find(shortestPath.begin(), shortestPath.end(), make_pair(i, j)) != shortestPath.end()) {
                        cout << "o ";
                    } else {
                        cout << grid[i][j] << " ";
                    }
                }
                cout << endl;
            }
            return shortestPath.size() - 1;
        }
        for (int i = 0; i < 12; ++i) {
            int newRow = curr.first + dx[i];
            int newCol = curr.second + dy[i];

            if (isValid(newRow, newCol, numRows, numCols, grid, dx[i] ,dy[i]) && !visited[newRow][newCol]) {
                q.push({newRow, newCol});
                visited[newRow][newCol] = true;
                parent[newRow][newCol] = curr;
            }
        }
    }
    return -1;
}


