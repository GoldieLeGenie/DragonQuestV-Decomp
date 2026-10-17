#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"
#include "main/dss/UnkSprite2D.hpp"
#include "ov001/town/SugorokuCommand.hpp"
#include "ov001/town/TownSugorokuDraw.hpp"
#include "ov028/sugoroku/TownSugorokuCommand.hpp"
#include "ov028/sugoroku/TownSugorokuPanelAction.hpp"
#include "ov028/sugoroku/TownSugorokuPanelChanceCard.hpp"

namespace twn
{
    struct SugorokuMapObj {
        int uid;                                // 0x0
        short type;                             // 0x4
        dss::BitFlag<unsigned short> flag;      // 0x6
    };

    struct TownSugorokuManager {
        static const int ARROW_NUM = 2;
        static const int SUGOROKU_OBJ_NUM = 10;
        static const int SUGOROKU_COMMAND_NUM = 160;

        enum {
            STAGE_INIT = 1,
            GAME_INIT = 2,
            DRAW_NUMBER = 4,
            DRAW_ARROW1 = 8,
            DRAW_ARROW2 = 16,
            DRAW_TIMER = 32,
            DRAW_GOLD = 64,
            BATTLE_END = 128,
            START_INN = 256,
            DRAW_SHOP = 4096,
            DRAW_MENUCANCEL = 8192,
        };

