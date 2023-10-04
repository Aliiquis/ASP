#include <iostream>

using namespace std;

class Plocica {
private:
    int a, b;
public:
    Plocica(int a, int b) : a(a), b(b) {};

    friend Plocica operator+(Plocica &prva, Plocica &druga);

    friend ostream &operator<<(ostream &out, Plocica &plocica);
};

Plocica operator+(Plocica &prva, Plocica &druga) {
    Plocica nova{0, 0};
    nova.a = prva.a + druga.a;
    nova.b = prva.b + druga.b;
    return nova;
}

ostream &operator<<(ostream &out, Plocica &plocica) {
    return out << plocica.a << " " << plocica.b;
}

int main() {
    Plocica prva{1, 2};
    Plocica druga{3, 4};
    Plocica treca = prva + druga;
    cout << treca << endl;
    return 0;
}
