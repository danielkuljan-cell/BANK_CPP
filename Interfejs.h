#ifndef INTERFEJS_H
#define INTERFEJS_H

#include <string>
using namespace std;

// kolory do konsoli, np: cout << ZIELONY << "tekst" << RESET;
const string RESET     = "\033[0m";
const string JASNY     = "\033[1m";
const string CZERWONY  = "\033[31m";
const string ZIELONY   = "\033[32m";
const string ZOLTY     = "\033[33m";
const string NIEBIESKI = "\033[34m";
const string FIOLETOWY = "\033[35m";
const string CYAN      = "\033[36m";

void wlaczKolory();
void wyczyscEkran();
void czekaj();
void czyscCin();
string wczytajUkrytePin();   // pin z gwiazdkami

void naglowekBanku();

// ramki do rysowania "kart"
void ramkaGora();
void ramkaSrodek();
void ramkaDol();
void wierszRamki(string tekst, string kolor);

string formatujIban(string iban);   // PL60 1028 1939 ...
void zagrajHavaNagila();

#endif
