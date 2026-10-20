#pragma ipa file
#include "main/ceremony/UnkCeremonyEndingFin.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/dss/RenderObject.hpp"
#include "main/dss/UnkDisplay.hpp"

inline UnkLZDataObject::UnkLZDataObject()
{
}

THUMB ceremony::UnkCeremonyEndingFin::UnkCeremonyEndingFin()
{
}

THUMB ceremony::UnkCeremonyEndingFin::~UnkCeremonyEndingFin()
{
}

THUMB ceremony::UnkCeremonyEndingFin* ceremony::UnkCeremonyEndingFin::getSingleton()
{
    static UnkCeremonyEndingFin s_instance;
    return &s_instance;
}

THUMB void ceremony::UnkCeremonyEndingFin::initialize()
{
    char path[0x80];

    frame_ = 0;
    dss::sprintf_s(path, sizeof(path), "data/ending/fin/fin_000.tex.lz");
    textureData_.setup(path, 0, 1);
    texture_ = (TextureObject*)textureData_.getAddr();
    texture_->unkfunc_02049e9c(1);
    sprite_.texture_ = texture_;
    sprite_.unkfunc_02047e88(0x48, 0x20);
    sprite_.unkfunc_02047ecc(0, 0, 0x80, 0x60);
    sprite_.unkfunc_02047ec0(0x80, 0x60);
    sprite_.screens_ = 1;
    enable_ = true;
}

THUMB void ceremony::UnkCeremonyEndingFin::terminate()
{
    frameData_.cleanup();
    texture_->unkfunc_02049f90();
    textureData_.cleanup();
}

THUMB void ceremony::UnkCeremonyEndingFin::execute()
{
    animTheEnd();
}

THUMB void ceremony::UnkCeremonyEndingFin::draw()
{
    RenderObject* sprite;

    setupOrtho2D();
    sprite = &sprite_;
    sprite->draw();
}

THUMB void ceremony::UnkCeremonyEndingFin::animTheEnd()
{
    char path[0x80];

    if (enable_ && (getDisplayFrame() & 1)) {
        if (frameData_.getAddr() != NULL) {
            frameData_.cleanup();
        }
        dss::sprintf_s(path, sizeof(path), "data/ending/fin/fin_%03d.tex.lz", frame_);
        frameData_.setup(path, 0, 1);
        frameAddr_ = frameData_.getAddr();
        dss::memcpy((void*)texture_->unkfunc_0204a1c4(),
                    (char*)frameAddr_ + ((TextureObject*)frameAddr_)->unkfunc_0204a1c4(), 0x1800);
        texture_->unkfunc_0204a090(0);
        if (++frame_ == 0xb5) {
            enable_ = false;
        }
    }
}

THUMB bool ceremony::UnkCeremonyEndingFin::isEnd()
{
    return !enable_;
}
