#include "main/status/BasePartyStatus.hpp"
#include "main/status/StageAttribute.hpp"
#include "main/status/UseActionFlag.hpp"
#include "main/dss/DssUtils.hpp"

// the unsigned long instances of the dss header templates are in this file
namespace dss {
    template <> unsigned long max<unsigned long>(unsigned long a, unsigned long b);
    template <> unsigned long min<unsigned long>(unsigned long a, unsigned long b);
}

inline bool status::UseActionFlag::isDouble() { return doubleFlag_; }

THUMB status::BasePartyStatus::BasePartyStatus() : bashaEnable_(1), fukuro_(0), carriage_(0)
{
}

THUMB bool status::BasePartyStatus::isCarriageEnter()
{
    if (carriage_ && g_StageAttribute.isCarriageEnable() && g_StageAttribute.isCarriageEnter()) {
        return true;
    }
    return false;
}

THUMB bool status::BasePartyStatus::isCarriageEnableOnGame()
{
    if (carriage_ && g_StageAttribute.isCarriageEnable() && isCarriageEnter()) {
        return true;
    }
    return false;
}

THUMB void status::BasePartyStatus::setGold(unsigned int gold)
{
    gold_ = gold;
    gold_ = dss::clamp<unsigned long>(gold, 0, 999999);
}

template <> THUMB unsigned long dss::clamp<unsigned long>(unsigned long a, unsigned long b, unsigned long c)
{
    return min(max(a, b), c);
}

template <> THUMB unsigned long dss::max<unsigned long>(unsigned long a, unsigned long b)
{
    return (a > b) ? a : b;
}

template <> THUMB unsigned long dss::min<unsigned long>(unsigned long a, unsigned long b)
{
    return (a < b) ? a : b;
}

THUMB void status::BasePartyStatus::addGold(int gold)
{
    gold_ += gold;
    gold_ = dss::clamp<unsigned long>(gold_, 0, 999999);
}

THUMB void status::BasePartyStatus::setBankMoney(unsigned int money)
{
    bankMoney_ = money;
    bankMoney_ = dss::clamp<unsigned long>(money, 0, 99999000);
}

THUMB void status::BasePartyStatus::setCasinoCoin(unsigned int coin)
{
    casinoCoin_ = coin;
    casinoCoin_ = dss::clamp<unsigned long>(coin, 0, 9999999);
}

THUMB void status::BasePartyStatus::setMedalCoin(unsigned int coin)
{
    medalCoin_ = coin;
    medalCoin_ = dss::clamp<unsigned long>(coin, 0, 999);
}

THUMB void status::BasePartyStatus::addMedalCoin(int coin)
{
    medalCoin_ += coin;
    medalCoin_ = dss::clamp<unsigned long>(medalCoin_, 0, 999);
}

THUMB int status::BasePartyStatus::getBattleExp()
{
    return battleExp_;
}

THUMB int status::BasePartyStatus::getBattleGold()
{
    return battleGold_;
}

THUMB void status::BasePartyStatus::reflectBattleGold()
{
    if (UseActionFlag::isDouble()) {
        battleGold_ *= 2;
    }
    addGold(battleGold_);
}
