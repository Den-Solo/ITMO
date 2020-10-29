#include "launchcounter.h"

int LaunchCounter::_DecLaunches()
{
    int val = WinReg::GetDword(BASE_KEY, reg_subpath_, reg_key_name_.c_str());
    --val;
    if (val > -1)
        WinReg::SetDword(BASE_KEY, reg_subpath_, reg_key_name_.c_str(), val);
    return val;
}
void LaunchCounter::SetUser(int user_id, bool is_new)
{
    user_id_ = user_id;
    reg_key_name_ += std::to_wstring((user_id_));
    if (is_new || !WinReg::KeyDwordExists(BASE_KEY, reg_subpath_, reg_key_name_.c_str())) {
        WinReg::SetDword(BASE_KEY, reg_subpath_, reg_key_name_.c_str(), MAX_ATTEMPTS - 1);
        launches_left_ = MAX_ATTEMPTS - 1;
    } else {
        launches_left_ = _DecLaunches();
    }
}
bool LaunchCounter::IsOver() const 
{
    return launches_left_ < 1;
}
std::wstring LaunchCounter::GetMsg() const
{
    if (this->IsOver())
        return L"Лимит исчерпан";
    else
        return L"Осталось " + std::to_wstring(launches_left_)+ L" попыток!";
}


