#pragma once

#include "WinRegistry.h"
#include "WinFileSys.h"
#include <Windows.h>
#include <string>
#include <vector>


class Installer
{
public:
    enum class ProgLimit
    {
        Launches = 0,
        Time
    };
private:
    std::wstring prog_limit_vals_[2] = {L"Launches",L"Time"};

private:

    const wchar_t prog_filename_[14] = L"TrialProg.exe";
    const wchar_t uninst_filename_[11] = L"uninst.exe";
    const wchar_t display_prog_name_[13] = L"TrialProgram";

    const HKEY base_key_ = HKEY_CURRENT_USER;
    const std::wstring rp_uninst_ = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\";
    const std::wstring gen_key_ = L"{AB048DC3-DD4C-4107-8484-31024DEF506E}_is1";
    const wchar_t rk_disp_[12] = L"DisplayName";
    const wchar_t rk_uninst_[16] = L"UninstallString";

    const wchar_t rp_apptype_[21] = L"SOFTWARE\\DenSolo.Inc"; /*rp == reg path*/
    const wchar_t rk_apptype_[5] = L"Type";  /*rk == reg key*/

    const std::wstring cur_dir_ = WinFS::GetCurrentDir() + L"\\";

private:
    std::wstring inst_dir_ = L"C:\\Users\\User\\AppData\\Local\\Programs\\TrialProgLaunches";
    bool is_create_desktop_shortcut_{false};
    bool is_create_startup_shortcut_{false};
    ProgLimit type_{ProgLimit::Launches};


public:
    Installer() = default;
    void SetPath(std::wstring path);
    void SetType(ProgLimit pl);
    void SetCreateDesktopShortcut(bool);
    void SetCreateStartupShortcut(bool);
    bool Exec();
    std::wstring GetPath() const;
};


