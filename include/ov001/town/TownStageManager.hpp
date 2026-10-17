#pragma once
#include <globaldefs.h>
#include "main/fld/FldStage.hpp"
#include "main/fld/FldCollision.hpp"
#include "ov001/town/stage/MapObjectAnimation.hpp"

namespace twn
{
    // Tells the stage collision which map objects are animated (common ids 0x1130-0x113C)
    struct UnkTownAnimObjectCheck : UnkFldAnimObjectCheck {
        virtual bool isAnimObject(fld::FLDObject* fld, int objectId);
    };

    struct TownStageManager {
        static const int ANIM_OBJ_COUNT = 4;

        FldStage stage_;                        // 0x000
        FldCollision coll_;                     // 0x8C0
        UnkTownAnimObjectCheck animObjectCheck_; // 0xB60
        int renderDraw_;                        // 0xB64
        int sugoroku_;                          // 0xB68
        int allocFlag_;                         // 0xB6C
        int softEraseObjId_[4];                 // 0xB70
        int softEraseNum_;                      // 0xB80
        int stopScript_;                        // 0xB84
        MapObjectAnimation mapObjectAnim_[4];   // 0xB88

        TownStageManager();
        ~TownStageManager();
        static TownStageManager* getSingleton();
        void initialize();
        void terminate();
        void execute();
        void draw();
        void setMainCameraFlag(bool flag);
        void SetRGBRate(dss::Fix32Vector3& rate, int real_time);
        void setRotObjectUid(int uid, dss::Fix32Vector3& angle);
        int getFloorMapUid();
        int getWallCollId();
        int getCollPolyByPolyNo(int polyNo, COLL_POLY* coll);
        void eraseCollision(int objectID);
        void resetCollision(int objectID);
        void SetBBoxFar(dss::Fix32 val);
        void addMapGroupPosFX32(int gid, dss::Fix32Vector3& newPos);
        void addMapGroupRotFX32(int gid, dss::Fix32Vector3& newRot);
        void pause(int flag);
        bool isStageExist(char* name);
        dss::Fix32Vector3 compute(dss::Fix32Vector3& oldPos, dss::Fix32Vector3& newPos, dss::Fix32 r, dss::Fix32 searchSurface, dss::Fix32 preR, dss::Fix32& height);
        int getLinkMapNameId();
        bool setExitPosition(dss::Fix32Vector3* pos, int index);
        dss::Fix32Vector3 getMapUidPos(int uid);
        dss::Fix32Vector3 getMapUidRot(int uid);
        void addMapUidPosFX32(int uid, dss::Fix32Vector3& pos);
        void setMapUidPosFX32(int uid, dss::Fix32Vector3& pos);
        dss::Fix32Vector3 getRiseupPos(int uid, int type);
        void setObjectDraw(int id, int num, int flag);
        int getObjectIDfromMapUid(int uid);
        void rotObjectUid(int uid, short angle);
        void eraseSurface(int id);
        void resetSurface(int id);
        bool addBoxCollision(dss::Fix32Vector3& center, short dir, dss::Fix32Vector3& vec, int& extraId);
        dss::Fix32 getDiagonalLength(int polyNo);
        dss::Fix32Vector3 getSurfaceDir(int surfaceId);
        bool checkCrossPolygon(dss::Fix32Vector3 pos0, dss::Fix32Vector3 pos1, int polyNo);
        int checkCrossNumCheckUnder(dss::Fix32Vector3& start, dss::Fix32Vector3& end, bool flag);
        int checkCrossNum(dss::Fix32Vector3& start, dss::Fix32Vector3& end, bool flag);
        int checkCrossNumEraseSurface(dss::Fix32Vector3& start, dss::Fix32Vector3& end, int mask, int flag, int& polyNo);
        bool getSearchPolyDirection(dss::Fix32Vector3& dir);
        bool getPolyDirection(dss::Fix32Vector3& dir, int polyNo);
        int getHitSurfaceIdByType(int type);
        dss::Fix32Vector3 getHitSurfaceDirByType(int type);
        void setSoftErase(int objectId);
        void execSoftErase();
        bool isEndSoftErase(int objectId);
        dss::Fix32Vector3 getHitSurfacePosByType(int type);
        int getExitIndex();
        bool isPolyFacePosition(int polyNo, dss::Fix32Vector3& playerPos);
        bool isPolyFacePosition(int polyNo, dss::Fix32Vector3& playerPos, dss::Fix32 len);
        bool getObjectPos(int objectID, int polyNo, dss::Fix32Vector3* pos);
        void addMovePosByObjNo(int objNo, dss::Fix32Vector3& oldPos, dss::Fix32Vector3& newPos);
        int getCrossPolygonOtherSurface(dss::Fix32Vector3& start, dss::Fix32Vector3& end, int* surface, int count, int& polyNo, dss::Fix32* dist, int all);
        void collEraseMapUid(int id);
        void startMapObjAnimRegist(int uid);
        bool setMapObjAnimRegist(int uid, int no);
        void execObjectAnimPlay();
        static float getRadius();
        static void setRadius(float r);
        VecFx32* GetCameraPosFX32(int no);
        VecFx32* GetCameraCentFX32(int no);
        VecFx32* GetCameraUpFX32(int no);
        void setMapUidAlpha(int uid, int alpha, int flag);
        int IsCommonAnimationEnd(int obj_uid);
        void addCollisionPosByMapUid(int uid_id, dss::Fix32Vector3& add);
        int eventAnim(int event, int objID);
        void eraseObject(int uid, int flag);
        void setBoxtestFlag(int flag);
        int characoterColl(dss::Fix32Vector3& oldPos, dss::Fix32Vector3& newPos, dss::Fix32 rad, dss::Fix32Vector3* retVec, int flag);
        int getCrossPolyNo(dss::Fix32Vector3& pos0, dss::Fix32Vector3& pos1, dss::Fix32* length, bool flag);
        int getMapObjUid(int obj_id);
        int getCommonID(int objectID);
        void setMapUidOnOff(int id, int flag);
        void collResetMapUid(int id);
        int getObjectID(int polygonNo);
        void setEraseSurface(int surfaceId, bool flag);
        bool isEraseHitSurface(int id);
        bool checkObectIn(int objectId, dss::Fix32Vector3& pos);
        void setPosByObjectID(int objID, dss::Fix32Vector3& pos);
        int collGetPolyIDbySurfaceID(int surfaceID);
        int getObjWallPolyNo(int objectId, int No);
        short getObjectRotIdx(int objectId);
        void setCommonAnimation(int objectId, int num);
        int getObjectNum();
        void setCameraNo(int no, int idx);
        void setAlpha(int id, int alpha);
        int getSurfaceByPolygonNo(int polyNo);
        bool getPolyPos(dss::Fix32Vector3* pos, int polyNo);
        int getFrontPoly(int polyNo, int objNo);
        int getHitPolyNoByType(int type);
        int getFloorPolygonNo();
        void clearHitSurfaceIdByType(int type);
        void setHitSurfaceIdByType(int type, int id);
        void searchFloorSurface(dss::Fix32Vector3& oldPos, dss::Fix32 radius, dss::Fix32 judgeLen, dss::Fix32Vector3& retVec);
        int getSearchObjectId();
        int getSearchPolyNo();
        int getFloorSurfaceId();
        void computeCollFloor(dss::Fix32Vector3& pos, dss::Fix32 rad, dss::Fix32Vector3 fixPos);
        int boxCollCompute(dss::Fix32Vector3& nowPos, dss::Fix32Vector3& nextPos, dss::Fix32 rad, dss::Fix32Vector3* retVec);
    };
} // namespace twn
