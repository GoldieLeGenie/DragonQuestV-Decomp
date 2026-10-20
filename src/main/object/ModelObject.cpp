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
    unk_1cc.setModelFile(modelData_.getAddr());
    unkfunc_02048d08(&unk_1cc);
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
    unk_1cc.release();
}

ARM void ModelObject::setup(const char* name, const char* animName, int loadSwitch)
{
    modelData_.setup(name, loadSwitch, 0);
    unk_1cc.setModelFile(modelData_.getAddr());
    unkfunc_02048d08(&unk_1cc);
}

ARM void ModelObject::setup(void* model, int flag)
{
    modelData_.setup(model);
    if (flag == 0) {
        data_020f3e88 = 1;
    }
    unk_1cc.setModelFile(modelData_.getAddr());
    unkfunc_02048d08(&unk_1cc);
    vf00();
}

ARM void ModelObject::vf00()
{
    m_play_flag = 0;
    m_animation_index = 0;
}

ARM void ModelObject::unkfunc_020508b8(const char* name, int index, int loadSwitch)
{
    DataObject& data = animData_[index];
    data.setup(name, loadSwitch, 0);
    if (data.getAddr() == 0) {
        return;
    }
    animation_[index].unkfunc_020465e0(data.getAddr(), unk_1cc.getModel());
    unkfunc_02049104(animation_[index].obj_);
    if (index == 0) {
        animation_[index].obj_->ratio = FX32_ONE;
    } else {
        animation_[index].obj_->ratio = 0;
    }
}

ARM void ModelObject::unkfunc_02050954(void* animation, int index)
{
    DataObject& data = animData_[index];
    data.setup(animation);
    if (data.getAddr() == 0) {
        return;
    }
    animation_[index].unkfunc_020465e0(data.getAddr(), unk_1cc.getModel());
    unkfunc_02049104(animation_[index].obj_);
}

ARM void ModelObject::cleanup(int flag)
{
    for (int i = 0; i < 6; i++) {
        if (animData_[i].getAddr()) {
            unkfunc_02049114(animation_[i].obj_);
            animation_[i].unkfunc_02046644();
        }
    }
    UnkModelObjectBase::vf04();
    modelData_.cleanup();
    for (int i = 0; i < 6; i++) {
        animData_[i].cleanup();
    }
    if (flag) {
        unk_1cc.release();
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
                animation_[i].unkfunc_0204667c();
            }
        }
    }
    if (animation_[m_animation_index].unkfunc_020466c4()) {
        m_play_flag = 0;
    }
}

ARM void ModelObject::start(int loop)
{
    m_play_flag = 1;
    for (int i = 0; i < 6; i++) {
        if (animData_[i].getAddr()) {
            animation_[i].unkfunc_02046658(loop);
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
    unkfunc_02049124(v);
}

ARM void ModelObject::setScale(const dss::Fix32Vector3& scale)
{
    unkfunc_02049124(scale);
}

ARM void ModelObject::setPosition(const dss::Fix32Vector3& position)
{
    unkfunc_02049134(position);
}

ARM void ModelObject::setRotationIdx(const dss::Vector3<short>& rotation)
{
    unkfunc_02049144(rotation);
}

ARM void ModelObject::pause(int flag)
{
    m_pause_flag = flag;
}
