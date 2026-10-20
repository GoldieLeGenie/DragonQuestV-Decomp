#pragma thumb on
#include "main/window/UnkMapPoint.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "nnsys/g3d.hpp"

int data_02101da4;
static dss::Fix32Vector3 s_pointPos[64];
static dss::Vector2<int> s_pointScreenPos[64][2];

void setProjectedPointPos(int index, dss::Fix32Vector3& pos)
{
    s_pointPos[index] = pos;
}

dss::Vector2<int>* getProjectedPointScreenPos(int index)
{
    return &s_pointScreenPos[index][getDisplayFrame() & 1];
}

extern "C" void func_02052180(void)
{
    if (data_02101da4) {
        int screen = (getDisplayFrame() & 1) ? 1 : 0;
        for (int i = 0; i < 64; i++) {
            if (func_02082a0c((VecFx32*)&s_pointPos[i], &s_pointScreenPos[i][screen].vx, &s_pointScreenPos[i][screen].vy) == -1) {
                s_pointScreenPos[i][screen].vx = -1;
                s_pointScreenPos[i][screen].vy = -1;
            }
        }
    }
}
