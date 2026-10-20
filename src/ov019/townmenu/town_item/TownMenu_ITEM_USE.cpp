#pragma ipa file
#include "ov019/townmenu/town_item/TownMenu_ITEM_USE.hpp"
#include "ov019/townmenu/town_item/TownMenuItemSelectChara.hpp"
#include "ov019/townmenu/town_item/UnkTownMenuItemCharaSelect.hpp"
#include "ov019/townmenu/TownMenuPlayerControl.hpp"
#include "ov019/townmenu/TownMenu_ROOT.hpp"
#include "ov019/townmenu/UnkMenuTemplateTown.hpp"
#include "ov019/townmenu/UnkTownMenuDraw.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov005/fld/FieldPlayerManager.hpp"
#include "main/cmn/GameManager.hpp"
#include "main/cmn/PartyTalk.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/global/UnkGlobalSystem.hpp"
#include "main/menu/MenuAPI.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/MenuUpdateAssist.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/sound/SoundManager.hpp"
#include "main/status/CharacterStatus.hpp"
#include "main/status/HaveStatusInfo.hpp"
#include "main/status/MenuStatus.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/StageAttribute.hpp"
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

inline int status::HaveStatusInfo::getUseActionEffectValue()
{
    return effectValue_;
}

inline void status::MenuStatus::setActorIndex(short actor)
{
    actorIndex_ = actor;
}

inline void status::MenuStatus::setMenuEventFlag(bool flag)
{
    menuEventFlag_ = flag;
}

inline int status::UseActionMessage::getExecMessage(int index)
{
    return execMessage_[index];
}

inline int status::UseActionMessage::getResultMessage(int index)
{
    return resultMessage_[index];
}

inline int status::UseActionMessage::getAddMessage(int index)
{
    return addMessage_[index];
}

inline void window::MenuControl::setMenu(int menu)
{
    menu_ = menu;
}

inline short TownMenuPlayerControl::getActiveItem()
{
    return activeItem_;
}

inline char TownMenuPlayerControl::getActiveItemPage()
{
    return activeItemPage_;
}

inline void menu::MenuPlayerControl::setTargetChara(short target)
{
    targetChara_ = target;
}

inline void menu::MenuPlayerControl::setTargetCharaPage(short page)
{
    targetCharaPage_ = page;
}

THUMB void TownMenu_ITEM_USE::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    activeItem_ = TownMenuPlayerControl::getSingleton()->getActiveItemIndexToAll();
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    navigator_.setupBase();
    navigator_.setup(2, 2, MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL));
    updateHP_ = 0;
    updateMP_ = 0;
    unk_28 = 0;
    unk_20 = 0;
    activeFukuro_ = TownMenuPlayerControl::getSingleton()->activeFukuro_;
    for (int i = 0; i < 4; i++) {
        resultMes_[i] = 0;
    }
    setActiveChara();
    if (activeFukuro_ == 1) {
        int activeItem = TownMenuPlayerControl::getSingleton()->getActiveItem();
        int page = TownMenuPlayerControl::getSingleton()->getActiveItemPage();
        itemID_ = MenuStatusInfo::getFukuroItemID(activeItem, page);
    } else {
        itemID_ = MenuStatusInfo::getPlayerItemID(activeChara_, activeItem_);
    }
    int page = TownMenuPlayerControl::getSingleton()->targetCharaPage_;
    int active = TownMenuPlayerControl::getSingleton()->targetChara_ - page * 4;
    menuItem_.active_ = dss::clamp<int>(0, active, 3);
    navigator_.setPageNo(page);
}

THUMB void TownMenu_ITEM_USE::menuExecute()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    townMenuPageTargetChara(&menuItem_, navigator_.getCountInPage(), menuItem_.active_);
}

THUMB void TownMenu_ITEM_USE::menuDraw()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    int open = gTownMenu_MESSAGE.isOpen();
    drawItemUseTargetScreen(open, itemID_, navigator_.getPageNo());
    if (!open) {
        menuItem_.drawActive();
    }
}

