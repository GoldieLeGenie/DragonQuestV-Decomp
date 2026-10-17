#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"

namespace twn
{
    struct TownFurnitureControlBase {
        enum {
            FURNITURE_MOVE = 0,
            FURNITURE_MOVE2 = 1,
            FURNITURE_FADE = 2,
            FURNITURE_ROTATE = 3,
            FURNITURE_GROUP_MOVE = 4,
            FURNITURE_GROUP_ROTATE = 5,
        };

        static const int FLAG_GARBAGE_CORRECT = 1;

        // vtable                               // 0x00
        int counter_;                           // 0x04
        int frame_;                             // 0x08
        int uid_;                               // 0x0C
        int enable_;                            // 0x10
        dss::BitFlag<unsigned char> flag_;      // 0x14

        TownFurnitureControlBase();
        ~TownFurnitureControlBase();
        virtual void execute();
        virtual int getType() = 0;
        virtual void setup(int uid, int frame);
        virtual void cleanup();
        virtual void setFurnitureMove(int uid, int frame, dss::Fix32Vector3& start, dss::Fix32Vector3& goal);
        virtual void setFurnitureFade(int uid, int frame, int fade, int priority);
        virtual void setFurnitureRotate(int uid, int frame, dss::Fix32Vector3& start, dss::Fix32Vector3& goal);
        virtual void setFurnitureGroupMove(int group, int frame, dss::Fix32Vector3& speed);
        virtual void setFurnitureGroupRotate(int group, int frame, dss::Fix32Vector3& speed);
        virtual bool isEnd();
        void setGarbageCorrect(bool flag);
        bool isGarbageCorrect();
    };

    struct TownFurnitureControlFade : TownFurnitureControlBase {
        int fade_;                              // 0x18
        int priority_;                          // 0x1C

        TownFurnitureControlFade();
        ~TownFurnitureControlFade();
        virtual void execute();
        virtual int getType();
        virtual void cleanup();
        virtual void setFurnitureFade(int uid, int frame, int fade, int priority);
    };

    struct TownFurnitureControlMove : TownFurnitureControlBase {
        dss::Fix32Vector3 start_;               // 0x18
        dss::Fix32Vector3 goal_;                // 0x24

        TownFurnitureControlMove();
        ~TownFurnitureControlMove();
        virtual void execute();
        virtual int getType();
        virtual void cleanup();
        virtual void setFurnitureMove(int uid, int frame, dss::Fix32Vector3& start, dss::Fix32Vector3& goal);
    };

    struct TownFurnitureControlMove2 : TownFurnitureControlBase {
        dss::Fix32Vector3 start_;               // 0x18
        dss::Fix32Vector3 goal_;                // 0x24

        TownFurnitureControlMove2();
        ~TownFurnitureControlMove2();
        virtual void execute();
        virtual int getType();
        virtual void cleanup();
    };

    struct TownFurnitureControlRotate : TownFurnitureControlBase {
        dss::Fix32Vector3 start_;               // 0x18
        dss::Fix32Vector3 goal_;                // 0x24

        TownFurnitureControlRotate();
        ~TownFurnitureControlRotate();
        virtual void execute();
        virtual int getType();
        virtual void cleanup();
        virtual void setFurnitureRotate(int uid, int frame, dss::Fix32Vector3& start, dss::Fix32Vector3& goal);
    };

    struct TownFurnitureGroupMove : TownFurnitureControlBase {
        dss::Fix32Vector3 diff_;                // 0x18

        TownFurnitureGroupMove();
        ~TownFurnitureGroupMove();
        virtual void execute();
        virtual int getType();
        virtual void cleanup();
        virtual void setFurnitureGroupMove(int group, int frame, dss::Fix32Vector3& speed);
    };

    struct TownFurnitureGroupRotate : TownFurnitureControlBase {
        dss::Fix32Vector3 diff_;                // 0x18

        TownFurnitureGroupRotate();
        ~TownFurnitureGroupRotate();
        virtual void execute();
        virtual int getType();
        virtual void cleanup();
        virtual void setFurnitureGroupRotate(int group, int frame, dss::Fix32Vector3& speed);
    };

    struct TownFurnitureControlStorage {
        static const unsigned int FURNITURE_MOVE_MAX = 8;
        static const unsigned int FURNITURE_FADE_MAX = 16;
        static const unsigned int FURNITURE_MOVE2_MAX = 8;
        static const unsigned int FURNITURE_ROTATE_MAX = 8;
        static const unsigned int FURNITURE_GROUP_MOVE_MAX = 8;
        static const unsigned int FURNITURE_GROUP_ROTATE_MAX = 8;

        TownFurnitureControlMove move_[FURNITURE_MOVE_MAX];                         // 0x000
        TownFurnitureControlFade fade_[FURNITURE_FADE_MAX];                         // 0x180
        TownFurnitureControlMove2 move2_[FURNITURE_MOVE2_MAX];                      // 0x380
        TownFurnitureControlRotate rotate_[FURNITURE_ROTATE_MAX];                   // 0x500
        TownFurnitureGroupMove groupMove_[FURNITURE_GROUP_MOVE_MAX];                // 0x680
        TownFurnitureGroupRotate groupRotate_[FURNITURE_GROUP_ROTATE_MAX];          // 0x7A0
        int fadeCounter_;                                                           // 0x8C0
        int moveCounter_;                                                           // 0x8C4
        int moveCounter2_;                                                          // 0x8C8
        int rotateCounter_;                                                         // 0x8CC
        int groupMoveCounter_;                                                      // 0x8D0
        int groupRotateCounter_;                                                    // 0x8D4

        TownFurnitureControlStorage();
        ~TownFurnitureControlStorage();
        void initialize();
        void terminate();
        TownFurnitureControlBase* getContainer(int type);
        void restoreContainer(int type);
    };

    struct TownFurnitureControlManager {
        static const int FURNITURE_CONTOROL_MAX = 24;

        TownFurnitureControlStorage storage_;                                       // 0x000
        TownFurnitureControlBase* furnControl_[FURNITURE_CONTOROL_MAX];            // 0x8D8

        static int furnitureCounter_;

        TownFurnitureControlManager();
        ~TownFurnitureControlManager();
        static TownFurnitureControlManager& getSingleton();
        void initialize();
        void terminate();
        void execute();
        bool isEnd(int index);
        int setFurnitureMove(int uid, int frame, dss::Fix32Vector3& goal);
        int setFurnitureFade(int uid, int frame, int fade, int priority);
        int setFurnitureRotate(int uid, int frame, dss::Fix32Vector3& goal);
        int setFurnitureGroupMove(int group, int frame, dss::Fix32Vector3& speed);
        int setFurnitureGroupRotate(int group, int frame, dss::Fix32Vector3& speed);
        void cleanup(int index);
        void setGarbageCorrect(int index, bool flag);
        bool isGarbageCorrect(int index);
    };
} // namespace twn
