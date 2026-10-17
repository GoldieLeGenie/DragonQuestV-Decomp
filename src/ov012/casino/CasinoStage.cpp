#pragma ipa file
#include "ov012/casino/CasinoStage.hpp"
#include "main/global/Global.hpp"
#include "ov012/casino/CasinoPoker.hpp"
#include "ov012/casino/CasinoSlot.hpp"
#include "ov012/casino/CasinoSystem.hpp"

const char* casino::CASINO_MAP_PATH = "data/map";

THUMB casino::CasinoStage::CasinoStage()
{
}

THUMB casino::CasinoStage::~CasinoStage()
{
}

THUMB casino::CasinoStage* casino::CasinoStage::getSingleton()
{
    static CasinoStage casinoStage;
    return &casinoStage;
}

THUMB void casino::CasinoStage::initialize()
{
    stage_.initialize(&CasinoSystem::getSingleton()->render_);
    stage_.setPath(CASINO_MAP_PATH);
    if (g_Global.getMinigame() == 0) {
        stage_.load(CasinoPoker::getSingleton()->getStageName());
    } else {
        stage_.load(CasinoSlot::getSingleton()->getSlotStageName(g_Global.getMinigame()));
    }
    stage_.setup();
}

THUMB void casino::CasinoStage::terminate()
{
    stage_.cleanup();
    stage_.terminate();
}

THUMB void casino::CasinoStage::setObjectDraw(int id, int draw, int uidFlag)
{
    if (draw == 1) {
        stage_.repop(id);
    }
    stage_.animLocation(id, draw, uidFlag);
}
