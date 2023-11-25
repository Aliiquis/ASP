//
// Created by Fran on 25 Nov 2023.
//
#include <iostream>

using namespace std;

int kvazi_binomni(int n, int m) {
    if (n < 0 || m > n) return 0;
    if (n == m || m == 0) return 1;
    return kvazi_binomni(n - 1, m - 1) + m * kvazi_binomni(n - 1, m + 1);
}

int main() {
    cout << kvazi_binomni(5, 5) << endl;
    cout << kvazi_binomni(5, 0) << endl;
    cout << kvazi_binomni(1, 5) << endl;
    cout << kvazi_binomni(5, 2);
    return 0;
}