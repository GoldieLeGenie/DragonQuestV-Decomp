#pragma once
#include <globaldefs.h>
#include "main/dss/GameSystemManager.hpp"
#include "main/dss/Render.hpp"
#include "ov001/town/main/system/TownSystemCommand.hpp"

namespace twn
{
    // clears and draws the town 3D render same as dragon quest 4
    struct UnkTownSystemRender : Render, args::GameSystem {
        ~UnkTownSystemRender();

        virtual void initialize();
        virtual void terminate();
        virtual void execute();
        virtual void draw();
    };

    struct TownSystemMenu : args::GameSystem {
        TownSystemMenu();
        ~TownSystemMenu();
        virtual void initialize();
        virtual void terminate();
        virtual void execute();
        virtual void draw();
    };

    struct TownSystemDrawTownMap : args::GameSystem {
        TownSystemDrawTownMap();
        ~TownSystemDrawTownMap();
        virtual void initialize();
        virtual void terminate();
        virtual void execute();
        virtual void draw();
    };

    struct TownSystemDrawShopList : args::GameSystem {
        TownSystemDrawShopList();
        ~TownSystemDrawShopList();
        virtual void initialize();
        virtual void terminate();
        virtual void execute();
        virtual void draw();
    };

    struct TownSystemMaterielMenu : args::GameSystem {
        TownSystemMaterielMenu();
        ~TownSystemMaterielMenu();
        virtual void initialize();
        virtual void terminate();
        virtual void execute();
        virtual void draw();
    };

    struct TownSystemMessage : args::GameSystem {
        TownSystemMessage();
        ~TownSystemMessage();
        virtual void initialize();
        virtual void terminate();
        virtual void execute();
        virtual void draw();
    };

    struct TownSystemSugoroku : args::GameSystem {
        TownSystemSugoroku();
        ~TownSystemSugoroku();
        virtual void initialize();
        virtual void terminate();
        virtual void execute();
        virtual void draw();
    };

    struct TownSystemCamera : args::GameSystem {
        TownSystemCamera();
        ~TownSystemCamera();
        virtual void initialize();
        virtual void terminate();
        virtual void execute();
        virtual void draw();
    };

    struct TownSystemStage : args::GameSystem {
        TownSystemStage();
        ~TownSystemStage();
        virtual void initialize();
        virtual void terminate();
        virtual void execute();
        virtual void draw();
    };

    struct TownSystemStageEffect : args::GameSystem {
        TownSystemStageEffect();
        ~TownSystemStageEffect();
        virtual void initialize();
        virtual void terminate();
        virtual void execute();
        virtual void draw();
    };

    struct TownSystemFurniture : args::GameSystem {
        TownSystemFurniture();
        ~TownSystemFurniture();
        virtual void initialize();
        virtual void terminate();
        virtual void execute();
        virtual void draw();
    };

    struct TownSystemRiseup : args::GameSystem {
        TownSystemRiseup();
        ~TownSystemRiseup();
        virtual void initialize();
        virtual void terminate();
        virtual void execute();
        virtual void draw();
    };

    struct TownSystemPlayer : args::GameSystem {
        TownSystemPlayer();
        ~TownSystemPlayer();
        virtual void initialize();
        virtual void terminate();
        virtual void execute();
        virtual void draw();
    };

    struct TownSystemCharacter : args::GameSystem {
        TownSystemCharacter();
        ~TownSystemCharacter();
        virtual void initialize();
        virtual void terminate();
        virtual void execute();
        virtual void draw();
    };

    struct TownSystemScript : args::GameSystem {
        int trigger_;                           // 0x04
        int eventLock_;                         // 0x08
        int scriptSearch_;                      // 0x0C
        int iconLock_;                          // 0x10

        TownSystemScript();
        ~TownSystemScript();
        virtual void initialize();
        virtual void terminate();
        virtual void execute();
        virtual void draw();
        void setEventLock(bool flag);
        void setScriptSearch(bool flag);
        bool isEventLock();
        int isScriptSearch();
        int isTriggerOk();
        void setTriggerFlag(bool flag);
    };

