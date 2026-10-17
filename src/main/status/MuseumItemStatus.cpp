#include "main/status/MuseumStatus.hpp"
#include "main/global/Global.hpp"
#include "ov001/town/TownMuseumManager.hpp"

inline unsigned short status::MuseumItemStatus::getMapObjectID() { return mapobjectid_; }
inline int Global::getMapNameId() { return nextMapNameId; }

THUMB void status::MuseumItemStatus::setIconIDandRedraw(unsigned short id)
{
    int old = iconid_;
    int now = id;
    iconid_ = now;
    g_MuseumStatus.updateLevel();
    int nowmid = g_Global.getMapNameId();
    if (nowmid != 999 && mapid_ == nowmid) {
        if (old != 0) {
            twn::TownMuseumManager::getSingleton().popExhibit(getMapObjectID());
        }
        if (now != 0) {
            twn::TownMuseumManager::getSingleton().pushExhibit(getMapObjectID(), now);
        }
    }
}
