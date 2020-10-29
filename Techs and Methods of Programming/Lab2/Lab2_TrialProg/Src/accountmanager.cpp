#include "accountmanager.h"

AccountManager::AccountManager()
    : limit_provider_(_GetLimitProvider())
{
    path_ = _GetUserPath();
    path_ += L"\\";
    path_ += dir_name_;
    if (!(CreateDirectory(path_.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError()))
        throw std::runtime_error("CreateDirectory error");
    path_ += L"\\";
    path_ += file_name_;
    accounts_ = _ReadAccounts(path_);

    if (!limit_provider_)
        throw std::runtime_error("");
}

std::unique_ptr<TrialLimitProvider> AccountManager::_GetLimitProvider()
{
    std::wstring reg_val = WinReg::GetWString(base_key_,reg_path_,key_name_);
    if (reg_val == L"Launches") {
        dir_name_ += L"Launches";
        return std::make_unique<LaunchCounter>();
    } else if (reg_val == L"Time") {
        dir_name_ += L"Time";
        return std::make_unique<TimeCounter>();
    }
    return nullptr;
}

int AccountManager::GetUserID() const
{
    assert(user_id_ != -1);
    return user_id_;
}
bool AccountManager::IsOver() const
{
    return limit_provider_->IsOver();
}
std::wstring AccountManager::GetMsg() const
{
    return limit_provider_->GetMsg();
}

void AccountManager::SetCurrentUser(std::wstring&& surname,std::wstring&& name)
{
    for (const auto& acc : accounts_)
    {
        if (acc.surname == surname
                && acc.name == name)
        {
            user_id_ = acc.id;
            break;
        }
    }
    if (user_id_ == -1)
    {
        accounts_.push_back({static_cast<int>(accounts_.size()),
              std::move(surname),std::move(name)});
        user_id_ = accounts_.back().id;
        is_new_user_ = true;
    } 
    if (is_new_user_)
        _SerializeAccounts(path_, accounts_);

    limit_provider_->SetUser(user_id_, is_new_user_);
}
bool AccountManager::IsNewUser() const
{
    return is_new_user_;
}
std::vector<AccountManager::Account> AccountManager::_ReadAccounts(const std::wstring& path)
{
    std::wifstream file(path);
    file.imbue(std::locale(locale_data_));
    if (!file.is_open())
    {
        return {};
    }

    size_t sz;
    file >> sz;

    if (sz < 0 || sz > 1024) /*probably broken file*/
        return {};

    std::vector<Account> result(sz);
    for (size_t i = 0; i < sz; ++i)
    {
        file >> result[i].id >> result[i].surname
                >> result[i].name;
    }
    return result;
}

void AccountManager::_SerializeAccounts(const std::wstring& path, const std::vector<Account>& accounts)
{
    std::wofstream file(path);
    file.imbue(std::locale(locale_data_));
    file << accounts.size() << L'\n';
    for (const auto& acc : accounts)
    {
        file << acc.id << L' '
             << acc.surname << L' '
             << acc.name
             << L'\n';
    }
}
std::wstring AccountManager::_GetUserPath()
{
    WCHAR path[MAX_PATH];
    if (SUCCEEDED(SHGetFolderPathW(NULL, CSIDL_PROFILE, NULL, 0, path))) {
        return std::wstring(path);
    }
    return L"";
}
