#include "main/dss/Render.hpp"
#include "main/dss/RenderObject.hpp"
#include "main/dss/Billboard.hpp"
#include "main/dss/Camera.hpp"
#include "main/dss/DssCore.hpp"
#include "main/dss/Pad.hpp"
#include "main/object/ModelObject.hpp"
#include "main/object/DSSAObject.hpp"

inline void RenderObject::draw()
{
}

unsigned long long data_020f3f04[10];

ARM Render::Render()
{
    unk_604 = 0;
}

ARM void Render::setup()
{
    camera_ = NULL;
    for (int i = 0; i < 32; i++) {
        scenes_[i] = NULL;
    }
    for (int i = 0; i < 64; i++) {
        objects_[i] = NULL;
    }
    for (int i = 0; i < 128; i++) {
        animations_[i] = NULL;
    }
}

ARM void Render::cleanup()
{
    camera_ = NULL;
    for (int i = 0; i < 32; i++) {
        scenes_[i] = NULL;
    }
    for (int i = 0; i < 64; i++) {
        objects_[i] = NULL;
    }
    for (int i = 0; i < 128; i++) {
        animations_[i] = NULL;
    }
}

ARM void Render::unkfunc_02048908()
{
    unsigned long long start = func_020885e0();
    VecFx32 scale = { FX32_ONE, FX32_ONE, FX32_ONE };
    VecFx32 trans = { 0, 0, 0 };
    func_0208032c(&scale);
    func_02080308((dss::Fix32Vector3*)&trans);
    func_020802dc();
    dss::g_Pad.edge();
    data_020f3f04[0] = func_020885e0() - start;
    setupOrtho2DBackground();
    drawBackgroundGradient();
    data_020f3f04[1] = func_020885e0() - start;
    drawSprites();
    data_020f3f04[2] = func_020885e0() - start;
    applyCamera();
    data_020f3f04[3] = func_020885e0() - start;
    drawScenes();
    data_020f3f04[4] = func_020885e0() - start;
    func_020802dc();
    func_02082604();
    drawObjects();
    drawCameraObjects();
    data_020f3f04[5] = func_020885e0() - start;
    drawSubScreenShade();
    data_020f3f04[6] = func_020885e0() - start;
    updateAnimations();
    data_020f3f04[7] = func_020885e0() - start;
    func_02082604();
}

ARM void Render::addScene(UnkRenderModel* model)
{
    for (int i = 0; i < 32; i++) {
        if (scenes_[i] == NULL) {
            scenes_[i] = model;
            return;
        }
    }
}

ARM void Render::removeScene(UnkRenderModel* model)
{
    for (int i = 0; i < 32; i++) {
        if (scenes_[i] == model) {
            scenes_[i] = NULL;
            return;
        }
    }
}

ARM void Render::applyCamera()
{
    if (camera_ != NULL) {
        camera_->applyCamera();
    }
}

ARM void Render::drawScenes()
{
    for (int i = 0; i < 32; i++) {
        if (scenes_[i] != NULL) {
            scenes_[i]->draw();
        }
    }
    func_02082604();
}

ARM void Render::addObject(RenderObject* object)
{
    for (int i = 0; i < 64; i++) {
        if (objects_[i] == NULL) {
            objects_[i] = object;
            return;
        }
    }
}

ARM void Render::removeObject(RenderObject* object)
{
    for (int i = 0; i < 64; i++) {
        if (objects_[i] != NULL && objects_[i] == object) {
            objects_[i] = NULL;
            return;
        }
    }
}

ARM void Render::drawObjects()
{
    for (int i = 0; i < 64; i++) {
        if (objects_[i] != NULL) {
            objects_[i]->draw();
        }
    }
}

ARM void Render::drawCameraObjects()
{
    if (camera_ == NULL) {
        return;
    }
    for (int i = 0; i < 32; i++) {
        if (cameraObjects_[i] != NULL) {
            cameraObjects_[i]->draw();
        }
    }
}

ARM void Render::updateAnimations()
{
    for (int i = 0; i < 128; i++) {
        if (animations_[i] != NULL) {
            animations_[i]->execute();
        }
    }
}

ARM void Render::addSprite(RenderObject* object)
{
    for (int i = 0; i < 128; i++) {
        if (sprites_[i] == NULL) {
            sprites_[i] = object;
            return;
        }
    }
}

ARM void Render::removeSprite(RenderObject* object)
{
    for (int i = 0; i < 128; i++) {
        if (sprites_[i] != NULL) {
            if (sprites_[i] == object) {
                sprites_[i] = NULL;
                return;
            }
        }
    }
}

ARM void Render::drawSprites()
{
    setupOrtho2D();
    for (int i = 0; i < 128; i++) {
        if (sprites_[i] != NULL) {
            sprites_[i]->draw();
        }
    }
}

ARM void UnkRenderModel::setRender(Render* render)
{
    render_ = render;
    render->addScene(this);
}

ARM void UnkRenderModel::removeRender()
{
    if (render_ != NULL) {
        render_->removeScene(this);
        render_ = NULL;
    }
}
