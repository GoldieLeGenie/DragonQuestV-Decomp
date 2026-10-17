#pragma ipa file
#include "main/script/ScriptBaseCommand.hpp"

// The original TU also emitted ScriptCommand's weak vtable (it is created last in the data layout).
// Our headers keep it external, so this dead-stripped stand-in recreates a vtable of the same size.
struct ScriptCommandWeakVtable : ScriptCommand {
    virtual void initialize(char* scriptParam);
    virtual int isEnd();
};

#include "ov001/script/ScriptMeisanhinCommand.hpp"
#include "ov019/materielmenu/MaterielMenu_WINDOW_MANAGER.hpp"
#include "main/window/ShopMenuControl.hpp"
#include "main/script/CommandParam.hpp"
#include "main/global/Global.hpp"
#include "main/status/GameFlag.hpp"
#include "main/status/MuseumStatus.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/PlayerData.hpp"
#include "main/status/UseItem.hpp"

#pragma thumb on

inline status::HaveItem& status::HaveStatusInfo::getHaveItem()
{
    return haveItem_;
}

inline ScriptCommand::ScriptCommand()
{
}

inline ScriptCommand::~ScriptCommand()
{
}

inline void ScriptCommandWeakVtable::initialize(char* scriptParam)
{
}

inline int ScriptCommandWeakVtable::isEnd()
{
    return 0;
}

inline void window::ShopMenuControl::startMenu(int menuType)
{
    menuType_ = menuType;
    state_ = 7;
}

inline bool window::ShopMenuControl::isMenuEnd()
{
    return state_ == 8;
}

inline void MaterielMenu_WINDOW_MANAGER::setOpenMenuForScript(bool flag)
{
    editMessageForScript_ = flag;
}

inline int status::MuseumStatus::getPenaltyPoint()
{
    return penaltyPoint_;
}

inline status::MuseumItemStatus& status::MuseumStatus::getMuseumItemStatus(int index)
{
    return museumitem_[index];
}

inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo()
{
    return haveStatusInfo_;
}

inline status::HaveItem& status::PlayerData::getHaveItem()
{
    return haveItem_;
}

inline int status::PartyStatusUtility::getSeparatePlayer(int no)
{
    return separatePlayer_[no];
}

inline void SetMeisanhinItem::execute()
{
}

bool cmdCheckMuseumLevel(void* scriptParam)
{
    PARAM_CHECK_MUSEUM_LEVEL* param = (PARAM_CHECK_MUSEUM_LEVEL*)scriptParam;
    int museumLevel = status::g_MuseumStatus.getMuseumLevel();
    bool ret;
    status::MUSEUMTREND trand = status::g_MuseumStatus.getMuseumTrend();
    ret = false;
    switch (param->level) {
    case 0:
        if (museumLevel == 1) {
            ret = true;
        }
        break;
    case 1:
        if (museumLevel == 2) {
            ret = true;
        }
        break;
    case 2:
        if (museumLevel == 3) {
            ret = true;
        }
        break;
    case 3:
        if (museumLevel == 4) {
            ret = true;
        }
        break;
    case 4:
        if (trand == status::MUSEUMTREND_BEAUTIFUL && museumLevel == 5) {
            ret = true;
        }
        break;
    case 5:
        if (trand == status::MUSEUMTREND_FUNNY && museumLevel == 5) {
            ret = true;
        }
        break;
    case 6:
        if (trand == status::MUSEUMTREND_FEAR && museumLevel == 5) {
            ret = true;
        }
        break;
    }
    return ret;
}

