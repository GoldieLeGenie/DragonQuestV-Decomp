#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"
#include "main/status/UseActionParam.hpp"

// town item menu: use of an item without target selection
struct TownMenuItemSelectCommandUse : menu::MenuBase {
    int m_isResult;                             // 0x1C
    int m_isSound;                              // 0x20
    int m_isHeal;                               // 0x24
    int m_resultMes[8];                         // 0x28
    short m_updataHP[4];                        // 0x48
    short m_itemID;                             // 0x50
    short m_updataMP;                           // 0x52
    short m_itemUsePlayer;                      // 0x54
    short m_preMe;                              // 0x56
    short m_preSe;                              // 0x58
    char m_papasuWait;                          // 0x5A

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void useItemNoTarget();
    void closeMenuCheck();
    void resultItem();
    void addMenuMessage();
    void getUseItemMessage(status::UseActionParam& param, int* useMes, int* resultMes);
    void openUseItemMessage();
    bool isDisableKimera();
};

extern TownMenuItemSelectCommandUse gTownMenuItemSelectCommandUse;
