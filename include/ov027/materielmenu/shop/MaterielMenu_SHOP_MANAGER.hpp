#pragma once
#include <globaldefs.h>

// shop item list and the selection of the shop menus
struct MaterielMenu_SHOP_MANAGER {
    enum SHOP_TYPE {
        SHOP_TYPE_NONE = 0,
        SHOP_TYPE_WEAPON = 2,
        SHOP_TYPE_PROTECTOR = 3,
        SHOP_TYPE_ITEM = 4,
        SHOP_TYPE_YOROZU = 5,
        SHOP_TYPE_GIFT = 6,
        SHOP_TYPE_WEAPON_SECOND = 9,
        SHOP_TYPE_PROTECTOR_SECOND = 10,
        SHOP_TYPE_ITEM_SECOND = 11,
        SHOP_TYPE_YOROZU_SECOND = 12,
        SHOP_TYPE_GIFT_SECOND = 13,
        SHOP_TYPE_MEDAL_KING = 14,
        SHOP_TYPE_SUGOROKU = 33,
    };

    int shopType_;                              // 0x00
    int itemPrice_[6];                          // 0x04
    short item_[6];                             // 0x1C
    char itemQuantity_[6];                      // 0x28
    char sellItemCount_;                        // 0x2E
    char shopAction_;                           // 0x2F
    char sellQuantity_;                         // 0x30

    static MaterielMenu_SHOP_MANAGER* getSingleton();
    void initialize();
    void openShopMenu(int type);
    void initializeShopItem();
    void setShopType(int type);
    int getShopType();
    void setShopAction(char action);
    int getShopAction();
    int getItem(int index);
    int getItemPrice(int index);
    int getItemPriceSum(int index);
    int getItemQuantity(int index);
    int getSellItemCount();
    int getMinimumPrice();
    void setSellQuantity(int quantity);
    int getSellQuantity();
    bool buyItem(int index, int activeChara);
    bool sellItem(int activeItem, int activeChara, int page);
    void resetItemQuantity();
    void addItem(int index);
    void subItem(int index);
    void setItemQuantity(int index, int quantity);
    bool sellOK();
    int getShopListType();
    void payOut(int index);
    bool sellOut(int price);
};

// shop clerk messages for the current shop type
struct MaterielMenu_SHOP_MESSAGE_MANAGER {
    int shopType_;                              // 0x00

    static MaterielMenu_SHOP_MESSAGE_MANAGER* getSingleton();
    int idle();
    int buy();
    int sell();
    int yameru();
    int cancel();
    void noMoney(int* mes);
    void buyItem(int plural, bool battleUse, int* mes);
    int haveItemMax();
    void buyToSack(bool haveMoney, int* mes);
    int getItem(bool isBasha, bool isDeath);
    int checkMoney(int overItem, int haveNoMoney, int* mes);
    int haveOther();
    int haveWhose();
    int haveSomething();
    int sortEnd();
    int checkEquip(bool equip);
    void equipItem(int* mes);
    int portSelmi();
    void haveNoItem(bool fukuro, int* mes);
    int sellOK();
    int sellHowMany();
    int sellPluralSellOK();
    void sellNG(bool sellYet, int* mes);
    int sellDifficult();
    void celectNo(bool sellYet, int* mes);
    void sellEnd(bool sellYet, int* mes);
    void overMoney(int* mes);
    int getMessageNo(int index);
};
