#include "Bank.h"

#include <fstream>
#include <sstream>

bool Bank::wczytajUzytkownikowZPliku(std::string nazwaPliku) {
    std::ifstream plik(nazwaPliku);

    if (!plik) {
        return false;
    }

    konta.clear();

    std::string linia;
    std::getline(plik, linia);

    while (std::getline(plik, linia)) {
        std::stringstream ss(linia);
        KontoBankowe konto;
        std::string id;
        std::string saldo;

        std::getline(ss, id, ',');
        std::getline(ss, konto.imie, ',');
        std::getline(ss, konto.login, ',');
        std::getline(ss, konto.pin, ',');
        std::getline(ss, saldo, ',');
        std::getline(ss, konto.iban, ',');
        std::getline(ss, konto.typKonta, ',');

        konto.id = std::stoi(id);
        konto.saldo = std::stod(saldo);
        konto.zabezpieczSaldo();

        konta.push_back(konto);
    }

    return true;
}

bool Bank::zapiszUzytkownikowDoPliku(std::string nazwaPliku) {
    std::ofstream plik(nazwaPliku);

    if (!plik) {
        return false;
    }

    plik << "ID,Imie,Login,PIN,Money,IBAN,TypKonta\n";

    for (int i = 0; i < konta.size(); i++) {
        plik << konta[i].doLiniiCsv() << "\n";
    }

    return true;
}

KontoBankowe* Bank::zaloguj(std::string login, std::string pin) {
    for (int i = 0; i < konta.size(); i++) {
        if (konta[i].login == login && konta[i].pin == pin) {
            return &konta[i];
        }
    }

    return nullptr;
}
