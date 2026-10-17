#pragma once
#include <globaldefs.h>
#include "main/dss/GameSystemManager.hpp"
#include "main/dss/Render.hpp"
#include "ov005/fld/FieldCommand.hpp"
#include "ov005/fld/FieldImageMap.hpp"

namespace fld
{
    struct FieldSystemEncount : args::GameSystem {
        FieldSystemEncount();
        ~FieldSystemEncount();
        virtual void initialize();
        virtual void terminate();
        virtual void execute();
        virtual void draw();
    };

    struct FieldSystemMessage : args::GameSystem {
        FieldSystemMessage();
        ~FieldSystemMessage();
        virtual void initialize();
        virtual void terminate();
        virtual void execute();
        virtual void draw();
    };

    struct FieldSystemMenu : args::GameSystem {
        FieldSystemMenu();
        ~FieldSystemMenu();
        virtual void initialize();
        virtual void terminate();
        virtual void execute();
        virtual void draw();
    };

    struct FieldSystemMaterielMenu : args::GameSystem {
        FieldSystemMaterielMenu();
        ~FieldSystemMaterielMenu();
        virtual void initialize();
        virtual void terminate();
        virtual void execute();
        virtual void draw();
    };

    struct FieldSystemStage : args::GameSystem {
        FieldSystemStage();
        ~FieldSystemStage();
        virtual void initialize();
        virtual void terminate();
        virtual void execute();
        virtual void draw();
    };

    struct FieldSystemPlayer : args::GameSystem {
        FieldSystemPlayer();
        ~FieldSystemPlayer();
        virtual void initialize();
        virtual void terminate();
        virtual void execute();
        virtual void draw();
    };

    struct FieldSystemScript : args::GameSystem {
        int eventLock_;                         // 0x04
        int search_;                            // 0x08

        FieldSystemScript();
        ~FieldSystemScript();
        virtual void initialize();
        virtual void terminate();
        virtual void execute();
        virtual void draw();
        bool isEventLock();
        void setEventLock(bool flag);
    };

    struct FieldSystemWorldMap : args::GameSystem {
        FieldImageMap imageMap;                 // 0x004

        FieldSystemWorldMap();
        ~FieldSystemWorldMap();
        virtual void initialize();
        virtual void terminate();
        virtual void execute();
        virtual void draw();
        void openAreaMap();
        void closeAreaMap();
        bool isAreaMapOpen();
        bool isAreaMapClose();
    };

    struct FieldSystemScreenEffect : args::GameSystem {
        FieldSystemScreenEffect();
        ~FieldSystemScreenEffect();
        virtual void initialize();
        virtual void terminate();
        virtual void execute();
        virtual void draw();
    };

    struct FieldSystem {
        enum {
            None = 0,
            CommandPriority = 1,
            ScreenEffectPriority = 2,
            MessagePriority = 3,
            MaterielMenuPriority = 4,
            MenuPriority = 5,
            StagePriority = 6,
            PlayerPriority = 7,
            EncountPriority = 8,
            ScriptPriority = 9,
            MapDrawPriority = 10,
            Max = 11,
        };

        int FieldSystemPriority;                // 0x000
        Render render_;                         // 0x004
        int cameraLock_;                        // 0x60C
        int encountStart_;                      // 0x610
        int counter_;                           // 0x614
        int exitSound_;                         // 0x618
        int scriptLock_;                        // 0x61C
        FieldSystemCommand fieldSystemCommand_; // 0x620
        FieldSystemEncount fieldSystemEncount_; // 0x77C
        FieldSystemMessage fieldSystemMessage_; // 0x780
        FieldSystemMenu fieldSystemMenu_;       // 0x784
        FieldSystemMaterielMenu fieldSystemMaterielMenu_; // 0x788
        FieldSystemStage fieldSystemStage_;     // 0x78C
        FieldSystemPlayer fieldSystemPlayer_;   // 0x790
        FieldSystemScript fieldSystemScript_;   // 0x794
        FieldSystemWorldMap fieldSystemWorldMap_; // 0x7A0
        FieldSystemScreenEffect fieldSystemScreenEffect_; // 0xBA4

        FieldSystem();
        static FieldSystem* getSingleton();
        void setExitSound(int flag);
        static int getFloorBgmIndex();
        void initialize();
        void terminate();
        void execute();
        void draw();
        void setLookAtPos(dss::Fix32Vector3 pos);
        void setLockCameraFlag(bool flag);
        FieldSystemScript& getScriptSystem();
    };
} // namespace fld
