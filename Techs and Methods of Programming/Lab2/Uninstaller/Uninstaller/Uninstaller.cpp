#include "Uninstaller.h"

bool Uninstaller::Exec() 
{
    bool status = true;

    status &= WinFS::RemoveFile(prog_filename_);
    status &= WinFS::RemoveFile(uninst_filename_);

    WinFS::RemoveDir(cur_dir_);

    status &= WinReg::DeleteKey(base_key_, (rp_uninst_ + gen_key_).c_str());

    WinFS::RemoveLinkDesktop(link_name_);
    WinFS::RemoveLinkStartMenu(link_name_);

    return status;
}