#pragma ipa file
#include "ov019/townmenu/town_item/TownMenuItemSelectCommandUse.hpp"
#include "ov019/townmenu/town_item/TownMenuItemMeisanMessage.hpp"
#include "ov019/townmenu/town_item/TownMenuItemSelectChara.hpp"
#include "ov019/townmenu/town_item/TownMenuItemUseManager.hpp"
#include "ov019/townmenu/town_item/UnkTownMenuItemCharaSelect.hpp"
#include "ov019/townmenu/TownMenuPlayerControl.hpp"
#include "ov019/townmenu/TownMenu_ROOT.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov001/town/TownStageEffectManager.hpp"
#include "ov005/fld/FieldPlayerManager.hpp"
#include "main/menu/MenuAPI.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/menu/UnkMenuStatusDraw.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/cmn/CommonSoundManager.hpp"
#include "main/cmn/NonBattleActionManager.hpp"
#include "main/cmn/PartyTalk.hpp"
#include "main/cmn/TalkSoundManager.hpp"
#include "main/global/Global.hpp"
#include "main/global/UnkGlobalSystem.hpp"
#include "main/sound/SoundManager.hpp"
#include "main/status/CharacterStatus.hpp"
#include "main/status/GameFlag.hpp"
#include "main/status/HaveStatusInfo.hpp"
#include "main/status/MenuStatus.hpp"
#include "main/status/StageAttribute.hpp"
#include "main/status/StoryStatus.hpp"
#include "main/status/UseActionParam.hpp"
#include "main/text/TextAPI.hpp"

using menu::MenuStatusInfo;
using menu::TownMenuPlayerControl;

inline dq5::CHAPTER_NO status::StoryStatus::getChapter()
{
    return chapter_;
}

inline int status::HaveStatus::getPlayerIndex() const
{
    return playerIndex_;
}

inline int status::HaveStatusInfo::getPlayerIndex() const
{
    return haveStatus_.getPlayerIndex();
}

inline void TownMenuItemSelectCommandUse::menuExecute()
{
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

inline int Global::getNowAreaNo()
{
    return areaNo_;
}

inline int Global::getMapNameId()
{
    return nextMapNameId;
}

inline int SoundManager::getBgmIndex()
{
    return bgmIndex_;
}

inline int cmn::CommonSoundManager::isPlaySound()
{
    return isPlaySound_;
}

inline void TownMenuItemMeisanMessage::setUseItem(short item)
{
    m_useItem = item;
}

inline short TownMenuPlayerControl::getActiveItem()
{
    return activeItem_;
}

inline char TownMenuPlayerControl::getActiveItemPage()
{
    return activeItemPage_;
}

THUMB void TownMenuItemSelectCommandUse::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (TownMenuPlayerControl::getSingleton()->activeFukuro_ == 1) {
        int itemPage = TownMenuPlayerControl::getSingleton()->getActiveItemPage();
        int activeItem = TownMenuPlayerControl::getSingleton()->getActiveItem();
        m_itemID = MenuStatusInfo::getFukuroItemID(activeItem, itemPage);
    } else {
        int activeChara = TownMenuPlayerControl::getSingleton()->activeChara_;
        int activeItem = TownMenuPlayerControl::getSingleton()->getActiveItemIndexToAll();
        m_itemID = MenuStatusInfo::getPlayerItemID(activeChara, activeItem);
    }
    m_isResult = 0;
    m_isSound = 0;
    m_isHeal = 0;
    m_updataMP = -1;
    m_itemUsePlayer = 0;
    m_papasuWait = -1;
    m_preMe = SoundManager::getBgmIndex();
    m_preSe = SoundManager::se2_;
    if (m_preSe != 0x66) {
        m_preSe = 0;
    }
    for (int i = 0; i < 4; i++) {
        m_updataHP[i] = -1;
    }
    for (int i = 0; i < 8; i++) {
        m_resultMes[i] = -1;
    }
    useItemNoTarget();
}