        dss::BitFlag<unsigned int> flag_;       // 0x0000
        unsigned short arrowIdx_[ARROW_NUM];    // 0x0004
        dss::Fix32Vector3 arrowPos[ARROW_NUM];  // 0x0008
        TownSugorokuArrow arrow_[ARROW_NUM];    // 0x0020
        TownSugorokuDice diceAnim_;             // 0x0320
        int drawDiceNo_;                        // 0x0A8C
        TownSugorokuDraw sugorokuDraw_;         // 0x0A90
        UnkMenuSprite shopSprite_;              // 0x1400 inn/shop sign
        int stageNO_;                           // 0x1450
        int stageOffset_;                       // 0x1454
        int state_;                             // 0x1458
        int nextState_;                         // 0x145C
        int treasureRoom_;                      // 0x1460
        int returnMenuFlag_;                    // 0x1464
        SugorokuCommand* sugorokuCommand_[SUGOROKU_COMMAND_NUM]; // 0x1468
        SugorokuMapObj sugorokuObj_[SUGOROKU_OBJ_NUM]; // 0x16E8
        int sugorokuTime_;                      // 0x1738
        int turnEnd_;                           // 0x173C
        SugorokuSystemStart sugorokuSystemStart_;                           // 0x1740
        SugorokuSystemDebugStart sugorokuSystemDebugStart_;                 // 0x1748
        SugorokuSystemPanelStart sugorokuSystemPanelStart_;                 // 0x174C
        SugorokuOpenRootMenu sugorokuOpenRootMenu_;                         // 0x1750
        SugorokuSystemDice sugorokuSystemDice_;                             // 0x1758
        SugorokuSystemDiceControl sugorokuSystemDiceControl_;               // 0x175C
        SugorokuSystemPlayerMove sugorokuSystemPlayerMove_;                 // 0x176C
        SugorokuSystemFadeOutEnd sugorokuSystemFadeOutEnd_;                 // 0x178C
        SugorokuSystemCameraMove sugorokuSystemCameraMove_;                 // 0x1790
        SugorokuSystemCameraEnd sugorokuSystemCameraMoveEnd_;               // 0x1794
        SugorokuSystemPanelLink sugorokuSystemPanelLink_;                   // 0x1798
        SugorokuSystemFadeOutNextShop sugorokuSystemFadeOutNextShop_;       // 0x179C
        SugorokuSystemFadeInNextShop sugorokuSystemFadeInNextShop_;         // 0x17A0
        SugorokuSystemShopOpen sugorokuSystemShopOpen_;                     // 0x17A4
        SugorokuSystemFadeOutNextMenu sugorokuSystemFadeOutNextMenu_;       // 0x17A8
        SugorokuSystemFadeInNextMenu sugorokuSystemFadeInNextMenu_;         // 0x17AC
        SugorokuSystemAbortEnd sugorokuSystemAbortEnd_;                     // 0x17B0
        SugorokuSystemTreasurePreRoom sugorokuSystemTreasurePreRoom_;       // 0x17B8
        SugorokuSystemTreasureRoomEndMessage sugorokuSystemTreasureRoomEndMessage_; // 0x17BC
        SugorokuSystemTreasureRoomMove sugorokuSystemTreasureRoomMove_;     // 0x17C4
        SugorokuSystemTreasureRoomEnd sugorokuSystemTreasureRoomEnd_;       // 0x17D0
        SugorokuSystemTreasureRoomSetTime sugorokuSystemTreasureRoomSetTime_; // 0x17D4
        SugorokuPanelActionKaidanUp sugorokuPanelActionKaidanUp_;           // 0x17EC
        SugorokuPanelActionKaidanDown sugorokuPanelActionKaidanDown_;       // 0x17F0
        SugorokuPanelFinish sugorokuPanelFinish_;                           // 0x17F4
        SugorokuPanelActionGoldUp50 sugorokuPanelActionGoldUp50_;           // 0x17FC
        SugorokuPanelActionGoldUp100 sugorokuPanelActionGoldUp100_;         // 0x1800
        SugorokuPanelActionGoldUp200 sugorokuPanelActionGoldUp200_;         // 0x1804
        SugorokuPanelActionGoldUp300 sugorokuPanelActionGoldUp300_;         // 0x1808
        SugorokuPanelActionGoldUp500 sugorokuPanelActionGoldUp500_;         // 0x180C
        SugorokuPanelActionGoldUp1000 sugorokuPanelActionGoldUp1000_;       // 0x1810
        SugorokuPanelActionGoldUp2000 sugorokuPanelActionGoldUp2000_;       // 0x1814
        SugorokuPanelActionGoldUp3000 sugorokuPanelActionGoldUp3000_;       // 0x1818
        SugorokuPanelActionGoldUp5000 sugorokuPanelActionGoldUp5000_;       // 0x181C
        SugorokuPanelActionGoldDown50 sugorokuPanelActionGoldDown50_;       // 0x1820
        SugorokuPanelActionGoldDown100 sugorokuPanelActionGoldDown100_;     // 0x1828
        SugorokuPanelActionGoldDown200 sugorokuPanelActionGoldDown200_;     // 0x1830
        SugorokuPanelActionGoldDown300 sugorokuPanelActionGoldDown300_;     // 0x1838
        SugorokuPanelActionGoldDown500 sugorokuPanelActionGoldDown500_;     // 0x1840
        SugorokuPanelActionGoldDown1000 sugorokuPanelActionGoldDown1000_;   // 0x1848
        SugorokuPanelActionGoldDown2000 sugorokuPanelActionGoldDown2000_;   // 0x1850
        SugorokuPanelActionGoldDown3000 sugorokuPanelActionGoldDown3000_;   // 0x1858
        SugorokuPanelActionGoldDown5000 sugorokuPanelActionGoldDown5000_;   // 0x1860
        SugorokuPanelActionDiceUp1 sugorokuPanelActionDiceUp1_;             // 0x1868
        SugorokuPanelActionDiceUp2 sugorokuPanelActionDiceUp2_;             // 0x186C
        SugorokuPanelActionDiceUp3 sugorokuPanelActionDiceUp3_;             // 0x1870
        SugorokuPanelActionDiceUp5 sugorokuPanelActionDiceUp5_;             // 0x1874
        SugorokuPanelActionDiceDown1 sugorokuPanelActionDiceDown1_;         // 0x1878
        SugorokuPanelActionDiceDown2 sugorokuPanelActionDiceDown2_;         // 0x187C
        SugorokuPanelActionDiceDown3 sugorokuPanelActionDiceDown3_;         // 0x1880
        SugorokuPanelActionDiceDown5 sugorokuPanelActionDiceDown5_;         // 0x1884
        SugorokuPanelActionMoveNext1 sugorokuPanelActionMoveNext1_;         // 0x1888
        SugorokuPanelActionMoveNext2 sugorokuPanelActionMoveNext2_;         // 0x188C
        SugorokuPanelActionMoveNext3 sugorokuPanelActionMoveNext3_;         // 0x1890
        SugorokuPanelActionMoveNext4 sugorokuPanelActionMoveNext4_;         // 0x1894
        SugorokuPanelActionMoveNext5 sugorokuPanelActionMoveNext5_;         // 0x1898
        SugorokuPanelActionMoveNext6 sugorokuPanelActionMoveNext6_;         // 0x189C
        SugorokuPanelActionMoveBack1 sugorokuPanelActionMoveBack1_;         // 0x18A0
        SugorokuPanelActionMoveBack2 sugorokuPanelActionMoveBack2_;         // 0x18A4
        SugorokuPanelActionMoveBack3 sugorokuPanelActionMoveBack3_;         // 0x18A8
        SugorokuPanelActionMoveBack4 sugorokuPanelActionMoveBack4_;         // 0x18AC
        SugorokuPanelActionMoveBack5 sugorokuPanelActionMoveBack5_;         // 0x18B0
        SugorokuPanelActionMoveBack6 sugorokuPanelActionMoveBack6_;         // 0x18B4
        SugorokuPanelActionEncountNormal sugorokuPanelActionEncountNormal_; // 0x18B8
        SugorokuPanelActionEncountMetal sugorokuPanelActionEncountMetal_;   // 0x18BC
        SugorokuPanelActionDamage sugorokuPanelActionDamage_;               // 0x18C0
        SugorokuPanelActionLostMp sugorokuPanelActionLostMp_;               // 0x18C8
        SugorokuPanelActionChangeParameter sugorokuPanelActionChangeParameter_; // 0x18CC
        SugorokuPanelActionChanceCard sugorokuPanelActionChanceCard_;       // 0x18E0
        SugorokuPanelActionBackToStart sugorokuPanelActionBackToStart_;     // 0x18E4
        SugorokuPanelActionHoleTrap sugorokuPanelActionHoleTrap_;           // 0x18E8
        SugorokuPanelActionTravelGate sugorokuPanelActionTravelGate_;       // 0x18EC
        SugorokuPanelActionTansu sugorokuPanelActionTansu_;                 // 0x18F0
        SugorokuPanelActionTubo sugorokuPanelActionTubo_;                   // 0x1914
        SugorokuPanelActionTreasuerBox sugorokuPanelActionTreasuerBox_;     // 0x1938
        SugorokuPanelActionInn sugorokuPanelActionInn_;                     // 0x195C
        SugorokuPanelActionShop sugorokuPanelActionShop_;                   // 0x1964
        SugorokuPanelActionFlat sugorokuPanelActionFlat_;                   // 0x196C
        SugorokuPanelActionForest sugorokuPanelActionForest_;               // 0x1994
        SugorokuPanelActionMountain sugorokuPanelActionMountain_;           // 0x19BC
        SugorokuPanelActionKanbanUp sugorokuPanelActionKanbanUp_;           // 0x19E4
        SugorokuPanelActionKanbanDown sugorokuPanelActionKanbanDown_;       // 0x19F0
        SugorokuPanelActionKanbanLeft sugorokuPanelActionKanbanLeft_;       // 0x19FC
        SugorokuPanelActionKanbanRight sugorokuPanelActionKanbanRight_;     // 0x1A08
        SugorokuPanelActionChangeGate sugorokuPanelActionChangeGate_;       // 0x1A14
        SugorokuPanelActionSugorokuDungeon sugorokuPanelActionSugorokuDungeon_; // 0x1A18
        SugorokuPanelActionTreasuerRoom sugorokuPanelActionTreasuerRoom_;   // 0x1A28
        SugorokuPanelActionHealPoint sugorokuPanelActionHealPoint_;         // 0x1A38
        SugorokuPanelActionSelectSpot sugorokuPanelActionSelectSpot_;       // 0x1A3C
        SugorokuSystemBattleEnd sugorokuSystemBattleEnd_;                   // 0x1A40
        SugorokuPanelChanceCardStrengthUp1 sugorokuPanelChanceCardStrengthUp1_; // 0x1A48
        SugorokuPanelChanceCardStrengthUp2 sugorokuPanelChanceCardStrengthUp2_; // 0x1A4C
        SugorokuPanelChanceCardAgilityUp1 sugorokuPanelChanceCardAgilityUp1_; // 0x1A50
        SugorokuPanelChanceCardAgilityUp2 sugorokuPanelChanceCardAgilityUp2_; // 0x1A54
        SugorokuPanelChanceCardProtectionUp1 sugorokuPanelChanceCardProtectionUp1_; // 0x1A58
        SugorokuPanelChanceCardProtectionUp2 sugorokuPanelChanceCardProtectionUp2_; // 0x1A5C
        SugorokuPanelChanceCardWisdomUp sugorokuPanelChanceCardWisdomUp_;   // 0x1A60
        SugorokuPanelChanceCardWisdomDown sugorokuPanelChanceCardWisdomDown_; // 0x1A64
        SugorokuPanelChanceCardLuckUp1 sugorokuPanelChanceCardLuckUp1_;     // 0x1A68
        SugorokuPanelChanceCardLuckUp2 sugorokuPanelChanceCardLuckUp2_;     // 0x1A6C
        SugorokuPanelChanceCardStrengthDown sugorokuPanelChanceCardStrengthDown_; // 0x1A70
        SugorokuPanelChanceCardAgilityDown sugorokuPanelChanceCardAgilityDown_; // 0x1A74
        SugorokuPanelChanceCardProtectionDown sugorokuPanelChanceCardProtectionDown_; // 0x1A78
        SugorokuPanelChanceCardLuckDown sugorokuPanelChanceCardLuckDown_;   // 0x1A7C
        SugorokuPanelChanceCardBackToStart sugorokuPanelChanceCardBackToStart_; // 0x1A80
        SugorokuPanelChanceCardEncount1 sugorokuPanelChanceCardEncount1_;   // 0x1A84
        SugorokuPanelChanceCardEncount2 sugorokuPanelChanceCardEncount2_;   // 0x1A90
        SugorokuPanelChanceCardEncount3 sugorokuPanelChanceCardEncount3_;   // 0x1A9C
        SugorokuPanelChanceCardGoldDown100 sugorokuPanelChanceCardGoldDown100_; // 0x1AA8
        SugorokuPanelChanceCardGoldUp100 sugorokuPanelChanceCardGoldUp100_; // 0x1AAC
        SugorokuPanelChanceCardNotEncount sugorokuPanelChanceCardNotEncount_; // 0x1AB0
        SugorokuPanelChanceCardHoleTrap sugorokuPanelChanceCardHoleTrap_;   // 0x1AB4
        SugorokuPanelChanceCardChanceParameter sugorokuPanelChanceCardChanceParameter_; // 0x1AB8
        SugorokuPanelChanceCardTreasuerBox sugorokuPanelChanceCardTreasuerBox_; // 0x1ACC
        SugorokuPanelChanceCardDiceCountUp sugorokuPanelChanceCardDiceCountUp_; // 0x1AE0
        SugorokuPanelChanceCardEncount4 sugorokuPanelChanceCardEncount4_;   // 0x1AE4
        SugorokuPanelChanceCardInn sugorokuPanelChanceCardInn_;             // 0x1AF0
        SugorokuPanelChanceCardSelectDice sugorokuPanelChanceCardSelectDice_; // 0x1AF4
        SugorokuPanelChanceCardMoveNext6 sugorokuPanelChanceCardMoveNext6_; // 0x1AF8
        SugorokuPanelChanceCardMoveBack5 sugorokuPanelChanceCardMoveBack5_; // 0x1AFC
        SugorokuPanelChanceCardDiceLimitDown sugorokuPanelChanceCardDiceLimitDown_; // 0x1B00
        SugorokuPanelChanceCardTreasuerRoom sugorokuPanelChanceCardTreasuerRoom_; // 0x1B04
        SugorokuPanelChanceCardLucky1 sugorokuPanelChanceCardLucky1_;       // 0x1B08
        SugorokuPanelChanceCardLucky2 sugorokuPanelChanceCardLucky2_;       // 0x1B0C
        SugorokuPanelChanceCardLucky3 sugorokuPanelChanceCardLucky3_;       // 0x1B10
        SugorokuPanelChanceCardUnlucky1 sugorokuPanelChanceCardUnlucky1_;   // 0x1B14
        SugorokuPanelChanceCardUnlucky2 sugorokuPanelChanceCardUnlucky2_;   // 0x1B18
        SugorokuPanelChanceCardUnlucky3 sugorokuPanelChanceCardUnlucky3_;   // 0x1B1C

