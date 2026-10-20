#include "main/dss/CharacterPalette.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/dss/VramTransferManager.hpp"

ARM CharacterPalette::CharacterPalette()
{
    size_ = 0;
    address_ = 0;
    handle_ = 0;
    enable_ = 0;
}

ARM CharacterPalette::~CharacterPalette()
{
}

ARM void CharacterPalette::unkfunc_0204a3f4(TextureObject* texture, int flag)
{
    int data = texture->unkfunc_0204a1d4();
    int size = texture->unkfunc_0204a1dc();
    dss::memcpy(palette_, (void*)data, size);
    size_ = size;
    handle_ = data_020f4f74.allocPlttVram(size);
    address_ = data_020f4f74.getPlttVramAddr(handle_);
    unkfunc_02086d78(flag);
    texFormat_ = texture->unk_20;
    enable_ = 0;
}

ARM void CharacterPalette::unkfunc_0204a474()
{
    if (handle_ != 0) {
        data_020f4f74.freePlttVram(handle_);
        handle_ = 0;
    }
}

ARM void CharacterPalette::unkfunc_02086d78(int flag)
{
    data_020f4f74.transferToVram(1, palette_, address_, size_, flag);
}

ARM void CharacterPalette::unkfunc_0204a4d4()
{
    if (enable_ == 0) {
        return;
    }
    *(volatile unsigned int*)0x040004ac = (unsigned int)address_ >> (4 - (texFormat_ == 2));
}
