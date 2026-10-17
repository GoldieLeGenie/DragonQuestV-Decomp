#pragma once
#include <globaldefs.h>
#include "main/cmn/ActionBase.hpp"
#include "main/dss/DssUtils.hpp"
#include "ov005/fld/FieldActionCalculate.hpp"

namespace fld
{
    struct FieldActionBase : cmn::ActionBase {
        int inputDir_;                          // 0x04
        int prevInputDir_;                      // 0x08
        char getOn_[4];                         // 0x0C

        static const dss::Fix32 Speed;
        static const dss::Fix32 xSpeed;
        static const dss::Fix32 ySpeed;
        static const dss::Fix32 shipSearchR;
        static const dss::Fix32 shipGetDownR;
        static const dss::Fix32 Speed2;
        static const dss::Fix32 xSpeed2;
        static const dss::Fix32 ySpeed2;
        static const dss::Fix32 balSpeed;
        static const dss::Fix32 balXSpeed;
        static const dss::Fix32 balYSpeed;
        static FieldCollInfo fieldCollInfo_;
        static int blockType_[9];
        static dss::Fix32Vector3 positionN_;
        static dss::Fix32Vector3 speed_;
        static int collSE_;
        static int move_;

        void moveNormal(dss::Fix32 speed, dss::Fix32 xspeed, dss::Fix32 yspeed);
        bool searchObject(dss::Fix32Vector3& searchPos, dss::Fix32 dr);
        void coll(int blkX, int blkY);
        void walkColl(int blkX, int blkY);
        void setColl(int blkX, int blkY, int collLength, int fixLength);
        void setWalkColl(int blkX, int blkY, int collLength, int fixLength);
        bool isKaigFix(int dir4, int num);
        void endlessMove(dss::Fix32 rate1, dss::Fix32 rate2, short no);
        bool checkGetOut();
        virtual bool isGetOffAttr();
        virtual bool search() = 0;
    };

    struct FieldActionWalk : FieldActionBase {
        int firstMove_;                         // 0x10

        virtual int setup();
        virtual void execute();
        void walkCollision();
        virtual int update();
        bool checkShipAction();
        virtual bool search();
    };

    struct FieldActionShip : FieldActionBase {
        enum {
            FIELD_SHIP_ACTION_NONE = 0,
            FIELD_SHIP_ACTION_GET_ON = 1,
            FIELD_SHIP_ACTION_GET_OFF = 2,
        };

        int shipAction_;                        // 0x10
        int move_;                              // 0x14
        int downCounter_;                       // 0x18

        virtual int setup();
        virtual void execute();
        void shipMove();
        void startAction();
        void scriptStart();
        virtual int update();
        bool checkGetDownShip(int blkX, int blkY, short dirIdx);
        virtual bool search();
        dss::Fix32Vector3& getShipDrawPos(int index);
    };

    struct FieldActionRura : FieldActionBase {
        enum {
            RURA_UP = 0,
            RURA_DOWN = 1,
            SORATOBU = 2,
        };

        static const int RULA_EFFECT = 0x39E;

        int count_;                             // 0x10
        int sprite_;                            // 0x14
        int effectIndex_;                       // 0x18
        dss::Fix32Vector3 effectPos_;           // 0x1C

        virtual int setup();
        virtual void execute();
        virtual int update();
        virtual bool search();
        int start(int type);
    };

    struct FieldActionCarpet : FieldActionBase {
        enum {
            READY = 0,
            RISE_UP = 1,
            RISE_UP_END = 2,
            MOVE = 3,
            GET_DOWN = 4,
            GET_DOWN_END = 5,
            GET_OUT_WAIT = 6,
        };

        int counter_;                           // 0x10
        int counter2_;                          // 0x14
        int state_;                             // 0x18
        dss::Fix32 carpetSpeed_;                // 0x1C

        virtual int setup();
        virtual void execute();
        virtual int update();
        virtual bool search();
        void setStart();
        bool isCarpetGetOnOffAttr();
        virtual bool isGetOffAttr();
        void carpetMove();
    };

    struct FieldActionCastle : FieldActionBase {
        enum {
            CROUD_DRAW = 0,
            READY_UP = 1,
            READY_UP_END = 2,
            MOVE = 3,
            GET_DOWN = 4,
            CROWD_ERASE = 5,
            CASTLE_END = 6,
        };

        int counter_;                           // 0x10
        int counter2_;                          // 0x14
        int state_;                             // 0x18
        dss::Fix32 castleSpeed_;                // 0x1C

        virtual int setup();
        virtual void execute();
        virtual int update();
        virtual bool search();
        void setStart();
        virtual bool isGetOffAttr();
        void castleMove();
    };

    struct FieldActionDragon : FieldActionBase {
        enum {
            READY_ROLLUP = 0,
            DRAGON_READY_DOWN = 1,
            DRAGON_RIDE_ON = 2,
            DRAGON_UP = 3,
            DRAGON_UP_END = 4,
            DRAGON_MOVE = 5,
            DRAGON_DOWN = 6,
            DRAGON_GET_OFF = 7,
            DRAGON_GET_OFF2 = 8,
            DRAGON_GET_OFF_END = 9,
        };

        static const int radius_ = 0x20;

        int cx_;                                // 0x10
        int cy_;                                // 0x14
        int rad_;                               // 0x18
        int offsetx_;                           // 0x1C
        int offsety_;                           // 0x20
        int counter_;                           // 0x24
        int state_;                             // 0x28
        dss::Fix32 dragonSpeed_;                // 0x2C

        static const dss::Fix32 sq2;

        virtual int setup();
        virtual void execute();
        virtual int update();
        virtual bool search();
        void setStart();
        void directStart();
        void doragonMove(short idx);
        virtual bool isGetOffAttr();
    };

    struct FieldActionRana : FieldActionBase {
        int prevType_;                          // 0x10
        int counter_;                           // 0x14
        int change_;                            // 0x18

        virtual int setup();
        virtual void execute();
        virtual int update();
        virtual bool search();
        void start(int type);
        int isEffectEnd();
    };

    struct FieldActionTabi : FieldActionBase {
        int counter_;                           // 0x10
        int exitIndex_;                         // 0x14
        int start_;                             // 0x18

        virtual int setup();
        virtual void execute();
        virtual int update();
        virtual bool search();
        void start(int index, int flag);
        int isEffectEnd();
    };
} // namespace fld
