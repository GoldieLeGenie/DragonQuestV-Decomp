#pragma once
#include <globaldefs.h>
#include "main/data/FileLoader.hpp"

// header of the binary tables exported from Excel
struct ExcelBinaryHeader {
    unsigned int id_;                           // 0x00
    unsigned int record_;                       // 0x04
    unsigned int size_;                         // 0x08
    unsigned int cash_;                         // 0x0C
    int current_;                               // 0x10
};

// binary table read record by record through a cache of cash_ records
struct ExcelBinaryData {
    unsigned int id_;                           // 0x00
    unsigned int record_;                       // 0x04 record count
    unsigned int size_;                         // 0x08 record size
    unsigned int cash_;                         // 0x0C cached records
    int current_;                               // 0x10 first cached record (-1: none)

    void setup(unsigned int allocsize);
    void* setup();
    void cleanup(void* addr);
    void* getRecord(int index, void* addr, const char* fname, dss::File::LoadSwitch loadSwitch);
    unsigned int getRecordCount();
    void setupHeader(const char* fname, dss::File::LoadSwitch loadSwitch);
    void* allocRecord(unsigned int size);
    void freeRecord(void* addr);
    void readRecord(void* addr, const char* fname, unsigned int seek, unsigned int cashsize, dss::File::LoadSwitch loadSwitch);
    void clearRecord(void* addr);
};
