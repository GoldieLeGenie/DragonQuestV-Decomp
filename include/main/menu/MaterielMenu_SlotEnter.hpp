#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

namespace menu {
    // casino slot machine selection
    struct MaterielMenu_SlotEnter : MenuBase {
        int count_;                             // 0x1C
        int enableFlag_;                        // 0x20
        int slotType_;                          // 0x24

        static int machineSelect_;

        virtual void menuSetup();
        virtual void menuExecute();
        virtual void menuDraw();
        virtual void menuUpdate();
        void setSlotType(int type);
        void enableUpdate();
        int getGameCost();
    };

    extern MaterielMenu_SlotEnter gMaterielMenu_SlotEnter;     // ov019
}
