#pragma once
#include <globaldefs.h>
#include "ov000/btl/BattleEffectStorage.hpp"
#include "ov000/btl/BattleEffectUnit.hpp"
#include "main/cmn/CommonEffectResource.hpp"

namespace status {
    struct CharacterStatus;
    struct PlayerStatus;
    struct UseActionParam;
}

namespace btl {
    struct BattleEffectManager {
        static const int MAX_REPRODUCT = 8;

        BattleEffectStorage storage_;               // 0x0000
        cmn::CommonEffectResource resource_;        // 0x2F74
        BattleEffectUnit unit_[MAX_REPRODUCT];      // 0x37E4
        int wait_;                                  // 0x40A4

        BattleEffectManager();
        ~BattleEffectManager();
        static BattleEffectManager* getSingleton();
        void initialize();
        void terminate();
        void execute();
        void extraDraw();
        void draw();
        void setCameraPos();
        int isEnd();
        bool isAllEnd();
        int getWeaponEffectID(status::PlayerStatus* playerStatus);
        int getEffectParam(int effectID);
        int setupEffect(int effectID);
        bool isEndWait();
        void setTarget(int index, status::UseActionParam& useActionParam);
        void setTarget(int index, status::CharacterStatus* actor, int anim);
        void setWaitTime(int index, int frame);
        int getHitFrame(int index);
        void setMessageWait(int wait);
        void setSpecialTarget(int index, int ctrlId, int anim);
    };
}
