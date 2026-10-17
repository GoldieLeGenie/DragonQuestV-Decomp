#include "ov001/town/TownFurniture.hpp"
#include "ov001/town/riseup/TownRiseupManager.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/PlayerStatus.hpp"
#include "main/text/TextAPI.hpp"

THUMB twn::TownFurnitureGold::TownFurnitureGold()
{
}

THUMB twn::TownFurnitureGold::~TownFurnitureGold()
{
}

THUMB void twn::TownFurnitureGold::setSecondMessage()
{
    addPartyGold();
    int chara = 0;
    for (int i = 0; i < status::g_Party.getCarriageOutCount(); i++) {
        if (!status::g_Party.getPlayerStatus(i).haveStatusInfo_.isDeath()) {
            chara = i;
            break;
        }
    }
    TextAPI::setMACRO0(0x12, 0x50000000, status::g_Party.getPlayerStatus(chara).haveStatusInfo_.haveStatus_.playerIndex_);
    TextAPI::setMACRO0(0x32, 0xf0000000, data_);
    addMessage(0xc44c4, true);
}

THUMB void twn::TownFurnitureGold::startRiseup()
{
    index_ = TownRiseupManager::getSingleton().setup(1000, getFurnPosition());
}

THUMB bool twn::TownFurnitureGold::endRiseup()
{
    TownFurnitureObject::endRiseup();
    return false;
}

THUMB void twn::TownFurnitureGold::addPartyGold()
{
    status::g_Party.addGold(data_);
}

THUMB bool twn::TownFurnitureGold::isRiseupEnd()
{
    return TownRiseupManager::getSingleton().isFinish(index_);
}
