#include "../asserts.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

typedef std::pair<int, int> Point;

std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << "(" << p.first << "," << p.second << ")";
    return os;
}

std::ostream& operator<<(std::ostream& os, const std::vector<Point>& v) {
    os << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        os << v[i];
        if (i != v.size() - 1) os << ", ";
    }
    os << "]";

    return os;
}

std::ostream& operator<<(std::ostream& os, const std::map<char, std::vector<Point>>& mp) {
    os << "{\n";
    for (auto kv : mp) {
        os << "  " << kv.first << ": " << kv.second << "\n";
    }
    os << "}";

    return os;
}

int inBounds(Point p, int n, int m) {
    return (0 <= p.first && p.first < n && 0 <= p.second && p.second < m);
}

int findAntiNodes(int n, int m, std::set<Point>& unique, const std::vector<Point>& points) {
    int cnt = 0;

    for (int i = 0; i < points.size(); ++i) {
        for (int j = i + 1; j < points.size(); ++j) {
            Point a = points[i];
            Point b = points[j];

            int dx = (b.first-a.first);
            int dy = (b.second-a.second);
            
            Point newA = {a.first-dx, a.second-dy};
            Point newB = {b.first+dx, b.second+dy};

            if (inBounds(newA,n,m) && !unique.count(newA)) {
                unique.insert(newA); cnt++;
            }
            if (inBounds(newB,n,m) && !unique.count(newB)) {
                unique.insert(newB); cnt++;
            }
        }
    }

    return cnt;
}

int part1(const std::string& filename) {
    std::ifstream in(filename);
    std::string line;
    int row = 0;
    std::map<char, std::vector<Point>> points;

    while (getline(in, line)) {
        for (size_t col = 0; col < line.size(); ++col) {
            if (line[col] != '.') {
                points[line[col]].push_back({row,col});
            }
        }
        row++;
    }

    for (auto& kv : points) {
        std::sort(kv.second.begin(), kv.second.end(), [](Point a, Point b) {
            return a.first < b.first || (a.first == b.first && a.second < b.second);
        });
    }

    std::set<Point> unique;
    int n = row;
    int m = line.size();
    int res = 0;

    for (auto& kv : points) {
        res += findAntiNodes(n,m,unique,kv.second);
    }

    return res;
}

int findAllAntiNodes(int n, int m, std::set<Point>& unique, const std::vector<Point>& points) {
    int cnt = 0;

    for (int i = 0; i < points.size(); ++i) {
        for (int j = i+1; j < points.size(); ++j) {
            Point a = points[i];
            Point b = points[j];

            if (!unique.count(a)) {
                unique.insert(a); cnt++;
            }
            if (!unique.count(b)) {
                unique.insert(b); cnt++;
            }

            int dx = (b.first-a.first);
            int dy = (b.second-a.second);
            
            Point newA = {a.first-dx, a.second-dy};
            Point newB = {b.first+dx, b.second+dy};

            while (inBounds(newA,n,m)) {
                if (!unique.count(newA)) {
                    unique.insert(newA); cnt++;
                }

                newA = {newA.first-dx, newA.second-dy};
            }
            while (inBounds(newB,n,m)) {
                if (!unique.count(newB)) {
                    unique.insert(newB); cnt++;
                }

                newB = {newB.first+dx, newB.second+dy};
            }
        }
    }

    return cnt;
}

int part2(const std::string& filename) {
    std::ifstream in(filename);
    std::string line;
    int row = 0;
    std::map<char, std::vector<Point>> points;

    while (getline(in, line)) {
        for (size_t col = 0; col < line.size(); ++col) {
            if (line[col] != '.') {
                points[line[col]].push_back({row,col});
            }
        }
        row++;
    }

    for (auto& kv : points) {
        std::sort(kv.second.begin(), kv.second.end(), [](Point a, Point b) {
            return a.first < b.first || (a.first == b.first && a.second < b.second);
        });
    }

    std::set<Point> unique;
    int n = row;
    int m = line.size();
    int res = 0;

    for (auto& kv : points) {
        res += findAllAntiNodes(n,m,unique,kv.second);
    }

    return res;
}

int main(void) {
    CASE(part1("test.txt"), 14);
    std::cout << "Part 1: " << part1("input.txt") << std::endl;

    CASE(part2("test.txt"), 34);
    std::cout << "Part 2: " << part2("input.txt") << std::endl;

    return 0;
}