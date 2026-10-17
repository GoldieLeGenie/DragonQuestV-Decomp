#include "main/leveldata/LevelDataUtility.hpp"
#include "main/leveldata/ShopIndex1.hpp"
#include "main/leveldata/ShopIndex2.hpp"
#include "main/leveldata/ShopIndex3.hpp"
#include "main/leveldata/ShopIndexSugoroku.hpp"
#include "main/leveldata/ColorCorrect.hpp"
#include "main/leveldata/FurnitureList.hpp"
#include "main/leveldata/CharaData.hpp"
#include "main/leveldata/VehicleData.hpp"
#include "main/leveldata/MapCamera.hpp"
#include "main/leveldata/FloorList.hpp"
#include "main/status/StoryStatus.hpp"
#include "main/status/GameFlag.hpp"
#include "main/global/Global.hpp"

inline unsigned short dq5::level::CharaData::getIndex()
{
    return index;
}

inline unsigned short dq5::level::ColorCorrect::getFloor()
{
    return floor;
}

inline unsigned short dq5::level::FloorList::getFloorIndex()
{
    return floorIndex;
}

inline unsigned short dq5::level::FloorList::getArea()
{
    return area;
}

inline char* dq5::level::FloorList::getFloor()
{
    return floor;
}

inline unsigned long dq5::level::FurnitureList::getFloor()
{
    return floor;
}

inline unsigned short dq5::level::MapCamera::getAreaNo()
{
    return areaNo;
}

inline unsigned short dq5::level::MapCamera::getFlagNo()
{
    return flagNo;
}

inline unsigned short dq5::level::MapCamera::getFloorNo()
{
    return floorNo;
}

inline unsigned short dq5::level::ShopIndex1::getArea()
{
    return area;
}

inline unsigned short dq5::level::ShopIndex2::getArea()
{
    return area;
}

inline unsigned short dq5::level::ShopIndex3::getArea()
{
    return area;
}

inline unsigned short dq5::level::ShopIndexSugoroku::getArea()
{
    return area;
}

inline unsigned short dq5::level::VehicleData::getPlaceNum()
{
    return placeNum;
}

inline unsigned short dq5::level::VehicleData::getFloor()
{
    return floor;
}

inline char dq5::level::VehicleData::getYounenki()
{
    return byte_1 & 1;
}

inline char dq5::level::VehicleData::getSeinenki()
{
    return (byte_1 & 2) >> 1;
}

inline char dq5::level::VehicleData::getSounenki()
{
    return (byte_1 & 4) >> 2;
}

inline dq5::CHAPTER_NO status::StoryStatus::getChapter()
{
    return chapter_;
}

inline unsigned int ExcelBinaryData::getRecordCount()
{
    return record_;
}

inline unsigned int dq5::level::CharaData::getArraySize()
{
    return binary_.getRecordCount();
}

inline unsigned int dq5::level::ColorCorrect::getArraySize()
{
    return binary_.getRecordCount();
}

inline unsigned int dq5::level::FloorList::getArraySize()
{
    return binary_.getRecordCount();
}

inline unsigned int dq5::level::FurnitureList::getArraySize()
{
    return binary_.getRecordCount();
}

inline unsigned int dq5::level::MapCamera::getArraySize()
{
    return binary_.getRecordCount();
}

inline unsigned int dq5::level::ShopIndex1::getArraySize()
{
    return binary_.getRecordCount();
}

inline unsigned int dq5::level::ShopIndex2::getArraySize()
{
    return binary_.getRecordCount();
}

inline unsigned int dq5::level::ShopIndex3::getArraySize()
{
    return binary_.getRecordCount();
}

inline unsigned int dq5::level::ShopIndexSugoroku::getArraySize()
{
    return binary_.getRecordCount();
}

inline unsigned int dq5::level::VehicleData::getArraySize()
{
    return binary_.getRecordCount();
}

