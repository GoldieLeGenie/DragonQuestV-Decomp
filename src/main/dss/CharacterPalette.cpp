#include "main/dss/CharacterPalette.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/dss/VramTransferManager.hpp"

ARM CharacterPalette::CharacterPalette()
{
    unk_404 = 0;
    unk_408 = 0;
    unk_40c = 0;
    enable_ = 0;
}

ARM CharacterPalette::~CharacterPalette()
{
}

ARM void CharacterPalette::unkfunc_0204a3f4(TextureObject* texture, int flag)
{
    int data = texture->unkfunc_0204a1d4();
    int size = texture->unkfunc_0204a1dc();
    dss::memcpy(unk_000, (void*)data, size);
    unk_404 = size;
    unk_40c = data_020f4f74.allocPlttVram(size);
    unk_408 = data_020f4f74.getPlttVramAddr(unk_40c);
    unkfunc_02086d78(flag);
    unk_400 = texture->unk_20;
    enable_ = 0;
}

ARM void CharacterPalette::unkfunc_0204a474()
{
    if (unk_40c != 0) {
        data_020f4f74.freePlttVram(unk_40c);
        unk_40c = 0;
    }
}

ARM void CharacterPalette::unkfunc_02086d78(int flag)
{
    data_020f4f74.transferToVram(1, unk_000, unk_408, unk_404, flag);
}

ARM void CharacterPalette::unkfunc_0204a4d4()
{
    if (enable_ == 0) {
        return;
    }
    *(volatile unsigned int*)0x040004ac = (unsigned int)unk_408 >> (4 - (unk_400 == 2));
}
