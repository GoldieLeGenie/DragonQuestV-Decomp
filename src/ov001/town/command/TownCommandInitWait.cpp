#include "ov001/town/command/TownCommandInitWait.hpp"
#include "main/town/TownCommandEncount.hpp"

#pragma thumb on

twn::TownCommandInitWait::TownCommandInitWait()
{
    count_ = 15;
    flag_ = true;
}

int twn::TownCommandInitWait::isExec()
{
    return flag_;
}

void twn::TownCommandInitWait::exec()
{
    CommandObjectDefineTownSystem::setAfterPartChange();
}

int twn::TownCommandInitWait::isEnd()
{
    if (--count_ == 0) {
        flag_ = false;
        return true;
    }
    return false;
}
