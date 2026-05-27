#ifndef KONTO_BANKOWE_H
#define KONTO_BANKOWE_H
#include <string>
#include "Klient.h"
using namespace std;

class KontoBankowe {
public:
    int id;
    Klient klient;
    double saldo;
    string iban;
    string typKonta;

    void pokazDane() const;
    bool wplac(double kwota);
    bool wyplac(double kwota);
    void zabezpieczSaldo();
    string doLiniiCsv() const;
};

#endif
