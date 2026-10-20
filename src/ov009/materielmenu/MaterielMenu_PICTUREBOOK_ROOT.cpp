#include "ov009/materielmenu/MaterielMenu_PICTUREBOOK_ROOT.hpp"
#include "ov009/materielmenu/MaterielMenu_PICTUREBOOK_DETAIL.hpp"
#include "main/cmn/ExtraMapLink.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/leveldata/BookData.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/status/BattleResult.hpp"
#include "main/status/StageInfo.hpp"
#include "ov019/materielmenu/MaterielMenuPlayerControl.hpp"
#include "ov019/materielmenu/MenuTemplate_materiel.hpp"
#include "ov019/materielmenu/UnkMaterielMenuWindowDraw.hpp"

inline void menu::MenuPlayerControl::setActiveItem(short item) { activeItem_ = item; }
inline void menu::MaterielMenuPlayerControl::setActiveItemPage(int active) { activeItemPage_ = active; }

inline unsigned int ExcelBinaryData::getRecordCount() { return record_; }
inline unsigned int dq5::level::BookData::getArraySize() { return binary_.getRecordCount(); }

THUMB void MaterielMenu_PICTUREBOOK_ROOT::menuSetup()
{
    menu::MenuStatusInfo::setMode(menu::MenuStatusInfo::PLAYER_MODE);
    unk_8c = dq5::level::BookData::getArraySize();
    m_activeMonster = menu::MaterielMenuPlayerControl::getSingleton()->activeItem_;
    m_nowPage = menu::MaterielMenuPlayerControl::getSingleton()->activeItemPage_;
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    menuItem_.active_ = m_activeMonster;
    navigator_.setupBase();
    navigator_.setup(2, 8, 0xca);
    gMaterielMenu_PICTUREBOOK_DETAIL.isOpen_ = 0;
    if (m_activeMonster == 0 && m_nowPage == 0) {
        for (unsigned int i = 0; i < 0xca; i++) {
            if (status::g_BattleResult.isMonsterEncount(i) == true) {
                m_nowPage = i >> 4;
                m_activeMonster = i & 0xf;
                menuItem_.active_ = m_activeMonster;
                break;
            }
        }
    }
    navigator_.setPageNo(m_nowPage);
    menu::MaterielMenuPlayerControl::getSingleton()->setActiveItem(m_activeMonster);
    menu::MaterielMenuPlayerControl::getSingleton()->setActiveItemPage(m_nowPage);
}

THUMB void MaterielMenu_PICTUREBOOK_ROOT::menuExecute()
{
    int maxCount = m_nowPage * 16;
    maxCount = 0xca - maxCount;
    menu::MenuTemplate_materiel::MATERIEL_PICTUREBOOK_SELECT(&menuItem_, menuItem_.active_, dss::clamp<int>(1, maxCount, 16));
}

THUMB void MaterielMenu_PICTUREBOOK_ROOT::menuDraw()
{
    if (status::g_BattleResult.getMonsterEncountCount() != 0) {
        menu::MenuStatusInfo::setMode(menu::MenuStatusInfo::PLAYER_MODE);
        drawMonsterBookScreen();
        menuItem_.drawActive();
    }
}

THUMB void MaterielMenu_PICTUREBOOK_ROOT::menuUpdate()
{
    menu::MenuStatusInfo::setMode(menu::MenuStatusInfo::PLAYER_MODE);
    if (gTownMenu_MESSAGE.isOpen() == 1) {
        if (gTownMenu_MESSAGE.stat_ == menu::MenuBase::MENUBASE_STAT_OK || gTownMenu_MESSAGE.stat_ == menu::MenuBase::MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
            close();
            cmn::g_extraMapLink.setMonstarBookLink();
            status::g_StageInfo.returnBookFlag_ = 1;
        }
        return;
    }
    navigator_.setup(2, 8, 0xca);
    int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
    if (result != 0) {
        m_activeMonster = menuItem_.active_;
        menu::MaterielMenuPlayerControl::getSingleton()->setActiveItem(m_activeMonster);
        if (m_nowPage != navigator_.getPageNo()) {
            m_nowPage = navigator_.getPageNo();
            menu::MaterielMenuPlayerControl::getSingleton()->setActiveItemPage(m_nowPage);
        }
        if (result == 2) {
            if (status::g_BattleResult.isMonsterEncount(navigator_.getIndex(m_activeMonster)) == true) {
                close();
                gMaterielMenu_PICTUREBOOK_DETAIL.isOpen_ = 1;
                gMaterielMenu_PICTUREBOOK_DETAIL.open();
            }
        }
        if (result == 3) {
            menu::MaterielMenuPlayerControl::getSingleton()->initialize();
            close();
            cmn::g_extraMapLink.setMonstarBookLink();
            status::g_StageInfo.returnBookFlag_ = 1;
        }
        if (result == 7) {
            if (status::g_BattleResult.getMonsterEncountCount() == 0) {
                m_activeMonster = navigator_.pageBack(m_activeMonster);
                m_nowPage = navigator_.getPageNo();
            } else {
                while (!checkPage()) {
                    m_activeMonster = navigator_.pageNext(m_activeMonster);
                    m_nowPage = navigator_.getPageNo();
                }
            }
            menu::MaterielMenuPlayerControl::getSingleton()->setActiveItem(m_activeMonster);
            menu::MaterielMenuPlayerControl::getSingleton()->setActiveItemPage(m_nowPage);
        }
        if (result == 6) {
            if (status::g_BattleResult.getMonsterEncountCount() == 0) {
                m_activeMonster = navigator_.pageNext(m_activeMonster);
                m_nowPage = navigator_.getPageNo();
            } else {
                while (!checkPage()) {
                    m_activeMonster = navigator_.pageBack(m_activeMonster);
                    m_nowPage = navigator_.getPageNo();
                }
            }
            menu::MaterielMenuPlayerControl::getSingleton()->setActiveItem(m_activeMonster);
            menu::MaterielMenuPlayerControl::getSingleton()->setActiveItemPage(m_nowPage);
        }
        redraw_ = 1;
    }
}

THUMB bool MaterielMenu_PICTUREBOOK_ROOT::checkPage()
{
    for (int i = 0; i < 16; i++) {
        if (status::g_BattleResult.isMonsterEncount(i + (m_nowPage << 4)) == true) {
            return true;
        }
    }
    return false;
}
