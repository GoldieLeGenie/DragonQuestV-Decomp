#include "ov005/fld/FieldCommand.hpp"
#include "main/cmn/CommandObjectField.hpp"
#include "main/window/ShopMenuControl.hpp"

THUMB int fld::FieldCommandMaterielMenu::isExec()
{
    if (window::gShopMenuControl.state_ == 7) {
        window::gShopMenuControl.setup();
        return true;
    }
    return false;
}

THUMB void fld::FieldCommandMaterielMenu::exec()
{
    CommandObjectDefineFieldSystem::setMateriel();
}

THUMB int fld::FieldCommandMaterielMenu::isEnd()
{
    return window::gShopMenuControl.state_ == 8;
}
