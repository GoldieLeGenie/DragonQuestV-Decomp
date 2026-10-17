#include "main/dss/DssVectorDefault.hpp"
#include "ov005/fld/FieldStage.hpp"
#include "main/cmn/CommonCounterInfo.hpp"
#include "main/cmn/ExtraMapLink.hpp"
#include "main/cmn/WorldLocation.hpp"
#include "main/global/Global.hpp"
#include "main/leveldata/FieldSymbol.hpp"
#include "main/status/StageAttribute.hpp"
#include "main/status/StageInfo.hpp"
#include "main/status/StoryStatus.hpp"
#include "ov005/fld/FieldPlayerManager.hpp"
#include "ov005/fld/FieldRectColl.hpp"

inline int status::StageInfo::getFieldChange()
{
    return fieldChangeIndex_;
}

inline int status::StageAttribute::getTimestopFlag()
{
    return timestop_;
}

inline dq5::CHAPTER_NO status::StoryStatus::getChapter()
{
    return chapter_;
}

inline int fld::FieldPlayerManager::getMoveType()
{
    return player_.getMoveType();
}

inline dss::Fix32Vector3 fld::FieldData::getPosition()
{
    return position_;
}

inline void fld::FieldData::setOffset(int offset)
{
    offset_ = offset;
}

inline int fld::FieldData::getOffset()
{
    return offset_;
}

inline unsigned int dq5::level::FieldSymbol::getArraySize()
{
    return binary_.record_;
}

