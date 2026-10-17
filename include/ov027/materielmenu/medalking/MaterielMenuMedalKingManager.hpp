#pragma once
#include <globaldefs.h>

// medal king prize helpers
struct MaterielMenuMedalKingManager {
    static int getItemID();
    static int getItemPrice(int index);
    static bool isNeedMedal();
    static void getItem();
    static void showMessage(int mesIndex0, int mesIndex1, int mesIndex2);
};
