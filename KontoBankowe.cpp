#include "KontoBankowe.h"
#include <iomanip>
#include <iostream>
#include <sstream>




void KontoBankowe::pokazDane() {
    zabezpieczSaldo();

    std::cout << "\nDANE KONTA\n";
    std::cout << "Imie i nazwisko: " << imie << "\n";
    std::cout << "Login: " << login << "\n";
    std::cout << "IBAN: " << iban << "\n";
    std::cout << "Typ konta: " << typKonta << "\n";
    std::cout << "Saldo: " << std::fixed << std::setprecision(2) << saldo << " PLN\n";
}

bool KontoBankowe::wplac(double kwota) {
    zabezpieczSaldo();

    if (kwota <= 0) {
        return false;
    }

    saldo = saldo + kwota;
    return true;
}

bool KontoBankowe::wyplac(double kwota) {
    zabezpieczSaldo();

    if (kwota <= 0 || kwota > saldo) {
        return false;
    }

    saldo = saldo - kwota;
    return true;
}

void KontoBankowe::zabezpieczSaldo() {
    if (saldo < 0) {
        saldo = 0;
    }
}

std::string KontoBankowe::doLiniiCsv() {
    zabezpieczSaldo();

    std::stringstream linia;

    linia << id << ","
          << imie << ","
          << login << ","
          << pin << ","
          << std::fixed << std::setprecision(2) << saldo << ","
          << iban << ","
          << typKonta;

    return linia.str();
}
