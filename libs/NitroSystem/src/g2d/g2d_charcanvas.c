#include "g2d_charcanvas.h"

#pragma thumb on

/* Character canvas: renders font glyphs into 4/8 bpp character (tile) memory. */

/* OBJ area of 1/2/4/8 x 1/2/4/8 characters [h][w] -> (width shift, height shift) */
static const u8 data_0208eb98[4][4][2] = {
    {{0, 0}, {1, 0}, {2, 0}, {2, 0}},
    {{0, 1}, {1, 1}, {2, 1}, {2, 1}},
    {{0, 2}, {1, 2}, {2, 2}, {3, 2}},
    {{0, 2}, {1, 2}, {2, 3}, {3, 3}},
};

/* object (height shift, width shift) [h][w] -> OAM shape / size bits */
static const u16 data_0208ebb8[4][4][2] = {
    {{0x0000, 0x0000}, {0x4000, 0x0000}, {0x4000, 0x4000}, {0x0000, 0x0000}},
    {{0x8000, 0x0000}, {0x0000, 0x4000}, {0x4000, 0x8000}, {0x0000, 0x0000}},
    {{0x8000, 0x4000}, {0x8000, 0x8000}, {0x0000, 0x8000}, {0x4000, 0xc000}},
    {{0x0000, 0x0000}, {0x0000, 0x0000}, {0x8000, 0xc000}, {0x0000, 0xc000}},
};

static inline void MI_CpuFill32(void* dest, u32 data, u32 size) {
    MI_CpuFill(data, dest, size);
}

#define CHR_SIZE(bpp) (8 * 8 * (bpp) / 8)

u32 func_0208a8d4(u32 x);

/* Returns the OBJ size table entry (width shift, height shift) for an area of w*h characters. */
static inline const u8* GetObjShiftWH(int w, int h) {
    int sw = (w >= 8) ? 3 : 31 - func_0208a8d4(w);
    int sh = (h >= 8) ? 3 : 31 - func_0208a8d4(h);

    return data_0208eb98[sh][sw];
}

static inline int UnkCanvasMin(int a, int b) { return (a <= b) ? a : b; }
static inline int UnkCanvasMax(int a, int b) { return (a >= b) ? a : b; }
static inline void UnkCanvasReaderInit(UnkBitReader* reader, const void* src) {
    reader->unk_04 = 0;
    reader->unk_00 = (u8*)src;
    reader->unk_05 = 0;
}
static inline u8 UnkCanvasFontHeight(const UnkFont* font) { return font->unk_00->unk_08->unk_01; }
static inline u8 UnkCanvasFontWidth(const UnkFont* font) { return font->unk_00->unk_08->unk_00; }
static inline u8 UnkCanvasFontBpp(const UnkFont* font) { return font->unk_00->unk_08->unk_06; }
static inline int UnkCanvasCharSize(const UnkCharCanvas* cc) { return CHR_SIZE(cc->unk_0c); }

static inline void FillRect4(void* chr, int x, int y, int w, int h, u32 pattern) {
    int rsft;
    u32 mask;
    u32* p;
    u32* end;

    x *= 4;
    rsft = 32 - (x + w * 4);
    mask = ((0xffffffff >> x) << (x + rsft)) >> rsft;
    pattern &= mask;
    mask = ~mask;
    p = (u32*)chr + y;
    end = p + h;
    for (; p < end; p++) {
        *p = pattern | (*p & mask);
    }
}

