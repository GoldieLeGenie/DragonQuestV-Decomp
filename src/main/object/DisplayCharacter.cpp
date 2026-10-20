#pragma ipa file
#include "main/object/DisplayCharacter.hpp"
#include "main/dss/Camera.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/dss/UnkPaletteEffect.hpp"
#include "main/dss/TextureObject.hpp"
#include "main/dss/VramTransferManager.hpp"
#include "main/fld/FldStage.hpp"
#include "nitro/fx/fx_trig.h"
#include "nitro/os.hpp"

inline bool isEven()
{
    return (getDisplayFrame() & 1) == 0;
}

inline dss::Camera* getCamera()
{
    bool even = isEven();
    dss::UnkDualCameraBase* camera = BillboardCharacter::camera_;
    return !even ? &camera->unk_004 : &camera->unk_074;
}

dss::Fix32 DisplayCharacter::workScale_(2.0f);
int DisplayCharacter::headEnable_ = 1;
int DisplayCharacter::shadowType_ = 0xe10000;
dss::Fix32Vector3 DisplayCharacter::boxTestRotate_;
dss::Fix32Vector3 DisplayCharacter::boxTestScale_(1.25f, 2.5f, 1.25f);
GXBoxTestParam DisplayCharacter::boxTestParam_;
dss::Fix32 DisplayCharacter::boxTestRate_(FX32_ONE);
dss::Fix32 DisplayCharacter::nearBodyOffset_(0.375f);
dss::Fix32 DisplayCharacter::nearHeadOffset_(0.28f);
dss::Fix32 DisplayCharacter::sleepHeight_(0.194f);
dss::Fix32 DisplayCharacter::sleepBodyOffset_(0.27f);
dss::Fix32 DisplayCharacter::sleepHeadOffset_(0.173f);
dss::Fix32Vector3 DisplayCharacter::sleepOffset_[8] = {
    dss::Fix32Vector3(0.0f, 0.0f, 0.5f),
    dss::Fix32Vector3(0.35f, 0.0f, 0.35f),
    dss::Fix32Vector3(0.5f, 0.0f, 0.0f),
    dss::Fix32Vector3(0.35f, 0.0f, -0.35f),
    dss::Fix32Vector3(0.0f, 0.0f, -0.5f),
    dss::Fix32Vector3(-0.35f, 0.0f, -0.35f),
    dss::Fix32Vector3(-0.5f, 0.0f, 0.0f),
};

const int DisplayCharacter::FLAG_BOX_TEST_OFF = 0x4000;
const int DisplayCharacter::SLEEP_DIRECTION = 8;

dss::UnkDualCameraBase* BillboardCharacter::camera_;

ARM DisplayCharacter::DisplayCharacter()
{
}

ARM DisplayCharacter::~DisplayCharacter()
{
}

ARM void DisplayCharacter::unkfunc_02056b80(void* data)
{
    unkfunc_0205568c(data);
    head_.texture_ = RenderObject::texture_;
}

ARM void DisplayCharacter::unkfunc_02056b98()
{
    unkfunc_02055a34();
    head_.texture_ = RenderObject::texture_;
}

