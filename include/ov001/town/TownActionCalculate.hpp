#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"

namespace twn
{
    struct TownActionCalculate {
        static const dss::Fix32 cos_PI_6;

        static bool IntersectRaySphere(dss::Fix32Vector3& p, dss::Fix32Vector3& d, dss::Fix32Vector3& sc, dss::Fix32 r, dss::Fix32& t, dss::Fix32Vector3& q);
        static bool crossCheck(dss::Fix32Vector3& nowPos, dss::Fix32Vector3& nextPos, dss::Fix32Vector3& target, dss::Fix32 radius);
        static void townCharaColl(dss::Fix32Vector3& nowPos, dss::Fix32Vector3& nextPos, dss::Fix32 r);
        static void townShipStageColl(dss::Fix32Vector3& nowPos, dss::Fix32Vector3& nextPos, dss::Fix32 radius, dss::Fix32 surfaceRad, dss::Fix32 preR);
        static bool checkGetDownShipAndIkada(dss::Fix32Vector3& nextPos, short dirIdx, dss::Fix32Vector3& targetPos, dss::Fix32Vector3& surfaceDir, dss::Fix32Vector3& surfacePos, dss::Fix32 downL);
        static void setAngle(char axisNo, short idx, dss::Vector3<short>& angle);
        static int townStageColl(dss::Fix32Vector3& nowPos, dss::Fix32Vector3& nextPos, dss::Fix32 r, dss::Fix32 surfaceR, dss::Fix32 objectR);
        static void getDirByIdx(short dir, dss::Fix32Vector3& vec);
        static void getVec4ByIdx(short dir, dss::Fix32Vector3& vec);
        static void getIdxByVec(short& idx, dss::Fix32Vector3& vec);
        static bool checkFarTalk(dss::Fix32Vector3& pos, int ctrSurfaceId, int searchObjectId, int searchPolyNo, dss::Fix32 len);
        static bool checkTalking(dss::Fix32Vector3& pos, short dirIdx, int searchObjectId);
        static dss::Fix32Vector3 getParamVec(unsigned char param);
        static short getIdxByParam(unsigned char param);
        static int getParamDir4ByIdx(short idx);
        static bool directionCheckByPosition(dss::Fix32Vector3& pos, dss::Fix32Vector3& target, short dirIdx, int cos);
        static void normalMove(dss::Fix32Vector3& pos, short& dirIdx, dss::Fix32 speed);
        static bool checkIkadaTalk(dss::Fix32Vector3 pos, short dirIdx, int surfaceId, int polyNo, bool flag);
        static bool checkGetOnShipAndIkada(const dss::Fix32Vector3& pos, const dss::Fix32Vector3& target, short dirIdx, dss::Fix32 length);
        static bool checkGetDownIkada(dss::Fix32Vector3& pos, short dirIdx, dss::Fix32Vector3& target);
        static bool checkLineOver(dss::Fix32Vector3& pos, dss::Fix32Vector3& line, dss::Fix32Vector3 normal);
        static int searchPairWdoor(int objectId, dss::Fix32Vector3* pos1, dss::Fix32Vector3* pos2);
    };
} // namespace twn
