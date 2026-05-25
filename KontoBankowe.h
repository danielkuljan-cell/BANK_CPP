#ifndef KONTO_BANKOWE_H
#define KONTO_BANKOWE_H

#include <string>

class KontoBankowe {
public:
    int id;
    std::string imie;
    std::string login;
    std::string pin;
    double saldo;
    std::string iban;
    std::string typKonta;

    void pokazDane();
    bool wplac(double kwota);
    bool wyplac(double kwota);
    void zabezpieczSaldo();
    std::string doLiniiCsv();
};

#endif
