#pragma once
#include <globaldefs.h>
#include "main/menu/MenuDisplay.hpp"
#include "main/dss/UnkBgBuffer.hpp"

// One line of text drawn as sprites (data_02114dd4.texts_: message window lines and name plate)
struct UnkMenuTextDisplay : MenuDisplay {
    unsigned char charWidths_[0x100];           // 0x030
    unsigned short charCodes_[0x100];              // 0x130 char codes of the text
    char text_[0x62];                         // 0x330 copy of the text
    int unk_394;                                // 0x394
    int centerOffset_;                                // 0x398
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
    void drawHiddenMask(UnkOamBuffer* oam, int x, int y, int width, int height);
    void unkfunc_02066fe4(int font, const char* text, int x, int y, int clear, int center);
    int setFramedText(int font, const char* text, int priority, int flag);
    void setVisibleCount(int count);
    void setVisibleWidth(int width);
    int getVisibleCount();
    int getCharCount();
    int getTextWidth();
    void clearScrolledLines(int scroll);
    void setTranslucent(int flag);
    void drawFrameSprite32(UnkOamBuffer* oam, int x, int y, int chr);
    void drawFrameSprite16(UnkOamBuffer* oam, int x, int y, int chr);
    void drawFrameSprite8(UnkOamBuffer* oam, int x, int y, int chr);    // 8x16 sprite
    void storeText(const char* text);    // keep a copy of the text
};

