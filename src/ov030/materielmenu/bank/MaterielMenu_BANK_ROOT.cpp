#include "ov030/materielmenu/bank/MaterielMenu_BANK_ROOT.hpp"
#include "ov030/materielmenu/bank/MaterielMenu_BANK_DRAW.hpp"
#include "ov030/materielmenu/bank/MaterielMenu_BANK_PUTIN.hpp"
#include "ov030/leveldata/GoldMessage.hpp"
#include "ov019/materielmenu/MaterielMenu_WINDOW_MANAGER.hpp"
#include "ov019/materielmenu/MenuTemplate_materiel.hpp"
#include "ov019/materielmenu/UnkMaterielMenuWindowDraw.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/status/StoryStatus.hpp"
#include "main/text/TextAPI.hpp"

using menu::MenuStatusInfo;

inline dq5::level::GoldMessage* dq5::level::GoldMessage::getRecord(int index)
{
    return (GoldMessage*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned long dq5::level::GoldMessage::getMessage1()
{
    return message1;
}

THUMB void MaterielMenu_BANK_ROOT::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    menuItem_.active_ = 0;
    navigator_.setupBase();
    m_state = ROOT_START;
}

THUMB void MaterielMenu_BANK_ROOT::menuExecute()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    menu::MenuTemplate_materiel::MATERIEL_SHOP_ROOT(&menuItem_, menuItem_.active_);
}

THUMB void MaterielMenu_BANK_ROOT::menuDraw()
{
    if (gTownMenu_MESSAGE.isMessageWAITPROG()) {
        MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
        drawBankRootScreen();
        menuItem_.drawActive();
    }
}

THUMB void MaterielMenu_BANK_ROOT::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (gTownMenu_MESSAGE.isOpen()) {
        if (gTownMenu_MESSAGE.isMessageWAITPROG()) {
            if (m_state == ROOT_START) {
                m_state = ROOT_MESSAGE;
                redraw_ = 1;
                return;
            }
            if (m_state == ROOT_MESSAGE) {
                navigator_.setup(1, 3, 3);
                int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
                if (result == 0) {
                    return;
                }
                if (result == 3) {
                    closeBank();
                }
                if (result == 2) {
                    gTownMenu_MESSAGE.close();
                    switch (menuItem_.active_) {
                        case 0:
                            gMaterielMenu_BANK_PUTIN.open();
                            close();
                            break;
                        case 1:
                            gMaterielMenu_BANK_DRAW.open();
                            close();
                            break;
                        case 2:
                            closeBank();
                            break;
                    }
                }
                redraw_ = 1;
                return;
            }
        }
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK || stat == MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
            if (m_state == ROOT_SELECT) {
                MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
            }
        }
        return;
    }
    if (m_state == ROOT_START) {
        gTownMenu_MESSAGE.openMessageForTALK();
        if (!status::g_Story.isUseBank()) {
            status::g_Story.setUseBank(true);
            for (int i = 0; i < 4; i++) {
                gTownMenu_MESSAGE.addMessage(getMessageNo(i + 1));
            }
            gTownMenu_MESSAGE.addMessageWAITKEY();
            return;
        }
        if (MenuStatusInfo::getBank() == 0) {
            gTownMenu_MESSAGE.addMessage(getMessageNo(5));
            gTownMenu_MESSAGE.addMessageNOWAIT(getMessageNo(6));
            gTownMenu_MESSAGE.addMessageWAITKEY();
        }
        else {
            TextAPI::setMACRO0(0x30, 0xf0000000, MenuStatusInfo::getBank());
            gTownMenu_MESSAGE.addMessage(getMessageNo(5));
            gTownMenu_MESSAGE.addMessageNOWAIT(getMessageNo(7));
            gTownMenu_MESSAGE.addMessageWAITKEY();
        }
    }
}

THUMB void MaterielMenu_BANK_ROOT::closeBank()
{
    gTownMenu_MESSAGE.openMessageForTALK();
    if (MenuStatusInfo::getBank() == 0) {
        gTownMenu_MESSAGE.addMessage(getMessageNo(22));
    }
    else {
        TextAPI::setMACRO0(0x30, 0xf0000000, MenuStatusInfo::getBank());
        gTownMenu_MESSAGE.addMessage(getMessageNo(21));
    }
    m_state = ROOT_SELECT;
}

THUMB int MaterielMenu_BANK_ROOT::getMessageNo(int index)
{
    return dq5::level::GoldMessage::getRecord(index)->getMessage1();
}
