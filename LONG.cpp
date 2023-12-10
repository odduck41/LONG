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
    if (!this->z) {
        this->z = true;
        return other -= *this;
    } else if (!other.z) {
        other.z = true;
        return *this -= other;
    }
    int carry = 0;

    // Reducing the PrePeriods to one length
    while (this->PrePeriod_.size() < other.PrePeriod_.size()) {
        if (this->Period_.empty()) {
            this->PrePeriod_.emplace_back(0);
        } else {
            this->PrePeriod_.emplace_back(this->Period_.front());
            this->Period_.erase(this->Period_.begin());
            this->Period_.emplace_back(this->PrePeriod_.back());
        }
    }
    while (other.PrePeriod_.size() < this->PrePeriod_.size()) {
        if (other.Period_.empty()) {
            other.PrePeriod_.emplace_back(0);
        } else {
            other.PrePeriod_.emplace_back(other.Period_.front());
            other.Period_.erase(other.Period_.begin());
            other.Period_.emplace_back(other.PrePeriod_.back());
        }
    }

    // Reducing the Periods to one length;
    auto NewLen = 0ull;
    if (!this->Period_.empty() && !other.Period_.empty()) {
        NewLen = lcd(this->Period_.size(), other.Period_.size());
    } else if (!this->Period_.empty()){
        NewLen = this->Period_.size();
    } else if (!other.Period_.empty()) {
        NewLen = other.Period_.size();
    }
    auto ThisPeriodCopy = this->Period_;
    auto OtherPeriodCopy = other.Period_;
    if (ThisPeriodCopy.empty()) {
        ThisPeriodCopy.emplace_back(0);
    }
    if (OtherPeriodCopy.empty()) {
        OtherPeriodCopy.emplace_back(0);
    }
    while (this->Period_.size() < NewLen) {
        for (auto &i: ThisPeriodCopy) {
            this->Period_.emplace_back(i);
        }
    }
    while (other.Period_.size() < NewLen) {
        for (auto &i: OtherPeriodCopy) {
            other.Period_.emplace_back(i);
        }
    }

    // Period addition
    for (auto i = 0ull; i < NewLen; ++i) {
        auto now = this->Period_[NewLen - i - 1] + other.Period_[NewLen - i - 1] + carry;
        this->Period_[NewLen - i - 1] = (now) % Base_;
        carry = now / (Base_);
    }
    if (!this->Period_.empty()) {
        this->Period_[NewLen - 1] += carry;
    }

    // PrePeriod addition
    for (auto i = 0ull; i < this->PrePeriod_.size(); ++i) {
        auto now = (int)this->PrePeriod_[this->PrePeriod_.size() - i - 1]
                + (int)other.PrePeriod_[this->PrePeriod_.size() - i - 1] + carry;
        this->PrePeriod_[this->PrePeriod_.size() - i - 1] = now % Base_;
        carry = now / (Base_);
    }
    // Integer addition
    for (int i = 0; i < std::max(other.Integer_.size(), this->Integer_.size()); ++i) {
        if (i < other.Integer_.size() && i < this->Integer_.size()) {
            auto now = (int)this->Integer_[i] + (int)other.Integer_[i] + carry;
            this->Integer_[i] = now % Base_;
            carry = now / Base_;
        } else if (i < other.Integer_.size()) {
            auto now = (int)other.Integer_[i] + carry;
            this->Integer_.emplace_back(now % Base_);
            carry = now / Base_;
        } else {
            auto now = (int)this->Integer_[i] + carry;
            this->Integer_[i] = now % Base_;
            carry = now / Base_;
        }
    }
    if (carry > 0) {
        this->Integer_.emplace_back(carry);
    }
    return *this;
}

LONG LONG::operator-=(const LONG &) {
    return LONG();
}
