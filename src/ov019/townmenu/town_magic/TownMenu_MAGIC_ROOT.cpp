#pragma ipa file
#include "ov019/townmenu/town_magic/TownMenu_MAGIC_ROOT.hpp"
#include "ov019/townmenu/town_magic/TownMenu_MAGIC_CHARSELECT.hpp"
#include "ov019/townmenu/town_magic/TownMenu_MAGIC_MOVE.hpp"
#include "ov019/townmenu/town_magic/UnkTownMenuMagicChara.hpp"
#include "ov019/townmenu/TownMenuPlayerControl.hpp"
#include "ov019/townmenu/TownMenu_ROOT.hpp"
#include "ov019/townmenu/UnkMenuTemplateTown.hpp"
#include "ov019/townmenu/UnkTownMenuDraw.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov005/fld/FieldPlayerManager.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/cmn/CommonRuraData.hpp"
#include "main/cmn/NonBattleActionManager.hpp"
#include "main/cmn/PartyTalk.hpp"
#include "main/cmn/TalkSoundManager.hpp"
#include "main/global/UnkGlobalSystem.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/MenuUpdateAssist.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/sound/SoundManager.hpp"
#include "main/status/CharacterStatus.hpp"
#include "main/status/HaveStatusInfo.hpp"
#include "main/status/MenuStatus.hpp"
#include "main/status/StageAttribute.hpp"
#include "main/status/UseAction.hpp"
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

inline void TownMenuPlayerControl::setActiveMagic(unsigned char active)
{
    activeMagic_ = active;
}

THUMB void TownMenu_MAGIC_ROOT::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    menuItem_.active_ = TownMenuPlayerControl::getSingleton()->activeMagic_;
    navigator_.setupBase();
    isResult_ = 0;
    magicID_ = 0;
    targetCount_ = 0;
    soundCount_ = 0;
}

THUMB void TownMenu_MAGIC_ROOT::menuExecute()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    unkfunc_02171598(&menuItem_, MenuStatusInfo::getPlayerActionCount(TownMenuPlayerControl::getSingleton()->activeChara_, MenuStatusInfo::USE_TOWN), menuItem_.active_);
}

THUMB void TownMenu_MAGIC_ROOT::menuDraw()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    int open = gTownMenu_MESSAGE.isOpen();
    unkfunc_02173400(open);
    if (!open) {
        menuItem_.drawActive();
    }
}

THUMB void TownMenu_MAGIC_ROOT::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    if (magicID_ == 0x7d && targetCount_ > 0 && isResult_ == 1) {
        if (soundCount_ > 25) {
            SoundManager::playSe(0x1f5, 0);
            soundCount_ = 0;
            targetCount_--;
        } else {
            soundCount_++;
        }
    }
    if (gTownMenu_MESSAGE.isOpen() == true) {
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK || stat == MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
            if (isResult_ == 1 && resultMagic() == true) {
                close();
                gTownMenu_ROOT.stat_ = MENUBASE_STAT_OK;
            }
        }
        return;
    }
    int activeChara = TownMenuPlayerControl::getSingleton()->activeChara_;
    navigator_.setup(2, 4, MenuStatusInfo::getPlayerActionCount(activeChara, MenuStatusInfo::USE_TOWN));
    int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
    if (result != 0) {
        if (result == 3) {
            TownMenuPlayerControl::getSingleton()->activeMagic_ = 0;
            close();
            data_ov019_021830a8.open();
            return;
        }
        int active = navigator_.getIndex(menuItem_.active_);
        magicID_ = MenuStatusInfo::getPlayerActionID(activeChara, active, MenuStatusInfo::USE_TOWN);
        TownMenuPlayerControl::getSingleton()->setActiveMagic(active);
        if (result == 2) {
            useMagic();
        }
        redraw_ = 1;
    }
}

THUMB void TownMenu_MAGIC_ROOT::useMagic()
{
    int activeChara = TownMenuPlayerControl::getSingleton()->activeChara_;
    if (status::UseAction::getUseMp(magicID_) > MenuStatusInfo::getHaveStatusInfo(activeChara).getMp()) {
        if (status::g_Menu.checkMenuEventNo(magicID_) == true) {
            if (magicID_ == 0x81) {
                useMoveMagic();
                return;
            }
            status::g_Menu.setMenuEventFlag(true);
            close();
            gTownMenu_ROOT.stat_ = MENUBASE_STAT_OK;
            if (data_02101c88.isCurrentPart(4)) {
                twn::TownPlayerManager::getSingleton().setLock(true);
            } else if (data_02101c88.isCurrentPart(6)) {
                fld::FieldPlayerManager::getSingleton().setLock(true);
            }
            return;
        }
        TextAPI::setMACRO0(1, 0x50000000, MenuStatusInfo::getPlayerIndex(activeChara));
        gTownMenu_MESSAGE.openMessageForMENU();
        gTownMenu_MESSAGE.addMessage(0xc3b73);
        return;
    }
    if (magicID_ == 0x81) {
        useMoveMagic();
        return;
    }
    if (status::g_Menu.checkMenuEventNo(magicID_) == true) {
        status::g_Menu.setMenuEventFlag(true);
        close();
        gTownMenu_ROOT.stat_ = MENUBASE_STAT_OK;
        if (data_02101c88.isCurrentPart(4)) {
            twn::TownPlayerManager::getSingleton().setLock(true);
        } else if (data_02101c88.isCurrentPart(6)) {
            fld::FieldPlayerManager::getSingleton().setLock(true);
        }
        return;
    }
    if (status::UseAction::getUseType(magicID_) == status::UseAction::Friend) {
        if (status::UseAction::getUseArea(magicID_) == status::UseAction::One) {
            close();
            gTownMenu_MAGIC_CHARSELECT.open();
            return;
        }
        useMagicNoTarget();
        return;
    }
    useMagicNoTarget();
}

