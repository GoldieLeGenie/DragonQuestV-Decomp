#include "main/data/DataObject.hpp"
#include "main/data/FileLoader.hpp"

static int s_dataCount;

ARM DataObject::DataObject()
{
    m_flag = 0;
    m_addr = 0;
}

ARM DataObject::~DataObject()
{
}

ARM void DataObject::setup(const char* filename, int a, int b)
{
    m_flag |= 1;
    m_addr = dss::g_File.allocAndLoad(filename, b, (dss::File::LoadSwitch)a);
    m_size = dss::g_File.size_;
    s_dataCount++;
}

ARM void DataObject::setup(void* addr)
{
    m_addr = addr;
    s_dataCount++;
}

ARM void DataObject::cleanup()
{
    if (m_flag & 1) {
        dssFree(&data_020fd24c, m_addr);
    }
    m_flag = 0;
    m_addr = 0;
    s_dataCount--;
}

ARM void* DataObject::getAddr()
{
    return m_addr;
}

ARM long DataObject::getSize()
{
    return m_size;
}

ARM int DataObject::reload(const char* filename, int a)
{
    return dss::g_File.loadToBuffer(filename, m_addr, a);
}

ARM void UnkLZDataObject::setup(const char* filename, int a, int b)
{
    m_flag |= 1;
    m_addr = dss::g_File.allocAndLoad(filename, b, (dss::File::LoadSwitch)a);
    m_size = dss::g_File.size_;
    if (isCompressed(m_addr)) {
        m_size = getUncompressedSize(m_addr);
        void* data = uncompressAlloc(m_addr);
        dssFree(&data_020fd24c, m_addr);
        m_addr = data;
    }
    s_dataCount++;
}

ARM void UnkLZDataObject::setup(void* addr)
{
    s_dataCount++;
    m_addr = addr;
}

ARM void DataObject::loadCompressed(const char* filename, dss::File::LoadSwitch sw)
{
    m_flag |= 1;
    m_addr = dss::g_File.loadCompressed(filename, sw);
    m_size = dss::g_File.size_;
    s_dataCount++;
}
