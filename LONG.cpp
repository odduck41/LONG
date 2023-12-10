#include "LONG.h"

// Parsing
void LONG::Parse_(const long long& from) {};
void LONG::Parse_(const double& from) {};
void LONG::Parse_(const std::string& from) {

};

// Initializing
LONG::LONG(const std::string & val) {
    Parse_(val);
}

LONG::LONG(const double & val) {
    Parse_(val);
}

LONG::LONG(const long long& val) {
    Parse_(val);
}

LONG::LONG(const int& val) : LONG(static_cast<long long> (val)) {};

LONG::LONG(const LONG & other) {
    ;
}

// Arithmetic operators
LONG LONG::operator*=(const LONG & other) {
    return {};
}

LONG LONG::operator+=(const LONG & other) {
    return {};
}

LONG LONG::operator-=(const LONG & other) {
    return {};
}

LONG LONG::operator/=(const LONG & other) {
    return {};
}

LONG LONG::operator*(const LONG & other) const{
    LONG copy = *this;
    return copy *= other;
}

LONG LONG::operator+(const LONG & other) const {
    LONG copy = *this;
    return copy += other;
}

LONG LONG::operator-(const LONG & other) const {
    LONG copy = *this;
    return copy -= other;
}

LONG LONG::operator/(const LONG & other) const {
    LONG copy = *this;
    return copy /= other;
}

// Comparing operators

short LONG::operator<=>(const LONG &) const {
    return 0;
}