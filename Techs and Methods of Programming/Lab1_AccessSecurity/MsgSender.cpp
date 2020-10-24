#include "MsgSender.h"

std::list<std::future<int>> MessageSender::futures_;
std::mutex MessageSender::m_;

int MessageSender::_ShowMsg(std::wstring&& title, std::wstring&& msg)
{
    return MessageBox(NULL, msg.c_str(), title.c_str(), MB_OK);
}
void MessageSender::_RemoveFinished()
{
    auto it = futures_.begin();
    while (it != futures_.end()) {
        if (it->wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            it = futures_.erase(it);
        } else {
            it = std::next(it);
        }
    }
}
int MessageSender::ShowNonBlockMsg(std::wstring&& title, std::wstring&& msg)
{
    std::lock_guard lock(m_);
    _RemoveFinished();
    futures_.push_back(
        std::async(std::launch::async, &MessageSender::_ShowMsg,
            std::move(title), std::move(msg)));
    return 0;
}
int MessageSender::ShowBlockMsg(std::wstring&& title, std::wstring&& msg)
{
    return _ShowMsg(std::move(title), std::move(msg));
}
