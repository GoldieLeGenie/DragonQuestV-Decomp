#pragma once
#include <globaldefs.h>
#include "main/object/DSSAObject.hpp"
#include "main/dss/TextureObject.hpp"

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

struct PaletteAnimation {
    UnkPaletteAnimationHeader header_;     /* 0x00 */
    UnkPaletteFrame16* frame16_;           /* 0x08 */
    UnkPaletteFrame256* frame256_;         /* 0x0C */

    PaletteAnimation();
    ~PaletteAnimation();
    void setup(void* data);
    int getWait(int frame);
    unsigned short* getColor(int frame);
    int getColorCount();
    int getFrameCount();
};

struct PaletteAnimationObject {
    PaletteAnimation anim_;             /* 0x00 */
    TextureObject* texture_;            /* 0x10 */
    int colorCount_;                    /* 0x14 */
    int frame_;                         /* 0x18 */
    int wait_;                          /* 0x1C */

    PaletteAnimationObject();
    void start();                            // start
    void execute();                            // execute
    void startAt(int address, int size);       // start
    void executeOnceAt(int address, int size);       // execute
    int isEnd();                             // isEnd
    void cleanup();                            // cleanup
};

extern unsigned short data_02101a68[256];               // palette work
