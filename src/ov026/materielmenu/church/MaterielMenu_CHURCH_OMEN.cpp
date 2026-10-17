#include "ov026/materielmenu/church/MaterielMenu_CHURCH_OMEN.hpp"
#include "ov026/materielmenu/church/MaterielMenu_CHURCH_ROOT.hpp"
#include "ov019/leveldata/ChurchMessage.hpp"
#include "ov019/materielmenu/MaterielMenuPlayerControl.hpp"
#include "ov019/materielmenu/UnkMaterielMenuWindowDraw.hpp"
#include "main/leveldata/CharacterInitData.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/PlayerStatus.hpp"
#include "main/text/TextAPI.hpp"

inline bool status::HaveStatus::isPlayer() const
{
    int flag = false;
    unsigned char type = (unsigned char)playerType_ + 0xff;
    if (type <= 4 && ((1 << type) & 0x13)) {
        flag = true;
    }
    return flag;
}

inline int status::HaveStatus::getPlayerKindIndex() const
{
    return playerKindIndex_;
}

inline int status::HaveStatus::getLevel() const
{
    return level_;
}

inline int status::HaveStatus::getPlayerIndex() const
{
    return playerIndex_;
}

inline int status::HaveStatusInfo::getPlayerIndex() const
{
    return haveStatus_.getPlayerIndex();
}

inline dq5::level::CharacterInitData* dq5::level::CharacterInitData::getRecord(int index)
{
    return (CharacterInitData*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned char dq5::level::CharacterInitData::getMostLv()
{
    return mostLv;
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

inline bool MaterielMenu_CHURCH_ROOT::getSexType()
{
    return sexType_ == 1;
}

THUMB void MaterielMenu_CHURCH_OMEN::menuSetup()
{
    status::g_Party.setBattleMode();
    menu::MaterielMenuPlayerControl::getSingleton()->initialize();
    m_expMessageCount = 0;
    m_firstFlag = 1;
    MaterielMenu_CHURCH_ROOT::setTalkSound();
}

THUMB void MaterielMenu_CHURCH_OMEN::menuExecute()
{
}

THUMB void MaterielMenu_CHURCH_OMEN::menuDraw()
{
    unkfunc_0217bf94(0, 0);
}

THUMB void MaterielMenu_CHURCH_OMEN::menuUpdate()
{
    rootUpdate();
}

THUMB bool MaterielMenu_CHURCH_OMEN::rootUpdate()
{
    int stat = gTownMenu_MESSAGE.stat_;
    if (stat == MENUBASE_STAT_OK || stat == MENUBASE_STAT_CANCEL) {
        gTownMenu_MESSAGE.restartMessage();
        selectNextExp();
        redraw_ = 1;
        return false;
    }
    if (gTownMenu_MESSAGE.isOpen() == false) {
        selectNextExp();
        redraw_ = 1;
        return false;
    }
    return true;
}

THUMB void MaterielMenu_CHURCH_OMEN::selectNextExp()
{
    status::g_Party.setPlayerMode();
    if (m_firstFlag) {
        oneMessage(0x10);
        gTownMenu_MESSAGE.setMessageCursor(true);
        m_firstFlag = 0;
        return;
    }
    int count = m_expMessageCount;
    if (count >= status::g_Party.getCount()) {
        gTownMenu_MESSAGE.openMessageForTALK();
        gTownMenu_MESSAGE.addMessageNOWAIT(getMessageNo(0x26));
        gTownMenu_MESSAGE.addMessageWAITKEY();
        close();
        gMaterielMenu_CHURCH_ROOT.open();
        gMaterielMenu_CHURCH_ROOT.menuItem_.active_ = 0;
        gMaterielMenu_CHURCH_ROOT.firstFlag_ = 0;
        return;
    }
    status::HaveStatusInfo& statusInfo = status::g_Party.getPlayerStatus(count).haveStatusInfo_;
    int exp = statusInfo.getLevelupExp();
    if (statusInfo.haveStatus_.isPlayer() == false) {
        m_expMessageCount++;
        selectNextExp();
        return;
    }
    int maxLevel = dq5::level::CharacterInitData::getRecord(statusInfo.haveStatus_.getPlayerKindIndex())->getMostLv();
    if (maxLevel == statusInfo.haveStatus_.getLevel()) {
        int playerID = statusInfo.getPlayerIndex();
        TextAPI::setMACRO0(6, 0x50000000, playerID);
        gTownMenu_MESSAGE.addMessage(getMessageNo(0x11));
        gTownMenu_MESSAGE.setMessageCursor(true);
    } else {
        int playerID = statusInfo.getPlayerIndex();
        TextAPI::setMACRO0(6, 0x50000000, playerID);
        TextAPI::setMACRO0(8, 0xf0000000, exp);
        gTownMenu_MESSAGE.addMessage(getMessageNo(0x12));
        gTownMenu_MESSAGE.setMessageCursor(true);
    }
    m_expMessageCount++;
}

THUMB void MaterielMenu_CHURCH_OMEN::oneMessage(int mes)
{
    gTownMenu_MESSAGE.openMessageForTALK();
    gTownMenu_MESSAGE.addMessage(getMessageNo(mes));
}

THUMB int MaterielMenu_CHURCH_OMEN::getMessageNo(int index)
{
    dq5::level::ChurchMessage* pChurchMes = dq5::level::ChurchMessage::getRecord(index);
    unsigned long mes;
    if (MaterielMenu_CHURCH_ROOT::getSexType()) {
        mes = pChurchMes->getMessage1();
    } else {
        mes = pChurchMes->getMessage2();
    }
    return mes;
}
