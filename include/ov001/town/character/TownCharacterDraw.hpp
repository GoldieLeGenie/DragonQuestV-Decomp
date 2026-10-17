#pragma once
#include <globaldefs.h>
#include "ov001/town/character/TownCharacterBase.hpp"
#include "main/object/DisplayCharacter.hpp"
#include "main/data/DataObject.hpp"

namespace twn {
    struct TownCharacterDraw : TownCharacterBase {
        DisplayCharacter character_;            // 0x15C
        DataObject dataObject_;                 // 0x408

        TownCharacterDraw();
        ~TownCharacterDraw();
        virtual void setup(TOWN_CHARACTER& chara);
        virtual void execute();
        virtual void cleanup();
        virtual void setDir(int dir);
        virtual int getDir();
        virtual void draw();
        virtual void setDisplay(int flag);
        virtual int isDisplay();
        virtual void setShadow(int flag);
        virtual void setAnimation(int flag);
        virtual void setNearCharacter(int flag);
        virtual void setWriggleCharacter(int flag);
        virtual void setPosition(dss::Fix32Vector3& pos);
        virtual void setSleepCharacter(int flag);
        virtual void changePose(int set);
        virtual void restorePose();
        virtual void setPaletteRate(dss::Fix32 r, dss::Fix32 g, dss::Fix32 b);
        virtual bool isEndPalletRate();
        virtual void setShadowOnly(int flag);
        virtual void setHueChange(int type, int frame);
        virtual bool isHueChange();
        virtual void setColor(unsigned char r, unsigned char g, unsigned char b);
        virtual void setRotation(unsigned short rot);
        virtual void requestReload();
        virtual unsigned char getAlpha();
        virtual void setAlpha(unsigned char alpha);
    };
}
