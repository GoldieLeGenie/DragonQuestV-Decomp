#include "ov004/ceremony/CeremonyStage.hpp"
#include "main/global/Global.hpp"

inline int Global::getMapNameId()
{
    return nextMapNameId;
}

const char* ceremony::CEREMONY_MAP_PATH = "data/map";

THUMB ceremony::CeremonyStage::CeremonyStage()
{
}

THUMB ceremony::CeremonyStage::~CeremonyStage()
{
}

THUMB ceremony::CeremonyStage* ceremony::CeremonyStage::getSingleton()
{
    static CeremonyStage m_singleton;
    return &m_singleton;
}

THUMB void ceremony::CeremonyStage::initialize()
{
    stage_.setPath(CEREMONY_MAP_PATH);
    if (g_Global.getMapNameId() != 0) {
        stage_.load("ev17");
        stage_.setup();
        enable_ = 1;
    } else {
        enable_ = 0;
    }
}

THUMB void ceremony::CeremonyStage::terminate()
{
    if (enable_) {
        stage_.cleanup();
        stage_.terminate();
    }
}

THUMB void ceremony::CeremonyStage::draw()
{
    if (enable_) {
        stage_.draw();
    }
}
