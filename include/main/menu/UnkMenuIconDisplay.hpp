#pragma once
#include <globaldefs.h>
#include "main/menu/UnkMenuDisplay.hpp"
#include "main/menu/UnkMenuIconData.hpp"

struct UnkHoppingDigit {
    int frame_;                                 // 0x00  -99: free, < 0: waiting
    int number_;                                // 0x04
    int x_;                                     // 0x08
    int y_;                                     // 0x0C
    int drawY_;                                 // 0x10

    void unkfunc_020658c8();
    void unkfunc_020658d0(int x, int y, int number, int delay);
    void unkfunc_020658ec(UnkOamBuffer* oam);
    void unkfunc_02065920(UnkOamBuffer* oam);
    int unkfunc_020659bc();
};


struct UnkHoppingNumber : UnkMenuDisplay {
    UnkHoppingDigit digit_[40];                 // 0x30

    UnkHoppingNumber();
    virtual void setup(int id);
    virtual void update(UnkOamBuffer* main, UnkOamBuffer* sub);
    virtual void execute(UnkOamBuffer* main, UnkOamBuffer* sub);
    virtual void draw(UnkOamBuffer* main, UnkOamBuffer* sub);
    UnkHoppingDigit* unkfunc_02065a58();
    void unkfunc_02065a84(int x, int y, int value, int delay);
};

// Four 48x48 icons on the main screen 
struct UnkMenuIconDisplay : UnkMenuDisplay {
    int posX_[4];                               // 0x30
    int posY_[4];                               // 0x40
    int value_[4];                              // 0x50
    int flag_[4];                               // 0x60

    UnkMenuIconDisplay();
    virtual void setup(int id);
    virtual void update(UnkOamBuffer* main, UnkOamBuffer* sub);
    virtual void execute(UnkOamBuffer* main, UnkOamBuffer* sub);
    virtual void draw(UnkOamBuffer* main, UnkOamBuffer* sub);
    void unkfunc_02064ddc(UnkOamBuffer* oam, int x, int y, int index);
    void unkfunc_02064ed8(int index, int value);
    void unkfunc_02065060(int index, int x, int y);
    void unkfunc_0206506c(int index, int flag);
    void unkfunc_02065074(int x, int y, void* src, int srcX, int srcY, int width);
};

