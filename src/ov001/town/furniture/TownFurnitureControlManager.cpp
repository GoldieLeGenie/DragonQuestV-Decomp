#include "ov001/town/TownFurnitureControl.hpp"
#include "ov001/town/TownStageManager.hpp"

int twn::TownFurnitureControlManager::furnitureCounter_;

THUMB twn::TownFurnitureControlManager::TownFurnitureControlManager()
{
}

THUMB twn::TownFurnitureControlManager::~TownFurnitureControlManager()
{
}

THUMB twn::TownFurnitureControlManager& twn::TownFurnitureControlManager::getSingleton()
{
    static TownFurnitureControlManager m_singleton;
    return m_singleton;
}

THUMB void twn::TownFurnitureControlManager::initialize()
{
    furnitureCounter_ = 0;
    storage_.initialize();
}

THUMB void twn::TownFurnitureControlManager::terminate()
{
    for (int i = 0; i < FURNITURE_CONTOROL_MAX; i++) {
        if (furnControl_[i] != NULL) {
            cleanup(i);
        }
    }
    storage_.terminate();
}

THUMB void twn::TownFurnitureControlManager::execute()
{
    if (furnitureCounter_ != 0) {
        for (int i = 0; i < FURNITURE_CONTOROL_MAX; i++) {
            if (furnControl_[i] != NULL) {
                furnControl_[i]->execute();
                if (isGarbageCorrect(i) && isEnd(i)) {
                    cleanup(i);
                }
            }
        }
    }
}

THUMB bool twn::TownFurnitureControlManager::isEnd(int index)
{
    return furnControl_[index]->isEnd();
}

THUMB int twn::TownFurnitureControlManager::setFurnitureMove(int uid, int frame, dss::Fix32Vector3& goal)
{
    dss::Fix32Vector3 start = TownStageManager::getSingleton()->getRiseupPos(uid, 0);
    for (int i = 0; i < FURNITURE_CONTOROL_MAX; i++) {
        if (furnControl_[i] == NULL) {
            furnControl_[i] = storage_.getContainer(0);
            furnControl_[i]->setFurnitureMove(uid, frame, start, goal);
            furnitureCounter_++;
            return i;
        }
    }
    return 0;
}

THUMB int twn::TownFurnitureControlManager::setFurnitureFade(int uid, int frame, int fade, int priority)
{
    for (int i = 0; i < FURNITURE_CONTOROL_MAX; i++) {
        if (furnControl_[i] == NULL) {
            furnControl_[i] = storage_.getContainer(2);
            furnControl_[i]->setFurnitureFade(uid, frame, fade, priority);
            furnitureCounter_++;
            return i;
        }
    }
    return 0;
}

THUMB int twn::TownFurnitureControlManager::setFurnitureRotate(int uid, int frame, dss::Fix32Vector3& goal)
{
    dss::Fix32Vector3 start = TownStageManager::getSingleton()->getMapUidRot(uid);
    for (int i = 0; i < FURNITURE_CONTOROL_MAX; i++) {
        if (furnControl_[i] == NULL) {
            furnControl_[i] = storage_.getContainer(3);
            furnControl_[i]->setFurnitureRotate(uid, frame, start, goal);
            furnitureCounter_++;
            return i;
        }
    }
    return 0;
}

THUMB int twn::TownFurnitureControlManager::setFurnitureGroupMove(int group, int frame, dss::Fix32Vector3& speed)
{
    for (int i = 0; i < FURNITURE_CONTOROL_MAX; i++) {
        if (furnControl_[i] == NULL) {
            int bit = 0;
            switch (group) {
            case 1:
                bit = 0x100;
                break;
            case 2:
                bit = 0x200;
                break;
            case 3:
                bit = 0x400;
                break;
            case 4:
                bit = 0x800;
                break;
            case 5:
                bit = 0x1000;
                break;
            case 6:
                bit = 0x2000;
                break;
            case 7:
                bit = 0x4000;
                break;
            case 8:
                bit = 0x8000;
                break;
            }
            furnControl_[i] = storage_.getContainer(4);
            furnControl_[i]->setFurnitureGroupMove(bit, frame, speed);
            furnitureCounter_++;
            return i;
        }
    }
    return 0;
}

THUMB int twn::TownFurnitureControlManager::setFurnitureGroupRotate(int group, int frame, dss::Fix32Vector3& speed)
{
    for (int i = 0; i < FURNITURE_CONTOROL_MAX; i++) {
        if (furnControl_[i] == NULL) {
            int bit = 0;
            switch (group) {
            case 1:
                bit = 0x100;
                break;
            case 2:
                bit = 0x200;
                break;
            case 3:
                bit = 0x400;
                break;
            case 4:
                bit = 0x800;
                break;
            case 5:
                bit = 0x1000;
                break;
            case 6:
                bit = 0x2000;
                break;
            case 7:
                bit = 0x4000;
                break;
            case 8:
                bit = 0x8000;
                break;
            }
            furnControl_[i] = storage_.getContainer(5);
            furnControl_[i]->setFurnitureGroupRotate(bit, frame, speed);
            furnitureCounter_++;
            return i;
        }
    }
    return 0;
}

THUMB void twn::TownFurnitureControlManager::cleanup(int index)
{
    furnControl_[index]->cleanup();
    storage_.restoreContainer(furnControl_[index]->getType());
    furnControl_[index] = NULL;
    furnitureCounter_--;
}

THUMB void twn::TownFurnitureControlManager::setGarbageCorrect(int index, bool flag)
{
    furnControl_[index]->setGarbageCorrect(flag);
}

THUMB bool twn::TownFurnitureControlManager::isGarbageCorrect(int index)
{
    return furnControl_[index]->isGarbageCorrect();
}
