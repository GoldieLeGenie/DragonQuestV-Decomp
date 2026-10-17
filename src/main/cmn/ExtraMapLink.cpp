#pragma ipa file
#include "main/cmn/ExtraMapLink.hpp"
#include "main/cmn/CommonCalculate.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/cmn/PlayerManager.hpp"
#include "main/global/Global.hpp"
#include "main/global/UnkGlobalSystem.hpp"
#include "main/global/StageLink.hpp"
#include "main/leveldata/FieldSymbol.hpp"
#include "main/leveldata/LevelDataUtility.hpp"
#include "main/leveldata/VehicleData.hpp"
#include "main/status/GameFlag.hpp"
#include "main/status/StageInfo.hpp"
#include "ov001/town/TownCamera.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov001/town/TownStageManager.hpp"
#include "ov005/fld/FieldPlayerManager.hpp"
#include "ov005/fld/FieldStage.hpp"

inline unsigned short dq5::level::VehicleData::getPlaceNum()
{
    return placeNum;
}

inline dq5::level::FieldSymbol* dq5::level::FieldSymbol::getRecord(int index)
{
    return (FieldSymbol*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline dq5::level::VehicleData* dq5::level::VehicleData::getRecord(int index)
{
    return (VehicleData*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline int dq5::level::VehicleData::getShipX()
{
    return shipX;
}

inline int dq5::level::VehicleData::getShipY()
{
    return shipY;
}


inline int Global::getMapNameId()
{
    return nextMapNameId;
}

inline unsigned int dq5::level::FieldSymbol::getArraySize()
{
    return binary_.record_;
}

inline unsigned short dq5::level::FieldSymbol::getUid()
{
    return uid;
}

inline char dq5::level::FieldSymbol::getWorld()
{
    return byte_1 & 3;
}

THUMB inline dss::Fix32Vector3& fld::FieldPlayerManager::getPosition()
{
    return position_;
}

cmn::ExtraMapLink cmn::g_extraMapLink;

THUMB void cmn::ExtraMapLink::setup()
{
    dss::Fix32Vector3 offset;
    mapLinkDataCount_ = 0;
    rectLinkCount_ = 0;
    soratobu_ = 0;
    warp_[0].surface = 0x100001;
    warp_[0].nextId = 0x100004;
    warp_[0].nextMapNameId = 0x199;
    warp_[1].surface = 0x100002;
    warp_[1].nextId = 0x100006;
    warp_[1].nextMapNameId = 0x199;
    warp_[2].surface = 0x100003;
    warp_[2].nextId = 0x100005;
    warp_[2].nextMapNameId = 0x199;
    warp_[3].surface = 0x100004;
    warp_[3].nextId = 0x100001;
    warp_[3].nextMapNameId = 0x199;
    warp_[4].surface = 0x100005;
    warp_[4].nextId = 0x100003;
    warp_[4].nextMapNameId = 0x199;
    warp_[5].surface = 0x100006;
    warp_[5].nextId = 0x100002;
    warp_[5].nextMapNameId = 0x199;
    warp_[6].surface = 0x100007;
    warp_[6].nextId = 0x100008;
    warp_[6].nextMapNameId = 0x1a4;
    warp_[7].surface = 0x100008;
    warp_[7].nextId = 0x100007;
    warp_[7].nextMapNameId = 0x19a;
}

THUMB void cmn::ExtraMapLink::setExtraFieldPos(dss::Fix32Vector3& pos, short& idx)
{
    switch (extraLink_) {
        case LINK_TOWN_TO_FIELD:
            pos += offset_;
            idx = extraIdx_;
            break;
        case RECT_FIELD_TO_WORLD:
        case RECT_FIELD_TO_YAMI:
        case RECT_FIELD_TO_GOT:
        case LINK_FIELD_ABS_POS:
            pos = offset_;
            idx = extraIdx_;
            break;
    }
    if (fld::FieldStage::getSingleton()->getSearchSymbolAttach(pos, 0) == 0x1a) {
        pos.vy += 0x20;
    }
    extraLink_ = 0;
}

THUMB int cmn::ExtraMapLink::checkFieldLink(int id)
{
    for (int i = 0; i < mapLinkDataCount_; i++) {
        if (id == mapLinkData_[i].nowId) {
            switch (mapLinkData_[i].type) {
                case NOT_LINK_THIS_TOWN:
                    return 4;
                case LINK_FIELD_TO_TOWN:
                    util::StageLink::setTownExitIndex(mapLinkData_[i].nextId);
                    g_Global.startTown(mapLinkData_[i].nextMapNameId);
                    fld::FieldPlayerManager::getSingleton();
                    cmn::PlayerManager::setLock(true);
                    status::g_StageInfo.symbolID_ = id;
                    return 3;
            }
        }
    }
    return 0;
}

THUMB bool cmn::ExtraMapLink::checkExtraTownPos(dss::Fix32Vector3& pos, short& idx)
{
    bool result = false;
    switch (extraLink_) {
        case LINK_EXTRA_TOWN:
            pos = extraPos_;
            idx = extraIdx_;
            result = true;
            break;
        case LINK_TOWN_OFFSET:
            pos += offset_;
            result = true;
            break;
    }
    extraLink_ = 0;
    return result;
}

THUMB void cmn::ExtraMapLink::setExtraExitTown(int mapNameId, int id)
{
    util::StageLink::setTownExitIndex(id);
    g_Global.startTown(mapNameId);
    extraLink_ = EXIT_TOWN;
    cmn::PlayerManager::setLock(true);
}

THUMB void cmn::ExtraMapLink::setExtraLinkTown(int mapNameId, dss::Fix32Vector3& pos, short dir)
{
    extraLink_ = LINK_EXTRA_TOWN;
    g_Global.startTown(mapNameId);
    extraPos_ = pos;
    extraIdx_ = dir;
}

THUMB void cmn::ExtraMapLink::setLinkData(int nowId, int nextId, LINK_TYPE type, int nowMapNameId, int nextMapNameId, dss::Fix32Vector3& offset)
{
    if (nowMapNameId != 0 && nowMapNameId != g_Global.getMapNameId()) {
        return;
    }
    for (int i = 0; i < mapLinkDataCount_; i++) {
        if (nowId == mapLinkData_[i].nowId) {
            setData(i, nowId, nextId, type, nowMapNameId, nextMapNameId, offset);
            return;
        }
    }
    setData(mapLinkDataCount_, nowId, nextId, type, nowMapNameId, nextMapNameId, offset);
    mapLinkDataCount_++;
}

THUMB void cmn::ExtraMapLink::setLinkData(int nowId, int nextId, LINK_TYPE type, int nowMapNameId, int nextMapNameId)
{
    dss::Fix32Vector3 offset(0, 0, 0);
    if (nowMapNameId != 0 && nowMapNameId != g_Global.getMapNameId()) {
        return;
    }
    for (int i = 0; i < mapLinkDataCount_; i++) {
        if (nowId == mapLinkData_[i].nowId) {
            setData(i, nowId, nextId, type, nowMapNameId, nextMapNameId, offset);
            return;
        }
    }
    setData(mapLinkDataCount_, nowId, nextId, type, nowMapNameId, nextMapNameId, offset);
    mapLinkDataCount_++;
}

THUMB int cmn::ExtraMapLink::checkTownMapLink(int id)
{
    switch (extraLink_) {
        case EXIT_TOWN:
            return 6;
        case LINK_EXTRA_TOWN:
            return 5;
    }
    for (int i = 0; i < mapLinkDataCount_; i++) {
        if (id == mapLinkData_[i].nowId && mapLinkData_[i].nowMapNameId == g_Global.getMapNameId()) {
            switch (mapLinkData_[i].type) {
                case LINK_TOWN_TO_TOWN:
                    util::StageLink::setTownExitIndex(mapLinkData_[i].nextId);
                    g_Global.startTown(mapLinkData_[i].nextMapNameId);
                    twn::TownPlayerManager::getSingleton().setLock(true);
                    return 1;
                case LINK_TOWN_TO_FIELD:
                    extraLink_ = LINK_TOWN_TO_FIELD;
                    offset_ = mapLinkData_[i].offsetData;
                    extraIdx_ = 4;
                    util::StageLink::setFieldSymbolIndex(mapLinkData_[i].nextId);
                    g_Global.nextFieldType_ = getFieldTypeBySurface(mapLinkData_[i].nextId);
                    g_Global.startField();
                    twn::TownPlayerManager::getSingleton().setLock(true);
                    status::g_StageInfo.idoLinkInFlag_ = 0;
                    status::g_StageInfo.idoLinkOutFlag_ = 0;
                    return 2;
                case NOT_LINK_THIS_TOWN:
                    return 4;
                case LINK_TOWN_OFFSET:
                    offset_ = mapLinkData_[i].offsetData;
                    extraLink_ = LINK_TOWN_OFFSET;
                    return 0;
                case LINK_TOWN_TO_TOWN_OFFSET:
                    offset_ = mapLinkData_[i].offsetData;
                    extraLink_ = LINK_TOWN_OFFSET;
                    util::StageLink::setTownExitIndex(mapLinkData_[i].nextId);
                    g_Global.startTown(mapLinkData_[i].nextMapNameId);
                    twn::TownPlayerManager::getSingleton().setLock(true);
                    return 1;
                case LINK_DEFAULT:
                    return 0;
            }
        }
    }
    return 0;
}

THUMB void cmn::ExtraMapLink::setExtraExitField(int id, dss::Fix32Vector3& pos)
{
    extraLink_ = LINK_TOWN_TO_FIELD;
    offset_ = pos;
    extraIdx_ = 4;
    util::StageLink::setFieldSymbolIndex(id);
    g_Global.nextFieldType_ = getFieldTypeBySymbol(id);
    g_Global.startField();
    cmn::PlayerManager::setLock(true);
    status::g_StageInfo.idoLinkInFlag_ = 0;
    status::g_StageInfo.idoLinkOutFlag_ = 0;
    cmn::PlayerManager::setLock(true);
}

THUMB void cmn::ExtraMapLink::setTownINN()
{
    dss::Fix32Vector3 pos = twn::TownPlayerManager::getSingleton().getPosition();
    short dir = twn::TownPlayerManager::getSingleton().getDirection();
    setExtraLinkTown(g_Global.getMapNameId(), pos, dir);
}

THUMB void cmn::ExtraMapLink::setMonstarBookLink()
{
    g_cmnPartyInfo.prevLocation_ = 1;
    if (g_Global.prevPartTown_ != 0) {
        dss::Fix32Vector3 pos = twn::TownPlayerManager::getSingleton().getPosition();
        short dir = twn::TownPlayerManager::getSingleton().getDirection();
        setExtraLinkTown(g_Global.prevMapNameId, pos, dir);
    } else {
        dss::Fix32Vector3 pos = g_cmnPartyInfo.position_;
        setExtraLinkFieldAbsPos(g_Global.getFieldType(), pos, g_cmnPartyInfo.dirIdx_);
    }
}

THUMB int cmn::ExtraMapLink::getFieldTypeBySurface(int surface)
{
    int id = surface & 0xfff;
    for (unsigned int i = 0; i < dq5::level::FieldSymbol::getArraySize(); i++) {
        if (id == dq5::level::FieldSymbol::getRecord(i)->getUid()) {
            return dq5::level::FieldSymbol::getRecord(i)->getWorld();
        }
    }
    return 0;
}

THUMB void cmn::ExtraMapLink::eraseSurface(int surface, LINK_TYPE type, int mapNameId)
{
    if (mapNameId == 0) {
        return;
    }
    if (type == NOT_LINK_THIS_TOWN) {
        twn::TownStageManager::getSingleton()->coll_.setEraseSurface(surface, true);
    } else {
        twn::TownStageManager::getSingleton()->coll_.setEraseSurface(surface, false);
    }
}

THUMB int cmn::ExtraMapLink::getFieldTypeBySymbol(int symbol)
{
    for (unsigned int i = 0; i < dq5::level::FieldSymbol::getArraySize(); i++) {
        if (symbol == dq5::level::FieldSymbol::getRecord(i)->getUid()) {
            return dq5::level::FieldSymbol::getRecord(i)->getWorld();
        }
    }
    return 0;
}

THUMB int cmn::ExtraMapLink::checkFieldRectLinkNo(dss::Fix32Vector3& pos)
{
    for (int i = 0; i < rectLinkCount_; i++) {
        if (CommonCalculate::simpleAreaInCheck(rectLinkData_[i].pos[0], rectLinkData_[i].pos[1], pos) == true) {
            return i;
        }
    }
    return -1;
}

THUMB int cmn::ExtraMapLink::checkFieldRectLinkByType(dss::Fix32Vector3& pos, int type)
{
    int no = checkFieldRectLinkNo(pos);
    if (no != -1 && type == rectLinkData_[no].type) {
        if (rectLinkData_[no].type == RECT_FIELD_TO_TOWN) {
            util::StageLink::setTownExitIndex(rectLinkData_[no].nextId);
            g_Global.startTown(rectLinkData_[no].nextMapNameId);
            fld::FieldPlayerManager::getSingleton();
            cmn::PlayerManager::setLock(true);
            offset_ = rectLinkData_[no].pos[3];
            return rectLinkData_[no].nowId;
        }
        extraLink_ = LINK_FIELD_ABS_POS;
        offset_ = rectLinkData_[no].pos[2];
        extraIdx_ = 4;
        switch (rectLinkData_[no].type) {
            case RECT_FIELD_TO_WORLD:
                g_Global.nextFieldType_ = 0;
                break;
            case RECT_FIELD_TO_YAMI:
                g_Global.nextFieldType_ = 3;
                break;
            case RECT_FIELD_TO_GOT:
                break;
        }
        g_Global.startField();
        return 1;
    }
    return 0;
}

THUMB bool cmn::ExtraMapLink::checkEraseSymbolNo(int id)
{
    for (int i = 0; i < mapLinkDataCount_; i++) {
        if (mapLinkData_[i].type == NOT_LINK_THIS_TOWN && id == mapLinkData_[i].nowId) {
            return true;
        }
    }
    return false;
}

THUMB void cmn::ExtraMapLink::setExtraLinkFieldAbsPos(int fieldType, dss::Fix32Vector3& pos, short dir)
{
    cmn::PlayerManager::setLock(true);
    extraLink_ = LINK_FIELD_ABS_POS;
    offset_ = pos;
    g_Global.nextFieldType_ = fieldType;
    g_Global.startField();
    cmn::PlayerManager::setLock(true);
    extraIdx_ = dir;
}

THUMB void cmn::ExtraMapLink::setRuraLink()
{
    int index = dq5::level::g_LevelDataUtility.getRuraIndex(status::g_StageInfo.getRuraTownID());
    if (soratobu_ == 1) {
        index = dq5::level::g_LevelDataUtility.getSoratobuIndex();
        g_Global.nextFieldType_ = 0;
        util::StageLink::setFieldSymbolIndex(0x41);
        g_Global.startField();
    } else if (index != 0x17) {
        int symbol = dq5::level::VehicleData::getRecord(index)->getPlaceNum();
        g_Global.nextFieldType_ = getFieldTypeBySymbol(symbol);
        util::StageLink::setFieldSymbolIndex(symbol);
        g_Global.startField();
    } else {
        dss::Fix32Vector3 pos(0, 0, 0);
        if (g_AreaFlag.check(0x19a) == true) {
            setExtraLinkTown(0x58, pos, 0);
        } else {
            pos.vx.value = -0x3000;
            pos.vy.value = 0x2800;
            pos.vz.value = 0x7000;
            setExtraLinkTown(0x4b, pos, 0);
        }
        g_cmnPartyInfo.setMenuAction((MENU_ACTION)0xb);
    }
    if (g_cmnPartyInfo.menuAction_ != 0xa) {
        dss::Fix32Vector3 pos(0, 0, 0);
        pos.vx.value = dq5::level::VehicleData::getRecord(index)->getShipX();
        pos.vy.value = dq5::level::VehicleData::getRecord(index)->getShipY();
        status::g_StageInfo.shipPosition_[1] = pos;
        if (index != 0x1c) {
            pos.vx = 578.5f;
            pos.vy = 2397.0f;
        }
        status::g_StageInfo.shipPosition_[0] = pos;
    }
    soratobu_ = 0;
    status::g_StageInfo.initDoorOpenFlag();
}

THUMB void cmn::ExtraMapLink::setRanaLink()
{
    if (data_02101c88.unkfunc_02051818(4)) {
        setExtraExitTown(status::g_StageInfo.lastRanaStageNameId_, status::g_StageInfo.lastFldSurface_);
        TownCamera::getSingleton()->endCameraReset_ = 1;
    } else if (data_02101c88.unkfunc_02051818(6)) {
        g_cmnPartyInfo.prevLocation_ = 1;
        dss::Fix32Vector3 pos = fld::FieldPlayerManager::getSingleton().getPosition();
        setExtraLinkFieldAbsPos(g_Global.getFieldType(), pos, 4);
    }
    g_cmnPartyInfo.resetShipIkadaMapName();
    status::g_StageInfo.initDoorOpenFlag();
}

THUMB void cmn::ExtraMapLink::setData(int index, int nowId, int nextId, LINK_TYPE type, int nowMapNameId, int nextMapNameId, dss::Fix32Vector3& offset)
{
    mapLinkData_[index].nowId = nowId;
    mapLinkData_[index].nextId = nextId;
    mapLinkData_[index].type = type;
    mapLinkData_[index].offsetData = offset;
    if (nowMapNameId != 0) {
        mapLinkData_[index].nowMapNameId = nowMapNameId;
    }
    if (nextMapNameId != 0) {
        mapLinkData_[index].nextMapNameId = nextMapNameId;
    }
    if (data_02101c88.unkfunc_02051818(4)) {
        eraseSurface(nowId, type, nowMapNameId);
    }
}

THUMB bool cmn::ExtraMapLink::checkWarp(int surface)
{
    for (int i = 0; i < WARP_COUNT; i++) {
        if (surface == warp_[i].surface) {
            util::StageLink::setTownExitIndex(warp_[i].nextId);
            g_Global.startTown(warp_[i].nextMapNameId);
            return true;
        }
    }
    return false;
}

THUMB void cmn::ExtraMapLink::setFieldTabi(int id)
{
    dss::Fix32Vector3 pos(0, 0, 0);
    setExtraExitField(0x56, pos);
}

THUMB bool cmn::ExtraMapLink::checkFieldToTownTabi(int id)
{
    if (id == 0x56) {
        return true;
    }
    return false;
}
