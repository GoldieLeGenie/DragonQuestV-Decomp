#include "ov012/casino/PokerAction.hpp"
#include "ov012/casino/CasinoPokerDraw.hpp"

THUMB bool casino::PokerActionBase::isEnd()
{
    if (isEnd_ == true) {
        isEnd_ = false;
        return true;
    }
    return false;
}

THUMB void casino::PokerActionBase::hopCard(int cardIndex)
{
    dss::Fix32Vector3 pos = CasinoPokerDraw::getSingleton()->card[cardIndex].getPosition();
    if (gyre_[cardIndex] < 8) {
        distance_.value += 0x200;
    }
    if (gyre_[cardIndex] > 8) {
        distance_.value -= 0x200;
    }
    pos.vy = distance_.value;
    CasinoPokerDraw::getSingleton()->setCardAngle(cardIndex, ang_[cardIndex]);
    CasinoPokerDraw::getSingleton()->setCardPosition(cardIndex, pos);
}
