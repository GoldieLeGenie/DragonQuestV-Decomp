#include "ov001/town/TownFukubikiDraw.hpp"
#include "ov001/town/TownStageManager.hpp"
#include "main/cmn/CommonCounterInfo.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/dss/TextureObject.hpp"
#include "main/object/BillboardCharacter.hpp"
#include "main/sound/SoundManager.hpp"

inline DSSAObject2D::DSSAObject2D()
{
}

inline DSSAObject2D::~DSSAObject2D()
{
}

THUMB twn::TownFukubikiDraw::TownFukubikiDraw()
{
    enable_ = false;
    isEnd_ = true;
    garagaraCounter_ = 0;
    drawCounter_ = 0;
}

THUMB twn::TownFukubikiDraw::~TownFukubikiDraw()
{
}

THUMB twn::TownFukubikiDraw& twn::TownFukubikiDraw::getSingleton()
{
    static TownFukubikiDraw townFukubikiDraw_;
    return townFukubikiDraw_;
}

THUMB void twn::TownFukubikiDraw::garagaraSetup(int number)
{
    isEnd_ = false;
    garagaraCounter_ = 0;
    drawCounter_ = 0;
    initialize();
    setup(number);
    TownStageManager::getSingleton()->setObjectDraw(0x12f2, 2, 1);
}

THUMB void twn::TownFukubikiDraw::execute()
{
    if (isEnd_ == true) {
        return;
    }
    if (garagaraCounter_ > 0x30) {
        draw();
        if (garagaraCounter_ == 0x31) {
            SoundManager::stopSeWithIndex(0x15d, 0);
            garagaraCounter_++;
        }
        if (drawCounter_ < 0x78) {
            if (drawCounter_ == 0x23) {
                SoundManager::playSe(0x15e, 0);
            }
            drawCounter_++;
        } else if (drawCounter_ > 0xb4 || cmn::g_CommonCounterInfo.checkBottun() == true) {
            cleanup();
            terminate();
            isEnd_ = true;
            BillboardCharacter::setAllCharaAnim(true);
        } else {
            drawCounter_++;
        }
    } else {
        if (garagaraCounter_ == 0) {
            seCtrl_ = SoundManager::playSe(0x15d, 0);
        }
        garagaraCounter_++;
    }
}

THUMB void twn::TownFukubikiDraw::initialize()
{
    char path[0x80];
    dss::sprintf_s(path, sizeof(path), "data/fukubiki/fukubiki.tex");
    lotteryTextureData_.setup(path, 0, 0);
    lotteryTexture_ = (TextureObject*)lotteryTextureData_.getAddr();
    lotteryTexture_->unkfunc_02049e9c(1);
}

THUMB void twn::TownFukubikiDraw::setup(int number)
{
    char path[0x80];
    dss::sprintf_s(path, sizeof(path), "data/fukubiki/fukubiki_%02d.dssa", number);
    lotteryAnimData_.setup(path, 0, 0);
    lotteryAnim_.setup(lotteryAnimData_.getAddr());
    lotteryAnim_.setTexture(lotteryTexture_);
    dss::sprintf_s(path, sizeof(path), "data/fukubiki/fukubiki_1%d.dssa", number);
    lotteryStopAnimData_.setup(path, 0, 0);
    lotteryStopAnim_.setup(lotteryStopAnimData_.getAddr());
    lotteryStopAnim_.setTexture(lotteryTexture_);
    enable_ = true;
    number_ = number;
    lotteryAnim_.start(0);
}

THUMB void twn::TownFukubikiDraw::cleanup()
{
    lotteryAnim_.cleanup();
    lotteryStopAnim_.cleanup();
    lotteryAnimData_.cleanup();
    lotteryStopAnimData_.cleanup();
    enable_ = false;
}

THUMB void twn::TownFukubikiDraw::terminate()
{
    lotteryTexture_->unkfunc_02049f90();
    lotteryTextureData_.cleanup();
}

THUMB void twn::TownFukubikiDraw::draw()
{
    if (enable_) {
        if (!lotteryAnim_.isEnd()) {
            if (getDisplayFrame() & 1) {
                lotteryAnim_.draw();
            }
            lotteryAnim_.execute();
        } else if (getDisplayFrame() & 1) {
            lotteryStopAnim_.draw();
        }
    }
}
