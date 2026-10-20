#include "main/cmn/CommonChapterTitle.hpp"

THUMB cmn::CommonChapterTitle& cmn::CommonChapterTitle::getSingleton()
{
    static CommonChapterTitle instance;
    return instance;
}

THUMB cmn::CommonChapterTitle::CommonChapterTitle()
{
}

THUMB cmn::CommonChapterTitle::~CommonChapterTitle()
{
}

THUMB void cmn::CommonChapterTitle::cleanup()
{
    if (sprite_.isLoaded()) {
        sprite_.unload();
    }
}

THUMB void cmn::CommonChapterTitle::draw()
{
    if (sprite_.isLoaded()) {
        sprite_.draw();
    }
}
