#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <atm/atm.hpp>

#include "mock_bank_api.hpp"

TEST_CASE("Verify User and Select Account", "[account]")
{
    MockBankAPI mock_bank_api;
    atm::ATM atm(mock_bank_api);

    SECTION("user1")
    {
        REQUIRE(atm.InsertCard("1234-1234-1234-1234") == atm::ErrorCode::SUCCESS);

        REQUIRE(atm.EnterPIN("0000") == atm::ErrorCode::AUTHENTICATION_FAILED);
        REQUIRE(atm.EnterPIN("4321") == atm::ErrorCode::SUCCESS);

        std::vector<std::string> accounts;
        REQUIRE(atm.GetAccounts(accounts) == atm::ErrorCode::SUCCESS);
        REQUIRE(accounts.size() == 3);
        REQUIRE(std::find(accounts.begin(), accounts.end(), "123-456-789789") != accounts.end());
        REQUIRE(std::find(accounts.begin(), accounts.end(), "000-111-222222") != accounts.end());
        REQUIRE(std::find(accounts.begin(), accounts.end(), "454-545-454545") != accounts.end());

        for (const auto &account : accounts)
        {
            REQUIRE(atm.SelectAccount(account) == atm::ErrorCode::SUCCESS);
        }
    }

    SECTION("user2")
    {

        REQUIRE(atm.InsertCard("9876-9876-9876-9876") == atm::ErrorCode::SUCCESS);

        REQUIRE(atm.EnterPIN("0000") == atm::ErrorCode::AUTHENTICATION_FAILED);
        REQUIRE(atm.EnterPIN("6789") == atm::ErrorCode::SUCCESS);

        std::vector<std::string> accounts;
        REQUIRE(atm.GetAccounts(accounts) == atm::ErrorCode::SUCCESS);
        REQUIRE(accounts.size() == 2);
        REQUIRE(std::find(accounts.begin(), accounts.end(), "987-654-321321") != accounts.end());
        REQUIRE(std::find(accounts.begin(), accounts.end(), "888-777-666666") != accounts.end());

        for (const auto &account : accounts)
        {
            REQUIRE(atm.SelectAccount(account) == atm::ErrorCode::SUCCESS);
        }
    }
}

TEST_CASE("Get Balance", "[balance]")
{
    MockBankAPI mock_bank_api;
    atm::ATM atm(mock_bank_api);

    atm.InsertCard("1234-1234-1234-1234");
    atm.EnterPIN("4321");

    std::vector<std::string> accounts;
    atm.GetAccounts(accounts);
    atm.SelectAccount("123-456-789789");

    int balance = 0;
    REQUIRE(atm.GetBalance(balance) == atm::ErrorCode::SUCCESS);
    REQUIRE(balance == 1000);
}

TEST_CASE("Withdraw", "[withdraw]")
{
    MockBankAPI mock_bank_api;
    atm::ATM atm(mock_bank_api);

    atm.InsertCard("1234-1234-1234-1234");
    atm.EnterPIN("4321");

    std::vector<std::string> accounts;
    atm.GetAccounts(accounts);
    atm.SelectAccount("123-456-789789");

    int balance = 0;
    atm.GetBalance(balance);

    REQUIRE(atm.Withdraw(500) == atm::ErrorCode::SUCCESS);
    REQUIRE(atm.GetBalance(balance) == atm::ErrorCode::SUCCESS);
    REQUIRE(balance == 500);
    REQUIRE(atm.Withdraw(600) == atm::ErrorCode::INSUFFICIENT_FUNDS);
    REQUIRE(atm.GetBalance(balance) == atm::ErrorCode::SUCCESS);
    REQUIRE(balance == 500);
}

