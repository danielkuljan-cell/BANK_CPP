#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <limits>

#include "Bank.h"
#include "Interfejs.h"

using namespace std;

// liczba na tekst z groszami, np. "8450.00"
string kwotaNaTekst(double kwota) {
    ostringstream ss;
    ss << fixed << setprecision(2) << kwota;
    return ss.str();
}

// strona glowna po zalogowaniu - taka karta + menu
void pokazPulpit(KontoBankowe* konto) {
    naglowekBanku();
    cout << "\n";

    ramkaGora();
    wierszRamki("  BANK - TWOJE KONTO", ZOLTY + JASNY);
    ramkaSrodek();
    wierszRamki("  Wlasciciel : " + konto->klient.imie, "");
    wierszRamki("  Typ konta  : " + konto->typKonta, "");
    wierszRamki("  IBAN       : " + formatujIban(konto->iban), "");
    ramkaSrodek();
    wierszRamki("  SALDO:  " + kwotaNaTekst(konto->saldo) + " PLN", ZIELONY + JASNY);
    ramkaDol();

    cout << "\n";

    ramkaGora();
    wierszRamki("  MENU", ZOLTY + JASNY);
    ramkaSrodek();
    wierszRamki("  [1] Pokaz dane konta", "");
    wierszRamki("  [2] Pokaz saldo", "");
    wierszRamki("  [3] Wplac pieniadze", "");
    wierszRamki("  [4] Wyplac pieniadze", "");
    wierszRamki("  [5] Przelew", "");
    wierszRamki("  [6] Wyloguj", "");
    ramkaDol();

    cout << "\n  Wybor: ";
}

// lista do kogo mozna zrobic przelew (wszyscy oprocz nas)
void pokazOdbiorcow(Bank& bank, KontoBankowe* konto) {
    ramkaGora();
    wierszRamki("  DOSTEPNI ODBIORCY (wpisz login lub IBAN)", ZOLTY + JASNY);
    ramkaSrodek();

    for (KontoBankowe& k : bank.konta) {
        if (k.iban == konto->iban) {
            continue;
        }

        string login = k.klient.login;
        while (login.length() < 8) {
            login += " ";
        }

        wierszRamki("  " + login + "  " + formatujIban(k.iban), "");
    }

    ramkaDol();
    cout << "\n";
}

// admin: wypisuje wszystkie konta
void pokazWszystkieKonta(Bank& bank) {
    ramkaGora();
    wierszRamki("  WSZYSTKIE KONTA", ZOLTY + JASNY);
    ramkaSrodek();

    for (KontoBankowe& k : bank.konta) {
        string login = k.klient.login;
        while (login.length() < 8) {
            login += " ";
        }

        wierszRamki("  " + to_string(k.id) + ". " + login + " " + kwotaNaTekst(k.saldo) + " PLN", "");
    }

    ramkaDol();
}

