#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

template <class A, class B, class C>
struct triple {
    A first;
    B second;
    C third;
};


typedef std::basic_string<unsigned char> ustring;

class LONG {
public:
    friend std::ostream& operator<<(std::ostream&, LONG);
    LONG() = default;
    explicit LONG(const std::string&, int = 10);
    //void to_(int);
    LONG operator+ (LONG) const;
    LONG operator* (const LONG&) const;
    LONG operator^ (long long) const;
    bool operator<(LONG) const;
    bool operator>(LONG) const;
    bool operator==(const LONG&) const;
    LONG operator/ (const LONG&) const;
    LONG to_10() const;
private:
    std::vector<unsigned char> Integer_;
    std::vector<unsigned char> PrePeriod_;
    std::vector<unsigned char> Period_;
    int Base_ = 10;
    void Parse(const std::string&);

};

