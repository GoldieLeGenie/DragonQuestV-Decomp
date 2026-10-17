#pragma once
#include <globaldefs.h>

namespace status {
    struct ShopList {
        enum Shop {
            SHOP_HOTEL = 0,
            SHOP_CHURCH = 1,
            SHOP_WEAPON = 2,
            SHOP_PROTECTOR = 3,
            SHOP_ITEM = 4,
            SHOP_YOROZU = 5,
            SHOP_CASINO = 6,
            SHOP_HOTEL_SECOND = 7,
            SHOP_CHURCH_SECOND = 8,
            SHOP_WEAPON_SECOND = 9,
            SHOP_PROTECTOR_SECOND = 10,
            SHOP_YOROZU_SECOND = 11,
            SHOP_ITEM_SECOND = 12,
            SHOP_CASINO_SECOND = 13,
        };
        enum SECTION {
            SECTION_FIRST = 0,
            SECTION_SECOND = 1,
            SECTION_THIRD = 2,
            SECTION_SUGOROKU = 3,
        };
        enum ChurchType {
            NoExist = 0,
            Exist = 1,
            NoPray = 2,
        };

        static const int HOTEL_COUNT = 1;
        static const int CHURCH_COUNT = 1;
        static const int WEAPON_COUNT = 6;
        static const int PROTECTOR_COUNT = 6;
        static const int ITEM_COUNT = 6;
        static const int YOROZU_COUNT = 6;
        static const int CASINO_COUNT = 6;
        static const int HOTEL_OFFSET = 0;
        static const int CHURCH_OFFSET = 1;
        static const int WEAPON_SHOP_OFFSET = 2;
        static const int PROTECTOR_SHOP_OFFSET = 8;
        static const int ITEM_SHOP_OFFSET = 14;
        static const int YOROZU_SHOP_OFFSET = 20;
        static const int CASINO_SHOP_OFFSET = 26;
        static const int SECOND_SHOP_OFFSET = 32;
        static const int SHOP_DATA_OFFSET = 64;

        static int section_;

        ShopList();
        ~ShopList();
        void initialize();
        static void setSection(int section);
        static int getAreaOffset(int area);
        int getDataIndex(int shop) const;
        int getShopCount(int shop) const;
        int getShopItem(int shop, int index) const;
        int getHotelPrice(bool second) const;
        ChurchType getChurchType(bool second) const;
    };

    extern ShopList g_Shop;
}
