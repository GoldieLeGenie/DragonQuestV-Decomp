#include "main/leveldata/MapCamera.hpp"
#include "main/leveldata/LevelData.hpp"

inline dq5::level::MapCamera* dq5::level::MapCamera::getRecord(int index)
{
    return (MapCamera*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

const char* dq5::level::MapCamera::filename_ = "data/leveldata/dq5ds_map_camera.dat";
ExcelBinaryData dq5::level::MapCamera::binary_;
void* dq5::level::MapCamera::addr_;
dss::File::LoadSwitch dq5::level::MapCamera::loadSwitch_;
char dq5::level::MapCamera::dataRegion[1040];

THUMB void dq5::level::MapCamera::setup()
{
    if (levelData.getLoadType(18) == 0) {
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

THUMB void dq5::level::MapCamera::cleanup()
{
}