        TownSugorokuManager();
        static TownSugorokuManager& getSingleton();
        void initialize();
        void terminate();
        void execute();
        void draw();
        void setupMapObj();
        void stageSetup();
        bool isSugorokuStage();
        void startSugoroku();
        bool isSugorokuMode();
        bool isTreasuerRoom();
        void setNextState(int state);
        int getSugorokuTimeEnd();
        void regist(int id, SugorokuCommand& command);
        void setShopDraw(int type);
        void clearShopDraw();
        void terminateSugoroku();
        void setArrowDraw(int no, bool flag);
        void setDrawDiceNum(bool flag);
        void drawSugorokuTimer();
        void setDrawTimer(bool flag);
        void setStageNo();
        int getSugorokuDungeonUid(int map);
        void getSugorokuDungeonData(int& map, int& uid);
        void registCommand();
        bool isDiceAnimEnd();
        void diceThrowIn(int number);
        int getStageNo();
        int getStageOffset();
        void setDrawDiceFreeOneFrame(int dice);
        int getTurnEnd();
        void setTurnEnd(bool flag);
        void setArrowIdx(int index, unsigned short idx);
        void setArrowPos(int index, dss::Fix32Vector3& pos);
        void setSugorokuTimeEnd(bool flag);
        void setTreasuerRoom(bool flag);
    };
} // namespace twn
