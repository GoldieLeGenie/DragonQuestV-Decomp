#include "ov018/menu/BattleMenu.hpp"
#include "ov018/menu/UnkBattleMenuDraw.hpp"
#include "main/menu/MenuStatusInfo.hpp"

ARM void BattleMenu_StadiumAbort::menuSetup()
{
}

ARM void BattleMenu_StadiumAbort::menuExecute()
{
}

ARM void BattleMenu_StadiumAbort::menuDraw()
{
    menu::MenuStatusInfo::setMode(menu::MenuStatusInfo::BATTLE_MODE);
    drawPartyHpPercents();
}

ARM void BattleMenu_StadiumAbort::menuUpdate()
{
}
