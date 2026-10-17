#include "ov001/town/command/TownMapDrawCommand.hpp"
#include "main/dss/Pad.hpp"
#include "main/global/Global.hpp"
#include "main/status/StageAttribute.hpp"
#include "main/town/TownCommandEncount.hpp"
#include "main/window/MapControl.hpp"
#include "main/window/ShoplistControl.hpp"

#pragma thumb on

inline void window::ShoplistControl::setOpen(bool flag)
{
    open_ = flag;
}

int twn::TownMapDrawCommand::isExec()
{
    if (dss::g_Pad.edge() & 0x800) {
        if (!status::g_StageAttribute.isMapIcon()) {
            return false;
        }
        if (!fadeEffector.isFadeEnd()) {
            return false;
        }
        window::gMapControl.setup();
        push_ = false;
        counter_ = 0;
        return true;
    }
    return false;
}

int twn::TownMapDrawCommand::isEnd()
{
    if (++counter_ < 30) {
        return false;
    }
    if (!push_) {
        if (dss::g_Pad.edge() & 0x800) {
            window::gMapControl.closeMap();
            window::gShoplistControl.setOpen(true);
            push_ = true;
        } else if ((dss::g_Pad.edge() & 1) || (dss::g_Pad.edge() & 2)) {
            window::gMapControl.closeMap();
            push_ = true;
        }
    }
    if (window::gMapControl.isEnd() == true) {
        return true;
    }
    return false;
}

void twn::TownMapDrawCommand::exec()
{
    CommandObjectDefineTownSystem::setTownMap();
}
