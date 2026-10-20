#pragma ipa file
#include "main/cmn/CommonEffect.hpp"

inline DSSAObject2D::DSSAObject2D()
{
}

inline DSSAObject2D::~DSSAObject2D()
{
}

inline PaletteAnimation::~PaletteAnimation()
{
}

inline PaletteAnimationObject::PaletteAnimationObject()
{
    texture_ = 0;
}

inline void cmn::CommonEffectSimple::operator delete(void* p)
{
    freeSystemMemory(p);
}

inline int cmn::CommonEffectFlat::getType()
{
    return 0;
}

inline int cmn::CommonEffectOrtho::getType()
{
    return 2;
}

inline int cmn::CommonEffectCubic::getType()
{
    return 1;
}

THUMB cmn::CommonEffectSimple::CommonEffectSimple()
{
    effectData_ = 0;
}

THUMB cmn::CommonEffectSimple::~CommonEffectSimple()
{
}

THUMB int cmn::CommonEffectSimple::isEnable()
{
    return effectData_ != 0;
}

THUMB cmn::CommonEffectFlat::CommonEffectFlat()
{
}

THUMB cmn::CommonEffectFlat::~CommonEffectFlat()
{
}

THUMB void cmn::CommonEffectFlat::setup(CommonEffectData* data, int flag)
{
    effectData_ = data;
    texture_ = data->getTextureData();
    dssaEffect_.setup(effectData_->getAnimationData());
    dssaEffect_.setTexture(texture_);
    dssaEffect_.type_ = DSSAObjectWithCamera::Near;
    if (effectData_->isPamEnable()) {
        paletteAnim_.anim_.setup(effectData_->getPaletteAnimData());
        paletteAnim_.texture_ = (TextureObject*)texture_;
        paletteAnim_.colorCount_ = paletteAnim_.anim_.getColorCount();
    }
    rate_.value = 0x1000;
}

THUMB void cmn::CommonEffectFlat::cleanup(int flag)
{
    if (!isEnable()) {
        return;
    }
    paletteAnim_.unkfunc_02051648();
    dssaEffect_.cleanup();
    effectData_ = 0;
}

THUMB void cmn::CommonEffectFlat::draw()
{
    dssaEffect_.draw();
    dssaEffect_.execute();
    if (effectData_->isPamEnable()) {
        paletteAnim_.unkfunc_02051440();
    }
}

THUMB void cmn::CommonEffectFlat::setPosition(dss::Fix32Vector3& position)
{
    dssaEffect_.setPosition(position);
}

THUMB void cmn::CommonEffectFlat::setScale(dss::Fix32 scale)
{
    dss::Fix32Vector3 one(1, 1, 1);
    dssaEffect_.setScale(one * scale);
    rate_ = scale;
}

THUMB void cmn::CommonEffectFlat::setDisplayType(int type)
{
    dssaEffect_.type_ = (DSSAObjectWithCamera::CameraType)type;
}

THUMB void cmn::CommonEffectFlat::start()
{
    dssaEffect_.start(0);
    if (effectData_->isPamEnable()) {
        paletteAnim_.unkfunc_020513c0();
    }
}

THUMB int cmn::CommonEffectFlat::isEnd()
{
    return dssaEffect_.isEnd();
}

THUMB cmn::CommonEffectCubic::CommonEffectCubic()
{
}

THUMB cmn::CommonEffectCubic::~CommonEffectCubic()
{
}

THUMB void cmn::CommonEffectCubic::setup(CommonEffectData* data, int flag)
{
    int count = 0;
    effectData_ = data;
    model_.setup(data->getModelData(), flag);
    for (int i = 0; i < 4; i++) {
        if (effectData_->getAnimData(count)) {
            model_.unkfunc_02050954(effectData_->getAnimData(count), count);
            count++;
        }
    }
    rate_.value = 0x1000;
}

THUMB void cmn::CommonEffectCubic::cleanup(int flag)
{
    if (!isEnable()) {
        return;
    }
    model_.cleanup(flag);
    effectData_ = 0;
}

THUMB void cmn::CommonEffectCubic::draw()
{
    model_.draw();
}

THUMB void cmn::CommonEffectCubic::setPosition(dss::Fix32Vector3& position)
{
    model_.setPosition(position);
}

THUMB void cmn::CommonEffectCubic::setScale(dss::Fix32 scale)
{
    model_.setScale(scale);
    rate_ = scale;
}

THUMB void cmn::CommonEffectCubic::start()
{
    model_.start(0);
}

THUMB int cmn::CommonEffectCubic::isEnd()
{
    return model_.m_play_flag == 0;
}

THUMB void cmn::CommonEffectCubic::setDisplayType(int type)
{
    model_.type_ = (ModelObjectWithCamera::CameraType)type;
}

THUMB cmn::CommonEffectOrtho::CommonEffectOrtho()
{
}

THUMB cmn::CommonEffectOrtho::~CommonEffectOrtho()
{
}

THUMB void cmn::CommonEffectOrtho::setup(CommonEffectData* data, int flag)
{
    effectData_ = data;
    texture_ = data->getTextureData();
    dssaEffect_.setup(effectData_->getAnimationData());
    dssaEffect_.setTexture(texture_);
    if (effectData_->isPamEnable()) {
        paletteAnim_.anim_.setup(effectData_->getPaletteAnimData());
        paletteAnim_.texture_ = (TextureObject*)texture_;
        paletteAnim_.colorCount_ = paletteAnim_.anim_.getColorCount();
    }
    rate_.value = 0x1000;
}

THUMB void cmn::CommonEffectOrtho::cleanup(int flag)
{
    if (!isEnable()) {
        return;
    }
    paletteAnim_.unkfunc_02051648();
    dssaEffect_.cleanup();
    effectData_ = 0;
}

THUMB void cmn::CommonEffectOrtho::draw()
{
    dssaEffect_.draw();
    dssaEffect_.execute();
    if (effectData_->isPamEnable()) {
        paletteAnim_.unkfunc_02051440();
    }
}

THUMB void cmn::CommonEffectOrtho::setPosition(dss::Fix32Vector3& position)
{
    dssaEffect_.setPosition(position);
}

THUMB void cmn::CommonEffectOrtho::setScale(dss::Fix32 scale)
{
    dss::Fix32Vector3 one(1, 1, 1);
    dssaEffect_.setScale(one * scale);
    rate_ = scale;
}

THUMB void cmn::CommonEffectOrtho::setDisplayType(int type)
{
}

THUMB void cmn::CommonEffectOrtho::start()
{
    dssaEffect_.start(0);
    if (effectData_->isPamEnable()) {
        paletteAnim_.unkfunc_020513c0();
    }
}

THUMB int cmn::CommonEffectOrtho::isEnd()
{
    return dssaEffect_.isEnd();
}
