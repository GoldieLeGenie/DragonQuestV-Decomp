#include "ov012/casino/PokerAction.hpp"
#include "main/sound/SoundManager.hpp"
#include "ov012/casino/CasinoPokerDraw.hpp"
#include "ov012/casino/PokerManager.hpp"

inline int casino::PokerManager::getCardNo(int index)
{
    return gameCard_[index].no_;
}

inline int casino::PokerManager::getCardType(int index)
{
    return gameCard_[index].type_;
}

THUMB void casino::PokerActionReverse::setup()
{
    for (int i = 0; i < 5; i++) {
        ang_[i] = 0;
        gyre_[i] = 0;
    }
    distance_ = CasinoPokerDraw::getSingleton()->getDistance();
    isEnd_ = false;
    index_ = 0;
}

THUMB void casino::PokerActionReverse::execute()
{
    hopCard(index_);
    gyre_[index_]++;
    ang_[index_] += 0x800;
    if (gyre_[index_] == 8) {
        int type;
        int no = 0;
        if (doubleUp_ == true) {
            type = PokerManager::getSingleton()->getHighAndLowCardType(index_);
        } else {
            type = PokerManager::getSingleton()->getCardType(index_);
        }
        if (type != TYPE_JOKER) {
            if (doubleUp_ == true) {
                no = PokerManager::getSingleton()->getHighAndLowCardNo(index_);
            } else {
                no = PokerManager::getSingleton()->getCardNo(index_);
            }
        }
        CasinoPokerDraw::getSingleton()->setCardTexture(index_, type, no);
    }
    if (gyre_[index_] > 16) {
        gyre_[index_] = 0;
        ang_[index_] = 0;
        SoundManager::playSe(0x155, 0);
        isEnd_ = true;
    }
}
