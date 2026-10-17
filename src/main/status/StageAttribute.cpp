#include "main/status/StageAttribute.hpp"
#include "main/status/StageInfo.hpp"
#include "main/status/StoryStatus.hpp"
#include "main/status/ShopList.hpp"
#include "main/global/Global.hpp"
#include "main/leveldata/FloorList.hpp"
#include "main/leveldata/FloorParam.hpp"
#include "main/leveldata/BattleMap.hpp"
#include "main/leveldata/LevelDataUtility.hpp"
#include "nitro/gx.h"

inline unsigned char dq5::level::BattleMap::getR()
{
    return R;
}

inline unsigned char dq5::level::BattleMap::getG()
{
    return G;
}

inline unsigned char dq5::level::BattleMap::getB()
{
    return B;
}

inline unsigned char dq5::level::BattleMap::getMapIndex()
{
    return mapIndex;
}

inline char* dq5::level::BattleMap::getMap()
{
    return map;
}

inline char dq5::level::BattleMap::getTime()
{
    return byte_1 & 1;
}

inline unsigned short dq5::level::FloorList::getFloorIndex()
{
    return floorIndex;
}

inline char dq5::level::FloorParam::getBattlefloor()
{
    return battlefloor;
}

inline char dq5::level::FloorParam::getEventfloor()
{
    return eventfloor;
}

inline char dq5::level::FloorParam::getDaytime()
{
    return byte_1 & 0xf;
}

inline char dq5::level::FloorParam::getIcon_map()
{
    return (byte_1 & 0xf0) >> 4;
}

inline char dq5::level::FloorParam::getIcon_shop()
{
    return byte_2 & 0xf;
}

inline char dq5::level::FloorParam::getIcon_rotate()
{
    return (byte_2 & 0xf0) >> 4;
}

inline char dq5::level::FloorParam::getRula()
{
    return byte_3 & 0xf;
}

inline char dq5::level::FloorParam::getRiremito()
{
    return (byte_3 & 0xf0) >> 4;
}

inline char dq5::level::FloorParam::getLanaruta()
{
    return byte_4 & 0xf;
}

inline char dq5::level::FloorParam::getHorsepict()
{
    return (byte_4 & 0xf0) >> 4;
}

inline char dq5::level::FloorParam::getNohorse()
{
    return byte_5 & 0xf;
}

inline char dq5::level::FloorParam::getNopict()
{
    return (byte_5 & 0xf0) >> 4;
}

inline char dq5::level::FloorParam::getSave()
{
    return byte_6 & 0xf;
}

inline char dq5::level::FloorParam::getYami()
{
    return (byte_6 & 0xf0) >> 4;
}

inline char dq5::level::FloorParam::getEncount()
{
    return byte_7 & 0xf;
}

inline dq5::CHAPTER_NO status::StoryStatus::getChapter()
{
    return chapter_;
}

inline unsigned int ExcelBinaryData::getRecordCount()
{
    return record_;
}

inline unsigned int dq5::level::BattleMap::getArraySize()
{
    return binary_.getRecordCount();
}

