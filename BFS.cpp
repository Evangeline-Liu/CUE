

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <valarray>
#include "algorithm"
using namespace std;

// function to see if valid position
bool isValid(int x, int y, int rows, int cols, std::vector<std::string> map, int dx, int dy, int& hills)
{
    if (x < 0 || x >= rows || y < 0 || y >= cols) {
        return false;
    }
    if (map[x][y] == '#') {
        return false;
    }
    //if not diagonal
    if (dx == 0 || dy == 0) {
        int steps = max(abs(dx), abs(dy));
        for (int step = 1; step < steps; ++step) {
            int newX = x - (dx / steps) * step;
            int newY = y - (dy / steps) * step;
            if (map[newX][newY] == '#') {
                return false;
            }
            if (map[newX][newY] == '<'){
                hills -=1;

            }
            if (map[newX][newY] == '>'){
                hills +=1;
            }

        }

    }
    //diagonal
    if (abs(dx)>0 && abs(dy)>0){
        //1x1
        if (dx ==1 && dy == 1) { // Moving down-right
            if (map[x][y-1] == '#' || map[x-1][y] == '#') {
                return false;
            }
            if (map[x][y-1] == '<' || map[x-1][y] == '<') {
                return false;
            }
            if (map[x][y-1] == '>' || map[x-1][y] == '>') {
                return false;
            }
        }
        else if (dx ==1 && dy == -1) { // Moving down-left
            if (map[x][y+1] == '#' || map[x-1][y] == '#') {
                return false;
            }
            if (map[x][y+1] == '<' || map[x-1][y] == '<') {
                return false;
            }if (map[x][y+1] == '>' || map[x-1][y] == '>') {
                return false;
            }

        }
        else if (dx == -1 && dy ==1) { // Moving up-right
            if (map[x][y-1] == '#' || map[x+1][y] == '#') {
                return false;
            }
            if (map[x][y-1] == '<' || map[x+1][y] == '<') {
                return false;
            }
            if (map[x][y-1] == '>' || map[x+1][y] == '>') {
                return false;
            }
        }
        else if (dx == -1 && dy== -1) { // Moving up-left
            if (map[x][y+1] == '#' || map[x+1][y] == '#') {
                return false;
            }
            if (map[x][y+1] == '<' || map[x+1][y] == '<') {
                return false;
            }
            if (map[x][y+1] == '>' || map[x+1][y] == '>') {
                return false;
            }

        }
        //2x1 moves
        else if (dx == 2 && dy == 1){
            if (map[x-1][y] == '#' || map[x][y-1] == '#' || map[x-1][y-1] == '#' ){
                return false;
            }
            if (map[x-1][y] == '<' || map[x][y-1] == '<' || map[x-1][y-1] == '<' ){
                return false;
            }
            if (map[x-1][y] == '>' || map[x][y-1] == '>' || map[x-1][y-1] == '>' ){
                return false;
            }

        }
        else if (dx == 2 && dy == -1) { // Moving down-left
            if (map[x - 1][y] == '#' || map[x][y + 1] == '#' || map[x - 1][y + 1] == '#') {
                return false;
            }
            if (map[x - 1][y] == '<' || map[x][y + 1] == '<' || map[x - 1][y + 1] == '<') {
                return false;
            }
            if (map[x - 1][y] == '>' || map[x][y + 1] == '>' || map[x - 1][y + 1] == '>') {
                return false;
            }
        }
        else if (dx == -2 && dy == 1) { // Moving up-right
            if (map[x + 1][y] == '#' || map[x][y - 1] == '#' || map[x + 1][y - 1] == '#') {
                return false;
            }
            if (map[x + 1][y] == '<' || map[x][y - 1] == '<' || map[x + 1][y - 1] == '<') {
                return false;
            }
            if (map[x + 1][y] == '>' || map[x][y - 1] == '>' || map[x + 1][y - 1] == '>') {
                return false;
            }
        }
        else if (dx == -2 && dy == -1) { // Moving up-left
            if (map[x + 1][y] == '#' || map[x][y + 1] == '#' || map[x + 1][y + 1] == '#') {
                return false;
            }
            if (map[x + 1][y] == '<' || map[x][y + 1] == '<' || map[x + 1][y + 1] == '<') {
                return false;
            }
            if (map[x + 1][y] == '>' || map[x][y + 1] == '>' || map[x + 1][y + 1] == '>') {
                return false;
            }
        }
        //1x2moves
        else if (dx == 1 && dy == 2){
            if (map[x][y-1] == '#' || map[x-1][y] == '#' || map[x-1][y-1] == '#'){
                return false;
            }
            if (map[x][y-1] == '<' || map[x-1][y] == '<' || map[x-1][y-1] == '<'){
                return false;
            }
            if (map[x][y-1] == '>' || map[x-1][y] == '>' || map[x-1][y-1] == '>'){
                return false;
            }
        }
        else if (dx == 1 && dy == -2) { // Moving down-left
            if (map[x][y - 1] == '#' || map[x - 1][y] == '#' || map[x - 1][y + 1] == '#') {
                return false;
            }
            if (map[x][y - 1] == '<' || map[x - 1][y] == '<' || map[x - 1][y + 1] == '<') {
                return false;
            }
            if (map[x][y - 1] == '>' || map[x - 1][y] == '>' || map[x - 1][y + 1] == '>') {
                return false;
            }
        }
        else if (dx == -1 && dy == 2) { // Moving up-right
            if (map[x][y + 1] == '#' || map[x + 1][y] == '#' || map[x + 1][y - 1] == '#') {
                return false;
            }
            if (map[x][y + 1] == '<' || map[x + 1][y] == '<' || map[x + 1][y - 1] == '<') {
                return false;
            }
            if (map[x][y + 1] == '>' || map[x + 1][y] == '>' || map[x + 1][y - 1] == '>') {
                return false;
            }
        }
        else if (dx == -1 && dy == -2) { // Moving up-left
            if (map[x][y + 1] == '#' || map[x + 1][y] == '#' || map[x + 1][y + 1] == '#') {
                return false;
            }
            if (map[x][y + 1] == '<' || map[x + 1][y] == '<' || map[x + 1][y + 1] == '<') {
                return false;
            }
            if (map[x][y + 1] == '>' || map[x + 1][y] == '>' || map[x + 1][y + 1] == '>') {
                return false;
            }
        }
        //2x2
        else if (dx == 2 && dy == 2){
            if (map[x][y-1] == '#' || map[x-1][y] == '#' ||map[x-1][y-1] == '#' || map[x-2][y-1]=='#' || map[x-1][y-2]=='#'){
                return false;
            }
            if (map[x][y-1] == '<' || map[x-1][y] == '<' ||map[x-1][y-1] == '<' || map[x-2][y-1]=='<' || map[x-1][y-2]=='<'){
                return false;
            }
            if (map[x][y-1] == '>' || map[x-1][y] == '>' ||map[x-1][y-1] == '>' || map[x-2][y-1]=='>' || map[x-1][y-2]=='>'){
                return false;
            }
        }
        else if (dx == 2 && dy == -2) { // Moving down-left
            if (map[x][y - 1] == '#' || map[x - 1][y] == '#' || map[x - 1][y + 1] == '#' || map[x - 2][y + 1] == '#' || map[x - 1][y + 2] == '#') {
                return false;
            }
            if (map[x][y - 1] == '<' || map[x - 1][y] == '<' || map[x - 1][y + 1] == '<' || map[x - 2][y + 1] == '<' || map[x - 1][y + 2] == '<') {
                return false;
            }
            if (map[x][y - 1] == '>' || map[x - 1][y] == '>' || map[x - 1][y + 1] == '>' || map[x - 2][y + 1] == '>' || map[x - 1][y + 2] == '>') {
                return false;
            }
        }
        else if (dx == -2 && dy == 2) { // Moving up-right
            if (map[x][y + 1] == '#' || map[x + 1][y] == '#' || map[x + 1][y - 1] == '#' || map[x + 2][y - 1] == '#' || map[x + 1][y - 2] == '#') {
                return false;
            }
            if (map[x][y + 1] == '<' || map[x + 1][y] == '<' || map[x + 1][y - 1] == '<' || map[x + 2][y - 1] == '<' || map[x + 1][y - 2] == '<') {
                return false;
            }
            if (map[x][y + 1] == '>' || map[x + 1][y] == '>' || map[x + 1][y - 1] == '>' || map[x + 2][y - 1] == '>' || map[x + 1][y - 2] == '>') {
                return false;
            }
        }
        else if (dx == -2 && dy == -2) { // Moving up-left
            if (map[x][y + 1] == '#' || map[x + 1][y] == '#' || map[x + 1][y + 1] == '#' || map[x + 2][y + 1] == '#' || map[x + 1][y + 2] == '#') {
                return false;
            }
            if (map[x][y + 1] == '<' || map[x + 1][y] == '<' || map[x + 1][y + 1] == '<' || map[x + 2][y + 1] == '<' || map[x + 1][y + 2] == '<') {
                return false;
            }
            if (map[x][y + 1] == '>' || map[x + 1][y] == '>' || map[x + 1][y + 1] == '>' || map[x + 2][y + 1] == '>' || map[x + 1][y + 2] == '>') {
                return false;
            }
        }
    }
    return true;
}