ARM void DisplayCharacter::setup(const char* name, dss::File::LoadSwitch loadSwitch)
{
    unkfunc_02055a88(name, loadSwitch);

    UnkBillboardVertex vertex = *unkfunc_02047a8c();
    UnkBillboardTexCoord texCoord = *unkfunc_02047b00();
    vertex.v[0].vy = vertex.v[3].vy * 7 / 16;
    vertex.v[1].vy = vertex.v[2].vy * 7 / 16;
    texCoord.v[0].vy = texCoord.v[0].vy * 9 / 16;
    texCoord.v[1].vy = texCoord.v[1].vy * 9 / 16;
    head_.unkfunc_02047a20(&vertex);
    head_.unkfunc_02047a94(&texCoord);
    head_.texture_ = RenderObject::texture_;
    head_.setScale(workScale_);
    head_.setPolygonID(1);

    UnkBillboardVertex bodyVertex = *unkfunc_02047a8c();
    UnkBillboardTexCoord bodyTexCoord = *unkfunc_02047b00();
    bodyVertex.v[3].vy = bodyVertex.v[3].vy * 1 / 2;
    bodyVertex.v[2].vy = bodyVertex.v[2].vy * 1 / 2;
    bodyTexCoord.v[2].vy = bodyTexCoord.v[0].vy * 1 / 2;
    bodyTexCoord.v[3].vy = bodyTexCoord.v[1].vy * 1 / 2;
    unkfunc_02047a20(&bodyVertex);
    unkfunc_02047a94(&bodyTexCoord);
    RenderObject::setPolygonID(1);

    boxTestParam_.x = 0;
    boxTestParam_.y = 0;
    boxTestParam_.z = 0;
    boxTestParam_.width = FX32_ONE;
    boxTestParam_.height = FX32_ONE;
    boxTestParam_.depth = FX32_ONE;
    unk_264 = 0;
}

ARM void DisplayCharacter::cleanup()
{
    BillboardCharacter::cleanup();
}

ARM void DisplayCharacter::setRender(Render* render)
{
    RenderObject::setRender(render);
}

ARM void DisplayCharacter::removeRender()
{
    RenderObject::removeRender();
}

ARM void DisplayCharacter::setAlpha(int alpha)
{
    RenderObject::setAlpha(alpha);
    head_.setAlpha(alpha);
    setShadowAlpha((unsigned char)(alpha * 12 / 31));
}

ARM int DisplayCharacter::box_testx1()
{
    dss::Fix32Vector3 position = *getPosition();
    position.vx.value -= 0x800;
    unkfunc_0206b048(&position, &boxTestRotate_, &boxTestScale_, &boxTestParam_, &boxTestRate_);
    int result;
    while (func_02075ff4(&result)) {
    }
    return result == 0;
}

ARM bool DisplayCharacter::unkfunc_02057098()
{
    dss::Fix32Vector3& cameraPosition = getCamera()->getPosition();
    VecFx32 vec;
    vec.x = position_.vx.value - cameraPosition.vx.value;
    vec.y = position_.vy.value - cameraPosition.vy.value;
    vec.z = position_.vz.value - cameraPosition.vz.value;
    fx32 dot = func_0208a210((VecFx32*)&getCamera()->unk_3c, &vec);
    return dot <= FX_Mul(func_0208a2d0(&vec), 0xfc2);
}

ARM void DisplayCharacter::draw()
{
    if (!isDisplayEnable() || !unkfunc_020560a4() || !enable_ || !alpha_) {
        flag_ |= FLAG_DRAW_RESET;
        return;
    }
    execHueChange();
    if (!(flag_ & FLAG_BOX_TEST_OFF)) {
        if (unkfunc_02057098()) {
            if (!((flag_ & FLAG_SLEEP) ? 1 : 0)) {
                execute();
            }
            flag_ |= FLAG_DRAW_RESET;
            return;
        }
        if (box_testx1()) {
            if (!((flag_ & FLAG_SLEEP) ? 1 : 0)) {
                execute();
            }
            flag_ |= FLAG_DRAW_RESET;
            return;
        }
    }
    dss::Fix32Vector3 position = *getPosition();
    exec();
    if (flag_ & FLAG_SLEEP) {
        startAnimation(1);
        drawSleepCharacter();
    } else {
        BillboardCharacter::draw();
        if (headEnable_ && !(flag_ & FLAG_SHADOW_ONLY)) {
            head_.unkfunc_02047b08(&uvOffset);
            head_.draw();
        }
    }
    setPosition(position);
}