static inline void FillRect8(void* chr, int x, int y, int w, int h, u32 pattern) {
    u32 maskLo;
    UnkChar8bppRow* end;
    UnkChar8bppRow* p;
    u32 valHi;
    u32 valLo;
    u32 t;
    u32 maskHi;

    x *= 8;
    w = 64 - (x + w * 8);
    maskLo = 0xffffffff >> x;
    if ((u32)w >= 32) {
        u32 s = w - 32;
        maskLo = (maskLo << (x + s)) >> s;
    } else {
        maskLo <<= x;
    }
    t = 0xffffffff << w;
    if ((u32)x >= 32) {
        u32 s = x - 32;
        maskHi = (t >> (s + w)) << s;
    } else {
        maskHi = t >> w;
    }

    valLo = pattern & maskLo;
    valHi = pattern & maskHi;
    maskLo = ~maskLo;
    maskHi = ~maskHi;
    p = (UnkChar8bppRow*)chr + y;
    end = p + h;
    for (; p < end; p++) {
        p->unk_00 = valLo | (p->unk_00 & maskLo);
        p->unk_04 = valHi | (p->unk_04 & maskHi);
    }
}

/* Returns the character number of character (x, y) in an OBJ area made of 2D-mapped objects. */
u32 func_0207edd8(u32 x, u32 y, int areaW, int areaH, int wShift, int hShift) {
    u32 charNo = 0;

    for (;;) {
        u32 maskW = 0xffffffff << wShift;
        u32 maskH = 0xffffffff << hShift;
        u32 fullW = areaW & maskW;
        u32 fullH = areaH & maskH;

        if (fullH <= y) {
            charNo += areaW * fullH;
            if (fullW <= x) {
                areaH -= fullH;
                charNo += fullW * areaH;
                x -= fullW;
                y -= fullH;
                areaW -= fullW;
            } else {
                areaW = fullW;
                y -= fullH;
                areaH -= fullH;
            }
        } else {
            u32 lowH = ~maskH;

            if (fullW <= x) {
                charNo += fullW * fullH;
                x -= fullW;
                areaW -= fullW;
                areaH = fullH;
            } else {
                charNo += fullW * (y & maskH);
                charNo += (x & maskW) << hShift;
                charNo += (y & lowH) << wShift;
                return charNo + (x & ~maskW);
            }
        }
        {
            const u8* shift = GetObjShiftWH(areaW, areaH);

            wShift = shift[0];
            hShift = shift[1];
        }
    }
}

/* Fills a w*h pixel rectangle at (x, y) of one character with a color pattern. */
void func_0207eec0(void* chr, int x, int y, int w, int h, u32 pattern, u32 bpp) {
    if (w == 8 && h == 8) {
        MI_CpuFill(pattern, chr, bpp * 8);
        return;
    }

    if (bpp == 4) {
        FillRect4(chr, x, y, w, h, pattern);
    } else {
        FillRect8(chr, x, y, w, h, pattern);
    }
}

/* Draws the part of a glyph that falls into one character. */
void func_0207ef8c(UnkGlyphCharParam* param) {
    u32 xs = UnkCanvasMax(param->unk_08, 0);
    int y0 = UnkCanvasMax(param->unk_0c, 0);
    u32 xe = (param->unk_08 + param->unk_10 < 8) ? param->unk_08 + param->unk_10 : 8;
    int y1 = (param->unk_0c + param->unk_14 < 8) ? param->unk_0c + param->unk_14 : 8;
    int srcY = -UnkCanvasMin(param->unk_0c, 0);
    int minX = UnkCanvasMin(param->unk_08, 0);
    u8* src;
    int bitPos;
    int srcBpp;
    int rowBits;
    int dstBpp;

    rowBits = param->unk_18;
    srcBpp = param->unk_1c;
    bitPos = srcY * rowBits + srcBpp * -minX;
    src = param->unk_04;
    dstBpp = param->unk_20;
    xs *= dstBpp;
    xe *= dstBpp;

    if (dstBpp == 4) {
        u32* row = (u32*)param->unk_00 + y0;
        u32* end = (u32*)param->unk_00 + y1;
        u32 col = param->unk_24;

        for (; row < end; row++) {
            UnkBitReader reader;
            u32 val = *row;
            u32 i;

            UnkCanvasReaderInit(&reader, src + (u32)bitPos / 8);
            func_0207f904(&reader, bitPos % 8);
            for (i = xs; i < xe; i += 4) {
                u32 c = func_0207f904(&reader, srcBpp);

                if (c != 0) {
                    val = (val & ~(0xf << i)) | ((col + c) << i);
                }
            }
            *row = val;
            bitPos += rowBits;
        }
    } else {
        UnkChar8bppRow* row = (UnkChar8bppRow*)param->unk_00 + y0;
        UnkChar8bppRow* end = (UnkChar8bppRow*)param->unk_00 + y1;
        u32 col = param->unk_24;

        for (; row < end; row++) {
            UnkBitReader reader;
            u32 lo = row->unk_00;
            u32 hi = row->unk_04;
            u32 i;

            UnkCanvasReaderInit(&reader, src + (u32)bitPos / 8);
            func_0207f904(&reader, bitPos % 8);
            for (i = xs; i < xe; i += 8) {
                u32 c = func_0207f904(&reader, srcBpp);

                if (c != 0) {
                    if (i < 32) {
                        lo = (lo & ~(0xff << i)) | ((col + c) << i);
                    } else {
                        u32 s = i - 32;

                        hi = (hi & ~(0xff << s)) | ((col + c) << s);
                    }
                }
            }
            row->unk_00 = lo;
            row->unk_04 = hi;
            bitPos += rowBits;
        }
    }
}

