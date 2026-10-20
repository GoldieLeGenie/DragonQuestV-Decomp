#pragma once
#include <globaldefs.h>
#include "main/menu/MenuDisplay.hpp"
#include "main/dss/UnkBgBuffer.hpp"

// One line of text drawn as sprites (data_02114dd4.texts_: message window lines and name plate)
struct UnkMenuTextDisplay : MenuDisplay {
    unsigned char charWidths_[0x100];           // 0x030
    unsigned short unk_130[0x100];              // 0x130 char codes of the text
    char unk_330[0x62];                         // 0x330 copy of the text
    int unk_394;                                // 0x394
    int unk_398;                                // 0x398
    int visibleWidth_;                          // 0x39C
    int visibleCount_;                          // 0x3A0
    int width_;                                 // 0x3A4
    int count_;                                 // 0x3A8
    int xlu_;                                   // 0x3AC
    UnkCharBuffer char_;                        // 0x3B0
    char charData_[0x800];                      // 0x3C0
    int frame_;                                 // 0xBC0  draw the frame
    int frameWidth_;                            // 0xBC4
    int unk_bc8;                                // 0xBC8
    int palette_;                               // 0xBCC
    int priority_;                              // 0xBD0
    int timer_;                                 // 0xBD4

    UnkMenuTextDisplay();
    virtual void setup(int id);
    virtual void update(UnkOamBuffer* main, UnkOamBuffer* sub);
    virtual void execute(UnkOamBuffer* main, UnkOamBuffer* sub);
    virtual void draw(UnkOamBuffer* main, UnkOamBuffer* sub);
    void unkfunc_02066ef4(UnkOamBuffer* oam, int x, int y, int width, int height);
    void unkfunc_02066fe4(int font, const char* text, int x, int y, int clear, int center);
    int unkfunc_020670f4(int font, const char* text, int priority, int flag);
    void unkfunc_02067180(int count);
    void unkfunc_020671c8(int width);
    int unkfunc_020671d0();
    int unkfunc_020671d8();
    int unkfunc_020671e0();
    void unkfunc_020671e8(int scroll);
    void unkfunc_02067268(int flag);
    void unkfunc_02067270(UnkOamBuffer* oam, int x, int y, int chr);
    void unkfunc_020672ac(UnkOamBuffer* oam, int x, int y, int chr);
    void unkfunc_020672e8(UnkOamBuffer* oam, int x, int y, int chr);    // 8x16 sprite
    void unkfunc_02067324(const char* text);    // keep a copy of the text
};

