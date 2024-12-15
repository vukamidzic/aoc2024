#include "../asserts.hpp"

#include <iostream>
#include <vector>
#include <fstream>
#include <set>

typedef std::pair<int, int> Pos;
typedef enum Dir { UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3 } Dir;
static const Pos dirs[] = { {-1,0},{1,0},{0,-1},{0,1} };
static const Dir right_turns[] = { RIGHT, LEFT, UP, DOWN };

Pos operator+(const Pos& a, const Pos& b) {
    return Pos(a.first + b.first, a.second + b.second);
}

bool in_bounds(Pos pos, int n, int m) {
    return pos.first >= 0 && pos.first < n && pos.second >= 0 && pos.second < m;
}

int dfs(int n, int m, std::vector<std::string>& grid, Pos curr) {
    Dir dir = UP; 
    int tiles = 0; 
    std::set<Pos> visited = {curr};

    while (true) {
        grid[curr.first][curr.second] = 'X';
        Pos next = curr + dirs[dir];
        if (!in_bounds(next,n,m)) 
            break;

        if (grid[next.first][next.second] == '#') {
            dir = right_turns[dir];
            curr = curr + dirs[dir];
        }
        else 
            curr = next;
        
        visited.insert(curr);
    }

    return visited.size();
}

int part1(const std::string& filename) {
    std::ifstream in(filename);
    std::vector<std::string> grid;
    std::string line;

    Pos start;
    int start_x = 0;
    while (getline(in, line)) {
        int start_y = line.find_first_of('^'); 
        if (start_y != std::string::npos) 
            start = Pos(start_x, start_y);

        start_x++;
        grid.push_back(line);
    }
    in.close();

    int res = dfs(grid.size(), grid[0].size(), grid, start);

    return res;
}

std::ostream& operator<<(std::ostream& os, Pos p) {
    os << "(" << p.first << "," << p.second << ")";
    return os;
}

bool findLoop(int n, int m, std::vector<std::string>& grid, Pos curr) {
    Dir dir = UP; 
    std::set<std::pair<Pos,Dir>> visited = {{curr,dir}};

    while (true) {
        auto next = curr + dirs[dir];
        if (!in_bounds(next,n,m)) return false;

        while (grid[next.first][next.second] == '#') {
            dir = right_turns[dir];
            next = curr + dirs[dir];
            if (!in_bounds(next,n,m)) return false;
        }
        if (visited.count({next,dir})) return true;

        curr = next;
        visited.insert({next,dir});
    }

    return false;
}

int part2(const std::string& filename) {
    std::ifstream in(filename);
    std::vector<std::string> grid;
    std::string line;

    Pos start;
    int start_x = 0;
    while (getline(in, line)) {
        int start_y = line.find_first_of('^'); 
        if (start_y != std::string::npos) 
            start = Pos(start_x, start_y);

        start_x++;
        grid.push_back(line);
    }
    in.close();

    int res = 0;

    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[0].size(); ++j) {
            if (grid[i][j] == '.') {
                grid[i][j] = '#';
                if (findLoop(grid.size(),grid[0].size(),grid,start)) res++;
                grid[i][j] = '.';
            }
        }
    }

    return res;
}

int main(void) {
    CASE(part1("test.txt"), 41);
    std::cout << "Part 1: " << part1("input.txt") << std::endl;

    CASE(part2("test.txt"), 6);
    std::cout << "Part 2: " << part2("input.txt") << std::endl;

    return 0;
}