#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

class LONG {
  public:
    friend std::ostream& operator<<(std::ostream& out, LONG th);
    LONG() = default;
    explicit LONG(const char*, int = 10);
    //LONG(const long long&);
    //LONG(const double&);
    //LONG(const int&);
    LONG(const char*);
    //LONG (const LONG&);
    //LONG operator*=(const LONG&);
    LONG operator+=(LONG);
    //LONG operator-=(const LONG&);
    //LONG operator/=(const LONG&);
    //LONG operator*(const LONG&) const;
    //LONG operator+(const LONG&) const;
    //LONG operator-(const LONG&) const;
    //LONG operator/(const LONG&) const;
    //short operator<=>(const LONG&) const;
  private:
    bool z = true; // true is +, false is -;
    int Base_;
    //void Parse_(const long long&);
    //void Parse_(const double&);
    void Parse_(const char*);
    std::vector<unsigned char> Integer_;
    std::vector<unsigned char> PrePeriod_;
    std::vector<unsigned char> Period_;
};