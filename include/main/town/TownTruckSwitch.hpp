#pragma once
#include <globaldefs.h>

namespace twn
{
    // Rail switch of the truck: the switch object and the rail object animate together
    struct TownTruckSwitch {
        int surfaceIndex_;                      // 0x00
        int switchUid_;                         // 0x04
        int switchAnim_;                        // 0x08
        int railUid_;                           // 0x0C
        int railAnim_;                          // 0x10

        void setupSwitch(int rootIndex, int switchUid, int switchAnim, int railUid, int railAnim);
        void switchRail();
    };
} // namespace twn
