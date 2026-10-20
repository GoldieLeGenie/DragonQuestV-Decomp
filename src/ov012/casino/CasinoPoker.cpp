#pragma ipa file
#include "ov012/casino/CasinoPoker.hpp"
#include "main/dss/DssUtils.hpp"
#include "ov012/casino/CasinoPokerDraw.hpp"
#include "ov012/casino/CasinoSystem.hpp"
#include "ov012/casino/PokerManager.hpp"
#include "ov019/materielmenu/MaterielMenu_WINDOW_MANAGER.hpp"

inline casino::CasinoMiniGameBase::~CasinoMiniGameBase()
{
}

inline char* casino::CasinoPoker::getStageName()
{
    return (char*)stagePoker;
}

const char* casino::CasinoPoker::stagePoker = "ev10";

THUMB casino::CasinoPoker::CasinoPoker()
{
}

THUMB casino::CasinoPoker::~CasinoPoker()
{
}

THUMB casino::CasinoPoker* casino::CasinoPoker::getSingleton()
{
    static CasinoPoker casinoPoker;
    return &casinoPoker;
}

THUMB void casino::CasinoPoker::initialize()
{
    CasinoPokerDraw::getSingleton()->initialize();
    PokerManager::getSingleton()->initialize();
    MaterielMenu_WINDOW_MANAGER::getSingleton()->openMaterielWindow(0x1c);
    char path[128];
    dss::sprintf_s(path, sizeof(path), "data/2d/map/casino_upper.tex");
    sprite_.loadFile(path, 0);
    sprite_.setSubScreen();
    sprite_.setPolygonID(0x3e);
    sprite_.setDepth(0);
    sprite_.sprite_.color0Opaque_ = 1;
    sprite_.setTexCoords(0, 0, 0x100, 0xc0);
    sprite_.setSize(0x100, 0xc0);
    sprite_.attachRender(&CasinoSystem::getSingleton()->render_);
}

THUMB void casino::CasinoPoker::terminate()
{
    sprite_.unload();
    CasinoPokerDraw::getSingleton()->terminate();
}

THUMB void casino::CasinoPoker::execute()
{
}

THUMB void casino::CasinoPoker::draw()
{
    CasinoPokerDraw::getSingleton()->draw();
    setupOrtho2D();
    sprite_.draw();
}
