#pragma once
#include "main/fld/Coll.hpp"

// copy of the collision functions linked in the slime race overlay
namespace race {

int coll_init(COLL_HEADER* header, NNSFndAllocator* allocator);
fx32 coll_GetCrossPoint3D(VecFx32* point, VecFx32* vertex, VecFx32* normal, VecFx32* cross);
int coll_CheckPolyPointOne(COLL_POLY* poly, VecFx32* point);
int coll_CheckPolyPoint(COLL_POLY* poly, VecFx32* point);
int coll_CheckLinePoint(const VecFx32* posP, fx32 r, const VecFx32* posA, const VecFx32* posB, const VecFx32* nml, VecFx32* cross);
int coll_CheckWallId(COLL_HEADER* header, VecFx32* center, fx32 r);
int coll_GetCollLinePosL(COLL_LINE* line, int size, short val);
int coll_GetCollLinePosG(COLL_LINE* line, int size, short val);
int coll_PreSearchFloorPoly(COLL_HEADER* header, VecFx32* point);
int coll_SearchFloorPoly(COLL_HEADER* header, VecFx32* point, fx32 height, VecFx32* ret);

}  // namespace race
