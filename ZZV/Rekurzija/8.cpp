//
// Created by Fran on 25 Nov 2023.
//
#include <iostream>

using namespace std;

int provjeriZagrade(char *niz, int *zastavica) {
    if (*niz == '\0') return *zastavica == 1 ? 0 : 1;
    else *niz == '[' ? (*zastavica)++ : (*zastavica)--;
    return provjeriZagrade(++niz, zastavica);
}

int main() {
    char niz[]{'[', '[', ']', ']', '\0'};
    int zastavica = 0;
    cout << provjeriZagrade(niz, &zastavica);
}