#include "main/sound/UnkSoundPlayer.hpp"

UnkSoundPlayer data_021025e0;

THUMB UnkSoundPlayer::UnkSoundPlayer() : enable_(0)
{
    bgmVolumeSys_ = 0x7f;
    bgmVolume_ = 0x7f;
    seVolumeSys_ = 0x7f;
    seVolume_ = 0x7f;
}

THUMB UnkSoundPlayer::~UnkSoundPlayer()
{
}

THUMB void UnkSoundPlayer::init()
{
    enable_ = 1;
    unk_008.init();
    for (int i = 0; i < 3; i++) {
        bgmHandle_[i].init(-1);
    }
    for (int i = 0; i < 8; i++) {
        seHandle_[i].init(-1);
    }
}

THUMB void UnkSoundPlayer::loadBgm(int bgm, int sub)
{
    if (enable_) {
        data_02101584.loadBgm(bgm, sub);
    }
}

THUMB void UnkSoundPlayer::preload(int a, int b)
{
    if (enable_) {
        data_02101584.preload(a, b);
    }
}

THUMB void UnkSoundPlayer::playBgm(int player, int bgm, int sub)
{
    if (!enable_) {
        return;
    }
    if (isBgmPlaying(bgm)) {
        stopBgm(0, 30);
    }
    bgm_ = bgm;
    bgmHandle_[player].playBgm(bgm, sub);
}

THUMB void UnkSoundPlayer::stopBgm(int player, int fade)
{
    if (enable_) {
        bgmHandle_[player].stopBgm(fade);
    }
}

THUMB void UnkSoundPlayer::stopAllBgm(int player, int fade)
{
    if (enable_) {
        bgmHandle_[player].stopAll(fade);
    }
}

THUMB int UnkSoundPlayer::isBgmPlaying(int player)
{
    return bgmHandle_[player].isBgmPlaying();
}

THUMB int UnkSoundPlayer::isBgmStopped(int player)
{
    return bgmHandle_[player].isBgmStopped();
}

THUMB void UnkSoundPlayer::pauseBgm(int player, int pause)
{
    bgmHandle_[player].setPause(pause);
}

THUMB void UnkSoundPlayer::setBgmVolumeSys(int volume)
{
    bgmVolumeSys_ = volume;
    applyBgmVolume();
}

THUMB void UnkSoundPlayer::setBgmVolume(int volume)
{
    bgmVolume_ = volume;
    applyBgmVolume();
}

THUMB int UnkSoundPlayer::getBgmVolume()
{
    return bgmVolume_;
}

THUMB void UnkSoundPlayer::setSeVolumeSys(int volume)
{
    seVolumeSys_ = volume;
    applySeVolume();
}

THUMB void UnkSoundPlayer::applyBgmVolume()
{
    int volume = bgmVolumeSys_ * bgmVolume_ / 127;
    for (int i = 0; i < 3; i++) {
        bgmHandle_[i].setVolume(volume);
    }
}

THUMB void UnkSoundPlayer::applySeVolume()
{
    int volume = seVolumeSys_ * seVolume_ / 127;
    for (int i = 0; i < 8; i++) {
        seHandle_[i].setVolume(volume);
    }
}

THUMB void UnkSoundPlayer::applySeHandleVolume(int index)
{
    seHandle_[index].setVolume(seVolumeSys_ * seVolume_ / 127);
}

THUMB int UnkSoundPlayer::playSe(int seqArc, int index)
{
    if (!enable_) {
        return -1;
    }
    int ret = 0;
    for (int i = 0; i < 8; i++) {
        if (seHandle_[i].isSe(-1, -1)) {
            ret = i;
            seHandle_[i].playSe(seqArc, index);
            applySeHandleVolume(i);
            break;
        }
    }
    return ret;
}

THUMB void UnkSoundPlayer::stopSeHandle(int index, int fade)
{
    if (enable_) {
        seHandle_[index].stopSe(fade);
    }
}

THUMB void UnkSoundPlayer::stopSe(int seqArc, int index, int fade)
{
    if (!enable_) {
        return;
    }
    for (int i = 0; i < 8; i++) {
        if (seHandle_[i].isSe(seqArc, index)) {
            seHandle_[i].stopSe(fade);
        }
    }
}

THUMB void UnkSoundPlayer::stopAllSe(int fade)
{
    if (!enable_) {
        return;
    }
    for (int i = 0; i < 8; i++) {
        seHandle_[i].stopSe(fade);
    }
}

THUMB void UnkSoundPlayer::playStrm(int no)
{
    if (enable_) {
        unk_008.play(no);
    }
}

THUMB void UnkSoundPlayer::stopStrm(int value)
{
    if (enable_) {
        unk_008.stop(value);
    }
}

THUMB int UnkSoundPlayer::isStrmPlaying()
{
    return unk_008.isPlaying();
}

THUMB void UnkSoundPlayer::updateSe()
{
    for (int i = 0; i < 8; i++) {
        if (seHandle_[i].sePlaying_) {
            seHandle_[i].sePlaying_ = 0;
        } else if (!seHandle_[i].isSePlaying()) {
            seHandle_[i].stopSe(5);
        }
    }
}
