#pragma once

#include <string>

enum class ATMErrorCode
{
    SUCCESS = 0,
    NO_CARD,
    AUTHENTICATION_FAILED,
    NO_ACCOUNT_SELECTED,
    INSUFFICIENT_FUNDS
};

class BankAPI
{
public:
    virtual ~BankAPI() = default;

    virtual bool VerifyPIN(const std::string &card_number, const std::string &pin) = 0;
    virtual int GetBalance(const std::string &card_number, const std::string &account) = 0;
    virtual void Deposit(const std::string &card_number, const std::string &account, int amount) = 0;
    virtual bool Withdraw(const std::string &card_number, const std::string &account, int amount) = 0;
};

class ATM
{
public:
    explicit ATM(BankAPI &bank_api);

    ATMErrorCode InsertCard(const std::string &card_number);
    ATMErrorCode EnterPIN(const std::string &pin);
    ATMErrorCode SelectAccount(const std::string &account);
    ATMErrorCode CheckBalance(int &balance);
    ATMErrorCode Deposit(int amount);
    ATMErrorCode Withdraw(int amount);

private:
    BankAPI &bank_api_;
    std::string current_card_;
    std::string current_account_;
    bool authenticated_;
};