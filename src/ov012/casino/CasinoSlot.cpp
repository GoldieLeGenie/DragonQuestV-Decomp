#pragma ipa file
#include "ov012/casino/CasinoSlot.hpp"
#include "ov012/casino/CasinoCamera.hpp"
#include "ov012/casino/CasinoStage.hpp"
#include "ov012/casino/Casino_Slot.hpp"
#include "ov019/materielmenu/MaterielMenu_WINDOW_MANAGER.hpp"

inline casino::CasinoMiniGameBase::~CasinoMiniGameBase()
{
}

inline char* casino::CasinoSlot::getStageName()
{
    return (char*)stageSlot100;
}

inline void dss::UnkDualCamera::setAngle(Vector3<short> angle)
{
    m_camera0.setAngle(angle);
}

inline int casino::Casino_SlotMachine::getEffectLamp(int cnt)
{
    return hitData_[cnt];
}

inline void casino::CasinoStage::setRotObjectUid(int uid, dss::Fix32Vector3& angle)
{
    stage_.m_fld.SetMapUidRotFX32(uid, (VecFx32*)&angle);
}

#pragma explicit_zero_data on
static short cameraAngleY = 0;
static short cameraAngleZ = 0;
static short cameraAngleX = -910;
const char* casino::CasinoSlot::stageSlot1 = "ev07";
const char* casino::CasinoSlot::stageSlot100 = "ev09";
static float cameraDistance = 37.48f;
static int lampBlinkFrame = 64;
const char* casino::CasinoSlot::stageSlot10 = "ev08";
#pragma explicit_zero_data reset

THUMB casino::CasinoSlot::CasinoSlot()
{
}

THUMB casino::CasinoSlot* casino::CasinoSlot::getSingleton()
{
    static CasinoSlot casinoSlot;
    return &casinoSlot;
}

THUMB void casino::CasinoSlot::initialize()
{
    dss::Vector3<short> slot_angle(cameraAngleX, cameraAngleY, cameraAngleZ);
    dss::Fix32 distance(cameraDistance);
    CasinoCamera* camera = CasinoCamera::getSingleton();
    camera->camera_.m_camera0.setDistance(distance);
    camera->camera_.m_camera1.setDistance(distance);
    CasinoCamera::getSingleton()->camera_.setAngle(slot_angle);
    CasinoCamera::getSingleton()->camera_.m_cameraNo = 1;
    CasinoCamera::getSingleton()->camera_.unk_0e8 = 0;
    CasinoCamera::getSingleton()->camera_.unk_0ec = 0;
    camera = CasinoCamera::getSingleton();
    camera->camera_.m_camera0.setFOV2(12);
    camera->camera_.m_camera1.setFOV2(12);
    setLampReelOff();
    bingoType_ = 2;
    MaterielMenu_WINDOW_MANAGER::getSingleton()->openMaterielWindow(0x2c);
}

THUMB void casino::CasinoSlot::terminate()
{
}

THUMB void casino::CasinoSlot::execute()
{
    for (int i = 0; i < 9; i++) {
        Casino_Slot::getSingleton();
        if (lineBingo[i]) {
            int count = bingoCounter[i] + 1;
            int interval = lampBlinkFrame / 2 - 1;
            bingoCounter[i] = count;
            if (interval == count) {
                playLightAnim(i);
            }
            if (lampBlinkFrame == bingoCounter[i]) {
                playDarkAnim(i);
                bingoCounter[i] = 0;
            }
        }
    }
}

THUMB void casino::CasinoSlot::draw()
{
}

