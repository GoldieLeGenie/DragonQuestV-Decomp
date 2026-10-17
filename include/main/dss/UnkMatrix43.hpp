#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"

namespace dss {
    // 4x3 fixed-point matrix (identity when constructed)
    struct UnkMatrix43 : MtxFx43 {
        UnkMatrix43();
        void unkfunc_0204f428();                // identity
        UnkMatrix43& operator=(const UnkMatrix43& o);
        UnkMatrix43 operator*(const UnkMatrix43& o) const;
        Fix32Vector3 operator*(const Fix32Vector3& v) const;
        void unkfunc_0204f4b4(short angle);     // rotation around X
        void unkfunc_0204f4ec(short angle);     // rotation around Y
        void unkfunc_0204f524(short angle);     // rotation around Z
    };
}
