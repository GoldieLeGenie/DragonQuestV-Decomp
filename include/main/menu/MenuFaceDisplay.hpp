#pragma once
#include <globaldefs.h>
#include "main/menu/MenuDisplay.hpp"

// 48x48 face icon (face48.mpt) or loading animation (loading48.mpt) drawn as 32x32 sprites (data_02114dd4.face_)
struct MenuFaceDisplay : MenuDisplay {
    int priority_;                              // 0x30
    int mode_;                                  // 0x34  1: whole icon, 2-10: one part, 11: loading animation
    int animFrame_;                             // 0x38

    MenuFaceDisplay();
    virtual void setup(int id);
    virtual void update(UnkOamBuffer* main, UnkOamBuffer* sub);
    virtual void execute(UnkOamBuffer* main, UnkOamBuffer* sub);
    virtual void draw(UnkOamBuffer* main, UnkOamBuffer* sub);
    void unkfunc_02064bc8(UnkOamBuffer* oam, int x, int y, int mode);
    void setPriority(int priority);
    void loadFace(int index);           // face icon
    void unkfunc_02064c80();                    // loading animation
    void unkfunc_0204f568();
    void loadIcon(int type, int index);
};
