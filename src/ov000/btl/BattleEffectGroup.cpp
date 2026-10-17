#include "ov000/btl/BattleEffectGroup.hpp"

inline void btl::BattleEffectGroup::init()
{
    effectSimple_[FIRST] = 0;
    effectSimple_[SECOND] = 0;
    flag_.clear();
    state_.clear();
}

THUMB btl::BattleEffectGroup::BattleEffectGroup()
{
    init();
}

THUMB btl::BattleEffectGroup::~BattleEffectGroup()
{
}

THUMB void btl::BattleEffectGroup::draw()
{
    if (flag_.check(FLAG_FIRST_DRAW) && !state_.check(FLAG_FIRST_DRAW)) {
        effectSimple_[FIRST]->draw();
    }
    if (flag_.check(FLAG_SECOND_DRAW) && !state_.check(FLAG_SECOND_DRAW)) {
        effectSimple_[SECOND]->draw();
    }
}

THUMB void btl::BattleEffectGroup::extraDraw()
{
    if (flag_.check(FLAG_FIRST_DRAW) && state_.check(FLAG_FIRST_DRAW)) {
        effectSimple_[FIRST]->draw();
    }
    if (flag_.check(FLAG_SECOND_DRAW) && state_.check(FLAG_SECOND_DRAW)) {
        effectSimple_[SECOND]->draw();
    }
}

THUMB void btl::BattleEffectGroup::start()
{
    flag_.set(FLAG_FIRST_DRAW);
    effectSimple_[FIRST]->start();
    if (effectSimple_[SECOND]) {
        flag_.set(FLAG_SECOND_DRAW);
        effectSimple_[SECOND]->start();
    }
}

THUMB void btl::BattleEffectGroup::addEffect(cmn::CommonEffectData* data, bool flag)
{
    cmn::CommonEffectSimple* effect;
    if (data->getEffectType() == 0) {
        effectFlat_.setup(data, true);
        effect = &effectFlat_;
    }
    else {
        effectCubic_.setup(data, flag);
        effect = &effectCubic_;
    }
    effectSimple_[regist_] = effect;
    regist_++;
}

THUMB void btl::BattleEffectGroup::cleanup(bool flag)
{
    effectFlat_.cleanup(true);
    effectCubic_.cleanup(flag);
    init();
    regist_ = 0;
}

THUMB void btl::BattleEffectGroup::setScale(dss::Fix32 scale)
{
    if (effectSimple_[FIRST]) {
        effectSimple_[FIRST]->setScale(scale);
    }
    if (effectSimple_[SECOND]) {
        effectSimple_[SECOND]->setScale(scale);
    }
}

THUMB void btl::BattleEffectGroup::setDisplayType(int type, int index)
{
    cmn::CommonEffectSimple*& simple = effectSimple_[index];
    if (simple) {
        if (type == 1) {
            simple->getType();
            simple->setDisplayType(1);
        }
        else {
            simple->setDisplayType(3);
        }
        if (type == 1) {
            if (index == FIRST) {
                state_.set(FLAG_FIRST_DRAW);
            }
            else {
                state_.set(FLAG_SECOND_DRAW);
            }
        }
        else if (index == FIRST) {
            state_.remove(FLAG_FIRST_DRAW);
        }
        else {
            state_.remove(FLAG_SECOND_DRAW);
        }
    }
}

THUMB void btl::BattleEffectGroup::setPosition(dss::Fix32Vector3& position)
{
    if (effectSimple_[FIRST]) {
        effectSimple_[FIRST]->setPosition(position);
    }
    if (effectSimple_[SECOND]) {
        effectSimple_[SECOND]->setPosition(position);
    }
}

THUMB bool btl::BattleEffectGroup::isEnable()
{
    return effectSimple_[FIRST] != 0;
}

THUMB bool btl::BattleEffectGroup::isEnd()
{
    bool ret = true;
    if (effectSimple_[FIRST]) {
        if (!effectSimple_[FIRST]->isEnd()) {
            ret = false;
        }
        else {
            flag_.remove(FLAG_FIRST_DRAW);
        }
    }
    if (effectSimple_[SECOND]) {
        if (!effectSimple_[SECOND]->isEnd()) {
            ret = false;
        }
        else {
            flag_.remove(FLAG_SECOND_DRAW);
        }
    }
    return ret;
}