THUMB void casino::CasinoSlot::playLightAnim(int pos)
{
    short hitLine = pos % 3;
    short hitData = Casino_Slot::getSingleton()->slotMachine_.hitData_[hitLine];
    short hitPanel = hitData + 0x233;
    short nmlPanel = hitData + 0x221;
    short bingoPanel = hitData + 0x245;
    short spPanel = hitData + 0x257;
    CasinoStage::getSingleton()->setObjectDraw(pos + 0x1f8, 1, 1);
    CasinoStage::getSingleton()->setObjectDraw(pos + 0x1f5, 0, 1);
    CasinoStage::getSingleton()->setObjectDraw(hitLine + 0x1f5, 0, 1);
    if (bingoType_ != 2) {
        CasinoStage::getSingleton()->setObjectDraw(hitPanel, 1, 1);
        CasinoStage::getSingleton()->setObjectDraw(nmlPanel, 0, 1);
        if (bingoType_ == 1) {
            CasinoStage::getSingleton()->setObjectDraw(0x202, 1, 1);
            CasinoStage::getSingleton()->setObjectDraw(0x201, 0, 1);
        }
    } else {
        CasinoStage::getSingleton()->setObjectDraw(spPanel, 1, 1);
        CasinoStage::getSingleton()->setObjectDraw(bingoPanel, 0, 1);
        CasinoStage::getSingleton()->setObjectDraw(0x203, 1, 1);
        CasinoStage::getSingleton()->setObjectDraw(0x202, 0, 1);
        CasinoStage::getSingleton()->setObjectDraw(0x21e, 1, 1);
        CasinoStage::getSingleton()->setObjectDraw(0x21d, 0, 1);
    }
}

THUMB void casino::CasinoSlot::playDarkAnim(int pos)
{
    short hitLine = pos % 3;
    short hitData = Casino_Slot::getSingleton()->slotMachine_.hitData_[hitLine];
    short hitPanel = hitData + 0x233;
    short nmlPanel = hitData + 0x221;
    short bingoPanel = hitData + 0x245;
    short spPanel = hitData + 0x257;
    CasinoStage::getSingleton()->setObjectDraw(pos + 0x1f8, 0, 1);
    CasinoStage::getSingleton()->setObjectDraw(hitLine + 0x1f5, 1, 1);
    if (bingoType_ != 2) {
        CasinoStage::getSingleton()->setObjectDraw(hitPanel, 0, 1);
        CasinoStage::getSingleton()->setObjectDraw(nmlPanel, 1, 1);
        if (bingoType_ == 1) {
            CasinoStage::getSingleton()->setObjectDraw(0x202, 0, 1);
            CasinoStage::getSingleton()->setObjectDraw(0x201, 1, 1);
        }
    } else {
        CasinoStage::getSingleton()->setObjectDraw(spPanel, 0, 1);
        CasinoStage::getSingleton()->setObjectDraw(bingoPanel, 1, 1);
        CasinoStage::getSingleton()->setObjectDraw(0x203, 0, 1);
        CasinoStage::getSingleton()->setObjectDraw(0x202, 1, 1);
        CasinoStage::getSingleton()->setObjectDraw(0x21e, 0, 1);
        CasinoStage::getSingleton()->setObjectDraw(0x21d, 1, 1);
    }
}

THUMB void casino::CasinoSlot::setSlotType(int type)
{
    slotType_ = type;
    for (int i = 0; i < reelMax; i++) {
        setUseReel(i, false);
        setLampOff();
    }
    for (int i = 0; i < 3; i++) {
        lineBingo[i] = 0;
        bingoCounter[i] = 0;
    }
    setUseReel(type, true);
}

THUMB void casino::CasinoSlot::rotReel(int index, unsigned short angle)
{
    dss::Fix32Vector3 ang;
    ang.vx.value = angle;
    CasinoStage::getSingleton()->setRotObjectUid(reelID[index], ang);
}

THUMB char* casino::CasinoSlot::getSlotStageName(int type)
{
    if (type == 100) {
        return (char*)stageSlot100;
    }
    if (type == 10) {
        return (char*)stageSlot10;
    }
    return (char*)stageSlot1;
}

THUMB void casino::CasinoSlot::stopEventAnim()
{
    CasinoStage::getSingleton()->stage_.eventAnim(0, 0);
    for (int i = 0; i < 9; i++) {
        lineBingo[i] = 0;
        bingoCounter[i] = 0;
    }
}

