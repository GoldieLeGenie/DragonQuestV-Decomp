#pragma ipa file
#define BILLBOARD_CHARACTER_TU
#include "main/dss/Position.hpp"

// The original TU also emitted the weak vtables of Position and UnkPositionInterface (created last in the data
// layout). Our headers keep Position's virtuals external, so this dead-stripped stand-in recreates both vtables.
struct PositionWeakVtable : UnkPositionInterface {
    virtual void setPosition(const dss::Fix32Vector3& position);
    virtual void setScale(dss::Fix32 scale);
    virtual void setScale(const dss::Fix32Vector3& scale);
    virtual void setRotation(const dss::Fix32Vector3& rotation);
    virtual void setRotationIdx(const dss::Vector3<unsigned short>& rotation);
};

#include "main/object/DisplayCharacter.hpp"
#include "main/dss/Camera.hpp"
#include "main/dss/UnkArchive.hpp"
#include "main/dss/UnkMatrix43.hpp"
#include "main/dss/UnkPaletteEffect.hpp"
#include "main/dss/ShadowPolygon.hpp"
#include "main/dss/TextureObject.hpp"
#include "nitro/fx/fx_atan.h"
#include "nitro/fx/fx_trig.h"
#include "nitro/os.hpp"

namespace dss {
    template <>
    ARM inline Vector3<Fix16>::Vector3() : vy(0L), vx(0L), vz(0L)
    {
    }
}

dss::BitFlag<unsigned char> BillboardCharacter::allFlag_(BillboardCharacter::FLAG_ANIM);

inline void PositionWeakVtable::setPosition(const dss::Fix32Vector3& position)
{
}

inline void PositionWeakVtable::setScale(dss::Fix32 scale)
{
}

inline void PositionWeakVtable::setScale(const dss::Fix32Vector3& scale)
{
}

inline void PositionWeakVtable::setRotation(const dss::Fix32Vector3& rotation)
{
}

inline void PositionWeakVtable::setRotationIdx(const dss::Vector3<unsigned short>& rotation)
{
}

inline UnkLZDataObject::UnkLZDataObject()
{
}

// not in the ROM (dead-stripped): keeps the weak UnkLZDataObject destructor emitted in front of the unit, and the
// weak vtables of the stand-in
THUMB void unkfunc_unused_020555c4()
{
    UnkLZDataObject data[2];
    PositionWeakVtable unused;
}

static dss::Fix32 s_scale(1.915f);
int BillboardCharacter::allAnimLock;
static int s_shadowType;
dss::Fix32 data_02102ee4(1.927f);
int BillboardCharacter::changeAngle_;
static int s_shadowEnable = 1;
dss::Camera* BillboardCharacter::baseCamera_;
UnkBillboardAnimation BillboardCharacter::animation_[] = {
    { 0, 12 },
    { 1, 12 },
    { 2, 12 },
    { 1, 12 },
    { -1, -1 },
};
static TextureObject* s_shadowTexture;
static dss::Vector3<dss::Fix16> s_shadowVertexRightTop(1.0f, 0.0f, 1.0f);

inline dss::Vector2<dss::Fix16>::Vector2(dss::Fix16 x, dss::Fix16 y)
{
    vx = x;
    vy = y;
}

inline UnkPolygonCorners::UnkPolygonCorners(const dss::Vector3<dss::Fix16>& v0, const dss::Vector3<dss::Fix16>& v1,
                                          const dss::Vector3<dss::Fix16>& v2, const dss::Vector3<dss::Fix16>& v3)
{
    v[0] = v0;
    v[1] = v1;
    v[2] = v2;
    v[3] = v3;
}

inline void UnkBillboardTexCoord::set(const dss::Vector2<dss::Fix32>& v0, const dss::Vector2<dss::Fix32>& v1,
                                      const dss::Vector2<dss::Fix32>& v2, const dss::Vector2<dss::Fix32>& v3)
{
    v[0] = v0;
    v[1] = v1;
    v[2] = v2;
    v[3] = v3;
}

