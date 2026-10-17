#pragma once
#include <globaldefs.h>

// opens/closes the materiel menu windows (inn, church, shops...)
struct MaterielMenu_WINDOW_MANAGER {
    enum MATERIEL_MENU_WINDOW {
        MENU_NONE = -1,
        MENU_INN = 0,
        MENU_CHURCH = 1,
        MENU_SHOP_WEAPON = 2,
        MENU_SHOP_PROTECTOR = 3,
        MENU_SHOP_ITEM = 4,
        MENU_SHOP_YOROZU = 5,
        MENU_CHANGE_GIFT = 6,
        MENU_INN_TYPE2 = 7,
        MENU_CHURCH_TYPE2 = 8,
        MENU_SHOP_WEAPON_TYPE2 = 9,
        MENU_SHOP_PROTECTOR_TYPE2 = 10,
        MENU_SHOP_ITEM_TYPE2 = 11,
        MENU_SHOP_YOROZU_TYPE2 = 12,
        MENU_CHANGE_GIFT_TYPE2 = 13,
        MENU_MEDAL_KING = 14,
        MENU_BANK = 15,
        MENU_COIN_SALEROOM = 16,
        MENU_SAVE = 17,
        MENU_SURECHIGAI_MAKE_TAISHI = 18,
        MENU_SURECHIGAI_ROOT = 19,
        MENU_SURECHIGAI_MESSAGE = 20,
        MENU_MONSTAR_JISAN = 21,
        MENU_LUIDANO_SAKABA = 22,
        MENU_HUKUBIKIJO = 23,
        MENU_MIMI_MEMO = 24,
        MENU_MIMI_HINT = 25,
        MENU_CASINO_FIGHTSTADIUM = 26,
        MENU_CASINO_SLOT_ENTER = 27,
        MENU_CASINO_POKER = 28,
        MENU_CHURCH_MIRACLE = 29,
        MENU_EXTRA_INN = 30,
        MENU_SUGOROKU_ROOT = 31,
        MENU_SUGOROKU_INN = 32,
        MENU_SUGOROKU_SHOP = 33,
        MENU_SUGOROKU_GETITEM = 34,
        MENU_SET_NAME = 35,
        MENU_SLIME_RACE = 36,
        MENU_SLIME_RACE_MAIN = 37,
        MENU_SLIME_RACE_RESULT = 38,
        MENU_SLIME_TOUCH = 39,
        MENU_SLIME_TOUCH_RESULT = 40,
        MENU_SET_MEISANHIN_ITEM = 41,
        MENU_TAISHI_INFO = 42,
        MENU_MONSTER_AZUKE = 43,
        MENU_CASINO_SLOT = 44,
    };

    int menuType_;                              // 0x00
    int endWindow_;                             // 0x04
    int surechigaiStart_;                       // 0x08
    int changeTaishi_;                          // 0x0C
    int editMessageForScript_;                  // 0x10
    int type_;                                  // 0x14
    int extraInnType_;                          // 0x18
    int nameType_;                              // 0x1C
    short sugorokuItem_;                        // 0x20

    static MaterielMenu_WINDOW_MANAGER* getSingleton();
    void openMaterielWindow(int menuType);
    void setSugorokuItem(short item);
    void closeMaterielWindow();
    void setSurechigaiFlag(bool flag);
    int getSurechigaiFlag();
    void setChangeTaishiFlag(bool flag);
    int getChangeTaishiFlag();
    void setOpenMenuForScript(bool flag);
    void setExtraInnType(int type);
    void setNameType(int type);
    void openBasicMenu(int menu);
    void setSaveMenuType(int type);
    int getCloseMaterielMenu();
};
