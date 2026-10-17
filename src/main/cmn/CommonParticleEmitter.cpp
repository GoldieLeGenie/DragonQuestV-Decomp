#pragma ipa file
#include "main/cmn/CommonParticleEmitter.hpp"
#include "main/data/DataObject.hpp"
#include "main/dss/UnkRandom.hpp"
#include "main/dss/UnkMemory.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/global/UnkGlobalSystem.hpp"
#include "ov001/town/TownCamera.hpp"
#include "ov005/fld/FieldCamera.hpp"
#include "ov001/town/riseup/TownRiseupExhibit.hpp"
#include "nitro/fx/fx_trig.h"

inline twn::UnkBillboardCorners::UnkBillboardCorners(const dss::Vector2<dss::Fix16>& v0, const dss::Vector2<dss::Fix16>& v1,
                                                   const dss::Vector2<dss::Fix16>& v2, const dss::Vector2<dss::Fix16>& v3)
{
    v[0] = v0;
    v[1] = v1;
    v[2] = v2;
    v[3] = v3;
}

inline bool cmn::CommonParticle::isDelete()
{
    return phase == 5;
}

inline void UnkBillboardTexCoord::set(const dss::Vector2<dss::Fix32>& v0, const dss::Vector2<dss::Fix32>& v1,
                                      const dss::Vector2<dss::Fix32>& v2, const dss::Vector2<dss::Fix32>& v3)
{
    v[0] = v0;
    v[1] = v1;
    v[2] = v2;
    v[3] = v3;
}

namespace cmn
{
    inline int p_rand(int max)
    {
        return UnkDssRand::rand(max);
    }
} // namespace cmn

static dss::Vector2<dss::Fix16> xyLeftBottom(-0.24f, -0.24f);
static dss::Vector2<dss::Fix16> xyRightBottom(0.24f, -0.24f);
static dss::Vector2<dss::Fix16> xyRightTop(0.24f, 0.24f);
static dss::Vector2<dss::Fix16> xyLeftTop(-0.24f, 0.24f);
static twn::UnkBillboardCorners xy(xyLeftBottom, xyRightBottom, xyRightTop, xyLeftTop);
static UnkTextureObject* unk_020f3590[3];
static DataObject unk_020f35d0[3];
static int s_maxAnim[3];
static int s_maxPattern;
static int unk_0209987c = 8; //max frame ? 
static int s_xRange = 0xffff, s_xDownRange = -s_xRange / 2, s_xUpRange = s_xRange / 2;
static int s_yRange = 0xffff, s_yDownRange = -s_yRange * 7 / 8, s_yUpRange = s_yRange / 8;
static int s_zRange = 0xffff, s_zDownRange = -s_zRange / 2, s_zUpRange = s_zRange / 2;
static dss::Fix32 unk_020f3568(0xfc2);
static VecFx32* unk_020f355c;
static UnkBillboardTexCoord unk_020f3600[8];

cmn::CommonParticle::CommonParticle()
{
}

cmn::CommonParticle::~CommonParticle()
{
}

namespace cmn
{
    static void setXRange(int range)
    {
        s_xRange = range;
        s_xDownRange = -range / 2;
        s_xUpRange = range / 2;
    }

    static void setYRange(int range)
    {
        s_yRange = range;
        s_yDownRange = -range * 7 / 8;
        s_yUpRange = range / 8;
    }

    static void setZRange(int range)
    {
        s_zRange = range;
        s_zDownRange = -range / 2;
        s_zUpRange = range / 2;
    }
} // namespace cmn

