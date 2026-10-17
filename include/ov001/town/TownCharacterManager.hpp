#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"
#include "ov001/town/character/TownCharacterStorage.hpp"

struct TownCharacterManager {
    static const int TOWN_CHARACTER_MAX = 32;

    int townCharacterCount_;                    // 0x0000
    twn::TownCharacterBase* character_[32];     // 0x0004
    twn::TownCharacterStorage characterStorage; // 0x0084
    bool checkArea_;                            // 0xDEB4
    bool search_;                               // 0xDEB5
    unsigned char unk_DEB6[0xDEBC - 0xDEB6];    // 0xDEB6

    static const dss::Fix32 defaultSpeed;

    TownCharacterManager();
    ~TownCharacterManager();
    static TownCharacterManager* getSingleton();
    void initialize();
    void terminate();
    void execute();
    int setup(TOWN_CHARACTER& chara);
    void draw();
    void requestCharacterReload();
    void setPosing(int index, int pose);
    int getMaxCharacter();
    bool isCharacterEnable(int index);
    void cleanup(int index);
    void setPlayerDirection(int index);
    void changePose(int index, int pose);
    dss::Fix32Vector3& getPosition(int index);
    void setRotate(int index, int dir);
    void setRotate(int index, dss::Vector3<short>& rot);
    void setTalkedArea(int index, bool flag);
    void setTalked(int index, bool flag);
    bool isTalked(int index);
    void setShadow(int index, int flag);
    void setAnimation(int index, int flag);
    void setWriggleCharacter(int index, int flag);
    void setNearCharacter(int index, int flag);
    void setDisplay(int index, int flag);
    void setAlpha(int index, unsigned char alpha);
    void setPosition(int index, dss::Fix32Vector3& pos);
    void setSleepCharacter(int index, int flag);
    void setCollFlag(int index, int flag);
    int getDirection(int index);
    void resetCharaTalk();
    bool checkCollision(dss::Fix32Vector3& pos, dss::Fix32 rr);
    bool charaToCharaColl(twn::TownCharacterBase* chara, dss::Fix32* llen, int* no);
    void characterColl(dss::Fix32Vector3& nowPos, dss::Fix32Vector3& nextPos, dss::Fix32 r);
    bool checkFarTalk(dss::Fix32Vector3& pos, dss::Fix32Vector3& vecN, dss::Fix32 ctrLen, int polyNo, bool farTalk);
    bool checkTalkingNearCharacter(dss::Fix32Vector3& pos, short dirIdx, int searchObject);
    void setCharaAnim(int index, short count);
    void eventLockAllChraraAnim();
    int getCharaIndex(int index);
    void restoreCharacterAnim();
    void setAllEventLock(bool flag);
    void setSpecCharaAlpha(int charIndex, unsigned char alpha);
    void setSpecCleanup(int charIndex);
    void setCopyPlayerChara(int index, dss::Fix32Vector3& pos, short idx, int charNo);
    bool checkIkadaTalk(dss::Fix32Vector3& target, dss::Fix32Vector3& playerDir);
    void checkObjectInTalk(int objectId);
    bool checkVoice(int index);
    int getVoice(int index);
    void setObjectMove(int ctrl, int uid, dss::Fix32Vector3& offset, int dir);
    void setSyncroPos(int index);
    void setScriptData(int index, twn::TOWN_SCRIPT_DATA& script);
    int isScriptEnd(int index);
    void execWait(int index);
    void execRiseup(int index);
    void execTremble(int index);
    void setFadeType(int index, int type, int frame);
    bool isEndFade(int index);
    void setScale(int index, dss::Fix32 scale);
    void setChangePaletteRate(int index, unsigned char r, unsigned char g, unsigned char b, int rgbFrame);
    bool isEndChangePalletRate(int index);
    void setMotion(int index, int motion, bool flag);
    bool isMotion(int index);
    void setHueChange(int index, int type, int frame);
    bool isHueChange(int index);
    void setShadowOnly(int index, int flag);
    void setEventLock(int index, bool flag);
    void setSimpleMove(int index);
    void setSimpleRot(int index, short idx, int frame, int mode);
    void setLockRot(int index, int lockRot);
    void setMoveType(int index, twn::SCRIPT_MOVE_TYPE type, twn::SCRIPT_MOVE_DATA& moveData);
    twn::SCRIPT_MOVE_TYPE getMoveType(int index);
    void setMoveToParty(int index);
    void setMoveRandom(int index);
    void setMovePassive(int index);
    void setMoveReverse(int index);
    bool isRotEnd(int index);
    void setRotFrame(int index, int frame, short idx, int flag, int typeA);
    bool isRotFrameEnd(int index);
    void setStageColl(int index, char flag);
    bool getCounterTalk(int index);
    void setMapUid(int index, int uid);
    void setVoice(int ctrl, int voice);
    void setSwingRound(int index, int flag);
    void setJumpMove(int index, dss::Fix32Vector3& target, int frame);
    void setSynchronous(int index, int flag, int no);
    void setMotionLock(int index, int flag);
    void setAreaCheck(bool flag);
};
