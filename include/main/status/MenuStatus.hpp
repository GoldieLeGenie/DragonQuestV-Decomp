#pragma once
#include <globaldefs.h>

namespace menu {
    enum BOOKING_FLAG {
        BOOKING_NONE = 0,
        BOOKING_RETURN = 1,
        BOOKING_INN = 2,
        BOOKING_CHURCH = 3,
        BOOKING_TOWN = 4,
        BOOKING_STADIUM = 5,
        BOOKING_FUKUBIKI = 6,
        BOOKING_JISAN = 7,
        BOOKING_LUIDA = 8,
        BOOKING_SLIMERACE = 9,
        BOOKING_SLIMETOUCH = 10,
        BOOKING_SURECHIGAI_ROOT = 11,
        BOOKING_SURECHIGAI = 12,
        BOOKING_GAMESET = 13,
    };
}

namespace status {
    struct MenuStatus {
        int messageVoice_[3];                   // 0x00
        int ownerVoice_;                        // 0x0C
        int drawFlag_;                          // 0x10
        int returnMenuType_;                    // 0x14
        int bookingFlag_;                       // 0x18
        int surechigaiMode_;                    // 0x1C
        int messageNo_[3];                      // 0x20
        int menuEventFlag_;                     // 0x2C
        int eventInnStart_;                     // 0x30
        int playerItemFlag_;                    // 0x34
        int addMessageFlag_;                    // 0x38
        int curseEffectStart_;                  // 0x3C
        short menuEventNo_[8];                  // 0x40
        short actorIndex_;                      // 0x50
        short targetIndex_;                     // 0x52
        short itemIndex_;                       // 0x54
        char innCount_;                         // 0x56
        char fukubikiPrize_;                    // 0x57
        char sackActive_;                       // 0x58
        char sackActivePage_;                   // 0x59
        char meisanSackActive_;                 // 0x5A
        char meisanSackActivePage_;             // 0x5B
        char pantherNo_;                        // 0x5C
        char addMonsterIndex_;                  // 0x5D

        MenuStatus();
        ~MenuStatus();
        void initialize();
        char getInnCount();
        void setMenuEventNo(short* item, int count);
        void setMenuEventNo(short no);
        bool checkMenuEventNo(int checkNo);
        void resetMenuEventNo();
        int getCurseEffectStart();
        void setCurseEffectStart(bool flag);
        int getBooking();
        void clearBooking();
        void setBooking(menu::BOOKING_FLAG flag);
        void setBooking(int flag);
        void setActorIndex(short actor);
        short getActorIndex();
        void setMenuEventFlag(bool flag);
        int getMenuEventFlag();
        int getLuraDisableMessage(int index);
        int getLuraDisableMessageVoice(int index);
        void setLuraDisableMessage(int mes);
        void setLuraDisableMessage(int index, int mes);
        void setLuraDisableMessageVoice(int index, int voice);
        int getEventInnStart();
        void setAddMonsterIndex(char index);
        void setItemIndex(short index);
        short getTargetIndex();
        void setTargetIndex(short target);
        short getItemIndex();
        void setBookingPantherNo(char no);
        char getBookingPantherNo();
    };

    extern MenuStatus g_Menu;
}
