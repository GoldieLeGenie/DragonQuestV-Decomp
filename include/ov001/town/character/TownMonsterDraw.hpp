#pragma once
#include <globaldefs.h>
#include "ov001/town/character/TownCharacterBase.hpp"
#include "main/object/DSSACharacter.hpp"
#include "main/dss/TextureObject.hpp"
#include "main/data/DataObject.hpp"

namespace twn {
    struct TownMonsterDraw : TownCharacterBase {
        DSSACharacter monster_;                 // 0x015C
        TextureObject texture_;              // 0x106C
        UnkFileDataObject textureData_;         // 0x10DC
        UnkFileDataObject animData_;            // 0x10EC
        int display_;                           // 0x10FC
        int defaultIndex_;                      // 0x1100

        TownMonsterDraw();
        ~TownMonsterDraw();
        virtual void setup(TOWN_CHARACTER& chara);
        virtual void cleanup();
        virtual void execute();
        virtual void draw();
        virtual void setDisplay(int flag);
        virtual int isDisplay();
        virtual void setNearCharacter(int flag);
        virtual void setAnimation(int flag);
        virtual void setPosition(dss::Fix32Vector3& pos);
        virtual void setPaletteRate(dss::Fix32 r, dss::Fix32 g, dss::Fix32 b);
        virtual void setMotion(int motion, bool flag);
        virtual bool isMotion();
        virtual void setDir(int dir);
        virtual int getDir();
        virtual void changePose(int pose);
        virtual void restorePose();
        virtual void requestReload();
        virtual void setScale(dss::Fix32 scale);
        virtual void setAlpha(unsigned char alpha);
    };
}