static void unkfunc_02044e08(int type)
{
    switch (type) {
        case 0:
            unk_020f35d0[0].setup("data/particle/mcyuki1.tex", 0, 0);
            s_maxAnim[0] = 0;
            s_maxPattern = 0;
            break;
        case 1:
            unk_020f35d0[0].setup("data/particle/hanab01.tex", 0, 0);
            s_maxAnim[0] = 5;
            s_maxPattern = 0;
            break;
        case 2:
            unk_020f35d0[0].setup("data/particle/djhosi1.tex", 0, 0);
            s_maxAnim[0] = 0;
            s_maxPattern = 0;
            break;
        case 3:
            unk_020f35d0[0].setup("data/particle/leaves1.tex", 0, 0);
            unk_020f35d0[1].setup("data/particle/leaves2.tex", 0, 0);
            unk_020f35d0[2].setup("data/particle/leaves3.tex", 0, 0);
            s_maxAnim[0] = 6;
            s_maxAnim[1] = 3;
            s_maxAnim[2] = 6;
            s_maxPattern = 2;
            break;
        default:
            unk_020f35d0[0].setup("data/particle/lastkira.tex", 0, 0);
            s_maxAnim[0] = 7;
            s_maxPattern = 0;
            break;
    }
    for (int i = 0; i < s_maxPattern + 1; i++) {
        unk_020f3590[i] = (UnkTextureObject*)unk_020f35d0[i].getAddr();
        unk_020f3590[i]->unkfunc_02049e9c(1);
    }
}

static void unkfunc_02044fb0()
{
    for (int i = 0; i < s_maxPattern + 1; i++) {
        unk_020f3590[i]->unkfunc_02049f90();
        unk_020f35d0[i].cleanup();
    }
}

void cmn::CommonParticle::unkfunc_0204500c()
{
    pattern = 0;
    for (int i = 0; i < 8; i++) {
        dss::Vector2<dss::Fix32> uvLeftTop(i * 16, 0);
        dss::Vector2<dss::Fix32> uvRightTop((i + 1) * 16, 0);
        dss::Vector2<dss::Fix32> uvRightBottom((i + 1) * 16, 16);
        dss::Vector2<dss::Fix32> uvLeftBottom(i * 16, 16);
        unk_020f3600[i].set(uvLeftBottom, uvRightBottom, uvRightTop, uvLeftTop);
    }
    unkfunc_02047a20(&xy);
    unkfunc_02047a94(unk_020f3600);
    setPolygonID(0x3c);
    if (s_maxPattern != 0) {
        pattern = UnkDssRand::rand(s_maxPattern);
    }
    texture_ = unk_020f3590[pattern];
    setAlpha(0);
    alpha_ = 0;
    frame = 0;
    anim = 0;
    phase = 1;
}

void cmn::CommonParticle::unkfunc_020451f8()
{
    frame = 0;
    if (s_maxAnim[pattern] == 0) {
        anim = 0;
    } else {
        anim = UnkDssRand::rand(s_maxAnim[pattern]);
    }
}

void cmn::CommonParticle::execute()
{
    position_.vx.value += velocity.vx.value;
    position_.vy.value += velocity.vy.value;
    position_.vz.value += velocity.vz.value;
    unkfunc_02045278();
    unkfunc_020452f4();
}

void cmn::CommonParticle::unkfunc_02045278()
{
    int maxAnim = s_maxAnim[pattern];
    if (maxAnim == 0) {
        return;
    }
    if (frame >= unk_0209987c) {
        anim = (anim + 1) % (maxAnim + 1);
        frame = 0;
        unkfunc_02047a94(&unk_020f3600[anim]);
    }
    frame++;
}

void cmn::CommonParticle::unkfunc_020452f4()
{
    switch (phase) {
        case 0:
            break;
        case 1:
            alpha_++;
            if (alpha_ > 31) {
                alpha_ = 31;
                phase = 0;
            }
            break;
        case 2:
            if (alpha_ >= 1) {
                alpha_--;
            } else {
                alpha_ = 0;
                phase = 3;
            }
            break;
        case 3:
            phase = 1;
            break;
        case 4:
            if (alpha_ <= 1) {
                alpha_ = 0;
                phase = 5;
            } else {
                alpha_--;
                setAlpha(alpha_);
            }
            break;
    }
}

