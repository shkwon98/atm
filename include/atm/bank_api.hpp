#pragma once

#include <string>
#include <vector>

namespace atm
{

/**
 * @brief Interface for banking operations
 *
 * This interface defines the contract between the ATM and the bank's backend system.
 */
class BankAPI
{
public:
    virtual ~BankAPI() = default;

    /**
     * @brief Verifies the PIN for a given card
     * @param[in] card_number The card number
     * @param[in] pin The PIN to verify
     * @return user token if successful, empty string if failed
     * @note The user token is a unique identifier for the user session and expires after a certain period.
     */
    virtual std::string VerifyPIN(const std::string &card_number, const std::string &pin = "") = 0;

    /**
     * @brief Gets the list of user accounts
     * @param[in] user_token The user token
     * @return List of account identifiers
     * @note The user token is used to identify the user session and may be required for security reasons.
     */
    virtual std::vector<std::string> GetUserAccounts(const std::string &user_token = "") = 0;

    /**
     * @brief Gets the balance for the specified account
     * @param[in] account The account identifier
     * @param[in] user_token The user token
     * @return The current balance
     * @note The user token is used to identify the user session and may be required for security reasons.
     */
    virtual int GetBalance(const std::string &account, const std::string &user_token = "") = 0;

    /**
     * @brief Deposits money into the specified account
     * @param[in] account The account identifier
     * @param[in] amount The amount to deposit
     * @param[in] user_token The user token
     * @note The user token is used to identify the user session and may be required for security reasons.
     */
    virtual void Deposit(const std::string &account, int amount, const std::string &user_token = "") = 0;

    /**
     * @brief Withdraws money from the specified account
     * @param[in] account The account identifier
     * @param[in] amount The amount to withdraw
     * @param[in] user_token The user token
     * @return true if withdrawal was successful, false if insufficient funds
     * @note The user token is used to identify the user session and may be required for security reasons.
     */
    virtual bool Withdraw(const std::string &account, int amount, const std::string &user_token = "") = 0;
};

} // namespace atm