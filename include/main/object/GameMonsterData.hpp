#pragma once
#include <globaldefs.h>
#include "main/data/DataObject.hpp"
#include "main/dss/TextureObject.hpp"

struct DSSACharacterData {
    UnkLZDataObject textureData_;               // 0x00
    UnkLZDataObject animationData_;             // 0x10

    DSSACharacterData();
    ~DSSACharacterData();
    void setup(void* texture, void* animation);
    void cleanup();
};

/* vtable 0x0209a718 */
struct DataCache {
    // vtable                                   // 0x00
    int index_;                                 // 0x04
    int indexArray_[4];                         // 0x08
    int referenceCount_[4];                     // 0x18
    UnkLZDataObject data_[4];                   // 0x28
    char filePath_[0x80];                       // 0x68

    DataCache();
    ~DataCache();
    virtual void* getAddr();
    virtual void unkfunc_02057f24(int index);   // called after a file is loaded
    virtual void unkfunc_02057f44(int index);   // called before a file is released
    void clear();
    void setup(int index);
    void cleanup(int index);
    void setFilePath(const char* path);
    void setup();
    void cleanup();
};

/* vtable 0x0209a704 */
struct UnkTextureDataCache : DataCache {
    TextureObject texture_[4];               // 0xE8

    virtual void* getAddr();
    virtual void unkfunc_02057f24(int index);   // copies the texture and loads it in VRAM
    virtual void unkfunc_02057f44(int index);   // frees the VRAM of the texture
};

struct GameMonsterData {
    int unk_00;                                 // 0x000
    int animationIndex_;                        // 0x004
    int dssaIndex_;                             // 0x008
    int dataIndex_[4];                          // 0x00C
    DSSACharacterData dssaCharacterData_[4];    // 0x01C
    int dssaIndexArray_[4];                     // 0x09C
    int dssaReferenceCount_[4];                 // 0x0AC
    UnkTextureDataCache textureData_;           // 0x0BC
    DataCache animationData_;                   // 0x364

    GameMonsterData();
    ~GameMonsterData();
    static void unkfunc_02058098(short (*linkList)[2]);    // sets the monster texture/animation file table
    void clear();
    DSSACharacterData* setup(int index);
    void cleanup(int index);
    void setupTexture(int index);
    void cleanupTexture(int index);
    void setupAnimation(int index);
    void cleanupAnimation(int index);
    void setupDSSACharacterData(int index);
    void cleanupDSSACharacterData(int index);
};
