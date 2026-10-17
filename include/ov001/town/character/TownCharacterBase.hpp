#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"
#include "main/dss/Camera.hpp"
#include "main/cmn/MoveBase.hpp"

struct Render;

struct TOWN_CHARACTER {
    int enable;                                 // 0x00
    int charaIndex;                             // 0x04
    int dir;                                    // 0x08
    int ctrlNo;                                 // 0x0C
    dss::Fix32Vector3 position;                 // 0x10
    dss::Flag flag;                             // 0x1C
};

namespace twn {
    extern const dss::Fix32 fixLen;

    enum SCRIPT_MOVE_TYPE {
        MOVE_TYPE_NONE = 0,
        MOVE_TYPE_AREA = 1,
        MOVE_TYPE_ROOT = 2,
        MOVE_TYPE_PURSUE = 3,
        MOVE_TYPE_TO_PARTY = 4,
        MOVE_TYPE_SIMPLE_MOVE = 5,
        MOVE_TYPE_JUMP = 6,
        MOVE_TYPE_PASSIVE = 7,
        MOVE_TYPE_RANDOM = 8,
        MOVE_TYPE_REVESE = 9,
        MOVE_TYPE_BIG_ROCK = 10,
        MOVE_TYPE_WAIT = 11,
        MOVE_TYPE_MAP_OBJ = 12,
    };

    struct SCRIPT_MOVE_DATA {
        dss::Fix32Vector3 vector[4];            // 0x00
        dss::Fix32 speed;                       // 0x30
        int frame;                              // 0x34
        int counter;                            // 0x38
    };

    struct TOWN_SCRIPT_DATA {
        dss::Fix32Vector3 node[4];              // 0x00
        int num[4];                             // 0x30
        int frame;                              // 0x40
        int counter;                            // 0x44
        int isEnd;                              // 0x48
    };

    struct TownCharacterBase {
        enum {
            SYNCHRONOUS_NONE = 0,
            SYNCHRONOUS_STOP = 1,
            SYNCHRONOUS_MOVE = 2,
        };

        // vtable                               // 0x000
        int charaParamIndex_;                   // 0x004
        int collFlag_;                          // 0x008
        TOWN_CHARACTER data_;                   // 0x00C
        TOWN_SCRIPT_DATA script_;               // 0x02C
        int type_;                              // 0x078
        SCRIPT_MOVE_TYPE moveType_;             // 0x07C
        SCRIPT_MOVE_DATA moveData_;             // 0x080
        Render* render_;                        // 0x0BC
        dss::Camera* cmr_;                      // 0x0C0
        cmn::MoveBase simpleMove_;              // 0x0C4
        dss::Fix32Vector3 syncroPos_;           // 0x114
        dss::Fix32Vector3 addRGB;               // 0x120
        dss::Fix32Vector3 setRGB;               // 0x12C
        int waitCounter_;                       // 0x138
        int voice_;                             // 0x13C
        short swingIdx_;                        // 0x140
        short blinkCounter_;                    // 0x142
        short alphaCounter_;                    // 0x144
        short alphaFrame_;                      // 0x146
        short changeAlphaType_;                 // 0x148
        short rgbFrame_;                        // 0x14A
        short animCounter_;                     // 0x14C
        short moveIdx_;                         // 0x14E
        short rgbFrameMax_;                     // 0x150
        unsigned char alphaAdd_;                // 0x152
        unsigned char remoteAlpha_;             // 0x153
        char mapNo_;                            // 0x154
        char stageColl_;                        // 0x155
        char rgbChangeType_;                    // 0x156
        char syncroNo_;                         // 0x157
        char syncroType_;                       // 0x158
        char alphaMax_;                         // 0x159
        char m_talk_enable;                     // 0x15A

        static int areaCheck_;
        static int allEventLock_;
        static int monsterTalk_;

