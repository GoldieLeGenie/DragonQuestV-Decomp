#include "main/object/PaletteAnimationObject.hpp"
#include "main/dss/VramTransferManager.hpp"

unsigned short data_02101a68[256];

ARM PaletteAnimation::PaletteAnimation()
{
    frame16_ = 0;
    frame256_ = 0;
}

ARM void PaletteAnimation::setup(void* data)
{
    UnkPaletteAnimationHeader* header = (UnkPaletteAnimationHeader*)data;
    header_ = *header++;
    if (header_.mode_ == 0) {
        frame16_ = (UnkPaletteFrame16*)header;
    } else {
        frame256_ = (UnkPaletteFrame256*)header;
    }
}

ARM int PaletteAnimation::getWait(int frame)
{
    if (header_.mode_ == 0) {
        return frame16_[frame].wait_;
    }
    return frame256_[frame].wait_;
}

ARM unsigned short* PaletteAnimation::getColor(int frame)
{
    if (header_.mode_ == 0) {
        return frame16_[frame].color_;
    }
    return frame256_[frame].color_;
}

ARM int PaletteAnimation::getColorCount()
{
    if (header_.mode_ == 0) {
        return 16;
    }
    return 256;
}

ARM int PaletteAnimation::getFrameCount()
{
    return header_.frameCount_;
}

ARM void PaletteAnimationObject::unkfunc_020513c0()
{
    wait_ = 0;
    frame_ = 0;
    dss::memcpy(data_02101a68, anim_.getColor(frame_), anim_.getColorCount() * 2);
    data_020f4f74.transferToVram(1, data_02101a68, texture_->unkfunc_0204a1cc(), texture_->unkfunc_0204a1dc(), 0);
}

ARM void PaletteAnimationObject::unkfunc_02051440()
{
    wait_++;
    if (wait_ < anim_.getWait(frame_)) {
        return;
    }
    wait_ = 0;
    frame_++;
    if (frame_ >= anim_.getFrameCount()) {
        frame_ = 0;
    }
    dss::memcpy(data_02101a68, anim_.getColor(frame_), anim_.getColorCount() * 2);
    data_020f4f74.transferToVram(1, data_02101a68, texture_->unkfunc_0204a1cc(), texture_->unkfunc_0204a1dc(), 0);
}

ARM void PaletteAnimationObject::unkfunc_0205150c(int address, int size)
{
    wait_ = 0;
    frame_ = 0;
    dss::memcpy(data_02101a68, anim_.getColor(frame_), anim_.getColorCount() * 2);
    data_020f4f74.transferToVram(1, data_02101a68, address, size, 0);
}

ARM void PaletteAnimationObject::unkfunc_02051580(int address, int size)
{
    wait_++;
    if (wait_ < anim_.getWait(frame_)) {
        return;
    }
    dss::memcpy(data_02101a68, anim_.getColor(frame_), anim_.getColorCount() * 2);
    data_020f4f74.transferToVram(1, data_02101a68, address, size, 0);
    wait_ = 0;
    frame_++;
}

ARM int PaletteAnimationObject::unkfunc_02051628()
{
    return frame_ >= anim_.getFrameCount();
}

ARM void PaletteAnimationObject::unkfunc_02051648()
{
    colorCount_ = 0;
    texture_ = 0;
}
