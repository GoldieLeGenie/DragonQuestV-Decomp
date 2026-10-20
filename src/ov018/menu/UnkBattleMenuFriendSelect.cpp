#include "ov018/menu/BattleMenu.hpp"
#include "ov018/menu/UnkBattleMenuDraw.hpp"
#include "ov000/status/MonsterParty.hpp"
#include "main/leveldata/MonsterData.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/MenuUpdateAssist.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/menu/UnkMenuTemplate.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/PlayerData.hpp"
#include "main/status/PlayerStatus.hpp"

using menu::MenuStatusInfo;

inline unsigned char dq5::level::MonsterData::getParty() { return party; }
inline dq5::level::MonsterData* dq5::level::MonsterData::getRecord(int index)
{
    return (MonsterData*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}
inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo() { return haveStatusInfo_; }
inline status::HaveStatus& status::HaveStatusInfo::getHaveStatus() { return haveStatus_; }

THUMB void UnkBattleMenuFriendSelect::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_AND_CARRIAGE_MODE);
    unk_28 = 1;
    int count = status::g_Party.getCarriageOutCount() + status::g_Party.getCarriageCount();
    for (int i = 0; i < count; i++) {
        if (status::g_Party.getPlayerStatus(i).getHaveStatusInfo().getHaveStatus().playerType_ == status::HaveStatus::TYPE_FRIENDMONSTER) {
            unk_28++;
        }
    }
    unk_4c = 0;
    unk_50 = 0;
    unk_54 = 0;
    for (int i = 0; i < 8; i++) {
        unk_2c[i] = -1;
    }
    unk_1c = status::g_Monster.getPartyMonster();
    unk_20 = dq5::level::MonsterData::getRecord(unk_1c)->getParty();
    unk_24 = status::PlayerDataAll::getNextAddFriendMonster(unk_20);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    menuItem_.active_ = 0;
    navigator_.setupBase();
    navigator_.setup(5, 1, unk_28);
    unk_58 = 0;
    BattleMenuPlayerControl::getSingleton()->activeChara_ = 0;
}

THUMB void UnkBattleMenuFriendSelect::menuExecute()
{
    setupCharaRowLayout5x1(&menuItem_, navigator_.getCountInPage(), menuItem_.active_);
}

THUMB void UnkBattleMenuFriendSelect::menuDraw()
{
    if (gTownMenu_MESSAGE.isOpen() != true) {
        int page = navigator_.getPageNo();
        int max = navigator_.getPageMaxCount() - 1;
        drawFriendSelectMenu(page, max, unk_24);
        menuItem_.drawActive();
    }
}

THUMB void UnkBattleMenuFriendSelect::menuUpdate()
{
    unkfunc_021713c4();
}

THUMB void UnkBattleMenuFriendSelect::unkfunc_021713c4()
{
    navigator_.setup(5, 1, unk_28);
    int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
    if (result != 0) {
        int active = menuItem_.active_;
        unk_4c = active + navigator_.getPageNo() * 5;
        if (result == 3) {
            unk_50 = 1;
        }
        if (result == 2) {
            unk_54 = 1;
        }
        int chara = unk_4c;
        BattleMenuPlayerControl::getSingleton()->activeChara_ = chara;
        redraw_ = 1;
    }
}
