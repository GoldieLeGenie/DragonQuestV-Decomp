#pragma ipa file
#include "ov001/town/character/TownCharacterStorage.hpp"

inline twn::TownCharacterFuniture::TownCharacterFuniture()
{
}

inline twn::TownCharacterFuniture::~TownCharacterFuniture()
{
}

#pragma thumb on

twn::TownCharacterStorage::TownCharacterStorage()
{
}

twn::TownCharacterStorage::~TownCharacterStorage()
{
}

void twn::TownCharacterStorage::initialize()
{
    characterCount_ = 0;
    monsterCount_ = 0;
    modelCount_ = 0;
    motionlessCount_ = 0;
    funitureCount_ = 0;
}

void twn::TownCharacterStorage::terminate()
{
}

twn::TownCharacterBase* twn::TownCharacterStorage::getContainer(int type)
{
    switch (type) {
    case STORAGE_CHARACTER_NORMAL:
        characterCount_++;
        for (int i = 0; i < CHARACTER_MAX; i++) {
            if (normal_[i].data_.enable == false) {
                return &normal_[i];
            }
        }
        break;
    case STORAGE_CHARACTER_SPRITE:
        monsterCount_++;
        for (int i = 0; i < SPRITE_MAX; i++) {
            if (monster_[i].data_.enable == false) {
                return &monster_[i];
            }
        }
        break;
    case STORAGE_CHARACTER_MODEL:
        modelCount_++;
        for (int i = 0; i < MODEL_MAX; i++) {
            if (model_[i].data_.enable == false) {
                return &model_[i];
            }
        }
        break;
    case STORAGE_CHARACTER_MOTIONLESS:
        motionlessCount_++;
        for (int i = 0; i < MOTIONLESS_MAX; i++) {
            if (motionless_[i].data_.enable == false) {
                return &motionless_[i];
            }
        }
        break;
    case STORAGE_CHARACTER_FURNITURE:
        funitureCount_++;
        for (int i = 0; i < FUNITURE_MAX; i++) {
            if (funitureChara_[i].data_.enable == false) {
                return &funitureChara_[i];
            }
        }
        break;
    }
    return NULL;
}

void twn::TownCharacterStorage::restoreContainer(int type)
{
    switch (type) {
    case STORAGE_CHARACTER_NORMAL:
        characterCount_--;
        break;
    case STORAGE_CHARACTER_SPRITE:
        monsterCount_--;
        break;
    case STORAGE_CHARACTER_MODEL:
        modelCount_--;
        break;
    case STORAGE_CHARACTER_MOTIONLESS:
        motionlessCount_--;
        break;
    case STORAGE_CHARACTER_FURNITURE:
        funitureCount_--;
        break;
    }
}
