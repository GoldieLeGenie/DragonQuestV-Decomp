#include "main/object/GameMonster.hpp"

#pragma thumb on

GameMonsterData GameMonster::gameMonsterData_;

GameMonster::GameMonster()
{
    dssaCharacterData_ = NULL;
}

GameMonster::~GameMonster()
{
}

void GameMonster::setup(int index)
{
    index_ = index;
    dssaCharacterData_ = gameMonsterData_.setup(index_);
    UnkTextureObject* texture = (UnkTextureObject*)((DSSACharacterData*)dssaCharacterData_)->textureData_.getAddr();
    DSSACharacter::unkfunc_020524c8(texture, &((DSSACharacterData*)dssaCharacterData_)->animationData_);
}

void GameMonster::cleanup()
{
    DSSACharacter::cleanup();
    gameMonsterData_.cleanup(index_);
    dssaCharacterData_ = NULL;
}

void GameMonster::setupTexture(int monsterIndex)
{
    gameMonsterData_.setupTexture(monsterIndex);
}

void GameMonster::cleanupTexture(int monsterIndex)
{
    gameMonsterData_.cleanupTexture(monsterIndex);
}

void GameMonster::clearGameMonsterData()
{
    gameMonsterData_.clear();
}
