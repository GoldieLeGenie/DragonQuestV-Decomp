#include "main/status/ItemData.hpp"

inline bool dss::UnkBitFlagUchar::check(unsigned char flag) const
{
    return (flag_ & flag) ? true : false;
}

inline void dss::UnkBitFlagUchar::set(unsigned char flag)
{
    flag_ |= flag;
}

inline void dss::UnkBitFlagUchar::remove(unsigned char flag)
{
    flag_ &= ~flag;
}

inline void dss::UnkBitFlagUchar::clear()
{
    flag_ = 0;
}


THUMB status::ItemData::ItemData()
{
    index_ = 0;
    count_ = 0;
    flag_.clear();
}

THUMB status::ItemData::~ItemData()
{
}

THUMB void status::ItemData::clear()
{
    index_ = 0;
    count_ = 0;
    flag_.clear();
}

THUMB void status::ItemData::setEquipment(bool flag)
{
    if (flag) {
        flag_.set(FLAG_EQUIP);
    } else {
        flag_.remove(FLAG_EQUIP);
    }
}

THUMB bool status::ItemData::isEquipment()
{
    return flag_.check(FLAG_EQUIP);
}

THUMB void status::ItemData::setSpell(bool flag)
{
    if (flag) {
        flag_.set(FLAG_SPELL);
    } else {
        flag_.remove(FLAG_SPELL);
    }
}

THUMB bool status::ItemData::isSpell()
{
    return flag_.check(FLAG_SPELL);
}
