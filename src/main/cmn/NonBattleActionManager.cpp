#include "main/cmn/NonBattleActionManager.hpp"
#include "main/cmn/CommonParticleEmitter.hpp"
#include "main/global/UnkGlobalSystem.hpp"
#include "main/object/BillboardCharacter.hpp"
#include "main/object/SpriteCharacter.hpp"
#include "ov001/town/TownStageManager.hpp"
#include "ov005/fld/FieldStage.hpp"

THUMB cmn::NonBattleActionManager* cmn::NonBattleActionManager::getSingleton()
{
    static NonBattleActionManager nonBattleActionManager;
    return &nonBattleActionManager;
}

THUMB void cmn::NonBattleActionManager::execute()
{
}

THUMB void cmn::NonBattleActionManager::setAction(ACTION_EFFECT action)
{
    waitTurn_ = 0;
    if (data_02101c88.unkfunc_02051818(4)) {
        twn::TownStageManager::getSingleton()->pause(1);
        BillboardCharacter::setAllCharaAnim(false);
    } else if (data_02101c88.unkfunc_02051818(6)) {
        fld::FieldStage::getSingleton()->fieldData.pause_ = 1;
        cmn::CommonParticleEmitter::getSingleton()->stop_ = 1;
        SpriteCharacter::setAllCharaAnim(false);
    }
    status_ = action;
    startFlag_ = 0;
}
