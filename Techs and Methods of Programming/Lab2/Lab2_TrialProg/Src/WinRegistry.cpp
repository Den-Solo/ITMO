#include "WinRegistry.h"


std::string GetLastErrorAsString()
{
    //Get the error message, if any.
    DWORD errorMessageID = ::GetLastError();
    if (errorMessageID == 0)
        return std::string(); //No error message has been recorded

    LPSTR messageBuffer = nullptr;
    size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

    std::string message(messageBuffer, size);

    //Free the buffer.
    LocalFree(messageBuffer);

    return message;
}

namespace WinReg
{
    bool KeyDwordExists(HKEY base_key, const wchar_t* subpath, const wchar_t* key_name)
    {
        return -1 != GetDword(base_key, subpath, key_name);
    }
    void SetValue(HKEY base_key, const wchar_t* subpath, const wchar_t* key_name, DWORD dwType, BYTE* val, DWORD dwSize)
    {
        DWORD dwDispos;
        HKEY hKey { NULL };
        if (ERROR_SUCCESS != RegCreateKeyEx(base_key, subpath, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, &dwDispos)) {
            goto Exit;
        }
        if (ERROR_SUCCESS != RegSetValueEx(hKey, key_name, 0, dwType, val, dwSize)) {
            goto Exit;
        }
    Exit:
        if (hKey)
            RegCloseKey(hKey);
    }
    std::vector<uint8_t> GetValue(HKEY base_key, const wchar_t* subpath, const wchar_t* key_name, DWORD dwFlags)
    {
        HKEY hKey { NULL };
        DWORD dwSz { 0 };
        std::vector<uint8_t> result;
        int a;
        if (ERROR_SUCCESS != RegOpenKeyEx(base_key, subpath, 0, KEY_READ, &hKey)) {
            goto Exit;
        }
        if (ERROR_SUCCESS != RegGetValue(hKey, NULL, key_name, dwFlags, NULL,NULL, &dwSz)) {
            goto Exit;
        }
        result.resize(dwSz);
        if (ERROR_SUCCESS != RegGetValue(hKey, NULL, key_name, dwFlags, NULL, result.data(), &dwSz)) {
            goto Exit;
        }
    Exit:
        if (hKey)
            RegCloseKey(hKey);
        return result;
    }

    void SetDword(HKEY base_key, const wchar_t* subpath, const wchar_t* key_name, int32_t val)
    {
        SetValue(base_key, subpath, key_name, REG_DWORD, (BYTE*)&val, sizeof(DWORD));
    }

    int32_t GetDword(HKEY base_key, const wchar_t* subpath, const wchar_t* key_name)
    {
        auto result = GetValue(base_key, subpath, key_name, RRF_RT_REG_DWORD);
        if (result.size() == 4)
            return *reinterpret_cast<int32_t*>(result.data());
        return -1; /*error*/
    }
    void SetWString(HKEY base_key, const wchar_t* subpath, const wchar_t* key_name, std::wstring val) 
    {
        SetValue(base_key, subpath, key_name, REG_SZ, (BYTE*)&val, sizeof(wchar_t) * val.size());
    }
    std::wstring GetWString(HKEY base_key, const wchar_t* subpath, const wchar_t* key_name) 
    {
        auto result = GetValue(base_key, subpath, key_name, RRF_RT_REG_SZ);
        if (result.size() > 0)
            return reinterpret_cast<wchar_t*>(result.data());
        return {}; /*error*/
    }
}