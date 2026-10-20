#include "ov025/materielmenu/surechigai/UnkMaterielMenu_02187cec.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov019/materielmenu/MaterielMenu_WINDOW_MANAGER.hpp"
#include "ov019/materielmenu/MenuTemplate_materiel.hpp"
#include "ov019/materielmenu/UnkMaterielMenuDrawParts.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/status/MuseumStatus.hpp"
#include "main/text/TextAPI.hpp"

using menu::MenuStatusInfo;

THUMB void UnkMaterielMenu_02187cec::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_NONE);
    menuItem_.active_ = 0;
    navigator_.setupBase();
    museumItem_ = status::g_MuseumStatus.findMuseumItemStatus(twn::TownPlayerManager::getSingleton().searchMapUid_);
    status::MuseumItemStatus* item = &status::g_MuseumStatus.museumitem_[museumItem_];
    mapId_ = item->mapid_;
    iconId_ = item->iconid_;
    gTownMenu_MESSAGE.openMessageForMENU();
    if (iconId_ == 0) {
        if (mapId_ == 0x27c) {
            gTownMenu_MESSAGE.addMessage(0xcc5c6);
        } else {
            gTownMenu_MESSAGE.addMessage(0xcc643);
        }
    } else if (mapId_ == 0x27c) {
        setTaishiMessageMacros(-1);
        gTownMenu_MESSAGE.addMessageNOWAIT(0xcc5c6);
        gTownMenu_MESSAGE.addMessageWAITKEY();
    } else {
        setTaishiMessageMacros(museumItem_ - 0x1b);
        gTownMenu_MESSAGE.addMessageNOWAIT(0xcc63f);
        gTownMenu_MESSAGE.addMessageWAITKEY();
    }
    setCaptureOffset(-4, 0);
}

THUMB void UnkMaterielMenu_02187cec::menuExecute()
{
    menu::MenuTemplate_materiel::MATERIEL_PICTUREBOOK_MONSTERANIME(&menuItem_);
}

THUMB void UnkMaterielMenu_02187cec::menuDraw()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (iconId_ != 0) {
        if (mapId_ == 0x27c) {
            drawTagModeTenantDetail(museumItem_, 1, 1);
            return;
        }
        drawTagModeTenantDetail(museumItem_ - 0x1b, 0, 1);
    }
}

THUMB void UnkMaterielMenu_02187cec::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (gTownMenu_MESSAGE.isOpen() == true) {
        if (gTownMenu_MESSAGE.isMessageWAITPROG() == true) {
            navigator_.setup(1, 1, 1);
            int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
            if (result == 0) {
                return;
            }
            if (result == 2 || result == 3) {
                MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
                resetCaptureOffset();
            }
            redraw_ = 1;
            return;
        }
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK || stat == MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
            MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
            resetCaptureOffset();
        }
    }
}

THUMB void UnkMaterielMenu_02187cec::setTaishiMessageMacros(int index)
{
    char line1[0x40];
    char line2[0x40];
    char line3[0x40];
    status::TaishiBase* taishi;
    if (index == -1) {
        taishi = &status::g_MuseumStatus.playerTaishi_;
    } else {
        taishi = &status::g_MuseumStatus.othersTaishi_[index];
    }
    splitCommentLines(line1, line2, line3, taishi->message_);
    TextAPI::setUserString(0, line1);
    TextAPI::setUserString(1, line2);
    TextAPI::setUserString(2, line3);
    if (index == -1) {
        TextAPI::setMACRO1(0x90, 0xd0000000, 0);
        TextAPI::setMACRO2(0x90, 0xd0000000, 1);
        TextAPI::setMACRO3(0x90, 0xd0000000, 2);
        return;
    }
    TextAPI::setMACRO1(0x94, 0xd0000000, 0);
    TextAPI::setMACRO2(0x94, 0xd0000000, 1);
    TextAPI::setMACRO3(0x94, 0xd0000000, 2);
}
