#include "ov005/fld/FieldCarrierDraw.hpp"

THUMB fld::SpriteShipCharacter::SpriteShipCharacter()
{
}

THUMB fld::SpriteShipCharacter::~SpriteShipCharacter()
{
}

THUMB void fld::SpriteShipCharacter::setup(const char* name)
{
    SpriteCharacter::setup(name, 0x20, 0x20, 0);
    frameHeight_ = 0x18;
    frameWidth_ = 0x20;
    resetFrame();
}

THUMB void fld::SpriteShipCharacter::execute()
{
    if (flag_.check(FLAG_ANIM_NEUTRAL)) {
        if (!allFlag_.check(FLAG_ANIM)) {
            return;
        }
    } else if (!flag_.check(FLAG_ANIM)) {
        return;
    }
    switch (anmIndex_ / 6) {
        case 0:
            unkfunc_02047ecc(0, 0, 0x20, 0x18);
            break;
        case 1:
            unkfunc_02047ecc(0x20, 0, 0x40, 0x18);
            break;
        case 2:
            unkfunc_02047ecc(0x40, 0, 0x60, 0x18);
            break;
        case 3:
            unkfunc_02047ecc(0x60, 0, 0x80, 0x18);
            break;
        case 4:
            unkfunc_02047ecc(0, 0x18, 0x20, 0x30);
            break;
        case 5:
            unkfunc_02047ecc(0x20, 0x18, 0x40, 0x30);
            break;
        case 6:
            unkfunc_02047ecc(0x40, 0x18, 0x60, 0x30);
            break;
    }
    anmIndex_++;
    anmIndex_ = dss::loop<long>(anmIndex_, 0, 0x2a);
}
