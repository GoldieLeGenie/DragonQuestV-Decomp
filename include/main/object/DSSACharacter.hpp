#pragma once
#include <globaldefs.h>
#include "main/dss/Position.hpp"
#include "main/dss/UnkTextureObject.hpp"
#include "main/data/DataObject.hpp"
#include "main/object/DSSAObject.hpp"
#include "main/dss/UnkCharacterPalette.hpp"

// streaming of a DSSA animation split in numbered files, double buffered in the animations 0 and 1
struct UnkDSSAStream {
    int unk_00;                                 // 0x00 next file number
    int unk_04;                                 // 0x04 file count
    int unk_08;                                 // 0x08 buffer index
};

// character drawn with DSSA animations (main 0x020523b0)
struct DSSACharacter : Position {
    virtual void setScale(dss::Fix32 scale);    // slot 1

    int unk_034;                                // 0x034
    int currentAnimationIndex_;                 // 0x038
    int nextAnimationIndex_;                    // 0x03C
    int firstAnimationIndex_;                   // 0x040
    DSSAObjectWithCamera dssaObject_[17];       // 0x044
    UnkTextureObject* unk_ae4;                  // 0xAE4 texture
    UnkCharacterPalette palette_;               // 0xAE8
    DataObject* dataObject_;                    // 0xEFC
    dss::Flag flag_;                            // 0xF00
    long flagCount_;                            // 0xF04
    int flagIndex_;                             // 0xF08
    int specialIndex_;                          // 0xF0C

    DSSACharacter();
    ~DSSACharacter();
    void unkfunc_0205248c(DataObject* texture, DataObject* animation);
    void unkfunc_020524c8(UnkTextureObject* texture, DataObject* animation);
    void unkfunc_02052594(UnkTextureObject* texture, const char* format, int count);
    void cleanup();
    void unkfunc_02052754();
    void draw();
    bool start(int index, int flag);
    void setAlpha(int alpha);
    bool isEnable(int index);
    int getCurrentFrame();
    int getMaxFrame();
    dss::Fix32Vector3 getNullPosition(int index, int no);
    void setCurrentFrame(int index, int frame);
    void setCameraType(DSSAObjectWithCamera::CameraType type);
    void pause(int flag);
    int getAnimation();
    static void setCamera(dss::Camera* camera);
};