THUMB void TownMenu_ITEM_USE::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    if (gTownMenu_MESSAGE.isOpen()) {
        if (gTownMenu_MESSAGE.isMessageWAITPROG() == true) {
            gTownMenu_MESSAGE.clearMessageWAITPROG();
            openHealMessage();
            return;
        }
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK || stat == MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
            close();
            if ((itemID_ == 0xa5 || itemID_ == 0x27) && isResult_ == 1) {
                gTownMenu_ROOT.stat_ = MENUBASE_STAT_OK;
                cmn::GameManager::getSingleton().resetParty();
                status::PartyStatusUtility::resetForceReorderMember();
                return;
            }
            if (unk_20 == 1) {
                data_ov019_02183524.fromMateriel_ = 0;
                data_ov019_02183524.open();
                return;
            }
            gTownMenuItemSelectChara.meisanhinFlag_ = 0;
            gTownMenuItemSelectChara.open();
        }
        return;
    }
    navigator_.setup(2, 2, MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL));
    int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
    if (result != 0) {
        TownMenuPlayerControl::getSingleton()->menu::MenuPlayerControl::setTargetChara(navigator_.getIndex(menuItem_.active_));
        TownMenuPlayerControl::getSingleton()->setTargetCharaPage(navigator_.getPageNo());
        if (result == 3) {
            TownMenuPlayerControl::getSingleton()->menu::MenuPlayerControl::setTargetChara(0);
            TownMenuPlayerControl::getSingleton()->setTargetCharaPage(0);
            close();
            gTownMenuItemSelectChara.meisanhinFlag_ = 0;
            gTownMenuItemSelectChara.open();
        }
        if (result == 2) {
            itemUse();
        }
        redraw_ = 1;
    }
}

THUMB void TownMenu_ITEM_USE::setActiveChara()
{
    if (activeFukuro_ == 0) {
        MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
        int playerIndex = MenuStatusInfo::getPlayerIndex(TownMenuPlayerControl::getSingleton()->activeChara_);
        MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
        for (char i = 0; i < MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL); i++) {
            if (MenuStatusInfo::isPlayerType(i, MenuStatusInfo::TYPE_BATTLE_NPC) != true && playerIndex == MenuStatusInfo::getPlayerIndex(i)) {
                activeChara_ = i;
                return;
            }
        }
    }
}

