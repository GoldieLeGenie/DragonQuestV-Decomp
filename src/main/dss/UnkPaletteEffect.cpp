#pragma ipa file
#include "main/dss/UnkPaletteEffect.hpp"
#include "main/dss/VramTransferManager.hpp"
#include "nitro/os.hpp"

namespace dss {
    template <typename T> T max(T a, T b)
    {
        return (a > b) ? a : b;
    }

    template <typename T> T min(T a, T b)
    {
        return (a < b) ? a : b;
    }

    template <typename T> T clamp(T a, T b, T c)
    {
        return min(max(a, b), c);
    }
}

NNSG3dResTex* data_020f3f54;
int data_020f3f58;
dss::Fix32Vector3 data_020f3f5c(1, 1, 1);
unsigned short data_020f3f68[0x800];

ARM void unkfunc_020491f8(NNSG3dResTex* tex)
{
    data_020f3f54 = tex;
}

ARM void setPaletteRgbRate(int index, dss::Fix32Vector3 rate)
{
    data_020f3f58 = index;
    data_020f3f5c = rate;
}

ARM void applyModelPaletteRgbRate(NNSG3dResTex* tex, dss::Fix32Vector3 rate)
{
    unsigned int size = tex->plttInfo.sizePltt << 3;
    unsigned int address = (tex->plttInfo.vramKey & 0xffff) << 3;
    MI_CpuCopyU8((unsigned char*)tex + tex->plttInfo.ofsPlttData, data_020f3f68, size);
    applyPaletteRgbRate(data_020f3f68, size, rate);
    DC_CleanAll();
    data_020f4f74.transferToVram(1, data_020f3f68, address, size, 0);
}

ARM void applyPaletteRgbRate(unsigned short* palette, int size, dss::Fix32Vector3& rate)
{
    for (int i = 0; i < size / 2; i++) {
        dss::Fix32 r;
        dss::Fix32 g;
        dss::Fix32 b;
        r = (long)(palette[i] & 0x1f);
        g = (long)((palette[i] & 0x3e0) >> 5);
        b = (long)((palette[i] & 0x7c00) >> 10);
        r = rate.vx * r;
        g = rate.vy * g;
        b = rate.vz * b;
        r = dss::clamp<dss::Fix32>(r, 0L, 31L);
        g = dss::clamp<dss::Fix32>(g, 0L, 31L);
        b = dss::clamp<dss::Fix32>(b, 0L, 31L);
        palette[i] = (unsigned char)(r.value >> 12) | ((unsigned char)(g.value >> 12) << 5) | ((unsigned char)(b.value >> 12) << 10);
    }
}

ARM void unkfunc_02049564(unsigned short* palette, int size, dss::Fix32Vector3& color, dss::Fix32 rate)
{
    for (int i = 0; i < size / 2; i++) {
        dss::Fix32 r;
        dss::Fix32 g;
        dss::Fix32 b;
        r = (long)(palette[i] & 0x1f);
        g = (long)((palette[i] & 0x3e0) >> 5);
        b = (long)((palette[i] & 0x7c00) >> 10);
        r = (r * (dss::Fix32(1L) - rate) + color.vx * rate) / dss::Fix32(1L);
        g = (g * (dss::Fix32(1L) - rate) + color.vy * rate) / dss::Fix32(1L);
        b = (b * (dss::Fix32(1L) - rate) + color.vz * rate) / dss::Fix32(1L);
        r = dss::clamp<dss::Fix32>(r, 0L, 31L);
        g = dss::clamp<dss::Fix32>(g, 0L, 31L);
        b = dss::clamp<dss::Fix32>(b, 0L, 31L);
        palette[i] = (unsigned char)(r.value >> 12) | ((unsigned char)(g.value >> 12) << 5) | ((unsigned char)(b.value >> 12) << 10);
    }
}

