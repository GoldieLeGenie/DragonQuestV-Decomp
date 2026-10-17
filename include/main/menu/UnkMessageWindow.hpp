#pragma once
#include <globaldefs.h>
#include "main/menu/UnkMenuDisplay.hpp"
#include "main/text/TextAPI.hpp"

struct UnkMenuTextDisplay;
struct UnkMenuWindowFrame;

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
    int unk_24;                                 // 0x24
    int intervalCursor_;                        // 0x28
    int lastCursor_;                            // 0x2C
    int font_;                                  // 0x30
    int fontHeight_;                            // 0x34
    int lineSpace_;                             // 0x38
    int scrollSpeed_;                           // 0x3C
    int frameType_;                             // 0x40
    int printSpeed_;                            // 0x44
    int wait_;                                  // 0x48
    int unk_4c;                                 // 0x4C
    int sound_;                                 // 0x50
    int unk_54;                                 // 0x54
};

// Message window drawn on the sub screen (data_02114dd4.message_)
struct UnkMessageWindow : UnkMenuDisplay {
    int windowType_;                            // 0x030
    UnkMessageWindowConfig* config_;               // 0x034
    int unk_038;                                // 0x038
    int lineCount_;                             // 0x03C
    int lineHeight_;                            // 0x040
    int scrollSpeed_;                           // 0x044
    int width_;                                 // 0x048
    int height_;                                // 0x04C
    UnkMenuWindowFrame* frame_;                 // 0x050
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
    int unk_9c4;                                // 0x9C4
    int wait_;                                  // 0x9C8
    int unk_9cc;                                // 0x9CC
    int unk_9d0;                                // 0x9D0
    int unk_9d4;                                // 0x9D4
    int shake_;                                 // 0x9D8
    int shakeCount_;                            // 0x9DC
    int shakeRepeat_;                           // 0x9E0
    int shakeX_;                                // 0x9E4
    int shakeY_;                                // 0x9E8
    int unk_9ec;                                // 0x9EC
    int unk_9f0;                                // 0x9F0
    int unk_9f4;                                // 0x9F4
    int sound_;                                 // 0x9F8
    int soundTimer_;                            // 0x9FC
    int soundSpeed_;                            // 0xA00
    int nameIndex_;                             // 0xA04
    int nameCount_;                             // 0xA08
    char names_[32][0x80];                      // 0xA0C

    UnkMessageWindow();
    virtual void setup(int id);
    virtual void update(UnkOamBuffer* main, UnkOamBuffer* sub);
    virtual void execute(UnkOamBuffer* main, UnkOamBuffer* sub);
    virtual void draw(UnkOamBuffer* main, UnkOamBuffer* sub);
    void unkfunc_02065e0c(const char* name);
    void unkfunc_02065e30(const char* text);
    void unkfunc_02065e40(const char* text);
    void unkfunc_02065fe0(int type);
    void unkfunc_02066028();
    void unkfunc_020661cc();
    void unkfunc_02066288();
    void unkfunc_020662dc();
    void unkfunc_020662e0();
    void unkfunc_0206653c();
    void unkfunc_0206662c();
    void unkfunc_0206668c();
    void unkfunc_02066788();
    void unkfunc_020667ac();
    void unkfunc_02066834();
    UnkMenuTextDisplay* unkfunc_02066864();
    UnkMenuTextDisplay* unkfunc_020668ac();
    UnkMenuTextDisplay* unkfunc_020668b0();
    void unkfunc_020668d4();
    int unkfunc_02066918(int c);
    int unkfunc_02066924(int c);
    int unkfunc_02066938(int c);
    void unkfunc_02066968(UnkTextIterator* it);
    void unkfunc_020669a0(int type, const char* name, const char* text);
    void unkfunc_020669c4(const char* text);
    void unkfunc_020669e0();
    void unkfunc_020669f0();
    void unkfunc_02066a00(int code);
    void unkfunc_02066a7c();
    void unkfunc_02066aa4(const char* name);
    void unkfunc_02066ad0();
    const char* unkfunc_02066b1c();
    void unkfunc_02066b48();
    int unkfunc_02066b74();
    int unkfunc_02066b88();
    int unkfunc_02066b9c();
    bool unkfunc_02066bb0();
    void unkfunc_02066bc4();
    void unkfunc_02066bd4();
    void unkfunc_02066be8(int flag);

    UnkTextIterator* getIterator();
};

extern int data_0209aaf0[8];             // shake offsets x
extern int data_0209ab10[8];             // shake offsets y
