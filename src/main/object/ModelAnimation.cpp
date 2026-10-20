#include "main/object/ModelObject.hpp"
#include "main/dss/UnkMemory.hpp"

inline bool ModelAnimation::checkFlag(int bit) const
{
    return (flag_ & bit) ? true : false;
}

ARM void ModelAnimation::unkfunc_020465e0(void* resource, void* model)
{
    resource_ = resource;
    func_0207ebe4(&allocator_, (int)*unkfunc_0204c618(&data_020fd24c), 4);
    anm_ = func_02083298(resource_, 0);
    obj_ = func_02082d90(&allocator_, anm_, model);
    func_0207fa14(obj_, anm_, model, NULL);
}

ARM void ModelAnimation::unkfunc_02046644()
{
    func_02082da8(&allocator_, obj_);
}

ARM void ModelAnimation::unkfunc_02046658(int loop)
{
    obj_->frame = 0;
    flag_ = 0;
    if (loop) {
        flag_ |= 1;
    }
}

ARM void ModelAnimation::unkfunc_0204667c()
{
    obj_->frame += FX32_ONE;
    if (obj_->frame < ((unsigned short*)obj_->resAnm)[2] << 12) {
        return;
    }
    if (checkFlag(1)) {
        obj_->frame = 0;
    } else {
        flag_ |= 2;
    }
}

ARM int ModelAnimation::unkfunc_020466c4()
{
    return checkFlag(2);
}