ARM void unkfunc_02049868(unsigned short* palette, unsigned int size, int mode)
{
    float cb;
    float cr;
    if (mode == 1) {
        cb = -0.091f;
        cr = 20.0f;
    } else {
        cb = -0.2f;
        cr = 0.1f;
    }
    for (unsigned int i = 0; i < size / 2; i++) {
        unsigned short color = palette[i];
        float r = color & 0x1f;
        float g = (color & 0x3e0) >> 5;
        float b = (color & 0x7c00) >> 10;
        r *= 8.0f;
        g *= 8.0f;
        b *= 8.0f;
        float y = 0.114f * b + (0.299f * r + 0.587f * g);
        float r2 = y + 1.402f * cr;
        float g2 = y - 0.34414f * cb - 0.71414f * cr;
        float b2 = y + 1.772f * cb;
        r2 = clampFloat(r2, 0.0f, 255.0f);
        g2 = clampFloat(g2, 0.0f, 255.0f);
        b2 = clampFloat(b2, 0.0f, 255.0f);
        r2 /= 8.0f;
        g2 /= 8.0f;
        b2 /= 8.0f;
        palette[i] = (unsigned int)r2 | ((unsigned int)g2 << 5) | ((unsigned int)b2 << 10);
    }
}

ARM float clampFloat(float value, float min, float max)
{
    return minFloat(maxFloat(value, min), max);
}

ARM float maxFloat(float a, float b)
{
    return (a > b) ? a : b;
}

ARM float minFloat(float a, float b)
{
    return (a < b) ? a : b;
}

ARM void unkfunc_02049ad8(TextureObject* texture, dss::Fix32Vector3& rgb)
{
    int data = texture->unkfunc_0204a1d4();
    int address = texture->unkfunc_0204a1cc();
    int size = texture->unkfunc_0204a1dc();
    MI_CpuCopyU8((void*)data, data_020f3f68, size);
    applyPaletteRgbRate(data_020f3f68, size, rgb);
    DC_CleanAll();
    data_020f4f74.transferToVram(1, data_020f3f68, address, size, 0);
}

ARM void unkfunc_02049b5c(NNSG3dResTex* tex, int r, int g, int b, dss::Fix32 rate)
{
    unsigned int size = tex->plttInfo.sizePltt << 3;
    unsigned int address = (tex->plttInfo.vramKey & 0xffff) << 3;
    MI_CpuCopyU8((unsigned char*)tex + tex->plttInfo.ofsPlttData, data_020f3f68, size);
    dss::Fix32Vector3 color;
    color.vx = (long)r;
    color.vy = dss::Fix32((long)g);
    color.vz = dss::Fix32((long)b);
    unkfunc_02049564(data_020f3f68, size, color, rate);
    DC_CleanAll();
    data_020f4f74.transferToVram(1, data_020f3f68, address, size, 0);
}

ARM void unkfunc_02049c30(NNSG3dResTex* tex)
{
    unsigned int offset = tex->plttInfo.ofsPlttData;
    unsigned int size = tex->plttInfo.sizePltt << 3;
    unsigned int address = (tex->plttInfo.vramKey & 0xffff) << 3;
    applyPaletteSepia(tex);
    DC_CleanAll();
    data_020f4f74.transferToVram(1, (unsigned char*)tex + offset, address, size, 0);
    data_020f4f74.doTransfers();
}

ARM void applyPaletteSepia(NNSG3dResTex* tex)
{
    unsigned int size = tex->plttInfo.sizePltt << 3;
    unsigned short* palette = (unsigned short*)((unsigned char*)tex + tex->plttInfo.ofsPlttData);
    for (unsigned int i = 0; i < size / 2; i++) {
        unsigned short color = *palette;
        float r = color & 0x1f;
        float g = (color & 0x3e0) >> 5;
        float b = (color & 0x7c00) >> 10;
        r *= 8.0f;
        g *= 8.0f;
        b *= 8.0f;
        float cb = -0.091f;
        float cr = 20.0f;
        float y = 0.114f * b + (0.299f * r + 0.587f * g);
        float r2 = y + 1.402f * cr;
        float g2 = y - 0.34414f * cb - 0.71414f * cr;
        float b2 = y + 1.772f * cb;
        r2 = clampFloat(r2, 0.0f, 255.0f);
        g2 = clampFloat(g2, 0.0f, 255.0f);
        b2 = clampFloat(b2, 0.0f, 255.0f);
        r2 /= 8.0f;
        g2 /= 8.0f;
        b2 /= 8.0f;
        *palette = (unsigned int)r2 | ((unsigned int)g2 << 5) | ((unsigned int)b2 << 10);
        palette++;
    }
}
