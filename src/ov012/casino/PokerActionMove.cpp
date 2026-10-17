#include "ov012/casino/PokerAction.hpp"
#include "ov012/casino/CasinoPokerDraw.hpp"

THUMB void casino::PokerActionMove::setup()
{
}

THUMB void casino::PokerActionMove::execute()
{
    int index = index_;
    dss::Fix32Vector3 pos = CasinoPokerDraw::getSingleton()->card[index].getPosition();
    dss::Fix32 space = CasinoPokerDraw::getSingleton()->getSpace();
    switch (direction_) {
    case 0:
        break;
    case 1:
        break;
    case 2:
        break;
    case 3:
        pos.vx.value -= 0x100;
        if (endPos_.vx.value >= pos.vx.value) {
            pos.vx.value = endPos_.vx.value;
            isEnd_ = true;
        }
        break;
    }
    CasinoPokerDraw::getSingleton()->setCardPosition(index_, pos);
}
