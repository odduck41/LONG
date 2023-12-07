class A {
public:
    A(int val) : m_value(val) {}

    A operator+(A a) {
        return m_value + a.m_value;
    }

    operator int() const {
        return m_value;
    }

    operator int() {
        return m_value;
    }

private:
    int m_value;
};

int main() {
    A a = 4;  // int to A conversion is implicit
    A value = a + 3;  // A to int conversion is implicit
    return 0;
}