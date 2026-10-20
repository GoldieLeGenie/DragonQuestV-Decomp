#include "main/dss/UnkBgBuffer.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/dss/UnkSystemText.hpp"

THUMB void initCharBuffer(UnkCharBuffer* buffer, void* buf, int width, int height)
{
    buffer->buf_ = buf;
    buffer->width_ = width;
    buffer->height_ = height;
    buffer->pitch_ = width;
}

THUMB void* getCharBufferTile(UnkCharBuffer* buffer, int x, int y)
{
    return (unsigned char*)buffer->buf_ + (y * buffer->pitch_ + x) * 0x20;
}

THUMB void fillCharBuffer(UnkCharBuffer* buffer, unsigned int pattern)
{
    fillCharBufferRect(buffer, 0, 0, buffer->width_, buffer->height_, pattern);
}

THUMB void fillCharBufferRect(UnkCharBuffer* buffer, int x, int y, int w, int h, unsigned int pattern)
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
        MI_CpuFill(pattern, getCharBufferTile(buffer, x, y + i), size);
    }
}

THUMB void setCharBufferPixel(UnkCharBuffer* buffer, int x, int y, int color)
{
    setTilePixel(getCharBufferTile(buffer, x >> 3, y >> 3), x & 7, y & 7, color);
}

THUMB void drawCharBufferSystemTile(UnkCharBuffer* buffer, int x, int y, int flip, int bank, unsigned short chr)
{
    unsigned char* src = (unsigned char*)getSystemTextData(bank != 0) + chr * 0x20;
    void* dst = getCharBufferTile(buffer, x, y);
    if (flip) {
        drawTileTransparentVFlip(dst, src);
    } else {
        drawTileTransparent(dst, src);
    }
}
