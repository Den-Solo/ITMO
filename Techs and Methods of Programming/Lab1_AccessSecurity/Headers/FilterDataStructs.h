#pragma once
#include <windows.h>
#include <aclapi.h>
#include <string>

namespace FilterData
{
    struct AccessInfo
    {
        DWORD access_perms{ GENERIC_ALL };
        DWORD inheritance{ INHERIT_ONLY };
        DWORD access_mode { GRANT_ACCESS };
    };
    struct NameFileInfo
    {
        std::wstring name;
        AccessInfo ai;
        bool if_created{ false };
    };
    struct PatternFileInfo
    {
        std::wstring name;
        AccessInfo ai;
    };
};
