#include "Bank.h"

BankAccount::BankAccount() {
    balance = 0.0;
}

void BankAccount::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
    }
}

bool BankAccount::withdraw(double amount) {
    if (amount > 0 && balance >= amount) {
        balance -= amount;
        return true;
    }
    return false;
}

double BankAccount::getBalance() {
    return balance;
}