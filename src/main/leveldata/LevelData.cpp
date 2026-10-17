#include "main/leveldata/LevelData.hpp"
#include "main/leveldata/ActionParam.hpp"
#include "main/leveldata/ActionTypeList.hpp"
#include "main/leveldata/AppriseItem.hpp"
#include "main/leveldata/BattleMap.hpp"
#include "main/leveldata/BookData.hpp"
#include "main/leveldata/CLUTCode.hpp"
#include "main/leveldata/CharaData.hpp"
#include "main/leveldata/CharacterInitData.hpp"
#include "main/leveldata/EffectColorParam.hpp"
#include "main/leveldata/EffectMessage.hpp"
#include "main/leveldata/EncountData.hpp"
#include "main/leveldata/EncountLayout.hpp"
#include "main/leveldata/EncountSpecial.hpp"
#include "main/leveldata/FieldSymbol.hpp"
#include "main/leveldata/FloorList.hpp"
#include "main/leveldata/FloorParam.hpp"
#include "main/leveldata/ItemData.hpp"
#include "main/leveldata/MonsterData.hpp"
#include "main/leveldata/PokerMessage.hpp"
#include "main/leveldata/ShopData1.hpp"
#include "main/leveldata/ShopData2.hpp"
#include "main/leveldata/ShopData3.hpp"
#include "main/leveldata/ShopDataSugoroku.hpp"
#include "main/leveldata/ShopIndex1.hpp"
#include "main/leveldata/ShopIndex2.hpp"
#include "main/leveldata/ShopIndex3.hpp"
#include "main/leveldata/ShopIndexSugoroku.hpp"
#include "main/leveldata/SlotDrum.hpp"
#include "main/leveldata/SlotMessage.hpp"
#include "main/leveldata/SplitMessage.hpp"
#include "main/leveldata/StadiumCard.hpp"
#include "main/leveldata/StadiumMessage.hpp"
#include "main/leveldata/TimeZone.hpp"
#include "main/leveldata/VehicleData.hpp"

dq5::level::LevelData dq5::level::levelData;

THUMB dq5::level::LevelData::LevelData()
{
}

THUMB dq5::level::LevelData::~LevelData()
{
}

THUMB void dq5::level::LevelData::setup()
{
    info_.setup("data/leveldata/infocontainer.dat", 1, 0);
    FloorList::setup();
    FloorParam::setup();
    EncountData::setup();
    EncountSpecial::setup();
    MonsterData::setup();
    CharacterInitData::setup();
    EncountLayout::setup();
    ActionParam::setup();
    ActionTypeList::setup();
    EffectMessage::setup();
    SplitMessage::setup();
    ItemData::setup();
    AppriseItem::setup();
    ShopIndex1::setup();
    ShopIndex2::setup();
    ShopIndex3::setup();
    ShopIndexSugoroku::setup();
    ShopData1::setup();
    ShopData2::setup();
    ShopData3::setup();
    ShopDataSugoroku::setup();
    SlotMessage::setup();
    StadiumMessage::setup();
    PokerMessage::setup();
    SlotDrum::setup();
    StadiumCard::setup();
    CharaData::setup();
    BookData::setup();
    FieldSymbol::setup();
    VehicleData::setup();
    TimeZone::setup();
    CLUTCode::setup();
    BattleMap::setup();
    EffectColorParam::setup();
}

THUMB int dq5::level::LevelData::getLoadType(int index)
{
    ExcelBinaryInfo* binaryInfo = (ExcelBinaryInfo*)info_.getAddr();
    return binaryInfo[index].uic_;
}
