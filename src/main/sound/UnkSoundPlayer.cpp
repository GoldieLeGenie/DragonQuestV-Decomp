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

THUMB void UnkSoundPlayer::unkfunc_02054fd0()
{
    enable_ = 1;
    unk_008.unkfunc_02050438();
    for (int i = 0; i < 3; i++) {
        bgmHandle_[i].unkfunc_0204fde0(-1);
    }
    for (int i = 0; i < 8; i++) {
        seHandle_[i].unkfunc_0204fde0(-1);
    }
}

THUMB void UnkSoundPlayer::unkfunc_02055010(int bgm, int sub)
{
    if (enable_) {
        data_02101584.unkfunc_02050284(bgm, sub);
    }
}

THUMB void UnkSoundPlayer::unkfunc_02055024(int a, int b)
{
    if (enable_) {
        data_02101584.unkfunc_020503f4(a, b);
    }
}

THUMB void UnkSoundPlayer::unkfunc_02055038(int player, int bgm, int sub)
{
    if (!enable_) {
        return;
    }
    if (unkfunc_020550a0(bgm)) {
        unkfunc_02055070(0, 30);
    }
    bgm_ = bgm;
    bgmHandle_[player].unkfunc_0204fdfc(bgm, sub);
}

THUMB void UnkSoundPlayer::unkfunc_02055070(int player, int fade)
{
    if (enable_) {
        bgmHandle_[player].unkfunc_0204feac(fade);
    }
}

THUMB void UnkSoundPlayer::unkfunc_02055088(int player, int fade)
{
    if (enable_) {
        bgmHandle_[player].unkfunc_0204ff54(fade);
    }
}

THUMB int UnkSoundPlayer::unkfunc_020550a0(int player)
{
    return bgmHandle_[player].unkfunc_0204fed0();
}

THUMB int UnkSoundPlayer::unkfunc_020550b0(int player)
{
    return bgmHandle_[player].unkfunc_0204ff08();
}

THUMB void UnkSoundPlayer::unkfunc_020550c0(int player, int pause)
{
    bgmHandle_[player].unkfunc_0204ff40(pause);
}

THUMB void UnkSoundPlayer::unkfunc_020550d4(int volume)
{
    bgmVolumeSys_ = volume;
    unkfunc_0205510c();
}

THUMB void UnkSoundPlayer::unkfunc_020550e4(int volume)
{
    bgmVolume_ = volume;
    unkfunc_0205510c();
}

THUMB int UnkSoundPlayer::unkfunc_020550f4()
{
    return bgmVolume_;
}

THUMB void UnkSoundPlayer::unkfunc_020550fc(int volume)
{
    seVolumeSys_ = volume;
    unkfunc_0205513c();
}

THUMB void UnkSoundPlayer::unkfunc_0205510c()
{
    int volume = bgmVolumeSys_ * bgmVolume_ / 127;
    for (int i = 0; i < 3; i++) {
        bgmHandle_[i].unkfunc_0205011c(volume);
    }
}

THUMB void UnkSoundPlayer::unkfunc_0205513c()
{
    int volume = seVolumeSys_ * seVolume_ / 127;
    for (int i = 0; i < 8; i++) {
        seHandle_[i].unkfunc_0205011c(volume);
    }
}

THUMB void UnkSoundPlayer::unkfunc_0205516c(int index)
{
    seHandle_[index].unkfunc_0205011c(seVolumeSys_ * seVolume_ / 127);
}

THUMB int UnkSoundPlayer::unkfunc_02055194(int seqArc, int index)
{
    if (!enable_) {
        return -1;
    }
    int ret = 0;
    for (int i = 0; i < 8; i++) {
        if (seHandle_[i].unkfunc_020500c4(-1, -1)) {
            ret = i;
            seHandle_[i].unkfunc_0204ff74(seqArc, index);
            unkfunc_0205516c(i);
            break;
        }
    }
    return ret;
}

THUMB void UnkSoundPlayer::unkfunc_020551f0(int index, int fade)
{
    if (enable_) {
        seHandle_[index].unkfunc_020500dc(fade);
    }
}

THUMB void UnkSoundPlayer::unkfunc_02055208(int seqArc, int index, int fade)
{
    if (!enable_) {
        return;
    }
    for (int i = 0; i < 8; i++) {
        if (seHandle_[i].unkfunc_020500c4(seqArc, index)) {
            seHandle_[i].unkfunc_020500dc(fade);
        }
    }
}

THUMB void UnkSoundPlayer::unkfunc_0205523c(int fade)
{
    if (!enable_) {
        return;
    }
    for (int i = 0; i < 8; i++) {
        seHandle_[i].unkfunc_020500dc(fade);
    }
}

THUMB void UnkSoundPlayer::unkfunc_02055260(int no)
{
    if (enable_) {
        unk_008.unkfunc_02050440(no);
    }
}

THUMB void UnkSoundPlayer::unkfunc_02055270(int value)
{
    if (enable_) {
        unk_008.unkfunc_0205045c(value);
    }
}

THUMB int UnkSoundPlayer::unkfunc_02055280()
{
    return unk_008.unkfunc_02050464();
}

THUMB void UnkSoundPlayer::unkfunc_0205528c()
{
    for (int i = 0; i < 8; i++) {
        if (seHandle_[i].sePlaying_) {
            seHandle_[i].sePlaying_ = 0;
        } else if (!seHandle_[i].unkfunc_020500f8()) {
            seHandle_[i].unkfunc_020500dc(5);
        }
    }
}
