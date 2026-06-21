// windows.h musi byc pierwszy, inaczej wywala blad z typem "byte"
#include <windows.h>
#include <mmsystem.h>   // PlaySound - trzeba linkowac -lwinmm

#include "Interfejs.h"

#include <iostream>
#include <limits>
#include <conio.h>      // _getch - czyta klawisz bez pokazywania go

using namespace std;

// stare MinGW czasem nie ma tej stalej
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

const int szerokosc = 46;   // ile miesci sie tekstu w ramce

void wlaczKolory() {
    // wlaczamy kolory (kody ANSI) w konsoli
    HANDLE uchwyt = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD tryb = 0;
    GetConsoleMode(uchwyt, &tryb);
    SetConsoleMode(uchwyt, tryb | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

    // UTF-8 zeby ramki (╔ ═ ║) sie ladnie rysowaly
    SetConsoleOutputCP(CP_UTF8);
}

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

string wczytajUkrytePin() {
    string pin = "";

    while (true) {
        char znak = _getch();

        if (znak == '\r') {     // enter konczy
            break;
        }
        if (znak == 8) {        // backspace
            if (!pin.empty()) {
                pin.pop_back();
                cout << "\b \b";
            }
            continue;
        }

        pin += znak;
        cout << "*";
    }

    cout << "\n";
    return pin;
}

void naglowekBanku() {
    cout << ZOLTY << JASNY;
    cout << "  ____    _    _   _ _  __\n";
    cout << " | __ )  / \\  | \\ | | |/ /\n";
    cout << " |  _ \\ / _ \\ |  \\| | ' / \n";
    cout << " | |_) / ___ \\| |\\  | . \\ \n";
    cout << " |____/_/   \\_\\_| \\_|_|\\_\\\n";
    cout << RESET;
    cout << CYAN << "        Twoj bank w terminalu\n" << RESET;
}

void ramkaGora() {
    cout << CYAN << "╔";
    for (int i = 0; i < szerokosc + 2; i++) cout << "═";
    cout << "╗" << RESET << "\n";
}

void ramkaSrodek() {
    cout << CYAN << "╠";
    for (int i = 0; i < szerokosc + 2; i++) cout << "═";
    cout << "╣" << RESET << "\n";
}

void ramkaDol() {
    cout << CYAN << "╚";
    for (int i = 0; i < szerokosc + 2; i++) cout << "═";
    cout << "╝" << RESET << "\n";
}

void wierszRamki(string tekst, string kolor) {
    cout << CYAN << "║ " << RESET;
    cout << kolor << tekst << RESET;

    // dopelniamy spacjami zeby ramka byla rowna
    for (int i = (int)tekst.length(); i < szerokosc; i++) {
        cout << " ";
    }

    cout << CYAN << " ║" << RESET << "\n";
}

string formatujIban(string iban) {
    // spacja co 4 znaki, np. PL60 1028 1939 ...
    string wynik = "";

    for (int i = 0; i < (int)iban.length(); i++) {
        if (i > 0 && i % 4 == 0) {
            wynik += " ";
        }
        wynik += iban[i];
    }

    return wynik;
}

void wlaczMuzykeTla() {
    // muzyka w tle w kolko (SND_LOOP). PlaySound ma jeden kanal, wiec
    // jak zagra hava.wav to tlo samo ucichnie - nie nakladaja sie.
    PlaySoundA("tlo.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

void zagrajHavaNagila() {
    // gra hava.wav (przerywa muzyke tla, bo PlaySound ma jeden kanal)
    PlaySoundA("hava.wav", NULL, SND_FILENAME | SND_ASYNC);
}
