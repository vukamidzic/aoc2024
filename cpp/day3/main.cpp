#include "../asserts.hpp"

#include <iostream>
#include <regex>
#include <fstream>
// #include <cassert>

#define assert_equal(res, expec) { \
    if ((res) != (expec)) { \
        std::cerr << "[\033[31mASSERT_FAIL\033[0m] Got " << (res) << ", expected " << (expec) << std::endl; \
        std::exit(1); \
    } \
    else { \
        std::cout << "[\033[32mASSERT_SUCCESS\033[0m] Passed" << std::endl; \
    } \
}

int part1(const std::string& filename) {
    std::ifstream in(filename);
    std::string content;

    char c;
    while (in >> c) {
        content += c;
    }

    std::regex r("mul\\((\\d+)\\,(\\d+)\\)");
    std::sregex_iterator it(content.begin(), content.end(), r);
    std::sregex_iterator end;
    
    int res = 0;
    while (it != end) {
        int first = std::stoi((*it)[1].str());
        int second = std::stoi((*it)[2].str());
        res += first * second;
        ++it;
    }

    return res;
}

int part2(const std::string& filename) {
    std::ifstream in(filename);
    std::string content;

    char c;
    while (in >> c) {
        content += c;
    }

    std::regex r("mul\\((\\d+)\\,(\\d+)\\)|(don't|do)\\(\\)");
    std::sregex_iterator it(content.begin(), content.end(), r);
    std::sregex_iterator end;
    
    int res = 0;
    bool enabled = true;
    while (it != end) {
        std::string instr = (*it).str(); 

        if (instr.find_first_of("mul") != std::string::npos) {
            if (enabled) {
                int first = std::stoi((*it)[1].str());
                int second = std::stoi((*it)[2].str());
                res += first * second;
            }
        }
        else if (instr == "don't()") {
            enabled = false;
        }
        else {
            enabled = true;
        }

        ++it;
    }

    return res;
}

int main(void) {
    CASE(part1("test.txt"),161);
    std::cout << part1("test.txt") << std::endl;

    CASE(part2("test.txt"),48);
    std::cout << part2("input.txt") << std::endl;


    return 0;
}