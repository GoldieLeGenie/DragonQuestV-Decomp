#include "ov024/materielmenu/casino/MaterielMenu_TouchResult.hpp"
#include "ov024/materielmenu/casino/MaterielMenu_SlimeTouch.hpp"
#include "ov019/materielmenu/MaterielMenu_WINDOW_MANAGER.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/status/MenuStatus.hpp"
#include "main/status/TouchData.hpp"
#include "main/text/TextAPI.hpp"

using menu::MenuStatusInfo;

inline status::TOUCH_ITEM_DATA& status::TouchData::getItem(int index)
{
    return item_[index];
}

inline int status::TouchData::getScore()
{
    return newScore_;
}

THUMB void MaterielMenu_TouchResult::menuSetup()
{
    itemCount_ = 0;
    rankIn_ = 0;
    itemGet_ = 0;
    status::g_Menu.bookingFlag_ = 0;
    mode_ = MODE_RESULT;
}

THUMB void MaterielMenu_TouchResult::menuExecute()
{
}

THUMB void MaterielMenu_TouchResult::menuDraw()
{
}

THUMB void MaterielMenu_TouchResult::menuUpdate()
{
    if (messageUpdate()) {
        commandUpdate();
    }
}

THUMB void MaterielMenu_TouchResult::commandUpdate()
{
    switch (mode_) {
        case MODE_RESULT:
            rankIn_ = 0;
            itemGet_ = 0;
            if (status::g_TouchData.rankIn_) {
                mode_ = MODE_RANK_IN;
                rankIn_ = 1;
            }
            else {
                mode_ = MODE_RANK_OUT;
            }
            for (int i = 0; i < 17; i++) {
                if (status::g_TouchData.item_[i].count > 0 && status::g_TouchData.item_[i].index != 0) {
                    itemGet_ = 1;
                }
            }
            break;
        case MODE_GIFTCHECK:
            for (; itemCount_ < 17; itemCount_++) {
                if (status::g_TouchData.getItem(itemCount_).count > 0 && status::g_TouchData.getItem(itemCount_).index != 0) {
                    break;
                }
            }
            mode_ = MODE_GIFT;
            break;
        case MODE_END:
            close();
            MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
            gMaterielMenu_SlimeTouch.open();
            break;
    }
}

THUMB bool MaterielMenu_TouchResult::messageUpdate()
{
    if (gTownMenu_MESSAGE.isOpen()) {
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK || stat == MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
            redraw_ = 1;
        }
        return false;
    }
    switch (mode_) {
        case MODE_RESULT:
        case MODE_GIFTCHECK:
        case MODE_END:
            return true;
        case MODE_RANK_IN:
            TextAPI::setMACRO0(0x95, 0xf0000000, status::g_TouchData.getScore());
            gTownMenu_MESSAGE.openMessageForMENU();
            gTownMenu_MESSAGE.addMessage(0xccd6f);
            mode_ = MODE_END;
            if (itemGet_) {
                gTownMenu_MESSAGE.addMessage(0xccd70);
                mode_ = MODE_GIFTCHECK;
            }
            break;
        case MODE_RANK_OUT:
            TextAPI::setMACRO0(0x95, 0xf0000000, status::g_TouchData.getScore());
            gTownMenu_MESSAGE.openMessageForMENU();
            gTownMenu_MESSAGE.addMessage(0xccd75);
            mode_ = MODE_END;
            if (itemGet_) {
                gTownMenu_MESSAGE.addMessage(0xccd76);
                mode_ = MODE_GIFTCHECK;
            }
            break;
        case MODE_GIFT:
            gTownMenu_MESSAGE.openMessageForMENU();
            if (itemCount_ >= 17) {
                gTownMenu_MESSAGE.addMessage(0xccd85);
                mode_ = MODE_END;
                break;
            }
            TextAPI::setMACRO0(10, 0x40000000, status::g_TouchData.getItem(itemCount_).index);
            TextAPI::setMACRO0(0x54, 0xf0000000, status::g_TouchData.getItem(itemCount_).count);
            if (status::g_TouchData.getItem(itemCount_).count > 1) {
                gTownMenu_MESSAGE.addMessage(0xccd83);
                for (int i = 0; i < status::g_TouchData.getItem(itemCount_).count; i++) {
                    MenuStatusInfo::addFukuroItem(status::g_TouchData.getItem(itemCount_).index, 1);
                }
            }
            else {
                gTownMenu_MESSAGE.addMessage(0xccd84);
                MenuStatusInfo::addFukuroItem(status::g_TouchData.getItem(itemCount_).index, 1);
            }
            itemCount_++;
            mode_ = MODE_GIFTCHECK;
            break;
    }
    return false;
}