/* Draws a glyph into a BG-style canvas (characters laid out in rows of unk_10). */
void func_0207f13c(UnkCharCanvas* cc, UnkFont* font, int x, int y, int cl, UnkGlyph* glyph) {
    int charSize = CHR_SIZE(cc->unk_0c);
    int px;
    int areaW = cc->unk_04;
    int areaH = cc->unk_08;
    int xEnd;
    int cx0;
    u8* dst;
    u8* charBase = cc->unk_00;
    UnkGlyphCharParam param;
    u32 cx1;
    u8 glyphW = glyph->unk_00->unk_01;
    int cw;
    int yEnd;
    int ch;
    int cy0;
    u32 cy1;
    int rowSkip;
    u8 glyphH = font->unk_00->unk_08->unk_01;

    if (glyphW == 0) {
        return;
    }
    if (x + glyphW < 0) {
        return;
    }
    if (y + glyphH < 0) {
        return;
    }
    cx0 = (x <= 0) ? 0 : (u32)x / 8;
    cy0 = (y <= 0) ? 0 : (u32)y / 8;
    cx1 = (u32)(x + glyphW + 7) / 8;
    if (cx1 >= areaW) {
        cx1 = areaW;
    }
    cy1 = (u32)(y + glyphH + 7) / 8;
    if (cy1 >= areaH) {
        cy1 = areaH;
    }
    cw = cx1 - cx0;
    ch = cy1 - cy0;
    if (cw < 0 || ch < 0) {
        return;
    }

    dst = charBase + charSize * (cc->unk_10.unk_00 * cy0 + cx0);
    rowSkip = charSize * (cc->unk_10.unk_00 - cw);
    if (x >= 0) {
        x &= 7;
    }
    if (y >= 0) {
        y &= 7;
    }
    xEnd = x - cw * 8;
    yEnd = y - ch * 8;
    param.unk_04 = glyph->unk_04;
    param.unk_10 = glyphW;
    param.unk_14 = glyphH;
    param.unk_24 = cl - 1;
    param.unk_1c = font->unk_00->unk_08->unk_06;
    param.unk_20 = cc->unk_0c;
    param.unk_18 = param.unk_1c * font->unk_00->unk_08->unk_00;
    for (; y > yEnd; y -= 8) {
        param.unk_0c = y;
        for (px = x; px > xEnd; px -= 8) {
            param.unk_00 = dst;
            param.unk_08 = px;
            func_0207ef8c(&param);
            dst += charSize;
        }
        dst += rowSkip;
    }
}


