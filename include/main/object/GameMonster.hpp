#pragma once
#include <globaldefs.h>
#include "main/dss/Position.hpp"
#include "main/dss/CharacterPalette.hpp"
#include "main/data/DataObject.hpp"
#include "main/object/DSSAObject.hpp"
#include "main/object/GameMonsterData.hpp"
#include "main/dss/TextureObject.hpp"

struct DSSACharacter : Position {
    virtual void setScale(dss::Fix32 scale);    // slot 1

    int textureLoaded_;                                // 0x034
    int currentAnimationIndex_;                 // 0x038
    int nextAnimationIndex_;                    // 0x03C
    int firstAnimationIndex_;                   // 0x040
    DSSAObjectWithCamera dssaObject_[17];       // 0x044
    void* texture_;                             // 0xAE4
    CharacterPalette palette_;               // 0xAE8
    DataObject* dataObject_;                    // 0xEFC
    dss::Flag flag_;                            // 0xF00
    long flagCount_;                            // 0xF04
    int flagIndex_;                             // 0xF08
    int specialIndex_;                          // 0xF0C

    DSSACharacter();
    ~DSSACharacter();
    void unkfunc_020524c8(TextureObject* texture, DataObject* animation);
    void cleanup();
    void draw();
    bool start(int index, int loop);
    int getCurrentFrame();
    int getMaxFrame();
    dss::Fix32Vector3 getNullPosition(int index, int no);
    void setCurrentFrame(int index, int frame);
    void setCameraType(DSSAObjectWithCamera::CameraType type);
    void setTransOfEnd();
    void setNextAnimationIndex(int index);
    int getAnimation();
};

struct GameMonster : DSSACharacter {
    int index_;                                 // 0xF10
    void* dssaCharacterData_;                   // 0xF14

    static GameMonsterData gameMonsterData_;

    GameMonster();
    ~GameMonster();
    void setup(int index);
    void cleanup();
    static void clearGameMonsterData();
    static void setupTexture(int monsterIndex);
    static void cleanupTexture(int monsterIndex);
};
