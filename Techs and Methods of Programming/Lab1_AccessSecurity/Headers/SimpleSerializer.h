#pragma once

#include "FilterDataStructs.h"

#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

#include <windows.h>

class SimpleSerializer 
{
public:
    enum class Mode 
    {
        Serialize,
        Deserialize
    };

private:
    std::fstream fs_;
    const Mode mode_;

private:
    void Serialize(const std::wstring& data);
    void Serialize(bool val);
    void Serialize(const FilterData::AccessInfo& ai);
    void Serialize(const FilterData::NameFileInfo& nfi);
    void Serialize(const FilterData::PatternFileInfo& pfi);

    void Deserialize(std::wstring& data);
    void Deserialize(bool& val);
    void Deserialize(FilterData::AccessInfo& ai);
    void Deserialize(FilterData::NameFileInfo& nfi);
    void Deserialize(FilterData::PatternFileInfo& pfi);

public:
    static bool DirExists(const std::wstring name);
    static bool FileExists(const std::wstring name);
    static bool CreateDir(const std::wstring& dir_name);
    static bool RemoveDir(const std::wstring& dir_name);
    static bool CreateNewFile(const std::wstring& dir_name);
    static bool RemoveFile(const std::wstring& dir_name);

public:
    SimpleSerializer(const std::wstring& file_name, Mode mode);
    template <class T>
    void Serialize(const std::vector<T>& data);
    template <class T>
    void Deserialize(std::vector<T>& data);
};
template <class T>
void SimpleSerializer::Serialize(const std::vector<T>& data)
{
    if (mode_ != Mode::Serialize)
        throw std::runtime_error("SimpleSerializer - use serialize mod");
    size_t sz = data.size();
    fs_.write(reinterpret_cast<char*>(&sz), sizeof(size_t));
    for (const auto& elem : data) {
        Serialize(elem);
    }
}
template <class T>
void SimpleSerializer::Deserialize(std::vector<T>& data)
{
    if (mode_ != Mode::Deserialize)
        throw std::runtime_error("SimpleSerializer - use deserialize mod");
    size_t sz;
    fs_.read(reinterpret_cast<char*>(&sz), sizeof(size_t));
    data.resize(sz);
    for (auto& elem : data) {
        Deserialize(elem);
    }
}
