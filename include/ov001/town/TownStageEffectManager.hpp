#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"
#include "main/data/DataObject.hpp"
#include "ov001/town/stage/effect/TownStageTinction.hpp"
#include "ov001/town/stage/effect/TownStageWrap.hpp"
#include "ov001/town/stage/effect/TownStageWireTrap.hpp"
#include "ov001/town/stage/effect/UnkTownSpotlight.hpp"

namespace twn {
    struct TownStageLightning {
        int frame_;                                 // 0x00
        int counter_;                               // 0x04
        int lightCounter_;                          // 0x08
        int phase_;                                 // 0x0C
        int light_;                                 // 0x10
        int dark_;                                  // 0x14
        int enable_;                                // 0x18
        DataObject unk_1c;                          // 0x1C
        DataObject unk_2c;                          // 0x2C

        TownStageLightning();
        ~TownStageLightning();
        void setup();
        void start(int first);
        void cleanup();
        void execute();
        void setEnable(bool enable);
    };

    struct TownStageNinePuzzle {
        static const int modelOffset = 500;
        static const int collisionOffset = 510;
        static const int distance_ = 0x8000;
        static const unsigned char defaultSection[3][3];

        int moveFrame_;                             // 0x00
        int phase_;                                 // 0x04
        int moveId_;                                // 0x08
        int enable_;                                // 0x0C
        int moveSection_;                           // 0x10
        int moveDirect_;                            // 0x14
        int ctrl_;                                  // 0x18

        TownStageNinePuzzle();
        ~TownStageNinePuzzle();
        void setup();
        void cleanup();
        void execute();
        bool checkMovable();
        void setSlideMove();
        void relocation(int id, int x, int z);
        void initPuzzle();
        bool checkPuzzleMove();
    };

    struct TownStageEffectManager {
        static const int MAX_TORCH = 7;

        TownStageTinction tinct_;                   // 0x000
        UnkTownSpotlight spotlight_;                // 0x024
        TownStageWrap wrap_;                        // 0x168
        TownStageLightning lightning_;              // 0x234
        TownStageNinePuzzle puzzle_;                // 0x270
        TownStageWireTrap wire_;                    // 0x28C

        TownStageEffectManager();
        ~TownStageEffectManager();
        static TownStageEffectManager* getSingleton();
        void initialize();
        void terminate();
        void execute();
        void draw();
        void loadStage();
        void setRGBRate(dss::Fix32Vector3& rate, int realTime);
        void setStopLightning(bool stop);
        void setTorchlight();
        void setSpotlight(dss::Fix32Vector3* pos);
        void clearTorchlight();
        void setLightSize(int size);
        void setLightAlpha(unsigned char alpha);
        void setBlindAlpha(unsigned char alpha);
        void setTextureScaling(fx32 scaleX, fx32 scaleY);
        void getTextureScaling(fx32& scaleX, fx32& scaleY);
        void setEffect(TownStageWrap::EFFECT_TYPE type);
        void resolveOverlapPosition();
        bool isTrap();
        bool isPuzzleMove();
        bool isMovable();
        void setDraw(int flag);
        void initPuzzle();
        void setPuzzle();
        int getCurrentBackColor();
        void setNextBackColor(int index);
        int getNextBackColor();
        dss::Fix32Vector3& getPaletteRate();
        dss::Fix32Vector3 getDefaultPaletteRate();
    };
}
