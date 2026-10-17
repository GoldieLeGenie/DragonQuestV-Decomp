#include "main/dss/UnkOverlaySlot.hpp"
#include "nitro/fs.hpp"

ARM UnkOverlaySlot::UnkOverlaySlot()
{
    loaded_ = 0;
    id_ = 0;
}

ARM UnkOverlaySlot::~UnkOverlaySlot()
{
}

ARM void UnkOverlaySlot::unkfunc_0204b580(int id)
{
    unkfunc_0204b5a8();
    FS_LoadOverlay(NULL, id);
    loaded_ = 1;
    id_ = id;
}

ARM void UnkOverlaySlot::unkfunc_0204b5a8()
{
    if (loaded_ == 0) {
        return;
    }
    FS_UnloadOverlay(NULL, id_);
    loaded_ = 0;
}

ARM void unkfunc_0204b5d4(int id)
{
    FS_LoadOverlay(NULL, id);
}

ARM void unkfunc_0204b5e8(int id)
{
    FS_UnloadOverlay(NULL, id);
}

unsigned int data_0209a238 = 0x120071fe;

ARM void unkfunc_0204b5fc(int flag)
{
    if (flag != 0) {
        data_0209a238 |= 0x8000;
    }
}

ARM int unkfunc_0204b61c()
{
    return data_0209a238 == 0x1200f1fe;
}
