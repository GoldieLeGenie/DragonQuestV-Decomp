#include "main/status/TouchData.hpp"

inline status::TouchData::TouchData()
{
    cleanUp();
}

status::TouchData status::g_TouchData;

THUMB void status::TouchData::cleanUp()
{
    for (int i = 0; i < 10; i++) {
        ranking_[i].score = 0;
        ranking_[i].stage = 0;
    }
    setUp();
}

THUMB void status::TouchData::setUp()
{
    int itemIndex[17] = {
        161, 169, 168, 0, 0, 161, 162, 179, 178, 169, 183, 185, 165, 182, 184, 67, 135,
    };
    for (int i = 0; i < 17; i++) {
        item_[i].index = itemIndex[i];
        item_[i].count = 0;
    }
}

THUMB bool status::TouchData::setRanking(int score, int stage)
{
    newScore_ = score;
    int tmpScore = score;
    int tmpStage = stage;
    bool accept = false;
    for (int i = 0; i < 10; i++) {
        if (ranking_[i].score < tmpScore) {
            int tmp = tmpScore;
            tmpScore = ranking_[i].score;
            ranking_[i].score = tmp;
            tmp = tmpStage;
            tmpStage = ranking_[i].stage;
            ranking_[i].stage = tmp;
            accept = true;
        }
        if (ranking_[i].stage == 0) {
            int tmp = tmpScore;
            tmpScore = ranking_[i].score;
            ranking_[i].score = tmp;
            tmp = tmpStage;
            tmpStage = ranking_[i].stage;
            ranking_[i].stage = tmp;
            accept = true;
        }
        if (tmpStage == 0) {
            break;
        }
    }
    rankIn_ = accept;
    return accept;
}
