#include "ov037/materielmenu/casino/FightStadiumManager.hpp"
#include "main/btl/Encount.hpp"
#include "main/dss/UnkRandom.hpp"
#include "main/leveldata/StadiumCard.hpp"
#include "main/menu/StadiumData.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/StageAttribute.hpp"
#include "main/text/TextAPI.hpp"

inline FightStadiumManager::FightStadiumManager()
{
}

inline unsigned char StadiumData::getBetArray()
{
    return monsterArray_;
}

inline bool FightStadiumManager::isManyName(int number)
{
    return orderNumber_[number] != -1;
}

inline unsigned int ExcelBinaryData::getRecordCount()
{
    return record_;
}

inline dq5::level::StadiumCard* dq5::level::StadiumCard::getRecord(int index)
{
    return (StadiumCard*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned char dq5::level::StadiumCard::getOdds4()
{
    return odds4;
}

inline unsigned char dq5::level::StadiumCard::getOdds1()
{
    return odds1;
}

inline unsigned char dq5::level::StadiumCard::getOdds2()
{
    return odds2;
}

inline unsigned char dq5::level::StadiumCard::getOdds3()
{
    return odds3;
}

inline void btl::EncountData::setTileLevel(int lv)
{
    tileLevel_ = lv;
}

inline void btl::Encount::setLevel(int lvl)
{
    encountData_.setTileLevel(lvl);
}

FightStadiumManager FightStadiumManager::m_singleton;

THUMB void FightStadiumManager::setup()
{
    for (int i = 0; i < 4; i++) {
        monster_[i] = 0;
        diameter_[i] = -1;
    }
    encount_ = 0;
    int listNum = UnkDssRand::rand(getCardCount()) + 1;
    encount_ = listNum + 189;
    monster_[0] = dq5::level::StadiumCard::getRecord(listNum)->monsterID1;
    monster_[1] = dq5::level::StadiumCard::getRecord(listNum)->monsterID2;
    monster_[2] = dq5::level::StadiumCard::getRecord(listNum)->monsterID3;
    monster_[3] = dq5::level::StadiumCard::getRecord(listNum)->monsterID4;
    diameter_[0] = dq5::level::StadiumCard::getRecord(listNum)->getOdds1() * 10 + UnkDssRand::rand(3);
    diameter_[1] = dq5::level::StadiumCard::getRecord(listNum)->getOdds2() * 10 + UnkDssRand::rand(3);
    diameter_[2] = dq5::level::StadiumCard::getRecord(listNum)->getOdds3() * 10 + UnkDssRand::rand(3);
    diameter_[3] = dq5::level::StadiumCard::getRecord(listNum)->getOdds4() * 10 + UnkDssRand::rand(3);
    cardCount_ = 0;
    while (cardCount_ < 4 && monster_[cardCount_] != 0) {
        cardCount_++;
    }
    for (int i = 0; i < 4; i++) {
        orderNumber_[i] = -1;
    }
    for (int i = 0; i < cardCount_; i++) {
        short howMany = 0;
        for (int count = 0; count < cardCount_; count++) {
            if (monster_[i] == monster_[count]) {
                howMany++;
                if (i > count) {
                    orderNumber_[i]++;
                }
            }
        }
        if (howMany > 1) {
            orderNumber_[i]++;
        }
    }
}

THUMB int FightStadiumManager::getCardCount()
{
    status::g_Party.setPlayerMode();
    int i;
    int maxLv = 0;
    for (i = 0; i < status::g_Party.getCount(); i++) {
        if (maxLv < status::g_Party.getPlayerStatus(i).haveStatusInfo_.haveStatus_.level_) {
            maxLv = status::g_Party.getPlayerStatus(i).haveStatusInfo_.haveStatus_.level_;
        }
    }
    unsigned int maxData = dq5::level::StadiumCard::binary_.getRecordCount();
    for (i = 1; i < maxData; i++) {
        if (maxLv < dq5::level::StadiumCard::getRecord(i)->level) {
            return i - 1;
        }
    }
    return maxData - 1;
}

THUMB int FightStadiumManager::getMonsterID(int number)
{
    return monster_[number];
}

THUMB int FightStadiumManager::getOrderCount(int number)
{
    return orderNumber_[number];
}

THUMB int FightStadiumManager::getDiameter(int number)
{
    return diameter_[number];
}

THUMB void FightStadiumManager::setBetOnMacro()
{
    int monsterNo = g_StadiumData.getBetArray();
    if (isManyName(monsterNo)) {
        int symbol = getOrderCount(monsterNo);
        TextAPI::setMACRO0(3, 0x60000000, getMonsterID(monsterNo), symbol);
    }
    else {
        TextAPI::setMACRO0(3, 0x60000000, getMonsterID(monsterNo));
    }
}

THUMB void FightStadiumManager::battleStart()
{
    status::g_StageAttribute.setBtlMapName("btlmd1");
    btl::Encount::getSingleton()->setLevel(99);
    g_StadiumData.result_ = 1;
    g_StadiumData.stadiumFlag_ = 1;
    btl::Encount::getSingleton()->forceEventBrew(encount_);
}