inline UnkBillboardTexCorners::UnkBillboardTexCorners(const dss::Vector2<dss::Fix32>& v0, const dss::Vector2<dss::Fix32>& v1,
                                                      const dss::Vector2<dss::Fix32>& v2, const dss::Vector2<dss::Fix32>& v3)
{
    set(v0, v1, v2, v3);
}

ARM BillboardCharacter::BillboardCharacter() : direction_(0), flag_(0)
{
    width_ = 0x20;
    height_ = 0x20;
    flag_ = 0;
    texture_ = NULL;
    changeAngle_ = 1;
}

ARM void DisplayCharacter::setCharacterSize(int width, int height)
{
    width_ = width;
    height_ = height;
}

ARM void BillboardCharacter::unkfunc_0205568c(void* data)
{
    textureNum_ = unkfunc_0204c860(data);
    for (int i = 0; i < textureNum_; i++) {
        textures_[i] = getArchiveFile(data, i);
    }
    OS_Wait();
    dss::Fix16 right;
    dss::Fix16 left;
    dss::Fix16 top;
    right.value = (width_ << 12) / 100;
    left.value = -right.value;
    top.value = ((height_ << 12) / 100) * 2;
    dss::Vector2<dss::Fix16> leftBottom(left, 0L);
    dss::Vector2<dss::Fix16> rightBottom(right, 0L);
    dss::Vector2<dss::Fix16> rightTop(right, top);
    dss::Vector2<dss::Fix16> leftTop(left, top);
    dss::Vector2<dss::Fix32> texCoordLeftTop(0L, 0L);
    dss::Vector2<dss::Fix32> texCoordRightTop(width_, 0L);
    dss::Vector2<dss::Fix32> texCoordRightBottom(width_, height_);
    dss::Vector2<dss::Fix32> texCoordLeftBottom(0L, height_);
    UnkBillboardVertex vertex;
    vertex.v[0] = leftBottom;
    vertex.v[1] = rightBottom;
    vertex.v[2] = rightTop;
    vertex.v[3] = leftTop;
    UnkBillboardTexCoord texCoord;
    texCoord.set(texCoordLeftBottom, texCoordRightBottom, texCoordRightTop, texCoordLeftTop);
    unkfunc_0205071c(&vertex, &texCoord, textures_[0]);
    textureIndex_ = -1;
}

static dss::Vector3<dss::Fix16> s_shadowVertexRightBottom(1.0f, 0.0f, -1.0f);
static dss::Vector3<dss::Fix16> s_shadowVertexLeftBottom(-1.0f, 0.0f, -1.0f);
static dss::Vector3<dss::Fix16> s_shadowVertexLeftTop(-1.0f, 0.0f, 1.0f);

ARM void BillboardCharacter::unkfunc_02055a34()
{
    unkfunc_0205568c(data_.getAddr());
    textureIndex_ = -1;
}

ARM void DisplayCharacter::unkfunc_02055a60()
{
    ((TextureObject*)RenderObject::texture_)->unkfunc_02049f90();
}

ARM void* BillboardCharacter::unkfunc_02055a70(int index)
{
    if (index >= textureNum_) {
        return NULL;
    }
    return textures_[index];
}

ARM void BillboardCharacter::unkfunc_02055a88(const char* name, dss::File::LoadSwitch loadSwitch)
{
    data_.setup(name, loadSwitch, 0);
    unkfunc_02055ab0();
}

ARM void BillboardCharacter::unkfunc_02055ab0()
{
    enable_ = 1;
    flag_ |= FLAG_DEFAULT;
    unkfunc_0205568c(data_.getAddr());
    anmIndex_ = 0;
    anmTime_ = 0;
    textureIndex_ = -1;
    preDirection_ = 5;
    setScale(s_scale);
    dss::Fix32Vector3 scale = UnkCharacterShadow::unkfunc_02056920();
    unk_108.vx.value = scale.vx.value * width_ / 32;
    unk_108.vy.value = scale.vy.value * width_ / 32;
    unk_108.vz.value = scale.vz.value * width_ / 32;
    shadow_.unkfunc_020567b0(0);
}

