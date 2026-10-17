#include "ov001/town/player/TownActionTabi.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov001/town/TownCharacterManager.hpp"
#include "ov001/town/TownStageManager.hpp"
#include "ov001/town/TownStageEffectManager.hpp"
#include "ov001/town/TownActionCalculate.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/cmn/ExtraMapLink.hpp"
#include "main/dss/GameSystemManager.hpp"
#include "main/global/Global.hpp"
#include "main/global/StageLink.hpp"
#include "main/object/BillboardCharacter.hpp"
#include "main/window/ScreenEffectManager.hpp"

#pragma thumb on

inline int Global::getMapNameId()
{
    return nextMapNameId;
}

inline void twn::TownPlayerManager::setMapLink(bool flag)
{
    flagMapLink_ = flag;
}

int twn::TownActionTabi::setup()
{
    counter = 0;
    start_ = false;
    exitIndex_ = 0;
    return -1;
}

void twn::TownActionTabi::execute()
{
    update();
}

int twn::TownActionTabi::update()
{
    if (isEffectEnd() == true) {
        if (start_ == false) {
            int nameId = util::StageLink::getNameId(g_Global.getMapNameId(), exitIndex_);
            TownPlayerManager::getSingleton().resetMapLink(RESET_EXIT_LOCK_TABI);
            if ((exitIndex_ & 0xfff) >= 300) {
                cmn::g_extraMapLink.setFieldTabi(exitIndex_);
            } else {
                cmn::g_extraMapLink.setExtraExitTown(nameId, exitIndex_);
            }
            cmn::g_cmnPartyInfo.setMenuAction(cmn::TABI_LINK);
        } else {
            TownPlayerManager::getSingleton().player_.actionType_ = ACTION_TYPE_WALK;
            TownPlayerManager::getSingleton().resetMapLink(RESET_EXIT_LOCK_TABI);
            TownPlayerManager::getSingleton().partyDraw_.requestCharacterReload();
            TownCharacterManager::getSingleton()->requestCharacterReload();
            BillboardCharacter::unkfunc_0205646c();
            TownStageManager::getSingleton()->stage_.resettingTexture();
            args::GameSystemManager::getSingleton().setExclusion(8, true);
            args::GameSystemManager::getSingleton().setDrawExclusion(2, true);
            args::GameSystemManager::getSingleton().setDrawExclusion(3, true);
            args::GameSystemManager::getSingleton().setDrawExclusion(4, true);
            args::GameSystemManager::getSingleton().setDrawExclusion(5, true);
            args::GameSystemManager::getSingleton().setDrawExclusion(6, true);
            args::GameSystemManager::getSingleton().setDrawExclusion(7, true);
            args::GameSystemManager::getSingleton().setDrawExclusion(8, true);
            args::GameSystemManager::getSingleton().setDrawExclusion(9, true);
            args::GameSystemManager::getSingleton().setDrawExclusion(0xd, true);
            args::GameSystemManager::getSingleton().setDrawExclusion(0xa, true);
            args::GameSystemManager::getSingleton().setDrawExclusion(0xb, true);
            args::GameSystemManager::getSingleton().setDrawExclusion(0xe, true);
            args::GameSystemManager::getSingleton().setDrawExclusion(0xf, true);
            args::GameSystemManager::getSingleton().setDrawExclusion(0xc, true);
            args::GameSystemManager::getSingleton().setDrawExclusion(0x11, true);
            TownStageEffectManager::getSingleton()->loadStage();
        }
        TownPlayerManager::getSingleton().setRemote(false);
    }
    position_.vy += TownPlayerAction::collR;
    TownActionCalculate::townStageColl(position_, position_, TownPlayerAction::collR, TownPlayerAction::surfaceR, TownPlayerAction::townCharaPreR);
    position_.vy -= TownPlayerAction::collR;
    TownPlayerManager::getSingleton().setMapLink(true);
    return -1;
}

void twn::TownActionTabi::start(int exitIndex, bool startFlag)
{
    window::gScreenEffect.effectStart(window::ScreenEffectManager::PLAY_BACK_TABI);
    start_ = startFlag;
    if (startFlag == true) {
        window::gScreenEffect.tabiEffect_.unkfunc_02029ba4(true);
    }
    TownPlayerManager::getSingleton().setRemote(true);
    TownPlayerManager::getSingleton().lockMapLink(EXIT_LOCK_TABI);
    counter = 0;
    exitIndex_ = exitIndex;
}

int twn::TownActionTabi::isEffectEnd()
{
    return window::gScreenEffect.isEnd();
}
