#include "ov001/town/TownMuseumManager.hpp"
#include "ov001/town/TownStageManager.hpp"
#include "ov001/town/riseup/TownRiseupManager.hpp"
#include "main/global/Global.hpp"
#include "main/status/MuseumStatus.hpp"

#pragma thumb on

inline int Global::getNowAreaNo()
{
    return areaNo_;
}

inline int Global::getMapNameId()
{
    return nextMapNameId;
}

inline status::MuseumItemStatus& status::MuseumStatus::getMuseumItemStatus(int index)
{
    return museumitem_[index];
}

inline unsigned short status::MuseumItemStatus::getMapID()
{
    return mapid_;
}

inline unsigned short status::MuseumItemStatus::getMapObjectID()
{
    return mapobjectid_;
}

inline unsigned short status::MuseumItemStatus::getIconID()
{
    return iconid_;
}

twn::TownMuseumManager::TownMuseumManager()
{
}

twn::TownMuseumManager::~TownMuseumManager()
{
}

twn::TownMuseumManager& twn::TownMuseumManager::getSingleton()
{
    static TownMuseumManager townMuseumManager;
    return townMuseumManager;
}

void twn::TownMuseumManager::initialize()
{
    if (g_Global.getNowAreaNo() == 0x5d) {
        for (int i = 0; i < MAX_EXHIBIT; i++) {
            pedestal_[i].uid = 0;
            pedestal_[i].drawID = 0;
        }
        int count = 0;
        for (int i = 0; i < status::MuseumStatus::MUSEUM_ITEM_MAX; i++) {
            status::MuseumItemStatus& item = status::g_MuseumStatus.getMuseumItemStatus(i);
            if (g_Global.getMapNameId() == item.getMapID() && item.getIconID() != 0) {
                dss::Fix32Vector3 pos = TownStageManager::getSingleton()->getMapUidPos(item.getMapObjectID());
                pos.vy.value += 0x800;
                pedestal_[count].drawID = TownRiseupManager::getSingleton().setupExhibitIcon(item.getIconID(), pos);
                TownRiseupManager::getSingleton().setFadeIn(pedestal_[count].drawID, 1);
                pedestal_[count].uid = item.getMapObjectID();
                count++;
            }
        }
    }
}

void twn::TownMuseumManager::terminate()
{
}

void twn::TownMuseumManager::execute()
{
}

void twn::TownMuseumManager::draw()
{
}

int twn::TownMuseumManager::getPedestal(int uid)
{
    int index = -1;
    for (int i = 0; i < MAX_EXHIBIT; i++) {
        if (uid == pedestal_[i].uid) {
            index = i;
            break;
        }
    }
    return index;
}

void twn::TownMuseumManager::pushExhibit(int uid, int icon)
{
    int index = getPedestal(0);
    dss::Fix32Vector3 pos = TownStageManager::getSingleton()->getMapUidPos(uid);
    pos.vy.value += 0x800;
    pedestal_[index].drawID = TownRiseupManager::getSingleton().setupExhibitIcon(icon, pos);
    TownRiseupManager::getSingleton().setFadeIn(pedestal_[index].drawID, 1);
    pedestal_[index].uid = uid;
}

void twn::TownMuseumManager::popExhibit(int uid)
{
    int index = getPedestal(uid);
    TownRiseupManager::getSingleton().setFadeOut(pedestal_[index].drawID, 1);
    pedestal_[index].uid = 0;
}
