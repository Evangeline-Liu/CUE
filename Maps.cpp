std::vector<std::string> GetMaps(int Num) {
    std::vector<std::string> Map1 = {
            "s.#..",
            "..#..",
            ".....",
            "..#..",
            "..#.e"
    };
    std::vector<std::string> Map2 = {
            "...#.",
            "...#.",
            ".....",
            "...#.",
            "...#."
    };
    std::vector<std::string> Map3 = {
            "....#..#..",
            "...<..>...",
            "...<..>.#.",
            "...<..>..#",
            "......#..."
    };
    std::vector<std::string> Map4 = {
            "....#..#..",
            "...#..>...",
            "...#..>.#.",
            "...#..>..#",
            "......>..."
    };
    std::vector<std::string> Map5 = {
            ".>>>>."
    };
    std::vector<std::string> Map6 = {
            ".#....##..",
            ".#.#..#...",
            ".#.#..#.#.",
            ".#.#..#.#.",
            "...#....#."
    };
    std::vector<std::string> Map7 = {
            "...#......",
            "...#......",
            "...#......",
            "...#......",
            "...#......"
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
    else if (Num ==4 ){
        return Map4;
    }
    else if (Num ==5 ){
        return Map5;
    }
    else if (Num ==6 ){
        return Map6;
    }
    else if (Num ==7 ){
        return Map7;
    }
    else {
        return {};
    }
}