THUMB void TownMenu_MAGIC_ROOT::useMoveMagic()
{
    if (cmn::CommonRuraData::getSingleton().getRuraCount() == 0) {
        gTownMenu_MESSAGE.openMessageForMENU();
        gTownMenu_MESSAGE.addMessage(0xc427c);
    } else {
        close();
        gTownMenu_MAGIC_MOVE.open();
    }
}

THUMB void TownMenu_MAGIC_ROOT::useMagicNoTarget()
{
    status::UseActionParam useActionParam;
    int activeChara = TownMenuPlayerControl::getSingleton()->activeChara_;
    int target = activeChara;
    if (magicID_ == 0x7d) {
        soundCount_ = 10;
        target = -1;
    }
    targetCount_ = MenuStatusInfo::usePlayerMagic(useActionParam, activeChara, target, magicID_);
    isResult_ = useActionParam.result_;
    TextAPI::setMACRO0(1, 0x50000000, MenuStatusInfo::getPlayerIndex(activeChara));
    status::UseActionMacro::setExecMacro(useActionParam.getActorCharacterStatus(), useActionParam.getTargetCharacterStatus(0), useActionParam.getActionIndex());
    if (status::g_Menu.getLuraDisableMessage(0) != 0 && (magicID_ == 0x82 || magicID_ == 0x86) && isResult_ == 0) {
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
    if (magicID_ == 0x8b) {
        SoundManager::playSe(0x23c, 0);
    } else {
        SoundManager::playSe(0x132, 0);
    }
    status::g_Menu.setActorIndex(useActionParam.getActorCharacterStatus()->getHaveStatusInfo().getPlayerIndex());
    gTownMenu_MESSAGE.openMessageForMENU();
    status::UseActionMessage& useActionMessage = useActionParam.message_[0];
    int execMessage = useActionMessage.getExecMessage(0);
    if (magicID_ == 0x7d) {
        if (isResult_ == 1) {
            gTownMenu_MESSAGE.addMessageNOWAIT(execMessage);
        } else {
            gTownMenu_MESSAGE.addMessageNOWAIT(useActionMessage.getResultMessage(0));
        }
    } else if (isResult_ == 0 && useActionMessage.getResultMessage(0) == 0xc40d3) {
        gTownMenu_MESSAGE.addMessage(useActionMessage.getResultMessage(0));
    } else {
        gTownMenu_MESSAGE.addMessage(execMessage);
    }
    if (magicID_ == 0x82 && isResult_ == 1) {
        return;
    }
    for (int i = 0; i < targetCount_; i++) {
        status::UseActionMacro::setResultMacro(useActionParam.getActorCharacterStatus(), useActionParam.getTargetCharacterStatus(i), useActionParam.getActionIndex());
        if (magicID_ == 0x8a && data_02101c88.isCurrentPart(6) == true) {
            gTownMenu_MESSAGE.addMessage(0xc424c);
            break;
        }
        for (int count = 0; useActionMessage.getResultMessage(count) != 0; count++) {
            int resultMessage = useActionMessage.getResultMessage(count);
            if (magicID_ == 0x7d) {
                if (isResult_ == 0) {
                    resultMessage++;
                }
                gTownMenu_MESSAGE.addMessageNOWAIT(resultMessage);
            } else if (isResult_ == 0 && resultMessage == 0xc40d3) {
                gTownMenu_MESSAGE.addMessage(resultMessage + 1);
            } else {
                gTownMenu_MESSAGE.addMessage(resultMessage);
            }
        }
    }
}

THUMB bool TownMenu_MAGIC_ROOT::resultMagic()
{
    bool ret = true;
    switch (magicID_) {
        case 0x82:
            cmn::g_cmnPartyInfo.setMenuAction(cmn::MENU_RIREMIT);
            cmn::NonBattleActionManager::getSingleton()->setAction(cmn::NonBattleActionManager::ACTION_RIREMITO);
            cmn::PartyTalk::getSingleton().resetPartyTalk();
            break;
        case 0x86:
            cmn::g_cmnPartyInfo.setMenuAction(cmn::MENU_RANARUTA);
            cmn::NonBattleActionManager::getSingleton()->setAction(cmn::NonBattleActionManager::ACTION_RANARUTA);
            cmn::PartyTalk::getSingleton().resetPartyTalk();
            break;
        case 0x85:
            status::StageAttribute::setToramana(ret);
            break;
        case 0x81:
        case 0x83:
        case 0x84:
        case 0x89:
        case 0x8a:
        case 0x8b:
            break;
        default:
            ret = false;
            break;
    }
    return ret;
}
