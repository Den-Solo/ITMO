#include "filter.h"

Filter::Filter(
    std::vector<std::wstring>&& file_names,
    std::vector<std::wstring>&& pattern_file_names,
    PSID usr)
    : user_sid_(usr)
{
    if (!SimpleSerializer::CreateDir(tmp_dir_name_))
        MessageSender::ShowNonBlockMsg(L"Not Critical Error", L"Cannot create TMP folder");
    FilterData::AccessInfo _; // not used
    ChangeUserAccess(tmp_dir_name_.c_str(), _, true);

    try {
        CheckIfFinishedCorrectly();
    } catch (...) {
        MessageSender::ShowNonBlockMsg(L"Error", L"Cannot restore settings");
    }

    name_files_info_.resize(file_names.size());
    for (size_t i = 0; i < file_names.size(); ++i) {
        name_files_info_[i].name = std::move(file_names[i]);
    }
    regex_ = BuildRegex(pattern_file_names);
    SetAccessByName();
    if (pattern_file_names.size() > 0)
        fDynCheck_ = std::async(std::launch::async, &Filter::SetAccessByPattern, this);
}

Filter::~Filter()
{
    KillAsync();
    SetDefaultAccessByName();
    if (!SimpleSerializer::RemoveDir(tmp_dir_name_))
        MessageSender::ShowNonBlockMsg(L"Error", L"Cannot delete TMP folder");
}
void Filter::CheckIfFinishedCorrectly()
{
    if (SimpleSerializer::FileExists(NFI_serilized_name_)) // finished incorrectly
    {
        SimpleSerializer ss(NFI_serilized_name_, SimpleSerializer::Mode::Deserialize);
        ss.Deserialize(name_files_info_);
        SetDefaultAccessByName();
    }
    if (SimpleSerializer::FileExists(PFI_serilized_name_)) // finished incorrectly
    {
        SimpleSerializer ss(PFI_serilized_name_, SimpleSerializer::Mode::Deserialize);
        ss.Deserialize(pattern_files_info_);
        SetDefaultStaticAccessByPattern();
    }
}

void Filter::ChangeUserAccess(const wchar_t* pwcObjName, FilterData::AccessInfo& ai, bool if_deny)
{
    DWORD dwRes = 0;
    PACL pOldDACL = NULL, pNewDACL = NULL;
    PSECURITY_DESCRIPTOR pSD = NULL;
    PSID psidOwner;

    EXPLICIT_ACCESS ea {
        if_deny ? GENERIC_ALL : ai.access_perms,
        if_deny ? DENY_ACCESS : static_cast<ACCESS_MODE>(ai.access_mode),
        if_deny ? NO_INHERITANCE : ai.inheritance,
        { 0, NO_MULTIPLE_TRUSTEE, TRUSTEE_IS_SID, TRUSTEE_IS_USER, (LPWCH)user_sid_ }
    };

    if (if_deny) { //save initial access rights
        // Get a pointer to the existing DACL.
        dwRes = GetNamedSecurityInfo(pwcObjName, SE_FILE_OBJECT,
            DACL_SECURITY_INFORMATION,
            &psidOwner, NULL, &pOldDACL, NULL, &pSD);
        ULONG cnt;
        PEXPLICIT_ACCESS ea_arr;
        GetExplicitEntriesFromAcl(pOldDACL, &cnt, &ea_arr);
        if (cnt > 0) {
            ai.access_perms = ea_arr[0].grfAccessMode;
            ai.inheritance = ea_arr[0].grfInheritance;
            ai.access_mode = ea_arr[0].grfAccessMode;
        }
    }

    // set EXPLICIT_ACCESS to get pNewDACL

    dwRes = SetEntriesInAcl(1, &ea, NULL, &pNewDACL);
    if (ERROR_SUCCESS != dwRes) {
        MessageSender::ShowNonBlockMsg(L"Error", (std::wstring(L"::SetEntriesInAcl ") + pwcObjName).c_str());
        goto Cleanup;
    }

    // Attach the new ACL as the object's DACL.

    dwRes = SetNamedSecurityInfo((LPWSTR)pwcObjName, SE_FILE_OBJECT,
        DACL_SECURITY_INFORMATION,
        NULL, NULL, pNewDACL, NULL);
    if (ERROR_SUCCESS != dwRes) {
        MessageSender::ShowNonBlockMsg(L"Error", (std::wstring(L"::SetNamedSecurityInfo ") + pwcObjName).c_str());
        goto Cleanup;
    }

Cleanup:
    if (pSD != NULL)
        LocalFree((HLOCAL)pSD);
    if (pNewDACL != NULL)
        LocalFree((HLOCAL)pNewDACL);
}

