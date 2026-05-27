#ifndef BANK_H
#define BANK_H
#include <string>
#include <vector>
#include "KontoBankowe.h"
using namespace std;

class Bank {
public:
    vector<KontoBankowe> konta;

    bool wczytajUzytkownikowZPliku(string nazwaPliku);
    bool zapiszUzytkownikowDoPliku(string nazwaPliku);
    KontoBankowe* zaloguj(string login, string pin);
};

#endif
