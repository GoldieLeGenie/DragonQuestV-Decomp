#pragma once
#include <globaldefs.h>

struct Render;
struct RenderObject;
struct ModelAnimation;
namespace dss {
    struct Camera;
}

// base of the 3D scenes drawn by Render (FldStage)
struct UnkRenderModel {
    virtual void setup() = 0;                   // slot 0
    virtual void cleanup() = 0;                 // slot 1
    virtual void draw() = 0;                    // slot 2

    Render* render_;                            // 0x04

    void unkfunc_02048cc4(Render* render);      // setRender
    void unkfunc_02048ce0();                    // removeRender
};

// BattleSystem2::render_ (type Render)
struct Render {
    dss::Camera* unk_000;                       // 0x000 camera
    UnkRenderModel* unk_004[32];                // 0x004 3D scenes
    RenderObject* unk_084[64];                  // 0x084 3D objects
    RenderObject* unk_184[32];                  // 0x184 3D objects drawn with a camera only
    ModelAnimation* unk_204[128];            // 0x204 animations
    RenderObject* unk_404[128];                 // 0x404 2D sprites
    int unk_604;                                // 0x604

    Render();
    void unkfunc_02048860();
    void unkfunc_020488b4();
    void unkfunc_02048908();                    // draw everything
    void unkfunc_02048a7c(UnkRenderModel* model);
    void unkfunc_02048aa4(UnkRenderModel* model);
    void unkfunc_02048ad0();
    void unkfunc_02048ae8();
    void unkfunc_02048b24(RenderObject* object);
    void unkfunc_02048b4c(RenderObject* object);
    void unkfunc_02048b80();
    void unkfunc_02048bb8();
    void unkfunc_02048bfc();
    void unkfunc_02048c2c(RenderObject* object);    // add to the first free slot of unk_404
    void unkfunc_02048c54(RenderObject* object);    // remove
    void unkfunc_02048c88();
};
