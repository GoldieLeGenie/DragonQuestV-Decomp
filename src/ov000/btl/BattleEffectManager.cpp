#include "ov000/btl/BattleEffectManager.hpp"
#include "ov000/btl/BattleCamera.hpp"
#include "main/leveldata/EffectParam.hpp"
#include "main/object/DSSAObject.hpp"
#include "main/object/ModelObject.hpp"
#include "main/status/PlayerStatus.hpp"

inline status::HaveEquipment& status::HaveStatusInfo::getHaveEquipment() { return haveEquipment_; }
inline unsigned int ExcelBinaryData::getRecordCount() { return record_; }
inline dq5::level::EffectParam* dq5::level::EffectParam::getRecord(int index) { return (EffectParam*)binary_.getRecord(index, addr_, filename_, loadSwitch_); }
inline unsigned int dq5::level::EffectParam::getArraySize() { return binary_.getRecordCount(); }
inline unsigned short dq5::level::EffectParam::getIndex() { return index; }

THUMB btl::BattleEffectManager::BattleEffectManager()
{
}

THUMB btl::BattleEffectManager::~BattleEffectManager()
{
}

THUMB btl::BattleEffectManager* btl::BattleEffectManager::getSingleton()
{
    static BattleEffectManager battleEffectManager;
    return &battleEffectManager;
}

THUMB void btl::BattleEffectManager::initialize()
{
    storage_.initialize();
    resource_.initialize();
    setCameraPos();
    BattleEffectUnit::setControlData(&storage_, &resource_);
    for (int i = 0; i < MAX_REPRODUCT; i++) {
        unit_[i].initialize();
    }
    wait_ = 0;
}

THUMB void btl::BattleEffectManager::terminate()
{
    for (int i = 0; i < MAX_REPRODUCT; i++) {
        unit_[i].terminate();
    }
    storage_.terminate();
    resource_.terminate();
}

THUMB void btl::BattleEffectManager::execute()
{
    for (int i = 0; i < MAX_REPRODUCT; i++) {
        unit_[i].execute();
    }
    if (wait_ > 0) {
        wait_--;
    }
}

THUMB void btl::BattleEffectManager::extraDraw()
{
    DSSAObject::calcType_ = 1;
    for (int i = 0; i < MAX_REPRODUCT; i++) {
        unit_[i].extraDraw();
    }
    DSSAObject::calcType_ = 0;
}

THUMB void btl::BattleEffectManager::draw()
{
    DSSAObject::calcType_ = 1;
    for (int i = 0; i < MAX_REPRODUCT; i++) {
        unit_[i].draw();
    }
    DSSAObject::calcType_ = 0;
}

THUMB void btl::BattleEffectManager::setCameraPos()
{
    ModelObjectWithCamera::camera_ = BattleCamera::getSingleton()->getCamera();
}

THUMB int btl::BattleEffectManager::isEnd()
{
    for (int i = 0; i < MAX_REPRODUCT; i++) {
        if (unit_[i].isEnable()) {
            return false;
        }
    }
    return true;
}

THUMB bool btl::BattleEffectManager::isAllEnd()
{
    return storage_.effectCounter_ == 0;
}

THUMB int btl::BattleEffectManager::getWeaponEffectID(status::PlayerStatus* playerStatus)
{
    int weaponID = playerStatus->haveStatusInfo_.getHaveEquipment().getEquipment(ITEM_WEAPON, 0);
    if (weaponID == 0) {
        weaponID = 0x42;
    }
    if (weaponID == 0x102) {
        return 0x170;
    }
    if (weaponID == 0x103) {
        return 0x171;
    }
    return weaponID + 0x12c;
}

THUMB int btl::BattleEffectManager::getEffectParam(int effectID)
{
    for (int i = 0; i < dq5::level::EffectParam::getArraySize(); i++) {
        if (effectID == dq5::level::EffectParam::getRecord(i)->getIndex()) {
            return i;
        }
    }
    return 0;
}

THUMB int btl::BattleEffectManager::setupEffect(int effectID)
{
    setCameraPos();
    int index;
    BattleEffectUnit* ctrl = 0;
    for (int i = 0; i < MAX_REPRODUCT; i++) {
        if (!unit_[i].isEnable()) {
            index = i;
            ctrl = &unit_[i];
            break;
        }
    }
    ctrl->setup(getEffectParam(effectID));
    if (!ctrl->isEnable()) {
        index = -1;
    }
    return index;
}

THUMB bool btl::BattleEffectManager::isEndWait()
{
    return wait_ == 0;
}
