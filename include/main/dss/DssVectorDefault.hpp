#pragma once
#include "main/dss/DssUtils.hpp"


namespace dss {
    template <typename T>
    inline Vector3<T>::Vector3() : vz(0L), vy(0L), vx(0L) {}
    template <typename T>
    inline Vector2<T>::Vector2() : vy(0L), vx(0L) {}
}
