#pragma once
#include <globaldefs.h>
#include "main/object/DSSAObject.hpp"
#include "main/dss/UnkTextureObject.hpp"

// DS palette animation data (header + per-frame 16/256-color palettes)
struct UnkPaletteAnimationHeader {
    unsigned short unk_00;              /* 0x00 */
    unsigned short mode_;               /* 0x02, 0: 16 colors, else 256 colors */
    unsigned short frameCount_;         /* 0x04 */
};

struct UnkPaletteFrame16 {
    unsigned short wait_;               /* 0x00 */
    unsigned short color_[16];          /* 0x02 */
};

struct UnkPaletteFrame256 {
    unsigned short wait_;               /* 0x00 */
    unsigned short color_[256];         /* 0x02 */
};

struct UnkPaletteAnimation {
    UnkPaletteAnimationHeader header_;     /* 0x00 */
    UnkPaletteFrame16* frame16_;           /* 0x08 */
    UnkPaletteFrame256* frame256_;         /* 0x0C */

    UnkPaletteAnimation();
    ~UnkPaletteAnimation();
    void setup(void* data);
    int getWait(int frame);
    unsigned short* getColor(int frame);
    int getColorCount();
    int getFrameCount();
};

struct UnkPaletteAnimationObject {
    UnkPaletteAnimation anim_;             /* 0x00 */
    UnkTextureObject* texture_;            /* 0x10 */
    int colorCount_;                    /* 0x14 */
    int frame_;                         /* 0x18 */
    int wait_;                          /* 0x1C */

    UnkPaletteAnimationObject();
    void unkfunc_020513c0();                            // start
    void unkfunc_02051440();                            // execute
    void unkfunc_0205150c(int address, int size);       // start
    void unkfunc_02051580(int address, int size);       // execute
    int unkfunc_02051628();                             // isEnd
    void unkfunc_02051648();                            // cleanup
};

extern unsigned short data_02101a68[256];               // palette work
