#pragma once
#include <globaldefs.h>
#include "main/dss/UnkRenderObject.hpp"

/* vtable 0x020c4404 */
struct UnkBillboard : UnkRenderObject3D {
    virtual void draw();                        // 0x020842c0

    UnkBillboardVertex vertex_;                    // 0x48
    UnkBillboardTexCoord texCoord_;                // 0x58
    UnkBillboardVertex drawVertex_;                // 0x78
    UnkBillboardTexCoord drawTexCoord_;            // 0x88
    dss::Vector2<dss::Fix32> unk_a8;            // 0xA8 texture coordinate offset
    unsigned short color_;                      // 0xB0

    UnkBillboard();                                // C2 0x02083da8
    void unkfunc_02047a20(const UnkBillboardVertex* vertex);       // setVertex
    UnkBillboardVertex* unkfunc_02047a8c();                        // getVertex
    void unkfunc_02047a94(const UnkBillboardTexCoord* texCoord);   // setTexCoord
    UnkBillboardTexCoord* unkfunc_02047b00();                      // getTexCoord
    void unkfunc_02047b08(const dss::Vector2<dss::Fix32>* offset);  // setTexCoordOffset
    void unkfunc_02047b2c();                                    // calc the draw vertex/texcoord
    void unkfunc_02047c10(int color);                           // setColor
};


#ifndef BILLBOARD_CHARACTER_TU
#include "main/dss/UnkTextureBillboard.hpp"
#endif
