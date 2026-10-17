#include "main/data/ExcelBinaryData.hpp"
#include "main/dss/UnkMemory.hpp"
#include <mem.h>

ARM void ExcelBinaryData::setup(unsigned int allocsize)
{
    current_ = -1;
    if (allocsize < cash_ * size_) {
        cash_ = allocsize / size_;
    }
}

ARM void* ExcelBinaryData::setup()
{
    void* addr = allocRecord(cash_);
    current_ = -1;
    return addr;
}

ARM void ExcelBinaryData::cleanup(void* addr)
{
    freeRecord(addr);
}

ARM void* ExcelBinaryData::getRecord(int index, void* addr, const char* fname, dss::File::LoadSwitch loadSwitch)
{
    if (current_ >= 0 && index >= current_ && index < current_ + cash_) {
        char* pAddr = (char*)addr + size_ * (index - current_);
        return pAddr;
    }
    clearRecord(addr);
    readRecord(addr, fname, index, cash_, loadSwitch);
    char* pAddr = (char*)addr + size_ * (index - current_);
    return pAddr;
}

ARM void ExcelBinaryData::setupHeader(const char* fname, dss::File::LoadSwitch loadSwitch)
{
    ExcelBinaryHeader header;
    dss::g_File.unkfunc_0204b250(fname, &header, 0, sizeof(header), loadSwitch);
    id_ = header.id_;
    record_ = header.record_;
    size_ = header.size_;
    cash_ = header.cash_;
    current_ = header.current_;
}

ARM void* ExcelBinaryData::allocRecord(unsigned int size)
{
    return unkfunc_0204c5bc(&data_020fd24c, size * size_, 0x20);
}

ARM void ExcelBinaryData::freeRecord(void* addr)
{
    unkfunc_0204c5c8(&data_020fd24c, addr);
}

ARM void ExcelBinaryData::readRecord(void* addr, const char* fname, unsigned int seek, unsigned int cashsize, dss::File::LoadSwitch loadSwitch)
{
    if (seek + cashsize >= record_) {
        seek = record_ - cashsize;
    }
    current_ = seek;
    dss::g_File.unkfunc_0204b250(fname, addr, seek * size_ + sizeof(ExcelBinaryHeader), cashsize * size_, loadSwitch);
}

ARM void ExcelBinaryData::clearRecord(void* addr)
{
    memset(addr, 0, size_ * cash_);
}
