#include "ov001/town/TownFurniture.hpp"
#include "ov001/town/TownWindowSystem.hpp"
#include "ov001/leveldata/FurnitureParam.hpp"
#include "main/cmn/PartyTalk.hpp"

inline unsigned long dq5::level::FurnitureParam::getNormalMsg()
{
    return normalMsg;
}

inline unsigned long dq5::level::FurnitureParam::getCheckMsg()
{
    return checkMsg;
}

THUMB twn::TownFurnitureMessage::TownFurnitureMessage()
{
}

THUMB twn::TownFurnitureMessage::~TownFurnitureMessage()
{
}

THUMB void twn::TownFurnitureMessage::setFirstMessage()
{
    if (checkMsg() != 0 || common_->getNormalMsg() != 0) {
        if (common_->getCheckMsg() != 0) {
            addMessage(common_->getCheckMsg(), false);
        }
        if (data_ != 0) {
            TownWindowSystem::getSingleton().waitCommonMessage();
        }
    }
}

THUMB void twn::TownFurnitureMessage::setSecondMessage()
{
    if (data_ != 0) {
        addMessage(data_, true);
        cmn::PartyTalk::getSingleton().setPreMessageNo(data_);
    }
}
