#include "main/dss/UnkBgText.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/dss/UnkUtf8Iterator.hpp"

UnkBgText data_021011f0;

THUMB void unkfunc_0204df4c()
{
    data_021011f0.count_ = 0;
    data_021011f0.font_ = NULL;
    data_021011f0.subFont_ = NULL;
    data_021011f0.mode_ = 1;
}

THUMB void unkfunc_0204df60(void* data, void* subData)
{
    data_021011f0.font12_.load(data, 12);
    data_021011f0.subFont12_.load(subData, 12);
}

THUMB void unkfunc_0204df84(void* data, void* subData)
{
    data_021011f0.font10_.load(data, 10);
    data_021011f0.subFont10_.load(subData, 10);
}

THUMB int unkfunc_0204dfa8(UnkCharBuffer* buffer, int x, int y, int color, const char* text)
{
    return unkfunc_0204dfbc(buffer, x, y, color, text, 0);
}

THUMB int unkfunc_0204dfbc(UnkCharBuffer* buffer, int x, int y, int color, const char* text, int wrap)
{
    UnkBgText* work = &data_021011f0;
    UnkG2dCanvas canvas;
    UnkG2dCanvas* pCanvas = NULL;
    work->count_ = 0;
    if (buffer != NULL) {
        void* chr = unkfunc_0204e564(buffer, x / 8, y / 8);
        x %= 8;
        y %= 8;
        pCanvas = &canvas;
        int areaWidth = buffer->pitch_;
        int areaHeight = buffer->height_;
        if (areaHeight > 24) {
            areaHeight = 24;
        }
        func_0207f780(&canvas, chr, areaWidth, areaHeight, 4);
    }
    int lineWidth = 0;
    int left = x;
    int maxWidth = 0;
    int height = 0;
    int i = 0;
    int lineHeight = work->lineHeight_ + 2;
    UnkUtf8Iterator it;
    it.setText(text);
    while (i < 0x100) {
        unsigned short c = it.getChar();
        it.nextChar();
        if (c == 0xffff || c == 0) {
            break;
        }
        int w;
        switch (c) {
        case 0xfeff:
        case 0xfffe:
            w = 0;
            break;
        case '\t':
            w = 13;
            break;
        case '\n':
            if (maxWidth < lineWidth) {
                maxWidth = lineWidth;
            }
            w = 0;
            lineWidth = 0;
            height += lineHeight;
            x = left;
            y += lineHeight;
            break;
        case ';':
            if (wrap) {
                if (maxWidth < lineWidth) {
                    maxWidth = lineWidth;
                }
                w = 0;
                lineWidth = 0;
                height += lineHeight;
                x = left;
                y += lineHeight;
            } else {
                w = 0;
            }
            break;
        case '$':
            if (wrap) {
                lineWidth += unkfunc_0204e1a0(pCanvas, x, y, color, '-');
                if (maxWidth < lineWidth) {
                    maxWidth = lineWidth;
                }
                w = 0;
                lineWidth = 0;
                height += lineHeight;
                x = left;
                y += lineHeight;
            } else {
                w = 0;
            }
            break;
        case '\r':
            w = 0;
            break;
        default:
            w = unkfunc_0204e1a0(NULL, x, y, color, c);
            if (w != 0) {
                if (x + w < 0x100) {
                    w = unkfunc_0204e1a0(pCanvas, x, y, color, c);
                }
            }
            break;
        }
        x += w;
        lineWidth += w;
        work->charWidths_[i] = w;
        work->charCodes_[i] = c;
        i++;
    }
    if (maxWidth < lineWidth) {
        maxWidth = lineWidth;
    }
    work->width_ = maxWidth;
    work->height_ = height;
    work->count_ = i;
    return 0;
}