ARM void BillboardCharacter::cleanup()
{
    removeRender();
    unkfunc_02050760();
    data_.cleanup();
    shadow_.unkfunc_02056824();
    enable_ = 0;
    flag_ = 0;
}

ARM void BillboardCharacter::draw()
{
    if (!enable_) {
        flag_ |= FLAG_DRAW_RESET;
        return;
    }
    setScale(s_scale);
    unkfunc_020561d0(s_scale);
    setCameraDirection(&baseCamera_->getDirection());
    if (flag_ & FLAG_ANIM_PALLET) {
        unkfunc_02049ad8((TextureObject*)texture_, unk_0fc);
    }
    execute();
    if (flag_ & FLAG_SHADOW) {
        shadow_.setScale(unk_108);
        shadow_.draw();
    }
    if (!(flag_ & FLAG_SHADOW_ONLY)) {
        Billboard::draw();
    }
    flag_ &= ~FLAG_DRAW_RESET;
}

ARM void BillboardCharacter::execute()
{
    if (allAnimLock == 1) {
        return;
    }
    if (flag_ & FLAG_ANIM_NEUTRAL) {
        if (!(allFlag_.flag_ & FLAG_ANIM)) {
            return;
        }
    } else if (!(flag_ & FLAG_ANIM)) {
        return;
    }
    if (flag_ & FLAG_WRIGGLE) {
        anmTime_ += 2;
    } else {
        anmTime_ += 1;
    }
    if (anmTime_ >= animation_[anmIndex_].time) {
        anmTime_ = 0;
        anmIndex_++;
        if (animation_[anmIndex_].index == -1) {
            anmTime_ = 0;
            anmIndex_ = 0;
        }
    }
    startAnimation(anmIndex_);
}

ARM void BillboardCharacter::startAnimation(int index)
{
    uvOffset.vx.value = (width_ * animation_[index].index) << 12;
    unk_a8.vx.value = uvOffset.vx.value;
    unk_a8.vy.value = uvOffset.vy.value;
}

ARM void BillboardCharacter::setRotate(unsigned short direction)
{
    direction_ = direction;
}

ARM unsigned short BillboardCharacter::getRotate()
{
    return direction_;
}

ARM void BillboardCharacter::unkfunc_02055db8(int index)
{
    if (textureIndex_ == index && !(flag_ & FLAG_RELOAD)) {
        return;
    }
    textureIndex_ = index;
    unkfunc_02050770((int)textures_[index]);
    flag_ &= ~FLAG_RELOAD;
}

static dss::Vector2<dss::Fix32> s_shadowTexCoordLeftTop(0L, 0L);
static dss::Vector2<dss::Fix32> s_shadowTexCoordLeftBottom(0L, 0x20L);
static dss::Vector2<dss::Fix32> s_shadowTexCoordRightBottom(0x20L, 0x20L);
static dss::Vector2<dss::Fix32> s_shadowTexCoordRightTop(0x20L, 0L);
static UnkPolygonCorners s_shadowVertex(s_shadowVertexRightTop, s_shadowVertexRightBottom, s_shadowVertexLeftBottom,
                                       s_shadowVertexLeftTop);
static UnkBillboardTexCorners s_shadowTexCoord(s_shadowTexCoordLeftTop, s_shadowTexCoordLeftBottom, s_shadowTexCoordRightBottom,
                                             s_shadowTexCoordRightTop);
static DataObject s_shadowData;
// mobile global that nothing uses here: dead-stripped (own section), but part of the pooled data layout
char g_chara_scale_flag;