/* Draws a glyph into an OBJ-style canvas (characters laid out as objects). */
void func_0207f26c(UnkCharCanvas* cc, UnkFont* font, int x, int y, int cl, UnkGlyph* glyph) {
    int px;
    int maxW;
    int maxH;
    int xEnd;
    int cx0;
    int yEnd;
    u8* charBase;
    UnkGlyphCharParam param;
    u32 cx1;
    u8 glyphW;
    int cw;
    int ch;
    int cy0;
    u32 cy1;
    UnkCharCanvasLayout layout;
    int hShift;
    int wShift;
    int areaH;
    int areaW;
    int charSize;
    int ccx;
    int ccy;
    u8 glyphH;

    charSize = CHR_SIZE(cc->unk_0c);
    maxW = cc->unk_04;
    maxH = cc->unk_08;
    glyphW = glyph->unk_00->unk_01;
    glyphH = font->unk_00->unk_08->unk_01;

    if (glyphW == 0) {
        return;
    }
    if (x + glyphW < 0) {
        return;
    }
    if (y + glyphH < 0) {
        return;
    }
    cx0 = (x <= 0) ? 0 : (u32)x / 8;
    cy0 = (y <= 0) ? 0 : (u32)y / 8;
    cx1 = (u32)(x + glyphW + 7) / 8;
    if (cx1 >= maxW) {
        cx1 = maxW;
    }
    cy1 = (u32)(y + glyphH + 7) / 8;
    if (cy1 >= maxH) {
        cy1 = maxH;
    }
    cw = cx1 - cx0;
    ch = cy1 - cy0;
    if (cw < 0 || ch < 0) {
        return;
    }

    if (x >= 0) {
        x &= 7;
    }
    if (y >= 0) {
        y &= 7;
    }
    xEnd = x - cw * 8;
    yEnd = y - ch * 8;
    charBase = cc->unk_00;
    param.unk_04 = glyph->unk_04;
    param.unk_14 = glyphH;
    param.unk_10 = glyphW;
    param.unk_24 = cl - 1;
    param.unk_1c = font->unk_00->unk_08->unk_06;
    param.unk_20 = cc->unk_0c;
    param.unk_18 = param.unk_1c * font->unk_00->unk_08->unk_00;
    layout = cc->unk_10;
    areaW = cc->unk_04;
    areaH = cc->unk_08;
    wShift = layout.unk_obj.unk_00;
    hShift = layout.unk_obj.unk_08;
    for (ccy = cy0; y > yEnd; ccy++, y -= 8) {
        param.unk_0c = y;
        ccx = cx0;
        for (px = x; px > xEnd; ccx++, px -= 8) {
            int charNo = func_0207edd8(ccx, ccy, areaW, areaH, wShift, hShift);

            param.unk_08 = px;
            param.unk_00 = charBase + charNo * charSize;
            func_0207ef8c(&param);
        }
    }
}

/* Clears a canvas whose characters are contiguous. */
void func_0207f3b4(UnkCharCanvas* cc, int cl) {
    u32 pat;
    int nChars;

    if (cc->unk_0c == 4) {
        pat = cl | (cl << 4);
        pat |= pat << 8;
        cl = pat | (pat << 16);
    } else {
        pat = cl | (cl << 8);
        cl = pat | (pat << 16);
    }
    nChars = cc->unk_04 * cc->unk_08;
    MI_CpuFill32(cc->unk_00, cl, nChars * CHR_SIZE(cc->unk_0c));
}

/* Clears a BG-style canvas row by row. */
void func_0207f3e8(UnkCharCanvas* cc, int cl) {
    int i;
    u8* p;
    int charSize;
    int stride;
    int rowSize;
    u32 pat;

    if (cc->unk_0c == 4) {
        pat = cl | (cl << 4);
        pat |= pat << 8;
        cl = pat | (pat << 16);
    } else {
        pat = cl | (cl << 8);
        cl = pat | (pat << 16);
    }
    charSize = CHR_SIZE(cc->unk_0c);
    stride = charSize * cc->unk_10.unk_00;
    rowSize = charSize * cc->unk_04;
    p = cc->unk_00;

    for (i = 0; i < cc->unk_08; i++) {
        MI_CpuFill(cl, p, rowSize);
        p += stride;
    }
}

