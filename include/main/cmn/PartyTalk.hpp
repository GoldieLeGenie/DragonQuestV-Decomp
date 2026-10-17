#pragma once
#include <globaldefs.h>
#include "main/leveldata/PartytalkYounen.hpp"
#include "main/leveldata/PartytalkYounenIndex.hpp"

namespace cmn {
    struct PartyTalk {
        static const int PIC_MESSAGE_COUNT_MAX = 50;
        static const int SAVE_MESSAGE_COUNT_MAX = 20;
        static const int PRE_MESSAGE_COUNT_MAX = 3;
        static const int MESSAGE_COUNT_MAX = 10;
        static const int YES_NO_COUNT = 3;
        static const int ADD_PLAYER_COUNT_MAX = 4;

        enum {
            TYPE_NORMAL = 0,
            TYPE_YESNO = 1,
            TYPE_SHAKE = 2,
        };

        struct PARTY_TALK {
            int mesSoundIndex_[MESSAGE_COUNT_MAX];      // 0x00
            int message_[MESSAGE_COUNT_MAX];            // 0x28
            char yesnoCount_[YES_NO_COUNT];             // 0x50
            short record_;                              // 0x54
            short talkMonster_;                         // 0x56
            char mesCount_;                             // 0x58
            char messageType_;                          // 0x59
        };

        PARTY_TALK partyTalk_[PIC_MESSAGE_COUNT_MAX];   // 0x0000
        int saveMessage_[SAVE_MESSAGE_COUNT_MAX];       // 0x11F8
        unsigned int size_;                             // 0x1248
        int preMessage_;                                // 0x124C
        char mesCount_;                                 // 0x1250
        char partyTalkNo_;                              // 0x1251
        char saveMessageCount_;                         // 0x1252
        char noChangeObjectLimitCount_;                 // 0x1253
        char player_[ADD_PLAYER_COUNT_MAX];             // 0x1254
        int intoFloor_;                                 // 0x1258
        int lastExit_;                                  // 0x125C
        int treasureUid_;                               // 0x1260
        short floor_;                                   // 0x1264
        short prevItem_;                                // 0x1266
        short useItem_;                                 // 0x1268
        char addPlayerCount_;                           // 0x126A
        int chapter_;                                   // 0x126C
        int saveMessageFlag_;                           // 0x1270
        int findPriorityMessage_;                       // 0x1274
        char carriageOutCount_;                         // 0x1278

        static PartyTalk& getSingleton();
        void initialize();
        void setPartyTalkMessage();
        void resetPartyTalk();
        void resetWalkPartyTalk();
        void setPreMessageNo(int mesNo);
        void setExitNo(int exitNo);
        void setPreItem(int itemID);
        void setUseItem(int itemID);
        void setTreasureUid(int uid);
        void setAddPlayer(int playerIndex);
        void getPartyTalk();
        dq5::level::PartytalkYounen* getPartytalkRecord(int index);
        dq5::level::PartytalkYounenIndex* getPartytalkRecordIndex(int index);
        void setPickMessage(int message, int record);
        void setMessage(dq5::level::PartytalkYounen* talk, int addCount);
        void setPartyTalkFlag(int conduct, unsigned int value);
        void getFloorPartyTalkRecord(int& start, int& end);
        int checkCondition(int condition, int value);
        int getPlayerIndex(int character);
        bool checkHaveItem(int itemID);
        void saveMessageUpdate();
        void checkNameGorosute(int& son, int& daughter);
        int getPartyTalkMessCount();
        int getTalkMonsterIndex();
        int getPartyTalkFirstMessage(int index);
        int getPartyTalkSoundChara(int index);
        int getPartyTalkMessageType();
        int getPartyTalkYesNoCount(int index);
    };
}
