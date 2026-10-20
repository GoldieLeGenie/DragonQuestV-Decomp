#pragma once
#include <globaldefs.h>
#include "main/dss/UnkMemory.hpp"
#include "main/data/FileLoader.hpp"

struct DataObject {
    // vtable                                   // 0x00
    int m_flag;                                 // 0x04
    void* m_addr;                               // 0x08
    long m_size;                                // 0x0C

    DataObject();
    ~DataObject();
    virtual void setup(const char* filename, int a, int b);
    virtual void setup(void* addr);
    void cleanup();
    void* getAddr();
    long getSize();
    int reload(const char* filename, int a);     // load the file again into the same buffer
    void loadCompressed(const char* filename, dss::File::LoadSwitch sw);  // load an LZ-compressed file
};

struct UnkLZDataObject : DataObject {
    UnkLZDataObject();
    virtual void setup(const char* filename, int a, int b);
    virtual void setup(void* addr);
};

// data object whose setup loads the file with DataObject::loadCompressed (vtable 0x0209c194)
struct UnkFileDataObject : DataObject {
    UnkFileDataObject();
    ~UnkFileDataObject();
    virtual void setup(const char* filename, int a, int b);
};
