#include "WinRegistry.h"


namespace WinReg
{
bool KeyDwordExists(HKEY base_key, const wchar_t* subpath, const wchar_t* val_name)
{
    return -1 != GetDword(base_key, subpath, val_name);
}
bool SetValue(HKEY base_key, const wchar_t* subpath, const wchar_t* val_name, DWORD dwType, BYTE* val, DWORD dwSize)
{
    DWORD dwDispos;
    HKEY hKey { NULL };
    bool status{true};
    if (ERROR_SUCCESS != RegCreateKeyEx(base_key, subpath, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, &dwDispos)) {
        status = false;
        goto Exit;
    }
    if (ERROR_SUCCESS != RegSetValueEx(hKey, val_name, 0, dwType, val, dwSize)) {
        status = false;
        goto Exit;
    }
Exit:
    if (hKey)
        RegCloseKey(hKey);
    return status;
}
std::vector<uint8_t> GetValue(HKEY base_key, const wchar_t* subpath, const wchar_t* val_name, DWORD dwFlags)
{
    HKEY hKey { NULL };
    DWORD dwSz { 0 };
    std::vector<uint8_t> result;
    if (ERROR_SUCCESS != RegOpenKeyEx(base_key, subpath, 0, KEY_READ, &hKey)) {
        goto Exit;
    }
    if (ERROR_SUCCESS != RegGetValue(hKey, NULL, val_name, dwFlags, NULL,NULL, &dwSz)) {
        goto Exit;
    }
    result.resize(dwSz);
    if (ERROR_SUCCESS != RegGetValue(hKey, NULL, val_name, dwFlags, NULL, result.data(), &dwSz)) {
        goto Exit;
    }
Exit:
    if (hKey)
        RegCloseKey(hKey);
    return result;
}
bool SetDword(HKEY base_key, const wchar_t* subpath, const wchar_t* val_name, int32_t val)
{
    return SetValue(base_key, subpath, val_name, REG_DWORD, (BYTE*)&val, sizeof(DWORD));
}
int32_t GetDword(HKEY base_key, const wchar_t* subpath, const wchar_t* val_name)
{
    auto result = GetValue(base_key, subpath, val_name, RRF_RT_REG_DWORD);
    if (result.size() == 4)
        return *reinterpret_cast<int32_t*>(result.data());
    return -1; /*error*/
}
bool SetWString(HKEY base_key, const wchar_t* subpath, const wchar_t* val_name, std::wstring val)
{
    return SetValue(base_key, subpath, val_name, REG_SZ, (BYTE*)val.c_str(), sizeof(std::wstring::value_type) * (val.size() + 1));
}
std::wstring GetWString(HKEY base_key, const wchar_t* subpath, const wchar_t* val_name)
{
    auto result = GetValue(base_key, subpath, val_name, RRF_RT_REG_SZ);
    if (result.size() > 0)
        return reinterpret_cast<wchar_t*>(result.data());
    return {}; /*error*/
}
bool DeleteKey(HKEY base_key, const wchar_t* subpath)
{
    return ERROR_SUCCESS == RegDeleteKeyEx(base_key,subpath,KEY_WOW64_64KEY,0);
}
}
