#include "ov000/leveldata/CameraFile.hpp"
#include "main/leveldata/LevelData.hpp"

const char* dq5::level::CameraFile::filename_ = "data/leveldata/dq5ds_camera_file.dat";
ExcelBinaryData dq5::level::CameraFile::binary_;
void* dq5::level::CameraFile::addr_;
dss::File::LoadSwitch dq5::level::CameraFile::loadSwitch_;
char dq5::level::CameraFile::dataRegion[1024];

THUMB void dq5::level::CameraFile::setup()
{
    if (levelData.getLoadType(8) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = dataRegion;
    binary_.setup(sizeof(dataRegion));
}
