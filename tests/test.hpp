#ifndef TEST_HPP
#define TEST_HPP

#include <iostream>
#include <string>
#include <cassert> 

#define TEST(MSG, COND) { \
    std::string t = MSG; \
    if (!COND) {\
        assert(COND && MSG);\
    }\
    std::cout << "PASSED: " << MSG << std::endl; \
}

#endif
