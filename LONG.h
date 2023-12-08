#pragma once
#include <vector>
#include <string>

class LONG {
  public:
    LONG() = default;
    LONG(const long long&, int = 10);
    LONG(const double&, int = 10);
    LONG(const int&, int = 10);
    LONG(const std::string&, int = 10);

    LONG (const LONG&);
    LONG operator*=(const LONG&);
    LONG operator+=(const LONG&);
    LONG operator-=(const LONG&);
    LONG operator/=(const LONG&);
    LONG operator*(const LONG&) const;
    LONG operator+(const LONG&) const;
    LONG operator-(const LONG&) const;
    LONG operator/(const LONG&) const;
    short operator<=>(const LONG&) const;
  private:
    int Base_ = 10;
    bool z = true; // true is +, false is -;
    void Parse_(const long long&);
    void Parse_(const double&);
    void Parse_(const std::string&);
    std::vector<unsigned char> Integer_;
    std::vector<unsigned char> PrePeriod_;
    std::vector<unsigned char> Period_;
};