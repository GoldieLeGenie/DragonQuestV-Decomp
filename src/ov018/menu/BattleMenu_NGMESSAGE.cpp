#include "ov018/menu/BattleMenu.hpp"
#include "ov018/menu/BattleMonsterNamePlate.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/text/TextAPI.hpp"

using menu::MenuStatusInfo;

THUMB void BattleMenu_NGMESSAGE::menuSetup()
{
    messageID_ = 0;
    returnPos_ = 0;
}

THUMB void BattleMenu_NGMESSAGE::menuExecute()
{
}

THUMB void BattleMenu_NGMESSAGE::menuDraw()
{
}

THUMB void BattleMenu_NGMESSAGE::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    if (gTownMenu_MESSAGE.isOpen()) {
        if ((unsigned int)(gTownMenu_MESSAGE.stat_ - 1) <= 1) {
            gTownMenu_MESSAGE.close();
            close();
            if (returnMenu_ == MENU_ACTIONMENU) {
                BattleMonsterNamePlate::getSingleton().init();
                BattleMonsterNamePlate::getSingleton().setMonster();
                gBattleMenu_ACTIONMENU.open();
                gBattleMenu_ACTIONMENU.pageItem_.active_ = returnPos_;
            } else {
                gBattleMenu_ROOT.open();
                gBattleMenu_ROOT.menuItem_.active_ = returnPos_;
            }
        }
        return;
    }
    int chara = BattleMenuPlayerControl::getSingleton()->activeChara_;
    if (chara != -1) {
        TextAPI::setMACRO0(1, 0x50000000, MenuStatusInfo::getHaveStatusInfo(chara).haveStatus_.playerIndex_);
    }
    gTownMenu_MESSAGE.openMessageForBATTLE();
    gTownMenu_MESSAGE.addMessage(messageID_);
    gTownMenu_MESSAGE.setMessageLastCursor(false);
}
