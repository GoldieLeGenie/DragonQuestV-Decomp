#include "main/dss/VramTransferManager.hpp"
#include "nitro/os.hpp"

VramTransferManager data_020f4f74;

ARM VramTransferManager::VramTransferManager()
{
    unk_00 = 0;
    unk_810 = 0;
    vblankTransfer_ = 1;
}

ARM VramTransferManager::~VramTransferManager()
{
}

ARM void VramTransferManager::initTransferQueue()
{
    func_02086778(tasks_, 0x80);
}

unsigned char data_020f578c[0x800];
unsigned char data_020f5f8c[0x800];

ARM void VramTransferManager::initVramManagers(int texSize, int plttSize)
{
    texSize_ = texSize;
    unk_00 = 0;
    plttUsed_ = 0;
    texVramFree_ = texSize;
    func_02086aa4(texSize, 0, data_020f5f8c, func_02086aa0(0x80), 1);
    if (texSize_ == 0x40000) {
        int handle1 = allocTexVram(0x20000);
        int handle2 = allocTexVram(0x20000);
        freeTexVram(handle1);
        freeTexVram(handle2);
    }
    func_02086cc8(plttSize, data_020f578c, func_02086cc4(0x80), 1);
}

ARM void VramTransferManager::onPartTerminate()
{
}

ARM int VramTransferManager::allocTexVram(int size)
{
    return (*data_0209c788)(size, 0, 0);
}

ARM void VramTransferManager::freeTexVram(unsigned int handle)
{
    (*data_0209c78c)(handle);
}

ARM int VramTransferManager::getTexVramAddr(unsigned int handle)
{
    return (handle & 0xffff) << 3;
}

ARM int VramTransferManager::getTexVramSize(unsigned int handle)
{
    return ((handle & 0x7fff0000) >> 16) << 4;
}

ARM int VramTransferManager::allocPlttVram(int size)
{
    int handle = (*data_0209c790)(size, 0, 0);
    plttUsed_ += size;
    return handle;
}

ARM void VramTransferManager::freePlttVram(unsigned int handle)
{
    (*data_0209c794)(handle);
    plttUsed_ -= getPlttVramSize(handle);
}

ARM int VramTransferManager::getPlttVramAddr(unsigned int handle)
{
    return (handle & 0xffff) << 3;
}

ARM int VramTransferManager::getPlttVramSize(unsigned int handle)
{
    return ((handle & 0xffff0000) >> 16) << 3;
}

ARM void VramTransferManager::transferToVram(int type, void* src, int address, unsigned int size, int flag)
{
    if (vblankTransfer_ != 0) {
        func_020867d0(type, address, src, size);
        if (flag != 0) {
            doTransfers();
        }
        return;
    }
    if (flag != 0 && func_02086814() != 0) {
        OS_Wait();
        doTransfers();
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
            doTransfers();
            while ((int)*(volatile unsigned short*)0x04000006 > 1) {
            }
        }
        address += length;
        src = (unsigned char*)src + length;
        remain -= length;
    } while (remain != 0);
}

ARM void VramTransferManager::doTransfers()
{
    func_02086790();
    unk_810 = 0;
}
