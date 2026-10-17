#include "main/sound/SoundManager.hpp"
#include "main/sound/Sound.hpp"
#include "main/sound/UnkSoundPlayer.hpp"
#include "nitro/os.hpp"

int SoundManager::fadeCount_;
int SoundManager::fadeFrame_;
int SoundManager::bgmIndex_;
int SoundManager::se2_;
int SoundManager::finalFormBGM_;
int SoundManager::interrupt_;
int SoundManager::townBgmEnable_ = 1;
int SoundManager::nextIndex_[2];

ARM void SoundManager::initialize(void* file, void* memory, int size, int a, int b, int c, unsigned char* volume)
{
    data_02101584.unkfunc_0205015c(file, memory, size, 1);
    data_021025e0.unkfunc_02054fd0();
    data_021025e0.unkfunc_02055024(a, b);
    data_021025e0.unkfunc_02055024(a, c);
    if (volume != NULL) {
        data_0209af0c = volume;
    }
    bgmIndex_ = 0;
    se2_ = 0;
}

ARM void SoundManager::update()
{
    if (nextIndex_[0] != 0 && Sound::unkfunc_020688d4()) {
        bgmIndex_ = nextIndex_[0];
        if (interrupt_ != 0) {
            Sound::unkfunc_02068868(nextIndex_[0], 1);
            interrupt_ = 0;
        } else {
            Sound::unkfunc_02068868(nextIndex_[0], 0);
        }
        nextIndex_[0] = 0;
        fadeFrame_ = 0;
        fadeCount_ = 0;
        if (nextIndex_[1] != 0) {
            nextIndex_[0] = nextIndex_[1];
            nextIndex_[1] = 0;
        }
    }
    updateFadeOut();
    if (!Sound::unkfunc_020688c4()) {
        bgmIndex_ = 0;
    }
    data_021025e0.unkfunc_0205528c();
}

ARM void SoundManager::updateFadeOut()
{
    if (fadeFrame_ == 0) {
        return;
    }
    fadeCount_++;
    if (fadeFrame_ == fadeCount_) {
        if (interrupt_ != 0) {
            Sound::unkfunc_020688e4(1);
        } else {
            Sound::unkfunc_0206889c(15);
        }
        fadeFrame_ = 0;
        fadeCount_ = 0;
        data_02101584.unkfunc_0205027c();
    }
    setBgmVolume(127 * (fadeFrame_ - fadeCount_) / fadeFrame_);
}

ARM void SoundManager::setFadeOut(int frame)
{
    fadeFrame_ = frame;
    fadeCount_ = 0;
}

ARM void SoundManager::play(int bgm, int fade)
{
    if (bgmIndex_ == bgm) {
        return;
    }
    nextIndex_[0] = bgm;
    setFadeOut(fade);
}

ARM void SoundManager::stop(int fade)
{
    Sound::unkfunc_0206889c(fade);
}

ARM void SoundManager::playRestart(int bgm, int fade)
{
    if (bgmIndex_ != 0) {
        nextIndex_[0] = bgm;
        nextIndex_[1] = bgmIndex_;
        setFadeOut(fade);
        interrupt_ = 1;
    } else {
        bgmIndex_ = bgm;
        Sound::unkfunc_02068868(bgm, 0);
    }
}

ARM void SoundManager::townPlay(int bgm)
{
    if (townBgmEnable_ != 0 && bgm != 0) {
        play(bgm, 5);
    }
    townBgmEnable_ = 1;
    for (int i = 0; i < 15; i++) {
        update();
        data_02101584.unkfunc_0205027c();
        OS_Wait();
    }
}

ARM void SoundManager::setTownPlayDisable()
{
    townBgmEnable_ = 0;
}

ARM void SoundManager::fieldPlay(int bgm)
{
    if (townBgmEnable_ != 0) {
        play(bgm, 5);
    }
    townBgmEnable_ = 1;
    for (int i = 0; i < 15; i++) {
        update();
        data_02101584.unkfunc_0205027c();
        OS_Wait();
    }
}

ARM void SoundManager::battlePlay(int bgm)
{
    if (bgmIndex_ == bgm) {
        return;
    }
    interrupt_ = 1;
    play(bgm, 5);
}

ARM void SoundManager::battleStop()
{
    stop(15);
}

ARM void SoundManager::playBgm(int bgm, int fade)
{
    play(bgm, fade);
}

ARM void SoundManager::stopBgm(int fade)
{
    stop(fade);
}

ARM void SoundManager::stopBgmForce(int fade)
{
    Sound::unkfunc_020688b0(fade);
}

ARM int SoundManager::playSe(int se, int param)
{
    return Sound::sePlay(se);
}

ARM void SoundManager::unkfunc_0206fc10(int se, int fade)
{
    Sound::unkfunc_0206897c(se);
}

ARM void SoundManager::stopSeWithIndex(int se, int fade)
{
    Sound::unkfunc_02068990(se, fade);
}

ARM void SoundManager::playSe2(int se, int param)
{
    Sound::sePlay2(se);
    se2_ = se;
}

ARM void SoundManager::unkfunc_0206fc44(int fade)
{
    Sound::unkfunc_02068968(fade);
    se2_ = 0;
}

ARM void SoundManager::setBgmVolumeSys(int volume)
{
    Sound::setBgmVolumeSys(volume);
}

ARM void SoundManager::setBgmVolume(int volume)
{
    Sound::setBgmVolume(volume);
}

ARM void SoundManager::setSeVolumeSys(int volume)
{
    Sound::setSeVolumeSys(volume);
}