/* Clears a pixel rectangle of a BG-style canvas. */
void func_0207f448(UnkCharCanvas* cc, int cl, int x, int y, int w, int h) {
    int cy;
    int cx;
    int dh;
    int xEnd;
    int yEnd;
    u32 chr;
    int cxEnd;
    int cyEnd;
    u32 row;
    int bpp;
    int cxStart;
    int charSize;
    int stride;

    xEnd = x + w;
    yEnd = y + h;
    bpp = cc->unk_0c;
    {
        u32 pat;

        if (bpp == 4) {
            pat = cl | (cl << 4);
            pat |= pat << 8;
            cl = pat | (pat << 16);
        } else {
            pat = cl | (cl << 8);
            cl = pat | (pat << 16);
        }
    }
    cxStart = x & ~7;
    cy = y & ~7;
    cxEnd = (xEnd + 7) & ~7;
    cyEnd = (yEnd + 7) & ~7;
    charSize = CHR_SIZE(bpp);
    stride = cc->unk_10.unk_00 * charSize;
    row = (u32)cc->unk_00 + charSize * (cy / 8 * cc->unk_10.unk_00 + cxStart / 8);

    for (; cy < cyEnd; cy += 8) {
        int dy = (cy < y) ? y - cy : 0;

        dh = ((yEnd - cy > 8) ? 8 : yEnd - cy) - dy;
        chr = row;
        for (cx = cxStart; cx < cxEnd; cx += 8) {
            int dx = (cx < x) ? x - cx : 0;
            int dw = ((xEnd - cx > 8) ? 8 : xEnd - cx) - dx;

            func_0207eec0((void*)chr, dx, dy, dw, dh, cl, bpp);
            chr += charSize;
        }
        row += stride;
    }
}

#pragma opt_loop_invariants off

/* Clears a pixel rectangle of an OBJ-style canvas. */
void func_0207f56c(UnkCharCanvas* cc, int cl, int x, int y, int w, int h) {
    int cy;
    int dh;
    int xEnd;
    int yEnd;
    int cxEnd;
    int cyEnd;
    int cx;
    UnkCharCanvasLayout layout;
    u8* charBase;
    int ccxStart;
    int cxStart;
    int hShift;
    int wShift;
    int areaH;
    int areaW;
    int charSize;
    int ccy;
    int ccx;
    u8 bpp;

    xEnd = x + w;
    yEnd = y + h;
    bpp = cc->unk_0c;
    {
        u32 pat;

        if (bpp == 4) {
            pat = cl | (cl << 4);
            pat |= pat << 8;
            cl = pat | (pat << 16);
        } else {
            pat = cl | (cl << 8);
            cl = pat | (pat << 16);
        }
    }

    layout = cc->unk_10;
    cxStart = x & ~7;
    cy = y & ~7;
    cxEnd = (xEnd + 7) & ~7;
    cyEnd = (yEnd + 7) & ~7;
    areaW = cc->unk_04;
    areaH = cc->unk_08;
    wShift = layout.unk_obj.unk_00;
    hShift = layout.unk_obj.unk_08;
    charSize = CHR_SIZE(bpp);
    ccxStart = cxStart / 8;
    charBase = cc->unk_00;
    ccy = cy / 8;

    for (; cy < cyEnd; ccy++, cy += 8) {
        int dy = (cy < y) ? y - cy : 0;

        dh = ((yEnd - cy > 8) ? 8 : yEnd - cy) - dy;
        ccx = ccxStart;
        for (cx = cxStart; cx < cxEnd; ccx++, cx += 8) {
            int charNo = func_0207edd8(ccx, ccy, areaW, areaH, wShift, hShift);
            int dx = (cx < x) ? x - cx : 0;
            int dw = ((xEnd - cx > 8) ? 8 : xEnd - cx) - dx;

            func_0207eec0(charBase + charNo * charSize, dx, dy, dw, dh, cl, bpp);
        }
    }
}