        TownCharacterBase();
        ~TownCharacterBase();
        virtual void setup(TOWN_CHARACTER& chara);
        virtual void cleanup() = 0;
        virtual void execute();
        virtual void draw() = 0;
        virtual void setDir(int dir);
        virtual int getDir();
        virtual void setRotation(dss::Vector3<short>& rot);
        virtual void setRotation(unsigned short rot);
        virtual void setShadow(int flag);
        virtual void setAnimation(int flag);
        virtual void setNearCharacter(int flag);
        virtual void setDisplay(int flag);
        virtual int isDisplay();
        virtual void setSleepCharacter(int flag);
        virtual void setWriggleCharacter(int flag);
        virtual void setAlpha(unsigned char alpha);
        virtual unsigned char getAlpha();
        virtual void changePose(int pose);
        virtual void restorePose();
        virtual void requestReload();
        virtual void setHueChange(int type, int frame);
        virtual bool isHueChange();
        virtual void setShadowOnly(int flag);
        virtual void setScale(dss::Fix32 scale);
        virtual void setPaletteRate(unsigned char r, unsigned char g, unsigned char b, dss::Fix32 rate);
        virtual void setPaletteRate(dss::Fix32 r, dss::Fix32 g, dss::Fix32 b);
        virtual void setChangePaletteRate(dss::Fix32Vector3& rate, int frame);
        virtual void setChangePaletteRate(unsigned char r, unsigned char g, unsigned char b, int frame);
        virtual bool isEndPalletRate();
        virtual void setPalletRate(dss::Fix32 rate);
        virtual void setPosition(dss::Fix32Vector3& pos);
        virtual void execPursueMove();
        virtual void execAreaMove();
        virtual void execRootMove();
        virtual void setMotion(int motion, bool flag);
        virtual bool isMotion();
        virtual void setColor(unsigned char r, unsigned char g, unsigned char b);
        virtual void execMovePassive();
        virtual void setMoveBigRock();
        virtual void execMoveBigRock();
        virtual void setMapUid(int uid);

        void setCollFlag(int flag);
        int getCollFlag();
        void setMoveType(SCRIPT_MOVE_TYPE type);
        SCRIPT_MOVE_TYPE getMoveType();
        void setMoveData(SCRIPT_MOVE_DATA& data);
        void setStageColl(char flag);
        int getCharaType();
        int getCharaIndex();
        dss::Fix32Vector3& getPosition();
        void setScriptData(TOWN_SCRIPT_DATA& data);
        int isScriptEnd();
        void execWait();
        void execMove();
        void execRiseup();
        void execTremble();
        void changeRGB();
        void changeAlpha();
        void checkMoveColl(dss::Fix32Vector3& pos1, dss::Fix32Vector3& pos2, dss::Fix32& ret, dss::Fix32& min);
        void setMoveToParty();
        void setNextMoveToParty();
        void setSimpleMove();
        void setSimpleRot(short idx, int frame, int mode);
        void setJumpMove(dss::Fix32Vector3 target, int frame);
        void jumpMove();
        void setLockRot(int flag);
        void setPosing(int pose);
        void setMovePassive();
        void setPassiveRetPos(dss::Fix32Vector3& retPos, dss::Fix32Vector3& playerPos, dss::Fix32Vector3& vec);
        void setMoveReverse();
        void execMoveReverse();
        void setMoveRandom();
        void execMoveRandom();
        bool checkPlayerColl(dss::Fix32Vector3& newPos);
        void setSwingRoundIdx();
        void setFadeType(int type, int frame);
        bool isEndFade();
        void setPersonalEventLock(bool flag);
        void setMonsterSpeak(int flag);
        void resetTalk();
        bool getSpeak();
        void setSpeak(bool flag);
        bool getTalked();
        void setTalked(bool flag);
        void setCounterTalk(bool flag);
        bool getCounterTalk();
        bool isRotEnd();
        void setSwingRound(int flag);
        void execMoveWait();
        void setRotFrame(int frame, short idx, int flag, int typeA);
        bool isRotFrameEnd();
        void setVoice(int voice);
        bool checkVoice();
        int getVoice();
        void setObjectMove(int uid, dss::Fix32Vector3& offset, int type);
        void mapObjMove();
        void setSynchronous(int flag, int no);
        void setSyncroPos();
        void setMotionLock(int flag);
        static void setAllEventLock(bool flag);
        static void setAreaCheck(bool flag);
        static bool getMonsterSpeakAll();
    };
}
