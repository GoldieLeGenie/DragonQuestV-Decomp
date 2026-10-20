#pragma once
#include <globaldefs.h>
#include "main/data/DataObject.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/dss/Sprite2D.hpp"

/* vtable 0x0209a760 */
struct SpriteShadow : Sprite2D {
    virtual void draw();

    SpriteShadow();
    ~SpriteShadow();
    void setPosition(int x, int y);
    void unkfunc_0205876c();                    // setup with the shadow texture
    void unkfunc_020587b4();
};

/* vtable 0x0209a780 */
struct SpriteCharacter : Sprite2D {
    enum {
        FLAG_ENABLE = 1,
        FLAG_DISPLAY = 2,
        FLAG_ANIM = 4,
        FLAG_STAY = 8,
        FLAG_SHADOW = 16,
        FLAG_RELOAD = 32,
        FLAG_ANIM_NEUTRAL = 256,
        FLAG_DEFAULT = 283
    };

    int anmIndex_;                              // 0x38
    dss::Flag flag_;                            // 0x3C
    int unk_40;                                 // 0x40
    DataObject data_;                           // 0x44
    int textureNum_;                            // 0x54
    TextureObject* unk_58;                   // 0x58 texture shown
    int unk_5c[7];                              // 0x5C
    TextureObject* unk_78[8];                // 0x78 textures of the file, one per direction
    short direction_;                           // 0x98
    short dispDirection_;                       // 0x9A
    int unk_9c;                                 // 0x9C width
    int unk_a0;                                 // 0xA0 height
    SpriteShadow shadow_;                       // 0xA4

    static dss::BitFlag<unsigned char> allFlag_;

    SpriteCharacter();
    ~SpriteCharacter();
    virtual void draw();
    virtual void setAlpha(int alpha);
    virtual void execute();
    void setup(const char* name, int width, int height, int flag);
    void cleanup();
    void unkfunc_020583ec();
    void unkfunc_0205833c(int width, int height);
    void unkfunc_0205853c(int dir);             // shows the texture of a direction
    void setPosition(int x, int y);
    void setPosition(dss::Vector2<int> pos);
    void reload();
    void setDirection(unsigned short dir);
    void setDisplayEnable(int flag);
    int isDisplayEnable();
    void setShadowStay(int flag);
    void setAnimFlag(int flag);
    void setShadowFlag(int flag);
    static void setAllCharaAnim(int flag);
    static int getAllCharaAnim();
    static int unkfunc_020586dc();
    static void unkfunc_0205870c();             // loads data/common.tex
    static void unkfunc_02058738();             // releases data/common.tex
    static void unkfunc_02058754();             // reloads data/common.tex
};
