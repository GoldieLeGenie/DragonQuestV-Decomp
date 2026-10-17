#pragma ipa file
#include "main/cmn/CommonEffectResource.hpp"

THUMB cmn::CommonEffectResource::CommonEffectResource()
{
}

THUMB cmn::CommonEffectResource::~CommonEffectResource()
{
}

THUMB void cmn::CommonEffectResource::initialize()
{
    maxStorage_ = 5;
    ResourceStorage::initialize();
}

THUMB void cmn::CommonEffectResource::terminate()
{
    ResourceStorage::terminate();
}

THUMB cmn::CommonEffectData* cmn::CommonEffectResource::getResource(int id)
{
    return &storage_[ResourceStorage::getResource(id)];
}

THUMB int cmn::CommonEffectResource::loadResource(int id)
{
    int area = getEmptyArea();
    storage_[area].setup(id);
    return area;
}

THUMB void cmn::CommonEffectResource::releaseResource(int id)
{
    storage_[getResourceArea(id)].cleanup();
}

THUMB int cmn::CommonEffectResource::getResourceStock()
{
    int stock = 0;
    for (unsigned int i = 0; i < 5; i++) {
        if (!storage_[i].isEnable()) {
            stock++;
        }
    }
    return stock;
}