ARM void BillboardCharacter::setCameraDirection(const dss::Fix32Vector3* direction)
{
    if (!(flag_ & FLAG_SLEEP)) {
        if (direction_ == preDirection_ && changeAngle_ == 0 && !(flag_ & FLAG_DRAW_RESET)) {
            return;
        }
        preDirection_ = direction_;
    }
    int cmrDir = FX_Atan2Idx(direction->vx.value, direction->vz.value);
    dispDirection_ = cmrDir - direction_ + 0x10000;
    dispDirection_ = (unsigned short)dispDirection_;
    if (textureNum_ == 4) {
        dispDirection_ = (unsigned short)(dispDirection_ + 0x2000);
        for (int i = 0; i < 4; i++) {
            int area = i * 0x4000 + 0x4000;
            if (area > dispDirection_) {
                if (flag_ & FLAG_SLEEP) {
                    if (i == 0) {
                        i = 2;
                    }
                    unkfunc_02055db8(i);
                    reverse_ = i % 2;
                } else {
                    unkfunc_02055db8(i);
                }
                break;
            }
        }
    } else if (!(flag_ & FLAG_SLEEP)) {
        dispDirection_ = (unsigned short)(dispDirection_ + 0x1000);
        for (int i = 0; i < 8; i++) {
            int area = i * 0x2000 + 0x2000;
            if (area > dispDirection_) {
                unkfunc_02055db8(i);
                break;
            }
        }
    } else {
        dispDirection_ = (unsigned short)(dispDirection_ + 0x2000);
        for (int i = 0; i < 4; i++) {
            int area = i * 0x4000 + 0x4000;
            if (area > dispDirection_) {
                if (i == 0) {
                    i = 2;
                }
                unkfunc_02055db8(i * 2);
                reverse_ = i % 2;
                break;
            }
        }
    }
    if (!UnkCharacterShadow::unkfunc_02056910()) {
        return;
    }
    dss::Vector3<unsigned short> rotation;
    rotation.set(0, 0, 0);
    rotation.vy = cmrDir;
    shadow_.setRotationIdx(rotation);
}

static dss::Fix32Vector3 s_shadowScale(0.347f, 10.0f, 0.206f);
static dss::Vector3<short> s_unused;
static dss::Vector3<dss::Fix16> s_sideVertex[4];
static dss::Fix32Vector3 s_sideDirection[32];
static UnkPolygonVertex s_side;
static ShadowPolygon s_shadowPolygons[32];

ARM void BillboardCharacter::setPosition(const dss::Fix32Vector3& position)
{
    Position::setPosition(position);
    if (flag_ & FLAG_STAY) {
        shadow_.setPosition(position_);
    }
}

ARM void DisplayCharacter::setShadowPos(dss::Fix32Vector3& pos)
{
    shadow_.setPosition(pos);
}

ARM void DisplayCharacter::setShadowType(int type)
{
    UnkCharacterShadow::unkfunc_02056900(type);
}

ARM void DisplayCharacter::setShadowAlpha(int alpha)
{
    shadow_.setAlpha(alpha);
}

ARM void BillboardCharacter::setDisplayEnable(int flag)
{
    if (flag) {
        flag_ |= FLAG_DISPLAY;
    } else {
        flag_ &= ~FLAG_DISPLAY;
    }
}

ARM void BillboardCharacter::unkfunc_0205608c(int flag)
{
    if (flag) {
        flag_ |= FLAG_VISIBLE;
    } else {
        flag_ &= ~FLAG_VISIBLE;
    }
}

ARM int BillboardCharacter::unkfunc_020560a4()
{
    return (flag_ & FLAG_VISIBLE) ? 1 : 0;
}

ARM bool BillboardCharacter::isDisplayEnable()
{
    return (flag_ & FLAG_DISPLAY) ? true : false;
}

ARM void DisplayCharacter::setShadowStay(int flag)
{
    if (flag) {
        flag_ |= FLAG_STAY;
    } else {
        flag_ &= ~FLAG_STAY;
    }
}

