#pragma once

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
     * @return true if PIN is correct, false otherwise
     */
    virtual bool VerifyPIN(const std::string &card_number, const std::string &pin) = 0;

    /**
     * @brief Gets the balance for the specified account
     * @param[in] card_number The card number
     * @param[in] account The account identifier
     * @return The current balance
     */
    virtual int GetBalance(const std::string &card_number, const std::string &account) = 0;

    /**
     * @brief Deposits money into the specified account
     * @param[in] card_number The card number
     * @param[in] account The account identifier
     * @param[in] amount The amount to deposit
     */
    virtual void Deposit(const std::string &card_number, const std::string &account, int amount) = 0;

    /**
     * @brief Withdraws money from the specified account
     * @param[in] card_number The card number
     * @param[in] account The account identifier
     * @param[in] amount The amount to withdraw
     * @return true if withdrawal was successful, false if insufficient funds
     */
    virtual bool Withdraw(const std::string &card_number, const std::string &account, int amount) = 0;
};

} // namespace atm