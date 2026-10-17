#pragma ipa file
#include "ov028/sugoroku/TownSugorokuPanelAction.hpp"
#include "ov028/sugoroku/TownSugorokuPanelChanceCard.hpp"
#include "ov001/leveldata/FurnitureData.hpp"
#include "ov001/town/TownFurniture.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov001/town/TownSugorokuManager.hpp"
#include "ov001/town/TownWindowSystem.hpp"
#include "ov001/town/riseup/TownRiseupManager.hpp"
#include "ov019/materielmenu/MaterielMenu_WINDOW_MANAGER.hpp"
#include "main/btl/Encount.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/dss/UnkRandom.hpp"
#include "main/leveldata/SugorokuChanceCard.hpp"
#include "main/leveldata/SugorokuChangeMsg.hpp"
#include "main/leveldata/SugorokuData.hpp"
#include "main/leveldata/SugorokuPanelList.hpp"
#include "main/leveldata/SugorokuSpecialMsg.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/sound/SoundManager.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/StageAttribute.hpp"
#include "main/status/StageInfo.hpp"
#include "main/text/TextAPI.hpp"
#include "main/town/TownSugorokuInfo.hpp"
#include "main/window/ShopMenuControl.hpp"

#pragma thumb on

inline void twn::SugorokuPanelActionSelectSpot::execute()
{
}

inline void twn::SugorokuPanelActionHealPoint::execute()
{
}

inline void twn::SugorokuPanelActionChangeGate::execute()
{
}

inline void twn::SugorokuPanelActionShop::execute()
{
}

inline void twn::SugorokuPanelActionInn::execute()
{
}

inline void twn::SugorokuPanelActionTravelGate::execute()
{
}

inline void twn::SugorokuPanelActionHoleTrap::execute()
{
}

inline void twn::SugorokuPanelActionBackToStart::execute()
{
}

inline void twn::SugorokuPanelActionChanceCard::execute()
{
}

inline void twn::SugorokuPanelActionLostMp::execute()
{
}

inline void twn::SugorokuPanelActionDamage::execute()
{
}

inline void twn::SugorokuPanelActionEncountMetal::execute()
{
}

inline void twn::SugorokuPanelActionEncountNormal::execute()
{
}

inline void twn::SugorokuPanelActionMoveBack6::execute()
{
}

inline void twn::SugorokuPanelActionMoveBack5::execute()
{
}

inline void twn::SugorokuPanelActionMoveBack4::execute()
{
}

inline void twn::SugorokuPanelActionMoveBack3::execute()
{
}

inline void twn::SugorokuPanelActionMoveBack2::execute()
{
}

inline void twn::SugorokuPanelActionMoveBack1::execute()
{
}

inline void twn::SugorokuPanelActionMoveNext6::execute()
{
}

inline void twn::SugorokuPanelActionMoveNext5::execute()
{
}

inline void twn::SugorokuPanelActionMoveNext4::execute()
{
}

inline void twn::SugorokuPanelActionMoveNext3::execute()
{
}

inline void twn::SugorokuPanelActionMoveNext2::execute()
{
}

inline void twn::SugorokuPanelActionMoveNext1::execute()
{
}

inline void twn::SugorokuPanelActionDiceDown5::execute()
{
}

inline void twn::SugorokuPanelActionDiceDown3::execute()
{
}

inline void twn::SugorokuPanelActionDiceDown2::execute()
{
}

inline void twn::SugorokuPanelActionDiceDown1::execute()
{
}

inline void twn::SugorokuPanelActionDiceUp5::execute()
{
}

inline void twn::SugorokuPanelActionDiceUp3::execute()
{
}

inline void twn::SugorokuPanelActionDiceUp2::execute()
{
}

inline void twn::SugorokuPanelActionDiceUp1::execute()
{
}

inline void twn::SugorokuPanelActionGoldDown5000::execute()
{
}

inline void twn::SugorokuPanelActionGoldDown3000::execute()
{
}

inline void twn::SugorokuPanelActionGoldDown2000::execute()
{
}

inline void twn::SugorokuPanelActionGoldDown1000::execute()
{
}

inline void twn::SugorokuPanelActionGoldDown500::execute()
{
}

inline void twn::SugorokuPanelActionGoldDown300::execute()
{
}

inline void twn::SugorokuPanelActionGoldDown200::execute()
{
}

inline void twn::SugorokuPanelActionGoldDown100::execute()
{
}

inline void twn::SugorokuPanelActionGoldDown50::execute()
{
}

inline void twn::SugorokuPanelActionGoldUp5000::execute()
{
}

inline void twn::SugorokuPanelActionGoldUp3000::execute()
{
}

inline void twn::SugorokuPanelActionGoldUp2000::execute()
{
}

inline void twn::SugorokuPanelActionGoldUp1000::execute()
{
}

inline void twn::SugorokuPanelActionGoldUp500::execute()
{
}

inline void twn::SugorokuPanelActionGoldUp300::execute()
{
}

inline void twn::SugorokuPanelActionGoldUp200::execute()
{
}

inline void twn::SugorokuPanelActionGoldUp100::execute()
{
}

inline void twn::SugorokuPanelActionGoldUp50::execute()
{
}

inline void twn::SugorokuPanelActionKaidanDown::execute()
{
}

inline void twn::SugorokuPanelActionKaidanDown::setup()
{
}

inline void twn::SugorokuPanelActionKaidanUp::execute()
{
}

inline void twn::SugorokuPanelActionKaidanUp::setup()
{
}

