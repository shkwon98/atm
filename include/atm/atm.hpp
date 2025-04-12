#pragma once

#include "atm/bank_api.hpp"
#include "atm/error_code.hpp"

namespace atm
{

/**
 * @brief ATM machine controller class
 *
 * This class handles all ATM operations including card insertion,
 * PIN verification, and account transactions.
 */
class ATM
{
public:
    /**
     * @brief Constructs an ATM object
     * @param bank_api Reference to the banking API implementation
     */
    explicit ATM(BankAPI &bank_api);

    /**
     * @brief Handles card insertion
     * @param[in] card_number The card number being inserted
     * @return atm::ErrorCode indicating success or failure
     */
    ErrorCode InsertCard(const std::string &card_number);

    /**
     * @brief Handles PIN entry
     * @param[in] pin The PIN entered by the user
     * @return atm::ErrorCode indicating success or failure
     */
    ErrorCode EnterPIN(const std::string &pin);

    /**
     * @brief Handles account selection
     * @param[in] account The account identifier selected by the user
     * @return atm::ErrorCode indicating success or failure
     */
    ErrorCode SelectAccount(const std::string &account);

    /**
     * @brief Checks the balance of the selected account
     * @param[out] balance The current balance
     * @return atm::ErrorCode indicating success or failure
     */
    ErrorCode CheckBalance(int &balance);

    /**
     * @brief Handles deposit operation
     * @param[in] amount The amount to deposit
     * @return atm::ErrorCode indicating success or failure
     */
    ErrorCode Deposit(int amount);

    /**
     * @brief Handles withdrawal operation
     * @param[in] amount The amount to withdraw
     * @return atm::ErrorCode indicating success or failure
     */
    ErrorCode Withdraw(int amount);

    /**
     * @brief Gets the list of available accounts for the authenticated user
     * @param[out] accounts Vector to store the account list
     * @return atm::ErrorCode indicating success or failure
     */
    ErrorCode GetAccounts(std::vector<std::string> &accounts);

private:
    BankAPI &bank_api_;           ///< Reference to the banking API
    std::string current_card_;    ///< Currently inserted card number
    std::string current_account_; ///< Currently selected account
    std::string user_token_;      ///< Current user's authentication token
    bool authenticated_;          ///< Authentication status
};

} // namespace atm