#pragma ipa file
#include "ov028/sugoroku/TownSugorokuPanelChanceCard.hpp"
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
#include "main/leveldata/SugorokuSpecialMsg.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/StageAttribute.hpp"
#include "main/text/TextAPI.hpp"
#include "main/town/TownSugorokuInfo.hpp"
#include "main/window/ShopMenuControl.hpp"

#pragma thumb on

inline void twn::SugorokuPanelChanceCardUnlucky3::execute()
{
}

inline void twn::SugorokuPanelChanceCardUnlucky2::execute()
{
}

inline void twn::SugorokuPanelChanceCardUnlucky1::execute()
{
}

inline void twn::SugorokuPanelChanceCardLucky3::execute()
{
}

inline void twn::SugorokuPanelChanceCardLucky2::execute()
{
}

inline void twn::SugorokuPanelChanceCardLucky1::execute()
{
}

inline void twn::SugorokuPanelChanceCardTreasuerRoom::execute()
{
}

inline void twn::SugorokuPanelChanceCardDiceLimitDown::execute()
{
}

inline void twn::SugorokuPanelChanceCardMoveBack5::execute()
{
}

inline void twn::SugorokuPanelChanceCardMoveNext6::execute()
{
}

inline void twn::SugorokuPanelChanceCardSelectDice::execute()
{
}

inline void twn::SugorokuPanelChanceCardInn::execute()
{
}

inline void twn::SugorokuPanelChanceCardDiceCountUp::execute()
{
}

inline void twn::SugorokuPanelChanceCardHoleTrap::execute()
{
}

inline void twn::SugorokuPanelChanceCardNotEncount::execute()
{
}

inline void twn::SugorokuPanelChanceCardGoldUp100::execute()
{
}

inline void twn::SugorokuPanelChanceCardGoldDown100::execute()
{
}

inline void twn::SugorokuPanelChanceCardBackToStart::execute()
{
}

inline void twn::SugorokuPanelChanceCardLuckDown::execute()
{
}

inline void twn::SugorokuPanelChanceCardProtectionDown::execute()
{
}

inline void twn::SugorokuPanelChanceCardAgilityDown::execute()
{
}

inline void twn::SugorokuPanelChanceCardStrengthDown::execute()
{
}

inline void twn::SugorokuPanelChanceCardLuckUp2::execute()
{
}

inline void twn::SugorokuPanelChanceCardLuckUp1::execute()
{
}

inline void twn::SugorokuPanelChanceCardWisdomDown::execute()
{
}

inline void twn::SugorokuPanelChanceCardWisdomUp::execute()
{
}

inline void twn::SugorokuPanelChanceCardProtectionUp2::execute()
{
}

inline void twn::SugorokuPanelChanceCardProtectionUp1::execute()
{
}

inline void twn::SugorokuPanelChanceCardAgilityUp2::execute()
{
}

inline void twn::SugorokuPanelChanceCardAgilityUp1::execute()
{
}

inline void twn::SugorokuPanelChanceCardStrengthUp2::execute()
{
}

