#pragma ipa file
#include "main/script/ScriptSoundCommand.hpp"
#include "main/script/CommandParam.hpp"
#include "main/global/UnkGlobalSystem.hpp"
#include "main/sound/SoundManager.hpp"

#pragma thumb on

inline ScriptCommand::ScriptCommand()
{
}

inline ScriptCommand::~ScriptCommand()
{
}

inline void BgmFade::terminate()
{
}

bool cmd_set_se(void* scriptParam)
{
    PARAM_SET_SE* param = (PARAM_SET_SE*)scriptParam;
    SoundManager::playSe(param->se, 0);
    return true;
}

bool cmd_cut_se(void* scriptParam)
{
    PARAM_CUT_SE* param = (PARAM_CUT_SE*)scriptParam;
    SoundManager::stopSeWithIndex(param->se, 0);
    return true;
}

bool cmd_set_sound_in_setup(void* scriptParam)
{
    PARAM_SET_SOUND_IN_SETUP* param = (PARAM_SET_SOUND_IN_SETUP*)scriptParam;
    if (data_02101c88.unkfunc_02051818(4)) {
        if (param->no == 0) {
            SoundManager::stop(5);
        } else {
            SoundManager::townPlay(param->no);
        }
    } else if (param->no == 0) {
        SoundManager::stop(5);
    } else {
        SoundManager::fieldPlay(param->no);
    }
    SoundManager::setTownPlayDisable();
    return true;
}

bool cmdSetSe2(void* scriptParam)
{
    PARAM_SET_SE* param = (PARAM_SET_SE*)scriptParam;
    SoundManager::playSe2(param->se, 0);
    return true;
}

bool cmdCutSe2(void* scriptParam)
{
    SoundManager::unkfunc_0206fc44(15);
    return true;
}

void BgmFade::initialize(char* scriptParam)
{
    PARAM_BGM_FADE* param = (PARAM_BGM_FADE*)scriptParam;
    bgm = param->sound;
    count = 0;
    frame = param->frame;
    fade = 12700 / frame;
    gain = 0;
    if (param->flag != 0) {
        gain = 12700;
        fade = -fade;
    } else {
        SoundManager::stopBgm(0);
        SoundManager::bgmIndex_ = 0;
        SoundManager::playBgm(bgm, 0);
    }
    SoundManager::setBgmVolume(gain / 100);
}

void BgmFade::execute()
{
}

int BgmFade::isEnd()
{
    gain += fade;
    SoundManager::setBgmVolume(gain / 100);
    count++;
    if (count >= frame) {
        if (fade < 0) {
            SoundManager::stopBgm(0);
        }
        return true;
    }
    return false;
}

BgmFade g_BgmFade;
