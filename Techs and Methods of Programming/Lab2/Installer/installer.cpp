#include "installer.h"

void Installer::SetPath(std::wstring path)
{
    inst_dir_ = path;
}
void Installer::SetType(ProgLimit pl)
{
    type_ = pl;
}
void Installer::SetCreateDesktopShortcut(bool val)
{
    is_create_desktop_shortcut_ = val;
}
void Installer::SetCreateStartupShortcut(bool val)
{
    is_create_startup_shortcut_ = val;
}
std::wstring Installer::GetPath() const
{
    return inst_dir_;
}
bool Installer::Exec()
{
    bool status = true;
    if (!WinFS::CreateDir(inst_dir_))
        return false;
    inst_dir_ += L"\\";

    if (!WinFS::CopyOrRewriteFile(cur_dir_ + prog_filename_,inst_dir_ + prog_filename_))
        return false;
    if (!WinFS::CopyOrRewriteFile(cur_dir_ + uninst_filename_, inst_dir_ + uninst_filename_))
        return false;
    status &= WinReg::SetWString(base_key_,rp_apptype_,rk_apptype_,prog_limit_vals_[static_cast<int>(type_)]);
    status &= WinReg::SetWString(base_key_,(rp_uninst_ + gen_key_).c_str(),rk_uninst_,inst_dir_ + uninst_filename_);
    status &= WinReg::SetWString(base_key_,(rp_uninst_ + gen_key_).c_str(),rk_disp_,display_prog_name_);

    if (is_create_desktop_shortcut_)
        WinFS::CreateLinkDesktop(inst_dir_ + prog_filename_, display_prog_name_, L"");
    if (is_create_startup_shortcut_)
        WinFS::CreateLinkStartMenu(inst_dir_ + prog_filename_, display_prog_name_, L"");
    return status;
}