#pragma opt_loop_invariants reset

/* canvas functions: BG, OBJ with 1D character mapping, OBJ with 2D character mapping */
static const UnkCharCanvasVTable data_0208eb80 = {func_0207f13c, func_0207f3b4, func_0207f448};
static const UnkCharCanvasVTable data_0208eb74 = {func_0207f13c, func_0207f3e8, func_0207f448};
static const UnkCharCanvasVTable data_0208eb8c = {func_0207f26c, func_0207f3b4, func_0207f56c};

void func_0207f6b4(UnkCharCanvas* cc, void* charBase, int areaW, int areaH, int bpp, const UnkCharCanvasVTable* vtable,
                   u32 param) {
    cc->unk_04 = areaW;
    cc->unk_08 = areaH;
    cc->unk_0c = bpp;
    cc->unk_00 = charBase;
    cc->unk_14 = vtable;
    cc->unk_10.unk_00 = param;
}

/* Draws character c at (x, y) with color cl, returns its advance width. */
int func_0207f6c8(UnkCharCanvas* cc, UnkFont* font, int x, int y, int cl, u16 c) {
    UnkGlyph glyph;
    u16 index = func_0207ed7c(font, c);
    UnkFontGlyph* cglp;

    if (index == 0xffff) {
        index = font->unk_00->unk_02;
    }
    glyph.unk_00 = func_0207eda8(font, index);
    glyph.unk_04 = font->unk_00->unk_08->unk_08 + index * font->unk_00->unk_08->unk_02;

    cglp = font->unk_00->unk_08;
    switch (cglp->unk_07) {
    case 0:
    case 7:
        x += glyph.unk_00->unk_00;
        break;
    case 1:
    case 2:
        x -= cglp->unk_00;
        y += glyph.unk_00->unk_00;
        break;
    case 3:
    case 4:
        x -= glyph.unk_00->unk_00 + glyph.unk_00->unk_01;
        y -= cglp->unk_01;
        break;
    case 5:
    case 6:
        y -= glyph.unk_00->unk_00 + cglp->unk_01;
        break;
    }

    cc->unk_14->unk_00(cc, font, x, y, cl, &glyph);
    return glyph.unk_00->unk_02;
}

void func_0207f780(UnkCharCanvas* cc, void* charBase, int areaW, int areaH, int bpp) {
    func_0207f6b4(cc, charBase, areaW, areaH, bpp, &data_0208eb80, areaW);
}

/* The OBJ canvas initializers and the OBJ arrange function are not linked in the ROM (no caller);
   the tables they use stay in this unit's .rodata. The 12-byte {-1, -1, -1} initializer at 0x0208eb68
   belongs to one of these functions; its real use is unknown (`none` below only reproduces it). */
void unkfunc_unused_20(UnkCharCanvas* cc, void* charBase, int areaW, int areaH, int bpp) {
    func_0207f6b4(cc, charBase, areaW, areaH, bpp, &data_0208eb74, 0);
}

void unkfunc_unused_21(UnkCharCanvas* cc, void* charBase, int areaW, int areaH, int bpp) {
    func_0207f6b4(cc, charBase, areaW, areaH, bpp, &data_0208eb8c, 0);
}

void unkfunc_unused_22(u16* attr, int w, int h) {
    const u8* shift = GetObjShiftWH(w, h);
    const int none[3] = {-1, -1, -1};

    attr[0] = data_0208ebb8[shift[1]][shift[0]][0];
    attr[1] = data_0208ebb8[shift[1]][shift[0]][1];
    attr[2] = (u16)none[w & 1];
}
