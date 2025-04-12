#include "atm/atm.hpp"

ATM::ATM(BankAPI &bank_api)
    : bank_api_(bank_api)
    , authenticated_(false)
{
}

ATMErrorCode ATM::InsertCard(const std::string &card_number)
{
    current_card_ = card_number;
    authenticated_ = false;
    current_account_.clear();

    return ATMErrorCode::SUCCESS;
}

ATMErrorCode ATM::EnterPIN(const std::string &pin)
{
    if (current_card_.empty())
    {
        return ATMErrorCode::NO_CARD;
    }

    authenticated_ = bank_api_.VerifyPIN(current_card_, pin);

    return authenticated_ ? ATMErrorCode::SUCCESS : ATMErrorCode::AUTHENTICATION_FAILED;
}

ATMErrorCode ATM::SelectAccount(const std::string &account)
{
    if (!authenticated_)
    {
        return ATMErrorCode::AUTHENTICATION_FAILED;
    }

    current_account_ = account;
    return ATMErrorCode::SUCCESS;
}

ATMErrorCode ATM::CheckBalance(int &balance)
{
    if (current_account_.empty())
    {
        return ATMErrorCode::NO_ACCOUNT_SELECTED;
    }

    balance = bank_api_.GetBalance(current_card_, current_account_);
    return ATMErrorCode::SUCCESS;
}

ATMErrorCode ATM::Deposit(int amount)
{
    if (current_account_.empty())
    {
        return ATMErrorCode::NO_ACCOUNT_SELECTED;
    }

    bank_api_.Deposit(current_card_, current_account_, amount);
    return ATMErrorCode::SUCCESS;
}

ATMErrorCode ATM::Withdraw(int amount)
{
    if (current_account_.empty())
    {
        return ATMErrorCode::NO_ACCOUNT_SELECTED;
    }
    if (!bank_api_.Withdraw(current_card_, current_account_, amount))
    {
        return ATMErrorCode::INSUFFICIENT_FUNDS;
    }

    return ATMErrorCode::SUCCESS;
}