bool cmdCheckMeisanCount(void* scriptParam)
{
    PARAM_CHECK_MEISAN_COUNT* param = (PARAM_CHECK_MEISAN_COUNT*)scriptParam;
    int museumF1 = status::g_MuseumStatus.getFloorItemCount(status::MUSEUMFLOOR_F1);
    int museumF2 = status::g_MuseumStatus.getFloorItemCount(status::MUSEUMFLOOR_F2);
    int museumF3 = status::g_MuseumStatus.getFloorItemCount(status::MUSEUMFLOOR_F3);
    int museumB1 = status::g_MuseumStatus.getFloorItemCount(status::MUSEUMFLOOR_B1);
    int museumS1 = status::g_MuseumStatus.getFloorItemCount(status::MUSEUMFLOOR_S1);
    int museumS2 = status::g_MuseumStatus.getFloorItemCount(status::MUSEUMFLOOR_S2);
    int itemCount = 0;
    switch (param->floor) {
    case 0:
        itemCount = museumF1 + museumF2 + museumF3 + museumB1 + museumS2;
        break;
    case 1:
        itemCount = museumF1 + museumF2 + museumF3 + museumB1;
        break;
    case 2:
        itemCount = museumF1 + museumF2 + museumF3;
        break;
    case 3:
        itemCount = museumS2;
        break;
    case 4:
        itemCount = museumB1;
        break;
    case 5:
        itemCount = museumF1;
        break;
    case 6:
        itemCount = museumF2;
        break;
    case 7:
        itemCount = museumF3;
        break;
    case 8:
        itemCount = museumS1;
        break;
    }
    if (param->condition == 0 && itemCount >= param->count) {
        return true;
    }
    if (param->condition == 1 && itemCount <= param->count) {
        return true;
    }
    if (param->condition == 2 && itemCount == param->count) {
        return true;
    }
    return false;
}

bool cmdCheckSpecialMuseum(void* scriptParam)
{
    PARAM_CHECK_SPECIAL_MUSEUM* param = (PARAM_CHECK_SPECIAL_MUSEUM*)scriptParam;
    bool bottl = status::g_MuseumStatus.isFloorItemSame(0xe3);
    bool sabaku = status::g_MuseumStatus.isFloorItemSame(0xea);
    bool choko = status::g_MuseumStatus.isFloorItemSame(0xeb);
    bool result = false;
    switch (param->special) {
    case 0:
        result = bottl;
        break;
    case 1:
        result = sabaku;
        break;
    case 2:
        result = choko;
        break;
    case 3:
        if (!bottl && !sabaku && !choko) {
            result = true;
        }
        break;
    }
    return result;
}

bool cmdCheckMeisanhin(void* scriptParam)
{
    PARAM_CHECK_MEISANHIN* param = (PARAM_CHECK_MEISANHIN*)scriptParam;
    int isMeisanF1 = status::g_MuseumStatus.getFloorItemCount(status::MUSEUMFLOOR_F1, param->meisanhin);
    int isMeisanF2 = status::g_MuseumStatus.getFloorItemCount(status::MUSEUMFLOOR_F2, param->meisanhin);
    int isMeisanF3 = status::g_MuseumStatus.getFloorItemCount(status::MUSEUMFLOOR_F3, param->meisanhin);
    int isMeisanB1 = status::g_MuseumStatus.getFloorItemCount(status::MUSEUMFLOOR_B1, param->meisanhin);
    int isMeisanS1 = status::g_MuseumStatus.getFloorItemCount(status::MUSEUMFLOOR_S1, param->meisanhin);
    int isMeisanS2 = status::g_MuseumStatus.getFloorItemCount(status::MUSEUMFLOOR_S2, param->meisanhin);
    int isMeisan = false;
    switch (param->floor) {
    case 0:
        if (isMeisanF1 + isMeisanF2 + isMeisanF3 + isMeisanB1 + isMeisanS2 > 0) {
            isMeisan = true;
        }
        break;
    case 1:
        if (isMeisanF1 + isMeisanF2 + isMeisanF3 + isMeisanB1 > 0) {
            isMeisan = true;
        }
        break;
    case 2:
        if (isMeisanF1 + isMeisanF2 + isMeisanF3 > 0) {
            isMeisan = true;
        }
        break;
    case 3:
        if (isMeisanS2 > 0) {
            isMeisan = true;
        }
        break;
    case 4:
        if (isMeisanB1 > 0) {
            isMeisan = true;
        }
        break;
    case 5:
        if (isMeisanF1 > 0) {
            isMeisan = true;
        }
        break;
    case 6:
        if (isMeisanF2 > 0) {
            isMeisan = true;
        }
        break;
    case 7:
        if (isMeisanF3 > 0) {
            isMeisan = true;
        }
        break;
    case 8:
        if (isMeisanS1 > 0) {
            isMeisan = true;
        }
        break;
    }
    if (param->condition == !isMeisan) {
        return true;
    }
    return false;
}