inline void twn::SugorokuPanelChanceCardStrengthUp1::execute()
{
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

inline dq5::level::SugorokuData* dq5::level::SugorokuData::getRecord(int index)
{
    return (SugorokuData*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned int dq5::level::SugorokuData::getArraySize()
{
    return binary_.record_;
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

inline void MaterielMenu_WINDOW_MANAGER::setSugorokuItem(short item)
{
    sugorokuItem_ = item;
}

inline unsigned short twn::PanelData::getUid()
{
    return uid_;
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

inline void btl::Encount::setFriendMonster(bool flag)
{
    encountData_.setTeamAddEnable(flag);
}

inline void btl::Encount::setEventEncount(bool flag)
{
    encountData_.setEventEncount(flag);
}

inline unsigned short status::HaveStatus::getStrength() const
{
    return baseStatus_.strength_;
}

inline unsigned short status::HaveStatus::getProtection() const
{
    return baseStatus_.protection_;
}

inline void twn::TownSugorokuInfo::setRandomEncountFlag(bool flag)
{
    randomEcountFlag_ = flag;
}

inline void twn::TownSugorokuInfo::setDiceControlFlag(bool flag)
{
    diceControlFlag_ = flag;
}

inline void twn::TownSugorokuInfo::setDiceLimit(bool flag)
{
    diceLimit_ = flag;
    if (flag == true) {
        diceLimitCount_ = 3;
    }
}

inline int btl::Encount::getEncountTileIdForPlayerLevel(int level)
{
    return encountData_.getEncountTileIdForPlayerLevel(level);
}

void twn::SugorokuPanelChanceCardStrengthUp1::setup()
{
    SugorokuPanelChanceCard::statusChange(0, 1, true);
}

int twn::SugorokuPanelChanceCardStrengthUp1::nextState()
{
    return sugoroku::SYSTEM_OPEN_MENU;
}

void twn::SugorokuPanelChanceCardStrengthUp2::setup()
{
    SugorokuPanelChanceCard::statusChange(0, 2, true);
}

int twn::SugorokuPanelChanceCardStrengthUp2::nextState()
{
    return sugoroku::SYSTEM_OPEN_MENU;
}

void twn::SugorokuPanelChanceCardAgilityUp1::setup()
{
    SugorokuPanelChanceCard::statusChange(1, 1, true);
}

int twn::SugorokuPanelChanceCardAgilityUp1::nextState()
{
    return sugoroku::SYSTEM_OPEN_MENU;
}

void twn::SugorokuPanelChanceCardAgilityUp2::setup()
{
    SugorokuPanelChanceCard::statusChange(1, 2, true);
}

int twn::SugorokuPanelChanceCardAgilityUp2::nextState()
{
    return sugoroku::SYSTEM_OPEN_MENU;
}

void twn::SugorokuPanelChanceCardProtectionUp1::setup()
{
    SugorokuPanelChanceCard::statusChange(2, 1, true);
}

int twn::SugorokuPanelChanceCardProtectionUp1::nextState()
{
    return sugoroku::SYSTEM_OPEN_MENU;
}

void twn::SugorokuPanelChanceCardProtectionUp2::setup()
{
    SugorokuPanelChanceCard::statusChange(2, 2, true);
}

int twn::SugorokuPanelChanceCardProtectionUp2::nextState()
{
    return sugoroku::SYSTEM_OPEN_MENU;
}

void twn::SugorokuPanelChanceCardWisdomUp::setup()
{
    SugorokuPanelChanceCard::statusChange(3, 1, true);
}

int twn::SugorokuPanelChanceCardWisdomUp::nextState()
{
    return sugoroku::SYSTEM_OPEN_MENU;
}

void twn::SugorokuPanelChanceCardWisdomDown::setup()
{
    SugorokuPanelChanceCard::statusChange(3, 1, false);
}

int twn::SugorokuPanelChanceCardWisdomDown::nextState()
{
    return sugoroku::SYSTEM_OPEN_MENU;
}

void twn::SugorokuPanelChanceCardLuckUp1::setup()
{
    SugorokuPanelChanceCard::statusChange(4, 1, true);
}

int twn::SugorokuPanelChanceCardLuckUp1::nextState()
{
    return sugoroku::SYSTEM_OPEN_MENU;
}

void twn::SugorokuPanelChanceCardLuckUp2::setup()
{
    SugorokuPanelChanceCard::statusChange(4, 2, true);
}

int twn::SugorokuPanelChanceCardLuckUp2::nextState()
{
    return sugoroku::SYSTEM_OPEN_MENU;
}

void twn::SugorokuPanelChanceCardStrengthDown::setup()
{
    SugorokuPanelChanceCard::statusChange(0, 1, false);
}

int twn::SugorokuPanelChanceCardStrengthDown::nextState()
{
    return sugoroku::SYSTEM_OPEN_MENU;
}

void twn::SugorokuPanelChanceCardAgilityDown::setup()
{
    SugorokuPanelChanceCard::statusChange(1, 1, false);
}

int twn::SugorokuPanelChanceCardAgilityDown::nextState()
{
    return sugoroku::SYSTEM_OPEN_MENU;
}

void twn::SugorokuPanelChanceCardProtectionDown::setup()
{
    SugorokuPanelChanceCard::statusChange(2, 1, false);
}

int twn::SugorokuPanelChanceCardProtectionDown::nextState()
{
    return sugoroku::SYSTEM_OPEN_MENU;
}

void twn::SugorokuPanelChanceCardLuckDown::setup()
{
    SugorokuPanelChanceCard::statusChange(4, 1, false);
}

int twn::SugorokuPanelChanceCardLuckDown::nextState()
{
    return sugoroku::SYSTEM_OPEN_MENU;
}

void twn::SugorokuPanelChanceCardBackToStart::setup()
{
    SugorokuPanelChanceCard::openMessage();
}

int twn::SugorokuPanelChanceCardBackToStart::nextState()
{
    return sugoroku::SYSTEM_PANEL_LINK;
}

void twn::SugorokuPanelChanceCardEncount1::setup()
{
    encountEnd_ = false;
    SugorokuPanelChanceCard::openMessage();
    tileID_ = SugorokuPanelChanceCard::getSugorokuEncountTileID(SugorokuPanelChanceCard::TYPE_BEAST);
}

void twn::SugorokuPanelChanceCardEncount1::execute()
{
    if (encountEnd_ != true) {
        encountEnd_ = SugorokuPanelChanceCard::sugorokuEncount(tileID_);
    }
}

int twn::SugorokuPanelChanceCardEncount1::nextState()
{
    return sugoroku::NOT_CHANGE_STATE;
}

void twn::SugorokuPanelChanceCardEncount2::setup()
{
    encountEnd_ = false;
    SugorokuPanelChanceCard::openMessage();
    tileID_ = SugorokuPanelChanceCard::getSugorokuEncountTileID(SugorokuPanelChanceCard::TYPE_SEA);
}

void twn::SugorokuPanelChanceCardEncount2::execute()
{
    if (encountEnd_ != true) {
        encountEnd_ = SugorokuPanelChanceCard::sugorokuEncount(tileID_);
    }
}

int twn::SugorokuPanelChanceCardEncount2::nextState()
{
    return sugoroku::NOT_CHANGE_STATE;
}

void twn::SugorokuPanelChanceCardEncount3::setup()
{
    encountEnd_ = false;
    SugorokuPanelChanceCard::openMessage();
    tileID_ = SugorokuPanelChanceCard::getSugorokuEncountTileID(SugorokuPanelChanceCard::TYPE_BIRD);
}

void twn::SugorokuPanelChanceCardEncount3::execute()
{
    if (encountEnd_ != true) {
        encountEnd_ = SugorokuPanelChanceCard::sugorokuEncount(tileID_);
    }
}

int twn::SugorokuPanelChanceCardEncount3::nextState()
{
    return sugoroku::NOT_CHANGE_STATE;
}

void twn::SugorokuPanelChanceCardEncount4::setup()
{
    encountEnd_ = false;
    SugorokuPanelChanceCard::openMessage();
    tileID_ = SugorokuPanelChanceCard::getSugorokuEncountTileID(SugorokuPanelChanceCard::TYPE_ZOMBIE);
}

void twn::SugorokuPanelChanceCardEncount4::execute()
{
    if (encountEnd_ != true) {
        encountEnd_ = SugorokuPanelChanceCard::sugorokuEncount(tileID_);
    }
}

int twn::SugorokuPanelChanceCardEncount4::nextState()
{
    return sugoroku::NOT_CHANGE_STATE;
}

void twn::SugorokuPanelChanceCardGoldDown100::setup()
{
    SugorokuPanelChanceCard::goldDown(100);
}

int twn::SugorokuPanelChanceCardGoldDown100::nextState()
{
    return sugoroku::SYSTEM_OPEN_MENU;
}

void twn::SugorokuPanelChanceCardGoldUp100::setup()
{
    SugorokuPanelChanceCard::goldUp(100);
}

int twn::SugorokuPanelChanceCardGoldUp100::nextState()
{
    return sugoroku::SYSTEM_OPEN_MENU;
}

void twn::SugorokuPanelChanceCardNotEncount::setup()
{
    SugorokuPanelChanceCard::openMessage();
    g_SugorokuInfo.setRandomEncountFlag(true);
}

int twn::SugorokuPanelChanceCardNotEncount::nextState()
{
    return sugoroku::SYSTEM_OPEN_MENU;
}

void twn::SugorokuPanelChanceCardHoleTrap::setup()
{
    SugorokuPanelChanceCard::openMessage();
    TownWindowSystem::getSingleton().addCommonMessage(0xca670);
}

int twn::SugorokuPanelChanceCardHoleTrap::nextState()
{
    return sugoroku::SYSTEM_PANEL_LINK;
}

void twn::SugorokuPanelChanceCardChanceParameter::setup()
{
    endFlag_ = false;
    mode_ = DICE_START;
    chanceParam_ = UnkDssRand::rand(6) + 1;
    updownParam_ = 0;
    int chanceNo = g_SugorokuInfo.getChanceCardID();
    TownWindowSystem::getSingleton().openSystemMessage(dq5::level::SugorokuChanceCard::getRecord(chanceNo)->exec, 1);
}

void twn::SugorokuPanelChanceCardChanceParameter::execute()
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
            int chanceNo = g_SugorokuInfo.getChanceCardID();
            int mes = dq5::level::SugorokuChanceCard::getRecord(chanceNo)->exec;
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
                if (SugorokuPanelChanceCard::isStatusLimit(chanceParam_, true) == true) {
                    TownWindowSystem::getSingleton().addCommonMessage(dq5::level::SugorokuChangeMsg::getRecord(2)->msg1);
                }
            } else {
                if (SugorokuPanelChanceCard::isStatusLimit(chanceParam_, false) == true) {
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

int twn::SugorokuPanelChanceCardChanceParameter::nextState()
{
    if (endFlag_ == true) {
        return sugoroku::SYSTEM_OPEN_MENU;
    }
    return sugoroku::NOT_CHANGE_STATE;
}

void twn::SugorokuPanelChanceCardChanceParameter::changeParam()
{
    status::HaveStatus& status = status::g_Party.getPlayerStatus(0).getHaveStatusInfo().getHaveStatus();
    char value = 1;
    if (updownParam_ % 2 != 0) {
        if (SugorokuPanelChanceCard::isStatusLimit(chanceParam_, false) == true) {
            return;
        }
        value *= -1;
    } else {
        if (SugorokuPanelChanceCard::isStatusLimit(chanceParam_, true) == true) {
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

void twn::SugorokuPanelChanceCardTreasuerBox::setup()
{
    endFlag_ = false;
    yesnoFlag_ = true;
    getItem_ = 0;
    riseUpIndex_ = 0;
    SugorokuPanelChanceCard::openMessage();
    gTownMenu_MESSAGE.setYesNo();
}

void twn::SugorokuPanelChanceCardTreasuerBox::execute()
{
    int stat = gTownMenu_MESSAGE.getStat();
    if (stat == menu::MenuBase::MENUBASE_STAT_OK) {
        if (yesnoFlag_ == false) {
            if (TownRiseupManager::getSingleton().isEnable(riseUpIndex_) == false) {
                window::gShopMenuControl.startMenu(0x22);
                MaterielMenu_WINDOW_MANAGER::getSingleton()->setSugorokuItem(getItem_);
                endFlag_ = true;
            }
        } else {
            unsigned char itemCount = 0;
            int dataOffset = TownSugorokuManager::getSingleton().getStageOffset();
            do {
                if (dq5::level::SugorokuData::getRecord(dataOffset + itemCount)->item == 0) {
                    break;
                }
                itemCount++;
                if (dataOffset + itemCount == dq5::level::SugorokuData::getArraySize()) {
                    break;
                }
            } while (dq5::level::SugorokuData::getRecord(dataOffset + itemCount)->index == 0);
            unsigned char item[12];
            for (int i = 0; i < itemCount; i++) {
                item[i] = dq5::level::SugorokuData::getRecord(dataOffset + i)->ratio256;
            }
            int getItemNo = dss::getRandArrayIndex(item, itemCount);
            getItem_ = dq5::level::SugorokuData::getRecord(dataOffset + getItemNo)->item;
            dss::Fix32Vector3 pos = TownPlayerManager::getSingleton().getPosition();
            if (getItem_ == 0xd1) {
                riseUpIndex_ = TownRiseupManager::getSingleton().setupMedal(pos);
            } else {
                riseUpIndex_ = TownRiseupManager::getSingleton().setup(getItem_, pos);
            }
            yesnoFlag_ = false;
        }
    }
    if (stat == menu::MenuBase::MENUBASE_STAT_CANCEL) {
        endFlag_ = true;
    }
}

int twn::SugorokuPanelChanceCardTreasuerBox::nextState()
{
    if (endFlag_ == true) {
        return sugoroku::SYSTEM_OPEN_MENU;
    }
    return sugoroku::NOT_CHANGE_STATE;
}

void twn::SugorokuPanelChanceCardDiceCountUp::setup()
{
    SugorokuPanelChanceCard::openMessage();
    int diceCount = g_SugorokuInfo.getDiceCount();
    g_SugorokuInfo.setDiceCount(diceCount + 10);
}

int twn::SugorokuPanelChanceCardDiceCountUp::nextState()
{
    return sugoroku::SYSTEM_OPEN_MENU;
}

void twn::SugorokuPanelChanceCardInn::setup()
{
    SugorokuPanelChanceCard::openMessage();
}

int twn::SugorokuPanelChanceCardInn::nextState()
{
    return sugoroku::SYSTEM_PANEL_LINK;
}

void twn::SugorokuPanelChanceCardSelectDice::setup()
{
    SugorokuPanelChanceCard::openMessage();
    g_SugorokuInfo.setDiceControlFlag(true);
}

int twn::SugorokuPanelChanceCardSelectDice::nextState()
{
    return sugoroku::SYSTEM_OPEN_MENU;
}

void twn::SugorokuPanelChanceCardMoveNext6::setup()
{
    g_SugorokuInfo.setNowMoveCount(6);
    SugorokuPanelChanceCard::openMessage();
}

int twn::SugorokuPanelChanceCardMoveNext6::nextState()
{
    return sugoroku::SYSTEM_MOVE;
}

void twn::SugorokuPanelChanceCardMoveBack5::setup()
{
    g_SugorokuInfo.setBack(true);
    g_SugorokuInfo.setNowMoveCount(5);
    SugorokuPanelChanceCard::openMessage();
}

int twn::SugorokuPanelChanceCardMoveBack5::nextState()
{
    return sugoroku::SYSTEM_MOVE;
}

void twn::SugorokuPanelChanceCardDiceLimitDown::setup()
{
    SugorokuPanelChanceCard::openMessage();
    g_SugorokuInfo.setDiceLimit(true);
}

int twn::SugorokuPanelChanceCardDiceLimitDown::nextState()
{
    return sugoroku::SYSTEM_OPEN_MENU;
}

void twn::SugorokuPanelChanceCardTreasuerRoom::setup()
{
    SugorokuPanelChanceCard::openMessage();
}

int twn::SugorokuPanelChanceCardTreasuerRoom::nextState()
{
    return sugoroku::SYSTEM_PANEL_LINK;
}

void twn::SugorokuPanelChanceCardLucky1::setup()
{
    SugorokuPanelChanceCard::goldUp(10);
}

int twn::SugorokuPanelChanceCardLucky1::nextState()
{
    return sugoroku::SYSTEM_OPEN_MENU;
}

void twn::SugorokuPanelChanceCardLucky2::setup()
{
    SugorokuPanelChanceCard::goldUp(20);
}

int twn::SugorokuPanelChanceCardLucky2::nextState()
{
    return sugoroku::SYSTEM_OPEN_MENU;
}

void twn::SugorokuPanelChanceCardLucky3::setup()
{
    SugorokuPanelChanceCard::goldUp(30);
}

int twn::SugorokuPanelChanceCardLucky3::nextState()
{
    return sugoroku::SYSTEM_OPEN_MENU;
}

void twn::SugorokuPanelChanceCardUnlucky1::setup()
{
    SugorokuPanelChanceCard::goldDown(10);
}

int twn::SugorokuPanelChanceCardUnlucky1::nextState()
{
    return sugoroku::SYSTEM_OPEN_MENU;
}

void twn::SugorokuPanelChanceCardUnlucky2::setup()
{
    SugorokuPanelChanceCard::goldDown(20);
}

int twn::SugorokuPanelChanceCardUnlucky2::nextState()
{
    return sugoroku::SYSTEM_OPEN_MENU;
}

void twn::SugorokuPanelChanceCardUnlucky3::setup()
{
    SugorokuPanelChanceCard::goldDown(30);
}

int twn::SugorokuPanelChanceCardUnlucky3::nextState()
{
    return sugoroku::SYSTEM_OPEN_MENU;
}

void twn::SugorokuPanelChanceCard::openMessage()
{
    int chanceNo = g_SugorokuInfo.getChanceCardID();
    unsigned long mes = dq5::level::SugorokuChanceCard::getRecord(chanceNo)->exec;
    TownWindowSystem::getSingleton().openSystemMessage();
    TownWindowSystem::getSingleton().serialCommonMessage(mes);
}

void twn::SugorokuPanelChanceCard::statusChange(int paramIndex, char value, bool statusUpFlag)
{
    unsigned long mes;
    openMessage();
    if (isStatusLimit(paramIndex, statusUpFlag) == true) {
        if (statusUpFlag == true) {
            mes = dq5::level::SugorokuChangeMsg::getRecord(2)->msg1;
        } else {
            mes = dq5::level::SugorokuChangeMsg::getRecord(3)->msg1;
        }
    } else {
        status::HaveStatus& haveStatus = status::g_Party.getPlayerStatus(0).getHaveStatusInfo().getHaveStatus();
        int lastValue = 0;
        if (statusUpFlag == false) {
            value *= -1;
        }
        switch (paramIndex) {
        case 0:
            lastValue = 255 - haveStatus.getStrength();
            haveStatus.addStrength(value);
            break;
        case 1:
            lastValue = 255 - haveStatus.getAgility();
            haveStatus.addAgility(value);
            break;
        case 2:
            lastValue = 255 - haveStatus.getProtection();
            haveStatus.addProtection(value);
            break;
        case 3:
            lastValue = 255 - haveStatus.getWisdom();
            haveStatus.addWisdom(value);
            break;
        case 4:
            lastValue = 255 - haveStatus.getLuck();
            haveStatus.addLuck(value);
            break;
        }
        if (statusUpFlag == true) {
            if (value == 2) {
                if (lastValue == 1) {
                    mes = 0xca6a7;
                } else {
                    mes = 0xca6a9;
                }
            } else {
                mes = 0xca6a7;
            }
        } else {
            mes = 0xca6ab;
        }
    }
    setParameterMacro(paramIndex);
    TownWindowSystem::getSingleton().addCommonMessage(mes);
}

bool twn::SugorokuPanelChanceCard::isStatusLimit(int paramIndex, bool statusUpFlag)
{
    status::HaveStatusInfo& statusInfo = status::g_Party.getPlayerStatus(0).getHaveStatusInfo();
    int noEquip = 1;
    bool limit = false;
    if (statusUpFlag == true) {
        switch (paramIndex) {
        case 0:
            if (statusInfo.getStrength(noEquip) == 255) {
                limit = true;
            }
            break;
        case 1:
            if (statusInfo.getAgility(noEquip) == 255) {
                limit = true;
            }
            break;
        case 2:
            if (statusInfo.getProtection(noEquip) == 255) {
                limit = true;
            }
            break;
        case 3:
            if (statusInfo.getWisdom(noEquip) == 255) {
                limit = true;
            }
            break;
        case 4:
            if (statusInfo.getLuck(noEquip) == 255) {
                limit = true;
            }
            break;
        case 5:
            if (statusInfo.getHpMax() == 999) {
                limit = true;
            }
            break;
        }
    } else {
        switch (paramIndex) {
        case 0:
            if (statusInfo.getStrength(noEquip) == 0) {
                limit = true;
            }
            break;
        case 1:
            if (statusInfo.getAgility(noEquip) == 0) {
                limit = true;
            }
            break;
        case 2:
            if (statusInfo.getProtection(noEquip) == 0) {
                limit = true;
            }
            break;
        case 3:
            if (statusInfo.getWisdom(noEquip) == 0) {
                limit = true;
            }
            break;
        case 4:
            if (statusInfo.getLuck(noEquip) == 0) {
                limit = true;
            }
            break;
        case 5:
            if (statusInfo.getHpMax() == 1) {
                limit = true;
            }
            break;
        }
    }
    return limit;
}

int twn::SugorokuPanelChanceCard::getSugorokuEncountTileID(ENCOUNT_TYPE type)
{
    int count = 0;
    int dataOffset = TownSugorokuManager::getSingleton().getStageOffset();
    bool endFlag = false;
    int tileNo[12];
    for (int i = 0; i < 12; i++) {
        tileNo[i] = 0;
    }
    do {
        switch (type) {
        case TYPE_BEAST:
            if (dq5::level::SugorokuData::getRecord(dataOffset + count)->encount1 != 0) {
                tileNo[count] = dq5::level::SugorokuData::getRecord(dataOffset + count)->encount1;
                count++;
            } else {
                endFlag = true;
            }
            break;
        case TYPE_SEA:
            if (dq5::level::SugorokuData::getRecord(dataOffset + count)->encount2 != 0) {
                tileNo[count] = dq5::level::SugorokuData::getRecord(dataOffset + count)->encount2;
                count++;
            } else {
                endFlag = true;
            }
            break;
        case TYPE_BIRD:
            if (dq5::level::SugorokuData::getRecord(dataOffset + count)->encount3 != 0) {
                tileNo[count] = dq5::level::SugorokuData::getRecord(dataOffset + count)->encount3;
                count++;
            } else {
                endFlag = true;
            }
            break;
        case TYPE_ZOMBIE:
            if (dq5::level::SugorokuData::getRecord(dataOffset + count)->encount4 != 0) {
                tileNo[count] = dq5::level::SugorokuData::getRecord(dataOffset + count)->encount4;
                count++;
            } else {
                endFlag = true;
            }
            break;
        }
        if (endFlag == true) {
            break;
        }
    } while (dq5::level::SugorokuData::getRecord(dataOffset + count)->index == 0);
    int tileID;
    if (count == 0) {
        int level = status::g_Party.getPlayerStatus(0).getHaveStatusInfo().getHaveStatus().getLevel();
        tileID = btl::Encount::getSingleton()->getEncountTileIdForPlayerLevel(level);
    } else {
        tileID = tileNo[UnkDssRand::rand(count)];
    }
    return tileID;
}

bool twn::SugorokuPanelChanceCard::sugorokuEncount(int tileID)
{
    if (TownWindowSystem::getSingleton().isMessageStart() == true) {
        return false;
    }
    status::g_StageAttribute.setEvBtlMapToBtlMap();
    btl::Encount::getSingleton()->forceEventBrew(tileID);
    g_SugorokuInfo.setContinue(TownSugorokuInfo::CONTINUE_BATTLE);
    g_SugorokuInfo.setNextMapPanelUid(g_SugorokuInfo.getNowPane()->getUid());
    btl::Encount::getSingleton()->setFriendMonster(false);
    btl::Encount::getSingleton()->setEventEncount(true);
    return true;
}

void twn::SugorokuPanelChanceCard::goldUp(int gold)
{
    int lastGold = 999999 - status::g_Party.getGold();
    int addMes = 0;
    status::g_Party.addGold(gold);
    TextAPI::setMACRO0(0x32, 0xf0000000, gold);
    TextAPI::setMACRO0(0x6a, 0xf0000000, gold);
    openMessage();
    if (lastGold == 0) {
        addMes = dq5::level::SugorokuChangeMsg::getRecord(0)->msg1;
    } else if (lastGold < gold) {
        addMes = dq5::level::SugorokuChangeMsg::getRecord(0)->msg2;
    }
    if (addMes != 0) {
        TextAPI::setMACRO0(0x32, 0xf0000000, lastGold);
        TextAPI::setMACRO0(0x6a, 0xf0000000, lastGold);
        TownWindowSystem::getSingleton().addCommonMessage(addMes);
    }
}

bool twn::SugorokuPanelChanceCard::goldDown(int gold)
{
    int downGold = status::g_Party.getGold() - gold;
    if (downGold < 0) {
        downGold = 0;
    }
    status::g_Party.setGold(downGold);
    TextAPI::setMACRO0(0x64, 0xf0000000, gold);
    openMessage();
    return true;
}

void twn::SugorokuPanelChanceCard::setParameterMacro(int paramIndex)
{
    switch (paramIndex) {
    case 0:
        TextAPI::setMACRO0(0x17, 0xe0000000, 0x11c);
        break;
    case 1:
        TextAPI::setMACRO0(0x17, 0xe0000000, 0xd9);
        break;
    case 2:
        TextAPI::setMACRO0(0x17, 0xe0000000, 0x11e);
        break;
    case 3:
        TextAPI::setMACRO0(0x17, 0xe0000000, 0xda);
        break;
    case 4:
        TextAPI::setMACRO0(0x17, 0xe0000000, 0xdb);
        break;
    case 5:
        TextAPI::setMACRO0(0x17, 0xe0000000, 0x3dd);
        break;
    }
}
