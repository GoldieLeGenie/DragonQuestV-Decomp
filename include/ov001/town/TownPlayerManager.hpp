#pragma once
#include <globaldefs.h>
#include "main/cmn/ActionBase.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/cmn/PlayerAction.hpp"
#include "main/cmn/PlayerManager.hpp"
#include "main/cmn/PartyMoveAction.hpp"
#include "main/cmn/MoveBase.hpp"
#include "main/data/DataObject.hpp"
#include "main/object/DisplayCharacter.hpp"
#include "ov001/town/player/TownActionDoor.hpp"
#include "ov001/town/player/TownActionFall.hpp"
#include "ov001/town/player/TownActionGimmick.hpp"
#include "ov001/town/player/TownActionIce.hpp"
#include "ov001/town/player/TownActionIkada.hpp"
#include "ov001/town/player/TownActionKaidan.hpp"
#include "ov001/town/player/TownActionKaifuku.hpp"
#include "ov001/town/player/TownActionRanaruta.hpp"
#include "ov001/town/player/TownActionRiremito.hpp"
#include "ov001/town/player/TownActionRope.hpp"
#include "ov001/town/player/TownActionRura.hpp"
#include "ov001/town/player/TownActionRuraFailed.hpp"
#include "ov001/town/player/TownActionShip.hpp"
#include "ov001/town/player/TownActionSube.hpp"
#include "ov001/town/player/TownActionTabi.hpp"
#include "ov001/town/player/TownActionTruck.hpp"
#include "ov001/town/player/TownActionWalk.hpp"

namespace twn {
    enum TOWN_PLAYER_ACTION_TYPE {
        ACTION_TYPE_WALK = 0,
        ACTION_TYPE_ROPE = 1,
        ACTION_TYPE_SUBE = 2,
        ACTION_TYPE_FALL = 3,
        ACTION_TYPE_BUMP = 4,
        ACTION_TYPE_KAIDAN = 5,
        ACTION_TYPE_FRAME_MOVE = 6,
        ACTION_TYPE_FRAME_ROT = 7,
        ACTION_TYPE_SHIP = 8,
        ACTION_TYPE_IKADA = 9,
        ACTION_TYPE_DOOR = 10,
        ACTION_TYPE_RURA = 11,
        ACTION_TYPE_RURA_FAILED = 12,
        ACTION_TYPE_RANARUTA = 13,
        ACTION_TYPE_RIREMITO = 14,
        ACTION_TYPE_KAIFUKU = 15,
        ACTION_TYPE_TABI = 16,
        ACTION_TYPE_SORATOBU = 17,
        ACTION_TYPE_ICE = 18,
        ACTION_TYPE_TRUCK = 19,
        ACTION_TYPE_GIMMICK = 20,
        ACTION_TYPE_LAST = 20,
    };

    enum CAMERA_ROT_TYPE {
        ROT_NONE = 0,
        ROT_TO_R = 1,
        ROT_TO_L = 2,
        ROT_TO_NORTH = 3,
        ROT_TO_NORTH_END = 4,
        ROT_TO_NORTH_FREE = 5,
    };

    enum EXIT_LOCK_TYPE {
        EXIT_LOCK_DOOR = 1,
        EXIT_LOCK_KAIDAN = 2,
        EXIT_LOCK_TABI = 4,
        EXIT_LOCK_RURA = 8,
    };

    enum RESET_EXIT_LOCK_TYPE {
        RESET_EXIT_LOCK_DOOR = 1,
        RESET_EXIT_LOCK_KAIDAN = 2,
        RESET_EXIT_LOCK_TABI = 4,
        RESET_EXIT_LOCK_RURA = 8,
        RESET_EXIT_ALL = -1,
    };