inline dq5::level::CharaData* dq5::level::CharaData::getRecord(int index)
{
    return (CharaData*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline dq5::level::ColorCorrect* dq5::level::ColorCorrect::getRecord(int index)
{
    return (ColorCorrect*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline dq5::level::FloorList* dq5::level::FloorList::getRecord(int index)
{
    return (FloorList*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline dq5::level::FurnitureList* dq5::level::FurnitureList::getRecord(int index)
{
    return (FurnitureList*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline dq5::level::MapCamera* dq5::level::MapCamera::getRecord(int index)
{
    return (MapCamera*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline dq5::level::ShopIndex1* dq5::level::ShopIndex1::getRecord(int index)
{
    return (ShopIndex1*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline dq5::level::ShopIndex2* dq5::level::ShopIndex2::getRecord(int index)
{
    return (ShopIndex2*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline dq5::level::ShopIndex3* dq5::level::ShopIndex3::getRecord(int index)
{
    return (ShopIndex3*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline dq5::level::ShopIndexSugoroku* dq5::level::ShopIndexSugoroku::getRecord(int index)
{
    return (ShopIndexSugoroku*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline dq5::level::VehicleData* dq5::level::VehicleData::getRecord(int index)
{
    return (VehicleData*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline int Global::getNowAreaNo() { return areaNo_; }
inline int Global::getMapNameId() { return nextMapNameId; }

dq5::level::LevelDataUtility dq5::level::g_LevelDataUtility;

THUMB dq5::level::LevelDataUtility::LevelDataUtility()
{
}

THUMB dq5::level::LevelDataUtility::~LevelDataUtility()
{
}

THUMB int dq5::level::LevelDataUtility::searchShopDataIndex(int areaId, int section)
{
    unsigned int max;
    switch (section) {
    case 0:
        max = ShopIndex1::getArraySize();
        break;
    case 1:
        max = ShopIndex2::getArraySize();
        break;
    case 2:
        max = ShopIndex3::getArraySize();
        break;
    default:
        max = ShopIndexSugoroku::getArraySize();
        break;
    }
    for (int i = 0; i < max; i++) {
        int id;
        switch (section) {
        case 0:
            id = ShopIndex1::getRecord(i)->getArea();
            break;
        case 1:
            id = ShopIndex2::getRecord(i)->getArea();
            break;
        case 2:
            id = ShopIndex3::getRecord(i)->getArea();
            break;
        default:
            id = ShopIndexSugoroku::getRecord(i)->getArea();
            break;
        }
        if (id == areaId) {
            return i;
        }
    }
    return -1;
}

THUMB int dq5::level::LevelDataUtility::searchMapCorrectIndex(int mapId)
{
    for (int i = 0; i < ColorCorrect::getArraySize(); i++) {
        if (mapId == ColorCorrect::getRecord(i)->getFloor()) {
            return i;
        }
    }
    return -1;
}

THUMB int dq5::level::LevelDataUtility::searchFurnDataIndex(int mapId)
{
    int index = -1;
    FurnitureList::setup();
    for (int i = 0; i < FurnitureList::getArraySize(); i++) {
        if (mapId == FurnitureList::getRecord(i)->getFloor()) {
            index = i;
            break;
        }
    }
    FurnitureList::cleanup();
    return index;
}

THUMB int dq5::level::LevelDataUtility::getCharaParamIndex(int index)
{
    for (int i = 0; i < CharaData::getArraySize(); i++) {
        if (index == CharaData::getRecord(i)->getIndex()) {
            return i;
        }
    }
    return 0;
}

THUMB int dq5::level::LevelDataUtility::getSoratobuIndex()
{
    for (int i = 0; i < VehicleData::getArraySize(); i++) {
        if (status::g_Story.getChapter() == dq5::CHAPTER_SEINENKI) {
            if (VehicleData::getRecord(i)->getSeinenki()) {
            }
            else {
                continue;
            }
        }
        else {
            if (VehicleData::getRecord(i)->getSounenki()) {
            }
            else {
                continue;
            }
        }
        if (VehicleData::getRecord(i)->getPlaceNum() == 0x41) {
            return i;
        }
    }
    return -1;
}

THUMB int dq5::level::LevelDataUtility::getKimeraIndex(int map)
{
    int count = 0;
    int uid = 0;
    for (int i = 0; i < VehicleData::getArraySize(); i++) {
        if (uid != VehicleData::getRecord(i)->getPlaceNum()) {
            count++;
        }
        uid = VehicleData::getRecord(i)->getPlaceNum();
        if (status::g_Story.getChapter() == dq5::CHAPTER_YOUNENKI) {
            if (VehicleData::getRecord(i)->getYounenki()) {
            }
            else {
                continue;
            }
        }
        else if (status::g_Story.getChapter() == dq5::CHAPTER_SEINENKI) {
            if (VehicleData::getRecord(i)->getSeinenki()) {
            }
            else {
                continue;
            }
        }
        else if (status::g_Story.getChapter() == dq5::CHAPTER_SOUNENKI) {
            if (VehicleData::getRecord(i)->getSounenki()) {
            }
            else {
                continue;
            }
        }
        if (map == VehicleData::getRecord(i)->getFloor()) {
            return count;
        }
    }
    return -1;
}

THUMB int dq5::level::LevelDataUtility::getRuraIndex(int flag)
{
    int count = 0;
    int uid = 0;
    for (int i = 0; i < VehicleData::getArraySize(); i++) {
        if (uid != VehicleData::getRecord(i)->getPlaceNum()) {
            count++;
        }
        uid = VehicleData::getRecord(i)->getPlaceNum();
        if (status::g_Story.getChapter() == dq5::CHAPTER_YOUNENKI) {
            if (VehicleData::getRecord(i)->getYounenki()) {
            }
            else {
                continue;
            }
        }
        else if (status::g_Story.getChapter() == dq5::CHAPTER_SEINENKI) {
            if (VehicleData::getRecord(i)->getSeinenki()) {
            }
            else {
                continue;
            }
        }
        else {
            if (VehicleData::getRecord(i)->getSounenki()) {
            }
            else {
                continue;
            }
        }
        if (count == flag) {
            return i;
        }
    }
    return -1;
}

THUMB int dq5::level::LevelDataUtility::getOverviewFloor(int mapId)
{
    for (int i = 0; i < MapCamera::getArraySize(); i++) {
        if (mapId == MapCamera::getRecord(i)->getFloorNo()) {
            return i;
        }
    }
    return -1;
}

THUMB int dq5::level::LevelDataUtility::getOverviewArea(int areaId)
{
    if (g_Global.getNowAreaNo() == 10 && g_AreaFlag.check(0x194)) {
        return 5;
    }
    for (int i = 0; i < MapCamera::getArraySize(); i++) {
        if (areaId == MapCamera::getRecord(i)->getAreaNo()) {
            if (MapCamera::getRecord(i)->getFlagNo() == 0) {
                return i;
            }
            if (!g_AreaFlag.check(MapCamera::getRecord(i)->getFlagNo())) {
                return i;
            }
        }
    }
    return -1;
}

THUMB int dq5::level::LevelDataUtility::getMapNameIdByName(const char* name)
{
    FloorList* floorData;
    int max = FloorList::getArraySize();
    for (int i = 0; i < max; i++) {
        floorData = FloorList::getRecord(i);
        char* tname = floorData->getFloor();
        if (name[0] == tname[0] && name[1] == tname[1] && dss::strcmp(name, tname) == 0) {
            return floorData->getFloorIndex();
        }
    }
    return 0;
}

THUMB const char* dq5::level::LevelDataUtility::getMapNameById(int no)
{
    int max = FloorList::getArraySize();
    FloorList* floorData;
    for (int i = 0; i < max; i++) {
        floorData = FloorList::getRecord(i);
        if (no == floorData->getFloorIndex()) {
            return floorData->getFloor();
        }
    }
    return NULL;
}

THUMB int dq5::level::LevelDataUtility::getAreaNoByMapId(int id)
{
    int max = FloorList::getArraySize();
    FloorList* floorData;
    for (int i = 0; i < max; i++) {
        floorData = FloorList::getRecord(i);
        if (id == floorData->getFloorIndex()) {
            return floorData->getArea();
        }
    }
    return 0;
}

THUMB int dq5::level::LevelDataUtility::getFloorDataIndex()
{
    int mapID = g_Global.getMapNameId();
    int max = FloorList::getArraySize();
    int i = 0;
    while (i < max) {
        if (mapID == FloorList::getRecord(i)->getFloorIndex()) {
            return i;
        }
        i++;
    }
    return 0;
}