inline dq5::level::BattleMap* dq5::level::BattleMap::getRecord(int index)
{
    return (BattleMap*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline dq5::level::FloorList* dq5::level::FloorList::getRecord(int index)
{
    return (FloorList*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline dq5::level::FloorParam* dq5::level::FloorParam::getRecord(int index)
{
    return (FloorParam*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

int status::StageAttribute::toramana_;
status::StageAttribute status::g_StageAttribute;

THUMB status::StageAttribute::StageAttribute()
{
}

THUMB status::StageAttribute::~StageAttribute()
{
}

THUMB void status::StageAttribute::initialize()
{
    flag_.clear();
    dss::strcpy_s(mapName_, sizeof(mapName_), "caf1");
    map_ = NULL;
    dss::strcpy_s(btlMapName_, sizeof(btlMapName_), "btl_pl_d");
    btlMap_ = NULL;
    dss::strcpy_s(evBtlMapName_, sizeof(evBtlMapName_), "btl_pl_d");
    evBtlMap_ = NULL;
    mapCorrectIndex_ = -1;
    shopDataIndex_ = -1;
}

THUMB void status::StageAttribute::setup(const char* mapname, int floorIndex, int areaIndex)
{
    flag_.clear();
    setMapName(mapname);
    floorIndex_ = floorIndex;
    dq5::level::FloorParam* floorparam = getFloorParam(floorIndex);
    g_StageAttribute.setTimeZoneEnable(floorparam->getDaytime());
    g_StageAttribute.setMapIcon(floorparam->getIcon_map());
    g_StageAttribute.setShopIcon(floorparam->getIcon_shop());
    g_StageAttribute.setCameraIcon(floorparam->getIcon_rotate());
    g_StageAttribute.setRula(floorparam->getRula() == 1);
    g_StageAttribute.setRulaDisable(floorparam->getRula() == 2);
    g_StageAttribute.setRiremito(floorparam->getRiremito() == 1);
    g_StageAttribute.setRiremitoDisable(floorparam->getRiremito() == 2);
    g_StageAttribute.setLanaruta(floorparam->getLanaruta());
    g_StageAttribute.setAbortSave(floorparam->getSave());
    g_StageAttribute.setYami(floorparam->getYami());
    if (floorparam->getHorsepict()) {
        g_StageAttribute.setCarriageEnable(true);
        g_StageAttribute.setCarriageEnter(true);
    }
    else {
        g_StageAttribute.setCarriageEnable(false);
        g_StageAttribute.setCarriageEnter(false);
    }
    if (floorparam->getNohorse()) {
        g_StageAttribute.setCarriageEnable(false);
    }
    else {
        g_StageAttribute.setCarriageEnable(true);
    }
    if (floorparam->getNopict()) {
        g_StageAttribute.setCarriageEnable(true);
        g_StageAttribute.setCarriageEnter(false);
    }
    if (g_Story.getChapter() != dq5::CHAPTER_YOUNENKI && (unsigned int)(floorIndex_ - 108) <= 2) {
        g_StageAttribute.setTimeZoneEnable(true);
        g_StageAttribute.setMapIcon(true);
        g_StageAttribute.setShopIcon(true);
        g_StageAttribute.setCameraIcon(true);
        g_StageAttribute.setRula(true);
        g_StageAttribute.setRulaDisable(false);
        g_StageAttribute.setRiremito(false);
        g_StageAttribute.setRiremitoDisable(false);
        g_StageAttribute.setLanaruta(true);
        g_StageAttribute.setAbortSave(false);
        g_StageAttribute.setCarriageEnable(false);
        g_StageAttribute.setCarriageEnter(false);
        g_StageAttribute.setCarriageEnable(true);
        g_StageAttribute.setCarriageEnable(true);
        g_StageAttribute.setCarriageEnter(false);
        g_StageAttribute.setYami(true);
    }
    bool encount = false;
    if (floorparam->getEncount() == 1 || floorparam->getEncount() == 2) {
        encount = true;
    }
    g_StageAttribute.setEncount(encount);
    bool eventEncount = false;
    if (floorparam->getEncount() == 3 || floorparam->getEncount() == 4) {
        eventEncount = true;
    }
    g_StageAttribute.setEventEncount(eventEncount);
    normalBtlMapIndex_ = floorparam->getBattlefloor();
    dq5::level::BattleMap* battleMap = getBattleMap(normalBtlMapIndex_);
    setBtlMapName(battleMap->getMap());
    battleBackColor_ = GX_RGB(battleMap->getR(), battleMap->getG(), battleMap->getB());
    eventBtlMapIndex_ = floorparam->getEventfloor();
    setEvBtlMapName(getBattleMap(eventBtlMapIndex_)->getMap());
    g_StageAttribute.setCoercionSort(true);
    mapCorrectIndex_ = dq5::level::g_LevelDataUtility.searchMapCorrectIndex(floorIndex);
    shopDataIndex_ = dq5::level::g_LevelDataUtility.searchShopDataIndex(areaIndex, ShopList::section_);
    furnitureIndex_ = dq5::level::g_LevelDataUtility.searchFurnDataIndex(floorIndex);
}

THUMB void status::StageAttribute::setupField()
{
    flag_.clear();
    if (g_Global.getFieldType() != 3) {
        g_StageAttribute.setTimeZoneEnable(true);
    }
    else {
        g_StageAttribute.setTimeZoneEnable(false);
    }
    if (g_Global.getFieldType() == 0) {
        g_StageAttribute.setMapIcon(true);
    }
    else {
        g_StageAttribute.setMapIcon(false);
    }
    g_StageAttribute.setShopIcon(false);
    g_StageAttribute.setCameraIcon(false);
    g_StageAttribute.setRula(true);
    g_StageAttribute.setRiremito(false);
    if (g_Global.getFieldType() == 0) {
        g_StageAttribute.setLanaruta(true);
        g_StageAttribute.setYami(true);
    }
    else {
        g_StageAttribute.setLanaruta(false);
        g_StageAttribute.setYami(false);
    }
    g_StageAttribute.setCarriageEnter(true);
    g_StageAttribute.setCarriageEnable(true);
    g_StageAttribute.setEncount(true);
    setBtlMapNameOnField(dq5::Field);
    setEvBtlMapName(btlMapName_);
}

THUMB void status::StageAttribute::cleanup()
{
}

THUMB void status::StageAttribute::setTimeZoneEnable(int flag)
{
    if (flag) {
        flag_.flag_ |= FLAG_TIMEZONE;
    }
    else {
        flag_.flag_ &= ~FLAG_TIMEZONE;
    }
}

THUMB bool status::StageAttribute::isTimeZoneEnable() const
{
    return flag_.check(FLAG_TIMEZONE);
}

THUMB void status::StageAttribute::setMapIcon(int flag)
{
    if (flag) {
        flag_.flag_ |= FLAG_MAPICON;
    }
    else {
        flag_.flag_ &= ~FLAG_MAPICON;
    }
}

THUMB bool status::StageAttribute::isMapIcon() const
{
    return flag_.check(FLAG_MAPICON);
}

THUMB void status::StageAttribute::setShopIcon(int flag)
{
    if (flag) {
        flag_.flag_ |= FLAG_SHOPICON;
    }
    else {
        flag_.flag_ &= ~FLAG_SHOPICON;
    }
}

THUMB bool status::StageAttribute::isShopIcon() const
{
    return flag_.check(FLAG_SHOPICON);
}

THUMB void status::StageAttribute::setCameraIcon(int flag)
{
    if (flag) {
        flag_.flag_ |= FLAG_CAMERAICON;
    }
    else {
        flag_.flag_ &= ~FLAG_CAMERAICON;
    }
}

THUMB bool status::StageAttribute::isCameraIcon() const
{
    return flag_.check(FLAG_CAMERAICON);
}

THUMB void status::StageAttribute::setRula(int flag)
{
    if (flag) {
        flag_.flag_ |= FLAG_RULA;
    }
    else {
        flag_.flag_ &= ~FLAG_RULA;
    }
}

THUMB bool status::StageAttribute::isRula() const
{
    return flag_.check(FLAG_RULA);
}

THUMB void status::StageAttribute::setRulaDisable(int flag)
{
    if (flag) {
        flag_.flag_ |= FLAG_RULA_DISABLE;
    }
    else {
        flag_.flag_ &= ~FLAG_RULA_DISABLE;
    }
}

THUMB bool status::StageAttribute::isRulaDisable() const
{
    return flag_.check(FLAG_RULA_DISABLE);
}

THUMB void status::StageAttribute::setRiremito(int flag)
{
    if (flag) {
        flag_.flag_ |= FLAG_RIREMITO;
    }
    else {
        flag_.flag_ &= ~FLAG_RIREMITO;
    }
}

THUMB bool status::StageAttribute::isRiremito() const
{
    return flag_.check(FLAG_RIREMITO);
}

THUMB void status::StageAttribute::setRiremitoDisable(int flag)
{
    if (flag) {
        flag_.flag_ |= FLAG_RIREMITO_DISABLE;
    }
    else {
        flag_.flag_ &= ~FLAG_RIREMITO_DISABLE;
    }
}

THUMB bool status::StageAttribute::isRiremitoDisable() const
{
    return flag_.check(FLAG_RIREMITO_DISABLE);
}

THUMB void status::StageAttribute::setLanaruta(int flag)
{
    if (flag) {
        flag_.flag_ |= FLAG_LANARUTA;
    }
    else {
        flag_.flag_ &= ~FLAG_LANARUTA;
    }
}

THUMB bool status::StageAttribute::isLanaruta() const
{
    return flag_.check(FLAG_LANARUTA);
}

THUMB void status::StageAttribute::setLanarutaDisable(int flag)
{
    if (flag) {
        flag_.flag_ |= FLAG_LANARUTA_DISABLE;
    }
    else {
        flag_.flag_ &= ~FLAG_LANARUTA_DISABLE;
    }
}

THUMB bool status::StageAttribute::isLanarutaDisable() const
{
    return flag_.check(FLAG_LANARUTA_DISABLE);
}

THUMB void status::StageAttribute::setYami(int flag)
{
    if (flag) {
        flag_.flag_ |= FLAG_YAMI;
    }
    else {
        flag_.flag_ &= ~FLAG_YAMI;
    }
}

THUMB bool status::StageAttribute::getYami() const
{
    return flag_.check(FLAG_YAMI);
}

THUMB void status::StageAttribute::setShopListDisable(int flag)
{
    if (flag) {
        flag_.flag_ |= FLAG_SHOP_LIST_DISABLE;
    }
    else {
        flag_.flag_ &= ~FLAG_SHOP_LIST_DISABLE;
    }
}

THUMB bool status::StageAttribute::isShopListDisable()
{
    return flag_.check(FLAG_SHOP_LIST_DISABLE);
}

THUMB bool status::StageAttribute::isKimeraSetDisable()
{
    return flag_.check(FLAG_KIMERA_SET_DISABLE);
}

THUMB void status::StageAttribute::setKimeraSetDisable(int flag)
{
    if (flag) {
        flag_.flag_ |= FLAG_KIMERA_SET_DISABLE;
    }
    else {
        flag_.flag_ &= ~FLAG_KIMERA_SET_DISABLE;
    }
}

THUMB void status::StageAttribute::setToramana(int flag)
{
    toramana_ = flag;
}

THUMB int status::StageAttribute::isToramana()
{
    return toramana_;
}

THUMB void status::StageAttribute::setCarriageEnter(int flag)
{
    if (flag) {
        flag_.flag_ |= FLAG_BASHA_ENTER;
    }
    else {
        flag_.flag_ &= ~FLAG_BASHA_ENTER;
    }
}

THUMB bool status::StageAttribute::isCarriageEnter() const
{
    return flag_.check(FLAG_BASHA_ENTER);
}

THUMB void status::StageAttribute::setCarriageEnable(int flag)
{
    if (flag) {
        flag_.flag_ |= FLAG_BASHA_ENABLE;
    }
    else {
        flag_.flag_ &= ~FLAG_BASHA_ENABLE;
    }
}

THUMB bool status::StageAttribute::isCarriageEnable() const
{
    return flag_.check(FLAG_BASHA_ENABLE);
}

THUMB void status::StageAttribute::setEncount(int flag)
{
    if (flag) {
        flag_.flag_ |= FLAG_ENCOUNT;
    }
    else {
        flag_.flag_ &= ~FLAG_ENCOUNT;
    }
}

THUMB bool status::StageAttribute::isEncount() const
{
    return flag_.check(FLAG_ENCOUNT);
}

THUMB void status::StageAttribute::setEventEncount(int flag)
{
    if (flag) {
        flag_.flag_ |= FLAG_EVENT_ENCOUNT;
    }
    else {
        flag_.flag_ &= ~FLAG_EVENT_ENCOUNT;
    }
}

THUMB void status::StageAttribute::setAbortSave(int flag)
{
    if (flag) {
        flag_.flag_ |= FLAG_ABORT_SAVE;
    }
    else {
        flag_.flag_ &= ~FLAG_ABORT_SAVE;
    }
}

THUMB void status::StageAttribute::setCoercionSort(int flag)
{
    if (flag) {
        flag_.flag_ |= FLAG_COERCION_SORT;
    }
    else {
        flag_.flag_ &= ~FLAG_COERCION_SORT;
    }
}

THUMB bool status::StageAttribute::isCoercionSort() const
{
    return flag_.check(FLAG_COERCION_SORT);
}
THUMB void status::StageAttribute::setBtlMapName(const char* name)
{
    dss::strcpy_s(btlMapName_, sizeof(btlMapName_), name);
    btlMap_ = btlMapName_;
}

THUMB void status::StageAttribute::setBtlMapNameOnField(dq5::LandType land)
{
    if (g_Global.getFieldType() == 3) {
        switch (land) {
        case dq5::Pond:
            normalBtlMapIndex_ = 25;
            dss::strcpy_s(btlMapName_, sizeof(btlMapName_), "btl_dk3");
            break;
        case dq5::Desert:
            normalBtlMapIndex_ = 24;
            dss::strcpy_s(btlMapName_, sizeof(btlMapName_), "btl_dk2");
            break;
        default:
            normalBtlMapIndex_ = 23;
            dss::strcpy_s(btlMapName_, sizeof(btlMapName_), "btl_dk1");
            break;
        }
    }
    else if (g_Global.getFieldType() == 1) {
        normalBtlMapIndex_ = 22;
        dss::strcpy_s(btlMapName_, sizeof(btlMapName_), "btl_sn_d");
    }
    else {
        switch (land) {
        case dq5::Floor:
            normalBtlMapIndex_ = 1;
            dss::strcpy_s(btlMapName_, sizeof(btlMapName_), "btl_pl_d");
            break;
        case dq5::Sea:
            normalBtlMapIndex_ = 10;
            dss::strcpy_s(btlMapName_, sizeof(btlMapName_), "btl_se_d");
            break;
        case dq5::Desert:
            normalBtlMapIndex_ = 4;
            dss::strcpy_s(btlMapName_, sizeof(btlMapName_), "btl_sd_d");
            break;
        case dq5::Mountain:
        case dq5::Lock:
            normalBtlMapIndex_ = 7;
            dss::strcpy_s(btlMapName_, sizeof(btlMapName_), "btl_mt_d");
            break;
        case dq5::Pond:
            normalBtlMapIndex_ = 13;
            dss::strcpy_s(btlMapName_, sizeof(btlMapName_), "btl_po_d");
            break;
        case dq5::Bush:
        case dq5::Field:
            normalBtlMapIndex_ = 1;
            dss::strcpy_s(btlMapName_, sizeof(btlMapName_), "btl_pl_d");
            break;
        case dq5::Forest:
            normalBtlMapIndex_ = 19;
            dss::strcpy_s(btlMapName_, sizeof(btlMapName_), "btl_wd_d");
            break;
        case dq5::Island:
            normalBtlMapIndex_ = 16;
            dss::strcpy_s(btlMapName_, sizeof(btlMapName_), "btl_is_d");
            break;
        }
    }
    getBtlMapName();
    dq5::level::BattleMap* battleMap = getBattleMap(normalBtlMapIndex_);
    battleBackColor_ = GX_RGB(battleMap->getR(), battleMap->getG(), battleMap->getB());
    btlMap_ = btlMapName_;
}

THUMB char* status::StageAttribute::getBtlMapName()
{
    if (isTimeZoneEnable()) {
        int index = normalBtlMapIndex_;
        if (getBattleMap(index)->getTime()) {
            return btlMap_;
        }
        btlMapName_[6] = '_';
        switch (g_StageInfo.getTimeZone()) {
        case TIME_ZONE_NONE:
        case TIME_ZONE_MORNING:
        case TIME_ZONE_DAYTIME:
            btlMapName_[7] = 'd';
            break;
        case TIME_ZONE_NIGHT:
            index += 2;
            btlMapName_[7] = 'n';
            break;
        case TIME_ZONE_EVENING:
            index += 1;
            btlMapName_[7] = 'e';
            break;
        }
        btlMapName_[8] = '\0';
        if (normalBtlMapIndex_ != 0) {
            dq5::level::BattleMap* battleMap = getBattleMap(index);
            battleBackColor_ = GX_RGB(battleMap->getR(), battleMap->getG(), battleMap->getB());
        }
    }
    return btlMap_;
}

THUMB void status::StageAttribute::setEvBtlMapName(const char* name)
{
    dss::strcpy_s(evBtlMapName_, sizeof(evBtlMapName_), name);
    evBtlMap_ = evBtlMapName_;
}

THUMB char* status::StageAttribute::getEvBtlMapName()
{
    dq5::level::BattleMap* battleMap = getBattleMap(eventBtlMapIndex_);
    battleBackColor_ = GX_RGB(battleMap->getR(), battleMap->getG(), battleMap->getB());
    if (isTimeZoneEnable()) {
        int index = eventBtlMapIndex_;
        if (getBattleMap(index)->getTime()) {
            return evBtlMap_;
        }
        evBtlMap_[6] = '_';
        switch (g_StageInfo.getTimeZone()) {
        case TIME_ZONE_NONE:
        case TIME_ZONE_MORNING:
        case TIME_ZONE_DAYTIME:
            evBtlMap_[7] = 'd';
            break;
        case TIME_ZONE_NIGHT:
            index += 2;
            evBtlMap_[7] = 'n';
            break;
        case TIME_ZONE_EVENING:
            index += 1;
            evBtlMap_[7] = 'e';
            break;
        }
        if (eventBtlMapIndex_ != 0) {
            battleMap = getBattleMap(index);
            battleBackColor_ = GX_RGB(battleMap->getR(), battleMap->getG(), battleMap->getB());
        }
    }
    return evBtlMap_;
}

THUMB void status::StageAttribute::setEvBtlMapToBtlMap()
{
    btlMap_ = getEvBtlMapName();
}

THUMB void status::StageAttribute::setMapName(const char* name)
{
    dss::strcpy_s(mapName_, sizeof(mapName_), name);
    map_ = mapName_;
}

THUMB char* status::StageAttribute::getMapName() const
{
    return map_;
}

THUMB unsigned short status::StageAttribute::getBattleMapBackColor()
{
    return battleBackColor_;
}

THUMB void status::StageAttribute::partyWipeOut()
{
}

THUMB dq5::level::FloorParam* status::StageAttribute::getFloorParam(int floorIndex)
{
    for (int i = 0; i < 628; i++) {
        if (floorIndex == dq5::level::FloorList::getRecord(i)->getFloorIndex()) {
            return dq5::level::FloorParam::getRecord(i);
        }
    }
    return NULL;
}

THUMB dq5::level::BattleMap* status::StageAttribute::getBattleMap(int battleIndex)
{
    for (int i = 0; i < dq5::level::BattleMap::getArraySize(); i++) {
        if (battleIndex == dq5::level::BattleMap::getRecord(i)->getMapIndex()) {
            return dq5::level::BattleMap::getRecord(i);
        }
    }
    return NULL;
}
