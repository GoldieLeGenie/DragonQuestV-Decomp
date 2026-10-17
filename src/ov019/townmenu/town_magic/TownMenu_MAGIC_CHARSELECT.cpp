#pragma ipa file
#include "ov019/townmenu/town_magic/TownMenu_MAGIC_CHARSELECT.hpp"
#include "ov019/townmenu/town_magic/TownMenu_MAGIC_ROOT.hpp"
#include "ov019/townmenu/TownMenuPlayerControl.hpp"
#include "ov019/townmenu/TownMenu_ROOT.hpp"
#include "ov019/townmenu/UnkMenuTemplateTown.hpp"
#include "ov019/townmenu/UnkTownMenuDraw.hpp"
#include "main/cmn/GameManager.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/MenuUpdateAssist.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/sound/SoundManager.hpp"
#include "main/status/CharacterStatus.hpp"
#include "main/status/HaveStatusInfo.hpp"
#include "main/status/MenuStatus.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/UseActionMacro.hpp"
#include "main/status/UseActionParam.hpp"
#include "main/text/TextAPI.hpp"
#include "main/window/MenuControl.hpp"

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

inline void window::MenuControl::setMenu(int menu)
{
    menu_ = menu;
}

inline void TownMenuPlayerControl::setTargetChara(unsigned char target)
{
    targetChara_ = target;
}

inline void TownMenuPlayerControl::setTargetItemPage(char page)
{
    targetItemPage_ = page;
}

THUMB void TownMenu_MAGIC_CHARSELECT::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    int activeChara = TownMenuPlayerControl::getSingleton()->activeChara_;
    int targetChara = TownMenuPlayerControl::getSingleton()->targetChara_;
    int activeMagic = TownMenuPlayerControl::getSingleton()->activeMagic_;
    int page = TownMenuPlayerControl::getSingleton()->targetItemPage_;
    menuItem_.active_ = targetChara;
    navigator_.setupBase();
    navigator_.setup(2, 2, MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL));
    navigator_.setPageNo(page);
    magicID_ = MenuStatusInfo::getPlayerActionID(activeChara, activeMagic, MenuStatusInfo::USE_TOWN);
    isResult_ = 0;
    unk_20 = 0;
    updateHP_ = 0;
    for (int i = 0; i < 4; i++) {
        resultMes_[i] = 0;
    }
}

THUMB void TownMenu_MAGIC_CHARSELECT::menuExecute()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    unkfunc_0217154c(&menuItem_, navigator_.getCountInPage(), menuItem_.active_);
}

THUMB void TownMenu_MAGIC_CHARSELECT::menuDraw()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    int open = gTownMenu_MESSAGE.isOpen();
    unkfunc_021734f8(open, navigator_.getPageNo());
    if (!open) {
        menuItem_.drawActive();
    }
}

THUMB void TownMenu_MAGIC_CHARSELECT::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    if (gTownMenu_MESSAGE.isOpen()) {
        if (gTownMenu_MESSAGE.isMessageWAITPROG() == true) {
            gTownMenu_MESSAGE.clearMessageWAITPROG();
            gTownMenu_MESSAGE.restartMessage();
            int target = navigator_.getIndex(menuItem_.active_);
            int count = 0;
            while (resultMes_[count] != 0) {
                TextAPI::setMACRO0(0x12, 0x50000000, MenuStatusInfo::getPlayerIndex(target));
                gTownMenu_MESSAGE.addMessage(resultMes_[count]);
                count++;
            }
            if (magicID_ == 0x7e) {
                MenuStatusInfo::resetPlayerCondition(target, MenuStatusInfo::CONDITION_POISON);
                MenuStatusInfo::resetPlayerCondition(target, MenuStatusInfo::CONDITION_VENOM);
            }
            if (magicID_ == 0x87) {
                MenuStatusInfo::resetPlayerCondition(target, MenuStatusInfo::CONDITION_SPELL);
            } else {
                MenuStatusInfo::getHaveStatusInfo(target).setHp(updateHP_);
            }
            if (isResult_ == 1) {
                SoundManager::playSe(0x1f5, 0);
            }
            unk_20 = 0;
            redraw_ = 1;
            return;
        }
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK || stat == MENUBASE_STAT_CANCEL) {
            if (resultRebirth() == true) {
                close();
                gTownMenu_ROOT.stat_ = MENUBASE_STAT_OK;
                cmn::GameManager::getSingleton().resetParty();
                status::PartyStatusUtility::resetForceReorderMember();
                return;
            }
            gTownMenu_MESSAGE.close();
            close();
            gTownMenu_MAGIC_ROOT.open();
        }
        return;
    }
    navigator_.setup(2, 2, MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL));
    int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
    if (result != 0) {
        if (result == 3) {
            close();
            gTownMenu_MAGIC_ROOT.open();
        }
        if (result == 2) {
            useMagic();
        }
        TownMenuPlayerControl::getSingleton()->setTargetChara(menuItem_.active_);
        TownMenuPlayerControl::getSingleton()->setTargetItemPage(navigator_.getPageNo());
        redraw_ = 1;
    }
}

