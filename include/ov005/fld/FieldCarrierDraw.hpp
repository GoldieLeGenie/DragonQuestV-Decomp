#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"
#include "main/dss/Sprite2D.hpp"
#include "main/object/SpriteCharacter.hpp"

namespace fld
{
    struct SpriteShipCharacter : SpriteCharacter {
        SpriteShipCharacter();
        ~SpriteShipCharacter();
        virtual void execute();
        void setup(const char* name);
    };

    struct FieldCarrirerDraw {
        // vtable                               // 0x00
        dss::Fix32Vector3 position_;            // 0x04

        FieldCarrirerDraw();
        ~FieldCarrirerDraw();
        virtual void setup() = 0;
        virtual void cleanup() = 0;
        virtual void setRotate(unsigned int rot) = 0;
        virtual void draw(dss::Vector2<int>& pos) = 0;
        virtual void setHeight(int height);
        virtual void setShadowAlpha(unsigned char alpha);
        virtual void setOffsetXY(int x, int y);
        virtual void setHigh(int high);
        virtual void setDrawPosition(int x, int y) = 0;
        virtual void setDepth(int depth) = 0;
        virtual void setShadowWH(int w, int h) = 0;
        virtual void setDisplayEnable(int flag) = 0;
        virtual int isDisplayEnable() = 0;
        virtual void setShadowStay(int flag) = 0;
        virtual void setAnimFlag(int flag) = 0;
        virtual void setShadowFlag(int flag) = 0;
        virtual void setShadowDepth(int depth) = 0;
        void setPosition(dss::Fix32Vector3& pos);
        dss::Fix32Vector3& getPosition();
    };

    struct FieldShipDraw : FieldCarrirerDraw {
        SpriteCharacter ship_;                  // 0x010
        int ride_;                              // 0x0EC
        int offset_;                            // 0x0F0

        static SpriteShipCharacter nami_;

        FieldShipDraw();
        ~FieldShipDraw();
        void setNamiAnim(int ride);
        static void initialize();
        static void terminate();
        virtual void setup();
        virtual void cleanup();
        virtual void setRotate(unsigned int rot);
        virtual void draw(dss::Vector2<int>& pos);
        virtual void setDrawPosition(int x, int y);
        virtual void setDepth(int depth);
        virtual void setShadowWH(int w, int h);
        virtual void setDisplayEnable(int flag);
        virtual int isDisplayEnable();
        virtual void setShadowStay(int flag);
        virtual void setAnimFlag(int flag);
        virtual void setShadowFlag(int flag);
        virtual void setShadowDepth(int depth);
    };

    struct FieldCarpetDraw : FieldCarrirerDraw {
        SpriteCharacter carpet_;                // 0x010
        SpriteCharacter shadow_;                // 0x0EC
        int ride_;                              // 0x1C8
        int high_;                              // 0x1CC

        FieldCarpetDraw();
        ~FieldCarpetDraw();
        virtual void setup();
        virtual void cleanup();
        virtual void setRotate(unsigned int rot);
        virtual void draw(dss::Vector2<int>& pos);
        virtual void setHeight(int height);
        virtual void setDrawPosition(int x, int y);
        virtual void setDepth(int depth);
        virtual void setShadowWH(int w, int h);
        virtual void setDisplayEnable(int flag);
        virtual int isDisplayEnable();
        virtual void setShadowStay(int flag);
        virtual void setAnimFlag(int flag);
        virtual void setShadowFlag(int flag);
        virtual void setShadowDepth(int depth);
    };

    struct FieldFirmamentDraw : FieldCarrirerDraw {
        UnkMenuSprite kumo_;                    // 0x010
        UnkMenuSprite firmament_;               // 0x060
        UnkMenuSprite shadow_;                  // 0x0B0
        int displayEnable_;                            // 0x100 display enable
        int animFlag_;                            // 0x104 anim flag
        int frame_;                             // 0x108
        int high_;                              // 0x10C

        FieldFirmamentDraw();
        ~FieldFirmamentDraw();
        virtual void setup();
        virtual void cleanup();
        virtual void setRotate(unsigned int rot);
        virtual void draw(dss::Vector2<int>& pos);
        virtual void setHeight(int height);
        virtual void setShadowAlpha(unsigned char alpha);
        virtual void setDrawPosition(int x, int y);
        virtual void setDepth(int depth);
        virtual void setShadowWH(int w, int h);
        virtual void setDisplayEnable(int flag);
        virtual int isDisplayEnable();
        virtual void setShadowStay(int flag);
        virtual void setAnimFlag(int flag);
        virtual void setShadowFlag(int flag);
        virtual void setShadowDepth(int depth);
    };

    struct FieldDragonDraw : FieldCarrirerDraw {
        SpriteCharacter dragon_;                // 0x010
        SpriteCharacter shadow_;                // 0x0EC
        int offsetx_;                           // 0x1C8
        int offsety_;                           // 0x1CC
        int high_;                              // 0x1D0

        FieldDragonDraw();
        ~FieldDragonDraw();
        virtual void setup();
        virtual void cleanup();
        virtual void setRotate(unsigned int rot);
        virtual void draw(dss::Vector2<int>& pos);
        virtual void setOffsetXY(int x, int y);
        virtual void setHigh(int high);
        virtual void setDrawPosition(int x, int y);
        virtual void setDepth(int depth);
        virtual void setShadowWH(int w, int h);
        virtual void setDisplayEnable(int flag);
        virtual int isDisplayEnable();
        virtual void setShadowStay(int flag);
        virtual void setAnimFlag(int flag);
        virtual void setShadowFlag(int flag);
        virtual void setShadowDepth(int depth);
    };
} // namespace fld