THUMB void casino::CasinoSlot::setUseReel(int type, bool flag)
{
    int i = 0;
    int reel = type * reelMax + 0x209;
    for (; i < reelMax; i++) {
        CasinoStage::getSingleton()->setObjectDraw(reel, flag, 1);
        if (flag) {
            reelID[i] = reel;
        }
        reel++;
    }
}

THUMB void casino::CasinoSlot::setLineLamp(int line, bool flag)
{
    if (flag) {
        CasinoStage::getSingleton()->setObjectDraw(line + 0x1f8, 1, 1);
        CasinoStage::getSingleton()->setObjectDraw(line + 0x1f5, 0, 1);
    } else {
        CasinoStage::getSingleton()->setObjectDraw(line + 0x1f8, 0, 1);
        CasinoStage::getSingleton()->setObjectDraw(line + 0x1f5, 1, 1);
    }
}

THUMB void casino::CasinoSlot::setLampReelOff()
{
    for (int i = 0; i < 20; i++) {
        CasinoStage::getSingleton()->setObjectDraw(i + 0x209, 0, 1);
    }
    setLampOff();
}

THUMB void casino::CasinoSlot::setLampOff()
{
    for (int i = 0; i < 16; i++) {
        CasinoStage::getSingleton()->setObjectDraw(i + 0x1f5, 0, 1);
    }
    for (int i = 0; i < 0x4a; i++) {
        CasinoStage::getSingleton()->setObjectDraw(i + 0x21d, 0, 1);
    }
    for (int i = 0; i < 3; i++) {
        CasinoStage::getSingleton()->setObjectDraw(i + 0x1f5, 1, 1);
    }
    for (int i = 0; i < 0x12; i++) {
        CasinoStage::getSingleton()->setObjectDraw(i + 0x21f, 1, 1);
    }
    CasinoStage::getSingleton()->setObjectDraw(0x201, 1, 1);
    CasinoStage::getSingleton()->setObjectDraw(0x21d, 1, 1);
}

THUMB void casino::CasinoSlot::setLineBingo(int line)
{
    lineBingo[line] = 1;
}

THUMB int casino::CasinoSlot::setBingoAnim(int image, int count)
{
    CasinoStage::getSingleton()->setObjectDraw(0x202, 1, 1);
    int base = image * 3;
    CasinoStage::getSingleton()->setObjectDraw(0x233 - (count - 2) + base, 1, 1);
    CasinoStage::getSingleton()->setObjectDraw(0x221 - (count - 2) + base, 0, 1);
    CasinoStage::getSingleton()->setObjectDraw(0x201, 1, 1);
    return base - (count - 2);
}

THUMB void casino::CasinoSlot::judgeBingoType(int type)
{
    if (bingoType_ < type) {
        bingoType_ = type;
    }
}

THUMB void casino::CasinoSlot::setBigBingoAnim()
{
    for (int i = 0; i < 16; i++) {
        CasinoStage::getSingleton()->setObjectDraw(i + 0x1f5, 0, 1);
    }
    for (int i = 0; i < 0x4a; i++) {
        CasinoStage::getSingleton()->setObjectDraw(i + 0x21d, 0, 1);
    }
    for (int i = 0; i < 3; i++) {
        CasinoStage::getSingleton()->setObjectDraw(i + 0x1f5, 1, 1);
    }
    for (int i = 0; i < 0x12; i++) {
        CasinoStage::getSingleton()->setObjectDraw(i + 0x243, 1, 1);
    }
    CasinoStage::getSingleton()->setObjectDraw(0x202, 1, 1);
    CasinoStage::getSingleton()->setObjectDraw(0x21d, 1, 1);
    CasinoStage::getSingleton()->setObjectDraw(0x204, 1, 1);
    CasinoStage::getSingleton()->stage_.eventAnim(1, 0);
}
