#include "ov001/town/TownSystem.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov001/script/ScriptMapCommand.hpp"
#include "main/global/Global.hpp"
#include "main/leveldata/LevelDataUtility.hpp"
#include "main/leveldata/VehicleData.hpp"
#include "main/script/ScriptSystem.hpp"
#include "main/status/BattleResult.hpp"
#include "main/status/StageAttribute.hpp"
#include "main/status/StageInfo.hpp"
#include "main/status/StoryStatus.hpp"

#pragma thumb on

inline dq5::CHAPTER_NO status::StoryStatus::getChapter()
{
    return chapter_;
}

inline int status::BattleResult::isDisableChurchMessage()
{
    return playerDemolitionMessage_;
}

inline void status::StageInfo::setReturnGame(dq5::RETURN_GAME_TYPE returnGame)
{
    returnGame_ = returnGame;
}

inline void status::StageInfo::setKimeraSymbol(int id)
{
    kimeraSymbol_ = id;
}

inline void MapObjGimmickMove::clear()
{
    count_ = 0;
    execNo_ = -1;
}

inline int Global::getMapNameId()
{
    return nextMapNameId;
}

inline int twn::TownActionTruck::isScriptMove()
{
    return TownPlayerManager::getSingleton().player_.townActionTruck_.scriptFlag_;
}

inline void twn::TownCommandInitWait::setWait(bool flag)
{
    flag_ = flag;
}

inline void twn::TownSystemCommand::setWait(bool flag)
{
    townCommandInitWait_.setWait(flag);
}

inline void twn::TownSystem::setWait(bool flag)
{
    townSystemCommand_.setWait(flag);
}

twn::TownSystemScript::TownSystemScript()
{
}

twn::TownSystemScript::~TownSystemScript()
{
}

void twn::TownSystemScript::initialize()
{
    eventLock_ = 0;
    scriptSearch_ = 0;
    g_MapObjGimmickMove.clear();
    if (status::g_BattleResult.isDisableChurchMessage() != 2) {
        status::g_StageInfo.setReturnGame(dq5::RETURN_GAME_CHURCH);
    }
    ScriptSystem::getSingleton()->initialize(status::g_Story.getChapter(), 0);
    status::g_StageInfo.setReturnGame(dq5::RETURN_GAME_NONE);
    if (TownActionTruck::isScriptMove()) {
        TownSystem::getSingleton().setWait(false);
    }
    if (!status::g_StageAttribute.isKimeraSetDisable()) {
        dq5::level::VehicleData::setup();
        int map = g_Global.getMapNameId();
        if (status::g_Story.getChapter() == dq5::CHAPTER_SEINENKI && map == 0x70) {
            map = 0x65;
        }
        int index = dq5::level::g_LevelDataUtility.getKimeraIndex(map);
        if (index != -1) {
            status::g_StageInfo.setKimeraSymbol(index);
        }
        dq5::level::VehicleData::cleanup();
    }
    status::g_StageAttribute.setKimeraSetDisable(false);
}

void twn::TownSystemScript::terminate()
{
    ScriptSystem::getSingleton()->terminate();
}

void twn::TownSystemScript::execute()
{
    trigger_ = true;
    ScriptSystem::getSingleton()->execute();
    scriptSearch_ = 0;
}

void twn::TownSystemScript::draw()
{
}

void twn::TownSystemScript::setEventLock(bool flag)
{
    if (flag == true) {
        eventLock_++;
    } else {
        eventLock_--;
    }
}

bool twn::TownSystemScript::isEventLock()
{
    if (eventLock_ > 0) {
        return true;
    }
    return false;
}
