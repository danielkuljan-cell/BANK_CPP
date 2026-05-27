#include "Bank.h"
#include <fstream>
#include <sstream>
using namespace std;

bool Bank::wczytajUzytkownikowZPliku(string nazwaPliku) {
    ifstream plik(nazwaPliku);

    if (!plik) {
        return false;
    }

    konta.clear();

    string linia;
    getline(plik, linia);

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