THUMB void TownMenuItemSelectCommandUse::menuDraw()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    drawPartyStatusWindows();
}

THUMB void TownMenuItemSelectCommandUse::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (m_papasuWait > -1) {
        if (m_papasuWait > 15) {
            close();
            gTownMenu_ROOT.stat_ = MENUBASE_STAT_OK;
        }
        m_papasuWait++;
        return;
    }
    if (gTownMenu_MESSAGE.isOpen() == true) {
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK || stat == MENUBASE_STAT_CANCEL) {
            if (m_isResult == 1 && m_isHeal == 1) {
                gTownMenu_MESSAGE.restartMessage();
                if (m_itemID == 0xa6) {
                    SoundManager::playSe(0x1f5, 0);
                    TextAPI::setMACRO0(1, 0x50000000, m_itemUsePlayer);
                    gTownMenu_MESSAGE.addMessage(0xc40f8);
                    gTownMenu_MESSAGE.setMessageLastCursor(false);
                    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
                    for (int i = 0; i < MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_CARRIAGE_OUT); i++) {
                        MenuStatusInfo::getHaveStatusInfo(i).setHp(m_updataHP[i]);
                    }
                    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
                }
                if (m_itemID == 0xa8) {
                    SoundManager::playSe(0x1f5, 0);
                    int activeChara = TownMenuPlayerControl::getSingleton()->activeChara_;
                    TextAPI::setMACRO0(1, 0x50000000, MenuStatusInfo::getPlayerIndex(activeChara));
                    TextAPI::setMACRO0(0x51, 0xf0000000, MenuStatusInfo::getHaveStatusInfo(activeChara).getUseActionEffectValue());
                    gTownMenu_MESSAGE.addMessage(0xc4100);
                    if (m_resultMes[2] != -1) {
                        gTownMenu_MESSAGE.addMessage(m_resultMes[2]);
                    }
                    MenuStatusInfo::getHaveStatusInfo(activeChara).setMp(m_updataMP);
                }
                redraw_ = 1;
                m_isHeal = 0;
                return;
            }
            gTownMenu_MESSAGE.close();
            if (m_itemID == 0xc3 && m_isSound == 0) {
                cmn::g_cmnSoundManager.setPlaySound(6, false);
                m_isSound = 1;
                return;
            }
            if (m_itemID == 0xc6 && m_isSound == 0) {
                cmn::g_cmnSoundManager.setPlaySound(7, false);
                m_isSound = 1;
                return;
            }
            resultItem();
        }
        return;
    }
    if (cmn::g_cmnSoundManager.isPlaySound() == true) {
        cmn::g_cmnSoundManager.execSound();
        return;
    }
    if (m_isSound == 1) {
        int mesCount = 0;
        gTownMenu_MESSAGE.openMessageForMENU();
        while (m_resultMes[mesCount] != -1) {
            if (mesCount > 4) {
                break;
            }
            gTownMenu_MESSAGE.addMessage(m_resultMes[mesCount]);
            mesCount++;
        }
        if (mesCount == 0) {
            close();
            gTownMenu_ROOT.stat_ = MENUBASE_STAT_OK;
        }
    }
}

