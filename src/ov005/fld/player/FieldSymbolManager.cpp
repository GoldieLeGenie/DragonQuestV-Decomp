#include "ov005/fld/FieldSymbolManager.hpp"
#include "main/leveldata/FieldSymbol.hpp"
#include "main/menu/UiMsg.hpp"
#include "main/status/StoryStatus.hpp"
#include "ov005/fld/FieldWindowSystem.hpp"

inline dq5::level::FieldSymbol* dq5::level::FieldSymbol::getRecord(int index)
{
    return (FieldSymbol*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned short dq5::level::FieldSymbol::getUid()
{
    return uid;
}

inline dq5::CHAPTER_NO status::StoryStatus::getChapter()
{
    return chapter_;
}

THUMB fld::FieldSymbolManager::FieldSymbolManager()
{
}

THUMB fld::FieldSymbolManager::~FieldSymbolManager()
{
}

THUMB fld::FieldSymbolManager& fld::FieldSymbolManager::getSingleton()
{
    static FieldSymbolManager instance;
    return instance;
}

THUMB void fld::FieldSymbolManager::initialize()
{
    resetFlag_ = 1;
    walkX_ = 0;
    walkX_ = 0;
}

THUMB void fld::FieldSymbolManager::terminate()
{
}

THUMB bool fld::FieldSymbolManager::checkSymbol(int index, int flag)
{
    index_ = -1;
    for (int i = 0; i < 0x80; i++) {
        if (index == dq5::level::FieldSymbol::getRecord(i)->getUid()) {
            index_ = i;
            break;
        }
    }
    if (index_ < 0) {
        return false;
    }
    if (dq5::level::FieldSymbol::getRecord(index_)->type != 9) {
        return false;
    }
    ui_MsgSndSet(0x30);
    FieldWindowSystem::getSingleton()->openCommonMessage();
    if (flag == true) {
        FieldWindowSystem::getSingleton()->addCommonMessage(0xc4c7d);
        FieldWindowSystem::getSingleton()->addCommonMessage(0xc4c7e);
    } else if (status::g_Story.getChapter() == dq5::CHAPTER_YOUNENKI) {
        FieldWindowSystem::getSingleton()->addCommonMessage(0xc4c7b);
    } else {
        FieldWindowSystem::getSingleton()->addCommonMessage(dq5::level::FieldSymbol::getRecord(index_)->message);
    }
    return true;
}
