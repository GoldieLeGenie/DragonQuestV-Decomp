#pragma once
#include <globaldefs.h>

namespace status {
    struct Status {
        static int flagShopInit;               // data_0209d7d0

        static void initialize();
        static void initialize_character();
        static void setEventParty(unsigned int index);
        static void setEventFlag(unsigned int index);
        static void setFlagShopIndex(int index);
        static void setFlagShopExec();
        static int changeIndexForChapter(int chapter, int index);
        static void setSackWeapon(int index);
        static void setSackArmor(int index);
        static void setSackItem(int index);
    };

    extern int flagShopIndex;                   // data_02093ea4
}