THUMB void TownMenuItemSelectCommandUse::useItemNoTarget()
{
    int activeChara = TownMenuPlayerControl::getSingleton()->activeChara_;
    int itemIndex = TownMenuPlayerControl::getSingleton()->getActiveItemIndexToAll();
    int mesCount = 0;
    int useMes[4] = {-1};
    for (int i = 0; i < 4; i++) {
        useMes[i] = -1;
    }
    int resultMes[4] = {-1};
    for (int i = 0; i < 4; i++) {
        resultMes[i] = -1;
    }
    short nowHP[4] = {-1};
    for (int i = 0; i < 4; i++) {
        nowHP[i] = -1;
    }
    status::UseActionParam useActionParam;
    int activeFukuro = TownMenuPlayerControl::getSingleton()->activeFukuro_;
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    for (int i = 0; i < MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_CARRIAGE_OUT); i++) {
        m_updataHP[i] = MenuStatusInfo::getHaveStatusInfo(i).getHp();
    }
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (activeFukuro == 1) {
        int count = 0;
        int maxCharaCount = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL);
        while (MenuStatusInfo::isPlayerCondition(count, MenuStatusInfo::CONDITION_DEATH) == true) {
            count++;
            if (count > maxCharaCount) {
                count = 0;
            }
        }
        m_itemUsePlayer = MenuStatusInfo::getPlayerIndex(count);
        m_isResult = MenuStatusInfo::useFukuroItem(useActionParam, itemIndex, -1);
        TownMenuPlayerControl::getSingleton()->setFukuroActiveItemByChangeMax();
    } else {
        m_updataMP = MenuStatusInfo::getHaveStatusInfo(activeChara).getMp();
        m_itemUsePlayer = MenuStatusInfo::getPlayerIndex(activeChara);
        m_isResult = MenuStatusInfo::usePlayerItem(useActionParam, activeChara, itemIndex, -1);
        TownMenuPlayerControl::getSingleton()->setPlayerActiveItemByChangeMax();
    }
    status::g_Menu.setActorIndex(useActionParam.getActorCharacterStatus()->getHaveStatusInfo().getPlayerIndex());
    cmn::PartyTalk::getSingleton().setUseItem(m_itemID);
    if (status::g_Menu.checkMenuEventNo(m_itemID) == true) {
        close();
        if (g_Global.getNowAreaNo() == 0x5d) {
            status::g_Menu.resetMenuEventNo();
            gTownMenuItemMeisanMessage.setUseItem(m_itemID);
            gTownMenuItemMeisanMessage.open();
        } else {
            status::g_Menu.setMenuEventFlag(true);
            gTownMenu_ROOT.stat_ = MENUBASE_STAT_OK;
            if (data_02101c88.unkfunc_02051818(4)) {
                twn::TownPlayerManager::getSingleton().setLock(true);
            } else if (data_02101c88.unkfunc_02051818(6)) {
                fld::FieldPlayerManager::getSingleton().setLock(true);
            }
        }
        return;
    }
    getUseItemMessage(useActionParam, useMes, resultMes);
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    for (int i = 0; i < MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_CARRIAGE_OUT); i++) {
        if (MenuStatusInfo::isPlayerCondition(i, MenuStatusInfo::CONDITION_DEATH) == true) {
            nowHP[i] = 0;
        } else {
            nowHP[i] = MenuStatusInfo::getHaveStatusInfo(i).getHpMax();
        }
        MenuStatusInfo::getHaveStatusInfo(i).setHp(m_updataHP[i]);
        m_updataHP[i] = nowHP[i];
    }
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (activeFukuro == 0) {
        short nowMP = MenuStatusInfo::getHaveStatusInfo(activeChara).getMp();
        MenuStatusInfo::getHaveStatusInfo(activeChara).setMp(m_updataMP);
        m_updataMP = nowMP;
    }
    if (m_itemID == 0xa6 || m_itemID == 0xa8) {
        m_isHeal = 1;
    }
    if (m_itemID == 0xc3 || m_itemID == 0xc6) {
        gTownMenu_MESSAGE.openMessageForMENU();
        TextAPI::setMACRO0(1, 0x50000000, m_itemUsePlayer);
        TextAPI::setMACRO0(10, 0x40000000, m_itemID);
        MenuAPI::addMessageSerial(useMes[0]);
        m_resultMes[0] = 0xc424e;
        return;
    }
    if (m_itemID == 0xd3 && m_preMe != 0x14) {
        if (m_preSe != 0) {
            SoundManager::unkfunc_0206fc44(0);
        }
        SoundManager::play(0x14, 5);
    }
    if (m_itemID == 0xf7) {
        SoundManager::playSe(0x256, 0);
    }
    while (useMes[mesCount] != -1) {
        if (mesCount > 4) {
            break;
        }
        m_resultMes[mesCount] = useMes[mesCount];
        mesCount++;
    }
    int resCount = 0;
    while (resultMes[resCount] != -1) {
        if (resCount > 4) {
            break;
        }
        m_resultMes[mesCount] = resultMes[resCount];
        mesCount++;
        resCount++;
    }
    addMenuMessage();
    openUseItemMessage();
}

