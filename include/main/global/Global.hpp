#pragma once
#include "main/global/UnkProtectCheck.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/dss/DssCore.hpp"
#include "main/dss/UnkSprite2D.hpp"
#include "main/global/GlobalGamePart.hpp"
#include "main/global/UnkGlobalSystem.hpp"

struct Global {
    int currentGamePart_;                       // 0x00
    int fieldType_;                             // 0x04
    int nextFieldType_;                         // 0x08
    int areaNo_;                                // 0x0C
    int prevAreaNo_;                            // 0x10
    int minigameType_;                          // 0x14
    int minigameStatus_;                        // 0x18
    int ceremonyType_;                          // 0x1C
    int ranarutaFlag_;                          // 0x20
    int checkShiftParty_;                       // 0x24
    int shiftPartyMessage_;                     // 0x28
    int partChangeFlag_;                        // 0x2C
    int fightStadiumFlag_;                      // 0x30
    int betOnIndex_;                            // 0x34
    int betCoin_;                               // 0x38
    short betMonsterID_;                        // 0x3C
    short betMonsterSymbol_;                    // 0x3E
    short diameter_;                            // 0x40
    int doubleUpFlag_;                          // 0x44
    int prevPartTown_;                          // 0x48
    int effectType_;                            // 0x4C
    dss::Fix32Vector3 battleLoseAfterPosition_; // 0x50
    short battleLoseAfterIdx_;                  // 0x5C
    int battleLoseAfterFlag_;                   // 0x60
    int battleLoseAfterMapNameId_;              // 0x64
    int prevMapNameId;                          // 0x68
    int nextMapNameId;                          // 0x6C
    char prevMapName[32];                       // 0x70
    char nextMapName[32];                       // 0x90
    char battleMapName[32];                     // 0xB0
    unsigned char fightStadiumResult_;          // 0xD0
    int actionIndex_;                           // 0xD4

    Global();
    ~Global();
    void initialize();
    void startGame();
    void startFirstTown();
    void startDebugTown();
    void startTown(int mapNameId);
    void startTown(const char* name);
    void startCasino();
    void startSlimeRace();
    void startSlimeTouch();
    void startBook();
    void startSurechigai();
    void setMinigame(int type);
    int getMinigame();
    void setCeremonyType(int type);
    int getCeremonyType();
    void setGameStatus(int status);
    int getGameStatus();
    void setRanarutaFlag(bool flag);
    int getRanarutaFlag();
    const char* getMapName();
    void setMapNameId(int id);
    void getMapNameById(char* buff, int id);
    int getMapNameIdByName(const char* name);
    int getMapNameId();
    int getPrevMapNameId();
    void setPartChangeFlag(bool flag);
    int getNowAreaNo();
    int isPartChangeFlag();
    bool isAreaChange();
    int getFieldType();
    void initFieldType();
    void startField();
    void startBattle();
    void directStartBattle();
    void endBattle(bool demolition);
    void setBattleLoseAfterMapNameId(int id, dss::Fix32Vector3& pos, short idx);
    void setBattleLoseAfterFlag(bool flag);
    void startTitle();
    void startOpeningStaff();
    void startStaffroll();
    void startFin();
    void startLogo();
    bool isNextPart(int part);
    void fadeOutBlack(int frame, bool flag);
    void fadeOutWhite(int frame, bool flag);
    void fadeInBlack(int frame);
    void fadeInWhite(int frame);
    void fadeIn(int frame);
    void updateArea();
    void checkFlag();
    void checkSave1();
    bool checkSave2();
};

// Changes the game part once the fade is over
struct UnkGlobalChangePart : UnkGlobalPart {
    int nextPart_;                              // 0x04

    virtual void update();
    virtual int isEnd();
    void setNextPart(int part);
};

// Waits a number of frames
struct UnkGlobalWaitPart : UnkGlobalPart {
    int count_;                                 // 0x04
    int frames_;                                // 0x08

    virtual void update();
    virtual void draw();
    virtual int isEnd();
    int isRunning();
};

// Screen fade 
struct FadeEffector : UnkGlobalPart {
    enum UnkFadeState {
        FADE_NONE = 0,
        FADE_OUT_BLACK = 1,
        FADE_IN_BLACK = 2,
        FADE_OUT_WHITE = 3,
        FADE_IN_WHITE = 4,
    };
    UnkFadeState state_;                          // 0x04
    int brightness_;                            // 0x08
    int count_;                                 // 0x0C
    int frames_;                                // 0x10
    int unk_14;                                 // 0x14 write the brightness to the screens
    int fadeDisable_;                           // 0x18 skips the next fade

    FadeEffector();
    virtual void update();
    virtual void draw();
    virtual int isEnd();
    void setFadeOutBlack(int frame, bool flag);
    void setFadeOutWhite(int frame, bool flag);
    void setFadeDisable(bool flag);
    void setFadeInBlack(int frame);
    void setFadeInWhite(int frame);
    void setFadeIn(int frame);
    int isFadeEnd();
    int isFadeOutBlack();
    int isFadeInBlack();
    int isFadeOutWhite();
    bool isFadeDisable();
};

struct UnkSpriteFade : UnkGlobalPart {
    FadeEffector::UnkFadeState state_;            // 0x04
    int alpha_;                                 // 0x08
    int count_;                                 // 0x0C
    int frames_;                                // 0x10
    UnkSprite2D sprite_[2];                     // 0x14 

    UnkSpriteFade();
    void flashWhite(int r, int g, int b, int frames);
    virtual void update();
    virtual void draw();
    virtual int isEnd();
};

extern Global g_Global;
extern FadeEffector fadeEffector;
extern UnkSpriteFade data_0211b27c;

