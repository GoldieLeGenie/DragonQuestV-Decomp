#include "main/sound/Sound.hpp"
#include "main/sound/UnkSoundPlayer.hpp"

static unsigned char s_bgm_volume_tbl[] = {
    0x00, 0x7f, 0x5f, 0x46, 0x46, 0x5f, 0x64, 0x64, 0x5a, 0x69, 0x6e, 0x64, 0x55, 0x5f, 0x50, 0x69,
    0x6e, 0x5f, 0x5f, 0x55, 0x69, 0x55, 0x5a, 0x5f, 0x5f, 0x7f, 0x5f, 0x69, 0x64, 0x55, 0x6e, 0x6e,
    0x7f, 0x7f, 0x7f, 0x5f, 0x5a, 0x55, 0x4b, 0x7d, 0x6e, 0x5a, 0x46, 0x50, 0x5f, 0x5f, 0x69, 0x69,
    0x4b, 0x55, 0x64, 0x5f, 0x64, 0x64, 0x64,
};
unsigned char* data_0209af0c = s_bgm_volume_tbl;

THUMB void Sound::unkfunc_02068868(int bgm, int sub)
{
    data_021025e0.unkfunc_020550e4(data_0209af0c[bgm]);
    data_021025e0.unkfunc_02055010(bgm, sub);
    data_021025e0.unkfunc_02055038(0, bgm, sub);
}

THUMB void Sound::unkfunc_0206889c(int fade)
{
    data_021025e0.unkfunc_02055070(0, fade);
}

THUMB void Sound::unkfunc_020688b0(int fade)
{
    data_021025e0.unkfunc_02055088(0, fade);
}

THUMB int Sound::unkfunc_020688c4()
{
    return data_021025e0.unkfunc_020550a0(0);
}

THUMB int Sound::unkfunc_020688d4()
{
    return data_021025e0.unkfunc_020550b0(0);
}

THUMB void Sound::unkfunc_020688e4(int pause)
{
    data_021025e0.unkfunc_020550c0(0, pause);
}

THUMB void Sound::unkfunc_020688f8(int no)
{
    data_021025e0.unkfunc_02055260(no);
}

THUMB void Sound::unkfunc_02068908(int value)
{
    data_021025e0.unkfunc_02055270(value);
}

THUMB int Sound::unkfunc_02068918()
{
    return data_021025e0.unkfunc_02055280();
}

THUMB int Sound::sePlay(int se)
{
    return data_021025e0.unkfunc_02055194(0, se);
}

THUMB int Sound::sePlay2(int se)
{
    data_021025e0.unkfunc_020550e4(110);
    data_021025e0.unkfunc_02055010(se, 0);
    data_021025e0.unkfunc_02055038(2, se, 0);
    return 0;
}

THUMB void Sound::unkfunc_02068968(int fade)
{
    data_021025e0.unkfunc_02055070(2, fade);
}

THUMB void Sound::unkfunc_0206897c(int fade)
{
    data_021025e0.unkfunc_020551f0(0, fade);
}

THUMB void Sound::unkfunc_02068990(int se, int fade)
{
    data_021025e0.unkfunc_02055208(0, se, fade);
}

THUMB void Sound::unkfunc_020689a4(int fade)
{
    data_021025e0.unkfunc_0205523c(fade);
}

THUMB int Sound::sePlayDirect(int se)
{
    int ret = data_021025e0.unkfunc_02055194(0, se);
    data_02101584.unkfunc_0205027c();
    return ret;
}

THUMB void Sound::setBgmVolume(int volume)
{
    data_021025e0.unkfunc_020550e4(volume);
}

THUMB int Sound::getBgmVolume()
{
    return data_021025e0.unkfunc_020550f4();
}

THUMB void Sound::setBgmVolumeSys(int volume)
{
    data_021025e0.unkfunc_020550d4(volume);
}

THUMB void Sound::setSeVolumeSys(int volume)
{
    data_021025e0.unkfunc_020550fc(volume);
}
