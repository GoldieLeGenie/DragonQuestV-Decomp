#include "ov001/town/TownFurnitureControl.hpp"

THUMB twn::TownFurnitureControlStorage::TownFurnitureControlStorage()
{
}

THUMB twn::TownFurnitureControlStorage::~TownFurnitureControlStorage()
{
}

THUMB void twn::TownFurnitureControlStorage::initialize()
{
    moveCounter_ = 0;
    fadeCounter_ = 0;
    moveCounter2_ = 0;
    rotateCounter_ = 0;
    groupMoveCounter_ = 0;
    groupRotateCounter_ = 0;
    for (unsigned int i = 0; i < FURNITURE_MOVE_MAX; i++) {
        move_[i].enable_ = false;
    }
    for (unsigned int i = 0; i < FURNITURE_FADE_MAX; i++) {
        fade_[i].enable_ = false;
    }
    for (unsigned int i = 0; i < FURNITURE_MOVE2_MAX; i++) {
        move2_[i].enable_ = false;
    }
    for (unsigned int i = 0; i < FURNITURE_ROTATE_MAX; i++) {
        rotate_[i].enable_ = false;
    }
    for (unsigned int i = 0; i < FURNITURE_GROUP_MOVE_MAX; i++) {
        groupMove_[i].enable_ = false;
    }
    for (unsigned int i = 0; i < FURNITURE_GROUP_ROTATE_MAX; i++) {
        groupRotate_[i].enable_ = false;
    }
}

THUMB void twn::TownFurnitureControlStorage::terminate()
{
}

THUMB twn::TownFurnitureControlBase* twn::TownFurnitureControlStorage::getContainer(int type)
{
    switch (type) {
    case 0:
        moveCounter_++;
        for (unsigned int i = 0; i < FURNITURE_MOVE_MAX; i++) {
            if (!move_[i].enable_) {
                return &move_[i];
            }
        }
        break;
    case 1:
        moveCounter2_++;
        for (unsigned int i = 0; i < FURNITURE_MOVE2_MAX; i++) {
            if (!move2_[i].enable_) {
                return &move2_[i];
            }
        }
        break;
    case 2:
        fadeCounter_++;
        for (unsigned int i = 0; i < FURNITURE_FADE_MAX; i++) {
            if (!fade_[i].enable_) {
                return &fade_[i];
            }
        }
        break;
    case 3:
        rotateCounter_++;
        for (unsigned int i = 0; i < FURNITURE_ROTATE_MAX; i++) {
            if (!rotate_[i].enable_) {
                return &rotate_[i];
            }
        }
        break;
    case 4:
        groupMoveCounter_++;
        for (unsigned int i = 0; i < FURNITURE_GROUP_MOVE_MAX; i++) {
            if (!groupMove_[i].enable_) {
                return &groupMove_[i];
            }
        }
        break;
    case 5:
        groupRotateCounter_++;
        for (unsigned int i = 0; i < FURNITURE_GROUP_ROTATE_MAX; i++) {
            if (!groupRotate_[i].enable_) {
                return &groupRotate_[i];
            }
        }
        break;
    }
    return NULL;
}

THUMB void twn::TownFurnitureControlStorage::restoreContainer(int type)
{
    switch (type) {
    case 0:
        moveCounter_--;
        break;
    case 1:
        moveCounter2_--;
        break;
    case 2:
        fadeCounter_--;
        break;
    case 3:
        rotateCounter_--;
        break;
    case 4:
        groupMoveCounter_--;
        break;
    case 5:
        groupRotateCounter_--;
        break;
    }
}
