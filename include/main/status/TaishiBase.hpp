#pragma once
#include <globaldefs.h>

namespace status {
    struct TaishiBase {
        int isTaishi_;                              // 0x00
        unsigned int uniqueId_;                     // 0x04
        unsigned int price_;                        // 0x08
        unsigned char objectId_;                    // 0x0C
        unsigned char production_;                  // 0x0D
        char taishiName_[28];                       // 0x0E
        char producer_[26];                         // 0x2A
        char message_[136];                         // 0x44

        TaishiBase();
        ~TaishiBase();
        void clearTaishi();
        void setTaishiFlag(bool flag);
        int getTaishiFlag();
        void setTaishiUniqueId(unsigned int id);
        unsigned int getTaishiUniqueId();
        void setTaishiPrice(unsigned int price);
        void setTaishiObjectId(unsigned char object);
        unsigned char getTaishiObjectId();
        void setTaishiProduction(unsigned char production);
        void setTaishiName(char* name);
        char* getTaishiName();
        char* getTaishiMessage();
        void setTaishiProducer(char* producer);
        void setTaishiMessage(char* message);
    };
}
