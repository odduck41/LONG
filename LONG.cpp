#include "LONG.h"


void LONG::Parse(const std::string& Val) {
    bool pre = false;
    bool per = false;
    for (int i = 0; Val[i] != '\0'; ++i) {
        int now = 0;
        if (Val[i] == '[') {
            ++i;
            for (;Val[i] != ']'; ++i) {
                now = now * 10 + (Val[i] - '0');
            }
        } else if (65 <= Val[i] && Val[i] <= 90) {
            now = Val[i] - 55;
        } else if (97 <= Val[i] && Val[i] <= 122) {
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

void LONG::to_(int Base) {
    ;
}

LONG LONG::operator+ (LONG other) const {
    LONG sum;
    other.to_(this->Base_);
    sum.Integer_.resize(std::max(other.Integer_.size(), this->Integer_.size()));
    sum.Base_ = this->Base_;
    int carry = 0;

    for (int i = 0; i < std::max(other.Integer_.size(), this->Integer_.size()); ++i) {
        if (i < other.Integer_.size() && i < this->Integer_.size()) {
            sum.Integer_[i] = ((int)this->Integer_[i] + (int)other.Integer_[i] + carry) % Base_;
            carry = ((int)this->Integer_[i] + (int)other.Integer_[i] + carry) / Base_;
        } else if (i < other.Integer_.size()) {
            sum.Integer_[i] = ((int)other.Integer_[i] + carry) % Base_;
            carry = ((int)other.Integer_[i] + carry) / Base_;
        } else {
            sum.Integer_[i] = ((int)this->Integer_[i] + carry) % Base_;
            carry = ((int)this->Integer_[i] + carry) / Base_;
        }
        if (carry > 0 && i + 1 == std::max(other.Integer_.size(), this->Integer_.size())) {
            sum.Integer_.push_back(carry);
        }
    }


    return sum;
}

std::string operator* (const std::string& s, int n) {
    std::string ans;
    for (int i = 0; i < n; ++i) {
        ans += s;
    }
    return ans;
}

LONG::LONG(const std::string& Val, int Base) : Base_(Base) {
    try {
        Parse(Val);
    } catch (std::pair<const char*, int> a) {
        std::cout << a.first << '\n' << "Base: " << Base_ << '\n' << "Number: " << Val << '\n'
        << "Here:   " << (std::string)" " * (a.second) << '^' << '\n';
    }
}