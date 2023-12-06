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
    sum.PrePeriod_.resize(std::max(other.PrePeriod_.size(), this->PrePeriod_.size()));
    sum.Base_ = this->Base_;
    int carry = 0;
    auto bvo = other.Period_;
    auto nvo = this->Period_;
    auto nvp = this->PrePeriod_;
    //Pre PrePeriod part
    while (this->PrePeriod_.size() > other.PrePeriod_.size()) {
        if (!other.Period_.empty()) {
            other.PrePeriod_.push_back(other.Period_[0]);
            auto tmp = other.Period_[0];
            other.Period_.erase(other.Period_.begin(), other.Period_.begin()+1);
            other.Period_.push_back(tmp);
        } else {
            other.Period_.push_back(0);
        }
    }
    while (nvp.size() < other.PrePeriod_.size()) {
        if (!nvo.empty()) {
            nvp.push_back(nvo[0]);
            auto tmp = nvo[0];
            nvo.erase(nvo.begin(), nvo.begin()+1);
            nvo.push_back(tmp);
        } else {
            nvp.push_back(0);
        }
    }
    //Period part
    unsigned long long val = 0;
    if (!this->Period_.empty() && !other.Period_.empty()) {
        val = lcd(this->Period_.size(), other.Period_.size());
    } else if (!this->Period_.empty()) {
        val = this->Period_.size();
    } else if (!other.Period_.empty()){
        val = other.Period_.size();
    }
    sum.Period_.resize(val);
    if (!other.Period_.empty()) {
        for (auto i = val / other.Period_.size(); i > 0; --i) {
            for (auto &j: bvo) {
                other.Period_.push_back(j);
            }
        }
    }
    if (!this->Period_.empty()) {
        for (auto i = val / this->Period_.size(); i > 0; --i) {
            for (auto &j: this->Period_) {
                nvo.push_back(j);
            }
        }
    }
    for (long long i = sum.Period_.size() - 1; i >= 0; --i) {
        int a = 0, b = 0;
        if (!nvo.empty()) {
            a = nvo[i];
        }
        if (!other.Period_.empty()) {
            b = other.Period_[i];
        }
        sum.Period_[i] = (a + b + carry) % Base_;
        carry = (a + b + carry) / Base_;
    }
    if (!sum.Period_.empty()) {
        sum.Period_[sum.Period_.size() - 1] += carry;
    }
    //PrePeriod part
    for (long long i = sum.PrePeriod_.size() - 1; i >= 0; --i) {
        sum.PrePeriod_[i] = ((int) nvp[i] + (int) other.PrePeriod_[i] + carry) % Base_;
        carry = ((int) nvp[i] + (int) other.PrePeriod_[i] + carry) / Base_;
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

LONG LONG::operator* (const LONG& other) const {
    LONG ans;
    auto first = this->Integer_;
    auto second = other.Integer_;
    if (first.size() > second.size()) {
        swap(first, second);
    }
    for (auto i = 0ull; i < second.size(); ++i) {
        long long carry = 0;
        LONG now;
        for (auto j = 0ull; j < first.size(); ++j) {
            long long tmp = second[i] * first[j] + carry;
            LONG ee(std::to_string(tmp%ans.Base_), ans.Base_);
            for (auto k = 0ull; k < j; ++k) {
                ee.Integer_.insert(ee.Integer_.begin(), 0);
            }
            now = now + ee;
            carry = tmp/ans.Base_;

        }
        if(carry) {
            now.Integer_.push_back(carry);
        }
        for (auto k = 0ull; k < i; ++k) {
            now.Integer_.insert(now.Integer_.begin(), 0);
        }
        ans = ans + now;
    }
    return ans;
}

LONG LONG::operator^ (int n) const {
    LONG ans("1");
    for (int i = 0; i < n; ++i) {
        ans = ans * (*this);
    }
    return ans;
}

bool LONG::operator==(const LONG& other) const {
    return other.Integer_ == this->Integer_;
}

bool LONG::operator>(LONG other) const{
    auto th = this->Integer_;
    auto oth = other.Integer_;
    std::reverse(th.begin(), th.end());
    std::reverse(oth.begin(), oth.end());
    std::stringstream ths, oths;
    for (auto &t: th) {
        ths << t;
    }
    for (auto &o: oth) {
        oths << o;
    }
    return ths.str() > oths.str();
}

bool LONG::operator<(LONG oth) const {
    return !(*this == oth) && !(*this > oth);
}

LONG LONG::to_10() const{
    LONG ans;
    ans.Base_ = 10;

}


LONG LONG::operator/ (LONG other) const {
    LONG l("0", this->Base_);
    LONG r;
    r.Integer_ = this->Integer_;
    r = r + LONG("1", this->Base_);
    r.Base_ = Base_;
    while (l + LONG("1", this->Base_) < r) {
        auto DoubledMid = l + r;
        if (DoubledMid * other > *this * LONG("2", this->Base_) || DoubledMid * other == *this * LONG("2", this->Base_)) {
            l = DoubledMid;
        } else {
            r = DoubledMid;
        }
    }
    return l;
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