    struct TownPlayerAction : cmn::PlayerAction {
        TOWN_PLAYER_ACTION_TYPE actionType_;    // 0x000C
        TOWN_PLAYER_ACTION_TYPE prevType_;      // 0x0010
        cmn::ActionBase* action_[21];           // 0x0014
        int allShadowReset_;                    // 0x0068
        char charaShadowStay_[8];               // 0x006C
        TownActionWalk townActionWalk_;         // 0x0074
        TownActionDoor townActionDoor_;         // 0x00C4
        TownActionFall townActionFall_;         // 0x01AC
        TownActionIkada townActionIkada_;       // 0x01DC
        TownActionKaidan townActionKaidan_;     // 0x0210
        TownActionSube townActionSube_;         // 0x02E8
        TownActionRope townActionRope_;         // 0x0328
        TownActionShip townActionShip_;         // 0x0344
        TownActionRura townActionRura_;         // 0x03B8
        TownActionRuraFailed townActionRuraFailed_; // 0x03DC
        TownActionRanaruta townActionRanaruta_; // 0x0408
        TownActionRiremito townActionRiremito_; // 0x0414
        TownActionTabi townActionTabi_;         // 0x041C
        TownActionKaifuku townActionKaifuku_;   // 0x042C
        TownActionIce townActionIce_;           // 0x0434
        TownActionTruck townActionTruck_;       // 0x0450
        TownActionGimmick townActionGimmick_;   // 0x1200

        static const dss::Fix32 collR;
        static const dss::Fix32 surfaceR;
        static const dss::Fix32 rageSurfaceR;
        static const dss::Fix32 objectR;
        static const dss::Fix32 fixR;
        static const dss::Fix32 kaidanR;
        static const dss::Fix32 walkSpeed;
        static const dss::Fix32 ropeSpeed;
        static const dss::Fix32 getOnOffSpeed;
        static const dss::Fix32 fallH;
        static const dss::Fix32 bumpH;
        static const dss::Fix32 shipR;
        static const dss::Fix32 ikadaR;
        static const dss::Fix32 getDownL;
        static const dss::Fix32 shipSpeed;
        static const dss::Fix32 ruraSpeed;
        static const dss::Fix32 shipCtrLen;
        static const dss::Fix32 walkCtrLen;
        static const dss::Fix32 talkR;
        static const dss::Fix32 talkRR;
        static const dss::Fix32 townCharaR;
        static const dss::Fix32 townCharaPreR;
        static const dss::Fix32 changePreR;
        static const dss::Fix32 shipCollR;
        static const dss::Fix32 collRR;
        static const dss::Fix32 coll2RR;

        int getPadInput();
        void setActionType(TOWN_PLAYER_ACTION_TYPE type);
        int getDirInput();
        TownPlayerAction();
        ~TownPlayerAction();
        void setup();
        void cleanup();
        void execute();
        void update();
        virtual void execMove();
        virtual void execCollision();
    };

    struct TownPartyDraw {
        static const int PARTY_MAX = 8;

        DisplayCharacter partyCharacter_[8];    // 0x0000
        DisplayCharacter separateChara_[5];     // 0x1560
        int separateCharaCount_;                // 0x22BC
        DisplayCharacter taimatsu_;             // 0x22C0
        int count_;                             // 0x256C
        int countReal_;                         // 0x2570
        char partyDispAlpha_[8];                // 0x2574
        short charaIndex_[8];                   // 0x257C
        int exe_;                               // 0x258C
        int taimatsuFlag_;                      // 0x2590
        int taimatsuSetup_;                     // 0x2594
        DataObject dataObject_[8];              // 0x2598

        static const unsigned short colorDoku;
        static const unsigned short colorBarrier;
        static const unsigned short colorYogan;

        TownPartyDraw();
        ~TownPartyDraw();
        void setBashaDraw();
        void setup();
        void separateSetup();
        void separatePos();
        void cleanup();
        void draw();
        void setPosition(int ctrl, const dss::Fix32Vector3& pos);
        void setRotate(int index, int dirIdx);
        void resetAlpha();
        void resetDrawPartyCount();
        void setDrawPartyOne();
        bool isPartyDrawNone();
        void setDrawPartyNone();
        void setAnimationOne(int flag);
        void setAnimation(int flag);
        void setWriggleCharacter(int flag);
        void setWriggleCharaAll(int flag);
        void setAlpha(int index, char value);
        void addAlpha(int index, char value);
        void execute();
        void setExcute(bool flag);
        void changePose(int playerIndex, int set);
        void setMemberShadow(int index, int flag);
        void setPlayerSize(int index, int charaIndex);
        void setSleep(int flag);
        void requestCharacterReload();
        void setVanAndBasha();
        void setMemberColor(int index, unsigned short color);
        int getMemberCharaIndex(int i);
        void setHueChange(int index, int type, int frame);
    };

