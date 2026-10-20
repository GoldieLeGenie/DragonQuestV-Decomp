#pragma once
#include <globaldefs.h>
#include "main/menu/MenuDisplay.hpp"

// Window frame drawn as sprites on the sub screen, with its name tab, blinking key cursor and arrow
// (data_02114dd4.windowFrame1_, windowFrame2_)
struct MenuWindowFrame : MenuDisplay {
    int cursor_;                                // 0x30  key cursor shown
    int arrow_;                                 // 0x34  arrow shown
    int unk_38;                                 // 0x38
    int arrowX_;                                // 0x3C
    int arrowY_;                                // 0x40
    int nameWidth_;                             // 0x44  name tab width, <= 16: no tab
    int blink_;                                 // 0x48
    int frameType_;                             // 0x4C  1: translucent

    MenuWindowFrame();
    virtual void setup(int id);
    virtual void update(UnkOamBuffer* main, UnkOamBuffer* sub);
    virtual void execute(UnkOamBuffer* main, UnkOamBuffer* sub);
    virtual void draw(UnkOamBuffer* main, UnkOamBuffer* sub);
    void setNameWidth(int width);
    void setCursor(int cursor);
    void unkfunc_020652bc(int x, int y, int arrow);
    void setFrameType(int type);
    void unkfunc_020652c8(UnkOamBuffer* oam, int x, int y, int w, int h);
    void unkfunc_0206539c(UnkOamBuffer* oam, int x, int y, int w, int h, int tabW, int tabH);
    void unkfunc_020654d0(UnkOamBuffer* oam, int x, int y, int length);    // top edge
    void unkfunc_020655b0(UnkOamBuffer* oam, int x, int y, int length);    // bottom edge
    void unkfunc_020656ac(UnkOamBuffer* oam, int x, int y, int length);    // left edge
    void unkfunc_0206578c(UnkOamBuffer* oam, int x, int y, int length);    // right edge
    void unkfunc_02065888(UnkOamBuffer* oam, int x, int y, int chr, int size);
};
