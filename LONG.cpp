#include "LONG.h"

unsigned long long gcd(unsigned long long a, unsigned long long b) {
    return b ? gcd(b, a%b) : a;
}

unsigned long long lcd(unsigned long long a, unsigned long long b) {
    return std::max(a, b)/gcd(a, b) * std::min(a, b);
}

void LONG::Parse_(const char* Val) {
    bool pre = false;
    bool per = false;
    z = (Val[0] != '-');
    for (int i = 0 + (int)!z; Val[i] != '\0'; ++i) {
        int now = 0;
        if (Val[i] == '[') {
            ++i;
            for (;Val[i] != ']'; ++i) {
                now = now * 10 + (Val[i] - '0');
            }
        } else if ('A' <= Val[i] && Val[i] <= 'Z') {
            now = Val[i] - 55;
        } else if ('a' <= Val[i] && Val[i] <= 'z') {
            now = Val[i] - 87;
        } else if ('0' <= Val[i] && Val[i] <= '9') {
            now = Val[i] - '0';
        } else if (Val[i] == ']') {
            continue;
        } else if (Val[i] == '.') {
            pre = true;
            continue;
        } else if (Val[i] == '(') {
            pre = false;
            per = true;
            continue;
        } else if (Val[i] == ')') {
            break;
        } else {
            throw std::pair<const char*, int> {"Symbol error", i};
        }
        if (now >= Base_) {
            throw std::pair<const char*, int>{"The number is greater than or equal to the base", i};
        }
        if (!pre && !per) {
            Integer_.emplace_back(now);
        } else if(pre) {
            PrePeriod_.emplace_back(now);
        } else {
            Period_.emplace_back(now);
        }
    }
    std::reverse(Integer_.begin(), Integer_.end());
}

LONG::LONG(const char* Val, int Base) : Base_(Base) {
    Parse_(Val);
}

LONG::LONG(const char* Val) : Base_(10) {
    Parse_(Val);
}

std::ostream& operator<< (std::ostream& out, LONG var) {
    if (!var.z) {
        out << "-";
    }
    for (auto i = 0ull; i < var.Integer_.size(); ++i) {
        if ((int)var.Integer_[var.Integer_.size() - i - 1] > 9) {
            out << '[';
        }
        out << (int)var.Integer_[var.Integer_.size() - i - 1];
        if ((int)var.Integer_[var.Integer_.size() - i - 1] > 9) {
            out << ']';
        }
    }
    if (!var.PrePeriod_.empty() || !var.Period_.empty()) {
        out << '.';
    }
    for (auto &i: var.PrePeriod_) {
        if (i > 9) {
            out << '[';
        }
        out << (int)i;
        if (i > 9) {
            out << ']';
        }
    }
    if (!var.Period_.empty()) {
        out << '(';
    }
    for (auto &i: var.Period_) {
        if (i > 9) {
            out << '[';
        }
        out << (int)i;
        if (i > 9) {
            out << ']';
        }
    }
    if (!var.Period_.empty()) {
        out << ')';
    }
    return out;
}


LONG LONG::operator+= (LONG other) {
    if (!other.z) {
        return *this -= other;
    }

}
