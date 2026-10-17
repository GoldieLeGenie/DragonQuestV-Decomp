#pragma once
#include <globaldefs.h>
#include "main/cmn/CommonEffect.hpp"
#include "main/cmn/CommonEffectResource.hpp"
#include "main/dss/DssUtils.hpp"

namespace fld
{
    struct FieldEffectBase {
        enum {
            FIELD_SPRITE_ANIM = 0,
        };

        // vtable                               // 0x00
        int index_;                             // 0x04
        dss::Fix32Vector3 position_;            // 0x08
        int enable_;                            // 0x14

        FieldEffectBase();
        ~FieldEffectBase();
        virtual void execute();
        virtual void draw() = 0;
        virtual void setup(int index);
        virtual void cleanup();
        virtual int getType() = 0;
        virtual void setPosition(dss::Fix32Vector3 pos);
        virtual bool isFinish();
        virtual void setResource(void* resource) = 0;
    };

    struct FieldEffectSprite : FieldEffectBase {
        cmn::CommonEffectOrtho sprite_;         // 0x18

        FieldEffectSprite();
        ~FieldEffectSprite();
        virtual void execute();
        virtual void draw();
        virtual void setup(int index);
        virtual void cleanup();
        virtual int getType();
        virtual void setPosition(dss::Fix32Vector3 pos);
        virtual bool isFinish();
        virtual void setResource(void* resource);
    };

    struct FieldEffectStorage {
        static const unsigned int EFFECT_SPRITE_MAX = 16;

        FieldEffectSprite sprite_[EFFECT_SPRITE_MAX];   // 0x000
        int spriteCounter_;                             // 0xE40

        FieldEffectStorage();
        ~FieldEffectStorage();
        void initialize();
        void terminate();
        FieldEffectBase* getContainer(int type);
        void restoreContainer(int type);
    };

    struct FieldEffectManager {
        static const int EFFECT_MAX = 16;

        FieldEffectStorage effectStorage_;              // 0x0000
        cmn::CommonEffectResource effectResourece_;     // 0x0E44
        FieldEffectBase* riseup_[EFFECT_MAX];           // 0x16B4

        static int riseupCounter_;

        FieldEffectManager();
        ~FieldEffectManager();
        static FieldEffectManager& getSingleton();
        void initialize();
        void terminate();
        int setup(int type, dss::Fix32Vector3 pos);
        void cleanup(int index);
        void draw();
        void execute();
    };
} // namespace fld
