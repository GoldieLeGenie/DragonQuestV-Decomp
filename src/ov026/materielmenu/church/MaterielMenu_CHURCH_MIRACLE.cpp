#include "ov026/materielmenu/church/MaterielMenu_CHURCH_MIRACLE.hpp"
#include "ov026/materielmenu/church/MaterielMenu_CHURCH_ROOT.hpp"
#include "ov019/leveldata/ChurchMessage.hpp"
#include "ov019/materielmenu/MaterielMenuPlayerControl.hpp"
#include "ov019/materielmenu/MaterielMenu_WINDOW_MANAGER.hpp"
#include "ov019/materielmenu/MenuTemplate_materiel.hpp"
#include "ov019/materielmenu/UnkMaterielMenuWindowDraw.hpp"
#include "main/cmn/CommonSoundManager.hpp"
#include "main/cmn/GameManager.hpp"
#include "main/cmn/PlayerManager.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/object/BillboardCharacter.hpp"
#include "main/status/MenuStatus.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/PlayerStatus.hpp"
#include "main/text/TextAPI.hpp"

using menu::MenuStatusInfo;

inline int cmn::CommonSoundManager::isPlaySound()
{
    return isPlaySound_;
}

inline unsigned int status::BasePartyStatus::getGold()
{
    return gold_;
}

inline int status::MenuStatus::getBooking()
{
    return bookingFlag_;
}

inline void status::MenuStatus::clearBooking()
{
    bookingFlag_ = 0;
}

inline void status::MenuStatus::setBooking(menu::BOOKING_FLAG flag)
{
    bookingFlag_ = flag;
}

inline int status::HaveStatus::getPlayerIndex() const
{
    return playerIndex_;
}

inline int status::HaveStatus::getLevel() const
{
    return level_;
}

inline void menu::MenuPlayerControl::setActiveChara(short chara)
{
    activeChara_ = chara;
}

inline bool MaterielMenu_CHURCH_ROOT::getSexType()
{
    return sexType_ == 1;
}

inline unsigned long dq5::level::ChurchMessage::getMessage1()
{
    return message1;
}

inline unsigned long dq5::level::ChurchMessage::getMessage2()
{
    return message2;
}

