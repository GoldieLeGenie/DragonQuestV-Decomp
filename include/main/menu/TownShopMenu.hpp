#pragma once
#include "main/menu/MenuBase.hpp"

namespace menu {
    struct TownShopMenu : MenuBase {
        int type_;                                  // 0x1C

        TownShopMenu();
        ~TownShopMenu();
        virtual void menuSetup();
        virtual void menuExecute();
        virtual void menuDraw();
        virtual void menuUpdate();
        int setPage(int page);
        bool nextPage();
    };
}

extern menu::TownShopMenu data_ov019_02182f2c;
