#pragma ipa file
#include "main/script/ScriptBaseCommand.hpp"

struct ScriptCommandWeakVtable : ScriptCommand {
    virtual void initialize(char* scriptParam);
    virtual int isEnd();
};

#include "main/script/ScriptCommandCommon.hpp"
#include "main/script/CommandParam.hpp"
#include "main/global/Global.hpp"
#include "main/global/UnkGlobalSystem.hpp"
#include "main/sound/SoundManager.hpp"
#include "main/sound/Sound.hpp"
#include "main/cmn/GameManager.hpp"
#include "main/cmn/CommonCalculate.hpp"
#include "main/status/StageInfo.hpp"
#include "main/status/StoryStatus.hpp"
#include "ov001/town/TownSystem.hpp"

inline ScriptCommand::ScriptCommand()
{
}

inline ScriptCommand::~ScriptCommand()
{
}

inline void ScriptCommandWeakVtable::initialize(char* scriptParam)
{
}

inline int ScriptCommandWeakVtable::isEnd()
{
    return 0;
}

inline void FadeIn::terminate()
{
}

inline void FadeOut::terminate()
{
}

inline void FadeIn2::terminate()
{
}

inline void FadeOut2::terminate()
{
}

inline void Music_volume::execute()
{
}

inline void status::StageInfo::setShipPosition(int index, dss::Fix32Vector3& pos)
{
    shipPosition_[index] = pos;
}

inline void status::StageInfo::setFieldChange(int ch)
{
    fieldChangeIndex_ = ch;
}

THUMB void FadeIn::initialize(char* scriptParam)
{
    PARAM_FADEIN* param = (PARAM_FADEIN*)scriptParam;
    g_Global.fadeIn(param->frame);
    count_ = 0;
    countFrame_ = param->frame;
}

THUMB void FadeIn::execute()
{
    count_++;
}

THUMB int FadeIn::isEnd()
{
    if (count_ >= countFrame_) {
        return true;
    }
    return false;
}

FadeIn g_FadeIn;

THUMB void FadeOut::initialize(char* scriptParam)
{
    PARAM_FADEOUT* param = (PARAM_FADEOUT*)scriptParam;
    if (param->type == 0) {
        g_Global.fadeOutBlack(param->frame, true);
    } else {
        g_Global.fadeOutWhite(param->frame, true);
    }
    count_ = 0;
    countFrame_ = param->frame;
}

THUMB void FadeOut::execute()
{
    count_++;
}

THUMB int FadeOut::isEnd()
{
    if (count_ >= countFrame_) {
        return true;
    }
    return false;
}

FadeOut g_FadeOut;

THUMB void FadeIn2::initialize(char* scriptParam)
{
    PARAM_FADEIN2* param = (PARAM_FADEIN2*)scriptParam;
    int frame = param->frame;
    switch (data_0211b27c.state_) {
    case FadeEffector::FADE_NONE:
        data_0211b27c.state_ = FadeEffector::FADE_OUT_BLACK;
        break;
    case FadeEffector::FADE_IN_BLACK:
        data_0211b27c.state_ = FadeEffector::FADE_OUT_WHITE;
        break;
    default:
        data_0211b27c.state_ = FadeEffector::FADE_OUT_BLACK;
        break;
    }
    data_0211b27c.count_ = 0;
    data_0211b27c.frames_ = frame;
    data_02101d14.addPart(&data_0211b27c);
    count_ = 0;
    countFrame_ = param->frame;
}

THUMB void FadeIn2::execute()
{
    count_++;
}

THUMB int FadeIn2::isEnd()
{
    if (count_ >= countFrame_) {
        return true;
    }
    return false;
}

FadeIn2 g_FadeIn2;

THUMB void FadeOut2::initialize(char* scriptParam)
{
    PARAM_FADEOUT2* param = (PARAM_FADEOUT2*)scriptParam;
    if (param->type == 0) {
        int frame = param->frame;
        data_0211b27c.state_ = FadeEffector::FADE_NONE;
        data_0211b27c.count_ = 0;
        data_0211b27c.frames_ = frame;
        data_0211b27c.sprite_[0].setColor(0, 0, 0);
        data_0211b27c.sprite_[1].setColor(0, 0, 0);
        data_02101d14.addPart(&data_0211b27c);
    } else {
        int frame = param->frame;
        data_0211b27c.state_ = FadeEffector::FADE_IN_BLACK;
        data_0211b27c.count_ = 0;
        data_0211b27c.frames_ = frame;
        data_0211b27c.sprite_[0].setColor(0x1F, 0x1F, 0x1F);
        data_0211b27c.sprite_[1].setColor(0x1F, 0x1F, 0x1F);
        data_02101d14.addPart(&data_0211b27c);
    }
    count_ = 0;
    countFrame_ = param->frame;
}

THUMB void FadeOut2::execute()
{
    count_++;
}

THUMB int FadeOut2::isEnd()
{
    if (count_ >= countFrame_) {
        return true;
    }
    return false;
}

