#include "../asserts.hpp"

#include <iostream>
#include <fstream>
#include <list>
#include <map>
#include <cmath>

int digitCount(int64_t num) {
    int cnt = 0;
    while (num > 0) {
        cnt++;
        num /= 10;
    }

    return cnt;
}

int countPebbles(std::list<int64_t>& pebbles) {
    for (int i = 0; i < 25; ++i) {
        for (auto it = pebbles.begin(); it != pebbles.end(); ++it) {
            if (*it == 0) {
                *it += 1;
            }
            else {
                int n = digitCount(*it);
                if (n % 2 == 0) {
                    pebbles.insert(it, *it / (int64_t)std::pow(10,n/2));
                    *it %= (int64_t)std::pow(10,n/2);
                }
                else {
                    *it *= 2024;
                }
            }
        }
    }

    return pebbles.size();
}

int part1(const std::string& filename) {
    std::ifstream in(filename);
    int pebble;
    std::list<int64_t> pebbles;

    while (in >> pebble) {
        pebbles.push_back(pebble);
    }
    in.close();

    int res = countPebbles(pebbles);

    return res;
}

int64_t part2(const std::string& filename) {
    std::ifstream in(filename);
    int pebble;
    std::map<int64_t,int64_t> pebbles;

    while (in >> pebble) {
        pebbles[pebble]++;
    }

    for (int i = 0; i < 75; ++i) {
        std::map<int64_t, int64_t> newPebbles;

        for (auto [pebble, count] : pebbles) {
            if (pebble == 0) {
                newPebbles[1] = count;
            }
            else {
                int n = digitCount(pebble);
                if (n % 2 == 0) {
                    newPebbles[pebble / (int64_t)std::pow(10,n/2)] += count;
                    newPebbles[pebble % (int64_t)std::pow(10,n/2)] += count;
                }
                else {
                    newPebbles[pebble*2024] = count;
                }
            }
        }

        pebbles.swap(newPebbles);
    }

    int64_t res = 0;
    for (auto [pebble, count] : pebbles) {
        res += count;
    }

    return res;
}

int main(void) {
    CASE(part1("test.txt"), 55312);
    std::cout << "Part 1: " << part1("input.txt") << std::endl;
    std::cout << "Part 2: " << part2("input.txt") << std::endl;

    return 0;
}