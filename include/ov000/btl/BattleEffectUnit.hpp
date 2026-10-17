#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"

namespace status {
    struct CharacterStatus;
    struct UseActionParam;
}

namespace cmn {
    struct CommonEffectResource;
}

namespace btl {
    struct BattleEffectStorage;
    struct BattleEffectGroup;

    struct BattleEffectUnit {
        static const int MAX_CONTAINER = 12;

        int effect_;                                // 0x000
        dss::Fix32Vector3 targetPos_[MAX_CONTAINER]; // 0x004
        int result_[MAX_CONTAINER];                 // 0x094
        BattleEffectGroup* group_[MAX_CONTAINER];   // 0x0C4
        int hit_;                                   // 0x0F4
        int pass_;                                  // 0x0F8
        int start_;                                 // 0x0FC
        int frame_;                                 // 0x100
        int max_;                                   // 0x104
        int process_;                               // 0x108
        int target_;                                // 0x10C
        int type_;                                  // 0x110
        int upper_;                                 // 0x114

        static BattleEffectStorage* storage_;
        static cmn::CommonEffectResource* resource_;

        BattleEffectUnit();
        ~BattleEffectUnit();
        static void setControlData(BattleEffectStorage* storage, cmn::CommonEffectResource* resource);
        void initialize();
        void terminate();
        void setTarget(status::UseActionParam& useActionParam);
        void setTarget(status::CharacterStatus* actor, int anim);
        void setSpecialTarget(int ctrlID, int anim);
        void setup(int effect);
        void cleanup();
        void setEffectPosition(int index, int monsterIndex, int anim);
        void shufflePosition();
        void setupEffectGroup(int index);
        void cleanupEffectGroup(int index);
        void draw();
        void extraDraw();
        void waitStart();
        void execute();
        int getHitFrame();
        bool isEnable();
        void setWaitTime(int time);
    };
}
