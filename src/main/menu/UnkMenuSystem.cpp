#include "main/menu/UnkMenuSystem.hpp"
#include "main/menu/UnkMenuIconData.hpp"
#include "main/menu/UnkMenuPartsDraw.hpp"
#include "main/menu/MenuManager.hpp"

extern "C" THUMB void func_020624a8()
{
    loadMenuIconFiles();
}

extern "C" THUMB void func_020624b0()
{
    initMenuMsgSystem();
    MenuManager::setup();
}

extern "C" THUMB void func_020624bc()
{
    setupMenuDisplays();
    initMenuBg();
}

extern "C" THUMB void func_020624c8()
{
}

extern "C" THUMB void func_020624cc()
{
    updateMenuDisplays();
    updateMenuBg();
}

extern "C" THUMB void func_020624d8()
{
    MenuManager::execute();
    executeMenuDisplays();
    executeMenuBg();
}

extern "C" THUMB void func_020624e8()
{
    drawMenuDisplays();
    transferMenuBg();
}
