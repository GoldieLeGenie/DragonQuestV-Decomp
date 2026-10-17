#include "main/status/StoryStatus.hpp"
#include "main/status/HaveStatus.hpp"
#include "main/status/ShopList.hpp"

inline void status::ShopList::setSection(int section)
{
    section_ = section;
}

inline void status::HaveStatus::setSeinenki(bool flag) { seinenki_ = flag; }

status::StoryStatus status::g_Story;

THUMB status::StoryStatus::StoryStatus()
{
    chapter_ = dq5::CHAPTER_DEBUG;
    flag_.clear();
}

THUMB status::StoryStatus::~StoryStatus()
{
}

THUMB void status::StoryStatus::initialize()
{
    setChapter(dq5::CHAPTER_DEBUG);
    for (int i = 0; i < 3; i++) {
        clearFriendMonster_[i] = -1;
    }
    for (int i = 0; i < 9; i++) {
        heroEquip_[i] = 0;
    }
}

THUMB void status::StoryStatus::setJisan(bool flag)
{
    if (flag) {
        flag_.flag_ |= FLAG_JISAN;
    }
    else {
        flag_.flag_ &= ~FLAG_JISAN;
    }
}

THUMB bool status::StoryStatus::isJisan()
{
    return flag_.check(FLAG_JISAN);
}

THUMB void status::StoryStatus::setUseBank(bool flag)
{
    if (flag) {
        flag_.flag_ |= FLAG_USE_BANK;
    }
    else {
        flag_.flag_ &= ~FLAG_USE_BANK;
    }
}

THUMB bool status::StoryStatus::isUseBank()
{
    return flag_.check(FLAG_USE_BANK);
}

THUMB void status::StoryStatus::setJisanSack(bool flag)
{
    if (flag) {
        flag_.flag_ |= FLAG_JISAN_SACK;
    }
    else {
        flag_.flag_ &= ~FLAG_JISAN_SACK;
    }
}

THUMB bool status::StoryStatus::isJisanSack()
{
    return flag_.check(FLAG_JISAN_SACK);
}

THUMB void status::StoryStatus::setGoldCard(bool flag)
{
    if (flag) {
        flag_.flag_ |= FLAG_HAVE_GOLD_CARD;
    }
    else {
        flag_.flag_ &= ~FLAG_HAVE_GOLD_CARD;
    }
}

THUMB bool status::StoryStatus::isGoldCard()
{
    return flag_.check(FLAG_HAVE_GOLD_CARD);
}

THUMB void status::StoryStatus::setMedalFlag(bool flag)
{
    if (flag) {
        flag_.flag_ |= FLAG_GET_MEDAL;
    }
    else {
        flag_.flag_ &= ~FLAG_GET_MEDAL;
    }
}

THUMB bool status::StoryStatus::isMedalFlag()
{
    return flag_.check(FLAG_GET_MEDAL);
}

THUMB void status::StoryStatus::setVehicleEnable(int type, bool flag)
{
    switch (type) {
    case 0:
        if (flag) {
            flag_.flag_ |= FLAG_GET_INLAND_SHIP;
        }
        else {
            flag_.flag_ &= ~FLAG_GET_INLAND_SHIP;
        }
        break;
    case 1:
        if (flag) {
            flag_.flag_ |= FLAG_GET_OCEAN_SHIP;
            flag_.flag_ &= ~FLAG_GET_INLAND_SHIP;
        }
        else {
            flag_.flag_ &= ~FLAG_GET_OCEAN_SHIP;
        }
        break;
    case 2:
        break;
    case 3:
        if (flag) {
            flag_.flag_ |= FLAG_GET_FIRMAMENT;
        }
        else {
            flag_.flag_ &= ~FLAG_GET_FIRMAMENT;
        }
        break;
    case 4:
        break;
    }
}

THUMB bool status::StoryStatus::isVehicleEnable(int type)
{
    switch (type) {
    case 0:
        return flag_.check(FLAG_GET_INLAND_SHIP);
    case 1:
        return flag_.check(FLAG_GET_OCEAN_SHIP);
    case 2:
        break;
    case 3:
        return flag_.check(FLAG_GET_FIRMAMENT);
    case 4:
        break;
    }
    return true;
}

THUMB void status::StoryStatus::setChapter(dq5::CHAPTER_NO chapter)
{
    chapter_ = chapter;
    if (chapter_ == dq5::CHAPTER_YOUNENKI) {
        HaveStatus::setSeinenki(false);
        ShopList::setSection(ShopList::SECTION_FIRST);
    }
    if (chapter_ == dq5::CHAPTER_SEINENKI) {
        HaveStatus::setSeinenki(true);
        ShopList::setSection(ShopList::SECTION_SECOND);
    }
    if (chapter_ == dq5::CHAPTER_SOUNENKI) {
        HaveStatus::setSeinenki(true);
        ShopList::setSection(ShopList::SECTION_THIRD);
    }
}
