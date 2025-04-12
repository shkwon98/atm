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
        std::vector<std::string> accounts;

        REQUIRE(atm.EnterPIN("0000") == atm::ErrorCode::NO_CARD);
        REQUIRE(atm.GetAccounts(accounts) == atm::ErrorCode::AUTHENTICATION_FAILED);

        REQUIRE(atm.InsertCard("1234-1234-1234-1234") == atm::ErrorCode::SUCCESS);

        REQUIRE(atm.GetAccounts(accounts) == atm::ErrorCode::AUTHENTICATION_FAILED);

        REQUIRE(atm.EnterPIN("0000") == atm::ErrorCode::AUTHENTICATION_FAILED);
        REQUIRE(atm.EnterPIN("4321") == atm::ErrorCode::SUCCESS);

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
        std::vector<std::string> accounts;

        REQUIRE(atm.EnterPIN("0000") == atm::ErrorCode::NO_CARD);
        REQUIRE(atm.GetAccounts(accounts) == atm::ErrorCode::AUTHENTICATION_FAILED);

        REQUIRE(atm.InsertCard("9876-9876-9876-9876") == atm::ErrorCode::SUCCESS);

        REQUIRE(atm.GetAccounts(accounts) == atm::ErrorCode::AUTHENTICATION_FAILED);

        REQUIRE(atm.EnterPIN("0000") == atm::ErrorCode::AUTHENTICATION_FAILED);
        REQUIRE(atm.EnterPIN("6789") == atm::ErrorCode::SUCCESS);

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
