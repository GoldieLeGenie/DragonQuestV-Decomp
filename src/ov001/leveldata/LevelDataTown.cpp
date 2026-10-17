#include "main/leveldata/LevelData.hpp"
#include "main/leveldata/MapCamera.hpp"
#include "main/leveldata/ColorCorrect.hpp"
#include "ov001/leveldata/FloorBackColor.hpp"
#include "ov001/leveldata/FloorFog.hpp"
#include "ov001/leveldata/FurnitureData.hpp"
#include "ov001/leveldata/FurnitureParam.hpp"
#include "ov001/leveldata/MirrorMessage.hpp"
#include "ov001/leveldata/BoobyTrap.hpp"

THUMB void dq5::level::LevelData::setupTown()
{
    FloorFog::setup();
    FloorBackColor::setup();
    ColorCorrect::setup();
    FurnitureData::setup();
    FurnitureParam::setup();
    MirrorMessage::setup();
    BoobyTrap::setup();
    MapCamera::setup();
}

THUMB void dq5::level::LevelData::cleanupTown()
{
    FloorFog::cleanup();
    FloorBackColor::cleanup();
    ColorCorrect::cleanup();
    FurnitureData::cleanup();
    FurnitureParam::cleanup();
    MirrorMessage::cleanup();
    BoobyTrap::cleanup();
    MapCamera::cleanup();
}
