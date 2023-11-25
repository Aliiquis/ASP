//
// Created by Fran on 25 Nov 2023.
//
#include <iostream>

using namespace std;

int provjeri_sortiranost(int *niz, int n) {
    if (n <= 1) return 1;
    if (niz[n - 1] < niz[n - 2]) return 0;
    return 1 * provjeri_sortiranost(niz, n - 1);
}

int main() {
    int niz[]{1, 2, 2, 2, 5};
    cout << provjeri_sortiranost(niz, 5);
    return 0;
}