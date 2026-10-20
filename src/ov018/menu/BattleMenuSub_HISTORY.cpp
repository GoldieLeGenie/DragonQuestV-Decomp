#include "ov018/menu/BattleMenu.hpp"
#include "ov018/menu/UnkBattleMenuDraw.hpp"
#include "main/menu/MenuStatusInfo.hpp"

using menu::MenuStatusInfo;

THUMB void BattleMenuSub_HISTORY::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::SHIFT_MEMBER_MODE);
    commandChara_ = -1;
    update_ = 1;
    history_ = 1;
    int count = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_CARRIAGE_OUT);
    for (int i = 0; i < count; i++) {
        BattleMenuPlayerControl::getSingleton()->flashStatus(i);
    }
}

THUMB void BattleMenuSub_HISTORY::menuExecute()
{
}

THUMB void BattleMenuSub_HISTORY::menuDraw()
{
    if (history_ != 0) {
        MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
        drawBattleHistory(commandChara_);
    }
}

THUMB void BattleMenuSub_HISTORY::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    int count = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_CARRIAGE_OUT);
    for (int i = 0; i < count; i++) {
        if (BattleMenuPlayerControl::getSingleton()->flashStatus(i)) {
            redraw_ = 1;
        }
    }
    if (update_ != 0) {
        int chara = BattleMenuPlayerControl::getSingleton()->activeChara_;
        for (int i = 0; i < count; i++) {
            if (i == chara) {
                if (BattleMenuPlayerControl::getSingleton()->makePlayerHistory()) {
                    redraw_ = 1;
                }
            } else if (BattleMenuPlayerControl::getSingleton()->resetPlayerHistory(i)) {
                redraw_ = 1;
            }
        }
        if (isRedraw_ != 0) {
            redraw_ = 1;
            isRedraw_ = 0;
        }
    }
}
