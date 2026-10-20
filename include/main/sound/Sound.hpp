#pragma once
#include <globaldefs.h>

struct Sound {
    static void bgmPlay(int bgm, int sub);     // play a bgm
    static void bgmStop(int fade);             // stop the bgm
    static void bgmStopAll(int fade);
    static int isBgmPlaying();                      // bgm playing
    static int isBgmStopped();                      // bgm stopped
    static void bgmPause(int pause);            // pause the bgm
    static void strmPlay(int no);
    static void strmStop(int value);
    static int isStrmPlaying();
    static int sePlay(int se);
    static int sePlay2(int se);
    static void se2Stop(int fade);
    static void seStopFirst(int fade);
    static void seStop(int se, int fade);     // stop a se
    static void seStopAll(int fade);             // stop all the se
    static int sePlayDirect(int se);
    static void setBgmVolume(int volume);
    static int getBgmVolume();
    static void setBgmVolumeSys(int volume);
    static void setSeVolumeSys(int volume);
};

extern unsigned char* data_0209af0c;          // bgm volumes
