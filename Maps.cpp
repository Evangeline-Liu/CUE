#include "Maps.h"

std::vector<std::string> GetMaps(int Num) {
    std::vector<std::string> Map1 = {
            "..#..",
            "..#..",
            "..#..",
            "..#..",
            "....."
    };
    std::vector<std::string> Map2 = {
            "..#..",
            "..#..",
            "#....",
            "#..#.",
            "...#."
    };
    std::vector<std::string> Map3 = {
            "....#..#..",
            "...#......",
            "..#..#..#.",
            ".#..#....#",
            "...#..#..."
    };

    if (Num == 1) {
        return Map1;
    }
    else if (Num==2) {
        return Map2;
    }
    else if (Num ==3 ){
        return Map3;
    }
    else {
        return {};
    }
}
