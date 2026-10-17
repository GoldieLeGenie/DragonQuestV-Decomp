#include "main/window/WorldMap.hpp"
#include "main/leveldata/FieldSymbol.hpp"
#include "main/status/StageInfo.hpp"

inline dq5::level::FieldSymbol* dq5::level::FieldSymbol::getRecord(int index)
{
    return (FieldSymbol*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned int dq5::level::FieldSymbol::getArraySize()
{
    return binary_.record_;
}

inline unsigned char dq5::level::FieldSymbol::getPosY()
{
    return posY;
}

inline unsigned char dq5::level::FieldSymbol::getPosX()
{
    return posX;
}

inline char dq5::level::FieldSymbol::getWorld()
{
    return byte_1 & 3;
}

inline char dq5::level::FieldSymbol::getSymbol()
{
    return (byte_1 & 0x3c) >> 2;
}

THUMB window::WorldMap::WorldMap()
{
}

THUMB window::WorldMap::~WorldMap()
{
}

THUMB void window::WorldMap::symbolDraw(int world)
{
    for (unsigned int i = 0; i < dq5::level::FieldSymbol::getArraySize(); i++) {
        if (dq5::level::FieldSymbol::getRecord(i)->getWorld() == world && dq5::level::FieldSymbol::getRecord(i)->getSymbol() != 0 &&
            status::g_StageInfo.getSymbolFlag(i)) {
            int y = dq5::level::FieldSymbol::getRecord(i)->getPosY();
            int x = dq5::level::FieldSymbol::getRecord(i)->getPosX();
            unk_54.unkfunc_02051b14(x - 1, y - 3);
            unk_54.unkfunc_02051bbc(0x1f, dss::abs(unk_a4 / 4), 0);
            unk_54.unkfunc_02051b68();
        }
    }
    unk_a4++;
    if (unk_a4 >= 0x80) {
        unk_a4 = -0x7f;
    }
}