ARM void BillboardCharacter::setAnimFlag(int flag)
{
    if (flag == 1) {
        flag_ |= FLAG_ANIM;
        flag_ &= ~FLAG_ANIM_NEUTRAL;
    } else if (flag == 2) {
        flag_ &= ~FLAG_ANIM;
        flag_ |= FLAG_ANIM_NEUTRAL;
    } else {
        flag_ &= ~FLAG_ANIM;
        flag_ &= ~FLAG_ANIM_NEUTRAL;
    }
}

ARM void BillboardCharacter::setNearFlag(int flag)
{
    if (flag) {
        flag_ |= FLAG_NEAR;
    } else {
        flag_ &= ~FLAG_NEAR;
    }
}

ARM void DisplayCharacter::setShadowFlag(int flag)
{
    if (flag) {
        flag_ |= FLAG_SHADOW;
    } else {
        flag_ &= ~FLAG_SHADOW;
    }
}

ARM void DisplayCharacter::setShadowOnlyFlag(int flag)
{
    if (flag) {
        flag_ |= FLAG_SHADOW_ONLY;
    } else {
        flag_ &= ~FLAG_SHADOW_ONLY;
    }
}

ARM void DisplayCharacter::setSleepFlag(int flag)
{
    if (!flag) {
        flag_ &= ~FLAG_SLEEP;
        return;
    }
    anmIndex_ = 1;
    startAnimation(1);
    flag_ |= FLAG_SLEEP;
}

ARM void BillboardCharacter::setWriggleFlag(int flag)
{
    if (flag) {
        flag_ |= FLAG_WRIGGLE;
    } else {
        flag_ &= ~FLAG_WRIGGLE;
    }
}

ARM void BillboardCharacter::unkfunc_020561d0(dss::Fix32 scale)
{
    dss::Fix32Vector3& cameraPosition = baseCamera_->getPosition();
    fx32 rate = FX_Sqrt(FX_Divide(cameraPosition.lengthsq(*getPosition()).value, baseCamera_->getDistanceSq().value));
    setScale(dss::Fix32(FX_Mul(scale.value, rate)));
}

ARM void BillboardCharacter::setCamera(dss::Camera* camera)
{
    baseCamera_ = camera;
}

ARM dss::Camera* BillboardCharacter::unkfunc_02056274()
{
    return baseCamera_;
}

ARM void BillboardCharacter::setAllCharaAnim(bool flag)
{
    if (flag) {
        allFlag_.flag_ |= FLAG_ANIM;
    } else {
        allFlag_.flag_ &= ~FLAG_ANIM;
    }
}

ARM bool BillboardCharacter::isAllAnimation()
{
    return allFlag_.check(FLAG_ANIM);
}

ARM void DisplayCharacter::unkfunc_020562d0(const dss::Fix32Vector3* rate)
{
    unk_0fc = *rate;
}

ARM void DisplayCharacter::unkfunc_020562e0(int flag)
{
    if (flag) {
        flag_ |= FLAG_ANIM_PALLET;
    } else {
        flag_ &= ~FLAG_ANIM_PALLET;
    }
}

ARM void DisplayCharacter::requestReload()
{
    flag_ |= FLAG_RELOAD;
    shadow_.unkfunc_02056824();
    shadow_.unkfunc_020567b0(0);
}

ARM UnkCharacterShadow::UnkCharacterShadow()
{
}

ARM UnkCharacterShadow::~UnkCharacterShadow()
{
}

ARM void BillboardCharacter::unkfunc_0205646c()
{
    unkfunc_0205678c();
    unkfunc_0205647c();
}