THUMB void TownMenuItemSelectCommandUse::closeMenuCheck()
{
    int count;
    if (TownMenuPlayerControl::getSingleton()->activeFukuro_ == 1) {
        count = MenuStatusInfo::getFukuroItemCount();
    } else {
        count = MenuStatusInfo::getPlayerItemCount(TownMenuPlayerControl::getSingleton()->activeChara_);
    }
    close();
    if (count == 0) {
        data_ov019_02183524.fromMateriel_ = 0;
        data_ov019_02183524.open();
    } else {
        gTownMenuItemSelectChara.meisanhinFlag_ = 0;
        gTownMenuItemSelectChara.open();
    }
}

THUMB void TownMenuItemSelectCommandUse::resultItem()
{
    m_isSound = 0;
    if (menu::TownMenuItemUseManager::getSingleton().getDefaultCloseMenuItem(m_itemID)) {
        close();
        gTownMenu_ROOT.stat_ = MENUBASE_STAT_OK;
        return;
    }
    switch (m_itemID) {
        case 0x90:
        case 0xa4:
            close();
            gTownMenu_ROOT.stat_ = MENUBASE_STAT_OK;
            if (m_resultMes[1] == -1) {
                if (m_isResult == 1) {
                    cmn::g_cmnPartyInfo.setMenuAction(cmn::MENU_KIMERA);
                    cmn::PartyTalk::getSingleton().resetPartyTalk();
                    return;
                }
                if (status::g_StageAttribute.isRula()) {
                    return;
                }
                cmn::g_cmnPartyInfo.setMenuAction(cmn::MENU_RURA_FAILED);
            }
            break;
        case 0xc0:
            close();
            gTownMenu_ROOT.stat_ = MENUBASE_STAT_OK;
            if (status::g_StageAttribute.isRulaDisable() == true) {
                break;
            }
            if (status::g_StageAttribute.isRula() == true) {
                cmn::g_cmnPartyInfo.setMenuAction(cmn::MENU_SORATOBU_START);
                cmn::PartyTalk::getSingleton().resetPartyTalk();
                break;
            }
            cmn::g_cmnPartyInfo.setMenuAction(cmn::MENU_RURA_FAILED);
            break;
        case 0xb4:
            if (m_isResult == 1) {
                close();
                gTownMenu_ROOT.stat_ = MENUBASE_STAT_OK;
                cmn::g_cmnPartyInfo.setMenuAction(cmn::MENU_RANARUTA);
                cmn::NonBattleActionManager::getSingleton()->setAction(cmn::NonBattleActionManager::ACTION_RANARUTA);
                cmn::PartyTalk::getSingleton().resetPartyTalk();
                break;
            }
            closeMenuCheck();
            break;
        case 0xc2:
            if (m_isResult == 1) {
                close();
                gTownMenu_ROOT.stat_ = MENUBASE_STAT_OK;
                twn::TownStageEffectManager::getSingleton()->setTorchlight();
                twn::TownStageEffectManager::getSingleton()->setStopLightning(true);
                twn::TownPlayerManager::getSingleton().partyDraw_.taimatsuFlag_ = 1;
                SoundManager::playSe(0x45b, 0);
                g_GlobalFlag.set(1);
                break;
            }
            closeMenuCheck();
            break;
        case 0xbe:
            if (m_isResult == 1) {
                close();
                gTownMenu_ROOT.stat_ = MENUBASE_STAT_OK;
                cmn::g_cmnPartyInfo.setMenuAction(cmn::MAGIC_CARPET);
                break;
            }
            closeMenuCheck();
            break;
        case 0xd3: {
            bool closeFlag = false;
            if (m_preSe != 0) {
                SoundManager::stop(0xf);
                SoundManager::playSe2(m_preSe, 0);
                closeFlag = true;
            }
            if (m_preMe == 0) {
                SoundManager::stop(5);
                closeFlag = true;
            } else if (m_preMe != 0x14) {
                SoundManager::play(m_preMe, 5);
                m_papasuWait = 0;
            } else {
                m_papasuWait = 0;
            }
            if (closeFlag == true) {
                close();
                gTownMenu_ROOT.stat_ = MENUBASE_STAT_OK;
            }
            break;
        }
        default:
            closeMenuCheck();
            break;
    }
}

