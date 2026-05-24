#ifndef BANK_H
#define BANK_H

class BankAccount {
private:
    double balance;

public:
    BankAccount();
    void deposit(double amount);
    bool withdraw(double amount);
    double getBalance();
};

#endif