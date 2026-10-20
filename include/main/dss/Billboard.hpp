#pragma once
#include <globaldefs.h>
#include "main/dss/RenderObject.hpp"

/* vtable 0x020c4404 */
struct Billboard : UnkRenderObject3D {
    virtual void draw();                        // 0x020842c0

    UnkBillboardVertex vertex_;                    // 0x48
    UnkBillboardTexCoord texCoord_;                // 0x58
    UnkBillboardVertex drawVertex_;                // 0x78
    UnkBillboardTexCoord drawTexCoord_;            // 0x88
    dss::Vector2<dss::Fix32> texCoordOffset_;            // 0xA8 texture coordinate offset
    unsigned short color_;                      // 0xB0

    Billboard();                                // C2 0x02083da8
    void unkfunc_02047a20(const UnkBillboardVertex* vertex);       // setVertex
    UnkBillboardVertex* getVertex();                        // getVertex
    void unkfunc_02047a94(const UnkBillboardTexCoord* texCoord);   // setTexCoord
    UnkBillboardTexCoord* getTexCoord();                      // getTexCoord
    void setTexCoordOffset(const dss::Vector2<dss::Fix32>* offset);  // setTexCoordOffset
    void calcDrawVertex();                                    // calc the draw vertex/texcoord
    void unkfunc_02047c10(int color);                           // setColor
};


#ifndef BILLBOARD_CHARACTER_TU
#include "main/dss/TextureBillboard.hpp"
#endif
