#include "SimpleSerializer.h"

void SimpleSerializer::Serialize(const std::wstring& data)
{
    size_t sz = data.size();
    fs_.write(reinterpret_cast<char*>(&sz), sizeof(size_t));
    fs_.write(reinterpret_cast<const char*>(data.c_str()),
        sz * sizeof(std::wstring::value_type));
}
void SimpleSerializer::Serialize(bool val)
{
    fs_.write(reinterpret_cast<const char*>(&val), sizeof(bool));
}
void SimpleSerializer::Serialize(const FilterData::AccessInfo& ai)
{
    fs_.write(reinterpret_cast<const char*>(&ai), sizeof(FilterData::AccessInfo));
}
void SimpleSerializer::Serialize(const FilterData::NameFileInfo& nfi)
{
    Serialize(nfi.name);
    Serialize(nfi.ai);
    Serialize(nfi.if_created);
}
void SimpleSerializer::Serialize(const FilterData::PatternFileInfo& pfi)
{
    Serialize(pfi.name);
    Serialize(pfi.ai);
}

void SimpleSerializer::Deserialize(std::wstring& data)
{
    size_t sz;
    fs_.read(reinterpret_cast<char*>(&sz), sizeof(size_t));
    fs_.read(reinterpret_cast<char*>(data.data()),
        sz * sizeof(std::wstring::value_type));
}
void SimpleSerializer::Deserialize(bool& val)
{
    fs_.read(reinterpret_cast<char*>(&val), sizeof(bool));
}
void SimpleSerializer::Deserialize(FilterData::AccessInfo& ai)
{
    fs_.read(reinterpret_cast<char*>(&ai), sizeof(FilterData::AccessInfo));
}
void SimpleSerializer::Deserialize(FilterData::NameFileInfo& nfi)
{
    Deserialize(nfi.name);
    Deserialize(nfi.ai);
    Deserialize(nfi.if_created);
}
void SimpleSerializer::Deserialize(FilterData::PatternFileInfo& pfi)
{
    Deserialize(pfi.name);
    Deserialize(pfi.ai);
}

SimpleSerializer::SimpleSerializer(const std::wstring& file_name, Mode mode)
    : mode_(mode)
{
    std::ios_base::openmode m = (mode_ == Mode::Serialize ? std::fstream::out : std::fstream::in);
    fs_.open(file_name, std::fstream::binary | m);
    if (!fs_.is_open())
        throw std::runtime_error("serialization failed");
}


bool SimpleSerializer::CreateDir(const std::wstring& dir_name) 
{
    if (!DirExists(dir_name))
        return CreateDirectory(dir_name.c_str(), NULL); 
    return true;
}
bool SimpleSerializer::RemoveDir(const std::wstring& dir_name) 
{
    if (DirExists(dir_name))
        return RemoveDirectory(dir_name.c_str());
    return true;
}
bool SimpleSerializer::CreateNewFile(const std::wstring& dir_name) 
{
    HANDLE h = CreateFile(dir_name.c_str(), GENERIC_READ | GENERIC_WRITE, 
        0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL,NULL);
    if (h == NULL)
        return false;
    CloseHandle(h);
    return true;
}
bool SimpleSerializer::RemoveFile(const std::wstring& dir_name)
{
    return DeleteFile(dir_name.c_str());
}
bool SimpleSerializer::DirExists(const std::wstring name)
{
    DWORD ftyp = GetFileAttributes(name.c_str());
    if (ftyp == INVALID_FILE_ATTRIBUTES)
        return false; //something is wrong with your path!
    if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
        return true; // this is a directory!
    return false; // this is not a directory!
}
bool SimpleSerializer::FileExists(const std::wstring name) 
{
    DWORD ftyp = GetFileAttributes(name.c_str());
    if (ftyp == INVALID_FILE_ATTRIBUTES)
        return false; //something is wrong with your path!
    if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
        return false; // this is a directory!
    return true; // this is not a directory!
}