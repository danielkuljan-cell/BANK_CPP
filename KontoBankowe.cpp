#include "KontoBankowe.h"
#include <iostream>
#include <sstream>
using namespace std;

void KontoBankowe::pokazDane() const {
    cout << "\nDANE KONTA\n";
    cout << "Imie i nazwisko: " << klient.imie << "\n";
    cout << "Login: " << klient.login << "\n";
    cout << "IBAN: " << iban << "\n";
    cout << "Typ konta: " << typKonta << "\n";
    cout << "Saldo: " << saldo << " PLN\n";
}

bool KontoBankowe::wplac(double kwota) {
    zabezpieczSaldo();

    if (kwota <= 0) {
        return false;
    }

    saldo += kwota;
    return true;
}

bool KontoBankowe::wyplac(double kwota) {
    zabezpieczSaldo();

    if (kwota <= 0 || kwota > saldo) {
        return false;
    }

    saldo -= kwota;
    return true;
}

void KontoBankowe::zabezpieczSaldo() {
    if (saldo < 0) {
        saldo = 0;
    }
}

string KontoBankowe::doLiniiCsv() const {
    stringstream linia;

    linia << id << ","
          << klient.imie << ","
          << klient.login << ","
          << klient.pin << ","
          << saldo << ","
          << iban << ","
          << typKonta;

    return linia.str();
}