THUMB void TownMenuItemSelectCommandUse::addMenuMessage()
{
    if (m_itemID == 0xc0) {
        if (!status::g_StageAttribute.isRula() || status::g_StageAttribute.isRulaDisable() == true) {
            return;
        }
        m_resultMes[1] = -1;
    }
    if (m_itemID == 0x9a) {
        int active = TownMenuPlayerControl::getSingleton()->activeChara_;
        int target = MenuStatusInfo::getPlayerSortIndex(m_itemUsePlayer);
        if (TownMenuPlayerControl::getSingleton()->activeFukuro_ == 1) {
            active = target;
        }
        if (MenuStatusInfo::getPlayerIndex(active) != 1) {
            m_resultMes[0] = 0xc40de;
            m_resultMes[1] = 0xc424c;
        }
    }
    if (isDisableKimera() == true) {
        m_resultMes[1] = -1;
    }
    if (m_itemID == 0xd3) {
        int index = MenuStatusInfo::getPlayerSortIndex(m_itemUsePlayer);
        if (MenuStatusInfo::isPlayerType(index, MenuStatusInfo::TYPE_FRIEND_MONSTER) == true) {
            m_resultMes[0] = 0x153b;
            m_resultMes[1] = -1;
        }
    }
}

THUMB void TownMenuItemSelectCommandUse::getUseItemMessage(status::UseActionParam& useActionParam, int* useMes, int* resultMes)
{
    int mesCount = 0;
    status::UseActionMessage& useActionMessage = useActionParam.message_[0];
    if (m_itemID == 0xbe || m_itemID == 0xbf) {
        useMes[0] = useActionMessage.getResultMessage(0);
        return;
    }
    while (useActionMessage.getExecMessage(mesCount) != 0) {
        useMes[mesCount] = useActionMessage.getExecMessage(mesCount);
        mesCount++;
    }
    if (m_itemID == 0xc0 && (m_itemID != 0xc0 || status::g_StageAttribute.isRulaDisable() != true)) {
        return;
    }
    {
        mesCount = 0;
        int addCount = mesCount;
        while (useActionMessage.getResultMessage(mesCount) != 0) {
            resultMes[mesCount] = useActionMessage.getResultMessage(mesCount);
            if (m_itemID == 0xa9 && m_isResult == 1) {
                resultMes[mesCount] = 0xc4256;
            }
            mesCount++;
        }
        while (useActionMessage.getAddMessage(addCount) != 0) {
            resultMes[mesCount] = useActionMessage.getAddMessage(addCount);
            mesCount++;
            addCount++;
        }
    }
}

