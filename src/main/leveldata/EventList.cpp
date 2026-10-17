#include "main/leveldata/EventList.hpp"
#include "main/leveldata/LevelData.hpp"

const char* dq5::level::EventList::filename_ = "data/leveldata/dq5ds_event_list.dat";
ExcelBinaryData dq5::level::EventList::binary_;
dss::File::LoadSwitch dq5::level::EventList::loadSwitch_;
void* dq5::level::EventList::addr_;

THUMB void dq5::level::EventList::setup()
{
    if (levelData.getLoadType(12) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = binary_.setup();
}

THUMB void dq5::level::EventList::cleanup()
{
    binary_.cleanup(addr_);
}
