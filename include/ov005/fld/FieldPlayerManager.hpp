#pragma once
#include <globaldefs.h>
#include "main/cmn/PlayerManager.hpp"
#include "ov005/fld/FieldCarrierDraw.hpp"
#include "ov005/fld/FieldParty.hpp"
#include "ov005/fld/FieldPartyDraw.hpp"
#include "ov005/fld/FieldPlayer.hpp"
#include "main/status/StageAttribute.hpp"

namespace fld {
    struct FieldPlayerManager : cmn::PlayerManager {
        int walkCounter;                                // 0x0A4
        int scriptMoveFlag_;                            // 0x0A8
        FieldPlayer player_;                            // 0x0AC
        FieldParty party_;                              // 0x1DC
        FieldPartyDraw partyDraw_;                      // 0x214
        FieldShipDraw shipDraw_[2];                     // 0x934
        FieldCarpetDraw carpetDraw_;                    // 0xB1C
        FieldFirmamentDraw firmamentDraw_;              // 0xCEC
        FieldDragonDraw fieldDragonDraw_;               // 0xDFC
        dss::Fix32Vector3 targetPos_;                   // 0xFD0
        dss::Fix32 speedToTarget_;                      // 0xFDC
        dss::Fix32Vector3& position_;                   // 0xFE0
        short& dirIdx_;                                 // 0xFE4
        dss::Fix32Vector3 drawRuraOffset_;              // 0xFE8
        dss::Fix32Vector3 dummyPos_;                    // 0xFF4
        int searchMapUid_;                              // 0x1000
        int hengeCounter_;                              // 0x1004
        int mapChangeCounter_;                          // 0x1008
        short ballonCounter_;                           // 0x100C
        char ballonType_;                               // 0x100E
        int prevAction_;                                // 0x1010
        int eventEncount_;                              // 0x1014
        int dummyPosFlag_;                              // 0x1018
        int remote_;                                    // 0x101C
        int height_;                                    // 0x1020

        FieldPlayerManager();
        static FieldPlayerManager& getSingleton();
        void initialize();
        void terminate();
        void execute();
        void draw();
        void setup();
        void cleanup();
        void reload();
        void everyExec();
        void normalExec();
        bool isTenkuNearArea();
        virtual void setPosition(dss::Fix32Vector3& pos);
        dss::Fix32Vector3& getPosition();
        virtual void setDirection(short idx);
        virtual short getDirection();
        virtual void resetParty();
        virtual void resetDrawPartyCount();
        virtual void setMoveToFirstFlag();
        virtual bool getMoveToFirstFlag();
        virtual void setPartyDrawOne();
        virtual void setDrawPartyNone();
        virtual int getPartyDrawCount();
        virtual bool isEqalNextPos(int index);
        virtual char getPartyDrawAlpha(int index);
        virtual void addPartyDrawAlpha(int index, char add);
        virtual void scriptColl(dss::Fix32Vector3& nextPos, short& dirIdx);
        virtual bool checkScriptSearch();
        int getAttr();
        void setDistance();
        void inputPad(int dir);
        void inputClear();
        int getPadInput();
        int getDirInput();
        void execMapLink();
        void setRemote(bool flag);
        void checkMenuAction(int action);
        bool search();
        dq5::LandType getLandType();
        void unkfunc_02131c70();
        void setSimpleMove(dss::Fix32Vector3 target, dss::Fix32 rate, int absFlag);
        void setDirectionMove(dss::Fix32 target, int dir);
        void setScriptGetDownShip(int dir);
        void setShipPos(int index, dss::Fix32Vector3& pos);
        dss::Fix32Vector3& getShipPos(int index);
        int isEndScriptGetDownShip();
        void resetLockByEventEncount();
        void setLink(bool flag);
        FieldCarrirerDraw* getCarrierDraw(int type);
        int getMoveType();
        bool isTenkuNearAreaGetOn();
        void setHeight(int high);
        short getDirIdx();
        void setMapLink(bool flag);
        FieldShipDraw& getShipDraw(int index);
        void setShipDir(int index, short dir);
        void setNamiAnim(int index, bool flag);
        void setDrawNone();
        void setDummyPos(dss::Fix32Vector3& pos);
        void setDummyPosFlag(bool flag);
        void setAllShadow(bool flag);
        void setMoveType(int type);
        FieldPlayer& getPlayerAction();
        void changePlayerPose(int index, int charaIndex);
        void setPartyToFirst();
        int getSearchMapUid();
        unsigned short getDamageColor(int type);
        void setMemberColor(int index, unsigned short color);
    };
}