TEST_CASE("Deposit", "[deposit]")
{
    MockBankAPI mock_bank_api;
    atm::ATM atm(mock_bank_api);

    atm.InsertCard("1234-1234-1234-1234");
    atm.EnterPIN("4321");

    std::vector<std::string> accounts;
    atm.GetAccounts(accounts);
    atm.SelectAccount("123-456-789789");

    int balance = 0;
    atm.GetBalance(balance);

    REQUIRE(atm.Deposit(500) == atm::ErrorCode::SUCCESS);
    REQUIRE(atm.GetBalance(balance) == atm::ErrorCode::SUCCESS);
    REQUIRE(balance == 1500);
}

TEST_CASE("Remove Card", "[card]")
{
    MockBankAPI mock_bank_api;
    atm::ATM atm(mock_bank_api);

    REQUIRE(atm.InsertCard("1234-1234-1234-1234") == atm::ErrorCode::SUCCESS);
    REQUIRE(atm.EnterPIN("4321") == atm::ErrorCode::SUCCESS);

    std::vector<std::string> accounts;
    REQUIRE(atm.GetAccounts(accounts) == atm::ErrorCode::SUCCESS);
    REQUIRE(accounts.size() > 0);

    REQUIRE(atm.RemoveCard() == atm::ErrorCode::SUCCESS);
    REQUIRE(atm.GetAccounts(accounts) == atm::ErrorCode::AUTHENTICATION_FAILED);
}

TEST_CASE("Invalid Account", "[account]")
{
    MockBankAPI mock_bank_api;
    atm::ATM atm(mock_bank_api);

    REQUIRE(atm.InsertCard("1234-1234-1234-1234") == atm::ErrorCode::SUCCESS);
    REQUIRE(atm.EnterPIN("4321") == atm::ErrorCode::SUCCESS);

    REQUIRE(atm.SelectAccount("999-999-999999") == atm::ErrorCode::INVALID_ACCOUNT);

    int balance = 0;
    REQUIRE(atm.GetBalance(balance) == atm::ErrorCode::NO_ACCOUNT_SELECTED);
}

TEST_CASE("Negative Amount Operations", "[amount]")
{
    MockBankAPI mock_bank_api;
    atm::ATM atm(mock_bank_api);

    atm.InsertCard("1234-1234-1234-1234");
    atm.EnterPIN("4321");

    std::vector<std::string> accounts;
    atm.GetAccounts(accounts);
    atm.SelectAccount("123-456-789789");

    REQUIRE(atm.Deposit(-100) == atm::ErrorCode::INVALID_AMOUNT);
    REQUIRE(atm.Withdraw(-50) == atm::ErrorCode::INVALID_AMOUNT);
}

TEST_CASE("Select Account Without PIN", "[error]")
{
    MockBankAPI mock_bank_api;
    atm::ATM atm(mock_bank_api);

    REQUIRE(atm.InsertCard("1234-1234-1234-1234") == atm::ErrorCode::SUCCESS);

    REQUIRE(atm.SelectAccount("123-456-789789") == atm::ErrorCode::AUTHENTICATION_FAILED);
}

TEST_CASE("Get Balance Without Card", "[error]")
{
    MockBankAPI mock_bank_api;
    atm::ATM atm(mock_bank_api);

    int balance = 0;
    REQUIRE(atm.GetBalance(balance) == atm::ErrorCode::NO_CARD);
}

TEST_CASE("Insert Same Card Multiple Times", "[error]")
{
    MockBankAPI mock_bank_api;
    atm::ATM atm(mock_bank_api);

    REQUIRE(atm.InsertCard("1234-1234-1234-1234") == atm::ErrorCode::SUCCESS);
    REQUIRE(atm.InsertCard("1234-1234-1234-1234") == atm::ErrorCode::CARD_ALREADY_INSERTED);
}

TEST_CASE("Withdraw Without Card", "[error]")
{
    MockBankAPI mock_bank_api;
    atm::ATM atm(mock_bank_api);

    REQUIRE(atm.Withdraw(100) == atm::ErrorCode::NO_CARD);
}

TEST_CASE("Deposit Without Card", "[error]")
{
    MockBankAPI mock_bank_api;
    atm::ATM atm(mock_bank_api);

    REQUIRE(atm.Deposit(100) == atm::ErrorCode::NO_CARD);
}
