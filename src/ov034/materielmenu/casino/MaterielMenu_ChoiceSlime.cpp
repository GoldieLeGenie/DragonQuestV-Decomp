#include "ov034/materielmenu/casino/MaterielMenu_ChoiceSlime.hpp"
#include "ov034/materielmenu/casino/MaterielMenu_RaceEntrance.hpp"
#include "ov019/materielmenu/MaterielMenu_WINDOW_MANAGER.hpp"
#include "ov019/materielmenu/MenuTemplate_materiel.hpp"
#include "ov019/materielmenu/UnkMaterielMenuWindowDraw.hpp"
#include "main/global/Global.hpp"
#include "main/leveldata/CharacterInitData.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/RaceData.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/PlayerStatus.hpp"
#include "main/text/TextAPI.hpp"

using menu::MenuStatusInfo;

inline unsigned int status::BasePartyStatus::getCasinoCoin()
{
    return casinoCoin_;
}

inline unsigned int status::BasePartyStatus::getGold()
{
    return gold_;
}

inline int Global::getMapNameId()
{
    return nextMapNameId;
}

inline void RaceData::setRaceMapId(int id)
{
    raceMap_ = id;
}

inline int RaceData::getSlimeNumber()
{
    return monsterNumber_;
}

inline dq5::level::CharacterInitData* dq5::level::CharacterInitData::getRecord(int index)
{
    return (CharacterInitData*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned short dq5::level::CharacterInitData::getMonsterID()
{
    return monsterID;
}

inline int status::HaveStatus::getPlayerKindIndex() const
{
    return playerKindIndex_;
}

inline int status::HaveStatus::getLevel() const
{
    return level_;
}

inline void menu::MenuItem::resetResult()
{
    result_ = 0;
    lastresult_ = 0;
}

THUMB void MaterielMenu_ChoiceSlime::menuSetup()
{
    mode_ = MODE_START_MSG;
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    yesno_ = 0;
    charaNum_ = 0;
}

THUMB void MaterielMenu_ChoiceSlime::menuExecute()
{
    if (mode_ == MODE_SELECT) {
        MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
        menu::MenuTemplate_materiel::MATERIEL_CHOICE_SLIME(&menuItem_, MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_CARRIAGE_OUT));
    }
}

THUMB void MaterielMenu_ChoiceSlime::menuDraw()
{
    if (mode_ == MODE_SELECT) {
        menuItem_.drawActive();
        drawChoiceSlimeScreen(charaNum_);
    }
    drawCoinsAndGold(status::g_Party.getCasinoCoin(), status::g_Party.getGold());
}

THUMB void MaterielMenu_ChoiceSlime::menuUpdate()
{
    if (messageUpdate()) {
        commandUpdate();
    }
}

THUMB bool MaterielMenu_ChoiceSlime::messageUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    int stat = gTownMenu_MESSAGE.stat_;
    int index = g_RaceData.getSlimeNumber();
    int openFlag = gTownMenu_MESSAGE.isOpen();
    if (openFlag && !gTownMenu_MESSAGE.isMessageWAITPROG() && !yesno_) {
        if (stat == MENUBASE_STAT_OK || stat == MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
        }
        return false;
    }
    TextAPI::setMACRO0(0x12, 0x50000000, index);
    switch (mode_) {
        case MODE_START_MSG:
            gTownMenu_MESSAGE.openMessageForTALK();
            gTownMenu_MESSAGE.addMessageNOWAIT(0xc9aba);
            gTownMenu_MESSAGE.addMessageWAITKEY();
            mode_ = MODE_SELECT;
            break;
        case MODE_NOT_SLIME:
            setMessage(0xc9abd, -1);
            mode_ = MODE_START_MSG;
            break;
        case MODE_CHILD_SLIME:
            setMessage(0xc9ac0, 0xc9ac1);
            mode_ = MODE_RESTART;
            break;
        case MODE_TIRED_SLIME:
            setMessage(0xc9ac4, 0xc9ac5);
            mode_ = MODE_RESTART;
            break;
        case MODE_IS_ACCEPT:
            if (!openFlag) {
                setYesNoMessage(0xc9ac8, -1);
                break;
            }
            if (stat == MENUBASE_STAT_OK) {
                yesno_ = 0;
                gTownMenu_MESSAGE.close();
                return true;
            }
            if (stat == MENUBASE_STAT_CANCEL) {
                yesno_ = 0;
                gTownMenu_MESSAGE.close();
                mode_ = MODE_RESTART;
            }
            break;
        case MODE_ACCEPT:
            if (!openFlag) {
                setYesNoMessage(0xc9ace, 0xc9acf);
                break;
            }
            if (stat == MENUBASE_STAT_OK) {
                yesno_ = 0;
                gTownMenu_MESSAGE.close();
                return true;
            }
            if (stat == MENUBASE_STAT_CANCEL) {
                yesno_ = 0;
                gTownMenu_MESSAGE.close();
                mode_ = MODE_LOOK_ONLY;
            }
            break;
        case MODE_NOT_MONEY:
            setMessage(0xc9acb, -1);
            mode_ = MODE_RESTART;
            break;
        case MODE_NOT_COIN:
            setMessage(0xc9ad2, -1);
            mode_ = MODE_LOOK_ONLY;
            break;
        case MODE_LOOK_ONLY:
            if (!openFlag) {
                setYesNoMessage(0xc9ad3, -1);
                break;
            }
            if (stat == MENUBASE_STAT_OK) {
                yesno_ = 0;
                gTownMenu_MESSAGE.close();
                g_RaceData.setSlimeMode();
                mode_ = MODE_IN_RACE;
            }
            if (stat == MENUBASE_STAT_CANCEL) {
                yesno_ = 0;
                gTownMenu_MESSAGE.close();
                mode_ = MODE_RESTART;
            }
            break;
        case MODE_RESTART:
        case MODE_CANCEL:
            return true;
        case MODE_IN_RACE:
            setMessage(0xc9ad6, -1);
            mode_ = MODE_RACE;
            break;
        case MODE_RACE:
            return true;
        case MODE_SELECT:
            return true;
        case MODE_END:
            return true;
    }
    return false;
}