void Filter::SetAccessByName()
{
    for (size_t i = 0; i < name_files_info_.size(); ++i) {
        DWORD dwFileAttr = GetFileAttributes(name_files_info_[i].name.c_str());
        if (dwFileAttr == INVALID_FILE_ATTRIBUTES) { //doesn't exit
            HANDLE hFile = CreateFile(name_files_info_[i].name.c_str(), GENERIC_WRITE, 0,
                NULL, CREATE_NEW, FILE_ATTRIBUTE_HIDDEN, NULL);
            if (hFile == INVALID_HANDLE_VALUE) {
                MessageSender::ShowNonBlockMsg(L"Error", (std::wstring(L"SetAccessByName::CreateFile ") + name_files_info_[i].name).c_str());
                return;
            }
            if (hFile != INVALID_HANDLE_VALUE && hFile != NULL)
                CloseHandle(hFile);
            name_files_info_[i].if_created = true;
        } else if (dwFileAttr & FILE_ATTRIBUTE_DIRECTORY)
            continue;

        ChangeUserAccess(name_files_info_[i].name.c_str(), name_files_info_[i].ai, true);
        blocked_files_.emplace(name_files_info_[i].name);
    }
    try {
        SimpleSerializer ss(NFI_serilized_name_, SimpleSerializer::Mode::Serialize);
        ss.Serialize(name_files_info_);
    } catch (std::runtime_error& e) {
        MessageSender::ShowNonBlockMsg(L"Error", L"Serializtion failed NFI");
    }
}

void Filter::SetDefaultAccessByName()
{
    for (size_t i = 0; i < name_files_info_.size(); ++i) {
        if (name_files_info_[i].if_created) {
            DeleteFile(name_files_info_[i].name.c_str());
        } else {
            ChangeUserAccess(name_files_info_[i].name.c_str(), name_files_info_[i].ai, false);
        }
    }
    DeleteFile(NFI_serilized_name_.c_str());
}

std::wstring Filter::WildcardToRegex(const std::wstring& wildcard)
{
    std::wstring res;
    res.reserve(wildcard.size() + 5);
    for (const auto ch : wildcard) {
        switch (ch) {
        case L'.':
            res += L"\\.";
            break;
        case L'*':
            res += L".*";
            break;
        case L'?':
            res += L".?";
            break;
        default:
            res += ch;
        }
    }
    return res;
}

std::wregex Filter::BuildRegex(const std::vector<std::wstring>& data)
{
    std::wstring reg_str;
    reg_str.reserve(100);

    for (size_t i = 0; i < data.size(); ++i) {
        if (i != 0)
            reg_str += L'|';
        reg_str += WildcardToRegex(data[i]);
    }
    return std::wregex(reg_str);
}

