#include "main/dss/DssCore.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/dss/UnkBgBuffer.hpp"
#include "main/dss/UnkMemory.hpp"
#include "main/data/FileLoader.hpp"
#include "nitro/os.hpp"
#include "nitro/gx.h"
#include <stdio.h>

inline UnkDebugConsole::UnkDebugConsole()
{
    init();
}

THUMB void unkfunc_0204afd8()
{
}

THUMB void unkfunc_0204afdc()
{
}

THUMB int getTick()
{
    return func_020885e0();
}

THUMB void debugPrintfStub(const char* format, ...)
{
}

THUMB void UnkDebugConsole::init()
{
}

THUMB void UnkDebugConsole::reset()
{
    clear();
}

THUMB void UnkDebugConsole::clear()
{
    clearScreenBuffer(getDebugScreenBuffer(), -1);
}

THUMB void UnkDebugConsole::clearRect(int x, int y, int w, int h)
{
    clearScreenBufferRect(getDebugScreenBuffer(), x, y, w, h, -1);
}

THUMB void UnkDebugConsole::print(int x, int y, const char* str)
{
    drawScreenBufferText(getDebugScreenBuffer(), x, y, str);
}

THUMB void UnkDebugConsole::printf(int x, int y, const char* format, ...)
{
    char buf[0x41];
    va_list args;
    va_start(args, format);
    vsnprintf(buf, sizeof(buf), format, args);
    drawScreenBufferText(getDebugScreenBuffer(), x, y, buf);
}

ARM void dssVBlankIntr()
{
    *(volatile unsigned int*)((unsigned int)data_027e0000 + 0x3ff8) |= 1;
}

ARM void initSystem(int exArena)
{
    if (exArena != 0) {
        OS_EnableMainExArena();
        data_020f6fa0 = 1;
    }
    OS_InitAllSystems();
    func_020786d4();
    func_0208a8b0();
    GX_SetPower(GX_POWER_ALL);
    GX_Init();
    func_020743b4(2);
    func_02088548();
    OS_InitThread();
    GX_DispOff();
    GXS_DispOff();
    func_02086f88(1, dssVBlankIntr);
    func_020870c4(1);
    OS_EnableIrq();
    func_02073850(3);
    GX_VBlankIntr(TRUE);
    func_0207b328();
}

ARM void clearVram()
{
    GX_SetBankForLcdc(GX_VRAM_ALL);
    MI_CpuFill(0, (void*)0x06800000, 0xa4000);
    func_02075550();
    MI_CpuFill(0xc0, (void*)0x07000000, 0x400);
    MI_CpuFill(0xc0, (void*)0x07000400, 0x400);
    MI_CpuFill(0, (void*)0x05000000, 0x400);
    MI_CpuFill(0, (void*)0x05000400, 0x400);
}

ARM void dss::File::init(int)
{
    loadFsTable();
    readOffset_ = 0;
    readSize_ = 0;
}

ARM void dss::File::loadFsTable()
{
    unsigned int size = FS_TryLoadTable(NULL, 0);
    FS_TryLoadTable(allocAppHeap(&data_020fd24c, size, 0x20), size);
}

ARM int dss::File::loadToBuffer(const char* fname, void* dst, int a)
{
    int size;
    if (a == 0) {
        size = unkfunc_0204b26c(fname, dst);
        readOffset_ = 0;
    } else {
        size = unkfunc_0204b284(fname, dst);
        readOffset_ = 0;
    }
    DC_CleanAll();
    return size;
}

ARM int dss::File::loadPartToBuffer(const char* fname, void* dst, int offset, int size, int a)
{
    readOffset_ = offset;
    readSize_ = size;
    return loadToBuffer(fname, dst, a);
}

ARM int dss::File::unkfunc_0204b26c(const char* fname, void* dst)
{
    int size = readRomFile(fname, dst);
    DC_CleanAll();
    return size;
}

ARM int dss::File::unkfunc_0204b284(const char* fname, void* dst)
{
    int size = readRomFile(fname, dst);
    DC_CleanAll();
    return size;
}

ARM void* dss::File::allocAndLoad(const char* fname, int a, LoadSwitch sw)
{
    int size = 0;
    void* archive = 0;
    if (archive == 0) {
        size = getRomFileSize(fname);
    }
    size_ = size;
    void* p;
    if (a != 0) {
        p = dssAlloc(&data_020fd24c, size, -0x20);
    } else {
        p = dssAlloc(&data_020fd24c, size, 0x20);
    }
    loadToBuffer(fname, p, 0);
    return p;
}

ARM void* dss::File::loadCompressed(const char* fname, LoadSwitch sw)
{
    void* p = 0;
    if (p == 0) {
        p = readCompressedFile(fname);
    }
    return p;
}

ARM int dss::File::getFileSize(const char* fname, LoadSwitch sw)
{
    int size = 0;
    void* archive = 0;
    if (archive == 0) {
        size = getRomFileSize(fname);
    }
    return size;
}

ARM bool dss::File::isExist(const char* fname, LoadSwitch sw)
{
    return getFileSize(fname, sw) != 0;
}

ARM unsigned int roundDown(unsigned int value, unsigned int align)
{
    return value & ~(align - 1);
}

ARM int dss::File::readRomFile(const char* fname, void* dst)
{
    func_02073868(&file_);
    int ok = func_02073a3c(&file_, fname);
    if (readOffset_ != 0) {
        func_02073b64(&file_, readOffset_, 0);
    }
    if (ok) {
        size_ = file_.endRomOffset - file_.startRomOffset;
        if (readSize_ != 0) {
            size_ = readSize_;
            readSize_ = 0;
        }
        size_ = func_02073b58(&file_, dst, size_);
        if (size_ == -1) {
            return 0;
        }
        func_02073a68(&file_);
    } else {
        size_ = 0;
    }
    return size_;
}

ARM void* dss::File::readCompressedFile(const char* fname)
{
    unsigned char* buf = data_020f6fe0;
    MIUncompContextLZ context;
    func_02073868(&file_);
    func_02073a3c(&file_, fname);
    func_02073b58(&file_, buf, 4);
    size_ = *(unsigned int*)buf >> 8;
    void* dst = dssAlloc(&data_020fd24c, size_, 0x20);
    func_020708d4(&context, dst, buf);
    while (func_020708fc(&context, buf, func_02073b58(&file_, buf, 0x1400)) != 0) {
    }
    DC_CleanAll();
    func_02073a68(&file_);
    return dst;
}

ARM int dss::File::getRomFileSize(const char* fname)
{
    FSFile file;
    func_02073868(&file);
    if (!func_02073a3c(&file, fname)) {
        return 0;
    }
    return file.endRomOffset - file.startRomOffset;
}

ARM void resetBgObjVram()
{
    func_02075b38();
    func_02075cd8();
    func_020827ac();
    *(volatile unsigned int*)0x04000000 &= ~0x07000000;
    *(volatile unsigned int*)0x04000000 &= ~0x38000000;
}

ARM void setMainBrightness(int brightness)
{
    func_0207438c((void*)0x0400006c, brightness);
}

ARM void setSubBrightness(int brightness)
{
    func_0207438c((void*)0x0400106c, brightness);
}

THUMB UnkDebugConsole data_020f6f9c;
