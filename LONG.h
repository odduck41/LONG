#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

template <class A, class B, class C>
struct triple {
    A first;
    B second;
    C third;
};


typedef std::basic_string<unsigned char> ustring;

class LONG {
public:
    LONG() = default;
    LONG(const std::string&, int = 10);
    void to_(int);
    LONG operator+ (LONG) const;
private:
    std::vector<unsigned char> Integer_;
    std::vector<unsigned char> PrePeriod_;
    std::vector<unsigned char> Period_;
    int Base_ = 10;
    void Parse(const std::string&);

};

