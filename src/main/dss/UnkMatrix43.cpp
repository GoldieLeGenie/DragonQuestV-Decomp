#include "main/dss/UnkMatrix43.hpp"
#include <nitro/fx/fx_trig.h>

ARM dss::UnkMatrix43::UnkMatrix43()
{
    func_02088d40(this);
}

ARM void dss::UnkMatrix43::setIdentity()
{
    func_02088d40(this);
}

ARM dss::UnkMatrix43& dss::UnkMatrix43::operator=(const UnkMatrix43& o)
{
    *(MtxFx43*)this = o;
    return *this;
}

ARM dss::UnkMatrix43 dss::UnkMatrix43::operator*(const UnkMatrix43& o) const
{
    UnkMatrix43 m;
    func_020891b4(this, &o, &m);
    return m;
}

ARM dss::Fix32Vector3 dss::UnkMatrix43::operator*(const Fix32Vector3& v) const
{
    Fix32Vector3 r;
    func_02089488((const VecFx32*)&v, this, (VecFx32*)&r);
    return r;
}

ARM void dss::UnkMatrix43::setRotX(short angle)
{
    func_02088dd0(this, FX_SinIdx((unsigned short)angle), FX_CosIdx((unsigned short)angle));
}

ARM void dss::UnkMatrix43::setRotY(short angle)
{
    func_02088df0(this, FX_SinIdx((unsigned short)angle), FX_CosIdx((unsigned short)angle));
}

ARM void dss::UnkMatrix43::setRotZ(short angle)
{
    func_02088e0c(this, FX_SinIdx((unsigned short)angle), FX_CosIdx((unsigned short)angle));
}
