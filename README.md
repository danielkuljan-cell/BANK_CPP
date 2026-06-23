# BANK_CPP

Siema! To moj projekt na studia - taki maly bank, tyle ze caly siedzi w konsoli i jest
napisany w C++. Mozesz sie zalogowac, sprawdzic kase, cos wplacic albo wyplacic, zrobic
przelew do kogos innego, a admin podejrzy wszystkie konta. No i leci muzyka, zeby bylo
smieszniej :)

## Co to potrafi

- Logowanie loginem i PIN-em. PIN sie maskuje gwiazdkami, tak jak w bankomacie.
- Pulpit z Twoimi danymi i saldem, narysowany w ramkach jak prawdziwa karta bankowa.
- Wplata i wyplata kasy.
- **Przelewy** do innych kont - po loginie albo po IBAN (mozesz wpisac ze spacjami albo
  bez "PL", program i tak ogarnie).
- **Zabezpieczenia:** blokada po 3 zlych logowaniach, potwierdzenie przelewu (t/n)
  i mozliwosc wycofania sie (0 = wstecz).
- **Panel admina** (login `admin`, PIN `admin`) - widzi wszystkie konta, zaklada nowe
  i ma **historie przelewow** (kto komu ile przelal).
- Wszystko zapisuje sie do pliku CSV po kazdej operacji, wiec po wylaczeniu nic nie ginie.
- **Muzyka w tle** (`tlo.wav`) leci od startu w kolko.
- **Hava Nagila** (`hava.wav`) przy wplacie i przelewie - taka mala nagroda.
- **Placz** (`plakal.wav`) przy klikaniu po menu - gra rownoczesnie z muzyka tla,
  nie wylacza jej.

## Jak to odpalic

W PowerShell:

```powershell
.\kompilowanie_bank.ps1
```

albo recznie:

```powershell
g++ main.cpp Bank.cpp KontoBankowe.cpp Interfejs.cpp -o bank.exe -lwinmm
```

`-lwinmm` jest potrzebne do dzwiekow. Pliki `.wav` musza lezec w tym samym folderze co
program. Pliki dzwiekowe robie z mp3, np.:
`ffmpeg -i hava.mp3 -acodec pcm_s16le -ar 44100 -ac 2 hava.wav`

> Wazne: jak cos zmienisz w kodzie, musisz przekompilowac od nowa, inaczej `bank.exe`
> zostanie stary. I zamknij bank przed kompilacja, bo zalaczony plik jest zablokowany.

Potem odpalasz `bank.exe`.

## Co jest w ktorym pliku

- `main.cpp` - menu i cala obsluga uzytkownika
- `Bank.h/.cpp` - klasa Bank (logowanie, czytanie/zapis pliku, szukanie konta)
- `KontoBankowe.h/.cpp` - jedno konto (wplata, wyplata, dane)
- `Klient.h` - dane klienta (imie, login, PIN)
- `Interfejs.h/.cpp` - wyglad konsoli (kolory, logo, ramki) i dzwieki
- `uzytkownicy.csv` - baza kont

## Konta do testu (login / PIN)

- `jan` / `1234`
- `anna` / `5678`
- `danielg` / `6767`
- `admin` / `admin` - panel admina
