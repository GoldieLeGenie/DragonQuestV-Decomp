#include "main/leveldata/BookData.hpp"
#include "main/leveldata/LevelData.hpp"

const char* dq5::level::BookData::filename_ = "data/leveldata/dq5ds_book_data.dat";
ExcelBinaryData dq5::level::BookData::binary_;
void* dq5::level::BookData::addr_;
dss::File::LoadSwitch dq5::level::BookData::loadSwitch_;
char dq5::level::BookData::dataRegion[48];

THUMB void dq5::level::BookData::setup()
{
    if (levelData.getLoadType(210) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = dataRegion;
    binary_.setup(sizeof(dataRegion));
}
