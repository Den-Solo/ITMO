#include "EnvironmentSetter.h"


EnvironmentSetter::EnvironmentSetter(int argc, char* argv[])
{ 
    if (argc == 1) { //unelevated
        ShellExecuteA(NULL, "runas", argv[0],
            GetUserSidStringFromProcess(GetCurrentProcess()).c_str(),
            NULL, SW_SHOW);
        throw std::runtime_error("VALID_EXIT");
    }
    setlocale(LC_ALL, "rus");
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
  
    ConvertStringSidToSidA(argv[1], &user_sid_);
    ws_user_sid_ = ConvertSidToWString(user_sid_);
    s_user_sid_ = argv[1];
    full_reg_subpath_ = ws_user_sid_ + L"\\" + taskmng_subpath_;

    CheckUniqueness();
    ChangeProcCnt();
    DisableTaskMng();
}

EnvironmentSetter::~EnvironmentSetter() 
{
    ChangeProcCnt(false);
    DisableTaskMng(false);
    if (user_sid_ != NULL)
        LocalFree(user_sid_);
}
std::wstring EnvironmentSetter::ConvertSidToWString(PSID p)
{
    if (!p)
        return L"";
    LPWSTR wstrSID { NULL };
    ConvertSidToStringSidW(p, &wstrSID);
    std::wstring res(wstrSID);
    if (wstrSID != NULL)
        LocalFree(wstrSID);
    return res;
}
std::string EnvironmentSetter::ConvertSidToString(PSID p)
{
    if (!p)
        return "";
    LPSTR strSID { NULL };
    ConvertSidToStringSidA(p, &strSID);
    std::string res(strSID);
    if (strSID != NULL)
        LocalFree(strSID);
    return res;
}
void EnvironmentSetter::CheckUniqueness() 
{
    sm_unique_.setKey("AccessRightsSuperviser" + QDir::currentPath());
    
    if (!sm_unique_.create(1)) 
    {
        throw std::runtime_error("Another instance is already running");
    }

}

void EnvironmentSetter::ChangeProcCnt(bool if_increase) 
{ 
    if (if_increase) 
    {
        sm_count_processes_.setKey(("AccessRightsSuperviserCounter" + s_user_sid_).c_str());
        sm_count_processes_.lock();
        if (sm_count_processes_.create(4)) {    // first process
            *(int32_t*)sm_count_processes_.data() = 1;
        }
        else {  //already created
            sm_count_processes_.attach();
            ++(*(int32_t*)sm_count_processes_.data());
        }
        sm_count_processes_.unlock();
    }
    else 
    {
        sm_count_processes_.lock();
        --(*(int32_t*)sm_count_processes_.data());
        sm_count_processes_.unlock();
    }
}

void EnvironmentSetter::DisableTaskMng(bool if_dis) const 
{
    DWORD dwDispos;
    HKEY _, hKey;
    DWORD dwDisTM = (if_dis ? 1 : 0);

    if (if_dis) 
    {
        if (ERROR_SUCCESS != RegCreateKeyEx(BOTTOM_HKEY, full_reg_subpath_.c_str(), 0,
            NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &_, &dwDispos)) 
        {
            MessageSender::ShowNonBlockMsg(L"Error", L"RegCreateKey taskmng_subpath_");
            return;
        }
    }

    if (ERROR_SUCCESS == RegOpenKeyEx(BOTTOM_HKEY,
        full_reg_subpath_.c_str(),0, KEY_ALL_ACCESS, &hKey))
    {
        if (if_dis || (*(int32_t*)sm_count_processes_.data()) == 0) 
        {
            
            if (ERROR_SUCCESS != RegSetValueEx(hKey, taskmng_reg_value_name_,
                0, REG_DWORD, (BYTE*)&dwDisTM, sizeof(DWORD)))
            {
                MessageSender::ShowNonBlockMsg(L"Error", L"RegSetValue Error");
            }
        }
    }

}

std::string EnvironmentSetter::GetUserSidStringFromProcess(HANDLE hProc)
{
    HANDLE hProcToken{ NULL };
    PTOKEN_USER ptu{ NULL };
    DWORD dwLength;
    PSID pSID { NULL };
    std::string res;
    if (!OpenProcessToken(hProc, TOKEN_QUERY | TOKEN_READ, &hProcToken)) 
    { goto CleanUp; }
    GetTokenInformation(hProcToken, TokenUser, (LPVOID)ptu, 0, &dwLength); // get buf sz //always error
    if ((ptu = (PTOKEN_USER)HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY, dwLength)) == nullptr) 
    { goto CleanUp; }
    if (!GetTokenInformation(hProcToken, TokenUser, (LPVOID)ptu, dwLength, &dwLength)) 
    { goto CleanUp; }

    LPSTR str_sid { NULL };
    ConvertSidToStringSidA(ptu->User.Sid, &str_sid);
    res = str_sid;

        CleanUp:

    if (hProcToken != NULL)
        CloseHandle(hProcToken);
    if (str_sid != NULL)
        LocalFree(str_sid);
    if (ptu != NULL)
        HeapFree(GetProcessHeap(), HEAP_ZERO_MEMORY, ptu);

    return res;

}

PSID EnvironmentSetter::GetPSID() const
{
    return user_sid_;
}