ARM void DisplayCharacter::drawSleepCharacter()
{
    if (!enable_) {
        return;
    }
    setScale(data_02102ee4);
    unkfunc_020561d0(data_02102ee4);
    setCameraDirection(&unkfunc_02056274()->getDirection());
    for (int i = 0; i < SLEEP_DIRECTION; i++) {
        sleepOffset_[i].vy = sleepHeight_;
    }
    dss::Fix32Vector3 position = *head_.getPosition() + sleepOffset_[(direction_ / 0x2000) & 7];

    UnkBillboardVertex* vertex = unkfunc_02047a8c();
    UnkBillboardTexCoord texCoord = *unkfunc_02047b00();
    dss::Vector2<dss::Fix32> offset = uvOffset;
    for (int i = 0; i < 4; i++) {
        texCoord.v[i].vx += offset.vx;
        texCoord.v[i].vy += offset.vy;
    }
    drawSleep(position, *vertex, texCoord);

    UnkBillboardVertex* headVertex = head_.unkfunc_02047a8c();
    UnkBillboardTexCoord headTexCoord = *head_.unkfunc_02047b00();
    dss::Vector2<dss::Fix32> headOffset = uvOffset;
    for (int i = 0; i < 4; i++) {
        headTexCoord.v[i].vx += headOffset.vx;
        headTexCoord.v[i].vy += headOffset.vy;
    }
    drawSleep(position, *headVertex, headTexCoord);
}

ARM void DisplayCharacter::drawSleep(dss::Fix32Vector3& position, UnkBillboardVertex& vertex, UnkBillboardTexCoord& texCoord)
{
    G3_PushMtx();
    G3_Translate(position.vx.value, position.vy.value, position.vz.value);
    loadBillboardMatrix();
    G3_Scale(scale_.vx.value, scale_.vx.value, scale_.vx.value);
    if (RenderObject::texture_) {
        ((TextureObject*)RenderObject::texture_)->unkfunc_0204a1e4();
        ((TextureObject*)RenderObject::texture_)->unkfunc_0204a264();
    } else {
        disableTexture();
    }
    unkfunc_02046fe8();
    unkfunc_02047b2c();
    G3_PushMtx();
    unsigned short angle = 0xa000 - dispDirection_;
    func_020761dc(FX_SinIdx(angle), FX_CosIdx(angle));
    if (reverse_) {
        G3_Begin(1);
        G3_Color(0x7fff);
        for (int i = 0; i < 4; i++) {
            G3_TexCoord(texCoord.v[i].vx.value, texCoord.v[i].vy.value);
            G3_Vtx(vertex.v[i].vx.value, vertex.v[i].vy.value, 0);
        }
        G3_End();
    } else {
        G3_Begin(1);
        G3_Color(0x7fff);
        for (int i = 0; i < 4; i++) {
            G3_TexCoord(texCoord.v[i].vx.value, texCoord.v[i].vy.value);
            G3_Vtx(vertex.v[i].vx.value, vertex.v[i].vy.value, 0);
        }
        G3_End();
    }
    G3_PopMtx(1);
    G3_PopMtx(1);
}

ARM void DisplayCharacter::exec()
{
    dss::Fix32Vector3& cameraPosition = unkfunc_02056274()->getPosition();
    VecFx32 vec;
    vec.x = cameraPosition.vx.value - position_.vx.value;
    vec.y = cameraPosition.vy.value - position_.vy.value;
    vec.z = cameraPosition.vz.value - position_.vz.value;
    fx32 length = func_0208a2d0(&vec);
    func_0208a330(&vec, &vec);
    fx32 offset;
    if (flag_ & FLAG_SLEEP) {
        offset = sleepBodyOffset_.value;
    } else {
        offset = nearBodyOffset_.value;
    }
    position_.vx.value += FX_Mul(vec.x, offset);
    position_.vy.value += FX_Mul(vec.y, offset);
    position_.vz.value += FX_Mul(vec.z, offset);
    if (flag_ & FLAG_SLEEP) {
        offset = sleepHeadOffset_.value;
    } else {
        offset = nearHeadOffset_.value;
    }
    dss::Fix32Vector3 headPosition;
    headPosition.vx.value = position_.vx.value + FX_Mul(vec.x, offset);
    headPosition.vy.value = position_.vy.value + FX_Mul(vec.y, offset);
    headPosition.vz.value = position_.vz.value + FX_Mul(vec.z, offset);
    head_.setPosition(headPosition);
    workScale_ = FX_Divide(FX_Mul(getScale()->vx.value, length - offset), length);
    head_.setScale(workScale_);
}

