#include "ov005/fld/FieldAction.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/cmn/ExtraMapLink.hpp"
#include "main/dss/GameSystemManager.hpp"
#include "main/window/ScreenEffectManager.hpp"
#include "ov005/fld/FieldPlayerManager.hpp"
#include "ov005/fld/FieldStage.hpp"
#include "ov005/fld/FieldSystem.hpp"

inline void fld::FieldStage::reload()
{
    fieldData.reload();
}

inline void fld::FieldPlayerManager::reload()
{
    partyDraw_.reload();
}

THUMB int fld::FieldActionTabi::setup()
{
    counter_ = 0;
    start_ = 0;
    exitIndex_ = 0;
    return -1;
}

THUMB void fld::FieldActionTabi::execute()
{
    update();
}

THUMB int fld::FieldActionTabi::update()
{
    if (isEffectEnd() == true) {
        if (start_ == 0) {
            cmn::g_extraMapLink.setExtraExitTown(0x157, 0x7012c);
            cmn::g_cmnPartyInfo.setMenuAction(cmn::TABI_LINK);
        } else {
            FieldStage::getSingleton()->reload();
            FieldPlayerManager::getSingleton().reload();
            FieldSystem::getSingleton()->fieldSystemWorldMap_.imageMap.reload();
            args::GameSystemManager::getSingleton().setDrawExclusion(6, true);
            args::GameSystemManager::getSingleton().setDrawExclusion(7, true);
            args::GameSystemManager::getSingleton().setDrawExclusion(10, true);
            args::GameSystemManager::getSingleton().setDrawExclusion(1, true);
        }
        start_ = 0;
        FieldPlayerManager::getSingleton().setRemote(false);
        return 0;
    }
    return -1;
}

THUMB void fld::FieldActionTabi::start(int index, int flag)
{
    start_ = flag;
    window::gScreenEffect.effectStart(window::ScreenEffectManager::PLAY_BACK_TABI);
    if (flag == true) {
        window::gScreenEffect.tabiEffect_.unkfunc_02029ba4(1);
    }
    FieldPlayerManager::getSingleton().setRemote(true);
    counter_ = 0;
    exitIndex_ = index;
}

THUMB int fld::FieldActionTabi::isEffectEnd()
{
    return window::gScreenEffect.isEnd();
}

THUMB bool fld::FieldActionTabi::search()
{
    return false;
}
