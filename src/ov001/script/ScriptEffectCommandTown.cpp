#pragma ipa file
#include "ov001/script/ScriptEffectCommandTown.hpp"
#include "ov001/town/riseup/TownRiseupManager.hpp"
#include "main/script/CommandParam.hpp"

inline ScriptCommand::ScriptCommand()
{
}

inline ScriptCommand::~ScriptCommand()
{
}

THUMB void Riseup_move::initialize(char* scriptParam)
{
    PARAM_RISEUP_MOVE* param = (PARAM_RISEUP_MOVE*)scriptParam;
    dss::Fix32Vector3 startPos;
    dss::Fix32Vector3 endPos;
    startPos.vx.value = param->startX;
    startPos.vy.value = param->startY;
    startPos.vz.value = param->startZ;
    endPos.vx.value = param->endX;
    endPos.vy.value = param->endY;
    endPos.vz.value = param->endZ;
    index = twn::TownRiseupManager::getSingleton().setupScript(param->item, startPos, endPos, param->frame);
}

THUMB int Riseup_move::isEnd()
{
    return twn::TownRiseupManager::getSingleton().isFinish(index);
}

THUMB void Riseup_move::execute()
{
}

Riseup_move gRiseup_move;
