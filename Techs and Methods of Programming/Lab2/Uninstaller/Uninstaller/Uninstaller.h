#pragma once

#include "WinFileSys.h"
#include "WinRegistry.h"

#include <windows.h>
#include <string>

class Uninstaller 
{
private:
    const wchar_t prog_filename_[14] = L"TrialProg.exe";
    const wchar_t uninst_filename_[11] = L"uninst.exe";

    const wchar_t link_name_[14] = L"TrialProgram";

    const HKEY base_key_ = HKEY_CURRENT_USER;
    const std::wstring rp_uninst_ = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\";
    const std::wstring gen_key_ = L"{AB048DC3-DD4C-4107-8484-31024DEF506E}_is1";

    const std::wstring cur_dir_ = WinFS::GetCurrentDir();

public:
    Uninstaller() = default;
    bool Exec();
};