THUMB void MaterielMenu_ChoiceSlime::commandUpdate()
{
    switch (mode_) {
        case MODE_SELECT:
            if (gTownMenu_MESSAGE.isMessageWAITPROG()) {
                selectUpdate();
            }
            break;
        case MODE_IS_ACCEPT:
            if (status::g_Party.getGold() >= 50) {
                mode_ = MODE_ACCEPT;
            } else {
                mode_ = MODE_NOT_MONEY;
            }
            break;
        case MODE_ACCEPT:
            if (status::g_Party.getCasinoCoin() != 0) {
                close();
                g_RaceData.setDoubleBetMode();
                gMaterielMenu_RaceEntrance.open();
                gMaterielMenu_RaceEntrance.mode_ = MaterielMenu_RaceEntrance::MODE_IN_RACE;
            } else {
                mode_ = MODE_NOT_COIN;
            }
            break;
        case MODE_RESTART:
        case MODE_CANCEL:
            close();
            gMaterielMenu_RaceEntrance.open();
            gMaterielMenu_RaceEntrance.mode_ = MaterielMenu_RaceEntrance::MODE_RESTART;
            break;
        case MODE_RACE:
            raceStart();
            break;
        case MODE_END:
            close();
            break;
    }
}

THUMB void MaterielMenu_ChoiceSlime::selectUpdate()
{
    status::g_Party.setPlayerMode();
    int result = menuItem_.execInput();
    int member = status::g_Party.getCarriageOutCount();
    switch (result) {
        case menu::MenuItem::MENUITEM_RESULT_OK:
            gTownMenu_MESSAGE.clearMessageWAITPROG();
            gTownMenu_MESSAGE.close();
            checkSlime();
            break;
        case menu::MenuItem::MENUITEM_RESULT_CANCEL:
            gTownMenu_MESSAGE.clearMessageWAITPROG();
            gTownMenu_MESSAGE.close();
            mode_ = MODE_CANCEL;
            break;
        case menu::MenuItem::MENUITEM_RESULT_LEFT:
            if (menuItem_.active_ == 0) {
                menuItem_.active_ = member - 1;
            }
            break;
        case menu::MenuItem::MENUITEM_RESULT_RIGHT:
            if (member - 1 == menuItem_.active_) {
                menuItem_.active_ = 0;
            }
            break;
    }
    if (result != 0) {
        redraw_ = 1;
    }
    menuItem_.resetResult();
    charaNum_ = menuItem_.active_;
}

THUMB void MaterielMenu_ChoiceSlime::checkSlime()
{
    status::g_Party.setPlayerMode();
    int member = status::g_Party.getCarriageOutCount();
    status::HaveStatusInfo& statusInfo = status::g_Party.getPlayerStatus(charaNum_).haveStatusInfo_;
    mode_ = MODE_IS_ACCEPT;
    int index = statusInfo.haveStatus_.getPlayerKindIndex();
    if (dq5::level::CharacterInitData::getRecord(index)->getMonsterID() != 0xde) {
        mode_ = MODE_NOT_SLIME;
    } else if (statusInfo.haveStatus_.getLevel() < 20) {
        mode_ = MODE_CHILD_SLIME;
    } else if (statusInfo.getHp() != statusInfo.getHpMax() || statusInfo.getMp() != statusInfo.getMpMax()) {
        mode_ = MODE_TIRED_SLIME;
    }
    g_RaceData.monsterNumber_ = MenuStatusInfo::getPlayerIndex(charaNum_);
}

THUMB void MaterielMenu_ChoiceSlime::raceStart()
{
    g_RaceData.setRaceMapId(g_Global.getMapNameId());
    g_Global.startSlimeRace();
    close();
    MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
}

THUMB void MaterielMenu_ChoiceSlime::setMessage(int mes1, int mes2)
{
    gTownMenu_MESSAGE.openMessageForTALK();
    if (mes2 == -1) {
        gTownMenu_MESSAGE.addMessage(mes1);
    } else {
        gTownMenu_MESSAGE.addMessage(mes1, mes2);
    }
}

THUMB void MaterielMenu_ChoiceSlime::setYesNoMessage(int mes1, int mes2)
{
    gTownMenu_MESSAGE.openMessageForTALK();
    if (mes2 == -1) {
        gTownMenu_MESSAGE.addMessage(mes1);
    } else {
        gTownMenu_MESSAGE.addMessage(mes1, mes2);
    }
    gTownMenu_MESSAGE.setYesNo();
    yesno_ = 1;
}