inline dq5::level::SugorokuPanelList* dq5::level::SugorokuPanelList::getRecord(int index)
{
    return (SugorokuPanelList*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline dq5::level::SugorokuSpecialMsg* dq5::level::SugorokuSpecialMsg::getRecord(int index)
{
    return (SugorokuSpecialMsg*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline dq5::level::SugorokuChangeMsg* dq5::level::SugorokuChangeMsg::getRecord(int index)
{
    return (SugorokuChangeMsg*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline dq5::level::SugorokuChanceCard* dq5::level::SugorokuChanceCard::getRecord(int index)
{
    return (SugorokuChanceCard*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline char dq5::level::SugorokuChanceCard::getFloor1()
{
    return byte_1 & 0x01;
}

inline char dq5::level::SugorokuChanceCard::getFloor2()
{
    return (byte_1 & 0x02) >> 1;
}

inline char dq5::level::SugorokuChanceCard::getFloor3()
{
    return (byte_1 & 0x04) >> 2;
}

inline char dq5::level::SugorokuChanceCard::getFloor4()
{
    return (byte_1 & 0x08) >> 3;
}

inline char dq5::level::SugorokuChanceCard::getFloor5()
{
    return (byte_1 & 0x10) >> 4;
}

inline char dq5::level::SugorokuChanceCard::getFloor6()
{
    return (byte_1 & 0x20) >> 5;
}

inline char dq5::level::SugorokuChanceCard::getFloor7()
{
    return (byte_1 & 0x40) >> 6;
}

inline char dq5::level::SugorokuChanceCard::getFloor8()
{
    return (byte_1 & 0x80) >> 7;
}

inline char dq5::level::SugorokuChanceCard::getFloor9()
{
    return byte_2 & 0x01;
}

inline char dq5::level::SugorokuChanceCard::getFloor10()
{
    return (byte_2 & 0x02) >> 1;
}

inline char dq5::level::SugorokuChanceCard::getFloor11()
{
    return (byte_2 & 0x04) >> 2;
}

inline char dq5::level::SugorokuChanceCard::getFloor12()
{
    return (byte_2 & 0x08) >> 3;
}

inline char dq5::level::SugorokuChanceCard::getFloor13()
{
    return (byte_2 & 0x10) >> 4;
}

inline char dq5::level::SugorokuChanceCard::getFloor14()
{
    return (byte_2 & 0x20) >> 5;
}

inline dq5::level::SugorokuData* dq5::level::SugorokuData::getRecord(int index)
{
    return (SugorokuData*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned int dq5::level::SugorokuData::getArraySize()
{
    return binary_.record_;
}

inline unsigned short dq5::level::SugorokuData::getMoneyMin()
{
    return moneyMin;
}

inline unsigned short dq5::level::SugorokuData::getMoneyMax()
{
    return moneyMax;
}

inline dq5::level::FurnitureData* dq5::level::FurnitureData::getRecord(int index)
{
    return (FurnitureData*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned int status::BasePartyStatus::getGold()
{
    return gold_;
}

inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo()
{
    return haveStatusInfo_;
}

inline status::HaveStatus& status::HaveStatusInfo::getHaveStatus()
{
    return haveStatus_;
}

inline int status::HaveStatus::getLevel() const
{
    return level_;
}

inline menu::MenuBase::MENUBASE_STAT menu::MenuBase::getStat()
{
    return stat_;
}

inline void window::ShopMenuControl::startMenu(int menuType)
{
    menuType_ = menuType;
    state_ = 7;
}

inline bool window::ShopMenuControl::isMenuEnd()
{
    return state_ == 8;
}

inline void MaterielMenu_WINDOW_MANAGER::setSugorokuItem(short item)
{
    sugorokuItem_ = item;
}

inline unsigned short twn::PanelData::getUid()
{
    return uid_;
}

inline unsigned short twn::PanelData::getPanelID()
{
    return panelID_;
}

inline void twn::PanelData::setPanelID(unsigned short id)
{
    panelID_ = id;
}

inline twn::PanelData* twn::TownSugorokuInfo::getNowPane()
{
    return nowPanel;
}

inline int twn::TownSugorokuInfo::getDiceCount()
{
    return diceCount_;
}

inline void twn::TownSugorokuInfo::setDiceCount(unsigned short count)
{
    diceCount_ = count;
}

inline void twn::TownSugorokuInfo::setNowMoveCount(char count)
{
    nowMoveCount = count;
}

inline void twn::TownSugorokuInfo::setBack(bool flag)
{
    back_ = flag;
}

inline void twn::TownSugorokuInfo::setContinue(int state)
{
    continueState_ = state;
}

inline void twn::TownSugorokuInfo::setNextMapPanelUid(unsigned short uid)
{
    nextPanelUid_ = uid;
}

inline unsigned short twn::TownSugorokuInfo::getChanceCardID()
{
    return chanceCardID_;
}

inline void twn::TownSugorokuInfo::setChanceCardID(unsigned short id)
{
    chanceCardID_ = id;
}

inline int twn::TownSugorokuManager::getStageNo()
{
    return stageNO_;
}

inline int twn::TownSugorokuManager::getStageOffset()
{
    return stageOffset_;
}

inline void twn::TownSugorokuManager::setDrawDiceFreeOneFrame(int dice)
{
    drawDiceNo_ = dice;
}

inline void btl::EncountData::setTeamAddEnable(bool flag)
{
    teamAddEnable_ = flag;
}

inline void btl::EncountData::setEventEncount(bool flag)
{
    eventEncount_ = flag;
}

inline int btl::Encount::getRandomTileID(int min, int max)
{
    return encountData_.getRandomTileID(min, max);
}

inline void btl::Encount::setFriendMonster(bool flag)
{
    encountData_.setTeamAddEnable(flag);
}

inline void btl::Encount::setEventEncount(bool flag)
{
    encountData_.setEventEncount(flag);
}

int twn::SugorokuPanelActionKaidanUp::nextState()
{
    SoundManager::playSe(0x131, 0);
    return sugoroku::SYSTEM_PANEL_LINK;
}

int twn::SugorokuPanelActionKaidanDown::nextState()
{
    SoundManager::playSe(0x131, 0);
    return sugoroku::SYSTEM_PANEL_LINK;
}

void twn::SugorokuPanelActionGoldUp50::setup()
{
    SugorokuPanelAction::goldUp(50);
}

int twn::SugorokuPanelActionGoldUp50::nextState()
{
    return sugoroku::SYSTEM_OPEN_MENU;
}

void twn::SugorokuPanelActionGoldUp100::setup()
{
    SugorokuPanelAction::goldUp(100);
}

int twn::SugorokuPanelActionGoldUp100::nextState()
{
    return sugoroku::SYSTEM_OPEN_MENU;
}

void twn::SugorokuPanelActionGoldUp200::setup()
{
    SugorokuPanelAction::goldUp(200);
}

int twn::SugorokuPanelActionGoldUp200::nextState()
{
    return sugoroku::SYSTEM_OPEN_MENU;
}

void twn::SugorokuPanelActionGoldUp300::setup()
{
    SugorokuPanelAction::goldUp(300);
}

int twn::SugorokuPanelActionGoldUp300::nextState()
{
    return sugoroku::SYSTEM_OPEN_MENU;
}

void twn::SugorokuPanelActionGoldUp500::setup()
{
    SugorokuPanelAction::goldUp(500);
}

int twn::SugorokuPanelActionGoldUp500::nextState()
{
    return sugoroku::SYSTEM_OPEN_MENU;
}

void twn::SugorokuPanelActionGoldUp1000::setup()
{
    SugorokuPanelAction::goldUp(1000);
}

int twn::SugorokuPanelActionGoldUp1000::nextState()
{
    return sugoroku::SYSTEM_OPEN_MENU;
}

void twn::SugorokuPanelActionGoldUp2000::setup()
{
    SugorokuPanelAction::goldUp(2000);
}

int twn::SugorokuPanelActionGoldUp2000::nextState()
{
    return sugoroku::SYSTEM_OPEN_MENU;
}

void twn::SugorokuPanelActionGoldUp3000::setup()
{
    SugorokuPanelAction::goldUp(3000);
}

int twn::SugorokuPanelActionGoldUp3000::nextState()
{
    return sugoroku::SYSTEM_OPEN_MENU;
}

void twn::SugorokuPanelActionGoldUp5000::setup()
{
    SugorokuPanelAction::goldUp(5000);
}

int twn::SugorokuPanelActionGoldUp5000::nextState()
{
    return sugoroku::SYSTEM_OPEN_MENU;
}

void twn::SugorokuPanelActionGoldDown50::setup()
{
    endFlag_ = SugorokuPanelAction::goldDown(50);
}

int twn::SugorokuPanelActionGoldDown50::nextState()
{
    if (endFlag_ == false) {
        return sugoroku::SYSTEM_FADE_OUT_END;
    }
    return sugoroku::SYSTEM_OPEN_MENU;
}

void twn::SugorokuPanelActionGoldDown100::setup()
{
    endFlag_ = SugorokuPanelAction::goldDown(100);
}

int twn::SugorokuPanelActionGoldDown100::nextState()
{
    if (endFlag_ == false) {
        return sugoroku::SYSTEM_FADE_OUT_END;
    }
    return sugoroku::SYSTEM_OPEN_MENU;
}

void twn::SugorokuPanelActionGoldDown200::setup()
{
    endFlag_ = SugorokuPanelAction::goldDown(200);
}

int twn::SugorokuPanelActionGoldDown200::nextState()
{
    if (endFlag_ == false) {
        return sugoroku::SYSTEM_FADE_OUT_END;
    }
    return sugoroku::SYSTEM_OPEN_MENU;
}

void twn::SugorokuPanelActionGoldDown300::setup()
{
    endFlag_ = SugorokuPanelAction::goldDown(300);
}

int twn::SugorokuPanelActionGoldDown300::nextState()
{
    if (endFlag_ == false) {
        return sugoroku::SYSTEM_FADE_OUT_END;
    }
    return sugoroku::SYSTEM_OPEN_MENU;
}

void twn::SugorokuPanelActionGoldDown500::setup()
{
    endFlag_ = SugorokuPanelAction::goldDown(500);
}

int twn::SugorokuPanelActionGoldDown500::nextState()
{
    if (endFlag_ == false) {
        return sugoroku::SYSTEM_FADE_OUT_END;
    }
    return sugoroku::SYSTEM_OPEN_MENU;
}

void twn::SugorokuPanelActionGoldDown1000::setup()
{
    endFlag_ = SugorokuPanelAction::goldDown(1000);
}

int twn::SugorokuPanelActionGoldDown1000::nextState()
{
    if (endFlag_ == false) {
        return sugoroku::SYSTEM_FADE_OUT_END;
    }
    return sugoroku::SYSTEM_OPEN_MENU;
}

void twn::SugorokuPanelActionGoldDown2000::setup()
{
    endFlag_ = SugorokuPanelAction::goldDown(2000);
}

int twn::SugorokuPanelActionGoldDown2000::nextState()
{
    if (endFlag_ == false) {
        return sugoroku::SYSTEM_FADE_OUT_END;
    }
    return sugoroku::SYSTEM_OPEN_MENU;
}

void twn::SugorokuPanelActionGoldDown3000::setup()
{
    endFlag_ = SugorokuPanelAction::goldDown(3000);
}

int twn::SugorokuPanelActionGoldDown3000::nextState()
{
    if (endFlag_ == false) {
        return sugoroku::SYSTEM_FADE_OUT_END;
    }
    return sugoroku::SYSTEM_OPEN_MENU;
}

void twn::SugorokuPanelActionGoldDown5000::setup()
{
    endFlag_ = SugorokuPanelAction::goldDown(5000);
}

int twn::SugorokuPanelActionGoldDown5000::nextState()
{
    if (endFlag_ == false) {
        return sugoroku::SYSTEM_FADE_OUT_END;
    }
    return sugoroku::SYSTEM_OPEN_MENU;
}

void twn::SugorokuPanelActionDiceUp1::setup()
{
    SugorokuPanelAction::diceUp(1);
}

int twn::SugorokuPanelActionDiceUp1::nextState()
{
    return sugoroku::SYSTEM_OPEN_MENU;
}

void twn::SugorokuPanelActionDiceUp2::setup()
{
    SugorokuPanelAction::diceUp(2);
}

int twn::SugorokuPanelActionDiceUp2::nextState()
{
    return sugoroku::SYSTEM_OPEN_MENU;
}

void twn::SugorokuPanelActionDiceUp3::setup()
{
    SugorokuPanelAction::diceUp(3);
}

int twn::SugorokuPanelActionDiceUp3::nextState()
{
    return sugoroku::SYSTEM_OPEN_MENU;
}

void twn::SugorokuPanelActionDiceUp5::setup()
{
    SugorokuPanelAction::diceUp(5);
}

int twn::SugorokuPanelActionDiceUp5::nextState()
{
    return sugoroku::SYSTEM_OPEN_MENU;
}

void twn::SugorokuPanelActionDiceDown1::setup()
{
    SugorokuPanelAction::diceDown(1);
}

int twn::SugorokuPanelActionDiceDown1::nextState()
{
    return SugorokuPanelAction::isMessageOpen(sugoroku::NEXT_ACTION_DICE);
}

void twn::SugorokuPanelActionDiceDown2::setup()
{
    SugorokuPanelAction::diceDown(2);
}

int twn::SugorokuPanelActionDiceDown2::nextState()
{
    return SugorokuPanelAction::isMessageOpen(sugoroku::NEXT_ACTION_DICE);
}

void twn::SugorokuPanelActionDiceDown3::setup()
{
    SugorokuPanelAction::diceDown(3);
}

int twn::SugorokuPanelActionDiceDown3::nextState()
{
    return SugorokuPanelAction::isMessageOpen(sugoroku::NEXT_ACTION_DICE);
}

void twn::SugorokuPanelActionDiceDown5::setup()
{
    SugorokuPanelAction::diceDown(5);
}

int twn::SugorokuPanelActionDiceDown5::nextState()
{
    return SugorokuPanelAction::isMessageOpen(sugoroku::NEXT_ACTION_DICE);
}

void twn::SugorokuPanelActionMoveNext1::setup()
{
    SugorokuPanelAction::moveNext(1);
}

int twn::SugorokuPanelActionMoveNext1::nextState()
{
    return SugorokuPanelAction::isMessageOpen(sugoroku::NEXT_ACTION_MOVE);
}

void twn::SugorokuPanelActionMoveNext2::setup()
{
    SugorokuPanelAction::moveNext(2);
}

int twn::SugorokuPanelActionMoveNext2::nextState()
{
    return SugorokuPanelAction::isMessageOpen(sugoroku::NEXT_ACTION_MOVE);
}

void twn::SugorokuPanelActionMoveNext3::setup()
{
    SugorokuPanelAction::moveNext(3);
}

int twn::SugorokuPanelActionMoveNext3::nextState()
{
    return SugorokuPanelAction::isMessageOpen(sugoroku::NEXT_ACTION_MOVE);
}

void twn::SugorokuPanelActionMoveNext4::setup()
{
    SugorokuPanelAction::moveNext(4);
}

int twn::SugorokuPanelActionMoveNext4::nextState()
{
    return SugorokuPanelAction::isMessageOpen(sugoroku::NEXT_ACTION_MOVE);
}

void twn::SugorokuPanelActionMoveNext5::setup()
{
    SugorokuPanelAction::moveNext(5);
}

int twn::SugorokuPanelActionMoveNext5::nextState()
{
    return SugorokuPanelAction::isMessageOpen(sugoroku::NEXT_ACTION_MOVE);
}

void twn::SugorokuPanelActionMoveNext6::setup()
{
    SugorokuPanelAction::moveNext(6);
}

int twn::SugorokuPanelActionMoveNext6::nextState()
{
    return SugorokuPanelAction::isMessageOpen(sugoroku::NEXT_ACTION_MOVE);
}

void twn::SugorokuPanelActionMoveBack1::setup()
{
    SugorokuPanelAction::moveBack(1);
}

int twn::SugorokuPanelActionMoveBack1::nextState()
{
    return SugorokuPanelAction::isMessageOpen(sugoroku::NEXT_ACTION_MOVE);
}

void twn::SugorokuPanelActionMoveBack2::setup()
{
    SugorokuPanelAction::moveBack(2);
}

int twn::SugorokuPanelActionMoveBack2::nextState()
{
    return SugorokuPanelAction::isMessageOpen(sugoroku::NEXT_ACTION_MOVE);
}

void twn::SugorokuPanelActionMoveBack3::setup()
{
    SugorokuPanelAction::moveBack(3);
}

int twn::SugorokuPanelActionMoveBack3::nextState()
{
    return SugorokuPanelAction::isMessageOpen(sugoroku::NEXT_ACTION_MOVE);
}

void twn::SugorokuPanelActionMoveBack4::setup()
{
    SugorokuPanelAction::moveBack(4);
}

int twn::SugorokuPanelActionMoveBack4::nextState()
{
    return SugorokuPanelAction::isMessageOpen(sugoroku::NEXT_ACTION_MOVE);
}

void twn::SugorokuPanelActionMoveBack5::setup()
{
    SugorokuPanelAction::moveBack(5);
}

int twn::SugorokuPanelActionMoveBack5::nextState()
{
    return SugorokuPanelAction::isMessageOpen(sugoroku::NEXT_ACTION_MOVE);
}

void twn::SugorokuPanelActionMoveBack6::setup()
{
    SugorokuPanelAction::moveBack(6);
}

int twn::SugorokuPanelActionMoveBack6::nextState()
{
    return SugorokuPanelAction::isMessageOpen(sugoroku::NEXT_ACTION_MOVE);
}

void twn::SugorokuPanelActionEncountNormal::setup()
{
    SugorokuPanelAction::startSugorokuEncount(sugoroku::ENCOUNT_TYPE_NORMAL);
}

int twn::SugorokuPanelActionEncountNormal::nextState()
{
    return sugoroku::NOT_CHANGE_STATE;
}

void twn::SugorokuPanelActionEncountMetal::setup()
{
    SugorokuPanelAction::startSugorokuEncount(sugoroku::ENCOUNT_TYPE_METAL);
}

int twn::SugorokuPanelActionEncountMetal::nextState()
{
    return sugoroku::NOT_CHANGE_STATE;
}

void twn::SugorokuPanelActionDamage::setup()
{
    endFlag_ = false;
    status::HaveStatusInfo& statusInfo = status::g_Party.getPlayerStatus(0).getHaveStatusInfo();
    int damage = statusInfo.getHpMax() / 3;
    int mes = dq5::level::SugorokuPanelList::getRecord(0x2d)->execMsg;
    TextAPI::setMACRO0(0x2b, 0xf0000000, damage);
    TownWindowSystem::getSingleton().openSystemMessage();
    TownWindowSystem::getSingleton().serialCommonMessage(mes);
    damage = -damage;
    statusInfo.addHp(damage);
}

int twn::SugorokuPanelActionDamage::nextState()
{
    return sugoroku::SYSTEM_OPEN_MENU;
}

void twn::SugorokuPanelActionLostMp::setup()
{
    status::HaveStatusInfo& statusInfo = status::g_Party.getPlayerStatus(0).getHaveStatusInfo();
    int nowMp = statusInfo.getMp();
    int xMP = 0, downMp = 0, mesNo;
    if (nowMp == 0) {
        mesNo = dq5::level::SugorokuSpecialMsg::getRecord(0)->msg2;
    } else {
        if (nowMp != 1) {
            xMP = nowMp / 2;
        }
        downMp = nowMp - xMP;
        statusInfo.setMp(xMP);
        mesNo = dq5::level::SugorokuSpecialMsg::getRecord(0)->msg1;
    }
    TextAPI::setMACRO0(0x51, 0xf0000000, downMp);
    TownWindowSystem::getSingleton().openSystemMessage();
    TownWindowSystem::getSingleton().serialCommonMessage(mesNo);
}

int twn::SugorokuPanelActionLostMp::nextState()
{
    return sugoroku::SYSTEM_OPEN_MENU;
}

void twn::SugorokuPanelActionChangeParameter::setup()
{
    endFlag_ = false;
    mode_ = DICE_START;
    chanceParam_ = UnkDssRand::rand(6) + 1;
    updownParam_ = 0;
    SugorokuPanelAction::openPanelActionMessage();
}

void twn::SugorokuPanelActionChangeParameter::execute()
{
    if (TownWindowSystem::getSingleton().isMessageStart() == true) {
        return;
    }
    if (TownSugorokuManager::getSingleton().isDiceAnimEnd() == true) {
        switch (mode_) {
        case DICE_START:
            TownSugorokuManager::getSingleton().diceThrowIn(chanceParam_);
            mode_ = DICE_PARAM;
            break;
        case DICE_PARAM: {
            TownSugorokuManager::getSingleton().setDrawDiceFreeOneFrame(chanceParam_);
            int panelActionNo = g_SugorokuInfo.getNowPane()->getPanelID();
            int mes = dq5::level::SugorokuPanelList::getRecord(panelActionNo + 1)->execMsg;
            SugorokuPanelChanceCard::setParameterMacro(chanceParam_ - 1);
            TownWindowSystem::getSingleton().openSystemMessage(mes + 1, 1);
            updownParam_ = UnkDssRand::rand(6) + 1;
            mode_ = DICE_UP_DOWN;
            break;
        }
        case DICE_UP_DOWN:
            TownSugorokuManager::getSingleton().setDrawDiceFreeOneFrame(0);
            TownSugorokuManager::getSingleton().diceThrowIn(updownParam_);
            mode_ = DICE_CLOSE;
            break;
        case DICE_CLOSE: {
            TownSugorokuManager::getSingleton().setDrawDiceFreeOneFrame(updownParam_);
            unsigned long mes;
            dq5::level::SugorokuSpecialMsg* spMsg = dq5::level::SugorokuSpecialMsg::getRecord(1);
            if (updownParam_ % 2 == 0) {
                mes = spMsg->msg1;
            } else {
                mes = spMsg->msg2;
            }
            SugorokuPanelChanceCard::setParameterMacro(chanceParam_ - 1);
            TownWindowSystem::getSingleton().openSystemMessage(mes, 1);
            if (updownParam_ % 2 == 0) {
                if (isParamLimitValue(true) == true) {
                    TownWindowSystem::getSingleton().addCommonMessage(dq5::level::SugorokuChangeMsg::getRecord(2)->msg1);
                }
            } else {
                if (isParamLimitValue(false) == true) {
                    TownWindowSystem::getSingleton().addCommonMessage(dq5::level::SugorokuChangeMsg::getRecord(3)->msg1);
                }
            }
            mode_ = DICE_END;
            break;
        }
        case DICE_END:
            TownSugorokuManager::getSingleton().setDrawDiceFreeOneFrame(0);
            changeParam();
            endFlag_ = true;
            break;
        }
    }
}

int twn::SugorokuPanelActionChangeParameter::nextState()
{
    if (endFlag_ == true) {
        return sugoroku::SYSTEM_OPEN_MENU;
    }
    return sugoroku::NOT_CHANGE_STATE;
}

bool twn::SugorokuPanelActionChangeParameter::isParamLimitValue(bool max)
{
    bool paramLimit = false;
    int noEquip = 1;
    status::HaveStatusInfo& statusInfo = status::g_Party.getPlayerStatus(0).getHaveStatusInfo();
    if (max == true) {
        switch (chanceParam_) {
        case SugorokuPanelChanceCard::CHANCE_STRENGTH:
            if (statusInfo.getStrength(noEquip) == 255) {
                paramLimit = true;
            }
            break;
        case SugorokuPanelChanceCard::CHANCE_AGILITY:
            if (statusInfo.getAgility(noEquip) == 255) {
                paramLimit = true;
            }
            break;
        case SugorokuPanelChanceCard::CHANCE_PROTECTION:
            if (statusInfo.getProtection(noEquip) == 255) {
                paramLimit = true;
            }
            break;
        case SugorokuPanelChanceCard::CHANCE_WISDOM:
            if (statusInfo.getWisdom(noEquip) == 255) {
                paramLimit = true;
            }
            break;
        case SugorokuPanelChanceCard::CHANCE_LUCK:
            if (statusInfo.getLuck(noEquip) == 255) {
                paramLimit = true;
            }
            break;
        case SugorokuPanelChanceCard::CHANCE_MAXHP:
            if (statusInfo.getHpMax() == 999) {
                paramLimit = true;
            }
            break;
        }
    } else {
        switch (chanceParam_) {
        case SugorokuPanelChanceCard::CHANCE_STRENGTH:
            if (statusInfo.getStrength(noEquip) == 0) {
                paramLimit = true;
            }
            break;
        case SugorokuPanelChanceCard::CHANCE_AGILITY:
            if (statusInfo.getAgility(noEquip) == 0) {
                paramLimit = true;
            }
            break;
        case SugorokuPanelChanceCard::CHANCE_PROTECTION:
            if (statusInfo.getProtection(noEquip) == 0) {
                paramLimit = true;
            }
            break;
        case SugorokuPanelChanceCard::CHANCE_WISDOM:
            if (statusInfo.getWisdom(noEquip) == 0) {
                paramLimit = true;
            }
            break;
        case SugorokuPanelChanceCard::CHANCE_LUCK:
            if (statusInfo.getLuck(noEquip) == 0) {
                paramLimit = true;
            }
            break;
        case SugorokuPanelChanceCard::CHANCE_MAXHP:
            if (statusInfo.getHpMax() == 1) {
                paramLimit = true;
            }
            break;
        }
    }
    return paramLimit;
}

void twn::SugorokuPanelActionChangeParameter::changeParam()
{
    status::HaveStatus& status = status::g_Party.getPlayerStatus(0).getHaveStatusInfo().getHaveStatus();
    char value = 1;
    if (updownParam_ % 2 != 0) {
        value *= -1;
        if (isParamLimitValue(false) == true) {
            return;
        }
    } else {
        if (isParamLimitValue(true) == true) {
            return;
        }
    }
    switch (chanceParam_) {
    case SugorokuPanelChanceCard::CHANCE_STRENGTH:
        status.addStrength(value);
        break;
    case SugorokuPanelChanceCard::CHANCE_AGILITY:
        status.addAgility(value);
        break;
    case SugorokuPanelChanceCard::CHANCE_PROTECTION:
        status.addProtection(value);
        break;
    case SugorokuPanelChanceCard::CHANCE_WISDOM:
        status.addWisdom(value);
        break;
    case SugorokuPanelChanceCard::CHANCE_LUCK:
        status.addLuck(value);
        break;
    case SugorokuPanelChanceCard::CHANCE_MAXHP:
        status.addHpMax(value);
        if (status.getHpMax() < status.getHp()) {
            status.setHp(status.getHpMax());
        }
        break;
    }
}

void twn::SugorokuPanelActionChanceCard::setup()
{
    SugorokuPanelAction::openPanelActionMessage();
    int selectChance = UnkDssRand::rand(38) + 1;
    if (g_SugorokuInfo.getChanceCardID() == 0) {
        g_SugorokuInfo.setChanceCardID(selectChance);
    } else {
        selectChance = g_SugorokuInfo.getChanceCardID();
    }
    while (SugorokuPanelAction::isSelectChanceCard(selectChance) == false) {
        selectChance = UnkDssRand::rand(38) + 1;
    }
    g_SugorokuInfo.setChanceCardID(selectChance);
}

int twn::SugorokuPanelActionChanceCard::nextState()
{
    return g_SugorokuInfo.getChanceCardID() + sugoroku::PANEL_TREASUER_BOX_OPEN;
}

void twn::SugorokuPanelActionBackToStart::setup()
{
    SugorokuPanelAction::openPanelActionMessage();
}

int twn::SugorokuPanelActionBackToStart::nextState()
{
    return sugoroku::SYSTEM_PANEL_LINK;
}

void twn::SugorokuPanelActionHoleTrap::setup()
{
    SugorokuPanelAction::openPanelActionMessage();
    g_SugorokuInfo.getNowPane()->setPanelID(0x44);
}

int twn::SugorokuPanelActionHoleTrap::nextState()
{
    return sugoroku::SYSTEM_PANEL_LINK;
}

void twn::SugorokuPanelActionTravelGate::setup()
{
}

int twn::SugorokuPanelActionTravelGate::nextState()
{
    return sugoroku::SYSTEM_PANEL_LINK;
}

void twn::SugorokuPanelActionTansu::setup()
{
    endFlag_ = false;
    yesnoFlag_ = true;
    openMenu_ = false;
    item_.index = 0;
    item_.itemID[0] = 0;
    item_.itemID[1] = 0;
    item_.messageNo[0] = 0;
    item_.messageNo[1] = 0;
    SugorokuPanelAction::openPanelActionMessage();
    gTownMenu_MESSAGE.setYesNo();
}

void twn::SugorokuPanelActionTansu::execute()
{
    int stat = menu::MenuBase::MENUBASE_STAT_ACTIVE;
    if (yesnoFlag_ == true) {
        stat = gTownMenu_MESSAGE.getStat();
    }
    if (stat == menu::MenuBase::MENUBASE_STAT_OK) {
        openMenu_ = SugorokuPanelAction::addTreasuerMessage(SugorokuPanelAction::TYPE_TANSU, item_);
        yesnoFlag_ = false;
    }
    if (stat == menu::MenuBase::MENUBASE_STAT_CANCEL) {
        endFlag_ = true;
    }
    if (yesnoFlag_ != true && TownRiseupManager::getSingleton().isEnable(item_.index) == false) {
        if (openMenu_ == true) {
            window::gShopMenuControl.startMenu(0x22);
            MaterielMenu_WINDOW_MANAGER::getSingleton()->setSugorokuItem(item_.itemID[0]);
        } else {
            TextAPI::setMACRO0(0x32, 0xf0000000, item_.itemID[0]);
            TownWindowSystem::getSingleton().openSystemMessage(item_.messageNo[0], 1);
            if (item_.messageNo[1] != 0) {
                TextAPI::setMACRO0(0x32, 0xf0000000, item_.itemID[1]);
                TownWindowSystem::getSingleton().addCommonMessage(item_.messageNo[1]);
            }
        }
        endFlag_ = true;
    }
}

int twn::SugorokuPanelActionTansu::nextState()
{
    if (endFlag_ == true) {
        return sugoroku::SYSTEM_OPEN_MENU;
    }
    return sugoroku::NOT_CHANGE_STATE;
}

void twn::SugorokuPanelActionTubo::setup()
{
    endFlag_ = false;
    yesnoFlag_ = true;
    openMenu_ = false;
    item_.index = 0;
    item_.itemID[0] = 0;
    item_.itemID[1] = 0;
    item_.messageNo[0] = 0;
    item_.messageNo[1] = 0;
    SugorokuPanelAction::openPanelActionMessage();
    gTownMenu_MESSAGE.setYesNo();
}

void twn::SugorokuPanelActionTubo::execute()
{
    int stat = menu::MenuBase::MENUBASE_STAT_ACTIVE;
    if (yesnoFlag_ == true) {
        stat = gTownMenu_MESSAGE.getStat();
    }
    if (stat == menu::MenuBase::MENUBASE_STAT_OK) {
        openMenu_ = SugorokuPanelAction::addTreasuerMessage(SugorokuPanelAction::TYPE_TUBO, item_);
        yesnoFlag_ = false;
    }
    if (stat == menu::MenuBase::MENUBASE_STAT_CANCEL) {
        endFlag_ = true;
    }
    if (yesnoFlag_ != true && TownRiseupManager::getSingleton().isEnable(item_.index) == false) {
        if (openMenu_ == true) {
            window::gShopMenuControl.startMenu(0x22);
            MaterielMenu_WINDOW_MANAGER::getSingleton()->setSugorokuItem(item_.itemID[0]);
        } else {
            TextAPI::setMACRO0(0x32, 0xf0000000, item_.itemID[0]);
            TownWindowSystem::getSingleton().openSystemMessage(item_.messageNo[0], 1);
            if (item_.messageNo[1] != 0) {
                TextAPI::setMACRO0(0x32, 0xf0000000, item_.itemID[1]);
                TownWindowSystem::getSingleton().addCommonMessage(item_.messageNo[1]);
            }
        }
        endFlag_ = true;
    }
}

int twn::SugorokuPanelActionTubo::nextState()
{
    if (endFlag_ == true) {
        return sugoroku::SYSTEM_OPEN_MENU;
    }
    return sugoroku::NOT_CHANGE_STATE;
}

void twn::SugorokuPanelActionTreasuerBox::setup()
{
    endFlag_ = false;
    yesnoFlag_ = true;
    openMenu_ = false;
    item_.index = 0;
    item_.itemID[0] = 0;
    item_.itemID[1] = 0;
    item_.messageNo[0] = 0;
    item_.messageNo[1] = 0;
    SugorokuPanelAction::openPanelActionMessage();
    gTownMenu_MESSAGE.setYesNo();
}

void twn::SugorokuPanelActionTreasuerBox::execute()
{
    int stat = menu::MenuBase::MENUBASE_STAT_ACTIVE;
    if (yesnoFlag_ == true) {
        stat = gTownMenu_MESSAGE.getStat();
    }
    if (stat == menu::MenuBase::MENUBASE_STAT_OK) {
        openMenu_ = SugorokuPanelAction::addTreasuerMessage(SugorokuPanelAction::TYPE_BOX, item_);
        yesnoFlag_ = false;
    }
    if (stat == menu::MenuBase::MENUBASE_STAT_CANCEL) {
        endFlag_ = true;
    }
    if (yesnoFlag_ != true && TownRiseupManager::getSingleton().isEnable(item_.index) == false) {
        if (openMenu_ == true) {
            window::gShopMenuControl.startMenu(0x22);
            MaterielMenu_WINDOW_MANAGER::getSingleton()->setSugorokuItem(item_.itemID[0]);
        } else {
            TextAPI::setMACRO0(0x32, 0xf0000000, item_.itemID[0]);
            TownWindowSystem::getSingleton().openSystemMessage(item_.messageNo[0], 1);
            if (item_.messageNo[1] != 0) {
                TextAPI::setMACRO0(0x32, 0xf0000000, item_.itemID[1]);
                TownWindowSystem::getSingleton().addCommonMessage(item_.messageNo[1]);
            }
        }
        endFlag_ = true;
    }
}

int twn::SugorokuPanelActionTreasuerBox::nextState()
{
    if (endFlag_ == true) {
        return sugoroku::SYSTEM_OPEN_MENU;
    }
    return sugoroku::NOT_CHANGE_STATE;
}

void twn::SugorokuPanelActionInn::setup()
{
}

int twn::SugorokuPanelActionInn::nextState()
{
    return sugoroku::SYSTEM_FADE_OUT_NEXT_SHOP;
}

void twn::SugorokuPanelActionShop::setup()
{
}

int twn::SugorokuPanelActionShop::nextState()
{
    return sugoroku::SYSTEM_FADE_OUT_NEXT_SHOP;
}

void twn::SugorokuPanelActionFlat::setup()
{
    endFlag_ = false;
    yesnoFlag_ = true;
    encountFlag_ = false;
    actionNo_ = -1;
    item_.index = 0;
    item_.itemID[0] = 0;
    item_.itemID[1] = 0;
    item_.messageNo[0] = 0;
    item_.messageNo[1] = 0;
    if (UnkDssRand::rand(16) == 0 && g_SugorokuInfo.randomEcountFlag_ == false) {
        SugorokuPanelAction::startSugorokuEncount(sugoroku::ENCOUNT_TYPE_FLAT);
        endFlag_ = true;
        encountFlag_ = true;
        return;
    }
    SugorokuPanelAction::openPanelActionMessage();
    gTownMenu_MESSAGE.setYesNo();
}

void twn::SugorokuPanelActionFlat::execute()
{
    if (endFlag_ == true || encountFlag_ == true) {
        return;
    }
    int stat = gTownMenu_MESSAGE.getStat();
    if (stat == menu::MenuBase::MENUBASE_STAT_OK) {
        if (yesnoFlag_ == false) {
            if (actionNo_ == 0 || actionNo_ == 1 || actionNo_ == 5) {
                endFlag_ = true;
                return;
            }
            if (TownRiseupManager::getSingleton().isEnable(item_.index) == false) {
                if (actionNo_ == 4) {
                    window::gShopMenuControl.startMenu(0x22);
                    MaterielMenu_WINDOW_MANAGER::getSingleton()->setSugorokuItem(item_.itemID[0]);
                } else {
                    TextAPI::setMACRO0(0x32, 0xf0000000, item_.itemID[0]);
                    TownWindowSystem::getSingleton().openSystemMessage(item_.messageNo[0], 1);
                    if (item_.messageNo[1] != 0) {
                        TextAPI::setMACRO0(0x32, 0xf0000000, item_.itemID[1]);
                        TownWindowSystem::getSingleton().addCommonMessage(item_.messageNo[1]);
                    }
                }
                endFlag_ = true;
            }
        } else {
            yesnoFlag_ = false;
            actionNo_ = SugorokuPanelAction::selectNormalPanelAction(item_);
        }
    } else if (stat == menu::MenuBase::MENUBASE_STAT_CANCEL) {
        endFlag_ = true;
    }
}

int twn::SugorokuPanelActionFlat::nextState()
{
    if (encountFlag_ == true) {
        return sugoroku::NOT_CHANGE_STATE;
    }
    if (endFlag_ == true) {
        if (actionNo_ == 4) {
            if (window::gShopMenuControl.isMenuEnd()) {
                return sugoroku::SYSTEM_OPEN_MENU;
            }
            return sugoroku::NOT_CHANGE_STATE;
        }
        if (actionNo_ == 0) {
            return sugoroku::SYSTEM_PANEL_LINK;
        }
        if (actionNo_ == 1) {
            SugorokuPanelAction::startSugorokuEncount(sugoroku::ENCOUNT_TYPE_FLAT);
            encountFlag_ = true;
            return sugoroku::NOT_CHANGE_STATE;
        }
        return sugoroku::SYSTEM_OPEN_MENU;
    }
    return sugoroku::NOT_CHANGE_STATE;
}

void twn::SugorokuPanelActionForest::setup()
{
    endFlag_ = false;
    yesnoFlag_ = true;
    encountFlag_ = false;
    actionNo_ = -1;
    item_.index = 0;
    item_.itemID[0] = 0;
    item_.itemID[1] = 0;
    item_.messageNo[0] = 0;
    item_.messageNo[1] = 0;
    if (UnkDssRand::rand(16) < 7 && g_SugorokuInfo.randomEcountFlag_ == false) {
        SugorokuPanelAction::startSugorokuEncount(sugoroku::ENCOUNT_TYPE_FOREST);
        endFlag_ = true;
        encountFlag_ = true;
        return;
    }
    SugorokuPanelAction::openPanelActionMessage();
    gTownMenu_MESSAGE.setYesNo();
}

void twn::SugorokuPanelActionForest::execute()
{
    if (endFlag_ == true || encountFlag_ == true) {
        return;
    }
    int stat = gTownMenu_MESSAGE.getStat();
    if (stat == menu::MenuBase::MENUBASE_STAT_OK) {
        if (yesnoFlag_ == false) {
            if (actionNo_ == 0 || actionNo_ == 1 || actionNo_ == 5) {
                endFlag_ = true;
                return;
            }
            if (TownRiseupManager::getSingleton().isEnable(item_.index) == false) {
                if (actionNo_ == 4) {
                    window::gShopMenuControl.startMenu(0x22);
                    MaterielMenu_WINDOW_MANAGER::getSingleton()->setSugorokuItem(item_.itemID[0]);
                } else {
                    TextAPI::setMACRO0(0x32, 0xf0000000, item_.itemID[0]);
                    TownWindowSystem::getSingleton().openSystemMessage(item_.messageNo[0], 1);
                    if (item_.messageNo[1] != 0) {
                        TextAPI::setMACRO0(0x32, 0xf0000000, item_.itemID[1]);
                        TownWindowSystem::getSingleton().addCommonMessage(item_.messageNo[1]);
                    }
                }
                endFlag_ = true;
            }
        } else {
            yesnoFlag_ = false;
            actionNo_ = SugorokuPanelAction::selectNormalPanelAction(item_);
        }
    } else if (stat == menu::MenuBase::MENUBASE_STAT_CANCEL) {
        endFlag_ = true;
    }
}

int twn::SugorokuPanelActionForest::nextState()
{
    if (encountFlag_ == true) {
        return sugoroku::NOT_CHANGE_STATE;
    }
    if (endFlag_ == true) {
        if (actionNo_ == 4) {
            if (window::gShopMenuControl.isMenuEnd()) {
                return sugoroku::SYSTEM_OPEN_MENU;
            }
            return sugoroku::NOT_CHANGE_STATE;
        }
        if (actionNo_ == 0) {
            return sugoroku::SYSTEM_PANEL_LINK;
        }
        if (actionNo_ == 1) {
            SugorokuPanelAction::startSugorokuEncount(sugoroku::ENCOUNT_TYPE_FOREST);
            encountFlag_ = true;
            return sugoroku::NOT_CHANGE_STATE;
        }
        return sugoroku::SYSTEM_OPEN_MENU;
    }
    return sugoroku::NOT_CHANGE_STATE;
}

void twn::SugorokuPanelActionMountain::setup()
{
    endFlag_ = false;
    yesnoFlag_ = true;
    encountFlag_ = false;
    actionNo_ = -1;
    item_.index = 0;
    item_.itemID[0] = 0;
    item_.itemID[1] = 0;
    item_.messageNo[0] = 0;
    item_.messageNo[1] = 0;
    if (UnkDssRand::rand(16) < 13 && g_SugorokuInfo.randomEcountFlag_ == false) {
        SugorokuPanelAction::startSugorokuEncount(sugoroku::ENCOUNT_TYPE_MOUNTAIN);
        endFlag_ = true;
        encountFlag_ = true;
        return;
    }
    SugorokuPanelAction::openPanelActionMessage();
    gTownMenu_MESSAGE.setYesNo();
}

void twn::SugorokuPanelActionMountain::execute()
{
    if (endFlag_ == true || encountFlag_ == true) {
        return;
    }
    int stat = gTownMenu_MESSAGE.getStat();
    if (stat == menu::MenuBase::MENUBASE_STAT_OK) {
        if (yesnoFlag_ == false) {
            if (actionNo_ == 0 || actionNo_ == 1 || actionNo_ == 5) {
                endFlag_ = true;
                return;
            }
            if (TownRiseupManager::getSingleton().isEnable(item_.index) == false) {
                if (actionNo_ == 4) {
                    window::gShopMenuControl.startMenu(0x22);
                    MaterielMenu_WINDOW_MANAGER::getSingleton()->setSugorokuItem(item_.itemID[0]);
                } else {
                    TextAPI::setMACRO0(0x32, 0xf0000000, item_.itemID[0]);
                    TownWindowSystem::getSingleton().openSystemMessage(item_.messageNo[0], 1);
                    if (item_.messageNo[1] != 0) {
                        TextAPI::setMACRO0(0x32, 0xf0000000, item_.itemID[1]);
                        TownWindowSystem::getSingleton().addCommonMessage(item_.messageNo[1]);
                    }
                }
                endFlag_ = true;
            }
        } else {
            yesnoFlag_ = false;
            actionNo_ = SugorokuPanelAction::selectNormalPanelAction(item_);
        }
    } else if (stat == menu::MenuBase::MENUBASE_STAT_CANCEL) {
        endFlag_ = true;
    }
}

int twn::SugorokuPanelActionMountain::nextState()
{
    if (encountFlag_ == true) {
        return sugoroku::NOT_CHANGE_STATE;
    }
    if (endFlag_ == true) {
        if (actionNo_ == 4) {
            if (window::gShopMenuControl.isMenuEnd()) {
                return sugoroku::SYSTEM_OPEN_MENU;
            }
            return sugoroku::NOT_CHANGE_STATE;
        }
        if (actionNo_ == 0) {
            return sugoroku::SYSTEM_PANEL_LINK;
        }
        if (actionNo_ == 1) {
            SugorokuPanelAction::startSugorokuEncount(sugoroku::ENCOUNT_TYPE_MOUNTAIN);
            encountFlag_ = true;
            return sugoroku::NOT_CHANGE_STATE;
        }
        return sugoroku::SYSTEM_OPEN_MENU;
    }
    return sugoroku::NOT_CHANGE_STATE;
}

void twn::SugorokuPanelActionKanbanUp::setup()
{
    endFlag_ = false;
    yesnoFlag_ = true;
    SugorokuPanelAction::openPanelActionMessage();
    gTownMenu_MESSAGE.setYesNo();
}

void twn::SugorokuPanelActionKanbanUp::execute()
{
    int stat = gTownMenu_MESSAGE.getStat();
    if (stat == menu::MenuBase::MENUBASE_STAT_OK) {
        if (yesnoFlag_ == false) {
            endFlag_ = true;
        } else {
            int mes = dq5::level::SugorokuSpecialMsg::getRecord(6)->msg1;
            TownWindowSystem::getSingleton().openSystemMessage(mes, 1);
            yesnoFlag_ = false;
        }
    }
    if (stat == menu::MenuBase::MENUBASE_STAT_CANCEL) {
        endFlag_ = true;
    }
}

int twn::SugorokuPanelActionKanbanUp::nextState()
{
    if (endFlag_ == true) {
        return sugoroku::SYSTEM_OPEN_MENU;
    }
    return sugoroku::NOT_CHANGE_STATE;
}

void twn::SugorokuPanelActionKanbanDown::setup()
{
    endFlag_ = false;
    yesnoFlag_ = true;
    SugorokuPanelAction::openPanelActionMessage();
    gTownMenu_MESSAGE.setYesNo();
}

void twn::SugorokuPanelActionKanbanDown::execute()
{
    int stat = gTownMenu_MESSAGE.getStat();
    if (stat == menu::MenuBase::MENUBASE_STAT_OK) {
        if (yesnoFlag_ == false) {
            endFlag_ = true;
        } else {
            int mes = dq5::level::SugorokuSpecialMsg::getRecord(6)->msg1;
            TownWindowSystem::getSingleton().openSystemMessage(mes, 1);
            yesnoFlag_ = false;
        }
    }
    if (stat == menu::MenuBase::MENUBASE_STAT_CANCEL) {
        endFlag_ = true;
    }
}

int twn::SugorokuPanelActionKanbanDown::nextState()
{
    if (endFlag_ == true) {
        return sugoroku::SYSTEM_OPEN_MENU;
    }
    return sugoroku::NOT_CHANGE_STATE;
}

void twn::SugorokuPanelActionKanbanLeft::setup()
{
    endFlag_ = false;
    yesnoFlag_ = true;
    SugorokuPanelAction::openPanelActionMessage();
    gTownMenu_MESSAGE.setYesNo();
}

void twn::SugorokuPanelActionKanbanLeft::execute()
{
    int stat = gTownMenu_MESSAGE.getStat();
    if (stat == menu::MenuBase::MENUBASE_STAT_OK) {
        if (yesnoFlag_ == false) {
            endFlag_ = true;
        } else {
            int mes = dq5::level::SugorokuSpecialMsg::getRecord(6)->msg1;
            TownWindowSystem::getSingleton().openSystemMessage(mes, 1);
            yesnoFlag_ = false;
        }
    }
    if (stat == menu::MenuBase::MENUBASE_STAT_CANCEL) {
        endFlag_ = true;
    }
}

int twn::SugorokuPanelActionKanbanLeft::nextState()
{
    if (endFlag_ == true) {
        return sugoroku::SYSTEM_OPEN_MENU;
    }
    return sugoroku::NOT_CHANGE_STATE;
}

void twn::SugorokuPanelActionKanbanRight::setup()
{
    endFlag_ = false;
    yesnoFlag_ = true;
    SugorokuPanelAction::openPanelActionMessage();
    gTownMenu_MESSAGE.setYesNo();
}

void twn::SugorokuPanelActionKanbanRight::execute()
{
    int stat = gTownMenu_MESSAGE.getStat();
    if (stat == menu::MenuBase::MENUBASE_STAT_OK) {
        if (yesnoFlag_ == false) {
            endFlag_ = true;
        } else {
            int mes = dq5::level::SugorokuSpecialMsg::getRecord(6)->msg1;
            TownWindowSystem::getSingleton().openSystemMessage(mes, 1);
            yesnoFlag_ = false;
        }
    }
    if (stat == menu::MenuBase::MENUBASE_STAT_CANCEL) {
        endFlag_ = true;
    }
}

int twn::SugorokuPanelActionKanbanRight::nextState()
{
    if (endFlag_ == true) {
        return sugoroku::SYSTEM_OPEN_MENU;
    }
    return sugoroku::NOT_CHANGE_STATE;
}

void twn::SugorokuPanelActionChangeGate::setup()
{
}

int twn::SugorokuPanelActionChangeGate::nextState()
{
    return sugoroku::SYSTEM_OPEN_MENU;
}

void twn::SugorokuPanelActionSugorokuDungeon::setup()
{
    endFlag_ = false;
    yesnoFlag_ = true;
    yes_ = false;
    if (TownSugorokuManager::getSingleton().getStageNo() <= 5) {
        SugorokuPanelAction::openPanelActionMessage();
        gTownMenu_MESSAGE.setYesNo();
    }
}

void twn::SugorokuPanelActionSugorokuDungeon::execute()
{
    if (TownSugorokuManager::getSingleton().getStageNo() <= 5) {
        int stat = gTownMenu_MESSAGE.getStat();
        if (stat == menu::MenuBase::MENUBASE_STAT_OK) {
            if (yesnoFlag_ == false) {
                endFlag_ = true;
                yes_ = true;
            } else {
                yesnoFlag_ = false;
            }
        }
        if (stat == menu::MenuBase::MENUBASE_STAT_CANCEL) {
            endFlag_ = true;
        }
    }
}

int twn::SugorokuPanelActionSugorokuDungeon::nextState()
{
    if (TownSugorokuManager::getSingleton().getStageNo() > 5) {
        SoundManager::playSe(0x131, 0);
        return sugoroku::SYSTEM_PANEL_LINK;
    }
    if (endFlag_ == true) {
        if (yes_ == true) {
            SoundManager::playSe(0x131, 0);
            return sugoroku::SYSTEM_PANEL_LINK;
        }
        return sugoroku::SYSTEM_OPEN_MENU;
    }
    return sugoroku::NOT_CHANGE_STATE;
}

void twn::SugorokuPanelActionTreasuerRoom::setup()
{
    endFlag_ = false;
    yesnoFlag_ = true;
    SugorokuPanelAction::openPanelActionMessage();
    gTownMenu_MESSAGE.setYesNo();
}

void twn::SugorokuPanelActionTreasuerRoom::execute()
{
    int stat = gTownMenu_MESSAGE.getStat();
    yes_ = false;
    if (stat == menu::MenuBase::MENUBASE_STAT_OK) {
        if (yesnoFlag_ == false) {
            endFlag_ = true;
            yes_ = true;
        } else {
            yesnoFlag_ = false;
        }
    }
    if (stat == menu::MenuBase::MENUBASE_STAT_CANCEL) {
        endFlag_ = true;
    }
}

int twn::SugorokuPanelActionTreasuerRoom::nextState()
{
    if (endFlag_ == true) {
        if (yes_ == true) {
            SoundManager::playSe(0x131, 0);
            return sugoroku::SYSTEM_PANEL_LINK;
        }
        return sugoroku::SYSTEM_OPEN_MENU;
    }
    return sugoroku::NOT_CHANGE_STATE;
}

void twn::SugorokuPanelActionHealPoint::setup()
{
    SugorokuPanelAction::openPanelActionMessage();
    status::g_Party.getPlayerStatus(0).getHaveStatusInfo().recovery();
}

int twn::SugorokuPanelActionHealPoint::nextState()
{
    return sugoroku::SYSTEM_OPEN_MENU;
}

void twn::SugorokuPanelActionSelectSpot::setup()
{
    TownWindowSystem::getSingleton().openSystemMessage(0xca6ad, 1);
    g_SugorokuInfo.diceControlFlag_ = true;
}

int twn::SugorokuPanelActionSelectSpot::nextState()
{
    return sugoroku::SYSTEM_OPEN_MENU;
}

void twn::SugorokuPanelAction::goldUp(int gold)
{
    int lastGold = 999999 - status::g_Party.getGold();
    int panelActionNo = g_SugorokuInfo.getNowPane()->getPanelID();
    int mes = dq5::level::SugorokuPanelList::getRecord(panelActionNo + 1)->execMsg;
    int addMes = 0;
    status::g_Party.addGold(gold);
    TextAPI::setMACRO0(0x32, 0xf0000000, gold);
    TownWindowSystem::getSingleton().openSystemMessage(mes, 1);
    if (lastGold == 0) {
        addMes = dq5::level::SugorokuChangeMsg::getRecord(0)->msg1;
    } else if (lastGold < gold) {
        TextAPI::setMACRO0(0x32, 0xf0000000, lastGold);
        addMes = dq5::level::SugorokuChangeMsg::getRecord(0)->msg2;
    }
    if (addMes != 0) {
        TownWindowSystem::getSingleton().addCommonMessage(addMes);
    }
}

bool twn::SugorokuPanelAction::goldDown(int gold)
{
    int panelActionNo = g_SugorokuInfo.getNowPane()->getPanelID();
    int mes = dq5::level::SugorokuPanelList::getRecord(panelActionNo + 1)->execMsg;
    int downGold = status::g_Party.getGold() - gold;
    if (downGold < 0) {
        downGold = 0;
    }
    status::g_Party.setGold(downGold);
    TextAPI::setMACRO0(0x64, 0xf0000000, gold);
    TownWindowSystem::getSingleton().openSystemMessage(mes, 1);
    return true;
}

void twn::SugorokuPanelAction::diceUp(int dice)
{
    int diceCount = g_SugorokuInfo.getDiceCount();
    diceCount += dice;
    if (diceCount > 999) {
        diceCount = 999;
    }
    g_SugorokuInfo.setDiceCount(diceCount);
    int panelActionNo = g_SugorokuInfo.getNowPane()->getPanelID();
    int mes = dq5::level::SugorokuPanelList::getRecord(panelActionNo + 1)->execMsg;
    TextAPI::setMACRO0(0x65, 0xf0000000, dice);
    TownWindowSystem::getSingleton().openSystemMessage(mes, 1);
}

void twn::SugorokuPanelAction::diceDown(int dice)
{
    int diceCount = g_SugorokuInfo.getDiceCount() - dice;
    if (diceCount < 0) {
        diceCount = 0;
    }
    g_SugorokuInfo.setDiceCount(diceCount);
    int panelActionNo = g_SugorokuInfo.getNowPane()->getPanelID();
    int mes = dq5::level::SugorokuPanelList::getRecord(panelActionNo + 1)->execMsg;
    TextAPI::setMACRO0(0x66, 0xf0000000, dice);
    TownWindowSystem::getSingleton().openSystemMessage(mes, 1);
}

void twn::SugorokuPanelAction::moveNext(char count)
{
    int panelActionNo = g_SugorokuInfo.getNowPane()->getPanelID();
    int mes = dq5::level::SugorokuPanelList::getRecord(panelActionNo + 1)->execMsg;
    g_SugorokuInfo.setNowMoveCount(count);
    TextAPI::setMACRO0(0x67, 0xf0000000, count);
    TownWindowSystem::getSingleton().openSystemMessage(mes, 1);
}

void twn::SugorokuPanelAction::moveBack(char count)
{
    int panelActionNo = g_SugorokuInfo.getNowPane()->getPanelID();
    int mes = dq5::level::SugorokuPanelList::getRecord(panelActionNo + 1)->execMsg;
    count = dss::abs(count);
    g_SugorokuInfo.setNowMoveCount(count);
    g_SugorokuInfo.setBack(true);
    TextAPI::setMACRO0(0x68, 0xf0000000, count);
    TownWindowSystem::getSingleton().openSystemMessage(mes, 1);
}

char twn::SugorokuPanelAction::isSelectChanceCard(int chanceNo)
{
    char chanceOK = false;
    dq5::level::SugorokuChanceCard* chance = dq5::level::SugorokuChanceCard::getRecord(chanceNo);
    switch (TownSugorokuManager::getSingleton().getStageNo()) {
    case 1:
        chanceOK = chance->getFloor1();
        break;
    case 2:
        chanceOK = chance->getFloor2();
        break;
    case 3:
        chanceOK = chance->getFloor3();
        break;
    case 4:
        chanceOK = chance->getFloor4();
        break;
    case 5:
        chanceOK = chance->getFloor5();
        break;
    case 6:
        chanceOK = chance->getFloor6();
        break;
    case 7:
        chanceOK = chance->getFloor7();
        break;
    case 8:
        chanceOK = chance->getFloor8();
        break;
    case 9:
        chanceOK = chance->getFloor9();
        break;
    case 10:
        chanceOK = chance->getFloor10();
        break;
    case 11:
        chanceOK = chance->getFloor11();
        break;
    case 12:
        chanceOK = chance->getFloor12();
        break;
    case 13:
        chanceOK = chance->getFloor13();
        break;
    case 14:
        chanceOK = chance->getFloor14();
        break;
    }
    return chanceOK;
}

void twn::SugorokuPanelAction::openPanelActionMessage()
{
    int panelActionNo = g_SugorokuInfo.getNowPane()->getPanelID();
    TownWindowSystem::getSingleton().openSystemMessage(dq5::level::SugorokuPanelList::getRecord(panelActionNo + 1)->execMsg, 1);
}

bool twn::SugorokuPanelAction::addTreasuerMessage(int type, RISEUP_ITEM& riseup)
{
    dq5::level::SugorokuSpecialMsg* treasuerMes = dq5::level::SugorokuSpecialMsg::getRecord(type);
    bool openMenuFlag = false;
    int riseupItem = 0;
    int uid = g_SugorokuInfo.getNowPane()->getUid();
    int index = TownFurnitureManager::getSingleton()->getFurnitureIndex(uid);
    dq5::level::FurnitureData* furnData = dq5::level::FurnitureData::getRecord(index);
    if (status::g_StageInfo.getFurnFlag(furnData->flagIndex) == false) {
        bool getItemFlag = false;
        int gold = furnData->gold;
        if (gold != 0) {
            getItemFlag = true;
            int lastGold = 999999 - status::g_Party.getGold();
            riseupItem = 1000;
            status::g_Party.addGold(gold);
            riseup.messageNo[0] = treasuerMes->msg2;
            if (lastGold == 0) {
                riseup.messageNo[1] = treasuerMes->msg3;
            } else if (lastGold < gold) {
                riseup.messageNo[1] = treasuerMes->msg4;
            }
            riseup.itemID[0] = gold;
            riseup.itemID[1] = lastGold;
            status::g_StageInfo.setFurnFlag(furnData->flagIndex);
        } else if (furnData->item != 0) {
            getItemFlag = true;
            riseupItem = riseup.itemID[0] = furnData->item;
            status::g_StageInfo.setFurnFlag(furnData->flagIndex);
            openMenuFlag = true;
        } else {
            riseup.messageNo[0] = treasuerMes->msg5;
        }
        if (getItemFlag == true) {
            dss::Fix32Vector3 pos = TownPlayerManager::getSingleton().getPosition();
            if (riseupItem == 0xd1) {
                riseup.index = TownRiseupManager::getSingleton().setupMedal(pos);
            } else {
                riseup.index = TownRiseupManager::getSingleton().setup(riseupItem, pos);
            }
        }
    } else {
        riseup.messageNo[0] = treasuerMes->msg5;
    }
    return openMenuFlag;
}

int twn::SugorokuPanelAction::selectNormalPanelAction(RISEUP_ITEM& riseup)
{
    int dataOffset = TownSugorokuManager::getSingleton().getStageOffset();
    dq5::level::SugorokuSpecialMsg* spMes = dq5::level::SugorokuSpecialMsg::getRecord(5);
    int messageNo = 0;
    unsigned char ary[6];
    for (int i = 0; i < 6; i++) {
        ary[i] = dq5::level::SugorokuData::getRecord(dataOffset + i)->ratio32 << 3;
    }
    int actionNo = dss::getRandArrayIndex(ary, 6);
    if (isSelectChanceCard(23) == false && actionNo == 0) {
        do {
            actionNo = dss::getRandArrayIndex(ary, 6);
        } while (actionNo == 0);
    }
    switch (actionNo) {
    case 0:
        messageNo = spMes->msg1;
        riseup.itemID[0] = -1;
        break;
    case 1:
        messageNo = spMes->msg3;
        riseup.itemID[0] = -1;
        break;
    case 2:
    case 3: {
        dq5::level::SugorokuData* data = dq5::level::SugorokuData::getRecord(dataOffset + actionNo);
        int lastGold = 999999 - status::g_Party.getGold();
        riseup.itemID[0] = data->getMoneyMin() + UnkDssRand::rand(data->getMoneyMax() - data->getMoneyMin());
        riseup.itemID[1] = lastGold;
        status::g_Party.addGold(riseup.itemID[0]);
        riseup.messageNo[0] = spMes->msg4;
        if (lastGold == 0) {
            riseup.messageNo[1] = spMes->msg5;
        } else if (lastGold < riseup.itemID[0]) {
            riseup.messageNo[1] = spMes->msg6;
        }
        dss::Fix32Vector3 pos = TownPlayerManager::getSingleton().getPosition();
        riseup.index = TownRiseupManager::getSingleton().setup(1000, pos);
        return actionNo;
    }
    case 4: {
        unsigned char itemCount = 0;
        do {
            if (dq5::level::SugorokuData::getRecord(dataOffset + itemCount)->item == 0) {
                break;
            }
            itemCount++;
            if (dataOffset + itemCount == dq5::level::SugorokuData::getArraySize()) {
                break;
            }
        } while (dq5::level::SugorokuData::getRecord(dataOffset + itemCount)->index == 0);
        unsigned char item[12] = {0};
        for (int i = 0; i < 12; i++) {
            item[i] = 0;
        }
        for (int i = 0; i < itemCount; i++) {
            item[i] = dq5::level::SugorokuData::getRecord(dataOffset + i)->ratio256;
        }
        int getItemNo = dss::getRandArrayIndex(item, itemCount);
        riseup.itemID[0] = dq5::level::SugorokuData::getRecord(dataOffset + getItemNo)->item;
        dss::Fix32Vector3 pos = TownPlayerManager::getSingleton().getPosition();
        if (riseup.itemID[0] == 0xd1) {
            riseup.index = TownRiseupManager::getSingleton().setupMedal(pos);
        } else {
            riseup.index = TownRiseupManager::getSingleton().setup(riseup.itemID[0], pos);
        }
        return actionNo;
    }
    case 5:
        messageNo = spMes->msg7;
        riseup.itemID[0] = -1;
        break;
    }
    TownWindowSystem::getSingleton().openSystemMessage(messageNo, 1);
    return actionNo;
}

void twn::SugorokuPanelAction::startSugorokuEncount(sugoroku::SUGOROKU_ENCOUNT_TYPE type)
{
    int level = status::g_Party.getPlayerStatus(0).getHaveStatusInfo().getHaveStatus().getLevel();
    int tileID, minLevel = 0, maxLevel = 0;
    switch (type) {
    case sugoroku::ENCOUNT_TYPE_NORMAL:
        minLevel = dss::clamp(7, level - 6, 45);
        maxLevel = dss::clamp(7, level - 3, 45);
        break;
    case sugoroku::ENCOUNT_TYPE_FLAT:
        minLevel = 1;
        maxLevel = 4;
        break;
    case sugoroku::ENCOUNT_TYPE_FOREST:
        minLevel = dss::clamp(4, level - 8, 15);
        maxLevel = dss::clamp(4, level - 5, 15);
        break;
    case sugoroku::ENCOUNT_TYPE_MOUNTAIN:
        minLevel = dss::clamp(5, level - 5, 25);
        maxLevel = dss::clamp(5, level - 3, 25);
        break;
    }
    if (type == sugoroku::ENCOUNT_TYPE_METAL) {
        tileID = 0x81;
    } else {
        tileID = btl::Encount::getSingleton()->getRandomTileID(minLevel, maxLevel);
    }
    status::g_StageAttribute.setEvBtlMapToBtlMap();
    btl::Encount::getSingleton()->forceEventBrew(tileID);
    g_SugorokuInfo.setContinue(TownSugorokuInfo::CONTINUE_BATTLE);
    g_SugorokuInfo.setNextMapPanelUid(g_SugorokuInfo.getNowPane()->getUid());
    btl::Encount::getSingleton()->setFriendMonster(false);
    btl::Encount::getSingleton()->setEventEncount(true);
}

int twn::SugorokuPanelAction::isMessageOpen(sugoroku::NEXT_ACTION nextAction)
{
    int next = sugoroku::SYSTEM_OPEN_MENU;
    if (nextAction == sugoroku::NEXT_ACTION_MOVE) {
        next = sugoroku::SYSTEM_MOVE;
    }
    if (TownWindowSystem::getSingleton().isMessageStart() == true) {
        next = sugoroku::NOT_CHANGE_STATE;
    }
    return next;
}
