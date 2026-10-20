#include "main/object/ModelObject.hpp"

inline dss::Fix32Vector3::Fix32Vector3(const Fix32& x, const Fix32& y, const Fix32& z)
{
    vx = x;
    vy = y;
    vz = z;
}

dss::Fix32 ModelObject::defaultScale(FX32_ONE * 6);

ARM void UnkStaticModelObject::setup(const char* name, int loadSwitch)
{
    modelData_.setup(name, loadSwitch, 0);
    model_.setModelFile(modelData_.getAddr());
    setupModel(&model_);
    vf00();
}

ARM void UnkStaticModelObject::vf00()
{
    UnkModelObjectBase::vf00();
}

ARM void UnkStaticModelObject::vf04()
{
    UnkModelObjectBase::vf04();
    modelData_.cleanup();
    model_.release();
}

ARM void ModelObject::setup(const char* name, const char* animName, int loadSwitch)
{
    modelData_.setup(name, loadSwitch, 0);
    model_.setModelFile(modelData_.getAddr());
    setupModel(&model_);
}

ARM void ModelObject::setup(void* model, int flag)
{
    modelData_.setup(model);
    if (flag == 0) {
        data_020f3e88 = 1;
    }
    model_.setModelFile(modelData_.getAddr());
    setupModel(&model_);
    vf00();
}

ARM void ModelObject::vf00()
{
    m_play_flag = 0;
    m_animation_index = 0;
}

ARM void ModelObject::loadAnimation(const char* name, int index, int loadSwitch)
{
    DataObject& data = animData_[index];
    data.setup(name, loadSwitch, 0);
    if (data.getAddr() == 0) {
        return;
    }
    animation_[index].setup(data.getAddr(), model_.getModel());
    addAnimation(animation_[index].obj_);
    if (index == 0) {
        animation_[index].obj_->ratio = FX32_ONE;
    } else {
        animation_[index].obj_->ratio = 0;
    }
}

ARM void ModelObject::setAnimation(void* animation, int index)
{
    DataObject& data = animData_[index];
    data.setup(animation);
    if (data.getAddr() == 0) {
        return;
    }
    animation_[index].setup(data.getAddr(), model_.getModel());
    addAnimation(animation_[index].obj_);
}

ARM void ModelObject::cleanup(int flag)
{
    for (int i = 0; i < 6; i++) {
        if (animData_[i].getAddr()) {
            removeAnimation(animation_[i].obj_);
            animation_[i].cleanup();
        }
    }
    UnkModelObjectBase::vf04();
    modelData_.cleanup();
    for (int i = 0; i < 6; i++) {
        animData_[i].cleanup();
    }
    if (flag) {
        model_.release();
    }
}

ARM void ModelObject::draw()
{
    if (!m_play_flag) {
        return;
    }
    UnkModelObjectBase::draw();
    if (!m_pause_flag) {
        for (int i = 0; i < 6; i++) {
            if (animData_[i].getAddr()) {
                animation_[i].execute();
            }
        }
    }
    if (animation_[m_animation_index].isEnd()) {
        m_play_flag = 0;
    }
}

ARM void ModelObject::start(int loop)
{
    m_play_flag = 1;
    for (int i = 0; i < 6; i++) {
        if (animData_[i].getAddr()) {
            animation_[i].start(loop);
        }
    }
}

ARM void ModelObject::startAnimation(int index, int loop)
{
    for (int i = 0; i < 6; i++) {
        if (animData_[i].getAddr()) {
            if (i == index) {
                animation_[i].obj_->ratio = FX32_ONE;
            } else {
                animation_[i].obj_->ratio = 0;
            }
        }
    }
    m_animation_index = index;
    start(loop);
}

ARM void ModelObject::setScale(dss::Fix32 scale)
{
    dss::Fix32Vector3 v(defaultScale, defaultScale, defaultScale);
    v *= scale;
    setModelScale(v);
}

ARM void ModelObject::setScale(const dss::Fix32Vector3& scale)
{
    setModelScale(scale);
}

ARM void ModelObject::setPosition(const dss::Fix32Vector3& position)
{
    setModelPosition(position);
}

ARM void ModelObject::setRotationIdx(const dss::Vector3<short>& rotation)
{
    setModelRotation(rotation);
}

ARM void ModelObject::pause(int flag)
{
    m_pause_flag = flag;
}
