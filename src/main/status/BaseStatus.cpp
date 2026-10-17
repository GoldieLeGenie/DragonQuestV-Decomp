#include "main/status/BaseStatus.hpp"
#include "main/dss/DssUtils.hpp"

namespace dss {
    template <> unsigned int max<unsigned int>(unsigned int a, unsigned int b);
    template <> unsigned int min<unsigned int>(unsigned int a, unsigned int b);
    template <> unsigned short max<unsigned short>(unsigned short a, unsigned short b);
    template <> unsigned short min<unsigned short>(unsigned short a, unsigned short b);
}

THUMB status::BaseStatus::BaseStatus()
{
    exp_ = 0;
    strength_ = 0;
    protection_ = 0;
    hp_ = 0;
    hpMax_ = 0;
    mp_ = 0;
    mpMax_ = 0;
    agility_ = 0;
    wisdom_ = 0;
    luck_ = 0;
}

THUMB status::BaseStatus::~BaseStatus()
{
}

THUMB void status::BaseStatus::clear()
{
    exp_ = 0;
    strength_ = 0;
    agility_ = 0;
    protection_ = 0;
    wisdom_ = 0;
    hp_ = 0;
    hpMax_ = 0;
    mp_ = 0;
    mpMax_ = 0;
    luck_ = 0;
}

THUMB void status::BaseStatus::setStrength(unsigned char str)
{
    strength_ = dss::clamp<unsigned int>(str, 0, 0xff);
}

template <> THUMB unsigned int dss::clamp<unsigned int>(unsigned int a, unsigned int b, unsigned int c)
{
    return min(max(a, b), c);
}

template <> THUMB unsigned int dss::max<unsigned int>(unsigned int a, unsigned int b)
{
    return (a > b) ? a : b;
}

template <> THUMB unsigned int dss::min<unsigned int>(unsigned int a, unsigned int b)
{
    return (a < b) ? a : b;
}

THUMB void status::BaseStatus::addStrength(char str)
{
    int strength = strength_ + str;
    strength_ = (unsigned char)dss::clamp<int>(strength, 0, 0xff);
}

THUMB void status::BaseStatus::setAgility(unsigned char agi)
{
    agility_ = dss::clamp<unsigned int>(agi, 0, 0xff);
}

THUMB void status::BaseStatus::addAgility(char agi)
{
    int agility = agility_ + agi;
    agility_ = dss::clamp<int>(agility, 0, 0xff);
}

THUMB void status::BaseStatus::setProtection(unsigned char pr)
{
    protection_ = dss::clamp<unsigned int>(pr, 0, 0xff);
}

THUMB void status::BaseStatus::addProtection(char pr)
{
    int protection = protection_ + pr;
    protection_ = (unsigned char)dss::clamp<int>(protection, 0, 0xff);
}

THUMB void status::BaseStatus::setWisdom(unsigned char wis)
{
    wisdom_ = dss::clamp<unsigned int>(wis, 0, 0xff);
}

THUMB void status::BaseStatus::addWisdom(char wis)
{
    int wisdom = wisdom_ + wis;
    wisdom_ = dss::clamp<int>(wisdom, 0, 0xff);
}

THUMB void status::BaseStatus::setLuck(unsigned char lc)
{
    luck_ = dss::clamp<unsigned int>(lc, 0, 0xff);
}

THUMB void status::BaseStatus::setHp(unsigned short hp)
{
    hp_ = dss::clamp<unsigned short>(hp, 0, 9999);
}

template <> THUMB unsigned short dss::clamp<unsigned short>(unsigned short a, unsigned short b, unsigned short c)
{
    return min(max(a, b), c);
}

template <> THUMB unsigned short dss::max<unsigned short>(unsigned short a, unsigned short b)
{
    return (a > b) ? a : b;
}

template <> THUMB unsigned short dss::min<unsigned short>(unsigned short a, unsigned short b)
{
    return (a < b) ? a : b;
}

THUMB void status::BaseStatus::setHpMax(unsigned short hp)
{
    hpMax_ = dss::clamp<unsigned short>(hp, 0, 9999);
}

THUMB void status::BaseStatus::addHpMax(char hp)
{
    hpMax_ = hpMax_ + (unsigned short)hp;
    hpMax_ = dss::clamp<unsigned short>(hpMax_, 0, 9999);
}

THUMB void status::BaseStatus::setMp(unsigned short mp)
{
    mp_ = dss::clamp<unsigned short>(mp, 0, 999);
}

THUMB void status::BaseStatus::setMpMax(unsigned short mp)
{
    mpMax_ = dss::clamp<unsigned short>(mp, 0, 999);
}

THUMB void status::BaseStatus::addMpMax(char mp)
{
    mpMax_ = mpMax_ + (unsigned short)mp;
    mpMax_ = dss::clamp<unsigned short>(mpMax_, 0, 999);
}
