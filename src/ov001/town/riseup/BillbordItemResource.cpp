#pragma ipa file
#include "ov001/town/riseup/BillbordItemResource.hpp"

THUMB twn::BillbordItemResource::BillbordItemResource()
{
}

THUMB twn::BillbordItemResource::~BillbordItemResource()
{
}

THUMB void twn::BillbordItemResource::initialize()
{
    maxStorage_ = RESOURCE_ITEM_MAX;
    ResourceStorage::initialize();
}

THUMB void twn::BillbordItemResource::terminate()
{
    ResourceStorage::terminate();
}

THUMB BillboardItem* twn::BillbordItemResource::getResource(int id)
{
    return &m_item[ResourceStorage::getResource(id)];
}

THUMB int twn::BillbordItemResource::loadResource(int id)
{
    int area = getEmptyArea();
    if (id < 1000) {
        m_item[area].unkfunc_0214e8b0("data/RISE/item.tex", id);
    } else {
        switch (id) {
        case 1000:
            m_item[area].unkfunc_0214e840("data/rise/gold.tex");
            break;
        case 1001:
            m_item[area].unkfunc_0214e840("data/rise/exclamation.tex");
            break;
        case 1002:
            m_item[area].unkfunc_0214e840("data/rise/question.tex");
            break;
        case 9999:
            m_item[area].unkfunc_0214e840("data/rise/number.tex");
            break;
        case 2000:
            m_item[area].unkfunc_0214e840("data/rise/exhibit.tex");
            break;
        }
    }
    return area;
}

THUMB void twn::BillbordItemResource::releaseResource(int id)
{
    m_item[getResourceArea(id)].cleanup();
}
