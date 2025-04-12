#pragma once

namespace atm
{

/**
 * @brief Error codes returned by ATM operations
 */
enum class ErrorCode
{
    SUCCESS = 0,           ///< Operation completed successfully
    NO_CARD,               ///< No card is inserted in the ATM
    AUTHENTICATION_FAILED, ///< PIN verification failed
    NO_ACCOUNT_SELECTED,   ///< No account has been selected
    INSUFFICIENT_FUNDS     ///< Not enough funds for withdrawal
};

} // namespace atm