ARM void BillboardCharacter::unkfunc_0205647c()
{
    s_shadowData.setup("data/common.tex", 0, 0);
    s_shadowTexture = (TextureObject*)s_shadowData.getAddr();
    s_shadowTexture->unkfunc_02049e9c(1);
    dss::UnkMatrix43 matrix;
    dss::Fix32Vector3 direction;
    dss::Fix32Vector3 work;
    direction.set(1.0f, 0.0f, 0.0f);
    s_sideDirection[0] = direction;
    for (int i = 1, angle = 0x2000; i < 9; angle += 0x2000, i++) {
        matrix.unkfunc_0204f4ec(angle);
        s_sideDirection[i] = matrix * direction;
    }
    for (int i = 0; i < 8; i++) {
        s_sideVertex[0].vx = s_sideDirection[i].vx;
        s_sideVertex[0].vy = s_sideDirection[i].vy;
        s_sideVertex[0].vz = s_sideDirection[i].vz;
        s_sideVertex[0].vy = -2.0f;
        s_sideVertex[1].vx = s_sideDirection[i + 1].vx;
        s_sideVertex[1].vy = s_sideDirection[i + 1].vy;
        s_sideVertex[1].vz = s_sideDirection[i + 1].vz;
        s_sideVertex[1].vy = -2.0f;
        s_sideVertex[2].vx = s_sideDirection[i + 1].vx;
        s_sideVertex[2].vy = s_sideDirection[i + 1].vy;
        s_sideVertex[2].vz = s_sideDirection[i + 1].vz;
        s_sideVertex[2].vy = 2.0f;
        s_sideVertex[3].vx = s_sideDirection[i].vx;
        s_sideVertex[3].vy = s_sideDirection[i].vy;
        s_sideVertex[3].vz = s_sideDirection[i].vz;
        s_sideVertex[3].vy = 2.0f;
        s_side.v[0] = s_sideVertex[0];
        s_side.v[1] = s_sideVertex[1];
        s_side.v[2] = s_sideVertex[2];
        s_side.v[3] = s_sideVertex[3];
        s_shadowPolygons[i].unkfunc_0204709c(&s_side);
        s_shadowPolygons[i].setScale(s_shadowScale);
        s_shadowPolygons[0].unkfunc_02047670(i, &s_side);
    }
}

ARM void BillboardCharacter::unkfunc_0205678c()
{
    s_shadowTexture->unkfunc_02049f90();
    s_shadowData.cleanup();
}

ARM void UnkCharacterShadow::unkfunc_020567b0(int type)
{
    s_shadowType = type;
    unkfunc_0204709c(&s_shadowVertex);
    unkfunc_02047138(&s_shadowTexCoord);
    texture_ = s_shadowTexture;
    setAlpha(12);
    position_.vy.value = 0x400;
    setScale(s_shadowScale);
}

ARM void UnkCharacterShadow::unkfunc_02056824()
{
}

ARM void UnkCharacterShadow::draw()
{
    if (!s_shadowEnable || !alpha_) {
        return;
    }
    if (s_shadowType == 0) {
        fx32 x = position_.vx.value;
        fx32 z = position_.vz.value;
        fx32 s = FX_SinIdx(unk_28.vy);
        fx32 c = FX_CosIdx(unk_28.vy);
        position_.vx.value += s / 16;
        position_.vz.value += c / 16;
        PolygonObject::draw();
        position_.vx.value = x;
        position_.vz.value = z;
        return;
    }
    s_shadowPolygons[0].setRotationIdx(unk_28);
    s_shadowPolygons[0].setPosition(position_);
    s_shadowPolygons[0].unkfunc_0204748c();
}

ARM void UnkCharacterShadow::unkfunc_02056900(int type)
{
    s_shadowType = type;
}

ARM int UnkCharacterShadow::unkfunc_02056910()
{
    return s_shadowEnable;
}

ARM dss::Fix32Vector3 UnkCharacterShadow::unkfunc_02056920()
{
    return s_shadowScale;
}

ARM void UnkCharacterShadow::setPosition(const dss::Fix32Vector3& position)
{
    position_.vx.value = position.vx.value;
    position_.vy.value = position.vy.value + 0x80;
    position_.vz.value = position.vz.value;
}

#include "main/dss/DssVectorDefault.hpp"