    enum SPEED_TYPE {
        SPEED_DEFALUT = 0,
        SPEED_TYPE1 = 1,
        SPEED_TYPE2 = 2,
    };

    struct TownPartyAction : cmn::PartyMoveAction {
        enum {
            START_ALPHA_CHANGE = 0,
            ALPHA_CHANGING = 1,
        };

        short counter_;                         // 0x02A
        int changeAlpha_;                       // 0x02C
        int half_;                              // 0x030
        int script_;                            // 0x034
        int fixFlag_;                           // 0x038
        dss::Fix32Vector3 temp[8];              // 0x03C
        int partyAlphaFlag_[8];                 // 0x09C
        cmn::MoveBase partyMove_[8];            // 0x0BC
        int distanceCount_;                     // 0x33C

        void setup();
        void cleanup();
        virtual void execute();
        void resetFixPos();
        virtual int getMemberCount();
        virtual const dss::Fix32Vector3& getMemberPos(int index);
        virtual short getMemberDir(int index);
        void setPosition();
        void setAllPotition(dss::Fix32Vector3& pos);
        int getDrawCount();
        bool isEqalNextPos(int index);
        void setMemberJump(int index);
        void setFormation(dss::Fix32Vector3& dirVec, short dirIdx, dss::Fix32 speed);
        void formationMoveUpdate();
        bool isFormationEnd();
        void setMoveToFirstHalfSpeed(SPEED_TYPE flag);
        bool getMoveFirstFlag();
        void setMoveFirstFlag(bool flag);
    };

    struct TownPlayerManager : cmn::PlayerManager {
        TownPartyDraw partyDraw_;               // 0x00A4
        TownPlayerAction player_;               // 0x26BC
        TownPartyAction party_;                 // 0x3B30
        int flagIdoLink_;                       // 0x3E70
        int exitLock_;                          // 0x3E74
        int execFlag_;                          // 0x3E78
        int remoteFlag_;                        // 0x3E7C
        int rotLock_;                           // 0x3E80
        int scriptType_;                        // 0x3E84
        int searchMapUid_;                      // 0x3E88
        char frmDir_;                           // 0x3E8C
        char charDir_;                          // 0x3E8D
        short frmDirIdx_;                       // 0x3E8E
        int idoMess_;                           // 0x3E90
        int tabiLink_;                          // 0x3E94
        CAMERA_ROT_TYPE cameraLot_;             // 0x3E98
        CAMERA_ROT_TYPE prev_cameraLot_;        // 0x3E9C
        int allShadowReset_;                    // 0x3EA0
        int shadowSet_;                         // 0x3EA4
        int mapChangeSE_;                       // 0x3EA8
        int txCounter_;                         // 0x3EAC
        int scriptRotFlag_;                     // 0x3EB0
        int scriptColl_;                        // 0x3EB4
        int riseupIndex_;                       // 0x3EB8
        int searchAction_;                      // 0x3EBC
        int wait_;                              // 0x3EC0
        unsigned int walkCounter_;              // 0x3EC4
        int defaultClip_;                       // 0x3EC8
        int effectPosFlag_;                     // 0x3ECC
        dss::Fix32Vector3 effectPos_;           // 0x3ED0
        dss::Fix32Vector3 flPos;                // 0x3EDC
        short flIdx;                            // 0x3EE8
        int link_;                              // 0x3EEC
        int playExitSE_;                        // 0x3EF0
        int defaultSELock_;                     // 0x3EF4
        int scriptPlayer_;                      // 0x3EF8
        int uid1_;                              // 0x3EFC
        int uid2_;                              // 0x3F00
        int objMoveUid_;                        // 0x3F04
        dss::Fix32Vector3 objMovePos_;          // 0x3F08