bool cmdCheckPenaltyPoint(void* scriptParam)
{
    PARAM_CHECK_PENALTY_POINT* param = (PARAM_CHECK_PENALTY_POINT*)scriptParam;
    int penalty = dss::abs(status::g_MuseumStatus.getPenaltyPoint());
    if (param->type == 0 && penalty >= param->min) {
        return true;
    }
    if (param->type == 1 && penalty < param->min) {
        return true;
    }
    if (param->type == 2 && penalty >= param->min && penalty <= param->max) {
        return true;
    }
    return false;
}

bool cmdStartSurechigaiParty(void* scriptParam)
{
    g_Global.startSurechigai();
    return true;
}

bool cmdIsCompleteMeisanhin(void* scriptParam)
{
    if (g_AreaFlag.check(0x52) == false) {
        return false;
    }
    if (g_AreaFlag.check(0x65) == false) {
        return false;
    }
    if (g_AreaFlag.check(0x87) == false) {
        return false;
    }
    if (g_AreaFlag.check(0x94) == false) {
        return false;
    }
    if (g_AreaFlag.check(0xc2) == false) {
        return false;
    }
    if (g_AreaFlag.check(0xc9) == false) {
        return false;
    }
    if (g_AreaFlag.check(0x2d6) == false) {
        return false;
    }
    if (g_AreaFlag.check(0xd0) == false) {
        return false;
    }
    if (g_AreaFlag.check(0xd2) == false) {
        return false;
    }
    if (g_AreaFlag.check(0x12c) == false) {
        return false;
    }
    if (g_AreaFlag.check(0x2c4) == false) {
        return false;
    }
    if (g_AreaFlag.check(0x131) == false) {
        return false;
    }
    if (g_AreaFlag.check(0x2d7) == false) {
        return false;
    }
    if (g_AreaFlag.check(0x134) == false) {
        return false;
    }
    if (g_AreaFlag.check(0x100) == false) {
        return false;
    }
    if (g_AreaFlag.check(0x108) == false) {
        return false;
    }
    if (g_AreaFlag.check(0x2d5) == false) {
        return false;
    }
    if (g_AreaFlag.check(0x116) == false) {
        return false;
    }
    if (g_AreaFlag.check(0x15f) == false) {
        return false;
    }
    if (g_AreaFlag.check(0x173) == false) {
        return false;
    }
    if (g_AreaFlag.check(0x170) == false) {
        return false;
    }
    if (g_AreaFlag.check(0x16e) == false) {
        return false;
    }
    if (g_AreaFlag.check(0x188) == false) {
        return false;
    }
    if (g_AreaFlag.check(0x233) == false) {
        return false;
    }
    if (g_AreaFlag.check(0x19c) == false) {
        return false;
    }
    if (g_AreaFlag.check(0x1e5) == false) {
        return false;
    }
    if (g_AreaFlag.check(0x1ec) == false) {
        return false;
    }
    if (g_AreaFlag.check(0x228) == false) {
        return false;
    }
    return true;
}

bool cmdCheckMeisanhinCount(void* scriptParam)
{
    PARAM_CHECK_MEISANHIN_COUNT* param = (PARAM_CHECK_MEISANHIN_COUNT*)scriptParam;
    status::g_Party.setAllPlayerMode();
    int itemCount, meisanCount = 0;
    int partyCount = status::g_Party.getCount();
    for (int i = 0; i < partyCount; i++) {
        status::HaveItem& item = status::g_Party.getPlayerStatus(i).getHaveStatusInfo().getHaveItem();
        itemCount = item.getCount();
        for (int j = 0; j < itemCount; j++) {
            if (status::UseItem::getItemType(item.getItem(j)) == ITEM_SPECIALTY) {
                meisanCount++;
            }
        }
    }
    status::HaveItemSack& sack = status::g_Party.haveItemSack_;
    itemCount = sack.getCount();
    for (int i = 0; i < itemCount; i++) {
        if (status::UseItem::getItemType(sack.getItem(i)) == ITEM_SPECIALTY) {
            meisanCount++;
        }
    }
    if (param->type == 0 && meisanCount >= param->min) {
        return true;
    }
    if (param->type == 1 && meisanCount < param->min) {
        return true;
    }
    if (param->type == 2 && meisanCount >= param->min && meisanCount <= param->max) {
        return true;
    }
    return false;
}

