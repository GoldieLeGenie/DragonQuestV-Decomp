#include "main/leveldata/StadiumCard.hpp"
#include "main/leveldata/LevelData.hpp"

inline dq5::level::StadiumCard* dq5::level::StadiumCard::getRecord(int index)
{
    return (StadiumCard*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

const char* dq5::level::StadiumCard::filename_ = "data/leveldata/dq5ds_stadium_card.dat";
ExcelBinaryData dq5::level::StadiumCard::binary_;
void* dq5::level::StadiumCard::addr_;
dss::File::LoadSwitch dq5::level::StadiumCard::loadSwitch_;
char dq5::level::StadiumCard::dataRegion[816];

THUMB void dq5::level::StadiumCard::setup()
{
    if (levelData.getLoadType(172) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = dataRegion;
    binary_.setup(sizeof(dataRegion));
    getRecord(0);
}
