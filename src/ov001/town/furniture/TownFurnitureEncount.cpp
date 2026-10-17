#include "ov001/town/TownFurniture.hpp"
#include "ov001/leveldata/FurnitureParam.hpp"
#include "main/btl/Encount.hpp"
#include "main/status/StageInfo.hpp"
#include "main/text/TextAPI.hpp"

inline unsigned long dq5::level::FurnitureParam::getMonsterMsg()
{
    return monsterMsg;
}

THUMB twn::TownFurnitureEncount::TownFurnitureEncount()
{
}

THUMB twn::TownFurnitureEncount::~TownFurnitureEncount()
{
}

THUMB void twn::TownFurnitureEncount::setupExtend(int data)
{
    monster_ = data;
}

THUMB void twn::TownFurnitureEncount::setSecondMessage()
{
    TextAPI::setMACRO0(0x13, 0x60000000, monster_);
    addMessage(common_->getMonsterMsg(), true);
}

THUMB void twn::TownFurnitureEncount::cleanup()
{
    TownFurnitureObject::cleanup();
    btl::Encount::getSingleton()->forceBrew(data_);
    status::g_StageInfo.encountMapUid_ = uid_;
}