ARM void DisplayCharacter::setColor(int color)
{
    unkfunc_02047c10(color);
    head_.unkfunc_02047c10(color);
}

ARM void DisplayCharacter::setBoxTestOff(bool flag)
{
    if (flag) {
        flag_ |= FLAG_BOX_TEST_OFF;
    } else {
        flag_ &= ~FLAG_BOX_TEST_OFF;
    }
}

ARM void DisplayCharacter::setSleep(int flag)
{
    setNearFlag(flag);
    setSleepFlag(flag);
}

ARM bool DisplayCharacter::isHueChange()
{
    return unk_264 != 0;
}

ARM void DisplayCharacter::setHueChange(int type, int frame)
{
    for (int i = 0; i < 8; i++) {
        TextureObject* texture = (TextureObject*)unkfunc_02055a70(i);
        if (texture == NULL) {
            break;
        }
        unsigned short* palette;
        if (texture->flags_ & 1) {
            palette = (unsigned short*)texture->unkfunc_0204a1d4();
        } else {
            palette = (unsigned short*)((char*)texture + texture->unkfunc_0204a1d4());
        }
        if (i != textureIndex_) {
            applyPaletteTone(palette, texture->unkfunc_0204a1dc(), type);
        } else {
            dss::memcpy(unk_288, palette, texture->unkfunc_0204a1dc());
            dss::memcpy(unk_268, palette, texture->unkfunc_0204a1dc());
            applyPaletteTone(unk_268, texture->unkfunc_0204a1dc(), type);
        }
    }
    unk_2a8 = textureIndex_;
    unk_264 = frame;
    unk_266 = 0;
}

ARM void DisplayCharacter::execHueChange()
{
    if (unk_264 == 0) {
        return;
    }
    if (unk_266 > unk_264) {
        unk_264 = 0;
        return;
    }
    if (unk_2a8 == -1) {
        unk_264 = 0;
        return;
    }
    TextureObject* texture = (TextureObject*)unkfunc_02055a70(unk_2a8);
    unsigned short* palette;
    if (texture->flags_ & 1) {
        palette = (unsigned short*)texture->unkfunc_0204a1d4();
    } else {
        palette = (unsigned short*)((char*)texture + texture->unkfunc_0204a1d4());
    }
    dss::Fix32 rate;
    dss::Fix32 inv;
    rate.value = (unk_266 << 12) / unk_264;
    inv.value = 0x1000 - rate.value;
    for (int i = 0; i < 16; i++) {
        unsigned short src = unk_288[i];
        unsigned short dst = unk_268[i];
        int r = (rate.value * (dst & 0x1f) + inv.value * (src & 0x1f)) / 0x1000;
        int g = (rate.value * ((dst & 0x3e0) >> 5) + inv.value * ((src & 0x3e0) >> 5)) / 0x1000;
        int b = (rate.value * ((dst & 0x7c00) >> 10) + inv.value * ((src & 0x7c00) >> 10)) / 0x1000;
        palette[i] = r + (g << 5) + (b << 10);
    }
    DC_CleanAll();
    data_020f4f74.transferToVram(1, palette, ((TextureObject*)unkfunc_02055a70(0))->unkfunc_0204a1cc(), ((TextureObject*)unkfunc_02055a70(0))->unkfunc_0204a1dc(), 0);
    unk_266++;
}

// not in the ROM (dummy function)
ARM void unkfunc_unused_0209a680(int type)
{
    DisplayCharacter::shadowType_ = type;
}
