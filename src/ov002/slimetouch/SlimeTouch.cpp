#pragma ipa file
#include "ov002/slimetouch/SlimeTouch.hpp"
#include "ov002/slimetouch/SlimeTouchGame.hpp"
#include "nnsys/fnd.hpp"
#include <mem.h>

ST_MG_ARG g_arg;
MG2_STATE MG2State = MG2_init;
int g_game_fin;

void SlimeTouchInit(void* work, unsigned int size, ST_ARG_SL_TOUCH* arg)
{
    g_mgWorkAddr = work;
    g_mgWorkSize = size;
    __builtin__clear(&g_arg, sizeof(g_arg));
    g_game_fin = 0;
    memcpy(&g_arg.slTouch, arg, sizeof(ST_ARG_SL_TOUCH));
    set_pMGArg(&g_arg);
    MiniGame2(&MG2State);
    MiniGame2(&MG2State);
}

void SlimeTouchDraw()
{
    g_game_fin = MiniGame2(&MG2State);
}

void SlimeTouchExec()
{
    releaseVramCache();
}

void SlimeTouchTerm()
{
    releaseVramCache();
    slime_cg_Release_all();
    sprite_all_free();
    func_0207e7cc(*getMgHeap());
}

int SlimeTouchResult(ST_ARG_SL_TOUCH* arg)
{
    memcpy(arg, &g_arg.slTouch, sizeof(ST_ARG_SL_TOUCH));
    return g_game_fin ? TRUE : FALSE;
}
