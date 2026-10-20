#pragma ipa file
#include "ov019/townmenu/town_magic/TownMenu_MAGIC_MOVE.hpp"
#include "ov019/townmenu/town_magic/TownMenu_MAGIC_ROOT.hpp"
#include "ov019/townmenu/TownMenuPlayerControl.hpp"
#include "ov019/townmenu/TownMenu_ROOT.hpp"
#include "ov019/townmenu/UnkMenuTemplateTown.hpp"
#include "ov019/townmenu/UnkTownMenuDraw.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov005/fld/FieldPlayerManager.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/cmn/CommonRuraData.hpp"
#include "main/cmn/PartyTalk.hpp"
#include "main/cmn/TalkSoundManager.hpp"
#include "main/global/UnkGlobalSystem.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/MenuUpdateAssist.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/sound/SoundManager.hpp"
#include "main/status/CharacterStatus.hpp"
#include "main/status/GameFlag.hpp"
#include "main/status/HaveStatusInfo.hpp"
#include "main/status/MenuStatus.hpp"
#include "main/status/StageAttribute.hpp"
#include "main/status/StageInfo.hpp"
#include "main/status/UseActionMacro.hpp"
#include "main/status/UseActionParam.hpp"
#include "main/text/TextAPI.hpp"

using menu::MenuStatusInfo;
using menu::TownMenuPlayerControl;

inline int status::HaveStatus::getPlayerIndex() const
{
    return playerIndex_;
}

inline int status::HaveStatusInfo::getPlayerIndex() const
{
    return haveStatus_.getPlayerIndex();
}

inline status::UseActionMessage::UseActionMessage()
{
    clear();
}

inline status::UseActionParam::UseActionParam()
{
    clear();
}

inline status::UseActionParam::~UseActionParam()
{
}

inline status::CharacterStatus* status::UseActionParam::getActorCharacterStatus()
{
    return actorCharacterStatus_;
}

inline status::CharacterStatus* status::UseActionParam::getTargetCharacterStatus(int index)
{
    return targetCharacterStatus_[index];
}

inline int status::UseActionParam::getActionIndex()
{
    return actionIndex_;
}

inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo()
{
    return haveStatusInfo_;
}

inline int status::UseActionMessage::getExecMessage(int index)
{
    return execMessage_[index];
}

inline int status::UseActionMessage::getResultMessage(int index)
{
    return resultMessage_[index];
}

inline void status::MenuStatus::setActorIndex(short actor)
{
    actorIndex_ = actor;
}

inline void status::MenuStatus::setMenuEventFlag(bool flag)
{
    menuEventFlag_ = flag;
}

inline int status::MenuStatus::getLuraDisableMessage(int index)
{
    return messageNo_[index];
}

inline int status::MenuStatus::getLuraDisableMessageVoice(int index)
{
    return messageVoice_[index];
}

THUMB void TownMenu_MAGIC_MOVE::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    navigator_.setupBase();
    isResult_ = 0;
    int count = 0;
    for (unsigned int i = 1; i < 21; i++) {
        if (g_AreaFlag.check(i) == true) {
            moveTown_[count] = i;
            count++;
        }
    }
    navigator_.setup(2, 4, count);
}

THUMB void TownMenu_MAGIC_MOVE::menuExecute()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    townMenuSelectMagic(&menuItem_, navigator_.getCountInPage(), menuItem_.active_);
}

THUMB void TownMenu_MAGIC_MOVE::menuDraw()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    int open = gTownMenu_MESSAGE.isOpen();
    drawWarpTownSelectScreen(open, navigator_.getPageNo());
    if (!open) {
        menuItem_.drawActive();
    }
}

THUMB void TownMenu_MAGIC_MOVE::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    if (gTownMenu_MESSAGE.isOpen()) {
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK || stat == MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
            close();
            gTownMenu_ROOT.stat_ = MENUBASE_STAT_OK;
            if (isResult_ == 1) {
                cmn::g_cmnPartyInfo.setMenuAction(cmn::MENU_RURA_SUCCESS);
                status::g_StageInfo.setRuraTownID(moveTown_[navigator_.getIndex(menuItem_.active_)]);
                cmn::PartyTalk::getSingleton().resetPartyTalk();
                return;
            }
            if (!status::g_StageAttribute.isRula() && !status::g_StageAttribute.isRulaDisable()) {
                cmn::g_cmnPartyInfo.setMenuAction(cmn::MENU_RURA_FAILED);
            }
        }
        return;
    }
    int count = cmn::CommonRuraData::getSingleton().getRuraCount();
    int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
    navigator_.setup(2, 4, count);
    if (result != 0) {
        TownMenuPlayerControl::getSingleton();
        if (result == 3) {
            close();
            gTownMenu_MAGIC_ROOT.open();
        }
        if (result == 2) {
            moveTown();
        }
        redraw_ = 1;
    }
}

THUMB void TownMenu_MAGIC_MOVE::moveTown()
{
    if (status::g_Menu.checkMenuEventNo(0x81) == true) {
        status::g_Menu.setMenuEventFlag(true);
        status::g_StageInfo.setRuraTownID(moveTown_[navigator_.getIndex(menuItem_.active_)]);
        close();
        gTownMenu_ROOT.stat_ = MENUBASE_STAT_OK;
        if (data_02101c88.isCurrentPart(4)) {
            twn::TownPlayerManager::getSingleton().setLock(true);
        } else if (data_02101c88.isCurrentPart(6)) {
            fld::FieldPlayerManager::getSingleton().setLock(true);
        }
        return;
    }
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    status::UseActionParam useActionParam;
    int activeChara = TownMenuPlayerControl::getSingleton()->activeChara_;
    MenuStatusInfo::usePlayerMagic(useActionParam, activeChara, activeChara, 0x81);
    isResult_ = useActionParam.result_;
    status::g_Menu.setActorIndex(useActionParam.getActorCharacterStatus()->getHaveStatusInfo().getPlayerIndex());
    status::UseActionMacro::setExecMacro(useActionParam.getActorCharacterStatus(), useActionParam.getTargetCharacterStatus(0), useActionParam.getActionIndex());
    TextAPI::setMACRO0(1, 0x50000000, useActionParam.getActorCharacterStatus()->getHaveStatusInfo().getPlayerIndex());
    if (status::g_Menu.getLuraDisableMessage(0) != 0 && isResult_ == 0) {
        for (int i = 0; i < 3; i++) {
            cmn::g_talkSound.setOrderMessage(status::g_Menu.getLuraDisableMessageVoice(i));
        }
        cmn::g_talkSound.setMessageSound(3, -1);
        gTownMenu_MESSAGE.openMessageForTALK();
        for (int i = 0; i < 3; i++) {
            int message = status::g_Menu.getLuraDisableMessage(i);
            if (message != 0) {
                gTownMenu_MESSAGE.addMessage(message);
                cmn::PartyTalk::getSingleton().setPreMessageNo(message);
            }
        }
        return;
    }
    SoundManager::playSe(0x132, 0);
    gTownMenu_MESSAGE.openMessageForMENU();
    status::UseActionMessage& useActionMessage = useActionParam.message_[0];
    for (int i = 0; useActionMessage.getExecMessage(i) != 0; i++) {
        gTownMenu_MESSAGE.addMessage(useActionMessage.getExecMessage(i));
    }
    if (status::g_StageAttribute.isRulaDisable() == true) {
        for (int i = 0; useActionMessage.getResultMessage(i) != 0; i++) {
            gTownMenu_MESSAGE.addMessage(useActionMessage.getResultMessage(i));
        }
    }
}
