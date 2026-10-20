#include "ov005/fld/FieldSymbolAnimation.hpp"
#include "main/dss/UnkArchive.hpp"

THUMB fld::FieldSymbolAnimation::FieldSymbolAnimation() : enable_(0)
{
}

THUMB fld::FieldSymbolAnimation::~FieldSymbolAnimation()
{
}

THUMB void fld::FieldSymbolAnimation::setup(const char* filename)
{
    data_.setup(filename, 1, 0);
    enable_ = 1;
    animId_ = 0;
}

THUMB void fld::FieldSymbolAnimation::calcAnim(TextureObject* texture)
{
    if (enable_ != 0 && texture != NULL) {
        int frame = animId_ / 8;
        if (frame == 8) {
            cleanup();
            return;
        }
        if (animId_ % 8 == 0) {
            texture->transferFrom((TextureObject*)getArchiveFile(data_.getAddr(), frame), 0);
        }
        animId_++;
    }
}

THUMB void fld::FieldSymbolAnimation::cleanup()
{
    data_.cleanup();
    enable_ = 0;
}
