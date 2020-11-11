#pragma once

#include <string>
#include <vector>
#include <Windows.h>

#include "winnls.h"
#include "shobjidl.h"
#include "shlobj_core.h"
#include "objbase.h"
#include "objidl.h"
#include "shlguid.h"

namespace WinFS 
{

bool FileExists(const std::wstring& name);
bool DirExists(const std::wstring& name);
bool CreateDir(const std::wstring& dir_name);
bool RemoveDir(const std::wstring& dir_name);
bool CreateNewFile(const std::wstring& dir_name);
bool RemoveFile(const std::wstring& file_name);
std::wstring GetCurrentDir();
bool CopyOrRewriteFile(const std::wstring& from, const std::wstring& to);


bool CreateLink(GUID folder,const std::wstring& path_obj, const std::wstring& link_name, const std::wstring& desc);
bool CreateLinkStartMenu(const std::wstring& path_obj, const std::wstring& link_name, const std::wstring& desc);
bool CreateLinkDesktop(const std::wstring& path_obj, const std::wstring& link_name, const std::wstring& desc);

bool RemoveLink(GUID folder, IID rclSid, const std::wstring& link_name);
bool RemoveLinkStartMenu( const std::wstring& link_name);
bool RemoveLinkDesktop(const std::wstring& link_name);
}