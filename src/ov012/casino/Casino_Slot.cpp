#include "ov012/casino/Casino_Slot.hpp"
#include "main/sound/SoundManager.hpp"
#include "ov012/casino/CasinoCamera.hpp"
#include "ov012/casino/CasinoSlot.hpp"

inline void dss::UnkDualCamera::setAngle(Vector3<short> angle)
{
    m_camera0.setAngle(angle);
}

inline int casino::Casino_SlotMachine::getEffectLamp(int cnt)
{
    return hitData_[cnt];
}

static short unk_0212ced4[6] = {0, 0, 0, 0, -910, 0};

THUMB casino::Casino_Slot* casino::Casino_Slot::getSingleton()
{
    static Casino_Slot casinoSlot;
    return &casinoSlot;
}

THUMB casino::Casino_Slot::Casino_Slot()
{
    resultCoin_ = 1;
    betCoin_ = 0;
    slotTable_ = -1;
    rollSePlayer_ = 0;
}

THUMB casino::Casino_Slot::~Casino_Slot()
{
}

THUMB void casino::Casino_Slot::setSlotType(int type)
{
    slotTable_ = type;
    betCoin_ = 0;
    resultCoin_ = 0;
    slotMachine_.setupSlot(type);
}

THUMB void casino::Casino_Slot::resetSlot()
{
    betCoin_ = 0;
    resultCoin_ = 0;
    slotMachine_.resetSlot();
    CasinoSlot::getSingleton()->setLampOff();
}

THUMB void casino::Casino_Slot::addCoin(int& coin)
{
    int bet = betCoin_;
    if (bet >= MAX_BET) {
        return;
    }
    if (coin < betCost_) {
        return;
    }
    CasinoSlot::getSingleton()->setLineLamp(bet, true);
    SoundManager::playSe(0x156, 0);
    coin -= betCost_;
    betCoin_++;
}

THUMB void casino::Casino_Slot::instantAddCoin(int& coin, int count)
{
    bool add = false;
    for (int i = 0; i < count; i++) {
        int bet = betCoin_;
        if (bet < MAX_BET && coin >= betCost_) {
            CasinoSlot::getSingleton()->setLineLamp(bet, true);
            coin -= betCost_;
            betCoin_++;
            add = true;
        }
    }
    if (add) {
        SoundManager::playSe(0x156, 0);
    }
}

THUMB void casino::Casino_Slot::subCoin(int& coin)
{
    if (betCoin_ <= 0) {
        return;
    }
    coin += betCost_;
    betCoin_--;
    CasinoSlot::getSingleton()->setLineLamp(betCoin_, false);
    SoundManager::playSe(0x157, 0);
}

THUMB int casino::Casino_Slot::getResultAllCoin()
{
    int resultList[9] = {0};
    int reelCount;
    for (int i = 0; i < 9; i++) {
        resultList[i] = 0;
    }
    reelCount = 0;
    effectFlag_ = reelCount;
    for (int i = 0; i < betCoin_; i++) {
        resultList[i] = slotMachine_.getResultCoin(i);
    }
    CasinoSlot::getSingleton()->setLampOff();
    if (CasinoSlot::getSingleton()->bingoType_ == 2) {
        CasinoSlot::getSingleton()->setBigBingoAnim();
        effectFlag_ = true;
    }
    for (int i = 0; i < betCoin_; i++) {
        resultCoin_ += resultList[reelCount];
        reelCount++;
        if (reelCount >= 3) {
            reelCount -= 3;
        }
    }
    resultCoin_ *= betCost_;
    return resultCoin_;
}

THUMB bool casino::Casino_Slot::runningSlot()
{
    bool result = slotMachine_.scrollSlot();
    if (result) {
        SoundManager::stopSeWithIndex(0x158, 0);
    }
    return result;
}

THUMB void casino::Casino_Slot::cashCoin(int& coin)
{
    if (resultCoin_ <= 0) {
        return;
    }
    coin++;
    if (coin > MAX_COIN) {
        coin = MAX_COIN;
    }
    SoundManager::playSe(0x154, 0);
    resultCoin_--;
}

THUMB void casino::Casino_Slot::cashAllCoin(int& coin)
{
    coin += resultCoin_;
    if (coin > MAX_COIN) {
        coin = MAX_COIN;
    }
    resultCoin_ = 0;
}

THUMB int casino::Casino_Slot::startSlot()
{
    slotMachine_.resetSlot();
    slotMachine_.setCoordinateImage();
    resultCoin_ = 0;
    rollSePlayer_ = SoundManager::playSe(0x158, 0);
    return 0;
}

THUMB bool casino::Casino_Slot::showEffect()
{
    if (effectFlag_) {
        if (effectCounter_ < 240) {
            int angle = -0x50000;
            if (effectCounter_ < 120) {
                angle = (effectCounter_ << 14) - 0x50000;
                if (angle >= 0x10000) {
                    angle = 0x10000;
                }
            } else {
                int down = 0x10000 - ((effectCounter_ - 120) << 14);
                if (down > angle) {
                    angle = down;
                }
            }
            CasinoCamera::getSingleton()->camera_.setAngle(dss::Vector3<short>(angle / 360, unk_0212ced4[3], unk_0212ced4[1]));
            effectCounter_++;
        } else if (resultCoin_ == 0) {
            CasinoCamera::getSingleton()->camera_.setAngle(dss::Vector3<short>(unk_0212ced4[4], unk_0212ced4[2], unk_0212ced4[0]));
            effectCounter_ = 0;
            CasinoSlot::getSingleton()->stopEventAnim();
            return true;
        }
    } else {
        if (effectCounter_ >= 90 && resultCoin_ == 0) {
            effectCounter_ = 0;
            CasinoSlot::getSingleton()->stopEventAnim();
            return true;
        }
        if (effectCounter_ < 90) {
            effectCounter_++;
        }
    }
    return false;
}
