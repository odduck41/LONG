#include "LONG.h"

unsigned long long gcd(unsigned long long a, unsigned long long b) {
    return b ? gcd(b, a%b) : a;
}
unsigned long long lcd(unsigned long long a, unsigned long long b) {
    return std::max(a, b)/gcd(a, b) * std::min(a, b);
}

std::ostream& operator<<(std::ostream& out, LONG th) {
    for (long long i = th.Integer_.size() - 1; i >= 0; --i) {
        if ((int)th.Integer_[i] > 9) {
            out << '[';
        }
        out << (int)th.Integer_[i];
        if ((int)th.Integer_[i] > 9) {
            out << ']';
        }
    }
    if (!th.PrePeriod_.empty() || !th.Period_.empty()) {
        out << '.';
    }
    for (auto &i: th.PrePeriod_) {
        if (i > 9) {
            out << '[';
        }
        out << (int)i;
        if (i > 9) {
            out << ']';
        }
    }
    if (!th.Period_.empty()) {
        out << '(';
    }
    for (auto &i: th.Period_) {
        if (i > 9) {
            out << '[';
        }
        out << (int)i;
        if (i > 9) {
            out << ']';
        }
    }
    if (!th.Period_.empty()) {
        out << ')';
    }
    return out;
}

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

LONG LONG::operator+ (LONG other) const {
    LONG sum;
    sum.Integer_.resize(std::max(other.Integer_.size(), this->Integer_.size()));
    sum.Base_ = this->Base_;
    int carry = 0;
    //Pre PrePeriod part

    //Period part
    if (this->PrePeriod_.size() == other.PrePeriod_.size()) {
        sum.Period_.resize(lcd(this->Period_.size(), other.Period_.size()));
        auto bvo = other.Period_;
        auto nvo = this->Period_;
        for (auto i = lcd(this->Period_.size(), other.Period_.size()) / other.Period_.size(); i > 0; --i) {
            for (auto &j: bvo) {
                other.Period_.push_back(j);
            }
        }
        for (auto i = lcd(this->Period_.size(), other.Period_.size()) / this->Period_.size(); i > 0; --i) {
            for (auto &j: this->Period_) {
                nvo.push_back(j);
            }
        }
        for (long long i = sum.Period_.size() - 1; i >= 0; --i) {
            sum.Period_[i] = ((int) nvo[i] + (int) other.Period_[i] + carry) % Base_;
            carry = ((int) nvo[i] + (int) other.Period_[i] + carry) / Base_;
        }
        sum.Period_[sum.Period_.size() - 1] += carry;
    }
    // Int part
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