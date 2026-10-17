#include "main/cmn/PlayerAction.hpp"

THUMB cmn::PlayerAction::PlayerAction()
{
}

THUMB cmn::PlayerAction::~PlayerAction()
{
}

THUMB void cmn::PlayerAction::unkfunc_02014160()
{
}

THUMB void cmn::PlayerAction::unkfunc_02014164()
{
}

THUMB void cmn::PlayerAction::inputPad(int dir)
{
    padInput_ = 1;
    dirInput_ = dir << 13;
}

THUMB void cmn::PlayerAction::inputClear()
{
    padInput_ = 0;
}
