#pragma once
#include "main/dss/UnkBillboard.hpp"
/* vtable 0x020c1c44 */
struct UnkTextureBillboard : UnkBillboard {
#ifndef BILLBOARD_CHARACTER_TU
    virtual void draw();                        // never defined: key function so the vtable is only emitted by BillboardCharacter.cpp
#endif

    void* texture_;                             // 0xB4

    void unkfunc_0205071c(const UnkBillboardVertex* vertex, const UnkBillboardTexCoord* texCoord, void* texture);
    void unkfunc_02050760();
    void unkfunc_02050770(int a);
};
