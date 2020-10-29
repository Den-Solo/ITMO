#include "timecounter.h"

using namespace std;
using namespace std::chrono;

void TimeCounter::SetUser(int user_id, bool is_new)
{
    reg_key_name_ += std::to_wstring((user_id));
    system_clock::time_point cur_time = system_clock::now();
    int32_t cur_time_sec = static_cast<int32_t>(
        duration_cast<chrono::seconds>(cur_time.time_since_epoch()).count());
    if (is_new || !WinReg::KeyDwordExists(BASE_KEY, reg_subpath_, reg_key_name_.c_str())) {
        WinReg::SetDword(BASE_KEY, reg_subpath_, reg_key_name_.c_str(), cur_time_sec);
        time_left_ = MAX_DURATION;
    } else {
        uint32_t start_time_sec = WinReg::GetDword(BASE_KEY, reg_subpath_, reg_key_name_.c_str());
        time_left_ = MAX_DURATION - chrono::seconds(cur_time_sec - start_time_sec);
    }
}
bool TimeCounter::IsOver() const
{
    return time_left_ < std::chrono::seconds(0);
}

std::wstring TimeCounter::GetMsg() const
{
    if (this->IsOver())
        return L"Лимит исчерпан";
    else
        return L"Осталось " + _DurationToWString(time_left_);
}


std::wstring TimeCounter::_DurationToWString(const std::chrono::system_clock::duration& d)
{
    uint32_t sec = static_cast<uint32_t>(duration_cast<chrono::seconds>(d).count());
    uint32_t days = sec / (3600 * 24);
    sec -= (3600 * 24) * days;
    uint32_t hr = sec / 3600;
    sec -= 3600 * hr;
    uint32_t min = sec / 60;
    sec -= 60 * min;

    std::wstringstream ss;
    ss << setfill(L'0') << days << L" дней " 
        << setw(2) << hr << ':' 
        << setw(2) << min << ':'
        << setw(2) << sec;
    return ss.str();
}