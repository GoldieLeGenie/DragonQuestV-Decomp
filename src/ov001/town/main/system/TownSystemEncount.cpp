#include "ov001/town/TownSystem.hpp"
#include "main/btl/Encount.hpp"
#include "main/global/Global.hpp"
#include "main/status/StageInfo.hpp"
#include "main/status/StoryStatus.hpp"

#pragma thumb on

inline dq5::CHAPTER_NO status::StoryStatus::getChapter()
{
    return chapter_;
}

inline int Global::getMapNameId()
{
    return nextMapNameId;
}

twn::TownSystemEncount::TownSystemEncount()
{
}

twn::TownSystemEncount::~TownSystemEncount()
{
}

void twn::TownSystemEncount::initialize()
{
    btl::Encount::getSingleton()->setupDungeon(status::g_Story.getChapter(), status::g_StageInfo.getTimeZone(), g_Global.getMapNameId());
}

void twn::TownSystemEncount::terminate()
{
}

void twn::TownSystemEncount::execute()
{
}

void twn::TownSystemEncount::draw()
{
}
