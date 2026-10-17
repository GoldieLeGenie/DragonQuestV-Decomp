#include "ov001/town/player/TownActionTruck.hpp"
#include "ov001/leveldata/TruckRail.hpp"
#include "ov001/town/TownStageManager.hpp"
#include "main/leveldata/TruckGoal.hpp"
#include "main/leveldata/TruckSwitch.hpp"
#include "main/global/Global.hpp"
#include "main/status/StageInfo.hpp"
#include "main/fld/Coll.hpp"

inline int Global::getNowAreaNo()
{
    return areaNo_;
}

inline int Global::getMapNameId()
{
    return nextMapNameId;
}

inline unsigned int ExcelBinaryData::getRecordCount()
{
    return record_;
}

inline dq5::level::TruckRail* dq5::level::TruckRail::getRecord(int index)
{
    return (TruckRail*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline dq5::level::TruckSwitch* dq5::level::TruckSwitch::getRecord(int index)
{
    return (TruckSwitch*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned int dq5::level::TruckSwitch::getArraySize()
{
    return binary_.getRecordCount();
}

inline unsigned short dq5::level::TruckSwitch::getSwitchUid()
{
    return switchUid;
}

inline char dq5::level::TruckSwitch::getSwitchAnim()
{
    return byte_1 & 7;
}

inline dq5::level::TruckGoal* dq5::level::TruckGoal::getRecord(int index)
{
    return (TruckGoal*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned int dq5::level::TruckGoal::getArraySize()
{
    return binary_.getRecordCount();
}

inline int dq5::level::TruckGoal::getX()
{
    return X;
}

inline int dq5::level::TruckGoal::getY()
{
    return Y;
}

inline int dq5::level::TruckGoal::getZ()
{
    return Z;
}

inline unsigned short dq5::level::TruckGoal::getFloor()
{
    return floor;
}

inline unsigned short dq5::level::TruckGoal::getUid()
{
    return uid;
}

inline int fld::FLDObject::CollGetPolyNoBySurface(int surface_id, int start)
{
    return coll_GetPolyNoBySurface(m_coll, surface_id, start);
}

inline void fld::FLDObject::CollEraseObjId(int obj_id)
{
    coll_EraseObjId(m_coll, obj_id);
}

inline void FldStage::eraseCollision(int objectID)
{
    m_fld.CollEraseObjId(objectID);
}

inline void FldStage::setRotObjectUid(int uId, dss::Fix32Vector3& angle)
{
    m_fld.SetMapUidRotFX32(uId, (VecFx32*)&angle);
}

inline int twn::TownStageManager::collGetPolyIDbySurfaceID(int surfaceID)
{
    return stage_.m_fld.CollGetPolyNoBySurface(surfaceID, 0);
}

inline int twn::TownStageManager::getCollPolyByPolyNo(int polyNo, COLL_POLY* coll)
{
    return stage_.collGetPoly(polyNo, coll);
}

inline bool twn::TownStageManager::getPolyPos(dss::Fix32Vector3* pos, int polyNo)
{
    return stage_.collGetPolygonPos(polyNo, pos);
}

inline void twn::TownStageManager::eraseCollision(int objectID)
{
    stage_.eraseCollision(objectID);
}

inline void twn::TownStageManager::setRotObjectUid(int uid, dss::Fix32Vector3& angle)
{
    stage_.setRotObjectUid(uid, angle);
}

inline void twn::TownTruckWagon::setMap(short map)
{
    map_ = map;
}

inline void twn::TownTruckWagon::setUid(short uid)
{
    uid_ = uid;
}

inline void twn::TownTruckWagon::setPos(dss::Fix32Vector3& pos)
{
    pos_ = pos;
}

inline void twn::TownTruckWagon::setIdx(short idx)
{
    idx_ = idx;
}

THUMB void twn::TownTruckSystem::initialize()
{
    for (int i = 0; i < 160; i++) {
        rail_[i].initialize();
    }
    railCount_ = 0;
    startOffset_ = -1;
    if (g_Global.getNowAreaNo() != 0x28) {
        return;
    }
    dq5::level::TruckRail::setup();
    int max = dq5::level::TruckRail::binary_.getRecordCount();
    int map = g_Global.getMapNameId();
    int found = 0;
    for (int i = 0; i < max; i++) {
        if (found == 0) {
            startOffset_++;
        }
        short flag = 0;
        if (dq5::level::TruckRail::getRecord(i)->floor == map) {
            found = 1;
            int index = dq5::level::TruckRail::getRecord(i)->ID;
            switch (dq5::level::TruckRail::getRecord(i)->special) {
                case 1:
                    flag |= 1;
                    break;
                case 2:
                    flag |= 2;
                    break;
                case 3:
                    flag |= 4;
                    break;
                case 4:
                    flag |= 8;
                    break;
                case 5:
                    flag |= 0x80;
                    break;
                case 6:
                    flag |= 0x100;
                    break;
                case 7:
                    flag |= 0x200;
                    break;
                case 8:
                    flag |= 0x400;
                    break;
            }
            short jumpMap = dq5::level::TruckRail::getRecord(i)->moveFloor;
            rail_[railCount_].setData(index, flag, dq5::level::TruckRail::getRecord(i)->moveID, jumpMap);
            railCount_++;
        }
    }
    for (int i = 0; i < railCount_; i++) {
        int start = startOffset_;
        int link1 = dq5::level::TruckRail::getRecord(start + i)->link1;
        int link2 = dq5::level::TruckRail::getRecord(start + i)->link2;
        int branch = dq5::level::TruckRail::getRecord(start + i)->branch;
        if (link1 == 0) {
            rail_[i].pushLink(rail_[i].index_ + 1);
            rail_[i + 1].pushLink(rail_[i].index_);
        } else if (link1 != 999) {
            int no = getRailNoByIndex(link1);
            rail_[i].pushLink(link1);
            rail_[no].pushLink(rail_[i].index_);
        } else if (link1 == 999 && i == 0) {
            rail_[i].pushLink(rail_[i].index_ + 1);
            rail_[i + 1].pushLink(rail_[i].index_);
        }
        if (link2 != 0) {
            int no = getRailNoByIndex(link2);
            rail_[i].pushLink(link2);
            rail_[no].pushLink(rail_[i].index_);
        }
        if (branch == 0 && link2 != 0) {
            rail_[i].root_ = rail_[i].index_ - 1;
        } else if (branch != 0) {
            rail_[i].root_ = branch;
        }
        if (rail_[i].link_[0] == 999 && rail_[i].link_[1] == 999 && rail_[i].link_[2] == 999) {
            rail_[i].pushLink(rail_[i].index_ + 1);
            rail_[i + 1].pushLink(rail_[i].index_);
        }
    }
    dq5::level::TruckRail::cleanup();
    setupWagon();
    for (int i = 0; i < railCount_; i++) {
        TownTruckRail& rail = rail_[i];
        if (rail.index_ == 0x3de) {
            rail.setupSwitch(0x322);
        }
        if (rail.index_ == 0x3df) {
            rail.setupSwitch(0x31f);
        }
    }
    if (g_Global.getMapNameId() == 0x149) {
        if (seesaw_.setupAnim() == true) {
            rail_[getRailNoByIndex(seesaw_.switchIndex_[0])].changeSwitch();
            rail_[getRailNoByIndex(seesaw_.switchIndex_[1])].changeSwitch();
        }
    }
}

THUMB int twn::TownTruckSystem::getRailNoByIndex(int index)
{
    for (int i = 0; i < railCount_; i++) {
        if (rail_[i].index_ == index) {
            return i;
        }
    }
    return 999;
}

THUMB int twn::TownTruckSystem::getNextRailNo(int nowNo, int prevNo)
{
    for (int i = 0; i < 3; i++) {
        short link = rail_[nowNo].link_[i];
        if (link == 999) {
            continue;
        }
        if (prevNo == 999) {
            return getRailNoByIndex(rail_[nowNo].link_[i]);
        }
        if (link != rail_[prevNo].index_ && link != rail_[nowNo].cutlink_) {
            if (rail_[nowNo].root_ == rail_[prevNo].index_) {
                if (link != rail_[nowNo].cutlink_) {
                    return getRailNoByIndex(rail_[nowNo].link_[i]);
                }
            } else if (rail_[nowNo].root_ != 999) {
                return getRailNoByIndex(rail_[nowNo].root_);
            } else {
                return getRailNoByIndex(rail_[nowNo].link_[i]);
            }
        }
    }
    return 999;
}

THUMB int twn::TownTruckSystem::checkWagon(dss::Fix32Vector3& pos)
{
    static const dss::Fix32 r(0x28f);
    int map = g_Global.getMapNameId();
    for (int i = 0; i < wagonCount_; i++) {
        if (wagon_[i].map_ == map) {
            if ((wagon_[i].pos_ - pos).lengthsq() < r) {
                if (wagon_[i].uid_ != delWagonUid_) {
                    return wagon_[i].uid_;
                }
            }
        }
    }
    return 0;
}

THUMB void twn::TownTruckSystem::nextPos(int nowRailNo, dss::Fix32Vector3& nowPos, dss::Fix32Vector3& target)
{
    int surfaceNo = rail_[nowRailNo].index_ + 0x130000;
    COLL_POLY poly;
    int polyNo = TownStageManager::getSingleton()->collGetPolyIDbySurfaceID(surfaceNo);
    TownStageManager::getSingleton()->getCollPolyByPolyNo(polyNo, &poly);
    dss::Fix32 maxLen(0L);
    int no2 = 0;
    int no1 = 0;
    dss::Fix32Vector3 t;
    if (rail_[nowRailNo].root_ == 999 && rail_[nowRailNo].link_[1] != 999) {
        for (int i = 0; i < 4; i++) {
            t.vx.value = poly.vertex[i].x;
            t.vy.value = poly.vertex[i].y;
            t.vz.value = poly.vertex[i].z;
            dss::Fix32 len = (t - nowPos).lengthsq();
            if (maxLen < len) {
                maxLen = len;
                no2 = no1;
                no1 = i;
            }
        }
        target.vx.value = poly.vertex[no2].x + poly.vertex[no1].x;
        target.vy.value = poly.vertex[no2].y + poly.vertex[no1].y;
        target.vz.value = poly.vertex[no2].z + poly.vertex[no1].z;
        target.vx /= 2;
        target.vy /= 2;
        target.vz /= 2;
    } else {
        target.set(0, 0, 0);
        for (int i = 0; i < 4; i++) {
            target.vx.value += poly.vertex[i].x;
            target.vy.value += poly.vertex[i].y;
            target.vz.value += poly.vertex[i].z;
        }
        target.vx /= 4;
        target.vy /= 4;
        target.vz /= 4;
    }
}

THUMB twn::TownTruckWagon& twn::TownTruckSystem::getWagonByUid(int uid)
{
    for (int i = 0; i < wagonCount_; i++) {
        if (wagon_[i].uid_ == uid) {
            return wagon_[i];
        }
    }
    return wagon_[0];
}

THUMB int twn::TownTruckSystem::getRailNo(dss::Fix32Vector3& nowPos)
{
    dss::Fix32 tsq(999L);
    dss::Fix32 tempsq;
    int no = -1;
    dss::Fix32Vector3 pos;
    for (int i = 0; i < railCount_; i++) {
        int poly = TownStageManager::getSingleton()->collGetPolyIDbySurfaceID(rail_[i].index_ + 0x130000);
        if (poly != -1) {
            TownStageManager::getSingleton()->getPolyPos(&pos, poly);
            tempsq = (pos - nowPos).lengthsq();
            if (tempsq < tsq) {
                tsq = tempsq;
                no = i;
            }
        }
    }
    return no;
}

THUMB void twn::TownTruckSystem::registWagon(int uid, int map)
{
    for (int i = 0; i < wagonCount_; i++) {
        if (wagon_[i].uid_ == uid) {
            int objId = TownStageManager::getSingleton()->getObjectIDfromMapUid(uid);
            if (wagon_[i].map_ == map) {
                TownStageManager::getSingleton()->eraseCollision(objId);
                TownStageManager::getSingleton()->setMapUidPosFX32(uid, wagon_[i].pos_);
                dss::Fix32Vector3 ang(0, 0, 0);
                ang.vy.value = wagon_[i].idx_;
                TownStageManager::getSingleton()->setRotObjectUid(uid, ang);
                return;
            }
            TownStageManager::getSingleton()->setObjectDraw(objId, 0, 0);
            TownStageManager::getSingleton()->eraseCollision(objId);
            return;
        }
    }
    wagon_[wagonCount_].setUid(uid);
    wagon_[wagonCount_].setMap(map);
    dss::Fix32Vector3 pos = TownStageManager::getSingleton()->getMapUidPos(uid);
    dss::Fix32Vector3 dir = TownStageManager::getSingleton()->getMapUidRot(uid);
    wagon_[wagonCount_].setPos(pos);
    wagon_[wagonCount_].setIdx(dir.vy.value);
    int objId = TownStageManager::getSingleton()->getObjectIDfromMapUid(uid);
    TownStageManager::getSingleton()->eraseCollision(objId);
    wagonCount_++;
}

THUMB void twn::TownTruckSystem::setupWagon()
{
    int map = g_Global.getMapNameId();
    switch (map) {
        case 0x143:
            registWagon(0x1d6, map);
            break;
        case 0x144:
            registWagon(0x1d7, map);
            registWagon(0x1d8, map);
            registWagon(0x1d9, map);
            break;
        case 0x145:
            registWagon(0x1da, map);
            registWagon(0x1db, map);
            registWagon(0x1dc, map);
            registWagon(0x1dd, map);
            break;
        case 0x146:
            registWagon(0x1dd, map);
            registWagon(0x1de, map);
            break;
        case 0x14a:
            registWagon(0x1e6, map);
            break;
        case 0x147:
            registWagon(0x1df, map);
            registWagon(0x1e0, map);
            break;
        case 0x149:
            registWagon(0x1e1, map);
            registWagon(0x1e2, map);
            registWagon(0x1e3, map);
            registWagon(0x1e4, map);
            registWagon(0x1e5, map);
            break;
    }
}

THUMB void twn::TownTruckSystem::setupSwitch(int rootIndex, int setIndex, int switchUid, int startSwitchAnim, int railUid, int startRailAnim)
{
    for (int i = 0; i < switchCount_; i++) {
        if (switch_[i].switchUid_ == switchUid) {
            if (switch_[i].switchAnim_ != startSwitchAnim) {
                int no = getRailNoByIndex(switch_[i].surfaceIndex_);
                rail_[no].setupSwitch(setIndex);
                rail_[no].changeSwitch();
            } else {
                rail_[getRailNoByIndex(rootIndex)].setupSwitch(setIndex);
            }
            TownStageManager::getSingleton()->setObjectDraw(switchUid, switch_[i].switchAnim_, 1);
            TownStageManager::getSingleton()->setObjectDraw(switch_[i].railUid_, switch_[i].railAnim_, 1);
            return;
        }
    }
    switch_[switchCount_].setupSwitch(rootIndex, switchUid, startSwitchAnim, railUid, startRailAnim);
    rail_[getRailNoByIndex(rootIndex)].setupSwitch(setIndex);
    switchCount_++;
}

THUMB void twn::TownTruckSystem::switchRail(int uid)
{
    for (int i = 0; i < switchCount_; i++) {
        if (switch_[i].switchUid_ == uid) {
            switch_[i].switchRail();
            rail_[getRailNoByIndex(switch_[i].surfaceIndex_)].changeSwitch();
        }
    }
}

THUMB void twn::TownTruckSystem::saveBeforSetup()
{
    unsigned int& switchInit = status::g_StageInfo.switchInitFlag_;
    unsigned int& switchData = status::g_StageInfo.switchDataFlag_;
    switchInit = 0;
    switchData = 0;
    dq5::level::TruckSwitch::setup();
    int max = dq5::level::TruckSwitch::getArraySize();
    for (int i = 0; i < switchCount_; i++) {
        for (int j = 0; j < max; j++) {
            if (switch_[i].switchUid_ == dq5::level::TruckSwitch::getRecord(j)->getSwitchUid()) {
                switchInit |= 1 << j;
                if (switch_[i].switchAnim_ != dq5::level::TruckSwitch::getRecord(j)->getSwitchAnim()) {
                    switchData |= 1 << j;
                }
            }
        }
    }
    dq5::level::TruckSwitch::cleanup();
    if (seesaw_.switchAnim_ == 3) {
        switchData |= 1 << 30;
    }
    dq5::level::TruckGoal::setup();
    max = dq5::level::TruckGoal::getArraySize();
    unsigned int& wagonData1 = status::g_StageInfo.wagonData1Flag_;
    unsigned int& wagonData2 = status::g_StageInfo.wagonData2Flag_;
    wagonData1 = 0;
    wagonData2 = 0;
    dss::Fix32 fix(0x800);
    for (int i = 0; i < wagonCount_; i++) {
        for (int j = 0; j < max; j++) {
            if (wagon_[i].uid_ == dq5::level::TruckGoal::getRecord(j)->getUid() && wagon_[i].map_ == dq5::level::TruckGoal::getRecord(j)->getFloor()) {
                dss::Fix32Vector3 goal;
                dss::Fix32Vector3 vec;
                goal.vx.value = dq5::level::TruckGoal::getRecord(j)->getX();
                goal.vy.value = dq5::level::TruckGoal::getRecord(j)->getY();
                goal.vz.value = dq5::level::TruckGoal::getRecord(j)->getZ();
                vec = wagon_[i].pos_ - goal;
                if (dss::abs<long>(vec.vx.value) < fix.value && dss::abs<long>(vec.vy.value) < fix.value && dss::abs<long>(vec.vz.value) < fix.value) {
                    if (j < 20) {
                        wagonData1 |= 1 << j;
                    } else {
                        wagonData2 |= 1 << (j - 20);
                    }
                    break;
                }
            }
        }
    }
    dq5::level::TruckGoal::cleanup();
}

THUMB void twn::TownTruckSystem::wagonCrear()
{
    if ((status::g_StageInfo.returnGame_ == 1 || status::g_StageInfo.returnGame_ == 2) && g_Global.getNowAreaNo() == 0x28) {
        return;
    }
    wagonCount_ = 0;
    switchCount_ = 0;
    seesaw_.setup();
}
