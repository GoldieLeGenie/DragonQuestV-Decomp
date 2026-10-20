#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"

// Player points drawn over the 2D maps
void setProjectedPointPos(int index, dss::Fix32Vector3& pos);      // sets the map position of the point
dss::Vector2<int>* getProjectedPointScreenPos(int index);                 // screen position of the point (blinking)

extern "C" void func_02052180(void);                             // update the points

extern int data_02101da4;                                       // the points are shown
