#include "Bank.h"
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cctype>
using namespace std;

// wywala spacje i robi wielkie litery zeby latwiej porownac to co wpisal user
static string normalizuj(string tekst) {
    string wynik = "";

    for (char znak : tekst) {
        if (znak == ' ') {
            continue;
        }
        wynik += (char)toupper((unsigned char)znak);
    }

    return wynik;
}

bool Bank::wczytajUzytkownikowZPliku(string nazwaPliku) {
    ifstream plik(nazwaPliku);

    if (!plik) {
        return false;
    }

    konta.clear();

    string linia;
    getline(plik, linia);  // pierwsza linia to naglowek, pomijamy

    while (getline(plik, linia)) {
        stringstream ss(linia);
        KontoBankowe konto;
        string id;
        string saldo;

        getline(ss, id, ',');
        getline(ss, konto.klient.imie, ',');
        getline(ss, konto.klient.login, ',');
        getline(ss, konto.klient.pin, ',');
        getline(ss, saldo, ',');
        getline(ss, konto.iban, ',');
        getline(ss, konto.typKonta, ',');

        konto.id = stoi(id);
        konto.saldo = stod(saldo);
        konto.zabezpieczSaldo();

        konta.push_back(konto);
    }

    return true;
}

bool Bank::zapiszUzytkownikowDoPliku(string nazwaPliku) {
    ofstream plik(nazwaPliku);

    if (!plik) {
        return false;
    }

    plik << "ID,Imie,Login,PIN,Money,IBAN,TypKonta\n";

    for (const auto& konto : konta) {
        plik << konto.doLiniiCsv() << "\n";
    }

    return true;
}

KontoBankowe* Bank::zaloguj(string login, string pin) {
    for (auto& konto : konta) {
        if (konto.klient.login == login && konto.klient.pin == pin) {
            return &konto;
        }
    }

    return nullptr;
}

// szuka po loginie albo IBAN (tez ze spacjami, tez bez PL)
KontoBankowe* Bank::znajdzKonto(string ibanLubLogin) {
    string szukane = normalizuj(ibanLubLogin);

    for (auto& konto : konta) {
        string login = normalizuj(konto.klient.login);
        string iban = normalizuj(konto.iban);

        if (login == szukane || iban == szukane) {
            return &konto;
        }
        if ("PL" + szukane == iban) {  // user wpisal IBAN bez PL
            return &konto;
        }
    }

    return nullptr;
}

bool Bank::stworzKonto(string imie, string login, string pin, string typKonta) {
    // sprawdzamy czy taki login juz jest
    for (auto& konto : konta) {
        if (konto.klient.login == login) {
            return false;
        }
    }

    // nowe id = najwieksze + 1
    int maxId = 0;
    for (auto& konto : konta) {
        if (konto.id > maxId) {
            maxId = konto.id;
        }
    }

    KontoBankowe nowe;
    nowe.id = maxId + 1;
    nowe.klient.imie = imie;
    nowe.klient.login = login;
    nowe.klient.pin = pin;
    nowe.saldo = 0;
    nowe.typKonta = typKonta;

    // prosty numer konta - losowe cyfry (to nie prawdziwy IBAN, ale starczy)
    nowe.iban = "PL";
    for (int i = 0; i < 20; i++) {
        nowe.iban += to_string(rand() % 10);
    }

    konta.push_back(nowe);
    return true;
}
