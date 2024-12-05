#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cassert>

bool isMonotone(const std::vector<int>& v) {
    if (v.size() < 2) return true;
    
    bool ascending = true;
    bool descending = true;

    for (int i = 1; i < v.size(); ++i) {
        if (v[i] > v[i-1]) {
            descending = false;
        }
        else if (v[i] < v[i-1]) {
            ascending = false;
        }
        else return false;
    }

    return ascending || descending;
}

bool validDiffs(const std::vector<int>& v) {
    for (int i = 1; i < v.size(); ++i) {
        int diff = std::abs(v[i]-v[i-1]);
        if (diff < 1 || diff > 3) return false;
    }

    return true;
}

int part1(const std::string& filename) {
    std::ifstream in(filename);
    std::string line;
    std::vector<std::vector<int>> levels;

    while (std::getline(in, line)) {
        std::istringstream ss(line);
        std::vector<int> level;
        int num;

        while (ss >> num) {
            level.push_back(num);
        }
        levels.push_back(level);
    }

    int res = 0;
    
    for (auto& level: levels) {
        if (isMonotone(level) && validDiffs(level)) res++;
    }

    return res;
}

int part2(const std::string& filename) {
    std::ifstream in(filename);
    std::string line;
    std::vector<std::vector<int>> levels;

    while (std::getline(in, line)) {
        std::istringstream ss(line);
        std::vector<int> level;
        int num;

        while (ss >> num) {
            level.push_back(num);
        }
        levels.push_back(level);
    }

    int res = 0;

    for (auto& level : levels) {
        bool canRemove = false;
        for (int i = 0; i < level.size(); i++) {
            int n = level.size();
            std::vector<int> newLevel;

            for (int j = 0; j < n; ++j) {
                if (j != i) newLevel.push_back(level[j]);
            }
            if (isMonotone(newLevel) && validDiffs(newLevel)) canRemove = true;
        }

        if (canRemove) res++;
    }

    return res;
}

int main(void) {
    assert(part1("test.txt") == 2);
    std::cout << part1("input.txt") << std::endl;

    assert(part2("test.txt") == 4);
    std::cout << part2("input.txt") << std::endl;

    return 0;
}