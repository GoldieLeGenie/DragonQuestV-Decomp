#include "ov005/fld/FieldPlayer.hpp"

THUMB fld::FieldPlayer::FieldPlayer()
{
}

THUMB fld::FieldPlayer::~FieldPlayer()
{
}

THUMB void fld::FieldPlayer::setup()
{
    fieldAction_[FIELD_ACTION_WALK] = &fieldActionWalk_;
    fieldAction_[FIELD_ACTION_SHIP] = &fieldActionShip_;
    fieldAction_[FIELD_ACTION_RURA] = &fieldActionRura_;
    fieldAction_[FIELD_ACTION_TABI] = &fieldActionTabi_;
    fieldAction_[FIELD_ACTION_CARPET] = &fieldActionCarpet_;
    fieldAction_[FIELD_ACTION_CASTLE] = &fieldActionCastle_;
    fieldAction_[FIELD_ACTION_RANA] = &fieldActionRana_;
    fieldAction_[FIELD_ACTION_DRAGON] = &fieldActionDragon_;
    actionIndex_ = 0;
    for (int i = 0; i < 8; i++) {
        int index = fieldAction_[i]->setup();
        if (index != -1) {
            actionIndex_ = index;
        }
    }
}

THUMB void fld::FieldPlayer::cleanup()
{
}

THUMB void fld::FieldPlayer::execute()
{
    fieldAction_[actionIndex_]->execute();
}

THUMB bool fld::FieldPlayer::update()
{
    int index = fieldAction_[actionIndex_]->update();
    if (index != -1) {
        actionIndex_ = index;
        return true;
    }
    return false;
}

THUMB void fld::FieldPlayer::setMoveType(int type)
{
    actionIndex_ = type;
}

THUMB int fld::FieldPlayer::getMoveType()
{
    return actionIndex_;
}

THUMB void fld::FieldPlayer::execCollision()
{
}

THUMB void fld::FieldPlayer::execMove()
{
}
