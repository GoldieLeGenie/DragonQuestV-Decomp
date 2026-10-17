#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"
#include "main/data/DataObject.hpp"
#include "main/fld/FLDObject.hpp"
#include "main/fld/Coll.hpp"

// tells which map objects are animated (their walls are always searchable)
struct UnkFldAnimObjectCheck {
    virtual bool isAnimObject(fld::FLDObject* fld, int objectId) = 0;
};

struct FldCollision {
    DataObject* coll_;                          // 0x000 collision file
    fld::FLDObject* g_fld;                      // 0x004
    int* collisionFlag_;                        // 0x008
    int id_;                                    // 0x00C
    int exitType_;                              // 0x010
    int polyIndex_;                             // 0x014
    int polyIndexBak_;                          // 0x018
    int floorPolygonNo_;                        // 0x01C
    int surfaceType_[22];                       // 0x020
    int surfacePolyNo_[22];                     // 0x078
    int eraseSurfaceId_[15];                    // 0x0D0
    int eraseCheckSurface_[15];                 // 0x10C
    int eraseSurfaceCount_;                     // 0x148
    int eraseCheckCount_;                       // 0x14C
    int searchObjectId_;                        // 0x150
    int searchPolyNo_;                          // 0x154
    int floorSurfaceId_;                        // 0x158
    int floorMapUid_;                           // 0x15C
    dss::Fix32 searchLen2;                      // 0x160
    dss::Fix32 surfaceLen;                      // 0x164
    COLL_POLY* nextList[30];                    // 0x168
    int collPolyNo[30];                         // 0x1E0
    int collCount;                              // 0x258
    int crossCount;                             // 0x25C
    short playerIdx_;                           // 0x260
    dss::Fix32Vector3 playerDir_;               // 0x264
    fx32 newX;                                  // 0x270
    fx32 newY;                                  // 0x274
    fx32 newZ;                                  // 0x278
    fx32 preR;                                  // 0x27C
    fx32 radB;                                  // 0x280
    fx32 radS;                                  // 0x284
    VecFx32 dirVec32;                           // 0x288
    dss::Fix32 dot_;                            // 0x294
    int playerDirFlag_;                         // 0x298
    UnkFldAnimObjectCheck* animObjectCheck_;    // 0x29C

    FldCollision();
    ~FldCollision();
    static int getCollisionTick();
    bool setExitPosition(dss::Fix32Vector3* pos, int index);
    dss::Fix32Vector3 compute(dss::Fix32Vector3& oldPos, dss::Fix32Vector3& newPos, dss::Fix32 radius, dss::Fix32 surfaceR, dss::Fix32 preR, dss::Fix32& height);
    void computeCollFloor(dss::Fix32Vector3& pos, dss::Fix32 radius, dss::Fix32Vector3& fixYPos);
    void searchClear();
    void computeCollWall(const dss::Fix32Vector3& oldPos, const dss::Fix32Vector3& newPos, dss::Fix32 collRad, dss::Fix32 searchRad, dss::Fix32 preRad, dss::Fix32Vector3& retPos);
    bool checkSignPoly(const dss::Fix32Vector3& newPos, dss::Fix32Vector3& cross, int polyNo, COLL_POLY* poly);
    int characterColl(dss::Fix32Vector3& oldPos, dss::Fix32Vector3& newPos, dss::Fix32 radius, dss::Fix32Vector3* retPos, int type);
    int getSearchObjectId();
    int getSearchPolyNo();
    int boxCompute(dss::Fix32Vector3& nowPos, dss::Fix32Vector3& nextPos, dss::Fix32 rad, dss::Fix32Vector3* retVec);
    bool checkCrossPolygon(VecFx32& pos, VecFx32& pos1, int polyNo);
    int getSurfaceByType(int type);
    int checkCrossNum(VecFx32& pos0, VecFx32& pos1, int notFloor);
    int checkCrossNumCheckUnder(VecFx32& pos0, VecFx32& pos1, int notFloor);
    int checkCrossNumEraseSurface(VecFx32 pos0, VecFx32 pos1, int surface, int notFloor, int& polyNo);
    bool getObjectPos(int objectID, int polyNo, dss::Fix32Vector3* pos);
    void searchFloorSurface(dss::Fix32Vector3& pos, dss::Fix32 radius, dss::Fix32 judgeLen, dss::Fix32Vector3& retVec);
    bool isAnimObject(int objectId);
    void setEraseSurface(int surfaceId, bool flag);
    int getFloorMapUid();
    int getSurfacePolyNoByType(int type);
    int getFloorPolygonNo();
    void clearSurfaceByType(int type);
    void setHitSurfaceByType(int type, int id);
    int getFloorSurfaceId();
    int getCollID();
    void resetEraseSurface();
    bool isEraseSurfaceId(int surfaceId);
    void wallPolyCheck(const dss::Fix32Vector3& newPos, COLL_POLY* poly, int start, int count);
    int getFrontPoly(int polyNo, int objNo);
    bool isEraseHitSurface(int surfaceId);
};
