#include "main/leveldata/SugorokuPanelList.hpp"
#include "main/leveldata/LevelData.hpp"

const char* dq5::level::SugorokuPanelList::filename_ = "data/leveldata/dq5ds_sugoroku_panel.dat";
ExcelBinaryData dq5::level::SugorokuPanelList::binary_;
void* dq5::level::SugorokuPanelList::addr_;
dss::File::LoadSwitch dq5::level::SugorokuPanelList::loadSwitch_;
char dq5::level::SugorokuPanelList::dataRegion[120];

THUMB void dq5::level::SugorokuPanelList::setup()
{
    if (levelData.getLoadType(155) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = dataRegion;
    binary_.setup(sizeof(dataRegion));
}

THUMB void dq5::level::SugorokuPanelList::cleanup()
{
}
