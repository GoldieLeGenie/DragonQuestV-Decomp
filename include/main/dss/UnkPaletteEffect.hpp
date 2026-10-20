#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"
#include "main/dss/TextureObject.hpp"
#include "nnsys/g3d.hpp"

// palette color effects (rgb rate, blend toward a color, sepia)
extern NNSG3dResTex* data_020f3f54;             // last loaded model textures
extern int data_020f3f58;
extern dss::Fix32Vector3 data_020f3f5c;         // rgb rate
extern unsigned short data_020f3f68[0x800];     // palette work

void unkfunc_020491f8(NNSG3dResTex* tex);
void setPaletteRgbRate(int index, dss::Fix32Vector3 rate);
void applyModelPaletteRgbRate(NNSG3dResTex* tex, dss::Fix32Vector3 rate);            // rgb rate on the palette of model textures
void applyPaletteRgbRate(unsigned short* palette, int size, dss::Fix32Vector3& rate);   // rgb rate
void unkfunc_02049564(unsigned short* palette, int size, dss::Fix32Vector3& color, dss::Fix32 rate);    // blend toward a color
void unkfunc_02049868(unsigned short* palette, unsigned int size, int mode);  // tint, mode 1: sepia
float clampFloat(float value, float min, float max);
float maxFloat(float a, float b);                                    // max
float minFloat(float a, float b);                                    // min
void unkfunc_02049ad8(TextureObject* texture, dss::Fix32Vector3& rgb);    // rgb rate on the palette of a texture
void unkfunc_02049b5c(NNSG3dResTex* tex, int r, int g, int b, dss::Fix32 rate);   // blend the palette of model textures
void unkfunc_02049c30(NNSG3dResTex* tex);                                    // sepia on the palette of model textures
void applyPaletteSepia(NNSG3dResTex* tex);                                    // sepia
