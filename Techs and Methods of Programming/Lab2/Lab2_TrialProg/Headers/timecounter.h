#pragma once

#include "WinRegistry.h"
#include "TrialLimitProvider.h"

#include <windows.h>
#include <string>
#include <stdexcept>
#include <chrono>
#include <sstream>
#include <iomanip>

class TimeCounter : public TrialLimitProvider
{
private:
    const std::chrono::system_clock::duration MAX_DURATION { std::chrono::seconds(90) };
    const HKEY BASE_KEY = HKEY_CURRENT_USER;
    const wchar_t reg_subpath_[41] = L"SOFTWARE\\DenSolo.Inc\\TrialProgTime\\Users";
    std::wstring reg_key_name_ = L"TimeLeft";

private:
    std::chrono::system_clock::duration time_left_ { -1 };

private:
    static std::wstring _DurationToWString(const std::chrono::system_clock::duration& d);

public:
    TimeCounter() = default;
    
    void SetUser(int user_id, bool is_new) override;
    bool IsOver() const override;
    std::wstring GetMsg() const override;
};
