#include "ov034/materielmenu/casino/MaterielMenu_RaceEntrance.hpp"
#include "ov034/materielmenu/casino/MaterielMenu_ChoiceSlime.hpp"
#include "ov019/materielmenu/MaterielMenu_WINDOW_MANAGER.hpp"
#include "ov019/materielmenu/MenuTemplate_materiel.hpp"
#include "ov019/materielmenu/UnkMaterielMenuWindowDraw.hpp"
#include "main/global/Global.hpp"
#include "main/leveldata/CharacterInitData.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/RaceData.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/menu/UiMsg.hpp"
#include "main/status/PartyStatus.hpp"

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

inline dq5::level::CharacterInitData* dq5::level::CharacterInitData::getRecord(int index)
{
    return (CharacterInitData*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned short dq5::level::CharacterInitData::getMonsterID()
{
    return monsterID;
}

inline void menu::MenuItem::resetResult()
{
    result_ = 0;
    lastresult_ = 0;
}

THUMB void MaterielMenu_RaceEntrance::menuSetup()
{
    mode_ = MODE_START_MSG;
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    ui_MsgSndSet(0x32);
}

THUMB void MaterielMenu_RaceEntrance::menuExecute()
{
    if (mode_ == MODE_SELECT) {
        menu::MenuTemplate_materiel::MATERIEL_RACE_ENTRANCE(&menuItem_);
    }
}

THUMB void MaterielMenu_RaceEntrance::menuDraw()
{
    if (mode_ == MODE_SELECT) {
        menuItem_.drawActive();
        drawRaceEntranceCommands();
    }
    drawCoinsAndGold(status::g_Party.getCasinoCoin(), status::g_Party.getGold());
}

THUMB void MaterielMenu_RaceEntrance::menuUpdate()
{
    if (messageUpdate()) {
        commandUpdate();
    }
}

THUMB bool MaterielMenu_RaceEntrance::messageUpdate()
{
    if (gTownMenu_MESSAGE.isOpen() && !gTownMenu_MESSAGE.isMessageWAITPROG()) {
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK || stat == MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
        }
        return false;
    }
    switch (mode_) {
        case MODE_START_MSG:
            g_RaceData.cleanUp();
            gTownMenu_MESSAGE.openMessageForTALK();
            gTownMenu_MESSAGE.addMessageNOWAIT(0xc9a92);
            gTownMenu_MESSAGE.addMessageWAITKEY();
            mode_ = MODE_SELECT;
            break;
        case MODE_RESTART:
            gTownMenu_MESSAGE.openMessageForTALK();
            gTownMenu_MESSAGE.addMessageNOWAIT(0xc9aee);
            gTownMenu_MESSAGE.addMessageWAITKEY();
            mode_ = MODE_SELECT;
            break;
        case MODE_IN_RACE:
            gTownMenu_MESSAGE.openMessageForTALK();
            gTownMenu_MESSAGE.addMessage(0xc9a9a);
            mode_ = MODE_RACE;
            break;
        case MODE_RACE:
            return true;
        case MODE_SELECT:
            return true;
        case MODE_NOT_HAVECOIN:
            gTownMenu_MESSAGE.openMessageForTALK();
            gTownMenu_MESSAGE.addMessage(0xc9a97);
            mode_ = MODE_END;
            break;
        case MODE_NOT_SLIME:
            gTownMenu_MESSAGE.openMessageForTALK();
            gTownMenu_MESSAGE.addMessage(0xc9ab6, 0xc9ab7);
            mode_ = MODE_END;
            break;
        case MODE_TUTORIAL:
            gTownMenu_MESSAGE.openMessageForTALK();
            gTownMenu_MESSAGE.addMessageCount(0xc9ae2, 10);
            mode_ = MODE_RESTART;
            break;
        case MODE_CANCEL:
            gTownMenu_MESSAGE.openMessageForTALK();
            gTownMenu_MESSAGE.addMessage(0xc9af1);
            mode_ = MODE_END;
            break;
        case MODE_END:
            return true;
    }
    return false;
}

THUMB void MaterielMenu_RaceEntrance::commandUpdate()
{
    switch (mode_) {
        case MODE_SELECT:
            if (gTownMenu_MESSAGE.isMessageWAITPROG()) {
                selectUpdate();
            }
            break;
        case MODE_RACE:
            raceStart();
            break;
        case MODE_END:
            MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
            break;
    }
}

THUMB void MaterielMenu_RaceEntrance::selectUpdate()
{
    int result = menuItem_.execInput();
    switch (result) {
        case menu::MenuItem::MENUITEM_RESULT_OK:
            gTownMenu_MESSAGE.clearMessageWAITPROG();
            gTownMenu_MESSAGE.close();
            if (menuItem_.active_ == 0) {
                if (status::g_Party.getCasinoCoin() != 0) {
                    g_RaceData.setBetMode();
                    mode_ = MODE_IN_RACE;
                } else {
                    mode_ = MODE_NOT_HAVECOIN;
                }
            }
            if (menuItem_.active_ == 1) {
                if (isEnableSlime()) {
                    close();
                    gMaterielMenu_ChoiceSlime.open();
                } else {
                    mode_ = MODE_NOT_SLIME;
                }
            }
            if (menuItem_.active_ == 2) {
                mode_ = MODE_TUTORIAL;
            }
            if (menuItem_.active_ == 3) {
                mode_ = MODE_CANCEL;
            }
            break;
        case menu::MenuItem::MENUITEM_RESULT_CANCEL:
        case menu::MenuItem::MENUITEM_RESULT_SUPERCANCEL:
            mode_ = MODE_CANCEL;
            break;
        case menu::MenuItem::MENUITEM_RESULT_UP:
            if (menuItem_.active_ == 0) {
                menuItem_.active_ = 3;
            }
            break;
        case menu::MenuItem::MENUITEM_RESULT_DOWN:
            if (menuItem_.active_ == 3) {
                menuItem_.active_ = 0;
            }
            break;
    }
    if (result != 0) {
        redraw_ = 1;
    }
    menuItem_.resetResult();
}

THUMB void MaterielMenu_RaceEntrance::raceStart()
{
    g_RaceData.setRaceMapId(g_Global.getMapNameId());
    g_Global.startSlimeRace();
    close();
    MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
}

THUMB bool MaterielMenu_RaceEntrance::isEnableSlime()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    int max = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL);
    for (int i = 0; i < max; i++) {
        int index = MenuStatusInfo::getPlayerKindIndex(i);
        if (dq5::level::CharacterInitData::getRecord(index)->getMonsterID() == 0xde) {
            return true;
        }
    }
    return false;
}
