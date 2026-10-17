#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"
#include "main/dss/Position.hpp"
#include "main/dss/Render.hpp"
#include "main/dss/UnkTextureObject.hpp"

/* vtable 0x020c43c4 */
struct UnkRenderObject {
    virtual void draw();                        // slot 0
    virtual void setPolygonID(int id);          // slot 1
    virtual void setAlpha(int alpha);           // slot 2
    virtual void setRender(Render* render);     // slot 3
    virtual void removeRender();                // slot 4
    virtual Render* getRender();                // slot 5

    Render* render_;                            // 0x04
    void* texture_;                             // 0x08
    unsigned char polygonID_;                   // 0x0C
    unsigned char alpha_;                       // 0x0D
    int enable_;                                // 0x10

    UnkRenderObject();                             // C2 0x02083658
    void unkfunc_02046fe8();                    // polygon attributes
    void unkfunc_02047010();                    // shadow mask polygon attributes
    void unkfunc_02047028();                    // shadow polygon attributes
};

/* vtable 0x020c1c88 */
struct UnkRenderObject3D : UnkRenderObject, Position {
#if !defined(BILLBOARD_CHARACTER_TU) && !defined(RENDER_OBJECT_TU)
    virtual void draw();                        // never defined: key function so the vtable is only emitted by BillboardCharacter.cpp
#endif
};

struct UnkBillboardVertex {
    dss::Vector2<dss::Fix16> v[4];
};

struct UnkBillboardTexCoord {
    dss::Vector2<dss::Fix32> v[4];

    void set(const dss::Vector2<dss::Fix32>& v0, const dss::Vector2<dss::Fix32>& v1,
             const dss::Vector2<dss::Fix32>& v2, const dss::Vector2<dss::Fix32>& v3);
};


void unkfunc_02047d38();                        // billboard: keep only the translation of the current matrix
void unkfunc_0204813c();                        // 2D projection (256x192, depth 1)
void unkfunc_020481fc();                        // 2D projection (256x192, depth 1/64), used by the battle monster mask and the sprites drawn over a 2D map
void unkfunc_020482b8();                        // 2D projection (256x192, depth 1024)
void unkfunc_02048370();                        // draw the background gradient
void unkfunc_020485cc(int r, int g, int b);     // background gradient: one color everywhere
void unkfunc_02048640(unsigned char* bottomUpLeft, unsigned char* bottomUpRight, unsigned char* bottomDownLeft, unsigned char* bottomDownRight,
                      unsigned char* topUpLeft, unsigned char* topUpRight, unsigned char* topDownLeft, unsigned char* topDownRight);
void unkfunc_02048640(unsigned char* bottomUpLeft, unsigned char* bottomUpRight, unsigned char* bottomDownLeft, unsigned char* bottomDownRight,
                      unsigned char* topUpLeft, unsigned char* topUpRight, unsigned char* topDownLeft, unsigned char* topDownRight);
void unkfunc_02048728(int enable);              // background gradient on/off
void unkfunc_02048738();