        TownPlayerManager();
        static TownPlayerManager& getSingleton();
        virtual void setPosition(dss::Fix32Vector3& pos);
        virtual dss::Fix32Vector3& getPosition();
        virtual short getDirection();
        virtual void setDirection(short idx);
        virtual void resetParty();
        virtual void resetDrawPartyCount();
        virtual void resetAlpha();
        virtual void setMoveToFirstFlag();
        virtual bool getMoveToFirstFlag();
        virtual void setPartyDrawOne();
        virtual void setDrawPartyNone();
        virtual int getPartyDrawCount();
        virtual char getPartyDrawAlpha(int index);
        virtual void addPartyDrawAlpha(int index, char a);
        virtual bool isEqalNextPos(int index);
        virtual void scriptColl(dss::Fix32Vector3& nextPos, short& dirIdx);
        virtual bool checkScriptSearch();
        void initialize();
        void terminate();
        void execute();
        void update();
        void draw();
        void setup();
        void cleanup();
        void unkfunc_0213d450();
        void normalExec();
        bool normalMapLink();
        bool execMapLink();
        void inputPad(int padDir);
        void setMapLink(bool flag);
        int isRemote();
        bool isLinked();
        TOWN_PLAYER_ACTION_TYPE getActionType();
        void setActionType(int type);
        void inputClear();
        void lockMapLink(EXIT_LOCK_TYPE type);
        void resetMapLink(RESET_EXIT_LOCK_TYPE type);
        void setPartyToFirst(dss::Fix32Vector3& pos);
        void setFormation(int frmDir, int charaDir, dss::Fix32 speed);
        void setRemote(bool flag);
        bool isLock();
        void setLock(bool lock);
        void setCameraRotToNorth();
        void setCameraRot();
        void setSimpleMove(dss::Fix32Vector3& prev, dss::Fix32Vector3& next, int frame);
        void setShadowExec(bool flag);
        void setEffectPosFlag(bool flag);
        void setEffectPos(dss::Fix32Vector3& pos);
        void setExitSE(bool flag);
        int getPadInput();
        int getDirInput();
        void setSpeedMove(dss::Fix32Vector3& prev, dss::Fix32Vector3& next, dss::Fix32 speed);
        void setJumpMove(dss::Fix32Vector3& endPos, int frame);
        int isFinish();
        void setMapObjMove(int flag, int mapUid, dss::Fix32Vector3& pos);
        void setCameraRotType(int type);
        bool isIdoLinkPos();
        unsigned short getDamageColor(int type);
        void setShadow();
        void setMenuAction(int type);
        void scriptExecute();
        void setScriptRot(int frame, short idx, int flag);
        void setStartEraseParty();
        void rizeupSet(int icon);
        bool rizeupEnd();
        int getInpasMapObj();
        bool getPlayerCopyInfo(int playerNo, dss::Fix32Vector3& pos, short& idx, int& charNo);
        void setIkadaSpeedMove(dss::Fix32Vector3& prev, dss::Fix32Vector3& next, dss::Fix32 speed);
        void setIkadaFrameMove(dss::Fix32Vector3& prev, dss::Fix32Vector3& next, int frame);
        void setIkadaMove();
        void rizeupSetParty(int charaNo, int markNo);
        void setVanAndBasha();
        bool isSaveAndBattleOK();
        bool checkSearchMapObj(bool searchFlag);
        bool checkIdo();
        bool checkTalkToCharacter();
        int getSearchMapUid();
        void setSearchMapUid(int uid);
        void setScriptSearchRange(int uid1, int uid2);
        void setLockRot(int flag);
        void setScriptColl(int scriptColl);
        void removeScriptColl(int scriptColl);
        void setAnimationOne(int flag);
        void setAnimation(int flag);
        void setPlayExitSE(bool flag);
        void setWriggleCharacter(int flag);
        void setSleep(int flag);
        void setScriptPlayer(int flag);
        bool isEndScriptRot();
        int isFormationEnd();
        bool isMapObjBackSide(int uid);
        void scriptTruckAction();
        void setDistance();
        TownPartyAction& getPartyAction();
        void changePlayerPose(int index, int set);
        void setMemberColor(int index, unsigned short color);
    };
}
