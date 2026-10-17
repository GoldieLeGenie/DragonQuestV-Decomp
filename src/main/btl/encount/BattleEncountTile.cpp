#include "main/btl/EncountTile.hpp"
#include "main/leveldata/EncountLayout.hpp"
#include "main/leveldata/LevelData.hpp"

inline dq5::level::EncountLayout* dq5::level::EncountLayout::getRecord(int index)
{
    return (EncountLayout*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned int ExcelBinaryData::getRecordCount()
{
    return record_;
}

inline unsigned short dq5::level::EncountLayout::getFloorNum() { return floorNum; }
inline unsigned char dq5::level::EncountLayout::getChapter() { return chapter; }
inline unsigned char dq5::level::EncountLayout::getTileID() { return tileID; }
inline unsigned int dq5::level::EncountLayout::getArraySize() { return binary_.getRecordCount(); }
inline unsigned char dq5::level::EncountSeaTile1::getTile(unsigned int x, unsigned int y) { return tile_[x + y * width_]; }
inline unsigned char dq5::level::EncountSeaTile2::getTile(unsigned int x, unsigned int y) { return tile_[x + y * width_]; }
inline unsigned char dq5::level::EncountTile1::getTile(unsigned int x, unsigned int y) { return tile_[x + y * width_]; }
inline unsigned char dq5::level::EncountTile2::getTile(unsigned int x, unsigned int y) { return tile_[x + y * width_]; }
inline unsigned char dq5::level::EncountTile3::getTile(unsigned int x, unsigned int y) { return tile_[x + y * width_]; }
inline unsigned char dq5::level::EncountFairyTile::getTile(unsigned int x, unsigned int y) { return tile_[x + y * width_]; }
inline unsigned char dq5::level::EncountDarkTile::getTile(unsigned int x, unsigned int y) { return tile_[x + y * width_]; }

THUMB btl::EncountTile::EncountTile()
{
}

THUMB btl::EncountTile::~EncountTile()
{
}

THUMB void btl::EncountTile::setupDungeon(int chapter, int floorIndex)
{
    chapter_ = chapter;
    tileId_ = getTileId(chapter, floorIndex);
    if (tileId_ == 0) {
        if (chapter_ == 3) {
            chapter_ = 2;
            tileId_ = getTileId(2, floorIndex);
        }
        if (tileId_ == 0) {
            if (chapter_ == 2) {
                chapter_ = 1;
            }
            tileId_ = getTileId(chapter_, floorIndex);
        }
    }
}

THUMB void btl::EncountTile::setupField(int chapter, int type, int land, int x, int y)
{
    if (type == 0) {
        if (chapter == 1) {
            tileId_ = getTileIdFieldOnYounenki(x, y);
        }
        if (chapter == 2) {
            tileId_ = getTileIdFieldOnSeinenki(x, y);
            if (land == 0) {
                tileId_ = getTileIdSeaOnSeinenki(x, y);
            }
        }
        if (chapter == 3) {
            tileId_ = getTileIdFieldOnSounenki(x, y);
            if (land == 0) {
                tileId_ = getTileIdSeaOnSounenki(x, y);
            }
        }
    }
    if (type == 1) {
        tileId_ = getTileIdFairy(x, y);
    }
    if (type == 2) {
        tileId_ = getTileIdFairy(x, y);
    }
    if (type == 3) {
        tileId_ = getTileIdDark(x, y);
    }
}

THUMB int btl::EncountTile::getTileId(int chapter, int floorIndex)
{
    for (int i = 0; i < dq5::level::EncountLayout::getArraySize(); i++) {
        dq5::level::EncountLayout* encountLayout = dq5::level::EncountLayout::getRecord(i);
        if (chapter == encountLayout->getChapter() && floorIndex == encountLayout->getFloorNum()) {
            return encountLayout->getTileID();
        }
    }
    return 0;
}

THUMB int btl::EncountTile::getTileIdFieldOnYounenki(int x, int y)
{
    int tileId = dq5::level::levelData.encountTile1_.getTile(x, y);
    return tileId;
}

THUMB int btl::EncountTile::getTileIdFieldOnSeinenki(int x, int y)
{
    int tileId = dq5::level::levelData.encountTile2_.getTile(x, y);
    return tileId;
}

THUMB int btl::EncountTile::getTileIdFieldOnSounenki(int x, int y)
{
    int tileId = dq5::level::levelData.encountTile3_.getTile(x, y);
    return tileId;
}

THUMB int btl::EncountTile::getTileIdSeaOnSeinenki(int x, int y)
{
    int tileId = dq5::level::levelData.encountSeaTile1_.getTile(x, y);
    return tileId;
}

THUMB int btl::EncountTile::getTileIdSeaOnSounenki(int x, int y)
{
    int tileId = dq5::level::levelData.encountSeaTile2_.getTile(x, y);
    return tileId;
}

THUMB int btl::EncountTile::getTileIdFairy(int x, int y)
{
    int tileId = dq5::level::levelData.encountFairyTile_.getTile(x, y);
    return tileId;
}

THUMB int btl::EncountTile::getTileIdDark(int x, int y)
{
    int tileId = dq5::level::levelData.encountDarkTile_.getTile(x, y);
    return tileId;
}
