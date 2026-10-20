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

ARM void UnkOverlaySlot::load(int id)
{
    unload();
    FS_LoadOverlay(NULL, id);
    loaded_ = 1;
    id_ = id;
}

ARM void UnkOverlaySlot::unload()
{
    if (loaded_ == 0) {
        return;
    }
    FS_UnloadOverlay(NULL, id_);
    loaded_ = 0;
}

ARM void loadOverlay(int id)
{
    FS_LoadOverlay(NULL, id);
}

ARM void unloadOverlay(int id)
{
    FS_UnloadOverlay(NULL, id);
}

unsigned int data_0209a238 = 0x120071fe;

ARM void setPadLock(int flag)
{
    if (flag != 0) {
        data_0209a238 |= 0x8000;
    }
}

ARM int isPadInputBlocked()
{
    return data_0209a238 == 0x1200f1fe;
}
