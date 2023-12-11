#include "LONG.h"

#include <utility>

unsigned long long gcd(unsigned long long a, unsigned long long b) {
    return b ? gcd(b, a%b) : a;
}

unsigned long long lcd(unsigned long long a, unsigned long long b) {
    return std::max(a, b)/gcd(a, b) * std::min(a, b);
}
void LONG::ToOneView(LONG &other) {
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

LONG LONG::operator-() const{
    LONG copy = *this;
    copy.z = !(this->z);
    return copy;
}

LONG LONG::operator+= (LONG other) {
    if (!this->z && !other.z) {
        ;
    } else if (!this->z) {
        return *this = (other -= (-(*this)));
    } else if (!other.z) {
        return *this -= (-other);
    }
    int carry = 0;
    this->ToOneView(other);
    auto NewLen = 0ull;
    if (!this->Period_.empty() && !other.Period_.empty()) {
        NewLen = lcd(this->Period_.size(), other.Period_.size());
    } else if (!this->Period_.empty()){
        NewLen = this->Period_.size();
    } else if (!other.Period_.empty()) {
        NewLen = other.Period_.size();
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
    for (auto i = 0ull; i < std::max(other.Integer_.size(), this->Integer_.size()); ++i) {
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

LONG LONG::operator-= (LONG other) {
    if (this->z && other.z) {
        ;
    } else if (this->z && !other.z) {
        return *this += (-other);
    } else if (!this->z && other.z) {
        return *this = -(*this += other);
    } else if (!this->z && !other.z){
        return *this = (-other -= (-*this));
    }
    this->ToOneView(other);
    if (other > *this) {
        return *this = -(other -= *this);
    }
    // Period part
    for (auto i = 0ull; i < Period_.size(); ++i) {
        if (this->Period_[Period_.size() - i - 1] >= other.Period_[Period_.size() - i - 1]) {
            this->Period_[Period_.size() - i - 1] -= other.Period_[Period_.size() - i - 1];
        } else {
            bool borrow = false;
            for (auto j = i + 1; j < Period_.size(); ++j) {
                if (this->Period_[Period_.size() - j - 1] > other.Period_[Period_.size() - j - 1]) {
                    this->Period_[Period_.size() - j - 1] -= 1;
                    borrow = true;
                    break;
                } else {
                    this->Period_[Period_.size() - j - 1] += (Base_ - 1);
                }
            }
            if (!borrow) {
                for (auto j = 0ull; j < PrePeriod_.size(); ++j) {
                    if (this->PrePeriod_[PrePeriod_.size() - j - 1] > other.PrePeriod_[PrePeriod_.size() - j - 1]) {
                        this->PrePeriod_[PrePeriod_.size() - j - 1] -= 1;
                        borrow = true;
                        break;
                    } else {
                        this->PrePeriod_[PrePeriod_.size() - j - 1] += (Base_ - 1);
                    }
                }
                for (auto j = i + 1; j < Period_.size(); ++j) {
                    this->Period_[Period_.size() - j - 1] += (Base_ - 1);
                }
            }
            if (!borrow) {
                for (auto j = 0ull; j < Integer_.size(); ++j) {
                    if (j < other.Integer_.size() && this->Integer_[j] > other.Integer_[j]) {
                        this->Integer_[j] -= 1;
                        break;
                    } else if (j < other.Integer_.size() && this->Integer_[j] < other.Integer_[j]){
                        this->Integer_[j] += (Base_ - 1);
                    } else {
                        this->Integer_[j] -= 1;
                        break;
                    }
                }
                for (auto j = 0ull; j < PrePeriod_.size(); ++j) {
                    this->PrePeriod_[PrePeriod_.size() - j - 1] += (Base_ - 1);
                }
                for (auto j = i + 1; j < Period_.size(); ++j) {
                    this->Period_[Period_.size() - j - 1] += (Base_ - 1);
                }
            }
            this->Period_[Period_.size() - i - 1] += Base_;
            this->Period_[Period_.size() - i - 1] -= other.Period_[Period_.size() - i - 1];
            if (i == Period_.size() - 1) {
                for (auto j = 0ull; j < Period_.size(); ++j) {
                    if (Period_[Period_.size() - j - 1] == 0) {
                        Period_[Period_.size() - j - 1] = Base_ - 1;
                    } else {
                        Period_[Period_.size() - j - 1] -= 1;
                        break;
                    }
                }
            }
        }
    }

    // PrePeriod part
    for (auto i = 0ull; i < PrePeriod_.size(); ++i) {
        if (this->PrePeriod_[PrePeriod_.size() - i - 1] >= other.PrePeriod_[PrePeriod_.size() - i - 1]) {
            this->PrePeriod_[PrePeriod_.size() - i - 1] -= other.PrePeriod_[PrePeriod_.size() - i - 1];
        } else {
            bool borrow = false;
            for (auto j = i + 1; j < PrePeriod_.size(); ++j) {
                if (this->PrePeriod_[PrePeriod_.size() - j - 1] > other.PrePeriod_[PrePeriod_.size() - j - 1]) {
                    this->PrePeriod_[PrePeriod_.size() - j - 1] -= 1;
                    borrow = true;
                    break;
                } else {
                    this->PrePeriod_[PrePeriod_.size() - j - 1] += (Base_ - 1);
                }
            }
            if (!borrow) {
                for (auto j = 0ull; j < Integer_.size(); ++j) {
                    if (j < other.Integer_.size() && this->Integer_[j] > other.Integer_[j]) {
                        this->Integer_[j] -= 1;
                        break;
                    } else if (j < other.Integer_.size() && this->Integer_[j] < other.Integer_[j]){
                        this->Integer_[j] += (Base_ - 1);
                    } else {
                        this->Integer_[j] -= 1;
                        break;
                    }
                }
                for (auto j = i + 1; j < PrePeriod_.size(); ++j) {
                    this->PrePeriod_[PrePeriod_.size() - j - 1] += (Base_ - 1);
                }
            }
            this->PrePeriod_[PrePeriod_.size() - i - 1] += Base_;
            this->PrePeriod_[PrePeriod_.size() - i - 1] -= other.PrePeriod_[PrePeriod_.size() - i - 1];
        }
    }
    // Integer part
    for (auto i = 0ull; i < other.Integer_.size(); ++i) {
        if (this->Integer_[i] >= other.Integer_[i]) {
            this->Integer_[i] -= other.Integer_[i];
        } else {
            for (auto j = i + 1; j < Integer_.size(); ++j) {
                if (j < other.Integer_.size() && this->Integer_[j] > other.Integer_[j]) {
                    this->Integer_[j] -= 1;
                    break;
                } else if (j < other.Integer_.size() && this->Integer_[j] < other.Integer_[j]){
                    this->Integer_[j] += (Base_ - 1);
                } else {
                    this->Integer_[j] -= 1;
                    break;
                }
            }
            this->Integer_[i] += Base_;
            this->Integer_[i] -= other.Integer_[i];
        }
    }
    for (auto i = 0ull; i < Integer_.size(); ++i) {
        if (Integer_[Integer_.size() - i - 1] == 0) {
            Integer_.erase(Integer_.end() - i - 1);
        } else {
            break;
        }
    }
    return *this;
}

bool LONG::operator> (LONG other){
    if (this->z && !other.z) {
        return true;
    } else if (!this->z && other.z) {
        return false;
    }
    this->ToOneView(other);
    if (this->Integer_.size() > other.Integer_.size()) {
        return this->z;
    } else if (this->Integer_.size() < other.Integer_.size()){
        return !this->z;
    }
    for (auto i = 0ull; i < this->Integer_.size(); ++i) {
        if (this->Integer_[Integer_.size() - i - 1] > other.Integer_[Integer_.size() - i - 1]) {
            return this->z;
        } else if (this->Integer_[Integer_.size() - i - 1] < other.Integer_[Integer_.size() - i - 1]) {
            return !this->z;
        }
    }
    for (auto i = 0ull; i < this->PrePeriod_.size(); ++i) {
        if (this->PrePeriod_[i] > other.PrePeriod_[i]) {
            return this->z;
        } else if (this->PrePeriod_[i] < other.PrePeriod_[i]) {
            return !this->z;
        }
    }
    for (auto i = 0ull; i < this->Period_.size(); ++i) {
        if (this->Period_[i] > other.Period_[i]) {
            return this->z;
        } else if (this->Period_[i] < other.Period_[i]) {
            return !this->z;
        }
    }
    return false;
}

bool LONG::operator== (LONG other) {
    this->ToOneView(other);
    return (this->z == other.z) && (this->Integer_ == other.Integer_) && (this->PrePeriod_ == other.PrePeriod_)
    &&(this->Period_ == other.Period_);
}

bool LONG::operator< (const LONG& other) {
    return *this != other && !(*this > other);
}

bool LONG::operator>=(const LONG& other) {
    return (*this == other) || (*this > other);
}

bool LONG::operator<=(const LONG& other) {
    return (*this == other) || (*this < other);
}