THUMB void TownMenu_ITEM_USE::itemUse()
{
    int target = navigator_.getIndex(menuItem_.active_);
    int mesCount = 0;
    int useMes[4] = {-1};
    for (int i = 0; i < 4; i++) {
        useMes[i] = -1;
    }
    int resultMes[4] = {-1};
    for (int i = 0; i < 4; i++) {
        resultMes[i] = -1;
    }
    int isPoison = MenuStatusInfo::isPlayerCondition(target, MenuStatusInfo::CONDITION_POISON);
    int isVenom = MenuStatusInfo::isPlayerCondition(target, MenuStatusInfo::CONDITION_VENOM);
    status::UseActionParam useActionParam;
    updateHP_ = MenuStatusInfo::getHaveStatusInfo(target).getHp();
    updateMP_ = MenuStatusInfo::getHaveStatusInfo(target).getMp();
    gTownMenu_MESSAGE.openMessageForMENU();
    if (activeFukuro_ == 1) {
        int count = 0;
        while (MenuStatusInfo::isPlayerType(count, MenuStatusInfo::TYPE_BATTLE_NPC) == true || MenuStatusInfo::isPlayerCondition(count, MenuStatusInfo::CONDITION_DEATH) == true) {
            count++;
            if (count > MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL)) {
                close();
                data_ov019_02183524.fromMateriel_ = 0;
                data_ov019_02183524.open();
                return;
            }
        }
        if (itemID_ == 0xa8) {
            TextAPI::setMACRO0(1, 0x50000000, MenuStatusInfo::getPlayerIndex(target));
        } else {
            TextAPI::setMACRO0(1, 0x50000000, MenuStatusInfo::getPlayerIndex(count));
        }
        if (checkUseCharaAlive(target) == false) {
            return;
        }
        isResult_ = MenuStatusInfo::useFukuroItem(useActionParam, activeItem_, target);
        TownMenuPlayerControl::getSingleton()->setFukuroActiveItemByChangeMax();
        if (MenuStatusInfo::getFukuroItemCount() == 0) {
            unk_20 = 1;
        }
    } else {
        TextAPI::setMACRO0(1, 0x50000000, MenuStatusInfo::getPlayerIndex(activeChara_));
        if (checkUseCharaAlive(target) == false) {
            return;
        }
        isResult_ = MenuStatusInfo::usePlayerItem(useActionParam, activeChara_, activeItem_, target);
        TownMenuPlayerControl::getSingleton()->setPlayerActiveItemByChangeMax();
        MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
        if (MenuStatusInfo::getPlayerItemCount(activeChara_) == 0) {
            unk_20 = 1;
        }
    }
    status::g_Menu.setActorIndex(useActionParam.getActorCharacterStatus()->getHaveStatusInfo().getPlayerIndex());
    cmn::PartyTalk::getSingleton().setUseItem(itemID_);
    if (status::g_Menu.checkMenuEventNo(itemID_) == true) {
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
    setUseItemMessage(useActionParam, useMes, resultMes, itemID_);
    short nowHP = MenuStatusInfo::getHaveStatusInfo(target).getHp();
    short nowMP = MenuStatusInfo::getHaveStatusInfo(target).getMp();
    MenuStatusInfo::getHaveStatusInfo(target).setHp(updateHP_);
    MenuStatusInfo::getHaveStatusInfo(target).setMp(updateMP_);
    updateHP_ = nowHP;
    updateMP_ = nowMP;
    if (isPoison == true) {
        MenuStatusInfo::setPlayerCondition(target, MenuStatusInfo::CONDITION_POISON);
    }
    if (isVenom == true) {
        MenuStatusInfo::setPlayerCondition(target, MenuStatusInfo::CONDITION_VENOM);
    }
    status::UseActionMacro::setExecMacro(useActionParam.getActorCharacterStatus(), useActionParam.getTargetCharacterStatus(0), useActionParam.getActionIndex());
    status::UseActionMacro::setResultMacro(useActionParam.getActorCharacterStatus(), useActionParam.getTargetCharacterStatus(0), useActionParam.getActionIndex());
    MenuStatusInfo::getHaveStatusInfo(target);
    TextAPI::setMACRO0(10, 0x40000000, itemID_);
    unk_28 = 1;
    if (itemID_ == 0xb9 && isResult_ == 1) {
        gTownMenu_MESSAGE.addMessage(useMes[0]);
        resultMes[0] = useMes[0] + 1;
    } else {
        MenuAPI::addMessageSerial(useMes[0]);
    }
    if (resultMes[0] != -1 && useHealItem() == true) {
        gTownMenu_MESSAGE.addMessageWAITKEY();
    }
    while (resultMes[mesCount] != -1) {
        if (mesCount > 4) {
            break;
        }
        if (useHealItem() == false) {
            gTownMenu_MESSAGE.addMessage(resultMes[mesCount]);
        } else {
            resultMes_[mesCount] = resultMes[mesCount];
        }
        mesCount++;
    }
    if ((itemID_ == 0xa5 || itemID_ == 0x27) && isResult_ == 1) {
        int itemCount;
        if (activeFukuro_ == 1) {
            itemCount = MenuStatusInfo::getFukuroItemCount();
        } else {
            itemCount = MenuStatusInfo::getPlayerItemCount(activeChara_);
        }
        if (itemCount == 0) {
            window::MenuControl::setMenu(3);
        } else {
            window::MenuControl::setMenu(2);
        }
        status::g_Menu.bookingFlag_ = 4;
        TownMenuPlayerControl::getSingleton()->initializeLock_ = 1;
    }
}

