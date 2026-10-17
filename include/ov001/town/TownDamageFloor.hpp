#pragma once
#include <globaldefs.h>
#include "main/cmn/CommonWalkDamage.hpp"

struct TownDamageFloor : cmn::CommonWalkDamage {
    dss::Fix32Vector3 nowPos_;                  // 0x18
    dss::Fix32Vector3 nextPos_;                 // 0x24
    int check_;                                 // 0x30

    static TownDamageFloor& getSingleton();
    void setup();
    virtual bool checkBarrier();
    virtual bool checkPoison();
    virtual bool checkYogan();
    virtual bool checkPuddle();
    virtual void setPartyMemberColor(int index, int type);
    virtual void setPuddleEffect(int index);
    void checkDamageFloor(dss::Fix32Vector3& nowPos, dss::Fix32Vector3& nextPos);
    void checkEncount();
};
