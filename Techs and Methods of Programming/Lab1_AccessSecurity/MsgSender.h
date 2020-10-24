#pragma once

#include <Windows.h>
#include <future>
#include <iostream>
#include <mutex>
#include <string>
#include <list>

class MessageSender 
{
private:
    static std::list<std::future<int>> futures_;
    static std::mutex m_;

private:
    static int _ShowMsg(std::wstring&& title, std::wstring&& msg);
    static void _RemoveFinished();

public:
    MessageSender() = default;
    ~MessageSender() = default;

    static int ShowNonBlockMsg(std::wstring&& title, std::wstring&& msg);
    static int ShowBlockMsg(std::wstring&& title, std::wstring&& msg);
};
