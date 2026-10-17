#pragma once
#include <globaldefs.h>

namespace fld
{
    // switches the field command objects on/off (main, mobile common/command_object/cmmand_object_field.cpp)
    struct CommandObjectDefineFieldSystem {
        static void setPartChange();
        static void setScreenEffect();
        static void setMessage();
        static void setReturnNormalMenu();
        static void setReturnMaterielMenu();
        static void setMenuSearchNone();
        static void setMenuSearchScript();
        static void setMateriel();
        static void setPlayer();
        static void setScriptEvent();
        static void setAreaMap();
        static void setfieldVehicle();
        static void setWalkCount();
        static void setEncount();
        static void setXmenu();
        static void setButtonSearch();
        static void setPartyTalk();
        static void setNormal();
        static void setButtonSearchScript();
        static void allFalse();
    };
} // namespace fld
