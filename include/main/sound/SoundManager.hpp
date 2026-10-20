#pragma once
#include <globaldefs.h>

struct SoundManager {
    static void initialize(void* file, void* memory, int size, int a, int b, int c, unsigned char* volume);
    static void update();
    static void updateFadeOut();
    static void setFadeOut(int frame);
    static void play(int bgm, int fade);
    static void stop(int fade);
    static void playRestart(int bgm, int fade);
    static void townPlay(int bgm);
    static void setTownPlayDisable();
    static void fieldPlay(int bgm);
    static void battlePlay(int bgm);
    static void battleStop();
    static void playBgm(int bgm, int fade);
    static void stopBgm(int fade);
    static void stopBgmForce(int fade);
    static int playSe(int se, int param);
    static void stopSe(int se, int fade);
    static void stopSeWithIndex(int se, int fade);
    static void playSe2(int se, int param);
    static void stopSe2(int fade);
    static void setBgmVolumeSys(int volume);
    static void setBgmVolume(int volume);
    static void setSeVolumeSys(int volume);
    static int getBgmIndex();
    static void setInterrupt(int flag);

    static int interrupt_;
    static int finalFormBGM_;
    static int se2_;
    static int bgmIndex_;
    static int fadeFrame_;
    static int fadeCount_;
    static int nextIndex_[2];
    static int townBgmEnable_;
};
