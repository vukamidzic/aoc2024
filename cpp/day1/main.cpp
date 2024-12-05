#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <set>

int part1(const std::string& filename) {
    std::ifstream in(filename);
    std::string line;

    std::multiset<int> leftSide;
    std::multiset<int> rightSide;

    while (std::getline(in, line)) {
        std::istringstream ss(line);
        int left, right;

        ss >> left;
        ss >> right;
        
        leftSide.insert(left);
        rightSide.insert(right);
    }
    in.close();

    int res = 0;
    auto it1 = leftSide.begin();
    auto it2 = rightSide.begin();
    
    while (it1 != leftSide.end() && it2 != rightSide.end()) {
        res += std::abs((*it1) - (*it2));
        ++it1;
        ++it2;
    }

    return res;
}

int part2(const std::string& filename) {
    std::ifstream in(filename);
    std::string line;

    std::multiset<int> leftSide;
    std::multiset<int> rightSide;

    while (std::getline(in, line)) {
        std::istringstream ss(line);
        int left, right;

        ss >> left;
        ss >> right;
        
        leftSide.insert(left);
        rightSide.insert(right);
    }
    in.close();

    std::set<int> leftVisited;
    int score = 0;

    for (auto it = leftSide.begin(); it != leftSide.end(); ++it) {
        if (!leftVisited.count((*it))) {
            int freq = rightSide.count((*it));
            score += (*it)*freq;
        }
    }

    return score;
}

int main(void) {
    assert(part1("test.txt") == 11);
    std::cout << part1("input.txt") << std::endl;

    assert(part2("test.txt") == 31);
    std::cout << part2("input.txt") << std::endl;

    return 0;
}
