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
    data_02101584.init(file, memory, size, 1);
    data_021025e0.init();
    data_021025e0.preload(a, b);
    data_021025e0.preload(a, c);
    if (volume != NULL) {
        data_0209af0c = volume;
    }
    bgmIndex_ = 0;
    se2_ = 0;
}

ARM void SoundManager::update()
{
    if (nextIndex_[0] != 0 && Sound::isBgmStopped()) {
        bgmIndex_ = nextIndex_[0];
        if (interrupt_ != 0) {
            Sound::bgmPlay(nextIndex_[0], 1);
            interrupt_ = 0;
        } else {
            Sound::bgmPlay(nextIndex_[0], 0);
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
    if (!Sound::isBgmPlaying()) {
        bgmIndex_ = 0;
    }
    data_021025e0.updateSe();
}

ARM void SoundManager::updateFadeOut()
{
    if (fadeFrame_ == 0) {
        return;
    }
    fadeCount_++;
    if (fadeFrame_ == fadeCount_) {
        if (interrupt_ != 0) {
            Sound::bgmPause(1);
        } else {
            Sound::bgmStop(15);
        }
        fadeFrame_ = 0;
        fadeCount_ = 0;
        data_02101584.update();
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
    Sound::bgmStop(fade);
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
        Sound::bgmPlay(bgm, 0);
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
        data_02101584.update();
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
        data_02101584.update();
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
    Sound::bgmStopAll(fade);
}

ARM int SoundManager::playSe(int se, int param)
{
    return Sound::sePlay(se);
}

ARM void SoundManager::stopSe(int se, int fade)
{
    Sound::seStopFirst(se);
}

ARM void SoundManager::stopSeWithIndex(int se, int fade)
{
    Sound::seStop(se, fade);
}

ARM void SoundManager::playSe2(int se, int param)
{
    Sound::sePlay2(se);
    se2_ = se;
}

ARM void SoundManager::stopSe2(int fade)
{
    Sound::se2Stop(fade);
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
