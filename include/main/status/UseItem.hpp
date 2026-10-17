#pragma once
#include <globaldefs.h>
#include "GameInfo.hpp"
#include "main/leveldata/ItemData.hpp"
#include "main/status/BaseItem.hpp"

namespace status {
    struct BaseHaveItem;
    struct HaveItemSack;
    struct HaveStatusInfo;
    struct UseActionParam;

    struct ExtraItemYakusou : BaseItem {
    };

    struct ExtraItemDokukesisou : BaseItem {
    };

    struct UseItem {
        enum UseType {
            Myself = 0,
            Friend = 1,
            Enemy = 2,
            Both = 3,
            None = 4,
        };
        enum UseArea {
            Zero = 0,
            One = 1,
            Group = 2,
            All = 3,
            Horse = 4,
            UsuallyHorse = 5,
            BattleHorse = 6,
        };
        enum SellType {
            SELL_OK = 0,
            SELL_NG = 1,
            SELL_DIFFICULT = 2,
            SELL_MAX = 3,
        };
        enum ThrowType {
            THROW_OK = 0,
            THROW_NG = 1,
            THROW_DIFFICULT = 2,
            THROW_MAX = 3,
        };

        static int itemIndex_;
        static int actionIndex_;
        static dq5::level::ItemData* itemData2_;
        static int allEquipment_;

        static void setItemRecord(int index);
        static void initialize();
        static ItemType getItemType(int itemIndex);
        static ItemType getEquipItemType(int itemIndex);
        static ThrowType getThrowType(int itemIndex);
        static SellType getSellType(int itemIndex);
        static bool isCurse(int itemIndex);
        static bool isLost(int itemIndex);
        static bool isOrder(int itemIndex);
        static int getEffect(int itemIndex);
        static int getSellPrice(int itemIndex);
        static int getBuyPrice(int itemIndex);
        static int isEquipEnable(int equipAttrIndex, int itemIndex, int sex);
        static EquipType getEquipType(int itemIndex);
        static int getEquipValue(int itemIndex);
        static BaseItem& getItem(int itemIndex);
        static UseType getUseType(int itemIndex);
        static UseArea getUseArea(int itemIndex);
        static int getUseAction(int itemIndex);
        static int getBattleUseAction(int itemIndex);
        static int getMenuMessage(int itemIndex);
        static bool isBattleUse(int itemIndex);
        static int getTypeSortIndex(int itemIndex);
        static int getNameSortIndex(int itemIndex);
        static int getCommentType(int itemIndex);
        static int getCommentKindIndex(int itemIndex);
        static int getCommentMessage(int itemIndex);
        static int getCasino(int itemIndex);
        static int getStopMessage(int itemIndex);
        static void execUse(UseActionParam& useActionParam);
        static void give(BaseHaveItem& srcHaveItem, int index, BaseHaveItem& desHaveItem);
        static void give2(HaveStatusInfo& srcHaveStatusInfo, int srcIndex, HaveItemSack& desHaveItemSack, int desIndex);
        static void give2(HaveItemSack& srcHaveItemSack, int srcIndex, HaveStatusInfo& desHaveStatusInfo, int desIndex);
        static void give2(HaveStatusInfo& srcHaveStatusInfo, int srcIndex, HaveStatusInfo& desHaveStatusInfo, int desIndex);
        static int getJudgeMessage(int itemIndex, int index);
    };
}
