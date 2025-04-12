#pragma once

#include <atm/bank_api.hpp>

#include <random>
#include <string>
#include <unordered_map>
#include <vector>

class MockBankAPI : public atm::BankAPI
{
public:
    MockBankAPI()
    {
        // Set card numbers and PINs
        cards_["1234-1234-1234-1234"] = "4321";
        cards_["9876-9876-9876-9876"] = "6789";

        // Set user IDs and card number lists
        user_cards_["user1"] = {"1234-1234-1234-1234"};
        user_cards_["user2"] = {"9876-9876-9876-9876"};

        // Set user IDs and account lists
        user_accounts_["user1"] = {"123-456-789789", "000-111-222222", "454-545-454545"};
        user_accounts_["user2"] = {"987-654-321321", "888-777-666666"};

        // Initialize account balances
        accounts_["123-456-789789"] = 1000;
        accounts_["000-111-222222"] = 500;
        accounts_["454-545-454545"] = 2000;
        accounts_["987-654-321321"] = 1500;
        accounts_["888-777-666666"] = 800;
    }

    std::string VerifyPIN(const std::string &card_number, const std::string &pin) override
    {
        auto it = cards_.find(card_number);
        if (it != cards_.end() && it->second == pin)
        {
            for (const auto &[user_id, card_numbers] : user_cards_)
            {
                if (std::find(card_numbers.begin(), card_numbers.end(), card_number) != card_numbers.end())
                {
                    std::random_device rd;
                    std::mt19937 gen(rd());
                    std::uniform_int_distribution dis(10000000, 99999999);

                    auto user_token = std::to_string(dis(gen));
                    user_tokens_[user_token] = user_id;
                    return user_token;
                }
            }
        }
        return "";
    }

    std::vector<std::string> GetUserAccounts(const std::string &user_token) override
    {
        if (user_token.empty())
        {
            return {};
        }

        auto user_id = GetUserID(user_token);
        if (user_id.empty())
        {
            return {};
        }

        return user_accounts_[user_id];
    }

    int GetBalance(const std::string &account, const std::string &user_token) override
    {
        if (user_token.empty())
        {
            return 0;
        }

        auto user_id = GetUserID(user_token);
        if (user_id.empty())
        {
            return 0;
        }

        if (std::find(user_accounts_[user_id].begin(), user_accounts_[user_id].end(), account)
            != user_accounts_[user_id].end())
        {
            return accounts_[account];
        }

        return 0;
    }

    void Deposit(const std::string &account, int amount, const std::string &user_token) override
    {
        if (user_token.empty())
        {
            return;
        }

        auto user_id = GetUserID(user_token);
        if (user_id.empty())
        {
            return;
        }

        if (std::find(user_accounts_[user_id].begin(), user_accounts_[user_id].end(), account)
            != user_accounts_[user_id].end())
        {
            accounts_[account] += amount;
        }
    }

    bool Withdraw(const std::string &account, int amount, const std::string &user_token) override
    {
        if (user_token.empty())
        {
            return false;
        }

        auto user_id = GetUserID(user_token);
        if (user_id.empty())
        {
            return false;
        }

        if (std::find(user_accounts_[user_id].begin(), user_accounts_[user_id].end(), account)
            != user_accounts_[user_id].end())
        {
            if (accounts_[account] >= amount)
            {
                accounts_[account] -= amount;
                return true;
            }
        }

        return false;
    }

private:
    std::string GetUserID(const std::string &user_token) const
    {
        if (auto it = user_tokens_.find(user_token); it != user_tokens_.end())
        {
            return it->second;
        }
        return "";
    }

    // Mock data
    std::unordered_map<std::string, std::vector<std::string>> user_cards_;
    std::unordered_map<std::string, std::vector<std::string>> user_accounts_;
    std::unordered_map<std::string, std::string> cards_;
    std::unordered_map<std::string, int> accounts_;

    // User tokens and their corresponding user IDs
    std::unordered_map<std::string, std::string> user_tokens_;
};
