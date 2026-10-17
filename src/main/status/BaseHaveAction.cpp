#include "main/status/BaseHaveAction.hpp"

THUMB status::BaseHaveAction::BaseHaveAction()
{
    clear();
}

THUMB status::BaseHaveAction::~BaseHaveAction()
{
}

THUMB void status::BaseHaveAction::clear()
{
    battleAction_ = 0;
    usuallyAction_ = 0;
    actionLevel_ = 0;
    actionFlag_ = 0;
}

THUMB bool status::BaseHaveAction::isEnable()
{
    if (battleAction_ != 0 || usuallyAction_ != 0) {
        return true;
    }
    return false;
}

THUMB void status::BaseHaveAction::add(int battleAction, int usuallyAction)
{
    battleAction_ = battleAction;
    usuallyAction_ = usuallyAction;
    actionFlag_ |= FLAG_REMEMBER;
}

THUMB int status::BaseHaveAction::getAction()
{
    return battleAction_;
}

THUMB int status::BaseHaveAction::getUsuallyAction()
{
    return usuallyAction_;
}

THUMB bool status::BaseHaveAction::isRemember()
{
    if (isEnable() && (actionFlag_ & FLAG_REMEMBER)) {
        return true;
    }
    return false;
}

THUMB void status::BaseHaveAction::remembering()
{
    if (isEnable()) {
        actionFlag_ |= FLAG_REMEMBERING;
    }
}

THUMB bool status::BaseHaveAction::isRemembering()
{
    if (isEnable() && (actionFlag_ & FLAG_REMEMBERING)) {
        return true;
    }
    return false;
}

THUMB void status::BaseHaveAction::clearRemembering()
{
    if (actionFlag_ & FLAG_REMEMBERING) {
        actionFlag_ &= ~FLAG_REMEMBERING;
    }
}