int BFS(vector<string> grid, pair<int, int> start, pair<int, int> finish) {
    int numRows = grid.size();
    int numCols = grid[0].size();

    vector<vector<bool>> visited(numRows, vector<bool>(numCols, false));
    vector<vector<pair<int, int>>> parent(numRows, vector<pair<int, int>>(numCols, {-1, -1}));
    vector<vector<float>> distance(numRows, vector<float>(numCols, 0));
    queue<pair<int, int>> q;
    q.push(start);
    visited[start.first][start.second] = true;
    int dx[] = {-3, -2, -1, 1, 2, 3, 0, 0, 0, 0 ,0 ,0,
                1, 1,2,2, 1, 1, 2, 2,-1,-1,-2,-2,
                -1,-1,-2,-2};
    int dy[] = {0, 0, 0, 0, 0, 0, -3, -2, -1, 1 ,2 ,3,
               1, 2,1,2, -1,-2,-1,-2,1,2,1,2,
               -1,-2,-1,-2};

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
                    if (find(shortestPath.begin(), shortestPath.end(), make_pair(i, j)) != shortestPath.end() &&grid[i][j]!='<') {
                        cout << "o ";
                    } else {
                        cout << grid[i][j] << " ";
                    }
                }
                cout << endl;
            }
            std::cout <<"Distance: " << distance[finish.first][finish.second] + 1<< std::endl;
            return shortestPath.size() - 1;
        }
        for (int i = 0; i < 28; ++i) {
            int newRow = curr.first + dx[i];
            int newCol = curr.second + dy[i];
            int hills = 0;
            if (isValid(newRow, newCol, numRows, numCols, grid, dx[i] ,dy[i], hills) && !visited[newRow][newCol]) {
                newCol+=hills;
                if (grid[newRow][newCol]== '>'){
                    //newCol+=1;
                    q.push({newRow, newCol+1});
                    visited[newRow][newCol+1] = true;
                    parent[newRow][newCol+1] = curr;
                }
                float dist = 0;
                dist +=sqrt(pow(dx[i], 2) + pow(dy[i],2));

                dist += distance[curr.first][curr.second];

                q.push({newRow, newCol});
                visited[newRow][newCol] = true;
                parent[newRow][newCol] = curr;
                distance[newRow][newCol] = dist;
            }
        }
    }
    return -1;
}

