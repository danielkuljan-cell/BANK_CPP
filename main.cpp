#include <cstdlib>
#include <iostream>
#include <limits>

#include "Bank.h"

using namespace std;

void wyczyscEkran() {
    system("cls");
}

void czekaj() {
    cout << "\nNacisnij Enter, aby kontynuowac...";
    cin.get();
}

void czyscCin() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    Bank bank;

    if (bank.wczytajUzytkownikowZPliku("uzytkownicy.csv") == false) {
        cout << "Nie udalo sie wczytac pliku.\n";
        return 0;
    }

    while (true) {
        string login;
        string pin;

        wyczyscEkran();
        cout << "=== BANK ===\n";
        cout << "Login: ";
        cin >> login;
        cout << "PIN: ";
        cin >> pin;

        KontoBankowe* konto = bank.zaloguj(login, pin);

        if (konto == nullptr) {
            cout << "\nBledny login albo PIN.\n";
            czyscCin();
            czekaj();
            continue;
        }

        int wybor = 0;

        while (wybor != 5) {
            wyczyscEkran();
            cout << "Witaj, " << konto->klient.imie << "\n\n";
            cout << "1. Pokaz dane\n";
            cout << "2. Pokaz saldo\n";
            cout << "3. Wplac pieniadze\n";
            cout << "4. Wyplac pieniadze\n";
            cout << "5. Wyloguj\n";
            cout << "Wybor: ";
            cin >> wybor;

            if (cin.fail()) {
                czyscCin();
                cout << "To nie jest liczba.\n";
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
                    cout << "Saldo: " << konto->saldo << " PLN\n";
                    czekaj();
                    break;

                case 3: {
                    double kwota;

                    cout << "Podaj kwote wplaty: ";
                    cin >> kwota;

                    if (cin.fail()) {
                        czyscCin();
                        cout << "Zla kwota.\n";
                        czekaj();
                        continue;
                    }

                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    if (konto->wplac(kwota)) {
                        bank.zapiszUzytkownikowDoPliku("uzytkownicy.csv");
                        cout << "Wplacono pieniadze.\n";
                    } else {
                        cout << "Kwota musi byc wieksza od zera.\n";
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
                        cout << "Zla kwota.\n";
                        czekaj();
                        continue;
                    }

                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    if (konto->wyplac(kwota)) {
                        bank.zapiszUzytkownikowDoPliku("uzytkownicy.csv");
                        cout << "Wyplacono pieniadze.\n";
                    } else {
                        cout << "Nie mozna wyplacic takiej kwoty.\n";
                    }

                    czekaj();
                    break;
                }

                case 5:
                    cout << "Wylogowano.\n";
                    break;

                default:
                    cout << "Nie ma takiej opcji.\n";
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
