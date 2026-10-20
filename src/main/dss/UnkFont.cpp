#include "main/dss/UnkFont.hpp"

THUMB UnkFont::UnkFont()
{
    unk_08 = 0;
    height_ = 0;
}

THUMB void UnkFont::load(void* data, int height)
{
    func_0207ed5c(&font_, data);
    unsigned short index = func_0207ed7c(&font_, '%');
    if (index != 0xffff) {
        font_.info_->alterCharIndex_ = index;
    }
    height_ = height;
}

THUMB int UnkFont::drawChar(UnkG2dCanvas* canvas, int x, int y, int color, unsigned short c)
{
    if (canvas == NULL) {
        unsigned short index = func_0207ed7c(&font_, c);
        if (index == 0xffff) {
            index = font_.info_->alterCharIndex_;
        }
        return func_0207eda8(&font_, index)->charWidth_;
    }
    if (c == 0x246a) {
        color = 7;
    }
    if (c == 0x2474) {
        color = 7;
    }
    if (c == 0x247e) {
        color = 7;
    }
    if (c == 0x2488) {
        color = 7;
    }
    if (c == 0x2492) {
        color = 7;
    }
    return func_0207f6c8(canvas, &font_, x, y, color, c);
}
