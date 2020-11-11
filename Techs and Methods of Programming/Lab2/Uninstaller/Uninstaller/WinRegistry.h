#pragma once

#include <Windows.h>
#include <stdexcept>
#include <vector>

namespace WinReg 
{
bool KeyDwordExists(HKEY base_key, const wchar_t* subpath, const wchar_t* val_name);

bool SetValue(HKEY base_key, const wchar_t* subpath, const wchar_t* val_name, DWORD dwType, BYTE* val, DWORD dwSize);
std::vector<uint8_t> GetValue(HKEY base_key, const wchar_t* subpath, const wchar_t* val_name, DWORD dwFlags);

bool SetDword(HKEY base_key, const wchar_t* subpath, const wchar_t* val_name, int32_t val);
int32_t GetDword(HKEY base_key, const wchar_t* subpath, const wchar_t* val_name);

bool SetWString(HKEY base_key, const wchar_t* subpath, const wchar_t* val_name, std::wstring val);
std::wstring GetWString(HKEY base_key, const wchar_t* subpath, const wchar_t* val_name);

bool DeleteKey(HKEY base_key, const wchar_t* subpath);
}
