#include "ov005/fld/FieldCommand.hpp"
#include "main/cmn/CommandObjectField.hpp"
#include "main/dss/Pad.hpp"
#include "main/global/Global.hpp"
#include "ov005/fld/FieldSystem.hpp"
#include "ov019/commonmenu/CommonMenu_Dummy.hpp"
#include <nitro/pad.h>

THUMB int fld::FieldCommandAreaMap::isExec()
{
    if (dss::g_Pad.edge() & PAD_BUTTON_Y) {
        if (!fadeEffector.isFadeEnd()) {
            return false;
        }
        if (g_Global.getFieldType() != 0) {
            return false;
        }
        FieldSystem::getSingleton()->fieldSystemWorldMap_.openAreaMap();
        gTownMenu_MapInfo.setMapInfo(1);
        return true;
    }
    return false;
}

THUMB int fld::FieldCommandAreaMap::isEnd()
{
    if (dss::g_Pad.edge() & PAD_BUTTON_Y || dss::g_Pad.edge() & PAD_BUTTON_B || dss::g_Pad.edge() & PAD_BUTTON_A ||
        dss::g_Pad.edge() & PAD_BUTTON_X) {
        if (FieldSystem::getSingleton()->fieldSystemWorldMap_.isAreaMapOpen()) {
            FieldSystem::getSingleton()->fieldSystemWorldMap_.closeAreaMap();
            gTownMenu_MapInfo.close();
        }
    }
    return FieldSystem::getSingleton()->fieldSystemWorldMap_.isAreaMapClose();
}

THUMB void fld::FieldCommandAreaMap::exec()
{
    CommandObjectDefineFieldSystem::setAreaMap();
}
