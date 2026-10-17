#include "main/dss/UnkBgBuffer.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/dss/UnkSystemText.hpp"

THUMB void unkfunc_0204e558(UnkCharBuffer* buffer, void* buf, int width, int height)
{
    buffer->buf_ = buf;
    buffer->width_ = width;
    buffer->height_ = height;
    buffer->pitch_ = width;
}

THUMB void* unkfunc_0204e564(UnkCharBuffer* buffer, int x, int y)
{
    return (unsigned char*)buffer->buf_ + (y * buffer->pitch_ + x) * 0x20;
}

THUMB void unkfunc_0204e574(UnkCharBuffer* buffer, unsigned int pattern)
{
    unkfunc_0204e58c(buffer, 0, 0, buffer->width_, buffer->height_, pattern);
}

THUMB void unkfunc_0204e58c(UnkCharBuffer* buffer, int x, int y, int w, int h, unsigned int pattern)
{
    if (x > buffer->width_ || y > buffer->height_) {
        return;
    }
    if (x + w > buffer->width_) {
        w = buffer->width_ - x;
    }
    if (y + h > buffer->height_) {
        h = buffer->height_ - y;
    }
    if (w == 0 || h == 0) {
        return;
    }
    unsigned int size = w * 0x20;
    for (int i = 0; i < h; i++) {
        MI_CpuFill(pattern, unkfunc_0204e564(buffer, x, y + i), size);
    }
}

THUMB void unkfunc_0204e5ec(UnkCharBuffer* buffer, int x, int y, int color)
{
    unkfunc_0204ee0c(unkfunc_0204e564(buffer, x >> 3, y >> 3), x & 7, y & 7, color);
}

THUMB void unkfunc_0204e60c(UnkCharBuffer* buffer, int x, int y, int flip, int bank, unsigned short chr)
{
    unsigned char* src = (unsigned char*)unkfunc_0204e698(bank != 0) + chr * 0x20;
    void* dst = unkfunc_0204e564(buffer, x, y);
    if (flip) {
        unkfunc_0204eed8(dst, src);
    } else {
        unkfunc_0204ee90(dst, src);
    }
}
