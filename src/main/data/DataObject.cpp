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
    m_addr = dss::g_File.unkfunc_0204b29c(filename, b, (dss::File::LoadSwitch)a);
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
        unkfunc_0204c5c8(&data_020fd24c, m_addr);
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

ARM int DataObject::unkfunc_0206e1fc(const char* filename, int a)
{
    return dss::g_File.unkfunc_0204b21c(filename, m_addr, a);
}

ARM void UnkLZDataObject::setup(const char* filename, int a, int b)
{
    m_flag |= 1;
    m_addr = dss::g_File.unkfunc_0204b29c(filename, b, (dss::File::LoadSwitch)a);
    m_size = dss::g_File.size_;
    if (unkfunc_0204c230(m_addr)) {
        m_size = unkfunc_0204c214(m_addr);
        void* data = unkfunc_0204c278(m_addr);
        unkfunc_0204c5c8(&data_020fd24c, m_addr);
        m_addr = data;
    }
    s_dataCount++;
}

ARM void UnkLZDataObject::setup(void* addr)
{
    s_dataCount++;
    m_addr = addr;
}

ARM void DataObject::unkfunc_0206e2c4(const char* filename, dss::File::LoadSwitch sw)
{
    m_flag |= 1;
    m_addr = dss::g_File.unkfunc_0204b310(filename, sw);
    m_size = dss::g_File.size_;
    s_dataCount++;
}
