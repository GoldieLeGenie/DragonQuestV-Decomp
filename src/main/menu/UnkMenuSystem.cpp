#include "main/menu/UnkMenuSystem.hpp"
#include "main/menu/UnkMenuIconData.hpp"
#include "main/menu/UnkMenuPartsDraw.hpp"
#include "main/menu/MenuManager.hpp"

extern "C" THUMB void func_020624a8()
{
    unkfunc_02063250();
}

extern "C" THUMB void func_020624b0()
{
    unkfunc_02061bd0();
    MenuManager::setup();
}

extern "C" THUMB void func_020624bc()
{
    setupMenuDisplays();
    unkfunc_02063414();
}

extern "C" THUMB void func_020624c8()
{
}

extern "C" THUMB void func_020624cc()
{
    unkfunc_02063d94();
    unkfunc_0206343c();
}

extern "C" THUMB void func_020624d8()
{
    MenuManager::execute();
    unkfunc_02063e98();
    unkfunc_02063440();
}

extern "C" THUMB void func_020624e8()
{
    unkfunc_02063f9c();
    unkfunc_02063450();
}
