#include "main/object/ModelObject.hpp"
#include "main/object/DSSAObject.hpp"
#include "nnsys/g3d.hpp"

ARM void UnkModelObjectBase::setupModel(UnkModelMember* member)
{
    member_ = member;
    NNSG3dResMdlSet* mdlSet = func_02083268(member->getModelFile());
    func_02080350(0, 0x93d, -0x93d, -0x93d);
    func_02080350(1, -0x93d, 0x93d, 0x93d);
    func_02080350(2, 0x93d, -0x93d, -0x93d);
    func_02080350(3, -0x93d, 0x93d, 0x93d);
    func_02080380(0, 0x7fff);
    func_02080380(1, 0x294a);
    func_02080380(2, 0x10);
    func_02080380(3, 0x210);
    func_02080390(0x2954, 0x18c6, 0);
    func_020803b0(0x20a, 0x38c6, 0);
    func_020803d0(0xf, 0, 2, 0, 0x1c, 0x800);
    count_ = mdlSet->dict.numEntry;
    for (int i = 0; i < count_; i++) {
        NNSG3dResMdl* mdl = NNS_G3dGetMdlByIdx(func_02083268(member->getModelFile()), i);
        func_0207fa78(&renderObj_[i], mdl);
        func_02082db0(mdl, 1, 0x40);
        func_02082db0(mdl, 1, 0x80);
        func_02082db0(mdl, 1, 0x200);
        func_02082db0(mdl, 1, 0x400);
        func_02082e1c(mdl, 1, 0xf);
        func_02082e1c(mdl, 1, 0x30);
        func_02082e1c(mdl, 1, 0xc0);
        func_02082e1c(mdl, 1, 0x3f000000);
        func_02082e1c(mdl, 1, 0x1f0000);
    }
    UnkModelObjectBase::vf00();
}

ARM void UnkModelObjectBase::vf00()
{
    m_scl.setFix32(1, 1, 1);
    m_pos.setFix32(0, 0, 0);
    m_rgb.setFix32(0, 0, 0);
    m_matrix.setIdentity();
}

ARM void UnkModelObjectBase::vf04()
{
}

ARM void UnkModelObjectBase::draw()
{
    for (int i = 0; i < count_; i++) {
        func_0208032c((VecFx32*)&m_scl);
        func_02080308(&m_pos);
        func_02070360(&m_matrix, &data_02124bb4.prmBaseRot);
        data_02124bb4.flag &= ~0xa4;
        func_020802dc();
        G3d_Render(&renderObj_[i]);
    }
    func_020802dc();
    func_02082604();
}

ARM void UnkModelObjectBase::setLightColor(int light, unsigned short color)
{
    switch (light) {
    case 0:
        func_02080380(0, color);
        break;
    case 1:
        func_02080380(1, color);
        break;
    case 2:
        func_02080380(2, color);
        break;
    case 3:
        func_02080380(3, color);
        break;
    }
}

ARM void UnkModelObjectBase::setLightVector(int light, dss::Vector3<dss::Fix16> vector)
{
    switch (light) {
    case 0:
        func_02080350(0, vector.vx.value, vector.vy.value, vector.vz.value);
        break;
    case 1:
        func_02080350(1, vector.vx.value, vector.vy.value, vector.vz.value);
        break;
    case 2:
        func_02080350(2, vector.vx.value, vector.vy.value, vector.vz.value);
        break;
    case 3:
        func_02080350(3, vector.vx.value, vector.vy.value, vector.vz.value);
        break;
    }
}

ARM void UnkModelObjectBase::addAnimation(NNSG3dAnmObj* obj)
{
    func_0207fb5c(renderObj_, obj);
}

ARM void UnkModelObjectBase::removeAnimation(NNSG3dAnmObj* obj)
{
    func_0207fbf4(renderObj_, obj);
}

ARM void UnkModelObjectBase::setModelScale(dss::Fix32Vector3 scale)
{
    m_scl = scale;
}

ARM void UnkModelObjectBase::setModelPosition(dss::Fix32Vector3 position)
{
    m_pos = position;
}

ARM void UnkModelObjectBase::setModelRotation(dss::Vector3<short> rotation)
{
    dss::UnkMatrix43 rotX;
    dss::UnkMatrix43 rotY;
    dss::UnkMatrix43 rotZ;
    m_rot = rotation;
    rotX.setRotX(m_rot.vx);
    rotY.setRotY(m_rot.vy);
    rotZ.setRotZ(m_rot.vz);
    m_matrix = rotX * rotY * rotZ;
}

ARM void UnkModelObjectBase::cleanup(int flag)
{
}
