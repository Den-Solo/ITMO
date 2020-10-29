#pragma once

#include "WinRegistry.h"
#include "launchcounter.h"
#include "timecounter.h"

#include <string>
#include <fstream>
#include <vector>
#include <cassert>
#include <Shlobj.h>
#include <locale>
#include <memory>

#include <Windows.h>

class AccountManager
{
public:
    struct Account
    {
        int id;
        std::wstring surname;
        std::wstring name;
    };

private: // values to get type of the limit_provider
    const HKEY base_key_ = HKEY_CURRENT_USER;
    const wchar_t reg_path_[21] = L"SOFTWARE\\DenSolo.Inc";
    const wchar_t key_name_[9] = L"Type";

private:
    std::wstring dir_name_ = L"TrialProg"; // recieves postfix in _GetLimitProvider
    static constexpr wchar_t file_name_[] = L"UserList.txt";
    static constexpr char locale_data_[] = "ru_RU.utf8";

private:
    int user_id_ = -1;
    std::vector<Account> accounts_;
    std::wstring path_;
    bool is_new_user_{false};
    std::unique_ptr<TrialLimitProvider> limit_provider_ { nullptr };

private:
    static std::wstring _GetUserPath();
    static std::vector<Account> _ReadAccounts(const std::wstring& path);
    static void _SerializeAccounts(const std::wstring& path, const std::vector<Account>& accounts);
    std::unique_ptr<TrialLimitProvider> _GetLimitProvider();

public:
    AccountManager();

    void SetCurrentUser(std::wstring&& surname, std::wstring&& name);

    int GetUserID() const;
    bool IsNewUser() const;
    bool IsOver() const;
    std::wstring GetMsg() const;
};
