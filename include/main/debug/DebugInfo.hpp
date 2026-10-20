#pragma once
#include <globaldefs.h>
#include "main/debug/UnkDebugDisplay.hpp"
#include "main/status/GameFlag.hpp"

// Debug info page: position, flags, message IDs, world/play time, heap and dss array warnings
struct DebugInfo : UnkDebugDisplay {
    // vtable                                   // 0x000
    int showPosition_;                          // 0x004
    int showWorldTime_;                         // 0x008
    int showPlayTime_;                          // 0x00C
    int showMessageID_;                         // 0x010
    int showFlag_;                              // 0x014
    int showHeap_;                              // 0x018
    int showArrayWarning_;                      // 0x01C
    int showLog_;                               // 0x020
    int unk_24;                                 // 0x024
    int showMuseum_;                            // 0x028
    int showFriend_;                            // 0x02C
    int areaFlagTop_;                           // 0x030 first flag shown
    int globalFlagTop_;                         // 0x034
    int localFlagTop_;                          // 0x038
    status::GameFlag areaFlag_;                 // 0x03C flags compared with the current ones
    status::GameFlag localFlag_;                // 0x0BC
    status::GameFlag globalFlag_;               // 0x13C
    short dir_;                                 // 0x1BC
    int posX_;                                  // 0x1C0
    int posY_;                                  // 0x1C4
    int posZ_;                                  // 0x1C8
    char dirText_[0x20];                        // 0x1CC
    char posXText_[0x20];                       // 0x1EC
    char posYText_[0x20];                       // 0x20C
    char posZText_[0x20];                       // 0x22C
    int messageID_[16];                         // 0x24C
    int logIndex_;                              // 0x28C
    char log_[24][0x20];                        // 0x290

    DebugInfo();
    virtual void initialize();
    virtual void draw();
    void drawArrayWarnings(int x, int y);        // array warnings
    void drawPosition(int x, int y);        // position, map name, walk count
    void clearMessageIDs();                    // clear the message IDs
    void addMessageID(int messageID);       // add a message ID
    void unkfunc_02027d1c(int x, int y);        // the 16 message IDs
    void drawShortMessageIDs(int x, int y);        // the first 6 message IDs
    void drawFlags(int x, int y);        // area, local and global flags
    void drawFlagTable(int x, int y, char kind, status::GameFlag* flag, int top, int lines, status::GameFlag* prevFlag);
    void drawWorldTime(int x, int y);        // world time
    void drawPlayTime(int x, int y);        // play time
    void drawMuseum(int x, int y);        // museum
    void drawHeap(int x, int y);        // free heap / VRAM
    void drawFriendMonsters(int x, int y);        // friend monsters
    void setShowArrayWarning(int show);            // show the array warnings
    void clearLog();                    // clear the log
    void drawLog(int x, int y);        // log
};

extern DebugInfo data_020c2d10;
