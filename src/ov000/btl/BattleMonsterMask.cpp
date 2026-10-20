#pragma ipa file
#include "ov000/btl/BattleMonsterMask.hpp"
#include "ov000/status/MonsterParty.hpp"
#include "ov018/btl/BattleMonsterDraw2.hpp"
#include "main/btl/MonsterData.hpp"
#include "main/window/UnkMapPoint.hpp"
#include "main/dss/RenderObject.hpp"

inline btl::BattleMonster& btl::BattleMonsterDraw2::getMonster(int index) { return monsters_[index]; }

namespace btl {
    static dss::Fix32 scale(1.0f);
}

int btl::BattleMonsterMask::monsterRectTemp[MONSTER_MAX];

THUMB btl::BattleMonsterMask::BattleMonsterMask() : select_(-1)
{
}

THUMB btl::BattleMonsterMask::~BattleMonsterMask()
{
}

THUMB btl::BattleMonsterMask* btl::BattleMonsterMask::getSingleton()
{
    static BattleMonsterMask battleMonsterMask;
    return &battleMonsterMask;
}

THUMB void btl::BattleMonsterMask::initialize()
{
    sprite_.screens_ = 3;
    sprite_.setPolygonID(0x3e);
    sprite_.depth_ = 0;
    sprite_.setAlpha(10);
    sprite_.unkfunc_02047e88(0, 0);
    sprite_.unkfunc_02047ec0(0x80, 0x80);
    sprite_.enable_ = 0;
    sprite_.setColor(0, 0, 0);
    mask_[0].loadFile("data/mask/en02.tex", 0);
    mask_[0].setAlpha(1);
    mask_[1].loadFile("data/mask/en01.tex", 0);
    mask_[1].setAlpha(1);
    for (int i = 0; i < MASK_MAX; i++) {
        mask_[i].setBothScreens();
        mask_[i].setPolygonID(0x3e);
        mask_[i].setDepth(0);
        mask_[i].setPosition(0, 0);
        mask_[i].setEnabled(0);
    }
    scale_ = 0x1000;
    data_02101da4 = 1;
}

THUMB void btl::BattleMonsterMask::setup()
{
    select_ = -1;
    int count = status::g_Monster.getCount();
    for (int i = 0; i < count; i++) {
        if (status::g_Monster.getMonsterStatus(i).haveStatusInfo_.drawCtrlId_ != -1) {
            calcTargetPos(i);
        }
    }
}

THUMB void btl::BattleMonsterMask::terminate()
{
    for (int i = 0; i < MASK_MAX; i++) {
        mask_[i].unload();
    }
    data_02101da4 = 0;
}

THUMB void btl::BattleMonsterMask::execute()
{
}

THUMB void btl::BattleMonsterMask::select(int groupId)
{
    select_ = groupId;
}

THUMB void btl::BattleMonsterMask::draw()
{
    if (select_ < 0) {
        sprite_.enable_ = 0;
        for (int i = 0; i < MASK_MAX; i++) {
            mask_[i].setEnabled(0);
        }
        return;
    }
    sprite_.enable_ = 1;
    for (int i = 0; i < MASK_MAX; i++) {
        mask_[i].setEnabled(1);
    }
    for (int i = 0; i < status::g_Monster.getCount(); i++) {
        if (status::g_Monster.getMonsterStatus(i).isBattleEnable() && select_ == status::g_Monster.getMonsterGroup(i)) {
            targetPos[i] = getTargetPos(i);
        }
    }
    setupOrtho2DFine();
    for (int j = 0; j < MASK_MAX; j++) {
        for (int i = 0; i < MONSTER_MAX; i++) {
            if (select_ == status::g_Monster.getMonsterGroup(i) && status::g_Monster.getMonsterStatus(i).isBattleEnable()) {
                mask_[j].setPosition(targetPos[i].vx / 2, targetPos[i].vy * 2 / 3);
                mask_[j].setRotation(0);
                mask_[j].draw();
            }
        }
    }
    sprite_.draw();
}

THUMB void btl::BattleMonsterMask::calcTargetPos(int actorindex)
{
    dss::Fix32 x;
    dss::Fix32 y;
    dss::Fix32Vector3 pos;
    int index = status::g_Monster.getMonsterStatus(actorindex).haveStatusInfo_.drawCtrlId_;
    dss::Fix32Vector3* position = BattleMonsterDraw2::getSingleton().getMonster(index).monsterDraw_.getPosition();
    pos = dss::Fix32Vector3(*position);
    unkfunc_02052150(actorindex, pos);
}

THUMB dss::Vector2<int> btl::BattleMonsterMask::getTargetPos(int actorindex)
{
    dss::Vector2<int> screen;
    int monster;
    if (status::g_Monster.getMonsterStatus(actorindex).haveStatusInfo_.isMosyasExec()) {
        monster = status::g_Monster.getMonsterStatus(actorindex).mosyasMonsterIndex_;
    }
    else {
        monster = status::g_Monster.getMonsterIndex(actorindex);
    }
    short* rect = MonsterTaiData[monster];
    int maskScaleX = dss::abs<int>(rect[1] - rect[3]);
    int maskScaleY = (scale_ * dss::abs<int>(rect[2] - rect[4])).value / 4096;
    maskScaleX = (scale_ * maskScaleX).value / 4096;
    screen = *unkfunc_02052164(actorindex);
    maskScaleY = maskScaleY * 2 / 3;
    screen.vx -= maskScaleY;
    screen.vy -= maskScaleX;
    for (int i = 0; i < MASK_MAX; i++) {
        mask_[i].setSize(maskScaleY, maskScaleX);
    }
    return screen;
}

THUMB int* btl::BattleMonsterMask::getMonsterTouchRect(int actorindex)
{
    int monster;
    if (status::g_Monster.getMonsterStatus(actorindex).haveStatusInfo_.isMosyasExec()) {
        monster = status::g_Monster.getMonsterStatus(actorindex).mosyasMonsterIndex_;
    }
    else {
        monster = status::g_Monster.getMonsterIndex(actorindex);
    }
    short* rect = MonsterTaiData[monster];
    int width = dss::abs<int>(rect[2] - rect[4]);
    int height = dss::abs<int>(rect[1] - rect[3]);
    dss::Vector2<int> screen = *unkfunc_02052164(actorindex);
    monsterRectTemp[0] = status::g_Monster.getMonsterGroup(actorindex);
    monsterRectTemp[1] = screen.vx - width / 2;
    monsterRectTemp[2] = screen.vy - height - rect[3] / 2;
    monsterRectTemp[3] = screen.vx + width / 2;
    monsterRectTemp[4] = screen.vy;
    return monsterRectTemp;
}
