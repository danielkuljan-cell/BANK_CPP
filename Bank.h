#ifndef BANK_H
#define BANK_H

#include <string>
#include <vector>

#include "KontoBankowe.h"

class Bank {
public:
    std::vector<KontoBankowe> konta;

    bool wczytajUzytkownikowZPliku(std::string nazwaPliku);
    bool zapiszUzytkownikowDoPliku(std::string nazwaPliku);
    KontoBankowe* zaloguj(std::string login, std::string pin);
};

#endif
