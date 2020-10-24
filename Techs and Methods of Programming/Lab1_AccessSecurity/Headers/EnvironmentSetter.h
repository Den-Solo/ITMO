#pragma once
#include "MsgSender.h"

#include <QSharedMemory>
#include <stdexcept>

#include <QDir>
#include <QTextCodec>

#include <Windows.h>
#include <fstream>
#include <sddl.h>
#include <Psapi.h>

#include <algorithm>

class EnvironmentSetter
{
private:
    QSharedMemory sm_unique_;
    QSharedMemory sm_count_processes_;

    const HKEY BOTTOM_HKEY = HKEY_USERS;
    const wchar_t taskmng_subpath_[73] = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System";
    const wchar_t taskmng_reg_value_name_[15] = L"DisableTaskMgr";

    PSID user_sid_ { NULL };
    std::wstring ws_user_sid_;
    std::string s_user_sid_;
    std::wstring full_reg_subpath_;

private:
    static std::string GetUserSidStringFromProcess(HANDLE hProc);
    static std::wstring ConvertSidToWString(PSID p);
    static std::string ConvertSidToString(PSID p);

private:
    void CheckUniqueness();
    void ChangeProcCnt(bool if_increase = true);

public:
    void DisableTaskMng(bool if_dis = true) const;
    PSID GetPSID() const;

    EnvironmentSetter(int argc, char* argv[]);
    ~EnvironmentSetter();
};
