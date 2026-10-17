#include "main/dss/UnkVramTransfer.hpp"
#include "nitro/os.hpp"

UnkVramTransfer data_020f4f74;

ARM UnkVramTransfer::UnkVramTransfer()
{
    unk_00 = 0;
    unk_810 = 0;
    unk_814 = 1;
}

ARM UnkVramTransfer::~UnkVramTransfer()
{
}

ARM void UnkVramTransfer::unkfunc_0204a528()
{
    func_02086778(tasks_, 0x80);
}

unsigned char data_020f578c[0x800];
unsigned char data_020f5f8c[0x800];

ARM void UnkVramTransfer::unkfunc_0204a53c(int texSize, int plttSize)
{
    texSize_ = texSize;
    unk_00 = 0;
    unk_04 = 0;
    unk_08 = texSize;
    func_02086aa4(texSize, 0, data_020f5f8c, func_02086aa0(0x80), 1);
    if (texSize_ == 0x40000) {
        int handle1 = unkfunc_0204a5f4(0x20000);
        int handle2 = unkfunc_0204a5f4(0x20000);
        unkfunc_0204a618(handle1);
        unkfunc_0204a618(handle2);
    }
    func_02086cc8(plttSize, data_020f578c, func_02086cc4(0x80), 1);
}

ARM void UnkVramTransfer::unkfunc_0204a5f0()
{
}

ARM int UnkVramTransfer::unkfunc_0204a5f4(int size)
{
    return (*data_0209c788)(size, 0, 0);
}

ARM void UnkVramTransfer::unkfunc_0204a618(unsigned int handle)
{
    (*data_0209c78c)(handle);
}

ARM int UnkVramTransfer::unkfunc_0204a634(unsigned int handle)
{
    return (handle & 0xffff) << 3;
}

ARM int UnkVramTransfer::unkfunc_0204a640(unsigned int handle)
{
    return ((handle & 0x7fff0000) >> 16) << 4;
}

ARM int UnkVramTransfer::unkfunc_0204a658(int size)
{
    int handle = (*data_0209c790)(size, 0, 0);
    unk_04 += size;
    return handle;
}

ARM void UnkVramTransfer::unkfunc_0204a690(unsigned int handle)
{
    (*data_0209c794)(handle);
    unk_04 -= unkfunc_02086360(handle);
}

ARM int UnkVramTransfer::unkfunc_0204a6cc(unsigned int handle)
{
    return (handle & 0xffff) << 3;
}

ARM int UnkVramTransfer::unkfunc_02086360(unsigned int handle)
{
    return ((handle & 0xffff0000) >> 16) << 3;
}

ARM void UnkVramTransfer::unkfunc_0204a6f0(int type, void* src, int address, unsigned int size, int flag)
{
    if (unk_814 != 0) {
        func_020867d0(type, address, src, size);
        if (flag != 0) {
            unkfunc_0204a7cc();
        }
        return;
    }
    if (flag != 0 && func_02086814() != 0) {
        OS_Wait();
        unkfunc_0204a7cc();
        while ((int)*(volatile unsigned short*)0x04000006 > 1) {
        }
    }
    unsigned int remain = size;
    do {
        unsigned int length;
        if (remain > 0x8000) {
            length = 0x8000;
            flag = 1;
        } else {
            length = remain;
        }
        func_020867d0(type, address, src, length);
        if (flag != 0) {
            OS_Wait();
            unkfunc_0204a7cc();
            while ((int)*(volatile unsigned short*)0x04000006 > 1) {
            }
        }
        address += length;
        src = (unsigned char*)src + length;
        remain -= length;
    } while (remain != 0);
}

ARM void UnkVramTransfer::unkfunc_0204a7cc()
{
    func_02086790();
    unk_810 = 0;
}
