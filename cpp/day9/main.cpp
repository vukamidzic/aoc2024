#include "../asserts.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

#define ll long long 
#define ull unsigned long long

ll mergeFiles(std::vector<int> disk) {
    int n = disk.size();
    int empty = 0, digit = n-1;

    while (empty < n && disk[empty] != -1) empty++;
    while (digit >= 0 && disk[digit] == -1) digit--;

    while (empty < digit) {
        disk[empty] = disk[digit];
        disk[digit] = -1;
        digit--;
        while (disk[digit] == -1) digit--;
        empty++;
        while (disk[empty] != -1) empty++;
    }

    ll res = 0;
    for (int i = 0; i < empty; ++i) {
        res += disk[i]*i;
    }

    return res;
}

ll part1(const std::string& filename) {
    std::ifstream in(filename);
    std::stringstream buf;
    buf << in.rdbuf();

    std::string data = buf.str();

    std::vector<int> disk;
    bool isEmpty = false;
    int fileID = 0;

    for (auto c : data) {
        int n = c-'0';
        if (isEmpty) {
            for (int i = 0; i < n; ++i) {
                disk.push_back(-1);
            }
        }
        else {
            for (int i = 0; i < n; ++i) {
                disk.push_back(fileID);
            }
            fileID++;
        }
        isEmpty = !isEmpty;
    }

    ll res = mergeFiles(disk);

    return res;
}

typedef struct File {
    File(int _id, int _pos, int _size) : 
        id(_id), 
        pos(_pos), 
        size(_size) {};
    int id;
    int pos;
    int size;
} File;

auto fileCmp = [](const File& f1, const File& f2) {
    return f1.pos > f2.pos;
};

typedef struct Space {
    Space(int _pos, int _size) :
        pos(_pos),
        size(_size) {};
    int pos;
    int size;
} Space;

ull insertFiles(std::vector<File>& files, std::vector<Space>& spaces) {
    ull res = 0;

    for (auto& file : files) {
        for (auto& space : spaces) {
            if (file.pos >= space.pos && file.size <= space.size) {
                file.pos = space.pos;
                space.pos += file.size;
                space.size -= file.size;
                break;
            }
        }
    }

    for (auto file : files) {
        ull fileRes = 0;
        int idx = file.pos;
        for (int i = 0; i < file.size; ++i) {
            fileRes += idx*file.id;
            idx++;
        }
        res += fileRes;
    }

    return res;
}

ull part2(const std::string& filename) {
    std::ifstream in(filename);
    std::stringstream buf;
    buf << in.rdbuf();

    std::string data = buf.str();

    std::vector<int> disk;
    bool isEmpty = false;
    int fileID = 0;
    int pos = 0;

    std::vector<File> files;
    std::vector<Space> spaces;

    for (auto c : data) {
        int n = c-'0';

        if (isEmpty) {
            Space space(pos,n);
            spaces.push_back(space);
        }
        else {
            File file(fileID,pos,n);
            files.push_back(file);
            fileID++;
        }
        pos += n;
        isEmpty = !isEmpty;
    }
    std::sort(files.begin(), files.end(), fileCmp);

    ll res = insertFiles(files, spaces);

    return res;
}

int main(void) {
    CASE(part1("test.txt"), 1928LL);
    std::cout << "Part 1: " << part1("input.txt") << std::endl;

    CASE(part2("test.txt"), 2858ULL);
    std::cout << "Part 2: " << part2("input.txt") << std::endl;

    return 0;
}