#include "LONG.h"

// Parsing
void LONG::Parse_(const long long& from) {};
void LONG::Parse_(const double& from) {};
void LONG::Parse_(const std::string& from) {

};

// Initializing
LONG::LONG(const std::string & val, int Base): Base_(Base) {
    Parse_(val);
}

LONG::LONG(const double & val, int Base): Base_(Base) {
    Parse_(val);
}

LONG::LONG(const long long& val, int Base): Base_(Base) {
    Parse_(val);
}

LONG::LONG(const int& val, int Base): LONG(static_cast<long long> (val), Base) {};

// Coping
LONG::LONG(const LONG & other) {
    this->z = other.z;
    this->Base_ = other.Base_;
    this->Integer_ = other.Integer_;
    this->PrePeriod_ = other.PrePeriod_;
    this->Period_ = other.Period_;
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