// menu admina - moze ogladac konta i zakladac nowe
void panelAdmina(Bank& bank) {
    int wybor = 0;

    while (wybor != 3) {
        wyczyscEkran();
        naglowekBanku();
        cout << "\n";
        ramkaGora();
        wierszRamki("  PANEL ADMINA", ZOLTY + JASNY);
        ramkaSrodek();
        wierszRamki("  [1] Pokaz wszystkie konta", "");
        wierszRamki("  [2] Stworz nowe konto", "");
        wierszRamki("  [3] Wyloguj", "");
        ramkaDol();
        cout << "\n  Wybor: ";
        cin >> wybor;

        if (cin.fail()) {
            czyscCin();
            cout << CZERWONY << "To nie jest liczba." << RESET << "\n";
            czekaj();
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        wyczyscEkran();

        switch (wybor) {
            case 1:
                pokazWszystkieKonta(bank);
                czekaj();
                break;

            case 2: {
                string imie, login, pin, typ;

                cout << "Imie i nazwisko: ";
                getline(cin, imie);
                cout << "Login: ";
                getline(cin, login);
                cout << "PIN: ";
                getline(cin, pin);
                cout << "Typ konta (np. Osobiste): ";
                getline(cin, typ);

                if (typ.empty()) {
                    typ = "Osobiste";
                }

                if (imie.empty() || login.empty() || pin.empty()) {
                    cout << CZERWONY << "Dane nie moga byc puste." << RESET << "\n";
                } else if (bank.stworzKonto(imie, login, pin, typ)) {
                    bank.zapiszUzytkownikowDoPliku("uzytkownicy.csv");
                    cout << ZIELONY << "Konto utworzone!" << RESET << "\n";
                } else {
                    cout << CZERWONY << "Taki login juz istnieje." << RESET << "\n";
                }

                czekaj();
                break;
            }

            case 3:
                cout << "Wylogowano admina.\n";
                break;

            default:
                cout << CZERWONY << "Nie ma takiej opcji." << RESET << "\n";
                czekaj();
                break;
        }
    }
}

int main() {
    wlaczKolory();
    srand(time(NULL));   // do losowania numeru konta

    Bank bank;

    if (bank.wczytajUzytkownikowZPliku("uzytkownicy.csv") == false) {
        cout << CZERWONY << "Nie udalo sie wczytac pliku." << RESET << "\n";
        return 0;
    }

    int bledneProby = 0;

    while (true) {
        string login;
        string pin;

        wyczyscEkran();
        naglowekBanku();
        cout << "\n";
        ramkaGora();
        wierszRamki("  LOGOWANIE DO KONTA", ZOLTY + JASNY);
        ramkaDol();
        cout << "Login: ";
        cin >> login;
        cout << "PIN: ";
        pin = wczytajUkrytePin();

        // admin ma swoj wlasny panel
        if (login == "admin" && pin == "admin") {
            bledneProby = 0;
            panelAdmina(bank);
            continue;
        }

        KontoBankowe* konto = bank.zaloguj(login, pin);

        if (konto == nullptr) {
            bledneProby++;

            cout << CZERWONY << "\nBledny login albo PIN. Pozostalo prob: "
                 << (3 - bledneProby) << RESET << "\n";

            // 3 zle proby i koniec
            if (bledneProby >= 3) {
                cout << CZERWONY << JASNY
                     << "Za duzo blednych prob! Dostep zablokowany." << RESET << "\n";
                czekaj();
                return 0;
            }

            czyscCin();
            czekaj();
            continue;
        }

        bledneProby = 0;

        int wybor = 0;

        while (wybor != 6) {
            wyczyscEkran();
            pokazPulpit(konto);
            cin >> wybor;

            if (cin.fail()) {
                czyscCin();
                cout << CZERWONY << "To nie jest liczba." << RESET << "\n";
                czekaj();
                continue;
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            wyczyscEkran();

            switch (wybor) {
                case 1:
                    konto->pokazDane();
                    czekaj();
                    break;

                case 2:
                    cout << "Saldo: " << ZIELONY << JASNY
                         << kwotaNaTekst(konto->saldo) << " PLN" << RESET << "\n";
                    czekaj();
                    break;

                case 3: {
                    double kwota;

                    cout << "Podaj kwote wplaty: ";
                    cin >> kwota;

                    if (cin.fail()) {
                        czyscCin();
                        cout << CZERWONY << "Zla kwota." << RESET << "\n";
                        czekaj();
                        continue;
                    }

                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    double saldoPrzed = konto->saldo;

                    if (konto->wplac(kwota)) {
                        bank.zapiszUzytkownikowDoPliku("uzytkownicy.csv");

                        ramkaGora();
                        wierszRamki("  WPLATA ZAKSIEGOWANA", ZIELONY + JASNY);
                        ramkaSrodek();
                        wierszRamki("  Wlasciciel  : " + konto->klient.imie, "");
                        wierszRamki("  Kwota wplaty:  +" + kwotaNaTekst(kwota) + " PLN", "");
                        wierszRamki("  Saldo przed :   " + kwotaNaTekst(saldoPrzed) + " PLN", "");
                        wierszRamki("  Saldo teraz :   " + kwotaNaTekst(konto->saldo) + " PLN", ZIELONY + JASNY);
                        ramkaDol();

                        zagrajHavaNagila();
                    } else {
                        cout << CZERWONY << "Kwota musi byc wieksza od zera." << RESET << "\n";
                    }

                    czekaj();
                    break;
                }

                case 4: {
                    double kwota;

                    cout << "Podaj kwote wyplaty: ";
                    cin >> kwota;

                    if (cin.fail()) {
                        czyscCin();
                        cout << CZERWONY << "Zla kwota." << RESET << "\n";
                        czekaj();
                        continue;
                    }

                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    if (konto->wyplac(kwota)) {
                        bank.zapiszUzytkownikowDoPliku("uzytkownicy.csv");
                        cout << ZIELONY << "Wyplacono pieniadze." << RESET << "\n";
                    } else {
                        cout << CZERWONY << "Nie mozna wyplacic takiej kwoty." << RESET << "\n";
                    }

                    czekaj();
                    break;
                }

                case 5: {
                    pokazOdbiorcow(bank, konto);

                    // bierzemy cala linie - inaczej IBAN ze spacjami sie rozjedzie
                    cout << "Podaj login lub IBAN odbiorcy (0 = wstecz): ";
                    string odbiorcaId;
                    getline(cin, odbiorcaId);

                    if (odbiorcaId == "0" || odbiorcaId.empty()) {
                        break;
                    }

                    KontoBankowe* odbiorca = bank.znajdzKonto(odbiorcaId);

                    if (odbiorca == nullptr) {
                        cout << CZERWONY << "Nie znaleziono odbiorcy o takim loginie/IBAN." << RESET << "\n";
                        czekaj();
                        break;
                    }
                    if (odbiorca == konto) {
                        cout << CZERWONY << "Nie mozesz zrobic przelewu na swoje wlasne konto." << RESET << "\n";
                        czekaj();
                        break;
                    }

                    cout << "Podaj kwote przelewu: ";
                    double kwota;
                    cin >> kwota;

                    if (cin.fail()) {
                        czyscCin();
                        cout << CZERWONY << "Zla kwota." << RESET << "\n";
                        czekaj();
                        break;
                    }

                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    if (kwota <= 0) {
                        cout << CZERWONY << "Kwota musi byc wieksza od zera." << RESET << "\n";
                        czekaj();
                        break;
                    }
                    if (kwota > konto->saldo) {
                        cout << CZERWONY << "Nie masz wystarczajacych srodkow na koncie." << RESET << "\n";
                        czekaj();
                        break;
                    }

                    // pytamy czy na pewno, zeby sie nie pomylic
                    cout << "\nPrzelac " << ZOLTY << kwotaNaTekst(kwota) << " PLN" << RESET
                         << " do: " << ZOLTY << odbiorca->klient.imie << RESET << "?  (t/n): ";
                    char potwierdzenie;
                    cin >> potwierdzenie;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    if (potwierdzenie != 't' && potwierdzenie != 'T') {
                        cout << CZERWONY << "Przelew anulowany." << RESET << "\n";
                        czekaj();
                        break;
                    }

                    double saldoPrzed = konto->saldo;

                    konto->wyplac(kwota);
                    odbiorca->wplac(kwota);
                    bank.zapiszUzytkownikowDoPliku("uzytkownicy.csv");

                    ramkaGora();
                    wierszRamki("  PRZELEW WYKONANY", ZIELONY + JASNY);
                    ramkaSrodek();
                    wierszRamki("  Odbiorca   : " + odbiorca->klient.imie, "");
                    wierszRamki("  Kwota      :  -" + kwotaNaTekst(kwota) + " PLN", "");
                    wierszRamki("  Saldo przed:   " + kwotaNaTekst(saldoPrzed) + " PLN", "");
                    wierszRamki("  Saldo teraz:   " + kwotaNaTekst(konto->saldo) + " PLN", ZIELONY + JASNY);
                    ramkaDol();

                    zagrajHavaNagila();

                    czekaj();
                    break;
                }

                case 6:
                    cout << "Wylogowano.\n";
                    break;

                default:
                    cout << CZERWONY << "Nie ma takiej opcji." << RESET << "\n";
                    czekaj();
                    break;
            }
        }

        char koniec;

        cout << "\nZakonczyc program? t/n: ";
        cin >> koniec;

        if (koniec == 't' || koniec == 'T') {
            break;
        }
    }

    return 0;
}