void Filter::EnumFiles(std::vector<WIN32_FIND_DATA>& fdata, std::vector<WIN32_FIND_DATA*>& pfdata)
{
    fdata.clear();
    pfdata.clear();
    fdata.reserve(20);

    WIN32_FIND_DATA fd;
    HANDLE hFind = ::FindFirstFile(L"*.*", &fd);
    while (INVALID_HANDLE_VALUE != hFind) {
        if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
            fdata.push_back(fd);
        if (!::FindNextFile(hFind, &fd)) {
            ::FindClose(hFind);
            break;
        }
    }
    pfdata.resize(fdata.size());
    for (auto i = 0; i < fdata.size(); ++i)
        pfdata[i] = &fdata[i];
    // sort by date in reverse order
    std::sort(pfdata.begin(), pfdata.end(),
        [](WIN32_FIND_DATA* elem1, WIN32_FIND_DATA* elem2) {
            return CompareFileTime(&elem1->ftLastAccessTime, &elem2->ftLastAccessTime) > 0;
        });
}

void Filter::SetStaticAccessByPattern()
{
    EnumFiles(fdata_,pfdata_);
    for (auto i = 0; i < pfdata_.size(); ++i) {
        if (std::regex_match(pfdata_[i]->cFileName, regex_)
            && blocked_files_.find(pfdata_[i]->cFileName) == blocked_files_.end()) {
            pattern_files_info_.push_back({ pfdata_[i]->cFileName, FilterData::AccessInfo {} });
            ChangeUserAccess(pattern_files_info_.back().name.c_str(), pattern_files_info_.back().ai, true);
            blocked_files_.emplace(pattern_files_info_.back().name);
        }
    }
    if (fdata_.size())
        start_dyn_check_ = pfdata_[0]->ftLastAccessTime;
    try {
        SimpleSerializer ss(PFI_serilized_name_, SimpleSerializer::Mode::Serialize);
        ss.Serialize(pattern_files_info_);
    } catch (std::runtime_error& e) {
        MessageSender::ShowNonBlockMsg(L"Error", L"Serializtion failed PFI");
    }
}

void Filter::SetDefaultStaticAccessByPattern()
{
    for (size_t i = 0; i < pattern_files_info_.size(); ++i) {
        ChangeUserAccess(pattern_files_info_[i].name.c_str(), pattern_files_info_[i].ai, false);
    }
    DeleteFile(PFI_serilized_name_.c_str());
}

void Filter::FastDynCheckByPattern()
{
    EnumFiles(fdata_, pfdata_);
    int i { 0 };
    while (i < pfdata_.size()
        && (CompareFileTime(&start_dyn_check_, &pfdata_[i]->ftLastAccessTime) < 0)) 
    {
        if (std::regex_match(pfdata_[i]->cFileName, regex_)
            && blocked_files_.find(pfdata_[i]->cFileName) == blocked_files_.end()) 
        {
            MessageSender::ShowNonBlockMsg(L"Invalid Access",
                (std::wstring(L"You cannot create ") + pfdata_[i]->cFileName).c_str());
            DeleteFile(pfdata_[i]->cFileName);
        }
        ++i;
    }
}
void Filter::DeepDynCheckByPattern()
{
    EnumFiles(fdata_, pfdata_);
    int i { 0 };
    while (i < pfdata_.size()) 
    {
        if (std::regex_match(pfdata_[i]->cFileName, regex_)
            && blocked_files_.find(pfdata_[i]->cFileName) == blocked_files_.end()) 
        {
            MessageSender::ShowNonBlockMsg(L"Invalid Access",
                (std::wstring(L"You cannot create ") + pfdata_[i]->cFileName).c_str());
            DeleteFile(pfdata_[i]->cFileName);
        }
        ++i;
    }
}

void Filter::SetAccessByPattern()
{
    SetStaticAccessByPattern();
    size_t i = 0;
    while (!bExit_) {
        if (i == 5) {
            DeepDynCheckByPattern();
            i = 0;
        } else {
            FastDynCheckByPattern();
        }
        std::this_thread::sleep_for(sleep_time_);
        ++i;
    }
    SetDefaultStaticAccessByPattern();
}

void Filter::KillAsync()
{
    bExit_ = true;
    if (fDynCheck_.valid())
        fDynCheck_.get();
}