inline dq5::level::FieldSymbol* dq5::level::FieldSymbol::getRecord(int index)
{
    return (FieldSymbol*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned short dq5::level::FieldSymbol::getUid()
{
    return uid;
}

THUMB fld::FieldStage::FieldStage()
{
}

THUMB fld::FieldStage::~FieldStage()
{
}

THUMB fld::FieldStage* fld::FieldStage::getSingleton()
{
    static FieldStage fieldStage;
    return &fieldStage;
}

THUMB void fld::FieldStage::initialize()
{
    map_ = g_Global.getFieldType();
    scriptShip_ = 0;
    if (map_ == 0) {
        fieldData.setup(map_, status::g_StageInfo.getFieldChange());
    } else {
        fieldData.setup(map_, 0);
        status::g_StageInfo.setWorldTime(cmn::WorldLocation::getDaytime());
    }
    FieldRectCollManager::getSingleton().setup();
    status::g_StageAttribute.setMapName("field");
    status::g_StageAttribute.setBtlMapName("field");
    status::g_StageAttribute.setEncount(1);
}

THUMB void fld::FieldStage::terminate()
{
    cmn::WorldLocation::setCurrentTimeZone();
    fieldData.cleanup(map_);
}

THUMB fld::FieldData& fld::FieldStage::getFieldData()
{
    return fieldData;
}

THUMB void fld::FieldStage::execute()
{
}

THUMB void fld::FieldStage::draw()
{
    FieldCarrirerDraw* carrier;
    dss::Vector2<int> pos;
    fieldData.draw();
    if (cmn::WorldLocation::isVehicleExist(0)) {
        if (status::g_Story.isVehicleEnable(0) == true) {
            carrier = FieldPlayerManager::getSingleton().getCarrierDraw(0);
            pos = calcDrawPosition(FieldPlayerManager::getSingleton().player_.fieldActionShip_.getShipDrawPos(0));
            carrier->draw(pos);
        }
        if (status::g_Story.isVehicleEnable(1) == true || scriptShip_ == 1) {
            carrier = FieldPlayerManager::getSingleton().getCarrierDraw(1);
            pos = calcDrawPosition(FieldPlayerManager::getSingleton().player_.fieldActionShip_.getShipDrawPos(1));
            carrier->draw(pos);
        }
        if (FieldPlayerManager::getSingleton().getMoveType() != 5 && status::g_Story.isVehicleEnable(3) == true) {
            carrier = FieldPlayerManager::getSingleton().getCarrierDraw(3);
            pos = calcDrawPosition(carrier->getPosition());
            carrier->draw(pos);
        }
    }
}

THUMB void fld::FieldStage::drawPlayer()
{
    fieldData.setPlayerCamera();
    dss::Vector2<int> pos;
    FieldCarrirerDraw* carrier;
    int type = FieldPlayerManager::getSingleton().getMoveType();
    switch (type) {
    case 7:
        carrier = FieldPlayerManager::getSingleton().getCarrierDraw(4);
        pos = calcDrawPosition(carrier->getPosition());
        carrier->draw(pos);
        carrier->setDepth(8);
        break;
    case 5:
        carrier = FieldPlayerManager::getSingleton().getCarrierDraw(3);
        pos = calcDrawPosition(carrier->getPosition());
        carrier->draw(pos);
        carrier->setDepth(8);
        break;
    case 6:
        carrier = FieldPlayerManager::getSingleton().getCarrierDraw(2);
        pos = calcDrawPosition(carrier->getPosition());
        carrier->draw(pos);
        break;
    }
}

THUMB void fld::FieldStage::setOffset(int offset)
{
    fieldData.setOffset(offset);
}

THUMB void fld::FieldStage::setPosition(dss::Fix32Vector3& pos)
{
    fieldData.setPosition(pos);
}

THUMB bool fld::FieldStage::getBlockAttr(int x, int y)
{
    return fieldData.isEnable(x, y);
}

THUMB int fld::FieldStage::getBlockAttr2(int x, int y)
{
    return fieldData.getAttr(x, y);
}

THUMB dss::Fix32Vector3 fld::FieldStage::getSymbolPosition(int index)
{
    return fieldData.getSymbolPosition(index);
}

THUMB int fld::FieldStage::getSearchSymbolAttach(dss::Fix32Vector3 pos, int* id)
{
    return fieldData.getSearchSymbolAttach(pos, id);
}

THUMB void fld::FieldStage::ChangeTime(int apply)
{
    dss::Fix32Vector3 rgbRate;
    int wt = status::g_StageInfo.getWorldTime();
    if (wt % 16 == 0 || apply == 1) {
        if (map_ == 0) {
            rgbRate = cmn::WorldLocation::calcPaletteRate(wt);
            fieldData.setPaletteRate(map_, rgbRate);
        } else {
            rgbRate = cmn::WorldLocation::calcDarkPaletteRate();
            fieldData.setPaletteRate(map_, rgbRate);
        }
    }
    if (status::g_StageAttribute.getTimestopFlag() != 1 && status::g_Story.getChapter() != dq5::CHAPTER_YOUNENKI && g_Global.getFieldType() == 0) {
        if (apply == 0) {
            wt++;
        }
        if (wt == 0) {
            cmn::g_CommonCounterInfo.setChangeDay();
        }
        if (wt >= cmn::WorldLocation::getMaxTime()) {
            wt = 0;
        }
        status::g_StageInfo.setWorldTime(wt);
    }
}

THUMB dss::Vector2<int> fld::FieldStage::calcDrawPosition(dss::Fix32Vector3& pos)
{
    dss::Fix32Vector3 fieldPos = fieldData.getPosition();
    dss::Vector2<int> posXY;
    int ofs = fieldData.getOffset() + 0x20;
    posXY.vx = pos.vx.value / FX32_ONE;
    posXY.vy = pos.vy.value / FX32_ONE;
    if (posXY.vx < ofs + 0x100 && fieldPos.vx.value / FX32_ONE > 0xf00 - ofs) {
        posXY.vx += 0x1000;
    }
    if (posXY.vx > 0xf00 - ofs && fieldPos.vx.value / FX32_ONE < ofs + 0x100) {
        posXY.vx -= 0x1000;
    }
    if (posXY.vy < ofs + 0xc0 && fieldPos.vy.value / FX32_ONE > 0xf40 - ofs) {
        posXY.vy += 0x1000;
    }
    if (posXY.vy > 0xf40 - ofs && fieldPos.vy.value / FX32_ONE < ofs + 0xc0) {
        posXY.vy -= 0x1000;
    }
    return posXY;
}

THUMB void fld::FieldStage::setSymbolFlag(int uid)
{
    for (unsigned int i = 0; i < dq5::level::FieldSymbol::getArraySize(); i++) {
        if (uid == dq5::level::FieldSymbol::getRecord(i)->getUid()) {
            status::g_StageInfo.setSymbolFlag(i);
            return;
        }
    }
}

THUMB void fld::FieldStage::eraseSymbol(int uid)
{
    fieldData.setDispSymbol(uid, 0);
    cmn::g_extraMapLink.setLinkData(uid, 0, cmn::NOT_LINK_THIS_TOWN, 0, 0);
}

THUMB void fld::FieldStage::setChipAttr(int x, int y, int* attr)
{
    attr[0] = getBlockAttr2(x, y - 1);
    attr[1] = getBlockAttr2(x + 1, y - 1);
    attr[2] = getBlockAttr2(x + 1, y);
    attr[3] = getBlockAttr2(x + 1, y + 1);
    attr[4] = getBlockAttr2(x, y + 1);
    attr[5] = getBlockAttr2(x - 1, y + 1);
    attr[6] = getBlockAttr2(x - 1, y);
    attr[7] = getBlockAttr2(x - 1, y - 1);
}

THUMB void fld::FieldStage::setShipColl(int x, int y, FieldCollInfo& info)
{
    info.blockColl[0] = getShipColl(x, y - 1);
    info.blockColl[1] = getShipColl(x + 1, y - 1);
    info.blockColl[2] = getShipColl(x + 1, y);
    info.blockColl[3] = getShipColl(x + 1, y + 1);
    info.blockColl[4] = getShipColl(x, y + 1);
    info.blockColl[5] = getShipColl(x - 1, y + 1);
    info.blockColl[6] = getShipColl(x - 1, y);
    info.blockColl[7] = getShipColl(x - 1, y - 1);
}

THUMB bool fld::FieldStage::getShipColl(int x, int y)
{
    bool ret = false;
    if (getBlockAttr2(x, y) == 8 || x < 0 || y < 0 || x >= 0x100 || y >= 0x100) {
        ret = true;
    }
    return ret;
}

THUMB void fld::FieldStage::setCarpetColl(int x, int y, FieldCollInfo& info)
{
    info.blockColl[0] = isCarpetColl(x, y - 1);
    info.blockColl[1] = isCarpetColl(x + 1, y - 1);
    info.blockColl[2] = isCarpetColl(x + 1, y);
    info.blockColl[3] = isCarpetColl(x + 1, y + 1);
    info.blockColl[4] = isCarpetColl(x, y + 1);
    info.blockColl[5] = isCarpetColl(x - 1, y + 1);
    info.blockColl[6] = isCarpetColl(x - 1, y);
    info.blockColl[7] = isCarpetColl(x - 1, y - 1);
}

THUMB bool fld::FieldStage::isCarpetColl(int x, int y)
{
    if (x < 0 || y < 0 || x >= 0x100 || y >= 0x100) {
        return true;
    }
    if (getBlockAttr2(x, y) == 8) {
        return true;
    }
    if (getBlockAttr2(x, y) == 9) {
        return true;
    }
    if (getBlockAttr2(x, y) == 7) {
        return true;
    }
    if (getBlockAttr2(x, y) == 5) {
        return false;
    }
    if (getBlockAttr2(x, y) == 4) {
        return false;
    }
    if (getBlockAttr(x, y) != false) {
        return true;
    }
    return false;
}

THUMB void fld::FieldStage::setWalkColl(int x, int y, FieldCollInfo& info)
{
    int attr2[8];
    info.blockColl[0] = getBlockAttr(x, y - 1);
    info.blockColl[1] = getBlockAttr(x + 1, y - 1);
    info.blockColl[2] = getBlockAttr(x + 1, y);
    info.blockColl[3] = getBlockAttr(x + 1, y + 1);
    info.blockColl[4] = getBlockAttr(x, y + 1);
    info.blockColl[5] = getBlockAttr(x - 1, y + 1);
    info.blockColl[6] = getBlockAttr(x - 1, y);
    info.blockColl[7] = getBlockAttr(x - 1, y - 1);
    if (getBlockAttr2(x, y) == 9) {
        attr2[0] = getBlockAttr2(x, y - 1);
        attr2[1] = getBlockAttr2(x + 1, y - 1);
        attr2[2] = getBlockAttr2(x + 1, y);
        attr2[3] = getBlockAttr2(x + 1, y + 1);
        attr2[4] = getBlockAttr2(x, y + 1);
        attr2[5] = getBlockAttr2(x - 1, y + 1);
        attr2[6] = getBlockAttr2(x - 1, y);
        attr2[7] = getBlockAttr2(x - 1, y - 1);
        if (attr2[0] == 7 && attr2[4] == 7) {
            if (attr2[2] == 7) {
                info.blockColl[2] = false;
            }
            if (attr2[6] == 7) {
                info.blockColl[6] = false;
            }
        }
        if (attr2[2] == 7 && attr2[6] == 7) {
            if (attr2[0] == 7) {
                info.blockColl[0] = false;
            }
            if (attr2[4] == 7) {
                info.blockColl[4] = false;
            }
        }
        if (attr2[0] == 7 && attr2[4] == 8) {
            if (attr2[2] == 7) {
                info.blockColl[6] = false;
            }
            if (attr2[6] == 7) {
                info.blockColl[2] = false;
            }
        }
    }
    if (fieldData.isCollSymbol(x, y - 1)) {
        info.blockColl[0] = false;
    }
    if (fieldData.isCollSymbol(x + 1, y - 1)) {
        info.blockColl[1] = false;
    }
    if (fieldData.isCollSymbol(x + 1, y)) {
        info.blockColl[2] = false;
    }
    if (fieldData.isCollSymbol(x + 1, y + 1)) {
        info.blockColl[3] = false;
    }
    if (fieldData.isCollSymbol(x, y + 1)) {
        info.blockColl[4] = false;
    }
    if (fieldData.isCollSymbol(x - 1, y + 1)) {
        info.blockColl[5] = false;
    }
    if (fieldData.isCollSymbol(x - 1, y)) {
        info.blockColl[6] = false;
    }
    if (fieldData.isCollSymbol(x - 1, y - 1)) {
        info.blockColl[7] = false;
    }
}
