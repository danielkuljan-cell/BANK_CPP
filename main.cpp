#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "httplib.h"
#include "Bank.h"

using namespace httplib;
using namespace std;

// testowy push
string readFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) return "";
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

int main() {
    Server svr;
    BankAccount myAccount;

    // Serwowanie strony głównej (HTML)
    svr.Get("/", [](const Request& req, Response& res) {
        res.set_content(readFile("index.html"), "text/html");
    });

    // Serwowanie styli CSS
    svr.Get("/style.css", [](const Request& req, Response& res) {
        res.set_content(readFile("style.css"), "text/css");
    });

    // API: Pobieranie balansu
    svr.Get("/api/balance", [&](const Request& req, Response& res) {
        res.set_content(to_string(myAccount.getBalance()), "text/plain");
    });

    // API: Wpłata
    svr.Post("/api/deposit", [&](const Request& req, Response& res) {
        if (req.has_param("amount")) {
            double amount = stod(req.get_param_value("amount"));
            myAccount.deposit(amount);
            res.set_content("Wplacono pomyslnie!", "text/plain");
        }
    });

    // API: Wypłata
    svr.Post("/api/withdraw", [&](const Request& req, Response& res) {
        if (req.has_param("amount")) {
            double amount = stod(req.get_param_value("amount"));
            if (myAccount.withdraw(amount)) {
                res.set_content("Wyplacono pomyslnie!", "text/plain");
            } else {
                res.set_content("Brak srodkow!", "text/plain");
            }
        }
    });

    cout << "Serwer dziala! Otworz podglad w Replit." << endl;
    // 0.0.0.0 pozwala na działanie w chmurze, port 8080
    svr.listen("0.0.0.0", 8080); 
    
    return 0;
}