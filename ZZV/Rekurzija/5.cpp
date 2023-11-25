//
// Created by Fran on 25 Nov 2023.
//
#include <iostream>

using namespace std;

void okreni_oduzmi(int *polje, int n) {
    if (n == 0) return;
    cout << polje[n - 1] - polje[0] << ' ';
    okreni_oduzmi(polje, n - 1);
}

int main() {
    int polje[]{2, 6, 8, 11, -3, 100};
    okreni_oduzmi(polje, 5);
    return 0;
}