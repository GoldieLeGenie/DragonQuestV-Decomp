#include "ov005/fld/FieldRectColl.hpp"

THUMB void fld::FieldRectCollManager::setup()
{
    rectCollCount_ = 0;
    for (int i = 0; i < 5; i++) {
        rectColl_[i].type = 0;
    }
}

THUMB fld::FieldRectCollManager& fld::FieldRectCollManager::getSingleton()
{
    static FieldRectCollManager instance;
    return instance;
}