THUMB bool TownMenu_ITEM_USE::checkUseCharaAlive(int target)
{
    if ((itemID_ == 0xa1 || itemID_ == 0xa8 || itemID_ == 0xa9 || itemID_ == 0xb9) && MenuStatusInfo::isPlayerCondition(target, MenuStatusInfo::CONDITION_DEATH) == true) {
        TextAPI::setMACRO0(10, 0x40000000, itemID_);
        TextAPI::setMACRO0(0x12, 0x50000000, MenuStatusInfo::getPlayerIndex(target));
        if (itemID_ == 0xa8) {
            TextAPI::setMACRO0(1, 0x50000000, MenuStatusInfo::getPlayerIndex(target));
            gTownMenu_MESSAGE.addMessage(0xc40dc);
        } else {
            gTownMenu_MESSAGE.addMessage(0xc41ed, 0xc41ee);
        }
        return false;
    }
    return true;
}

THUMB bool TownMenu_ITEM_USE::useHealItem()
{
    if (itemID_ == 0x27 || itemID_ == 0xa1 || itemID_ == 0xa8 || itemID_ == 0xa9 || itemID_ == 0xa5 || itemID_ == 0xa2 || itemID_ == 0x27 || itemID_ == 0xb9) {
        return true;
    }
    return false;
}

THUMB void TownMenu_ITEM_USE::openHealMessage()
{
    int target = navigator_.getIndex(menuItem_.active_);
    if (resultMes_[0] != 0) {
        gTownMenu_MESSAGE.restartMessage();
    }
    int count = 0;
    while (resultMes_[count] != 0) {
        TextAPI::setMACRO0(0x12, 0x50000000, MenuStatusInfo::getPlayerIndex(target));
        TextAPI::setMACRO0(0x51, 0xf0000000, MenuStatusInfo::getHaveStatusInfo(target).getUseActionEffectValue());
        gTownMenu_MESSAGE.addMessage(resultMes_[count]);
        count++;
    }
    if (isResult_ == 1) {
        SoundManager::playSe(0x1f5, 0);
    }
    MenuStatusInfo::getHaveStatusInfo(target).setHp(updateHP_);
    MenuStatusInfo::getHaveStatusInfo(target).setMp(updateMP_);
    if (itemID_ == 0xa2) {
        MenuStatusInfo::resetPlayerCondition(target, MenuStatusInfo::CONDITION_POISON);
        MenuStatusInfo::resetPlayerCondition(target, MenuStatusInfo::CONDITION_VENOM);
    }
    unk_28 = 0;
    redraw_ = 1;
}

THUMB void TownMenu_ITEM_USE::setUseItemMessage(status::UseActionParam& useActionParam, int* useMes, int* resultMes, short itemID)
{
    int mesCount = 0;
    status::UseActionMessage& useActionMessage = useActionParam.message_[0];
    while (useActionMessage.getExecMessage(mesCount) != 0) {
        useMes[mesCount] = useActionMessage.getExecMessage(mesCount);
        mesCount++;
    }
    if (itemID == 0xc0 && (itemID != 0xc0 || status::g_StageAttribute.isRulaDisable() != true)) {
        return;
    }
    {
        mesCount = 0;
        while (useActionMessage.getResultMessage(mesCount) != 0) {
            resultMes[mesCount] = useActionMessage.getResultMessage(mesCount);
            if (itemID == 0xa9 && useActionParam.result_ == 1) {
                resultMes[mesCount] = 0xc4256;
            }
            mesCount++;
        }
        int addCount = 0;
        while (useActionMessage.getAddMessage(addCount) != 0) {
            resultMes[mesCount] = useActionMessage.getAddMessage(addCount);
            mesCount++;
            addCount++;
        }
    }
}
