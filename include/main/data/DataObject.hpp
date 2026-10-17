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
    int unkfunc_0206e1fc(const char* filename, int a);     // load the file again into the same buffer
    void unkfunc_0206e2c4(const char* filename, dss::File::LoadSwitch sw);  // load an LZ-compressed file
};

struct UnkLZDataObject : DataObject {
    UnkLZDataObject();
    virtual void setup(const char* filename, int a, int b);
    virtual void setup(void* addr);
};

// data object whose setup loads the file with DataObject::unkfunc_0206e2c4 (vtable 0x0209c194)
struct UnkFileDataObject : DataObject {
    UnkFileDataObject();
    ~UnkFileDataObject();
    virtual void setup(const char* filename, int a, int b);
};
