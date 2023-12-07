#include "LONG.h"

// Parsing
void LONG::Parse_(const long long&) {};
void LONG::Parse_(const double&) {};
void LONG::Parse_(const std::string&) {};

// Initializing
LONG::LONG(const std::string & val) {
    ;
}

LONG::LONG(const double & val) {
    ;
}

LONG::LONG(const long long int & val) {
    ;
}

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