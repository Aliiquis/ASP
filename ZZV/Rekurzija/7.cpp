//
// Created by Fran on 25 Nov 2023.
//
#include <iostream>

using namespace std;

int poljeEkstrema(int *polje, int n) {
    if (n <= 2) return 1;
    if (polje[n - 3] <= polje[n - 2] && polje[n - 2] <= polje[n - 1]) return 0;
    if (polje[n - 3] >= polje[n - 2] && polje[n - 2] >= polje[n - 1]) return 0;
    return 1 * poljeEkstrema(polje, n - 1);
}

int main() {
    int polje[]{1, 2, 0, 2, 1, 2};
    cout << poljeEkstrema(polje, 6);
    return 0;
}