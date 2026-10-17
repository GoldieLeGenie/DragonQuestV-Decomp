#pragma once
#include <globaldefs.h>
#include "ov019/commonmenu/MenuPlayerControl.hpp"

namespace menu {

enum TOWN_MENU {
    TOWN_MENU_TALK = 0,
    TOWN_MENU_MAGIC = 1,
    TOWN_MENU_ITEM = 2,
    TOWN_MENU_SEARCH = 3,
    TOWN_MENU_STATUS = 4,
    TOWN_MENU_OPERATION = 5,
};

// selection state shared by the town menus
struct TownMenuPlayerControl : MenuPlayerControl {
    char activeItemPage_;                       // 0x0C
    int activeFukuro_;                          // 0x10
    short targetItem_;                          // 0x14
    char targetItemPage_;                       // 0x16
    int targetFukuro_;                          // 0x18
    int initializeLock_;                        // 0x1C
    unsigned char actorIndex_;                  // 0x20
    unsigned char targetIndex_;                 // 0x21
    unsigned char activeCommand_;               // 0x22
    unsigned char activeTactics_;               // 0x23
    unsigned char unk_24;                       // 0x24
    unsigned char unk_25;                       // 0x25
    char unk_26;                                // 0x26  previous active command

    static TownMenuPlayerControl* getSingleton();
    void setActiveItem(short item);
    short getActiveItem();
    void setActiveItemPage(char page);
    void setActiveFukuro();
    void resetActiveFukuro();
    char getActiveItemPage();
    short getTargetChara();
    void setTargetChara(unsigned char target);
    char getTargetItemPage();
    void setTargetItem(short target);
    void setTargetItemPage(char page);
    void initialize();
    void setActiveChara(unsigned char chara);
    short getActiveItemIndexToAll();
    short getTargetItemIndexToAll();
    void setActiveCommand(unsigned char activeCommand);
    void setActiveMagic(unsigned char active);
    unsigned char getActiveCommand();
    unsigned char getActiveTactics();
    void setActiveTactics(unsigned char tactics);
    unsigned char getDrawCharaCount(TOWN_MENU menuType);
    void setPlayerActiveItemByChangeMax();
    void setFukuroActiveItemByChangeMax();
    void setPlayerTargetItemByChangeMax();
    void setFukuroTargetItemByChangeMax();
};

extern TownMenuPlayerControl gTownMenuPlayerControl;

}  // namespace menu
