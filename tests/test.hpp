#ifndef TEST_HPP
#define TEST_HPP

#include <cassert>
#include <iostream>
#include <string>

#define TEST(MSG, COND)                                                                            \
  {                                                                                                \
    std::string t = MSG;                                                                           \
    if (!COND) {                                                                                   \
      assert(COND &&MSG);                                                                          \
    }                                                                                              \
    std::cout << "PASSED: " << MSG << std::endl;                                                   \
  }

#endif
