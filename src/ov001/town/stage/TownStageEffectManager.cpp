#pragma ipa file
#include "ov001/town/TownStageEffectManager.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov001/town/TownCharacterManager.hpp"
#include "main/global/Global.hpp"
#include "main/status/BattleResult.hpp"
#include "main/status/GameFlag.hpp"
#include "main/status/StageInfo.hpp"
#include "main/dss/UnkModelMember.hpp"
#include "main/dss/UnkPaletteEffect.hpp"

#pragma thumb on

inline int Global::getNowAreaNo()
{
    return areaNo_;
}

inline int Global::getMapNameId()
{
    return nextMapNameId;
}

inline int status::BattleResult::isDisableChurchMessage()
{
    return playerDemolitionMessage_;
}

inline void status::StageInfo::setRockFlag(int index, bool flag)
{
    rockFlag_[index] = flag;
}

inline int TownCharacterManager::getMaxCharacter()
{
    return TOWN_CHARACTER_MAX;
}

inline twn::TownStageWrap::TownStageWrap()
{
}

inline twn::TownStageWrap::~TownStageWrap()
{
}

inline fx32 twn::TownStageWrap::getScalingX()
{
    return scaleX_;
}

inline fx32 twn::TownStageWrap::getScalingY()
{
    return scaleY_;
}

twn::TownStageEffectManager::TownStageEffectManager()
{
}

twn::TownStageEffectManager::~TownStageEffectManager()
{
}

twn::TownStageEffectManager* twn::TownStageEffectManager::getSingleton()
{
    static TownStageEffectManager townStageEffectManager;
    return &townStageEffectManager;
}

void twn::TownStageEffectManager::initialize()
{
    loadStage();
    if (status::g_BattleResult.isDisableChurchMessage() != 2 && g_Global.getMapNameId() == 0x27) {
        g_LocalFlag.set(0xe);
    }
    if (g_Global.getMapNameId() == 10 && !g_AreaFlag.check(0x51)) {
        lightning_.setup();
    }
    if (g_Global.getNowAreaNo() != 0x33) {
        wire_.enable_ = false;
    }
    if (g_Global.getNowAreaNo() == 0x33 || g_Global.getNowAreaNo() == 0x27) {
        wire_.enable_ = true;
        if (!g_LocalFlag.check(100)) {
            for (int i = 0; i < 10; i++) {
                status::g_StageInfo.setRockFlag(i, true);
            }
        }
    }
    if (g_Global.getNowAreaNo() == 0x2a && !g_LocalFlag.check(0x65)) {
        for (int i = 0; i < 10; i++) {
            status::g_StageInfo.setRockFlag(i, true);
        }
    }
}

void twn::TownStageEffectManager::terminate()
{
    tinct_.cleanup();
    wrap_.cleanup();
    lightning_.cleanup();
    spotlight_.unkfunc_0212e8d4();
    puzzle_.cleanup();
    wire_.cleanup();
}

void twn::TownStageEffectManager::execute()
{
    spotlight_.unkfunc_0212e900();
    lightning_.execute();
    puzzle_.execute();
    wire_.execute();
}

void twn::TownStageEffectManager::draw()
{
    spotlight_.unkfunc_0212e920();
}

void twn::TownStageEffectManager::loadStage()
{
    tinct_.loadStage();
}

void twn::TownStageEffectManager::setRGBRate(dss::Fix32Vector3& rate, int realTime)
{
    tinct_.setRGBRate(rate, realTime);
}

void twn::TownStageEffectManager::setStopLightning(bool stop)
{
    lightning_.setEnable(!stop);
    if (stop) {
        dss::Fix32Vector3 rate;
        rate.vx.value = 0x1000;
        rate.vy.value = 0x1000;
        rate.vz.value = 0x1000;
        unkfunc_02049228(unkfunc_02046f40(), rate);
    } else {
        dss::Fix32Vector3 rate;
        unkfunc_02049228(unkfunc_02046f40(), rate);
    }
}

void twn::TownStageEffectManager::setTorchlight()
{
    spotlight_.unkfunc_0212e850();
    spotlight_.setBlindAlpha(0x12);
    spotlight_.unkfunc_0212e974(1, 1, 8);
    int add = 0x20;
    int size = 0x20;
    spotlight_.unkfunc_0212e95c(true);
    for (int i = 0; i < MAX_TORCH; i++) {
        spotlight_.unkfunc_0212e8b4(i, &TownPlayerManager::getSingleton().getPosition());
        spotlight_.light_[i].alpha_ = i * 4 + 1;
        size += add / 2;
        spotlight_.light_[i].size_ = size;
        add = 0x40 - size;
        spotlight_.light_[i].color_ = 0x3084;
    }
    TownCharacterManager::getSingleton()->setSpecCleanup(0x4d);
}

