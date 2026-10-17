#pragma once
#include <globaldefs.h>

struct MaterielMenu_WINDOW_MANAGER {
    static MaterielMenu_WINDOW_MANAGER* getSingleton();
    void openMaterielWindow(int menuType);
    void closeMaterielWindow();
};
