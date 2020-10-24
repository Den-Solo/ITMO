#pragma once

#include "FilterDataStructs.h"
#include "MsgSender.h"
#include "SimpleSerializer.h"

#include <chrono>
#include <future>
#include <regex>
#include <string>
#include <string_view>
#include <thread>
#include <vector>
#include <unordered_set>
#include <fstream>

#include <aclapi.h>
#include <windows.h>

class Filter
{

private: // const vals
    const std::chrono::milliseconds sleep_time_ { 2000 }; //for DynamicCheck thread
    const std::wstring tmp_dir_name_ = L".AccessFilter";
    const std::wstring NFI_serilized_name_ = tmp_dir_name_ + L"/.NFI";
    const std::wstring PFI_serilized_name_ = tmp_dir_name_ + L"/.PFI";
    const PSID user_sid_;

private:
    std::vector<FilterData::NameFileInfo> name_files_info_;
    std::vector<FilterData::PatternFileInfo> pattern_files_info_;
    std::vector<WIN32_FIND_DATA> fdata_;
    std::vector<WIN32_FIND_DATA*> pfdata_; //files sorted by date
    std::unordered_set<std::wstring_view> blocked_files_;

    std::wregex regex_;
    FILETIME start_dyn_check_ { 0 };

    std::atomic_bool bExit_ { false };
    std::future<void> fDynCheck_;

private:
    static std::wstring WildcardToRegex(const std::wstring& wildcard);
    static std::wregex BuildRegex(const std::vector<std::wstring>& data);
    static void EnumFiles(std::vector<WIN32_FIND_DATA>& fdata, std::vector<WIN32_FIND_DATA*>& pfdata);


private:
    void CheckIfFinishedCorrectly();
    void ChangeUserAccess(const wchar_t* pwcObjName, FilterData::AccessInfo& ai, bool if_deny);

    void SetAccessByName(); // sets special access rights for file names
    void SetDefaultAccessByName(); // return original file access rights

    void SetStaticAccessByPattern();
    void SetDefaultStaticAccessByPattern();
    void FastDynCheckByPattern();
    void DeepDynCheckByPattern();

    void SetAccessByPattern(); // runs rules by pattern
    void KillAsync(); // stop async thread

public:
    Filter(
        std::vector<std::wstring>&& file_names,
        std::vector<std::wstring>&& pattern_file_names,
        PSID usr
    );
    ~Filter(); // restore rights, clean
};
