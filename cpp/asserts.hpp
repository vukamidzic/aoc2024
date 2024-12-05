#ifndef TEST_HPP
#define TEST_HPP

#include <iostream>
#include <vector>
#include <functional>

template<typename T>
void assert_equal(T res, T expec) {
    if (res != expec) {
        std::cout << "[\033[31mASSERT_FAIL\033[0m] Expected " << expec << ", got " << res << std::endl;
    }
    else {
        std::cout << "[\033[32mASSERT_SUCCESS\033[0m] Passed" << std::endl;
    }
};

#define CASE(res, expec) \
    std::cout << "Running " << #res << std::endl;   \
    assert_equal((res),(expec));                    

void assert_section(const std::string& name, std::function<void()> funcs) { funcs(); }

#define SECTION(name,...) assert_section(name, []() {__VA_ARGS__})

#endif