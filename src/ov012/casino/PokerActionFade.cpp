#include "ov012/casino/PokerAction.hpp"
#include "ov012/casino/CasinoPokerDraw.hpp"

THUMB void casino::PokerActionFade::setup()
{
    isEnd_ = false;
    for (int i = 0; i < 5; i++) {
        alpha_[i] = CasinoPokerDraw::getSingleton()->getAlpha();
    }
    if (alpha_[0] == 0) {
        fadeIn_ = true;
    } else {
        fadeIn_ = false;
    }
}

THUMB void casino::PokerActionFade::execute()
{
    if (fadeIn_ == true) {
        alpha_[index_]++;
    } else {
        alpha_[index_]--;
    }
    CasinoPokerDraw::getSingleton()->setAlpha(index_, alpha_[index_]);
    if (alpha_[index_] == 0 || alpha_[index_] == 0x1f) {
        isEnd_ = true;
    }
}
