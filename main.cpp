#include <iostream>
#include "LONG.h"

using namespace std;

int main() {
    LONG a = "-115.167(900)";
    LONG b = "-16.06(2677)";
    LONG c = b;
    cout << (b += a) << endl;
    cout << a << endl;
    cout << b << endl;
    cout << (b -= a);
}