THUMB void TownMenu_MAGIC_CHARSELECT::useMagic()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    status::UseActionParam useActionParam;
    int activeChara = TownMenuPlayerControl::getSingleton()->activeChara_;
    int target = navigator_.getIndex(menuItem_.active_);
    int isPoison = MenuStatusInfo::isPlayerCondition(target, MenuStatusInfo::CONDITION_POISON);
    int isVenom = MenuStatusInfo::isPlayerCondition(target, MenuStatusInfo::CONDITION_VENOM);
    int isSpell = MenuStatusInfo::isPlayerCondition(target, MenuStatusInfo::CONDITION_SPELL);
    gTownMenu_MESSAGE.openMessageForMENU();
    TextAPI::setMACRO0(1, 0x50000000, MenuStatusInfo::getPlayerIndex(activeChara));
    if ((magicID_ == 0x7a || magicID_ == 0x7b || magicID_ == 0x7c || magicID_ == 0x7e || magicID_ == 0x87) && MenuStatusInfo::isPlayerCondition(target, MenuStatusInfo::CONDITION_DEATH) == true) {
        TextAPI::setMACRO0(0x11, 0x70000000, MenuStatusInfo::getWordDBIndex(magicID_));
        TextAPI::setMACRO0(0x12, 0x50000000, MenuStatusInfo::getPlayerIndex(target));
        gTownMenu_MESSAGE.addMessage(0xc40d3, 0xc40d4);
        SoundManager::playSe(0x132, 0);
        return;
    }
    updateHP_ = MenuStatusInfo::getHaveStatusInfo(target).getHp();
    MenuStatusInfo::usePlayerMagic(useActionParam, activeChara, target, magicID_);
    isResult_ = useActionParam.result_;
    short nowHP = MenuStatusInfo::getHaveStatusInfo(target).getHp();
    MenuStatusInfo::getHaveStatusInfo(target).setHp(updateHP_);
    updateHP_ = nowHP;
    if (isPoison == true) {
        MenuStatusInfo::setPlayerCondition(target, MenuStatusInfo::CONDITION_POISON);
    }
    if (isVenom == true) {
        MenuStatusInfo::setPlayerCondition(target, MenuStatusInfo::CONDITION_VENOM);
    }
    if (isSpell == true) {
        MenuStatusInfo::setPlayerCondition(target, MenuStatusInfo::CONDITION_SPELL);
    }
    status::UseActionMacro::setExecMacro(useActionParam.getActorCharacterStatus(), useActionParam.getTargetCharacterStatus(0), useActionParam.getActionIndex());
    status::UseActionMacro::setResultMacro(useActionParam.getActorCharacterStatus(), useActionParam.getTargetCharacterStatus(0), useActionParam.getActionIndex());
    status::UseActionMessage& useActionMessage = useActionParam.message_[0];
    if (isResult_ == 0 && useActionMessage.getResultMessage(0) == 0xc40d3) {
        gTownMenu_MESSAGE.addMessage(useActionMessage.getResultMessage(0));
        gTownMenu_MESSAGE.addMessage(useActionMessage.getResultMessage(0) + 1);
    } else {
        gTownMenu_MESSAGE.addMessage(useActionMessage.getExecMessage(0));
        gTownMenu_MESSAGE.addMessageWAITKEY();
    }
    unk_20 = 1;
    if (isResult_ != 0 || useActionMessage.getResultMessage(0) != 0xc40d3) {
        for (int count = 0; useActionMessage.getResultMessage(count) != 0; count++) {
            resultMes_[count] = useActionMessage.getResultMessage(count);
        }
    }
    if (resultRebirth() == true) {
        window::MenuControl::setMenu(1);
        status::g_Menu.bookingFlag_ = 4;
        TownMenuPlayerControl::getSingleton()->initializeLock_ = 1;
    }
    status::g_Menu.setActorIndex(useActionParam.getActorCharacterStatus()->getHaveStatusInfo().getPlayerIndex());
    SoundManager::playSe(0x132, 0);
}

THUMB int TownMenu_MAGIC_CHARSELECT::resultRebirth()
{
    if (magicID_ == 0x7f || magicID_ == 0x80) {
        return isResult_;
    }
    return 0;
}
