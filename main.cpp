#include <iostream>
#include "LONG.h"

using namespace std;

int main() {
    LONG d = "-99.105(223633174128)";
    LONG a = "115.167(900)";
    LONG b = "-16.06(2677)";
    LONG c = b;
    cout << (b + a) << endl << b << endl;
    cout << (b - a);
}
