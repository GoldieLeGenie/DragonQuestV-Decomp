#pragma once
#include <globaldefs.h>
#include "main/menu/MenuDisplay.hpp"
#include "main/text/TextAPI.hpp"

struct UnkMenuTextDisplay;
struct MenuWindowFrame;

// Message window layout, one per eMessageWindow type
struct UnkMessageWindowConfig {
    int type_;                                  // 0x00
    int x_;                                     // 0x04
    int y_;                                     // 0x08
    int width_;                                 // 0x0C
    int height_;                                // 0x10
    int margin_;                                // 0x14
    int nameX_;                                 // 0x18
    int nameY_;                                 // 0x1C
    int lineCount_;                             // 0x20
    int extraHeight_;                                 // 0x24
    int intervalCursor_;                        // 0x28
    int lastCursor_;                            // 0x2C
    int font_;                                  // 0x30
    int fontHeight_;                            // 0x34
    int lineSpace_;                             // 0x38
    int scrollSpeed_;                           // 0x3C
    int frameType_;                             // 0x40
    int printSpeed_;                            // 0x44
    int wait_;                                  // 0x48
    int waitProgFrames_;                                 // 0x4C
    int sound_;                                 // 0x50
    int centerText_;                                 // 0x54
};

// Message window drawn on the sub screen (data_02114dd4.message_)
struct MessageWindow : MenuDisplay {
    int windowType_;                            // 0x030
    UnkMessageWindowConfig* config_;               // 0x034
    int centerText_;                                // 0x038
    int lineCount_;                             // 0x03C
    int lineHeight_;                            // 0x040
    int scrollSpeed_;                           // 0x044
    int width_;                                 // 0x048
    int height_;                                // 0x04C
    MenuWindowFrame* frame_;                 // 0x050
    UnkMenuTextDisplay* namePlate_;             // 0x054
    UnkMenuTextDisplay* lines_[4];              // 0x058
    UnkMenuTextDisplay* freeLines_[4];          // 0x068
    char name_[0x104];                          // 0x078
    char text_[0x800];                          // 0x17C
    int unk_97c;                                // 0x97C
    UnkUtf8Iterator iterator_;                     // 0x980
    int state_;                                 // 0x9A4
    UnkMenuTextDisplay* waitLine_;              // 0x9A8
    int intervalCursor_;                        // 0x9AC
    int lastCursor_;                            // 0x9B0
    int cursor_;                                // 0x9B4
    int scroll_;                                // 0x9B8
    int keyWait_;                               // 0x9BC
    int keySound_;                              // 0x9C0
    int keyTimer_;                                // 0x9C4
    int wait_;                                  // 0x9C8
    int waitProgFlag_;                                // 0x9CC
    int waitProg_;                                // 0x9D0
    int shakeRequest_;                                // 0x9D4
    int shake_;                                 // 0x9D8
    int shakeCount_;                            // 0x9DC
    int shakeRepeat_;                           // 0x9E0
    int shakeX_;                                // 0x9E4
    int shakeY_;                                // 0x9E8
    int printDelayRequest_;                                // 0x9EC
    int printDelayCount_;                                // 0x9F0
    int printDelay_;                                // 0x9F4
    int sound_;                                 // 0x9F8
    int soundTimer_;                            // 0x9FC
    int soundSpeed_;                            // 0xA00
    int nameIndex_;                             // 0xA04
    int nameCount_;                             // 0xA08
    char names_[32][0x80];                      // 0xA0C

    MessageWindow();
    virtual void setup(int id);
    virtual void update(UnkOamBuffer* main, UnkOamBuffer* sub);
    virtual void execute(UnkOamBuffer* main, UnkOamBuffer* sub);
    virtual void draw(UnkOamBuffer* main, UnkOamBuffer* sub);
    void setName(const char* name);
    void setText(const char* text);
    void appendText(const char* text);
    void setWindowType(int type);
    void startWindow();
    void updateNameFrame();
    void executeState();
    void stateIdle();
    void stateNextLine();
    void statePrint();
    void stateScroll();
    void stateWaitKey();
    void stateWaitProg();
    void stateFinish();
    void initLines();
    UnkMenuTextDisplay* allocLine();
    UnkMenuTextDisplay* getFirstLine();
    UnkMenuTextDisplay* getLastLine();
    void releaseFirstLine();
    int isEndChar(int c);
    int isNewlineChar(int c);
    int isControlCode(int c);
    void skipNewlines(UnkTextIterator* it);
    void openWindow(int type, const char* name, const char* text);
    void addText(const char* text);
    void addWaitKey();
    void addWaitProg();
    void addControlCode(int code);
    void clearNames();
    void addName(const char* name);
    void nextName();
    const char* getCurrentName();
    void restart();
    int isWaitTrigger();
    int isFinish();
    int isEnd();
    bool isWaitProg();
    void clearWaitTriggerSE();
    void clearWaitTriggerNoSE();
    void setWaitProg(int flag);

    UnkTextIterator* getIterator();
};

extern int data_0209aaf0[8];             // shake offsets x
extern int data_0209ab10[8];             // shake offsets y
