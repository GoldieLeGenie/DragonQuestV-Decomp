#pragma once
#include <globaldefs.h>
#include "main/profile/Profile.hpp"

namespace profile {
    struct CatalogView {
        int useFlag_;                           // 0x00
        int id_;                                // 0x04
        char name_[18];                         // 0x08
        char restart_[32];                      // 0x1A
        int savetype_;                          // 0x3C
        int chapter_;                           // 0x40
        int level_;                             // 0x44
        int town_;                              // 0x48
        int time_;                              // 0x4C
        int clear_;                             // 0x50
    };

    struct BANKINFO {
        unsigned int MAGIC;                     // 0x00
        unsigned int TAG;                       // 0x04
        unsigned int BANK;                      // 0x08
        unsigned int CHECKSUM;                  // 0x0C
        unsigned char DUMMY[496];               // 0x10
    };

    struct SaveLoad {
        static int asyncBank_;
        static int asyncResult_;
        static Profile* asyncBuff_;
        static int lastSleep_;
        static int catalogRecent_;
        static CatalogView catalogView_[3];

        static int unkfunc_02040cec(int bank);
        static CatalogView* getCatalogView();
        static int getCatalogRecent();
        static bool loadbank(int bank);
        static bool savebank(int bank, SAVETYPE type);
        static void savebankAsync(int bank, SAVETYPE type);
        static int savebankAsyncWait();
        static int savebankAsyncResult();
        static bool killbank(int bank);
        static bool unkfunc_02041078(int bank);
        static bool memorysave(unsigned int seek, void* buff, unsigned int size);
        static void memorysaveAsync(unsigned int seek, void* buff, unsigned int size);
        static int memorysaveAsyncWait();
        static bool memorysaveAsyncResult();
        static bool memoryload(unsigned int seek, void* buff, unsigned int size);
        static void setCatalogMacro(CatalogView* view);
        static int getPlaceNameNo(int chap, char* name);
        static int getPlaceNameByChapter(int chap);
        static bool isThisMap(char* now, char* name);
        static bool isCardOK();
        static int checkBackup();
        static bool setSaveBank(int bank);
        static int getSaveBank();
    };
}
