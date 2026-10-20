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

ARM void Render::unkfunc_02048860()
{
    unk_000 = NULL;
    for (int i = 0; i < 32; i++) {
        unk_004[i] = NULL;
    }
    for (int i = 0; i < 64; i++) {
        unk_084[i] = NULL;
    }
    for (int i = 0; i < 128; i++) {
        unk_204[i] = NULL;
    }
}

ARM void Render::unkfunc_020488b4()
{
    unk_000 = NULL;
    for (int i = 0; i < 32; i++) {
        unk_004[i] = NULL;
    }
    for (int i = 0; i < 64; i++) {
        unk_084[i] = NULL;
    }
    for (int i = 0; i < 128; i++) {
        unk_204[i] = NULL;
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
    unkfunc_02048370();
    data_020f3f04[1] = func_020885e0() - start;
    unkfunc_02048c88();
    data_020f3f04[2] = func_020885e0() - start;
    unkfunc_02048ad0();
    data_020f3f04[3] = func_020885e0() - start;
    unkfunc_02048ae8();
    data_020f3f04[4] = func_020885e0() - start;
    func_020802dc();
    func_02082604();
    unkfunc_02048b80();
    unkfunc_02048bb8();
    data_020f3f04[5] = func_020885e0() - start;
    unkfunc_02048738();
    data_020f3f04[6] = func_020885e0() - start;
    unkfunc_02048bfc();
    data_020f3f04[7] = func_020885e0() - start;
    func_02082604();
}

ARM void Render::unkfunc_02048a7c(UnkRenderModel* model)
{
    for (int i = 0; i < 32; i++) {
        if (unk_004[i] == NULL) {
            unk_004[i] = model;
            return;
        }
    }
}

ARM void Render::unkfunc_02048aa4(UnkRenderModel* model)
{
    for (int i = 0; i < 32; i++) {
        if (unk_004[i] == model) {
            unk_004[i] = NULL;
            return;
        }
    }
}

ARM void Render::unkfunc_02048ad0()
{
    if (unk_000 != NULL) {
        unk_000->applyCamera();
    }
}

ARM void Render::unkfunc_02048ae8()
{
    for (int i = 0; i < 32; i++) {
        if (unk_004[i] != NULL) {
            unk_004[i]->draw();
        }
    }
    func_02082604();
}

ARM void Render::unkfunc_02048b24(RenderObject* object)
{
    for (int i = 0; i < 64; i++) {
        if (unk_084[i] == NULL) {
            unk_084[i] = object;
            return;
        }
    }
}

ARM void Render::unkfunc_02048b4c(RenderObject* object)
{
    for (int i = 0; i < 64; i++) {
        if (unk_084[i] != NULL && unk_084[i] == object) {
            unk_084[i] = NULL;
            return;
        }
    }
}

ARM void Render::unkfunc_02048b80()
{
    for (int i = 0; i < 64; i++) {
        if (unk_084[i] != NULL) {
            unk_084[i]->draw();
        }
    }
}

ARM void Render::unkfunc_02048bb8()
{
    if (unk_000 == NULL) {
        return;
    }
    for (int i = 0; i < 32; i++) {
        if (unk_184[i] != NULL) {
            unk_184[i]->draw();
        }
    }
}

ARM void Render::unkfunc_02048bfc()
{
    for (int i = 0; i < 128; i++) {
        if (unk_204[i] != NULL) {
            unk_204[i]->unkfunc_0204667c();
        }
    }
}

ARM void Render::unkfunc_02048c2c(RenderObject* object)
{
    for (int i = 0; i < 128; i++) {
        if (unk_404[i] == NULL) {
            unk_404[i] = object;
            return;
        }
    }
}

ARM void Render::unkfunc_02048c54(RenderObject* object)
{
    for (int i = 0; i < 128; i++) {
        if (unk_404[i] != NULL) {
            if (unk_404[i] == object) {
                unk_404[i] = NULL;
                return;
            }
        }
    }
}

ARM void Render::unkfunc_02048c88()
{
    setupOrtho2D();
    for (int i = 0; i < 128; i++) {
        if (unk_404[i] != NULL) {
            unk_404[i]->draw();
        }
    }
}

ARM void UnkRenderModel::unkfunc_02048cc4(Render* render)
{
    render_ = render;
    render->unkfunc_02048a7c(this);
}

ARM void UnkRenderModel::unkfunc_02048ce0()
{
    if (render_ != NULL) {
        render_->unkfunc_02048aa4(this);
        render_ = NULL;
    }
}
