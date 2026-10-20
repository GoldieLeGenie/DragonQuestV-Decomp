#pragma once
#include <globaldefs.h>
#include "main/data/DataObject.hpp"
#include "main/object/DSSAObject.hpp"

struct TextureObject;

namespace twn
{
    struct TownFukubikiDraw {
        DataObject lotteryTextureData_;         // 0x000
        TextureObject* lotteryTexture_;      // 0x010
        DataObject lotteryAnimData_;            // 0x014
        DSSAObject2D lotteryAnim_;              // 0x024
        DataObject lotteryStopAnimData_;        // 0x0C0
        DSSAObject2D lotteryStopAnim_;          // 0x0D0
        int isEnd_;                             // 0x16C
        int enable_;                            // 0x170
        int number_;                            // 0x174
        int garagaraCounter_;                   // 0x178
        int drawCounter_;                       // 0x17C
        int seCtrl_;                            // 0x180

        TownFukubikiDraw();
        ~TownFukubikiDraw();
        static TownFukubikiDraw& getSingleton();
        void garagaraSetup(int number);
        void execute();
        void initialize();
        void setup(int number);
        void cleanup();
        void terminate();
        void draw();
    };
} // namespace twn
