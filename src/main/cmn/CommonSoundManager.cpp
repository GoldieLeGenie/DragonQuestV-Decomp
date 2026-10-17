#include "main/cmn/CommonSoundManager.hpp"
#include "main/sound/SoundManager.hpp"

inline int SoundManager::getBgmIndex()
{
    return bgmIndex_;
}

inline void SoundManager::setInterrupt(int flag)
{
    interrupt_ = flag;
}

namespace cmn {
    CommonSoundManager g_cmnSoundManager;
}

THUMB void cmn::CommonSoundManager::initialize()
{
    soundType_ = 0;
    playSoundNo_ = 0;
    waitSoundTime_ = 0;
    playTime_ = 0;
    preSoundIndex_ = 0;
    soundCount_ = -1;
    isPlaySound_ = 0;
    nextMapMe_ = 0;
    interruptMe_ = 0;
}

THUMB void cmn::CommonSoundManager::setPlaySound(int music, bool flag)
{
    isPlaySound_ = 1;
    interruptMe_ = 1;
    soundType_ = music;
    soundCount_ = 0;
    waitSoundTime_ = 30;
    preSoundIndex_ = SoundManager::getBgmIndex();
    nextMapMe_ = flag;
    switch (soundType_) {
    case 0:
        break;
    case 1:
        playSoundNo_ = 0x2d;
        playTime_ = 200;
        interruptMe_ = 0;
        break;
    case 2:
        playSoundNo_ = 0x24;
        playTime_ = 420;
        break;
    case 3:
        playSoundNo_ = 0x25;
        playTime_ = 480;
        waitSoundTime_ = 30;
        break;
    case 4:
    case 18:
        waitSoundTime_ = 60;
        playSoundNo_ = 0x26;
        playTime_ = 240;
        interruptMe_ = 0;
        break;
    case 5:
        playSoundNo_ = 0x30;
        playTime_ = 2460;
        break;
    case 6:
        playSoundNo_ = 0x31;
        playTime_ = 300;
        interruptMe_ = 0;
        break;
    case 7:
        playSoundNo_ = 0x32;
        playTime_ = 1260;
        interruptMe_ = 0;
        break;
    case 8:
        playSoundNo_ = 0x27;
        playTime_ = 200;
        break;
    case 9:
        playSoundNo_ = 0x28;
        playTime_ = 530;
        break;
    case 10:
        playSoundNo_ = 0x29;
        playTime_ = 1320;
        break;
    case 11:
        playSoundNo_ = 0x2a;
        playTime_ = 180;
        break;
    case 12:
        playSoundNo_ = 0x2b;
        playTime_ = 150;
        break;
    case 13:
        playSoundNo_ = 0x2c;
        playTime_ = 240;
        break;
    case 14:
        playSoundNo_ = 0x2e;
        playTime_ = 120;
        break;
    case 15:
        playSoundNo_ = 0x2f;
        playTime_ = 150;
        break;
    case 16:
        playSoundNo_ = 0x33;
        playTime_ = 1620;
        break;
    case 17:
        playSoundNo_ = 0x34;
        playTime_ = 300;
        break;
    case 19:
        playSoundNo_ = 0x25;
        playTime_ = 480;
        waitSoundTime_ = 0;
        break;
    }
    if (nextMapMe_ == 1) {
        SoundManager::play(playSoundNo_, 5);
    }
}

THUMB void cmn::CommonSoundManager::execSound()
{
    if (soundCount_ == waitSoundTime_) {
        if (nextMapMe_ == 0) {
            if (preSoundIndex_ != 0) {
                SoundManager::setInterrupt(interruptMe_);
            }
            SoundManager::play(playSoundNo_, 5);
        }
        soundCount_++;
    } else if (soundCount_ < playTime_) {
        soundCount_++;
    } else if (soundCount_ == playTime_) {
        if (nextMapMe_ == 1) {
            SoundManager::stopBgm(0);
        }
        soundCount_++;
    } else if (soundCount_ > playTime_) {
        soundCount_ = 0;
        isPlaySound_ = 0;
        if (soundType_ != 4 && soundType_ != 11 && nextMapMe_ == 0 && preSoundIndex_ != 0) {
            SoundManager::play(preSoundIndex_, 5);
        }
    }
}

THUMB void cmn::CommonSoundManager::setFadeOut(int frame)
{
    if (SoundManager::getBgmIndex() != 0) {
        SoundManager::setInterrupt(true);
        SoundManager::setFadeOut(frame);
    }
}
