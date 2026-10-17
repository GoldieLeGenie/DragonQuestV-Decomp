#include "main/leveldata/FieldSymbol.hpp"
#include "main/leveldata/LevelData.hpp"

inline dq5::level::FieldSymbol* dq5::level::FieldSymbol::getRecord(int index)
{
    return (FieldSymbol*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

const char* dq5::level::FieldSymbol::filename_ = "data/leveldata/dq5ds_field_symbol.dat";
ExcelBinaryData dq5::level::FieldSymbol::binary_;
void* dq5::level::FieldSymbol::addr_;
dss::File::LoadSwitch dq5::level::FieldSymbol::loadSwitch_;
char dq5::level::FieldSymbol::dataRegion[1140];

THUMB void dq5::level::FieldSymbol::setup()
{
    if (levelData.getLoadType(13) == 0) {
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
