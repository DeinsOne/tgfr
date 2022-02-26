#ifndef __CONFIG_HPP
#define __CONFIG_HPP

#include <cstdio>

class Counter {
    std::size_t m_num = 0;

public:
    Counter() = default;

    void add() { m_num++; }
    std::size_t get() { return m_num; }
};

#endif // __CONFIG_HPP
