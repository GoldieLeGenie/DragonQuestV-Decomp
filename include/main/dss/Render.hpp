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

    void setRender(Render* render);      // setRender
    void removeRender();                    // removeRender
};

// BattleSystem2::render_ (type Render)
struct Render {
    dss::Camera* camera_;                       // 0x000 camera
    UnkRenderModel* scenes_[32];                // 0x004 3D scenes
    RenderObject* objects_[64];                  // 0x084 3D objects
    RenderObject* cameraObjects_[32];                  // 0x184 3D objects drawn with a camera only
    ModelAnimation* animations_[128];            // 0x204 animations
    RenderObject* sprites_[128];                 // 0x404 2D sprites
    int unk_604;                                // 0x604

    Render();
    void setup();
    void cleanup();
    void unkfunc_02048908();                    // draw everything
    void addScene(UnkRenderModel* model);
    void removeScene(UnkRenderModel* model);
    void applyCamera();
    void drawScenes();
    void addObject(RenderObject* object);
    void removeObject(RenderObject* object);
    void drawObjects();
    void drawCameraObjects();
    void updateAnimations();
    void addSprite(RenderObject* object);    // add to the first free slot of sprites_
    void removeSprite(RenderObject* object);    // remove
    void drawSprites();
};