void cmn::CommonParticle::loopBack(dss::Camera* camera)
{
    dss::Fix32Vector3& target = camera->getTarget();
    if (phase == 3) {
        int distance = target.vx.value - position_.vx.value;
        if (distance < s_xDownRange) {
            position_.vx.value -= s_xRange;
        } else if (distance > s_xUpRange) {
            position_.vx.value += s_xRange;
        }
        distance = target.vy.value - position_.vy.value;
        if (distance < s_yDownRange) {
            position_.vy.value -= s_yRange;
        } else if (distance > s_yUpRange) {
            position_.vy.value += s_yRange;
        }
        distance = target.vz.value - position_.vz.value;
        if (distance < s_zDownRange) {
            position_.vz.value -= s_zRange;
        } else if (distance > s_zUpRange) {
            position_.vz.value += s_zRange;
        }
    } else if (phase != 2) {
        int distance = target.vx.value - position_.vx.value;
        if (distance < s_xDownRange) {
            phase = 2;
        } else if (distance > s_xUpRange) {
            phase = 2;
        }
        distance = target.vy.value - position_.vy.value;
        if (distance < s_yDownRange) {
            phase = 2;
        } else if (distance > s_yUpRange) {
            phase = 2;
        }
        distance = target.vz.value - position_.vz.value;
        if (distance < s_zDownRange) {
            phase = 2;
        } else if (distance > s_zUpRange) {
            phase = 2;
        }
    }
}

bool cmn::CommonParticle::unkfunc_0204556c(dss::Camera* camera)
{
    VecFx32 v;
    dss::Fix32Vector3& pos = camera->getPosition();
    v.x = position_.vx.value - pos.vx.value;
    v.y = position_.vy.value - pos.vy.value;
    v.z = position_.vz.value - pos.vz.value;
    func_0208a330(&v, &v);
    return func_0208a210(unk_020f355c, &v) >= unk_020f3568.value;
}

void cmn::CommonParticle::unkfunc_020455ec()
{
}

cmn::CommonParticleEmitter::CommonParticleEmitter() : enable_(0), stop_(0)
{
}

cmn::CommonParticleEmitter::~CommonParticleEmitter()
{
}

cmn::CommonParticleEmitter* cmn::CommonParticleEmitter::getSingleton()
{
    static CommonParticleEmitter s_singleton;
    return &s_singleton;
}

void cmn::CommonParticleEmitter::initialize()
{
    if (data_02101c88.unkfunc_02051818(4)) {
        unk_00 = &TownCamera::getSingleton()->camera_;
    } else {
        unk_00 = &fld::FieldCamera::getSingleton().camera_;
    }
    int fov = unk_00->unk_004.getFOV2();
    unk_020f3568.value = FX_CosIdx(fov * 0x10000 / 360);
}

void cmn::CommonParticleEmitter::setupParameter(int type)
{
    switch (type) {
        case 0:
            maxScale_ = dss::Fix32(0.7f);
            minScale_ = dss::Fix32(0.25f);
            count_ = 80;
            offset_.value = 0x10000;
            baseVelocity_.set(0.0f, -0.02f, 0.0f);
            offsetVelocity_.set(0.0149f, 0.001f, 0.0149f);
            setYRange(0xffff);
            break;
        case 1:
            maxScale_.value = 0x1000;
            minScale_ = dss::Fix32(0.3f);
            count_ = 0;
            offset_.value = 0x10000;
            baseVelocity_.set(-0.0146f, -0.02f, -0.0049f);
            offsetVelocity_.set(0.0188f, 0.001f, 0.0068f);
            setYRange(0xffff);
            break;
        case 2:
            maxScale_.value = 0x1000;
            minScale_.value = 0x4cc;
            count_ = 128;
            offset_.value = -0x10000;
            baseVelocity_.set(0.001f, 0.0063f, 0.001f);
            offsetVelocity_.set(0.0198f, 0.0098f, 0.0198f);
            setYRange(0xa000);
            break;
        case 3:
            maxScale_ = dss::Fix32(0.9f);
            minScale_ = dss::Fix32(0.4f);
            count_ = 40;
            offset_.value = 0x10000;
            baseVelocity_.set(0.0f, -0.02f, 0.0f);
            offsetVelocity_.set(0.0149f, 0.001f, 0.0149f);
            setYRange(0x7000);
            break;
        default:
            maxScale_ = dss::Fix32(1.0f);
            minScale_ = dss::Fix32(0.5f);
            count_ = 0;
            offset_.value = -0x10000;
            baseVelocity_.set(-0.0127f, -0.0115f, 0.0f);
            offsetVelocity_.set(0.0198f, 0.0098f, 0.0198f);
            setXRange(0xe000);
            setYRange(0x10000);
            setZRange(0xa000);
            break;
    }
}

