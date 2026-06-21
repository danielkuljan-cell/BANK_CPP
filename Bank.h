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
    KontoBankowe* znajdzKonto(string ibanLubLogin);

    // dla admina - zaklada nowe konto, false jak login juz zajety
    bool stworzKonto(string imie, string login, string pin, string typKonta);

    // dopisuje przelew do pliku historia.csv (kto komu ile)
    void dopiszHistorie(string nadawca, string odbiorca, double kwota);
};

#endif