bool cmdCheckLevel3Meisanhin(void* scriptParam)
{
    PARAM_CHECK_LEVEL3_MEISANHIN* param = (PARAM_CHECK_LEVEL3_MEISANHIN*)scriptParam;
    int level3[8] = {
        status::g_MuseumStatus.getFloorItemCount(status::MUSEUMFLOOR_B1, 0xdd),
        status::g_MuseumStatus.getFloorItemCount(status::MUSEUMFLOOR_B1, 0xe0),
        status::g_MuseumStatus.getFloorItemCount(status::MUSEUMFLOOR_B1, 0xe2),
        status::g_MuseumStatus.getFloorItemCount(status::MUSEUMFLOOR_B1, 0xec),
        status::g_MuseumStatus.getFloorItemCount(status::MUSEUMFLOOR_B1, 0xf1),
        status::g_MuseumStatus.getFloorItemCount(status::MUSEUMFLOOR_B1, 0xf3),
        status::g_MuseumStatus.getFloorItemCount(status::MUSEUMFLOOR_B1, 0xf9),
        status::g_MuseumStatus.getFloorItemCount(status::MUSEUMFLOOR_B1, 0xfa),
    };
    bool putinMeisan = false;
    for (int i = 0; i < 8; i++) {
        if (level3[i] == 1) {
            putinMeisan = true;
        }
    }
    if (putinMeisan == true && param->flag == 0) {
        return true;
    }
    if (putinMeisan == false && param->flag == 1) {
        return true;
    }
    return false;
}

bool cmdLevelUpLocket(void* scriptParam)
{
    int museumItemStatusID = status::g_MuseumStatus.findMuseumItemStatusForItemID(0xf8);
    if (museumItemStatusID != -1) {
        status::g_MuseumStatus.getMuseumItemStatus(museumItemStatusID).setIconIDandRedraw(0xf9);
    } else {
        status::g_Party.setAllPlayerMode();
        int count = status::g_Party.getCount();
        for (int i = 0; i < count; i++) {
            status::HaveItem& item = status::g_Party.getPlayerStatus(i).getHaveStatusInfo().getHaveItem();
            int itemCount = item.getCount();
            for (int j = 0; j < itemCount; j++) {
                if (item.getItem(j) == 0xf8) {
                    item.del(j);
                    item.add(0xf9);
                    return true;
                }
            }
        }
        if (status::PartyStatusUtility::separateFlag_ == 1) {
            int count = 0;
            while (status::PartyStatusUtility::getSeparatePlayer(count) != -1) {
                int index = status::PartyStatusUtility::getSeparatePlayer(count);
                status::HaveItem& item = status::PlayerDataAll::playerData_[index].getHaveItem();
                int itemCount = item.getCount();
                for (int i = 0; i < itemCount; i++) {
                    if (item.getItem(i) == 0xf8) {
                        item.del(i);
                        item.add(0xf9);
                        return true;
                    }
                }
                count++;
                if (count >= 10) {
                    break;
                }
            }
        }
        status::HaveItemSack& sack = status::g_Party.haveItemSack_;
        int itemCount = sack.getCount();
        for (int i = 0; i < itemCount; i++) {
            if (sack.getItem(i) == 0xf8) {
                sack.execThrow(i);
                sack.add(0xf9);
                return true;
            }
        }
    }
    return false;
}

bool cmdUpdateMuseumLevel(void* scriptParam)
{
    status::g_MuseumStatus.updateMuseum();
    return true;
}

void SetMeisanhinItem::initialize(char* scriptParam)
{
    window::gShopMenuControl.startMenu(0x29);
    MaterielMenu_WINDOW_MANAGER::getSingleton()->setOpenMenuForScript(true);
}

int SetMeisanhinItem::isEnd()
{
    if (window::gShopMenuControl.isMenuEnd()) {
        MaterielMenu_WINDOW_MANAGER::getSingleton()->setOpenMenuForScript(false);
        return true;
    }
    return false;
}

SetMeisanhinItem gSetMeisanhinItem;

void ScriptMeisanhinCommand_weakVtable()
{
    ScriptCommandWeakVtable unused;
}
