#include <cstdlib>
#include <iostream>
#include <limits>

#include "Bank.h"

void wyczyscEkran() {
    system("cls");
}

void czekaj() {
    std::cout << "\nNacisnij Enter, aby kontynuowac...";
    std::cin.get();
}

void czyscCin() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    Bank bank;

    if (bank.wczytajUzytkownikowZPliku("uzytkownicy.csv") == false) {
        std::cout << "Nie udalo sie wczytac pliku.\n";
        return 0;
    }

    while (true) {
        std::string login;
        std::string pin;

        wyczyscEkran();
        std::cout << "=== BANK ===\n";
        std::cout << "Login: ";
        std::cin >> login;
        std::cout << "PIN: ";
        std::cin >> pin;

        KontoBankowe* konto = bank.zaloguj(login, pin);

        if (konto == nullptr) {
            std::cout << "\nBledny login albo PIN.\n";
            czyscCin();
            czekaj();
            continue;
        }

        int wybor = 0;

        while (wybor != 5) {
            wyczyscEkran();
            std::cout << "Witaj, " << konto->imie << "\n\n";
            std::cout << "1. Pokaz dane\n";
            std::cout << "2. Pokaz saldo\n";
            std::cout << "3. Wplac pieniadze\n";
            std::cout << "4. Wyplac pieniadze\n";
            std::cout << "5. Wyloguj\n";
            std::cout << "Wybor: ";
            std::cin >> wybor;

            if (std::cin.fail()) {
                czyscCin();
                std::cout << "To nie jest liczba.\n";
                czekaj();
                continue;
            }

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            wyczyscEkran();

            switch (wybor) {
                case 1:
                    konto->pokazDane();
                    czekaj();
                    break;

                case 2:
                    std::cout << "Saldo: " << konto->saldo << " PLN\n";
                    czekaj();
                    break;

                case 3: {
                    double kwota;

                    std::cout << "Podaj kwote wplaty: ";
                    std::cin >> kwota;

                    if (std::cin.fail()) {
                        czyscCin();
                        std::cout << "Zla kwota.\n";
                        czekaj();
                        continue;
                    }

                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    if (konto->wplac(kwota)) {
                        bank.zapiszUzytkownikowDoPliku("uzytkownicy.csv");
                        std::cout << "Wplacono pieniadze.\n";
                    } else {
                        std::cout << "Kwota musi byc wieksza od zera.\n";
                    }

                    czekaj();
                    break;
                }

                case 4: {
                    double kwota;

                    std::cout << "Podaj kwote wyplaty: ";
                    std::cin >> kwota;

                    if (std::cin.fail()) {
                        czyscCin();
                        std::cout << "Zla kwota.\n";
                        czekaj();
                        continue;
                    }

                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    if (konto->wyplac(kwota)) {
                        bank.zapiszUzytkownikowDoPliku("uzytkownicy.csv");
                        std::cout << "Wyplacono pieniadze.\n";
                    } else {
                        std::cout << "Nie mozna wyplacic takiej kwoty.\n";
                    }

                    czekaj();
                    break;
                }

                case 5:
                    std::cout << "Wylogowano.\n";
                    break;

                default:
                    std::cout << "Nie ma takiej opcji.\n";
                    czekaj();
                    break;
            }
        }

        char koniec;

        std::cout << "\nZakonczyc program? t/n: ";
        std::cin >> koniec;

        if (koniec == 't' || koniec == 'T') {
            break;
        }
    }

    return 0;
}
