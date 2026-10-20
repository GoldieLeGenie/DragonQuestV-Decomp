#pragma ipa file
#include "main/object/GameMonsterData.hpp"
#include "main/dss/DssUtils.hpp"

inline UnkLZDataObject::UnkLZDataObject()
{
}

inline DSSACharacterData::DSSACharacterData()
{
}

inline DSSACharacterData::~DSSACharacterData()
{
}

inline void DSSACharacterData::setup(void* texture, void* animation)
{
    textureData_.setup(texture);
    animationData_.setup(animation);
}

inline void DSSACharacterData::cleanup()
{
    animationData_.cleanup();
    textureData_.cleanup();
}

inline void DataCache::unkfunc_02057f24(int index)
{
}

inline void DataCache::unkfunc_02057f44(int index)
{
}

#pragma thumb on

static short (*s_linkList)[2];

DataCache::DataCache()
{
    for (int i = 0; i < 4; i++) {
        indexArray_[i] = -1;
        referenceCount_[i] = 0;
    }
}

DataCache::~DataCache()
{
}

void DataCache::clear()
{
    int i;
    for (i = 0; i < 4; i++) {
        indexArray_[i] = -1;
        referenceCount_[i] = 0;
    }
    for (i = 0; i < 4; i++) {
        cleanup(i);
    }
}

void DataCache::setup(int index)
{
    index_ = -1;
    for (int i = 0; i < 4; i++) {
        if (index == indexArray_[i]) {
            index_ = i;
            referenceCount_[i]++;
            break;
        }
    }
    if (index_ != -1) {
        return;
    }
    for (int i = 0; i < 4; i++) {
        if (indexArray_[i] == -1) {
            index_ = i;
            indexArray_[i] = index;
            referenceCount_[i]++;
            setup();
            return;
        }
    }
}

void DataCache::cleanup(int index)
{
    for (int i = 0; i < 4; i++) {
        if (index == indexArray_[i] && --referenceCount_[i] == 0) {
            index_ = i;
            indexArray_[i] = -1;
            cleanup();
        }
    }
}

void DataCache::setFilePath(const char* path)
{
    dss::strcpy_s(filePath_, 0x80, path);
}

void* DataCache::getAddr()
{
    if (index_ == -1) {
        return NULL;
    }
    return data_[index_].getAddr();
}

void DataCache::setup()
{
    char path[0x80];
    dss::sprintf(path, filePath_, indexArray_[index_]);
    data_[index_].setup(path, 1, 1);
    unkfunc_02057f24(index_);
}

void DataCache::cleanup()
{
    unkfunc_02057f44(index_);
    data_[index_].cleanup();
}

void UnkTextureDataCache::unkfunc_02057f24(int index)
{
    TextureObject* texture = (TextureObject*)data_[index].getAddr();
    texture->loadToVram(1);
    dss::memcpy(&texture_[index_], texture, sizeof(TextureObject));
    data_[index_].cleanup();
}

void UnkTextureDataCache::unkfunc_02057f44(int index)
{
    texture_[index].freeVram();
}

void* UnkTextureDataCache::getAddr()
{
    return &texture_[index_];
}

GameMonsterData::GameMonsterData()
{
    clear();
}

GameMonsterData::~GameMonsterData()
{
}

void GameMonsterData::unkfunc_02058098(short (*linkList)[2])
{
    s_linkList = linkList;
}

void GameMonsterData::clear()
{
    for (int i = 0; i < 4; i++) {
        dataIndex_[i] = -1;
        dssaIndexArray_[i] = -1;
        dssaReferenceCount_[i] = 0;
    }
    textureData_.clear();
    animationData_.clear();
}

DSSACharacterData* GameMonsterData::setup(int index)
{
    setupTexture(index);
    setupAnimation(index);
    setupDSSACharacterData(index);
    if (dssaIndex_ == -1) {
        return NULL;
    }
    return &dssaCharacterData_[dssaIndex_];
}

void GameMonsterData::cleanup(int index)
{
    cleanupDSSACharacterData(index);
    cleanupTexture(index);
    cleanupAnimation(index);
}

void GameMonsterData::setupTexture(int index)
{
    textureData_.setFilePath("data/monster/m%03d.tex.lz");
    textureData_.setup(s_linkList[index][0]);
}

void GameMonsterData::cleanupTexture(int index)
{
    textureData_.cleanup(s_linkList[index][0]);
}

void GameMonsterData::setupAnimation(int index)
{
    animationData_.setFilePath("data/monster/m%03d.anm.lz");
    animationData_.setup(s_linkList[index][1]);
}

void GameMonsterData::cleanupAnimation(int index)
{
    animationData_.cleanup(s_linkList[index][1]);
}

void GameMonsterData::setupDSSACharacterData(int index)
{
    dssaIndex_ = -1;
    for (int i = 0; i < 4; i++) {
        if (index == dssaIndexArray_[i]) {
            dssaIndex_ = i;
            dssaReferenceCount_[i]++;
            return;
        }
    }
    for (int i = 0; i < 4; i++) {
        if (dssaIndexArray_[i] == -1) {
            dssaIndexArray_[i] = index;
            dssaReferenceCount_[i]++;
            dssaCharacterData_[i].setup(textureData_.getAddr(), animationData_.getAddr());
            dssaIndex_ = i;
            return;
        }
    }
}

void GameMonsterData::cleanupDSSACharacterData(int index)
{
    for (int i = 0; i < 4; i++) {
        if (index == dssaIndexArray_[i]) {
            dssaReferenceCount_[i]--;
            if (dssaReferenceCount_[i] == 0) {
                dssaIndexArray_[i] = -1;
                dssaCharacterData_[i].cleanup();
            }
            return;
        }
    }
}
