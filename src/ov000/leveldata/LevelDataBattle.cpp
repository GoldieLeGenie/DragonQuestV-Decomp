#include "main/leveldata/LevelData.hpp"
#include "main/leveldata/EffectParam.hpp"
#include "main/leveldata/MonsterAnim.hpp"
#include "ov000/leveldata/CameraFile.hpp"

THUMB void dq5::level::LevelData::setupBattle()
{
    CameraFile::setup();
    EffectParam::setup();
    MonsterAnim::setup();
}

THUMB void dq5::level::LevelData::cleanupBattle()
{
    EffectParam::cleanup();
    MonsterAnim::cleanup();
}