void twn::TownStageEffectManager::setSpotlight(dss::Fix32Vector3* pos)
{
    spotlight_.unkfunc_0212e850();
    spotlight_.setBlindAlpha(0);
    spotlight_.unkfunc_0212e974(0, 0, 0);
    int add = 0;
    int size = 0x40;
    spotlight_.unkfunc_0212e95c(true);
    for (int i = 0; i < MAX_TORCH; i++) {
        spotlight_.unkfunc_0212e8b4(i, pos);
        spotlight_.light_[i].alpha_ = i * 4 + 1;
        size += add / 2;
        spotlight_.light_[i].size_ = size;
        add = 0x40 - size;
        spotlight_.light_[i].color_ = 0x7fff;
    }
}

void twn::TownStageEffectManager::clearTorchlight()
{
    for (int i = 0; i < MAX_TORCH; i++) {
        spotlight_.unkfunc_0212e8c4(i);
    }
    spotlight_.unkfunc_0212e95c(false);
}

void twn::TownStageEffectManager::setLightSize(int size)
{
    int min = size - 8;
    if (min < 0) {
        min = 0;
    }
    int add = size - min;
    int lightSize = min;
    for (int i = 0; i < MAX_TORCH; i++) {
        lightSize += add / 2;
        spotlight_.light_[i].size_ = lightSize;
        add = min - lightSize;
    }
}

void twn::TownStageEffectManager::setLightAlpha(unsigned char alpha)
{
    for (int i = 0; i < MAX_TORCH; i++) {
        spotlight_.light_[i].alpha_ = alpha;
    }
}

void twn::TownStageEffectManager::setTextureScaling(fx32 scaleX, fx32 scaleY)
{
    wrap_.setScalingX(scaleX);
    wrap_.setScalingY(scaleY);
}

void twn::TownStageEffectManager::getTextureScaling(fx32& scaleX, fx32& scaleY)
{
    scaleX = wrap_.getScalingX();
    scaleY = wrap_.getScalingY();
}

void twn::TownStageEffectManager::setEffect(TownStageWrap::EFFECT_TYPE type)
{
    wrap_.setup(type);
}

static const dss::Fix32 DEMONS_ANOTHER_LEFT(7.5f);
static const dss::Fix32 DEMONS_LIMIT_LEFT(9.75f);
static const dss::Fix32 DEMONS_LIMIT_RIGHT(13.25f);
static const dss::Fix32 DEMONS_LIMIT_DEPTH(-6.0f);
static const dss::Fix32 DEMONS_OFFSET_DEPTH(-1.6f);

void twn::TownStageEffectManager::resolveOverlapPosition()
{
    int count = 0;
    dss::Fix32Vector3 pos[11];
    for (int i = 0; i < TownCharacterManager::getSingleton()->getMaxCharacter(); i++) {
        if (TownCharacterManager::getSingleton()->isCharacterEnable(i) && TownCharacterManager::getSingleton()->getCharaIndex(i) == 0x5a) {
            pos[count] = TownCharacterManager::getSingleton()->getPosition(i);
            count++;
        }
    }
    for (int i = 0; i < count; i++) {
        if (pos[i].vy.value < -0x80) {
            pos[i].vy.value = 0;
            if (pos[i].vx.value > DEMONS_ANOTHER_LEFT.value) {
                if (pos[i].vx.value < DEMONS_LIMIT_LEFT.value) {
                    pos[i].vx.value = DEMONS_LIMIT_LEFT.value;
                }
                if (pos[i].vx.value > DEMONS_LIMIT_RIGHT.value) {
                    pos[i].vx.value = DEMONS_LIMIT_RIGHT.value;
                }
            }
            TownCharacterManager::getSingleton()->setPosition(i, pos[i]);
        }
    }
    dss::Fix32Vector3 playerPos = TownPlayerManager::getSingleton().getPosition();
    playerPos.vy.value = 0;
    pos[count] = playerPos;
    dss::Fix32 range = TownPlayerAction::townCharaR * TownPlayerAction::townCharaR + 0x400;
    for (int i = 0; i < count + 1; i++) {
        for (int j = 0; j < count + 1; j++) {
            if (i != j) {
                dss::Fix32Vector3 diff = pos[i] - pos[j];
                if (diff.lengthsq() < range) {
                    pos[i].vz.value -= TownPlayerAction::townCharaR.value * 2;
                    if (pos[i].vz.value < DEMONS_LIMIT_DEPTH.value) {
                        pos[i].vz.value = DEMONS_OFFSET_DEPTH.value + 0x400;
                        pos[i].vx.value -= TownPlayerAction::townCharaR.value * 2;
                    }
                    if (i == count) {
                        TownPlayerManager::getSingleton().setPosition(pos[i]);
                    } else {
                        TownCharacterManager::getSingleton()->setPosition(i, pos[i]);
                    }
                    i--;
                    break;
                }
            }
        }
    }
}