THUMB void TownMenuItemSelectCommandUse::openUseItemMessage()
{
    if (m_itemID == 0xbf) {
        if (m_isResult == 1) {
            close();
            gTownMenu_ROOT.stat_ = MENUBASE_STAT_OK;
            cmn::g_cmnPartyInfo.setMenuAction(cmn::MASTER_DRAGON);
            return;
        }
        cmn::g_talkSound.setOrderMessage(0x30);
        cmn::g_talkSound.setOrderMessage(0x33);
        cmn::g_talkSound.setMessageSound(2, -1);
        gTownMenu_MESSAGE.openMessageForTALK();
        gTownMenu_MESSAGE.addMessage(m_resultMes[0]);
        if (data_02101c88.unkfunc_02051818(6) == 1 && g_Global.getFieldType() == 0) {
            gTownMenu_MESSAGE.addMessage(m_resultMes[0] + 1);
        }
        return;
    }
    if (m_itemID == 0xc2 && data_02101c88.unkfunc_02051818(6) == 0
        && twn::TownStageEffectManager::getSingleton()->spotlight_.enable_ == 0
        && status::g_Story.getChapter() == 1 && g_Global.getMapNameId() == 10 && !g_AreaFlag.check(0x51)) {
        m_isResult = 1;
        gTownMenu_MESSAGE.openMessageForMENU();
        MenuAPI::addMessageSerial(0x4f4);
        cmn::PartyTalk::getSingleton().setPreMessageNo(0x4f5);
        return;
    }
    int count = 1;
    int active = TownMenuPlayerControl::getSingleton()->activeChara_;
    int target = MenuStatusInfo::getPlayerSortIndex(m_itemUsePlayer);
    if (TownMenuPlayerControl::getSingleton()->activeFukuro_ == 1) {
        active = target;
    }
    TextAPI::setMACRO0(1, 0x50000000, m_itemUsePlayer);
    TextAPI::setMACRO0(10, 0x40000000, m_itemID);
    TextAPI::setMACRO0(0x82, 0xc0000000, g_Global.getMapNameId());
    if (m_itemID == 0xa8) {
        TextAPI::setMACRO0(0x51, 0xf0000000, MenuStatusInfo::getHaveStatusInfo(target).getUseActionEffectValue());
        TextAPI::setMACRO0(0x12, 0x50000000, m_itemUsePlayer);
    } else {
        TextAPI::setMACRO0(0x12, 0x50000000, m_itemUsePlayer);
        TextAPI::setMACRO0(0x51, 0xf0000000, MenuStatusInfo::getHaveStatusInfo(active).getUseActionEffectValue());
    }
    if (status::g_Menu.messageNo_[0] != 0
        && (m_itemID == 0xa4 || m_itemID == 0x90 || m_itemID == 0xb4 || m_itemID == 0xc0) && m_isResult == 0) {
        for (int i = 0; i < 3; i++) {
            cmn::g_talkSound.setOrderMessage(status::g_Menu.messageVoice_[i]);
        }
        cmn::g_talkSound.setMessageSound(3, -1);
        gTownMenu_MESSAGE.openMessageForTALK();
        for (int i = 0; i < 3; i++) {
            int message = status::g_Menu.messageNo_[i];
            if (message != 0) {
                gTownMenu_MESSAGE.addMessage(message);
                cmn::PartyTalk::getSingleton().setPreMessageNo(message);
            }
        }
        return;
    }
    gTownMenu_MESSAGE.openMessageForMENU();
    if (m_resultMes[0] == -1) {
        if (m_itemID == 0xbe) {
            if (m_isResult == 1) {
                close();
                gTownMenu_ROOT.stat_ = MENUBASE_STAT_OK;
                cmn::g_cmnPartyInfo.setMenuAction(cmn::MAGIC_CARPET);
            }
        } else {
            closeMenuCheck();
        }
    } else if ((m_itemID == 0xa6 || m_itemID == 0xa8) && m_isResult == 1) {
        gTownMenu_MESSAGE.addMessage(m_resultMes[0]);
        m_resultMes[1] = -1;
    } else {
        MenuAPI::addMessageSerial(m_resultMes[0]);
    }
    while (m_resultMes[count] != -1) {
        if (count > 8) {
            break;
        }
        gTownMenu_MESSAGE.addMessage(m_resultMes[count]);
        count++;
    }
    if ((m_itemID == 0xa6 || m_itemID == 0xa8) && m_isResult == 1) {
        gTownMenu_MESSAGE.setMessageCursor(true);
    }
}

THUMB bool TownMenuItemSelectCommandUse::isDisableKimera()
{
    if (m_itemID == 0xa4 || m_itemID == 0x90) {
        if (status::g_StageAttribute.isRulaDisable() == true) {
            return false;
        }
        if (!status::g_StageAttribute.isRula()) {
            return true;
        }
        return false;
    }
    return false;
}
