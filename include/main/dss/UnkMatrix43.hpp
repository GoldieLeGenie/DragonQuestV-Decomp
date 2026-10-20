#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"

namespace dss {
    // 4x3 fixed-point matrix (identity when constructed)
    struct UnkMatrix43 : MtxFx43 {
        UnkMatrix43();
        void setIdentity();                // identity
        UnkMatrix43& operator=(const UnkMatrix43& o);
        UnkMatrix43 operator*(const UnkMatrix43& o) const;
        Fix32Vector3 operator*(const Fix32Vector3& v) const;
        void setRotX(short angle);     // rotation around X
        void setRotY(short angle);     // rotation around Y
        void setRotZ(short angle);     // rotation around Z
    };
}
