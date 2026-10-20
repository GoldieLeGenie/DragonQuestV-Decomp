#include "main/part/SlimeRacePart.hpp"
#include "main/dss/DssCore.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/dss/Pad.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/dss/UnkDisplayPlugin.hpp"
#include "main/dss/UnkMemory.hpp"
#include "main/dss/UnkOverlaySlot.hpp"
#include "main/dss/UnkRandom.hpp"
#include "main/dss/VramTransferManager.hpp"
#include "main/global/Global.hpp"
#include "main/menu/MaterielMenuWindowManager.hpp"
#include "main/menu/RaceData.hpp"
#include "main/menu/UnkMenuPartsDraw.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/text/TextHook.hpp"
#include "nitro/gx.h"
#include "nitro/gx.hpp"
#include "nitro/os.hpp"
#include "nnsys/g3d.hpp"
#include "ov003/slimerace/SlimeRace.hpp"
#include <nitro/os/interrupt.h>

inline unsigned int status::BasePartyStatus::getCasinoCoin()
{
    return casinoCoin_;
}

inline int RaceData::getRaceMapId()
{
    return raceMap_;
}

inline unsigned char RaceData::getPaddock()
{
    return slimeNum_;
}

inline bool RaceData::isLookOnly()
{
    return look_;
}

race::SlimeRacePart g_SlimeRacePart;
static void* s_work;

THUMB void race::SlimeRacePart::initialize()
{
    func_02075360();
    func_0207534c();
    GX_ResetBankForTex();
    GX_ResetBankForSubObj();
    GX_ResetBankForSubBg();
    GX_SetBankForTex(GX_VRAM_AB);
    data_020f4f74.unkfunc_0204a53c(0x40000, 0x4000);
    unkfunc_0204c9d8(&dss::g_DISPLAYPLUGIN_DOUBLE3D);
    func_02062480(5, 0x1f, 0x10, 0x1f);
    func_02062480(6, 6, 0x19, 0x1f);
    func_02062480(7, 0x10, 0x1f, 0x10);
    func_02062480(8, 0x1f, 0x18, 8);
    func_02062480(9, 0x1f, 8, 8);
    func_02062480(10, 8, 0xb, 0x1f);
    func_02062480(11, 0x1f, 0x1f, 0);
    unkfunc_0204afe0();
    unkfunc_0204b5d4((int)&OVERLAY_3_ID);
    unkfunc_0204b5d4((int)&OVERLAY_19_ID);
    ov019_entry();
    const RACE_BG_MAP map[2] = {RACE_BG_MAP_ev3, RACE_BG_MAP_ev5};
    ST_ARG_SL_RACE arg;
    arg.coin = status::g_Party.getCasinoCoin();
    arg.nakamaSlime = NAKAMA_SLIME_nonEntry;
    if (g_RaceData.getRaceMapId() == 0x98) {
        arg.bgMap = RACE_BG_MAP_ev1;
        if (g_RaceData.getPaddock() == 6) {
            arg.bgMap = RACE_BG_MAP_ev2;
        }
    } else {
        arg.bgMap = map[UnkDssRand::rand(2)];
        if (g_RaceData.getPaddock() == 6) {
            arg.bgMap = RACE_BG_MAP_ev4;
        }
    }
    if (g_RaceData.getPaddock() == 6) {
        arg.nakamaSlime = NAKAMA_SLIME_entry_bet;
    }
    if (g_RaceData.isLookOnly()) {
        arg.nakamaSlime = NAKAMA_SLIME_entry_nonBet;
    }
    arg.unk_0c = 0;
    s_work = unkfunc_0204c5bc(&data_020fd24c, 0x80000, 0x20);
    SlimeRaceInit(s_work, 0x80000, &arg);
    func_02082654(1);
    OS_Wait();
    g_Global.fadeIn(30);
    MaterielMenu_WINDOW_MANAGER::getSingleton()->openMaterielWindow(0x25);
    DC_CleanAll();
}

THUMB void race::SlimeRacePart::terminate()
{
    dss::g_Pad.unkfunc_0204bc24(0);
    SlimeRaceTerm();
    unkfunc_0204c5c8(&data_020fd24c, s_work);
    s_work = NULL;
    unkfunc_0204b5e8((int)&OVERLAY_3_ID);
    unkfunc_0204b5e8((int)&OVERLAY_19_ID);
    data_020f4f74.unkfunc_0204a5f0();
}

THUMB void race::SlimeRacePart::onExecutePart()
{
    SlimeRaceExec();
    ST_ARG_SL_RACE arg;
    if (SlimeRaceResult(&arg)) {
        gTextHook.raceResultA_ = arg.rank[0];
        gTextHook.raceResultB_ = arg.rank[1];
    }
}

THUMB void race::SlimeRacePart::onDrawPart()
{
    SlimeRaceDraw();
}

THUMB void race::SlimeRacePart::onWindowPart()
{
}

THUMB void race::SlimeRacePart::onDebugPart()
{
}

THUMB void race::SlimeRacePart::onSwapBuffersPart()
{
    BOOL enable = OS_DisableIME();
    REG_GFX_FIFO_SWAP_BUFFERS = 0;
    OS_RestoreIME(enable);
}