void cmn::CommonParticleEmitter::setup(int type)
{
    dss::Fix32Vector3 pos;
    dss::Fix32Vector3 velocity;
    dss::Fix32 scl;
    unkfunc_02044e08(type);
    setupParameter(type);
    stop_ = 0;
    enable_ = 1;
    CommonParticle particle;
    particle_ = (CommonParticle*)unkfunc_0204c5bc(&data_020fd24c, sizeof(CommonParticle) * 196, 0x20);
    for (int i = 0; i < 196; i++) {
        dss::memcpy(&particle_[i], &particle, sizeof(CommonParticle));
        particle_[i].unkfunc_0204500c();
        setupParticle(i);
    }
}

void cmn::CommonParticleEmitter::setupParticle(int index)
{
    dss::Fix32Vector3 pos;
    dss::Fix32Vector3 velocity;
    dss::Fix32 scl;
    int range = s_xRange;
    pos.vx.value = p_rand(range) - range / 2;
    range = s_zRange;
    pos.vz.value = p_rand(range) - range / 2;
    pos.vy.value = p_rand(dss::abs<long>(offset_.value));
    scl.value = minScale_.value + p_rand(maxScale_.value - minScale_.value);
    if (offsetVelocity_.vx.value > 0) {
        velocity.vx.value = baseVelocity_.vx.value + p_rand(offsetVelocity_.vx.value) - offsetVelocity_.vx.value / 2;
    }
    if (offsetVelocity_.vy.value > 0) {
        velocity.vy.value = baseVelocity_.vy.value + p_rand(offsetVelocity_.vy.value) - offsetVelocity_.vy.value / 2;
    }
    if (offsetVelocity_.vz.value > 0) {
        velocity.vz.value = baseVelocity_.vz.value + p_rand(offsetVelocity_.vz.value) - offsetVelocity_.vz.value / 2;
    }
    particle_[index].setPosition(pos);
    particle_[index].setScale(scl);
    particle_[index].velocity = velocity;
    particle_[index].unkfunc_020451f8();
}

void cmn::CommonParticleEmitter::cleanup()
{
    for (int i = 0; i < 196; i++) {
        particle_[i].unkfunc_020455ec();
    }
    unkfunc_0204c5c8(&data_020fd24c, particle_);
    unkfunc_02044fb0();
    enable_ = 0;
}

void cmn::CommonParticleEmitter::terminate()
{
    if (enable_) {
        cleanup();
    }
}

void cmn::CommonParticleEmitter::execute()
{
    if (!enable_) {
        return;
    }
    if (stop_) {
        return;
    }
    int delCount = 0;
    for (int i = 0; i < count_; i++) {
        particle_[i].execute();
        if (particle_[i].isDelete()) {
            delCount++;
        }
    }
    count_ -= delCount;
}

void cmn::CommonParticleEmitter::draw()
{
    int polygonID = 0;
    if (!enable_) {
        return;
    }
    int screen;
    if (data_02101c88.unkfunc_02051818(4)) {
        screen = (unkfunc_0204ccd0() & 1) == 0 ? 1 : 0;
    } else {
        screen = unkfunc_0204ccd0() & 1;
    }
    unk_020f355c = (VecFx32*)&(screen == 0 ? &unk_00->unk_004 : &unk_00->unk_074)->unk_3c;
    for (int i = 0; i < count_; i++) {
        particle_[i].loopBack(&unk_00->unk_004);
    }
    for (int i = 0; i < count_; i++) {
        if (particle_[i].unkfunc_0204556c(screen == 0 ? &unk_00->unk_004 : &unk_00->unk_074)) {
            particle_[i].setPolygonID(polygonID & 0x3f);
            particle_[i].draw();
            polygonID++;
        }
    }
}

void cmn::CommonParticleEmitter::setCount(int count)
{
    if (count_ > count) {
        for (int i = count; i < count_; i++) {
            particle_[i].phase = 4;
        }
    } else {
        for (int i = count; i < count_; i++) {
            particle_[i].phase = 1;
        }
        count_ = count;
    }
}

#include "main/dss/DssVectorDefault.hpp"
