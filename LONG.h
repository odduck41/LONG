#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

unsigned long long gcd(unsigned long long, unsigned long long);
unsigned long long lcd(unsigned long long, unsigned long long);

class LONG {
  public:
    friend std::ostream& operator<<(std::ostream& out, LONG th);
    LONG() = default;
    explicit LONG(const char*, int = 10);
    LONG(const char*);
    LONG operator-() const;
    //LONG (const LONG&);
    //LONG operator*=(LONG);
    LONG operator+=(LONG);
    LONG operator-=(LONG);
    //LONG operator/=(const LONG&);
    //LONG operator*(const LONG&) const;
    LONG operator+(const LONG&) const;
    LONG operator-(const LONG&) const;
    LONG lbl (LONG);
    //LONG operator/(const LONG&) const;
    bool operator> (LONG);
    bool operator== (LONG);
    bool operator< (const LONG&);
    bool operator>= (const LONG&);
    bool operator<= (const LONG&);
  private:
    bool z = true; // true is +, false is -;
    void ToOneView(LONG& other);
    void Parse_(const char*);
  protected:
    std::vector<unsigned char> Integer_;
    std::vector<unsigned char> PrePeriod_;
    std::vector<unsigned char> Period_;
    int Base_;
};
