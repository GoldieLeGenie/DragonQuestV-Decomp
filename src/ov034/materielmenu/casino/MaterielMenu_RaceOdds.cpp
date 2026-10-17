#include "ov034/materielmenu/casino/MaterielMenu_RaceOdds.hpp"
#include "ov003/slimerace/SlimeRace.hpp"
#include "ov019/materielmenu/MenuTemplate_materiel.hpp"
#include "ov019/materielmenu/UnkMaterielMenuWindowDraw.hpp"
#include "main/dss/Pad.hpp"
#include "main/menu/RaceData.hpp"
#include "main/status/PartyStatus.hpp"

inline unsigned char RaceData::getPaddock()
{
    return slimeNum_;
}

inline bool RaceData::isLookOnly()
{
    return look_;
}

inline unsigned int RaceData::getBetCoin()
{
    return betCoin_;
}

inline unsigned int status::BasePartyStatus::getCasinoCoin()
{
    return casinoCoin_;
}

inline void menu::MenuItem::setSEenable(bool flag)
{
    enableSE_ = flag;
}

inline void menu::MenuItem::resetResult()
{
    result_ = 0;
    lastresult_ = 0;
}

THUMB void MaterielMenu_RaceOdds::menuSetup()
{
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    menuItem_.setSEenable(false);
    if (g_RaceData.getPaddock() == 5) {
        maxToken_ = 10;
        menuItemY_ = 6;
        uniqueItem_ = 4;
    } else {
        maxToken_ = 15;
        menuItemY_ = 8;
        uniqueItem_ = 5;
    }
    int* odds = unkfunc_02130878();
    for (int i = 0; i < maxToken_; i++) {
        if (*odds == 0) {
            odds++;
        }
        g_RaceData.oddsData_[i].odds = *odds;
        odds++;
    }
    navigator_.setup(2, menuItemY_, maxToken_ + 1);
    unk_28 = 0;
    unk_2c = 0;
    unk_a4 = 0;
    mode_ = MODE_STANDBY;
    if (g_RaceData.isLookOnly()) {
        mode_ = MODE_READY;
    }
}

THUMB void MaterielMenu_RaceOdds::menuExecute()
{
    if (mode_ == MODE_STANDBY) {
        if (g_RaceData.getPaddock() == 5) {
            menu::MenuTemplate_materiel::unkfunc_0217d5a8(&menuItem_, maxToken_ + 1);
        } else {
            menu::MenuTemplate_materiel::unkfunc_0217d60c(&menuItem_, maxToken_ + 1);
        }
    }
}

THUMB void MaterielMenu_RaceOdds::menuDraw()
{
    switch (mode_) {
        case MODE_STANDBY:
            unkfunc_0217c1e0(g_RaceData.getPaddock(), 0);
            menuItem_.drawActive();
            break;
        case MODE_START:
            unkfunc_0217c1e0(g_RaceData.getPaddock(), 1);
            break;
        case MODE_RESULT:
            unkfunc_0217c2a4();
            unkfunc_0217c1e0(g_RaceData.getPaddock(), 1);
            break;
    }
}

THUMB void MaterielMenu_RaceOdds::menuUpdate()
{
    if (mode_ == MODE_STANDBY) {
        navigator_.setup(2, menuItemY_, maxToken_ + 1);
        commandUpdate();
    }
    if (mode_ == MODE_READY) {
        if (unkfunc_02130860() == 3) {
            mode_ = MODE_START;
            redraw_ = 1;
        }
    }
    if (mode_ == MODE_RESULT) {
        if (dss::g_Pad.edge() == 1) {
            mode_ = MODE_ESCAPE;
            redraw_ = 1;
        }
    }
}

THUMB void MaterielMenu_RaceOdds::commandUpdate()
{
    if (unkfunc_02186d18()) {
        return;
    }
    unk_28 = 0;
    unk_2c = 0;
    int active = menuItem_.active_;
    int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
    if (result == 0) {
        return;
    }
    unkfunc_02186cd8(active, result);
    if (result == 2) {
        if (unkfunc_02186e28()) {
            if (g_RaceData.getBetCoin() == 0) {
                menuItem_.resetResult();
                return;
            }
            for (int i = 0; i < maxToken_; i++) {
                int* bets = unkfunc_02130884();
                bets[i] = g_RaceData.oddsData_[i].coin;
            }
            unkfunc_0213086c(1);
            mode_ = MODE_READY;
        } else if (betCoin()) {
            unk_28 = 1;
        }
        redraw_ = 1;
    }
    if (result == 3) {
        if (!unkfunc_02186e28()) {
            if (backCoin()) {
                unk_28 = 2;
            }
            redraw_ = 1;
        }
    }
    menuItem_.resetResult();
}

THUMB void MaterielMenu_RaceOdds::unkfunc_02186cd8(int active, int result)
{
    int cursor = menuItem_.active_;
    if (g_RaceData.getPaddock() == 6) {
        return;
    }
    if (active == 8 && cursor == active + 1) {
        menuItem_.active_ = active - 1;
    }
    if (active == 10 && (result == 6 || result == 7)) {
        menuItem_.active_ = active - 1;
    }
    if (active == 9 && cursor == active - 1) {
        menuItem_.active_ = active + 1;
    }
}

THUMB bool MaterielMenu_RaceOdds::unkfunc_02186d18()
{
    unsigned int coin = status::g_Party.getCasinoCoin();
    switch (unk_28) {
        case 1:
            if (dss::g_Pad.pad() == 1) {
                if (unk_2c >= 30) {
                    if (coin == 0 || !betCoin()) {
                        break;
                    }
                    unk_2c--;
                    redraw_ = 1;
                } else {
                    unk_2c++;
                }
                return true;
            }
            break;
        case 2:
            if (dss::g_Pad.pad() == 2) {
                if (unk_2c >= 30) {
                    if (!backCoin()) {
                        break;
                    }
                    unk_2c--;
                    redraw_ = 1;
                } else {
                    unk_2c++;
                }
                return true;
            }
            break;
    }
    return false;
}

THUMB bool MaterielMenu_RaceOdds::betCoin()
{
    unsigned int coin = status::g_Party.getCasinoCoin();
    if (coin == 0) {
        return false;
    }
    int active = menuItem_.active_;
    if (g_RaceData.betCoin(active / 2 + menuItemY_ * (active % 2))) {
        status::g_Party.setCasinoCoin(coin - 1);
        return true;
    }
    return false;
}

THUMB bool MaterielMenu_RaceOdds::backCoin()
{
    unsigned int coin = status::g_Party.getCasinoCoin();
    int active = menuItem_.active_;
    if (g_RaceData.delCoin(active / 2 + menuItemY_ * (active % 2))) {
        status::g_Party.setCasinoCoin(coin + 1);
        return true;
    }
    return false;
}

THUMB bool MaterielMenu_RaceOdds::unkfunc_02186e28()
{
    if (g_RaceData.getPaddock() == 5) {
        if (menuItem_.active_ == 9) {
            return true;
        }
    } else if (menuItem_.active_ == 15) {
        return true;
    }
    return false;
}
