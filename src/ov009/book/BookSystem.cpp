#pragma ipa file
#include "ov009/book/BookSystem.hpp"
#include "ov009/book/BookCamera.hpp"
#include "ov009/book/BookMonsterDraw.hpp"
#include "ov009/materielmenu/MaterielMenu_PICTUREBOOK_DETAIL.hpp"
#include "ov009/materielmenu/MaterielMenu_PICTUREBOOK_ROOT.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/dss/RenderObject.hpp"
#include "main/leveldata/EffectParam.hpp"
#include "main/leveldata/MonsterAnim.hpp"
#include "main/object/DSSAObject.hpp"

THUMB book::BookSystem::BookSystem()
{
}

THUMB book::BookSystem::~BookSystem()
{
}

THUMB book::BookSystem& book::BookSystem::getSingleton()
{
    static BookSystem bookSystem;
    return bookSystem;
}

THUMB void book::BookSystem::initialize()
{
    char path[128];
    dss::Fix32 scl;
    scl.value = 0x120;
    DSSAObject::setDefaultScale(scl);
    DSSAObject::setPriority(1);
    dq5::level::EffectParam::setup();
    dq5::level::MonsterAnim::setup();
    render_.unkfunc_02048860();
    BookCamera::getSingleton().initialize();
    BookMonsterDraw::getSingleton().initialize();
    monsterNo_ = 0;
    BookMonsterDraw::getSingleton().setup(0);
    gMaterielMenu_PICTUREBOOK_ROOT.open();
    scl.value = 0x120;
    DSSAObject::setDefaultScale(scl);
    DSSAObject::setPriority(1);
    dss::sprintf_s(path, sizeof(path), "data/2d/map/encyclopedia.tex");
    sprite_.loadFile(path, 0);
    sprite_.setMainScreen();
    sprite_.setAlpha(0x1f);
    sprite_.setPolygonID(0x20);
}

THUMB void book::BookSystem::terminate()
{
    BookMonsterDraw::getSingleton().terminate();
    BookCamera::getSingleton().terminate();
    render_.unkfunc_020488b4();
    sprite_.unload();
    dq5::level::EffectParam::cleanup();
    dq5::level::MonsterAnim::cleanup();
}

THUMB void book::BookSystem::execute()
{
    if (gMaterielMenu_PICTUREBOOK_DETAIL.isOpen_) {
        BookMonsterDraw::getSingleton().execute();
    }
}

THUMB void book::BookSystem::draw()
{
    BookCamera::getSingleton().draw();
    render_.unkfunc_02048908();
    if (gMaterielMenu_PICTUREBOOK_DETAIL.isOpen_) {
        BookMonsterDraw::getSingleton().draw();
    }
    setupOrtho2DBackground();
    sprite_.draw();
}
