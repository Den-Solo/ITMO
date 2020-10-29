#pragma once

#include <Windows.h>
#include <stdexcept>
#include <vector>

namespace WinReg 
{
bool KeyDwordExists(HKEY base_key, const wchar_t* subpath, const wchar_t* key_name);

void SetValue(HKEY base_key, const wchar_t* subpath, const wchar_t* key_name, DWORD dwType, BYTE* val, DWORD dwSize);
std::vector<uint8_t> GetValue(HKEY base_key, const wchar_t* subpath, const wchar_t* key_name, DWORD dwFlags);

void SetDword(HKEY base_key, const wchar_t* subpath, const wchar_t* key_name, int32_t val);
int32_t GetDword(HKEY base_key, const wchar_t* subpath, const wchar_t* key_name);

void SetWString(HKEY base_key, const wchar_t* subpath, const wchar_t* key_name, std::wstring val);
std::wstring GetWString(HKEY base_key, const wchar_t* subpath, const wchar_t* key_name);
}