THUMB int unkfunc_0204e1a0(UnkG2dCanvas* canvas, int x, int y, int color, unsigned short c)
{
    UnkBgText* work = &data_021011f0;
    UnkFont* font = work->font_;
    if (work->mode_ == 1) {
        switch (c) {
        case 0xff10:
            c = 0x249c;
            break;
        case 0xff11:
            c = 0x249d;
            break;
        case 0xff12:
            c = 0x249e;
            break;
        case 0xff13:
            c = 0x249f;
            break;
        case 0xff14:
            c = 0x24a0;
            break;
        case 0xff15:
            c = 0x24a1;
            break;
        case 0xff16:
            c = 0x24a2;
            break;
        case 0xff17:
            c = 0x24a3;
            break;
        case 0xff18:
            c = 0x24a4;
            break;
        case 0xff19:
            c = 0x24a5;
            break;
        case 0x3000:
            c = 0x24a6;
            break;
        case 0xff0f:
            c = 0x24a7;
            break;
        case 0xff1a:
            c = 0x24a8;
            break;
        case 0xff01:
            c = 0x24b0;
            break;
        }
    }
    if (work->mode_ == 2) {
        switch (c) {
        case 0xff10:
            c = 0x322a;
            break;
        case 0xff11:
            c = 0x322b;
            break;
        case 0xff12:
            c = 0x322c;
            break;
        case 0xff13:
            c = 0x322d;
            break;
        case 0xff14:
            c = 0x322e;
            break;
        case 0xff15:
            c = 0x322f;
            break;
        case 0xff16:
            c = 0x3230;
            break;
        case 0xff17:
            c = 0x3231;
            break;
        case 0xff18:
            c = 0x3232;
            break;
        case 0xff19:
            c = 0x3233;
            break;
        case 0x3000:
            c = 0x3234;
            break;
        case 0xff0f:
            c = 0x3235;
            break;
        case 0xff1a:
            c = 0x3236;
            break;
        case 0xff01:
            c = 0x323e;
            break;
        }
    }
    switch (c) {
    case 0x80:
        c = 0x24d5;
        break;
    case 0x81:
        c = 0x24d6;
        break;
    case 0x82:
        c = 0x24d7;
        break;
    case 0x83:
        c = 0x24d8;
        break;
    case 0x84:
        c = 0x24d9;
        break;
    case 0x85:
        c = 0x24c6;
        break;
    }
    if (c == 0x3000) {
        if (work->size_ == 12) {
            return 10;
        }
        if (work->size_ == 10) {
            return 8;
        }
    }
    if (c == ' ') {
        if (work->size_ == 12) {
            return 4;
        }
        if (work->size_ == 10) {
            return 3;
        }
    }
    switch (c) {
    case 0x3220:
    case 0x3221:
    case 0x3222:
    case 0x3223:
    case 0x3224:
    case 0x3225:
    case 0x3226:
    case 0x3227:
    case 0x3228:
    case 0x3229:
        return 0;
    }
    if ((c & 0xff00) == 0) {
        font = work->subFont_;
    }
    if (c == 0xd7) {
        font = work->font_;
    }
    if (c == 0xf7) {
        font = work->font_;
    }
    if ((c & 0xff00) == 0x100) {
        font = work->subFont_;
    }
    if ((c & 0xff00) == 0x400) {
        font = work->subFont_;
    }
    if ((c & 0xff00) == 0x2400) {
        font = work->subFont_;
    }
    if ((c & 0xff00) == 0x3200) {
        font = work->subFont_;
    }
    return font->drawChar(canvas, x, y, color, c);
}

THUMB void unkfunc_0204e478(int size)
{
    UnkBgText* work = &data_021011f0;
    if (size == 12) {
        work->font_ = &work->font12_;
        work->subFont_ = &work->subFont12_;
        work->lineHeight_ = unkfunc_0204e4c8(12);
    }
    if (size == 10) {
        work->font_ = &work->font10_;
        work->subFont_ = &work->subFont10_;
        work->lineHeight_ = unkfunc_0204e4c8(10);
    }
    work->size_ = size;
}

THUMB int unkfunc_0204e4c8(int size)
{
    switch (size) {
    case 12:
        return 12;
    case 10:
        return 10;
    }
    return 0;
}

THUMB int unkfunc_0204e4dc(unsigned char* widths, int max)
{
    if (max < data_021011f0.count_) {
        return -1;
    }
    if (max > data_021011f0.count_) {
        max = data_021011f0.count_;
    }
    MI_CpuCopyU8(data_021011f0.charWidths_, widths, max);
    return max;
}

THUMB int unkfunc_0204e50c(unsigned short* codes, int size)
{
    if (size < data_021011f0.count_) {
        return -1;
    }
    if (size > data_021011f0.count_ * 2) {
        size = data_021011f0.count_ * 2;
    }
    MI_CpuCopyU8(data_021011f0.charCodes_, codes, size);
    return size;
}

THUMB int unkfunc_0204e540()
{
    return data_021011f0.width_;
}

extern "C" THUMB void func_0204e54c(int mode)
{
    data_021011f0.mode_ = mode;
}