FadeOut2 g_FadeOut2;

THUMB bool cmd_is_trigger_common(void* scriptParam)
{
    PARAM_IS_TRIGGER_FORWARD* param = (PARAM_IS_TRIGGER_FORWARD*)scriptParam;
    dss::Fix32Vector3 pos = cmn::GameManager::getSingleton().playerManager_->getPosition();
    short idx = cmn::GameManager::getSingleton().playerManager_->getDirection();
    dss::Fix32Vector3 start;
    dss::Fix32Vector3 end;
    start.set(param->startX, param->startY, param->startZ);
    end.set(param->endX, param->endY, param->endZ);
    (start + end) / 2 - pos;
    int checkDir;
    if (param->flag == 0) {
        checkDir = 7;
    } else {
        checkDir = 6;
    }
    int checkArea = 0;
    return cmn::CommonCalculate::areaCheck(pos, idx, start, end, checkArea, checkDir);
}

THUMB bool cmd_set_music(void* scriptParam)
{
    PARAM_SET_MUSIC* param = (PARAM_SET_MUSIC*)scriptParam;
    SoundManager::play(param->music, 5);
    return true;
}

THUMB bool cmd_music_pause(void* scriptParam)
{
    PARAM_MUSIC_PAUSE* param = (PARAM_MUSIC_PAUSE*)scriptParam;
    if (param->pause == 1) {
        SoundManager::stop(5);
    }
    return true;
}

THUMB bool cmd_play_music_now_map(void* scriptParam)
{
    if (data_02101c88.isCurrentPart(4) == 1) {
        SoundManager::townPlay(twn::TownSystem::getFloorBgmIndex());
    } else if (data_02101c88.isCurrentPart(6) == 1) {
        SoundManager::fieldPlay(7);
    }
    return true;
}

THUMB bool cmd_not_play_normal_sound(void* scriptParam)
{
    SoundManager::setTownPlayDisable();
    return true;
}

THUMB void Music_volume::initialize(char* scriptParam)
{
    PARAM_MUSIC_VOLUME* param = (PARAM_MUSIC_VOLUME*)scriptParam;
    endVolume_ = (int)param->volume * 127 / 100;
    dss::clamp(0, endVolume_, 127);
    start_ = Sound::getBgmVolume();
    frame_ = param->frame;
    add_ = (long)((endVolume_ - start_) / frame_);
    counter_ = 0;
}

THUMB int Music_volume::isEnd()
{
    if (counter_ >= frame_) {
        Sound::setBgmVolume(endVolume_);
        return true;
    }
    int start = start_;
    int volume = add_.value * counter_ / FX32_ONE;
    dss::clamp(0, start + volume, 127);
    Sound::setBgmVolume(start + volume);
    counter_++;
    return false;
}

Music_volume gMusic_volume;

THUMB void PlayMusic::initialize(char* scriptParam)
{
    PARAM_PLAY_MUSIC* param = (PARAM_PLAY_MUSIC*)scriptParam;
    musicNo_ = param->musicNo;
    playTime_ = param->frame + 30;
    flag_ = param->flag;
    soundCount_ = 0;
    playEnd_ = false;
    SoundManager::stopBgm(0);
}

THUMB void PlayMusic::execute()
{
    if (soundCount_ == -1) {
        playEnd_ = true;
    }
    if (soundCount_ == 30) {
        SoundManager::play(musicNo_, 5);
        soundCount_++;
    } else if (soundCount_ < playTime_) {
        soundCount_++;
    } else if (soundCount_ == playTime_) {
        SoundManager::stopBgm(0);
        soundCount_++;
    } else if (soundCount_ > playTime_) {
        if (!flag_) {
            if (data_02101c88.isCurrentPart(4) == 1) {
                SoundManager::townPlay(twn::TownSystem::getFloorBgmIndex());
            } else if (data_02101c88.isCurrentPart(6) == 1) {
                SoundManager::fieldPlay(7);
            }
        }
        soundCount_ = -1;
    }
}

THUMB int PlayMusic::isEnd()
{
    return playEnd_;
}

PlayMusic gPlayMusic;

THUMB bool cmd_set_ship_pos(void* scriptParam)
{
    PARAM_SET_SHIP_POS* param = (PARAM_SET_SHIP_POS*)scriptParam;
    dss::Fix32Vector3 pos;
    pos.vx.value = param->posX;
    pos.vy.value = param->posY;
    pos.vz.value = param->posZ;
    pos *= 16;
    status::g_StageInfo.setShipPosition(0, pos);
    return true;
}

THUMB bool cmdChangeField(void* scriptParam)
{
    PARAM_CHANGE_FIELD* param = (PARAM_CHANGE_FIELD*)scriptParam;
    status::g_StageInfo.setFieldChange(param->index);
    return true;
}

THUMB bool cmd_check_smallmedal(void* scriptParam)
{
    return status::g_Story.isMedalFlag();
}

void ScriptCommandCommon_weakVtable()
{
    ScriptCommandWeakVtable unused;
}
