#include "WinFileSys.h"

namespace WinFS {
bool FileExists(const std::wstring& name)
{
    DWORD ftyp = GetFileAttributes(name.c_str());
    if (ftyp == INVALID_FILE_ATTRIBUTES)
        return false; //something is wrong with your path!
    if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
        return false; // this is a directory!
    return true; // this is not a directory!
}
bool DirExists(const std::wstring& name)
{
    DWORD ftyp = GetFileAttributes(name.c_str());
    if (ftyp == INVALID_FILE_ATTRIBUTES)
        return false; //something is wrong with your path!
    if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
        return true; // this is a directory!
    return false; // this is not a directory!
}
bool RemoveFile(const std::wstring& file_name)
{
    return DeleteFile(file_name.c_str());
}
bool CreateDir(const std::wstring& dir_name)
{
    if (!DirExists(dir_name))
        return CreateDirectory(dir_name.c_str(), NULL);
    return true;
}
bool RemoveDir(const std::wstring& dir_name)
{
    if (DirExists(dir_name))
        return RemoveDirectory(dir_name.c_str());
    return true;
}
bool CreateNewFile(const std::wstring& dir_name)
{
    HANDLE h = CreateFile(dir_name.c_str(), GENERIC_READ | GENERIC_WRITE,
        0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (h == NULL)
        return false;
    CloseHandle(h);
    return true;
}
std::wstring GetCurrentDir()
{
    int dwSz { 0 };
    std::vector<uint8_t> buf;
    dwSz = GetCurrentDirectory(0, NULL);
    buf.resize(sizeof(wchar_t) * dwSz);
    if (!GetCurrentDirectory(dwSz, reinterpret_cast<wchar_t*>(buf.data())))
        return {};
    return reinterpret_cast<wchar_t*>(buf.data());
}
bool CopyOrRewriteFile(const std::wstring& from, const std::wstring& to)
{
    return CopyFile(from.c_str(), to.c_str(), false);
}

bool CreateLink(GUID folder, const std::wstring& path_obj, const std::wstring& link_name, const std::wstring& desc)
{
    HRESULT hres;
    IShellLink* psl;

    CoInitialize(NULL);

    hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_ALL, IID_IShellLink, (LPVOID*)&psl);
    if (SUCCEEDED(hres)) {
        IPersistFile* ppf;
        PWSTR folder_path { NULL };
        SHGetKnownFolderPath(folder, 0, NULL, &folder_path);
        // Set the path to the shortcut target and add the description.
        psl->SetPath(path_obj.c_str());
        psl->SetDescription(desc.c_str());

        // Query IShellLink for the IPersistFile interface, used for saving the
        // shortcut in persistent storage.
        hres = psl->QueryInterface(IID_IPersistFile, (LPVOID*)&ppf);

        if (SUCCEEDED(hres)) {
            // Save the link by calling IPersistFile::Save.
            WCHAR wsz[MAX_PATH]; 
            hres = _wmakepath_s(wsz, _MAX_PATH, NULL, folder_path,
                link_name.c_str(), L"lnk");
            hres = ppf->Save(wsz, TRUE);
            ppf->Release();
        }
        psl->Release();
        if (folder_path)
            CoTaskMemFree(folder_path);
    }
    CoUninitialize();
    return hres == S_OK;
}
bool CreateLinkStartMenu(const std::wstring& path_obj, const std::wstring& link_name, const std::wstring& desc)
{
    return CreateLink(FOLDERID_Programs, path_obj, link_name, desc);
}
bool CreateLinkDesktop(const std::wstring& path_obj, const std::wstring& link_name, const std::wstring& desc)
{
    return CreateLink(FOLDERID_Desktop, path_obj, link_name, desc);
}

bool RemoveLink(GUID folder,  const std::wstring& link_name)
{
    HRESULT hr = CoInitialize(NULL);
    PWSTR folder_path { NULL };

    SHGetKnownFolderPath(folder, 0, NULL, &folder_path);

    WCHAR wsz[MAX_PATH];
    hr = _wmakepath_s(wsz, _MAX_PATH, NULL, folder_path,
        link_name.c_str(), L"lnk");

    if (SUCCEEDED(hr)) {
        IShellItem* pitem;
        hr = SHCreateItemFromParsingName(wsz,NULL,
            IID_PPV_ARGS(&pitem));

        if (SUCCEEDED(hr)) {
            WinFS::RemoveFile(wsz);
        }
    }

    CoUninitialize();
    return hr == S_OK;
}
bool RemoveLinkStartMenu(const std::wstring& link_name)
{
    return RemoveLink(FOLDERID_Programs,  link_name);
}
bool RemoveLinkDesktop(const std::wstring& link_name)
{
    return RemoveLink(FOLDERID_Desktop, link_name);
}
}