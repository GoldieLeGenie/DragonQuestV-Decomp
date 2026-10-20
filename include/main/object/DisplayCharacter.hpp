#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"
#include "main/data/FileLoader.hpp"
#include "main/object/BillboardCharacter.hpp"
#include "nitro/g3.hpp"

/* vtable 0x0209a6a0 */
struct DisplayCharacter : BillboardCharacter {
    virtual void draw();
    virtual void setAlpha(int alpha);
    virtual void setRender(Render* render);
    virtual void removeRender();

    Billboard head_;                         // 0x1B0
    unsigned short unk_264;                     // 0x264 hue change frame count
    unsigned short unk_266;                     // 0x266 hue change frame
    unsigned short unk_268[16];                 // 0x268 hue changed palette
    unsigned short unk_288[16];                 // 0x288 original palette
    int unk_2a8;                                // 0x2A8 texture index of the hue change

    static const int FLAG_BOX_TEST_OFF;
    static const int SLEEP_DIRECTION;

    static int shadowType_;
    static int headEnable_;
    static dss::Fix32 workScale_;
    static dss::Fix32Vector3 boxTestRotate_;
    static dss::Fix32Vector3 boxTestScale_;
    static GXBoxTestParam boxTestParam_;
    static dss::Fix32 boxTestRate_;
    static dss::Fix32 nearBodyOffset_;
    static dss::Fix32 nearHeadOffset_;
    static dss::Fix32 sleepHeight_;
    static dss::Fix32 sleepBodyOffset_;
    static dss::Fix32 sleepHeadOffset_;
    static dss::Fix32Vector3 sleepOffset_[8];

    int box_testx1();
    bool unkfunc_02057098();                    // camera far from the character
    void drawSleepCharacter();
    void drawSleep(dss::Fix32Vector3& position, UnkBillboardVertex& vertex, UnkBillboardTexCoord& texCoord);
    void execHueChange();

    DisplayCharacter();
    ~DisplayCharacter();
    void setShadowType(int type);
    void exec();
    void setBoxTestOff(bool flag);
    void setSleep(int flag);
    void setCharacterSize(int width, int height);
    void setup(const char* name, dss::File::LoadSwitch loadSwitch);
    void cleanup();
    void unkfunc_02055a60();                    // releases the texture VRAM
    void unkfunc_02056b80(void* data);          // sets the texture from a loaded pack
    void unkfunc_02056b98();                    // restores the default texture
    void unkfunc_020562e0(int flag);            // palette rgb rate on/off
    void unkfunc_020562d0(const dss::Fix32Vector3* rate);   // palette rgb rate
    void setShadowPos(dss::Fix32Vector3& pos);
    void setShadowAlpha(int alpha);
    void setShadowStay(int flag);
    void setShadowFlag(int flag);
    void setSleepFlag(int flag);
    void setShadowOnlyFlag(int flag);
    void setHueChange(int type, int frame);
    bool isHueChange();
    void requestReload();
    void setColor(int color);
    unsigned char getAlpha();
};
