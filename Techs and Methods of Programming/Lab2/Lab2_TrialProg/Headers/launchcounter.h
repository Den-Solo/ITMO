#pragma once

#include "TrialLimitProvider.h"

#include <string>
#include <stdexcept>


class LaunchCounter : public TrialLimitProvider
{
private:
    const int MAX_ATTEMPTS = 4;
    const HKEY BASE_KEY = HKEY_CURRENT_USER; 
    const wchar_t reg_subpath_[45] = L"SOFTWARE\\DenSolo.Inc\\TrialProgLaunches\\Users";
    std::wstring reg_key_name_ = L"AttemptsLeft";

private:
    int launches_left_ { -1 };

private:
    int _DecLaunches();

public:
    LaunchCounter() = default;

    void SetUser(int user_id, bool is_new) override;
    bool IsOver() const override;
    std::wstring GetMsg() const override;
};
