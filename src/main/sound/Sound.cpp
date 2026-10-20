#include "main/sound/Sound.hpp"
#include "main/sound/UnkSoundPlayer.hpp"

static unsigned char s_bgm_volume_tbl[] = {
    0x00, 0x7f, 0x5f, 0x46, 0x46, 0x5f, 0x64, 0x64, 0x5a, 0x69, 0x6e, 0x64, 0x55, 0x5f, 0x50, 0x69,
    0x6e, 0x5f, 0x5f, 0x55, 0x69, 0x55, 0x5a, 0x5f, 0x5f, 0x7f, 0x5f, 0x69, 0x64, 0x55, 0x6e, 0x6e,
    0x7f, 0x7f, 0x7f, 0x5f, 0x5a, 0x55, 0x4b, 0x7d, 0x6e, 0x5a, 0x46, 0x50, 0x5f, 0x5f, 0x69, 0x69,
    0x4b, 0x55, 0x64, 0x5f, 0x64, 0x64, 0x64,
};
unsigned char* data_0209af0c = s_bgm_volume_tbl;

THUMB void Sound::bgmPlay(int bgm, int sub)
{
    data_021025e0.setBgmVolume(data_0209af0c[bgm]);
    data_021025e0.loadBgm(bgm, sub);
    data_021025e0.playBgm(0, bgm, sub);
}

THUMB void Sound::bgmStop(int fade)
{
    data_021025e0.stopBgm(0, fade);
}

THUMB void Sound::bgmStopAll(int fade)
{
    data_021025e0.stopAllBgm(0, fade);
}

THUMB int Sound::isBgmPlaying()
{
    return data_021025e0.isBgmPlaying(0);
}

THUMB int Sound::isBgmStopped()
{
    return data_021025e0.isBgmStopped(0);
}

THUMB void Sound::bgmPause(int pause)
{
    data_021025e0.pauseBgm(0, pause);
}

THUMB void Sound::strmPlay(int no)
{
    data_021025e0.playStrm(no);
}

THUMB void Sound::strmStop(int value)
{
    data_021025e0.stopStrm(value);
}

THUMB int Sound::isStrmPlaying()
{
    return data_021025e0.isStrmPlaying();
}

THUMB int Sound::sePlay(int se)
{
    return data_021025e0.playSe(0, se);
}

THUMB int Sound::sePlay2(int se)
{
    data_021025e0.setBgmVolume(110);
    data_021025e0.loadBgm(se, 0);
    data_021025e0.playBgm(2, se, 0);
    return 0;
}

THUMB void Sound::se2Stop(int fade)
{
    data_021025e0.stopBgm(2, fade);
}

THUMB void Sound::seStopFirst(int fade)
{
    data_021025e0.stopSeHandle(0, fade);
}

THUMB void Sound::seStop(int se, int fade)
{
    data_021025e0.stopSe(0, se, fade);
}

THUMB void Sound::seStopAll(int fade)
{
    data_021025e0.stopAllSe(fade);
}

THUMB int Sound::sePlayDirect(int se)
{
    int ret = data_021025e0.playSe(0, se);
    data_02101584.update();
    return ret;
}

THUMB void Sound::setBgmVolume(int volume)
{
    data_021025e0.setBgmVolume(volume);
}

THUMB int Sound::getBgmVolume()
{
    return data_021025e0.getBgmVolume();
}

THUMB void Sound::setBgmVolumeSys(int volume)
{
    data_021025e0.setBgmVolumeSys(volume);
}

THUMB void Sound::setSeVolumeSys(int volume)
{
    data_021025e0.setSeVolumeSys(volume);
}
