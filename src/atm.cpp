#include "atm/atm.hpp"

#include <algorithm>

namespace atm
{

ATM::ATM(BankAPI &bank_api)
    : bank_api_(bank_api)
    , current_card_("")
    , current_account_("")
    , user_token_("")
    , authenticated_(false)
{
}

ErrorCode ATM::InsertCard(const std::string &card_number)
{
    if (card_number.empty())
    {
        return ErrorCode::INVALID_CARD;
    }
    if (!current_card_.empty())
    {
        return ErrorCode::CARD_ALREADY_INSERTED;
    }

    current_card_ = card_number;
    authenticated_ = false;
    user_token_.clear();
    current_account_.clear();

    return ErrorCode::SUCCESS;
}

ErrorCode ATM::RemoveCard()
{
    if (current_card_.empty())
    {
        return ErrorCode::NO_CARD;
    }

    current_card_.clear();
    authenticated_ = false;
    user_token_.clear();
    current_account_.clear();

    return ErrorCode::SUCCESS;
}

ErrorCode ATM::EnterPIN(const std::string &pin)
{
    if (current_card_.empty())
    {
        return ErrorCode::NO_CARD;
    }

    user_token_ = bank_api_.VerifyPIN(current_card_, pin);
    authenticated_ = !user_token_.empty();

    return authenticated_ ? ErrorCode::SUCCESS : ErrorCode::AUTHENTICATION_FAILED;
}

ErrorCode ATM::GetAccounts(std::vector<std::string> &accounts)
{
    if (!authenticated_)
    {
        return ErrorCode::AUTHENTICATION_FAILED;
    }

    user_accounts_ = bank_api_.GetUserAccounts(user_token_);
    accounts = user_accounts_;

    return ErrorCode::SUCCESS;
}

ErrorCode ATM::SelectAccount(const std::string &account)
{
    if (!authenticated_)
    {
        return ErrorCode::AUTHENTICATION_FAILED;
    }
    if (account.empty())
    {
        return ErrorCode::NO_ACCOUNT_SELECTED;
    }
    if (std::find(user_accounts_.begin(), user_accounts_.end(), account) == user_accounts_.end())
    {
        return ErrorCode::INVALID_ACCOUNT;
    }

    current_account_ = account;
    return ErrorCode::SUCCESS;
}

ErrorCode ATM::GetBalance(int &balance)
{
    if (current_card_.empty())
    {
        return ErrorCode::NO_CARD;
    }
    if (current_account_.empty())
    {
        return ErrorCode::NO_ACCOUNT_SELECTED;
    }

    balance = bank_api_.GetBalance(current_account_, user_token_);
    return ErrorCode::SUCCESS;
}

ErrorCode ATM::Deposit(int amount)
{
    if (amount <= 0)
    {
        return ErrorCode::INVALID_AMOUNT;
    }
    if (current_card_.empty())
    {
        return ErrorCode::NO_CARD;
    }
    if (current_account_.empty())
    {
        return ErrorCode::NO_ACCOUNT_SELECTED;
    }

    bank_api_.Deposit(current_account_, amount, user_token_);
    return ErrorCode::SUCCESS;
}

ErrorCode ATM::Withdraw(int amount)
{
    if (amount <= 0)
    {
        return ErrorCode::INVALID_AMOUNT;
    }
    if (current_card_.empty())
    {
        return ErrorCode::NO_CARD;
    }
    if (current_account_.empty())
    {
        return ErrorCode::NO_ACCOUNT_SELECTED;
    }
    if (!bank_api_.Withdraw(current_account_, amount, user_token_))
    {
        return ErrorCode::INSUFFICIENT_FUNDS;
    }

    return ErrorCode::SUCCESS;
}

} // namespace atm