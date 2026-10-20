#pragma ipa file
#include "ov012/casino/CasinoSystem.hpp"
#include "main/global/Global.hpp"
#include "main/sound/SoundManager.hpp"
#include "ov012/casino/CasinoCamera.hpp"
#include "ov012/casino/CasinoPoker.hpp"
#include "ov012/casino/CasinoSlot.hpp"
#include "ov012/casino/CasinoStage.hpp"

inline void casino::CasinoMiniGameBase::setRender(Render* render)
{
    render_ = render;
}

THUMB casino::CasinoSystem::CasinoSystem()
{
}

THUMB casino::CasinoSystem::~CasinoSystem()
{
}

THUMB casino::CasinoSystem* casino::CasinoSystem::getSingleton()
{
    static CasinoSystem casinoSystem;
    return &casinoSystem;
}

THUMB void casino::CasinoSystem::initialize()
{
    render_.setup();
    if (g_Global.getMinigame() == 0) {
        minigame = CasinoPoker::getSingleton();
    } else {
        minigame = CasinoSlot::getSingleton();
    }
    minigame->setRender(&render_);
    CasinoCamera::getSingleton()->initialize();
    CasinoStage::getSingleton()->initialize();
    minigame->initialize();
    SoundManager::townPlay(8);
}

THUMB void casino::CasinoSystem::terminate()
{
    minigame->terminate();
    CasinoStage::getSingleton()->terminate();
    CasinoCamera::getSingleton()->terminate();
    render_.cleanup();
}

THUMB void casino::CasinoSystem::execute()
{
    minigame->execute();
}

THUMB void casino::CasinoSystem::draw()
{
    CasinoCamera::getSingleton()->draw();
    minigame->draw();
    render_.unkfunc_02048908();
}
