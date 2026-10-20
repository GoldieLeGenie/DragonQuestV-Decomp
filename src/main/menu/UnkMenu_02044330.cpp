#include "main/menu/UnkMenu_02044330.hpp"
#include "main/debug/DebugInfo.hpp"
#include "main/text/TextAPI.hpp"

THUMB void UnkMenu_02044330::menuSetup()
{
    data_020c2d10.clearMessageIDs();
}

THUMB void UnkMenu_02044330::menuExecute()
{
}

THUMB void UnkMenu_02044330::menuDraw()
{
}

THUMB void UnkMenu_02044330::menuUpdate()
{
    startNextMessage();
}

THUMB void UnkMenu_02044330::startNextMessage()
{
    if (messageId_ != 0) {
        return;
    }
    for (int i = 0; i < 8; i++) {
        if (messageQueue_[i] != 0) {
            messageId_ = messageQueue_[i];
            messageQueue_[i] = 0;
            lineCount_ = TextAPI::splitMessage(messageId_, text_[0], text_[1], text_[2], text_[3], NULL, NULL, NULL, NULL);
            unk_448 = 0;
            unk_44c = 0;
            return;
        }
    }
    stat_ = MENUBASE_STAT_OK;
}