    struct TownSystemEncount : args::GameSystem {
        int data_;                              // 0x04

        TownSystemEncount();
        ~TownSystemEncount();
        virtual void initialize();
        virtual void terminate();
        virtual void execute();
        virtual void draw();
    };

    struct TownSystemParticle : args::GameSystem {
        TownSystemParticle();
        ~TownSystemParticle();
        virtual void initialize();
        virtual void terminate();
        virtual void execute();
        virtual void draw();
    };

    struct TownSystemGlobalMap : args::GameSystem {
        TownSystemGlobalMap();
        ~TownSystemGlobalMap();
        virtual void initialize();
        virtual void terminate();
        virtual void execute();
        virtual void draw();
    };

    struct TownSystemMuseum : args::GameSystem {
        TownSystemMuseum();
        ~TownSystemMuseum();
        virtual void initialize();
        virtual void terminate();
        virtual void execute();
        virtual void draw();
    };

    struct TownSystemScreenEffect : args::GameSystem {
        TownSystemScreenEffect();
        ~TownSystemScreenEffect();
        virtual void initialize();
        virtual void terminate();
        virtual void execute();
        virtual void draw();
    };

    struct TownSystem {
        enum {
            None = 0,
            CommandPriority = 1,
            RenderPriority = 2,
            ScreenEffectPriority = 3,
            MessagePriority = 4,
            MaterielMenuPriority = 5,
            MenuPriority = 6,
            DrawTownShopListPriority = 7,
            StagePriority = 8,
            StageEffectPriority = 9,
            FurniturePriority = 10,
            RiseupPriority = 11,
            SugorokuPriority = 12,
            CharacterPriority = 13,
            PlayerPriority = 14,
            EncountPriority = 15,
            ScriptPriority = 16,
            CameraPriority = 17,
            ParticlePriority = 18,
            GlobalMapPriority = 19,
            MuseumPriority = 20,
            DrawTownMapPriority = 21,
            Max = 22,
        };

        int TownSystemPriority;                                 // 0x000
        int TownDrawPriority;                                   // 0x004
        UnkTownSystemRender townSystemRender_;                  // 0x008
        TownSystemCommand townSystemCommand_;                   // 0x614
        TownSystemMenu townSystemMenu_;                         // 0x7D0
        TownSystemDrawTownMap townSystemDrawTownMap_;           // 0x7D4
        TownSystemDrawShopList townSystemDrawShopList_;         // 0x7D8
        TownSystemMaterielMenu townSystemMaterielMenu_;         // 0x7DC
        TownSystemMessage townSystemMessage_;                   // 0x7E0
        TownSystemSugoroku townSystemSugoroku_;                 // 0x7E4
        TownSystemCamera townSystemCamera_;                     // 0x7E8
        TownSystemStage townSystemStage_;                       // 0x7EC
        TownSystemStageEffect townSystemStageEffect_;           // 0x7F0
        TownSystemFurniture townSystemFurniture_;               // 0x7F4
        TownSystemRiseup townSystemRiseup_;                     // 0x7F8
        TownSystemPlayer townSystemPlayer_;                     // 0x7FC
        TownSystemCharacter townSystemCharacter_;               // 0x800
        TownSystemScript townSystemScript_;                     // 0x804
        TownSystemEncount townSystemEncount_;                   // 0x818
        TownSystemParticle townSystemParticle_;                 // 0x820
        TownSystemGlobalMap townSystemGlobalMap_;               // 0x824
        TownSystemMuseum townSystemMuseum_;                     // 0x828
        TownSystemScreenEffect townSystemScreenEffect_;         // 0x82C

        TownSystem();
        static TownSystem& getSingleton();
        void initialize();
        void terminate();
        void execute();
        void draw();
        void debug();
        static int getFloorBgmIndex();
        TownSystemScript& getScriptSystem();
        void setWait(bool flag);
    };
} // namespace twn
