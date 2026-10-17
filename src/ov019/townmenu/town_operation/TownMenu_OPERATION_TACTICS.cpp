#pragma ipa file
#include "ov019/townmenu/town_operation/TownMenu_OPERATION_TACTICS.hpp"
#include "ov019/townmenu/town_operation/TownMenu_OPERATION_ROOT.hpp"
#include "ov019/townmenu/UnkMenuTemplateTown.hpp"
#include "ov019/townmenu/UnkTownMenuDraw.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/MenuUpdateAssist.hpp"

using menu::MenuStatusInfo;

THUMB void TownMenu_OPERATION_TACTICS::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    charaItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    tacticsItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_NONE);
    navigator_.setupBase();
    mode_ = 0;
    prevMode_ = 0;
    charaCount_ = 0;
    for (char i = 0; i < MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL); i++) {
        if (MenuStatusInfo::isPlayerType(i, MenuStatusInfo::TYPE_PLAYER) == true && MenuStatusInfo::getPlayerIndex(i) > 1) {
            playerList_[charaCount_] = i;
            charaCount_++;
        }
    }
    playerList_[charaCount_] = -1;
}

THUMB void TownMenu_OPERATION_TACTICS::menuExecute()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    if (mode_ == 0) {
        int active = charaItem_.active_;
        if (charaCount_ < 5) {
            unkfunc_021714a8(&charaItem_, charaCount_ + 1, active, -1, -1);
        } else {
            unkfunc_02171458(&charaItem_, charaCount_ + 1, active, -1, -1);
        }
    } else {
        unkfunc_02171530(&tacticsItem_, tacticsItem_.active_);
    }
}

THUMB void TownMenu_OPERATION_TACTICS::menuDraw()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    int active = charaItem_.active_;
    int chara = playerList_[active];
    if (active == charaCount_) {
        chara = -2;
    }
    if (mode_ == 0) {
        unkfunc_02173720(playerList_, chara);
    } else {
        unkfunc_02173770(playerList_, chara, active);
    }
    charaItem_.drawActive();
    tacticsItem_.drawActive();
}

THUMB void TownMenu_OPERATION_TACTICS::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    if (mode_ == 0) {
        navigator_.setup(5, 2, charaCount_ + 1);
        int result = MenuUpdate_Assist::menuSelect(charaItem_, navigator_);
        if (result != 0) {
            if (result == 3) {
                close();
                gTownMenu_OPERATION_ROOT.open();
            }
            if (result == 2) {
                mode_ = 1;
                unkfunc_02177258();
            }
            redraw_ = 1;
        }
    }
    if (mode_ == 1) {
        navigator_.setup(3, 2, 6);
        int result = MenuUpdate_Assist::menuSelect(tacticsItem_, navigator_);
        if (result != 0) {
            if (result == 2 || result == 3) {
                mode_ = 0;
                if (result == 2) {
                    unkfunc_02177288();
                }
            }
            redraw_ = 1;
        }
    }
    if (prevMode_ != mode_) {
        int charaActive = charaItem_.active_;
        int tacticsActive = tacticsItem_.active_;
        if (mode_ == 0) {
            charaItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
            tacticsItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH, menu::MenuItem::CURSORTYPE_NONE);
        } else {
            charaItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH, menu::MenuItem::CURSORTYPE_NONE);
            tacticsItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
        }
        charaItem_.active_ = charaActive;
        tacticsItem_.active_ = tacticsActive;
        prevMode_ = mode_;
    }
}

THUMB void TownMenu_OPERATION_TACTICS::unkfunc_02177258()
{
    unsigned char tactics;
    if (charaItem_.active_ == charaCount_) {
        tactics = MenuStatusInfo::getPlayerTactics(playerList_[0]);
    } else {
        tactics = MenuStatusInfo::getPlayerTactics(playerList_[charaItem_.active_]);
    }
    tacticsItem_.active_ = tactics;
}

THUMB void TownMenu_OPERATION_TACTICS::unkfunc_02177288()
{
    int tactics[6] = {0, 1, 2, 3, 4, 5};
    int active = tacticsItem_.active_;
    if (charaItem_.active_ == charaCount_) {
        for (int i = 0; playerList_[i] != -1; i++) {
            MenuStatusInfo::setPlayerTactics(playerList_[i], (CommandType)tactics[active]);
        }
    } else {
        MenuStatusInfo::setPlayerTactics(playerList_[charaItem_.active_], (CommandType)tactics[active]);
    }
}
