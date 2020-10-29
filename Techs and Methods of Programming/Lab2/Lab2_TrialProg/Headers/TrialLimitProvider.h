#pragma once

#include "WinRegistry.h"

class TrialLimitProvider {

protected:
    int user_id_ { -1 };

public:
    virtual ~TrialLimitProvider() = default;
    virtual void SetUser(int user_id, bool is_new) = 0;
    virtual bool IsOver() const = 0;
    virtual std::wstring GetMsg() const = 0;
};