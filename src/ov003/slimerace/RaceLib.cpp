#include "ov003/slimerace/SlimeRace.hpp"
#include "nnsys/fnd.hpp"
#include <mem.h>

namespace race {

ST_MG_ARG g_arg;
MG3_STATE MG3State;
int g_game_fin;

}  // namespace race

using namespace race;

void SlimeRaceInit(void* addr, unsigned int size, ST_ARG_SL_RACE* arg)
{
    g_mgWork = addr;
    g_mgWorkSize = size;
    __builtin__clear(&g_arg, sizeof(g_arg));
    g_game_fin = 0;
    memcpy(&g_arg.slRace, arg, sizeof(ST_ARG_SL_RACE));
    set_pMGArg(&g_arg);
    MiniGame3(&MG3State);
}

void SlimeRaceDraw()
{
    g_game_fin = MiniGame3(&MG3State);
}

void SlimeRaceExec()
{
    unkfunc_021295e0();
}

void SlimeRaceTerm()
{
    unkfunc_021295e0();
    slimeRace_Final();
    sprite_all_free();
    func_0207e7cc(unkfunc_02128060()->handle);
}

int SlimeRaceResult(ST_ARG_SL_RACE* arg)
{
    memcpy(arg, &g_arg.slRace, sizeof(ST_ARG_SL_RACE));
    return unkfunc_02130860() == 5;
}

int unkfunc_02130860()
{
    return get_slimeRaceJoutai();
}

void unkfunc_0213086c(int state)
{
    set_slimeRaceJoutai(state);
}

int* unkfunc_02130878()
{
    return get_pSlimeRaceOdds();
}

int* unkfunc_02130884()
{
    return get_pSlimeRaceBets();
}
