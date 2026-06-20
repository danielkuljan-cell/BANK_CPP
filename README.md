# BANK_CPP

Prosty bank w konsoli napisany w C++ (projekt studencki).

## Funkcje

- Logowanie loginem i PIN-em (dane w pliku `uzytkownicy.csv`)
- Strona glowna (pulpit) z danymi konta i saldem
- Podglad danych konta i salda
- Wplata i wyplata pieniedzy
- **Przelewy** miedzy kontami (po loginie lub IBAN - tez ze spacjami / bez "PL")
- **Zabezpieczenia:** PIN maskowany gwiazdkami, blokada po 3 blednych logowaniach,
  potwierdzenie przelewu (t/n) i mozliwosc anulowania (0 = wstecz)
- **Panel admina** (login `admin`, PIN `admin`) - podglad wszystkich kont
  i zakladanie nowych kont
- Zapis stanu kont do pliku CSV po kazdej operacji
- Kolorowy interfejs (ramki w stylu karty bankowej)
- Piosenka **Hava Nagila** przy wplacie i przelewie - gra plik `hava.wav`
  (PlaySound, w tle). Plik powstal z `hava.mp3` poleceniem:
  `ffmpeg -i hava.mp3 -acodec pcm_s16le -ar 44100 -ac 2 hava.wav`

## Kompilacja

W PowerShell uruchom:

```powershell
.\kompilowanie_bank.ps1
```

albo recznie:

```powershell
g++ main.cpp Bank.cpp KontoBankowe.cpp Interfejs.cpp -o bank.exe -lwinmm
```

> `-lwinmm` jest potrzebne do odtwarzania dzwieku (Hava Nagila).
> Piosenka gra z pliku `hava.wav` lezacego w folderze projektu.

Potem uruchom `bank.exe`.

## Pliki

- `main.cpp` - menu i obsluga uzytkownika
- `Bank.h/.cpp` - klasa Bank (logowanie, wczytywanie/zapis pliku, szukanie konta)
- `KontoBankowe.h/.cpp` - pojedyncze konto (wplata, wyplata, dane)
- `Klient.h` - dane klienta (imie, login, PIN)
- `Interfejs.h/.cpp` - wyglad konsoli (kolory, logo) i dzwiek (Hava Nagila)
- `uzytkownicy.csv` - baza kont

## Przykladowe konta (login / PIN)

- `jan` / `1234`
- `anna` / `5678`
- `danielg` / `6767`
- `admin` / `admin` - panel admina (zakladanie kont)
