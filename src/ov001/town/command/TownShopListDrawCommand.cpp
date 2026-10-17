#include "ov001/town/command/TownShopListDrawCommand.hpp"
#include "main/status/StageAttribute.hpp"
#include "main/town/TownCommandEncount.hpp"
#include "main/window/MapControl.hpp"
#include "main/window/ShoplistControl.hpp"

#pragma thumb on

inline int window::ShoplistControl::isOpen()
{
    return open_;
}

inline void window::ShoplistControl::setOpen(bool flag)
{
    open_ = flag;
}

inline bool window::ShoplistControl::isEnd()
{
    return state_ == 6;
}

inline int status::StageAttribute::getShopDataIndex()
{
    return shopDataIndex_;
}

int twn::TownShopListDrawCommand::isExec()
{
    if (window::gShoplistControl.isOpen() == true) {
        if (!status::g_StageAttribute.isShopIcon()) {
            window::gShoplistControl.setOpen(false);
            return false;
        }
        if (status::g_StageAttribute.getShopDataIndex() == -1) {
            window::gShoplistControl.setOpen(false);
            return false;
        }
        if (status::g_StageAttribute.isShopListDisable() == true) {
            window::gShoplistControl.setOpen(false);
            return false;
        }
        window::gShoplistControl.setup();
        return true;
    }
    return false;
}

int twn::TownShopListDrawCommand::isEnd()
{
    if (window::gMapControl.isEnd() == false) {
        return false;
    } else {
        return window::gShoplistControl.isEnd();
    }
}

void twn::TownShopListDrawCommand::exec()
{
    CommandObjectDefineTownSystem::setShopList();
}