inline dq5::level::ChurchMessage* dq5::level::ChurchMessage::getRecord(int index)
{
    return (ChurchMessage*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

THUMB void MaterielMenu_CHURCH_MIRACLE::menuSetup()
{
    status::g_Party.setBattleMode();
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    menuItem_.active_ = 0;
    navigator_.setupBase();
    navigator_.setup(5, 2, status::g_Party.getCount());
    miracle_ = -1;
    miracleStatus_ = MIRACLE_NONE;
    unk_fc = 1;
    soundType_ = 1;
    MaterielMenu_CHURCH_ROOT::setTalkSound();
    for (int i = 0; i < 2; i++) {
        miracleAmount_[i] = 0;
    }
    if (status::g_Menu.getBooking() == menu::BOOKING_RETURN) {
        miracleStatus_ = MIRACLE_ISEND;
        MaterielMenu_CHURCH_ROOT::setupSexType();
    }
}

THUMB void MaterielMenu_CHURCH_MIRACLE::menuExecute()
{
    status::g_Party.setBattleMode();
    menu::MenuTemplate_materiel::MATERIEL_ICON32_5x2_CHURCH(&menuItem_, menuItem_.active_, status::g_Party.getCount());
}

THUMB void MaterielMenu_CHURCH_MIRACLE::menuDraw()
{
    if (gTownMenu_MESSAGE.isMessageWAITPROG() && miracleStatus_ != MIRACLE_ISEND && miracleStatus_ != MIRACLE_SOUND && miracleStatus_ != MIRACLE_SOUNDEND) {
        status::g_Party.setBattleMode();
        status::g_Party.getCount();
        unkfunc_0217bfbc();
        menuItem_.drawActive();
        return;
    }
    drawChurchScreen(0, 0);
}

THUMB void MaterielMenu_CHURCH_MIRACLE::menuUpdate()
{
    if (cmn::g_cmnSoundManager.isPlaySound() == true) {
        cmn::g_cmnSoundManager.execSound();
        return;
    }
    status::g_Party.setBattleMode();
    if (messageUpdate() == false) {
        listUpdate();
    }
}

THUMB void MaterielMenu_CHURCH_MIRACLE::execMiracle()
{
    status::HaveStatusInfo& statusInfo = status::g_Party.getPlayerStatus(activeChara_).haveStatusInfo_;
    if (miracle_ == MaterielMenu_CHURCH_ROOT::MIRACLE_ORDER_REVIVAL) {
        statusInfo.rebirth();
        cmn::GameManager::getSingleton().resetParty();
    } else if (miracle_ == MaterielMenu_CHURCH_ROOT::MIRACLE_ORDER_ANTIDOTE) {
        statusInfo.statusChange_.cleanup(dq5::level::ActionParam::ACTIONTYPE_DOKU);
        statusInfo.statusChange_.cleanup(dq5::level::ActionParam::ACTIONTYPE_MOUDOKU);
    } else if (miracle_ == MaterielMenu_CHURCH_ROOT::MIRACLE_ORDER_ANTICURSE) {
        statusInfo.breakSpell();
    }
}

THUMB void MaterielMenu_CHURCH_MIRACLE::makePayment()
{
    int miracle = miracle_;
    if (status::g_Party.getGold() >= miracleAmount_[miracle]) {
        if (miracle == MaterielMenu_CHURCH_ROOT::MIRACLE_ORDER_REVIVAL) {
            selectRevival();
        } else if (miracle == MaterielMenu_CHURCH_ROOT::MIRACLE_ORDER_ANTIDOTE) {
            selectAntidote();
        } else if (miracle == MaterielMenu_CHURCH_ROOT::MIRACLE_ORDER_ANTICURSE) {
            selectAntiCurse();
        }
    } else {
        gTownMenu_MESSAGE.close();
        selectCheckNG();
    }
}

THUMB bool MaterielMenu_CHURCH_MIRACLE::messageUpdate()
{
    int stat = gTownMenu_MESSAGE.stat_;
    if (gTownMenu_MESSAGE.isOpen() == false && miracleStatus_ != MIRACLE_ISEND) {
        return false;
    }
    switch (miracleStatus_) {
        case MIRACLE_NONE:
            if (stat == MENUBASE_STAT_OK || stat == MENUBASE_STAT_CANCEL) {
                gTownMenu_MESSAGE.close();
                redraw_ = 1;
            }
            break;
        case MIRACLE_CHECK:
            if (stat == MENUBASE_STAT_OK) {
                makePayment();
                redraw_ = 1;
            } else if (stat == MENUBASE_STAT_CANCEL) {
                gTownMenu_MESSAGE.close();
                selectNG();
                redraw_ = 1;
            }
            break;
        case MIRACLE_SOUND:
            if (stat == MENUBASE_STAT_OK || stat == MENUBASE_STAT_CANCEL || gTownMenu_MESSAGE.isMessageWAITPROG()) {
                MaterielMenu_CHURCH_ROOT::setTalkSound();
                gTownMenu_MESSAGE.close();
                gTownMenu_MESSAGE.openMessageForTALK();
                gTownMenu_MESSAGE.addMessageNOWAIT(getMessageNo(0x26));
                gTownMenu_MESSAGE.addMessageWAITKEY();
                openRootMenu();
            }
            return true;
        case MIRACLE_ISEND:
            if (stat == MENUBASE_STAT_OK || stat == MENUBASE_STAT_CANCEL || gTownMenu_MESSAGE.isMessageWAITPROG()) {
                gTownMenu_MESSAGE.close();
                unkfunc_02186ec8();
                redraw_ = 1;
            }
            return true;
        case MIRACLE_SOUNDEND:
            if (gTownMenu_MESSAGE.isMessageWAITPROG()) {
                cmn::g_cmnSoundManager.setFadeOut(10);
                cmn::g_cmnSoundManager.setPlaySound(3, false);
                if (miracle_ == MaterielMenu_CHURCH_ROOT::MIRACLE_ORDER_REVIVAL) {
                    miracleStatus_ = MIRACLE_ISEND;
                } else {
                    miracleStatus_ = MIRACLE_SOUND;
                }
                execMiracle();
            }
            return true;
    }
    if (gTownMenu_MESSAGE.isMessageWAITPROG() == false) {
        return true;
    }
    return false;
}

THUMB void MaterielMenu_CHURCH_MIRACLE::calcCost()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    unsigned char level = status::g_Party.getPlayerStatus(activeChara_).haveStatusInfo_.haveStatus_.level_;
    miracleAmount_[0] = (level * level + 10) / 10 * 10;
    miracleAmount_[1] = 5;
    miracleAmount_[2] = level * 30;
}

THUMB void MaterielMenu_CHURCH_MIRACLE::selectUpdate()
{
    redraw_ = 1;
    int active = menuItem_.active_;
    int playerIndex = status::g_Party.getPlayerStatus(active).haveStatusInfo_.haveStatus_.getPlayerIndex();
    switch (isMiracle(active, miracle_)) {
        case HEAL_ENABLE:
            activeChara_ = active;
            miracleStatus_ = MIRACLE_CHECK;
            calcCost();
            selectGoldCheck();
            break;
        case HEAL_NEEDLESS:
            gTownMenu_MESSAGE.openMessageForTALK();
            TextAPI::setMACRO0(0x12, 0x50000000, playerIndex);
            gTownMenu_MESSAGE.addMessage(getMiracleMessageNo(2));
            gTownMenu_MESSAGE.setMessageLastCursor(true);
            miracleStatus_ = MIRACLE_SOUND;
            break;
        case HEAL_DISABLE:
            if (miracle_ == MaterielMenu_CHURCH_ROOT::MIRACLE_ORDER_ANTICURSE) {
                gTownMenu_MESSAGE.openMessageForTALK();
                TextAPI::setMACRO0(0x12, 0x50000000, playerIndex);
                int mes1 = getMessageNo(0x1f);
                gTownMenu_MESSAGE.addMessage(mes1, getMessageNo(0x20));
                gTownMenu_MESSAGE.setMessageLastCursor(true);
                miracleStatus_ = MIRACLE_SOUND;
            }
            break;
    }
}

THUMB bool MaterielMenu_CHURCH_MIRACLE::listUpdate()
{
    if (gTownMenu_MESSAGE.isMessageWAITPROG() == false) {
        return false;
    }
    if (unk_fc) {
        unk_fc = 0;
        redraw_ = 1;
        return false;
    }
    int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
    navigator_.setup(5, 2, status::g_Party.getCount());
    if (result != 0) {
        if (result == 2) {
            selectUpdate();
            return true;
        }
        if (result == 3) {
            gTownMenu_MESSAGE.openMessageForTALK();
            gTownMenu_MESSAGE.addMessage(getMessageNo(0x25));
            miracleStatus_ = MIRACLE_SOUND;
            redraw_ = 1;
            return true;
        }
        activeChara_ = menuItem_.active_;
        menu::MaterielMenuPlayerControl::getSingleton()->setActiveChara(activeChara_);
        redraw_ = 1;
        return true;
    }
    return false;
}

THUMB void MaterielMenu_CHURCH_MIRACLE::selectRevival()
{
    gTownMenu_MESSAGE.close();
    int playerIndex = status::g_Party.getPlayerStatus(activeChara_).haveStatusInfo_.haveStatus_.getPlayerIndex();
    gTownMenu_MESSAGE.openMessageForTALK();
    TextAPI::setMACRO0(0x12, 0x50000000, playerIndex);
    gTownMenu_MESSAGE.addMessage(getMessageNo(0x16));
    gTownMenu_MESSAGE.addMessage(getMessageNo(0x17));
    gTownMenu_MESSAGE.addMessageWAITKEY();
    status::g_Menu.setBooking(menu::BOOKING_CHURCH);
    miracleStatus_ = MIRACLE_SOUNDEND;
    status::PartyStatusUtility::resetForceReorderMember();
}

THUMB void MaterielMenu_CHURCH_MIRACLE::unkfunc_02186ec8()
{
    status::HaveStatusInfo& statusInfo = status::g_Party.getPlayerStatus(activeChara_).haveStatusInfo_;
    gTownMenu_MESSAGE.close();
    if (status::g_Menu.getBooking() == menu::BOOKING_CHURCH) {
        redraw_ = 1;
        payOutMiracle();
        close();
        cmn::GameManager::getSingleton().playerManager_->setLock(true);
        cmn::GameManager::getSingleton().playerManager_->charaColl_ = 0;
        BillboardCharacter::setAllCharaAnim(false);
        MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
        return;
    }
    cmn::GameManager::getSingleton().playerManager_->setLock(false);
    cmn::GameManager::getSingleton().playerManager_->charaColl_ = 1;
    BillboardCharacter::setAllCharaAnim(true);
    int playerIndex = status::g_Party.getPlayerStatus(activeChara_).haveStatusInfo_.haveStatus_.getPlayerIndex();
    gTownMenu_MESSAGE.openMessageForMENU();
    TextAPI::setMACRO0(0x12, 0x50000000, playerIndex);
    gTownMenu_MESSAGE.addMessage(getMessageNo(0x18));
    status::g_Menu.clearBooking();
    miracleStatus_ = MIRACLE_SOUND;
}

THUMB void MaterielMenu_CHURCH_MIRACLE::selectAntidote()
{
    status::HaveStatusInfo& statusInfo = status::g_Party.getPlayerStatus(activeChara_).haveStatusInfo_;
    gTownMenu_MESSAGE.close();
    int playerIndex = status::g_Party.getPlayerStatus(activeChara_).haveStatusInfo_.haveStatus_.getPlayerIndex();
    gTownMenu_MESSAGE.openMessageForTALK();
    TextAPI::setMACRO0(0x12, 0x50000000, playerIndex);
    gTownMenu_MESSAGE.addMessage(getMessageNo(0x1c));
    gTownMenu_MESSAGE.addMessageWAITKEY();
    payOutMiracle();
    miracleStatus_ = MIRACLE_SOUNDEND;
}

THUMB void MaterielMenu_CHURCH_MIRACLE::selectAntiCurse()
{
    status::HaveStatusInfo& statusInfo = status::g_Party.getPlayerStatus(activeChara_).haveStatusInfo_;
    gTownMenu_MESSAGE.close();
    gTownMenu_MESSAGE.openMessageForTALK();
    TextAPI::setMACRO0(0x12, 0x50000000, status::g_Party.getPlayerStatus(activeChara_).haveStatusInfo_.haveStatus_.getPlayerIndex());
    gTownMenu_MESSAGE.addMessage(getMessageNo(0x22));
    gTownMenu_MESSAGE.addMessageWAITKEY();
    payOutMiracle();
    miracleStatus_ = MIRACLE_SOUNDEND;
}

THUMB void MaterielMenu_CHURCH_MIRACLE::selectGoldCheck()
{
    int playerIndex = status::g_Party.getPlayerIndex(activeChara_);
    gTownMenu_MESSAGE.openMessageForTALK();
    TextAPI::setMACRO0(0x12, 0x50000000, playerIndex);
    TextAPI::setMACRO0(0x41, 0xf0000000, miracleAmount_[0]);
    TextAPI::setMACRO0(0x40, 0xf0000000, miracleAmount_[1]);
    TextAPI::setMACRO0(0x28, 0xf0000000, miracleAmount_[2]);
    gTownMenu_MESSAGE.addMessage(getMiracleMessageNo(0));
    gTownMenu_MESSAGE.setYesNo();
}

THUMB void MaterielMenu_CHURCH_MIRACLE::selectCheckNG()
{
    gTownMenu_MESSAGE.openMessageForTALK();
    gTownMenu_MESSAGE.addMessage(getMessageNo(0x24));
    miracleStatus_ = MIRACLE_SOUND;
}

THUMB void MaterielMenu_CHURCH_MIRACLE::selectNG()
{
    gTownMenu_MESSAGE.openMessageForTALK();
    gTownMenu_MESSAGE.addMessage(getMessageNo(0x23));
    miracleStatus_ = MIRACLE_SOUND;
}

THUMB MaterielMenu_CHURCH_MIRACLE::HEAL_RESULT MaterielMenu_CHURCH_MIRACLE::isMiracle(int index, int miracle)
{
    status::HaveStatusInfo& statusInfo = status::g_Party.getPlayerStatus(index).haveStatusInfo_;
    switch (miracle) {
        case MaterielMenu_CHURCH_ROOT::MIRACLE_ORDER_REVIVAL:
            if (statusInfo.isDeath()) {
                return HEAL_ENABLE;
            }
            break;
        case MaterielMenu_CHURCH_ROOT::MIRACLE_ORDER_ANTIDOTE:
            if (statusInfo.statusChange_.isEnable(dq5::level::ActionParam::ACTIONTYPE_DOKU) || statusInfo.statusChange_.isEnable(dq5::level::ActionParam::ACTIONTYPE_MOUDOKU)) {
                return HEAL_ENABLE;
            }
            break;
        case MaterielMenu_CHURCH_ROOT::MIRACLE_ORDER_ANTICURSE:
            if (statusInfo.isSpell()) {
                return HEAL_ENABLE;
            }
            if (statusInfo.haveItem_.isSpell()) {
                return HEAL_DISABLE;
            }
            break;
    }
    return HEAL_NEEDLESS;
}

THUMB void MaterielMenu_CHURCH_MIRACLE::payOutMiracle()
{
    status::g_Party.setGold(status::g_Party.getGold() - miracleAmount_[miracle_]);
}

THUMB void MaterielMenu_CHURCH_MIRACLE::openRootMenu()
{
    close();
    gMaterielMenu_CHURCH_ROOT.open();
    gMaterielMenu_CHURCH_ROOT.menuItem_.active_ = 0;
    gMaterielMenu_CHURCH_ROOT.firstFlag_ = 0;
}

THUMB int MaterielMenu_CHURCH_MIRACLE::getMiracleMessageNo(int index)
{
    int mesIndex = 0;
    switch (index) {
        case 0:
            if (miracle_ == MaterielMenu_CHURCH_ROOT::MIRACLE_ORDER_REVIVAL) {
                mesIndex = 0x15;
            }
            if (miracle_ == MaterielMenu_CHURCH_ROOT::MIRACLE_ORDER_ANTIDOTE) {
                mesIndex = 0x1b;
            }
            if (miracle_ == MaterielMenu_CHURCH_ROOT::MIRACLE_ORDER_ANTICURSE) {
                mesIndex = 0x21;
            }
            break;
        case 1:
            if (miracle_ == MaterielMenu_CHURCH_ROOT::MIRACLE_ORDER_REVIVAL) {
                mesIndex = 0x15;
            }
            if (miracle_ == MaterielMenu_CHURCH_ROOT::MIRACLE_ORDER_ANTIDOTE) {
                mesIndex = 0x1b;
            }
            if (miracle_ == MaterielMenu_CHURCH_ROOT::MIRACLE_ORDER_ANTICURSE) {
                mesIndex = 0x21;
            }
            break;
        case 2:
            if (miracle_ == MaterielMenu_CHURCH_ROOT::MIRACLE_ORDER_REVIVAL) {
                mesIndex = 0x14;
            }
            if (miracle_ == MaterielMenu_CHURCH_ROOT::MIRACLE_ORDER_ANTIDOTE) {
                mesIndex = 0x1a;
            }
            if (miracle_ == MaterielMenu_CHURCH_ROOT::MIRACLE_ORDER_ANTICURSE) {
                mesIndex = 0x1e;
            }
            break;
    }
    return getMessageNo(mesIndex);
}

THUMB int MaterielMenu_CHURCH_MIRACLE::getMessageNo(int index)
{
    dq5::level::ChurchMessage* message = dq5::level::ChurchMessage::getRecord(index);
    unsigned long mes;
    if (MaterielMenu_CHURCH_ROOT::getSexType()) {
        mes = message->getMessage1();
    } else {
        mes = message->getMessage2();
    }
    return mes;
}
