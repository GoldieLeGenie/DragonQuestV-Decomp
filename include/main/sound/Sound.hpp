#pragma once
#include <globaldefs.h>

struct Sound {
    static void unkfunc_02068868(int bgm, int sub);     // play a bgm
    static void unkfunc_0206889c(int fade);             // stop the bgm
    static void unkfunc_020688b0(int fade);
    static int unkfunc_020688c4();                      // bgm playing
    static int unkfunc_020688d4();                      // bgm stopped
    static void unkfunc_020688e4(int pause);            // pause the bgm
    static void unkfunc_020688f8(int no);
    static void unkfunc_02068908(int value);
    static int unkfunc_02068918();
    static int sePlay(int se);
    static int sePlay2(int se);
    static void unkfunc_02068968(int fade);
    static void unkfunc_0206897c(int fade);
    static void unkfunc_02068990(int se, int fade);     // stop a se
    static void unkfunc_020689a4(int fade);             // stop all the se
    static int sePlayDirect(int se);
    static void setBgmVolume(int volume);
    static int getBgmVolume();
    static void setBgmVolumeSys(int volume);
    static void setSeVolumeSys(int volume);
};

extern unsigned char* data_0209af0c;          // bgm volumes
