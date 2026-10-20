#include "ov001/town/TownPlayerManager.hpp"
#include "ov001/town/TownActionCalculate.hpp"
#include "ov001/town/TownCamera.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/global/Global.hpp"
#include "main/leveldata/CharaData.hpp"
#include "main/leveldata/LevelDataUtility.hpp"
#include "main/object/BillboardCharacter.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/PlayerData.hpp"
#include "main/status/PlayerStatus.hpp"
#include "main/status/StageInfo.hpp"
#include "nitro/os.hpp"

inline dq5::level::CharaData* dq5::level::CharaData::getRecord(int index)
{
    return (CharaData*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned char dq5::level::CharaData::getHeight()
{
    return height;
}

inline unsigned char dq5::level::CharaData::getWidth()
{
    return width;
}

inline void dq5::level::CharaData::setWidth(unsigned char data)
{
    width = data;
}

inline int Global::getMapNameId()
{
    return nextMapNameId;
}

inline int Global::getNowAreaNo()
{
    return areaNo_;
}

inline int cmn::CommonPartyInfo::getKeepMap()
{
    return keepMap_;
}

inline short cmn::CommonPartyInfo::getCarriageOutDir(int index)
{
    return separateDir_[index];
}

inline int status::PartyStatusUtility::isSeparate()
{
    return separateFlag_;
}

inline int status::PartyStatusUtility::getCarriageOutPlayer(int no)
{
    return separateCarriageOutPlayer_[no];
}

inline status::PlayerData& status::PlayerDataAll::getPlayerData(int index)
{
    return playerData_[index];
}

inline unsigned short status::PlayerData::getHp()
{
    return baseStatus_.hp_;
}

inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo()
{
    return haveStatusInfo_;
}

inline int twn::TownPartyDraw::getMemberCharaIndex(int i)
{
    return charaIndex_[i];
}

inline void twn::TownPartyDraw::setHueChange(int index, int type, int frame)
{
    partyCharacter_[index].setHueChange(type, frame);
}

static float unk_02151940 = 0.01f;
static dss::Fix32Vector3 defaultPosition(0, 0, 0);
const unsigned short twn::TownPartyDraw::colorBarrier = 0x1e52;
const unsigned short twn::TownPartyDraw::colorDoku = 0x48f2;
const unsigned short twn::TownPartyDraw::colorYogan = 0x2959;

THUMB twn::TownPartyDraw::TownPartyDraw()
{
    for (int i = 0; i < PARTY_MAX; i++) {
        partyDispAlpha_[i] = 31;
        partyCharacter_[i].setBoxTestOff(true);
    }
}

THUMB twn::TownPartyDraw::~TownPartyDraw()
{
}

THUMB void twn::TownPartyDraw::setBashaDraw()
{
    char path[128];
    for (int i = 0; i < count_; i++) {
        switch (i) {
        case 0: {
            status::PlayerStatus& playerStatus = status::g_Party.getPlayerStatus(i);
            charaIndex_[i] = playerStatus.getHaveStatusInfo().getCharaIndex();
            if (playerStatus.getHaveStatusInfo().isDeath()) {
                charaIndex_[i] = 0x59;
            }
            break;
        }
        case 1:
            charaIndex_[i] = 0x12d;
            break;
        case 2:
            charaIndex_[i] = 0x12c;
            break;
        default: {
            status::PlayerStatus& playerStatus = status::g_Party.getPlayerStatus(i - 2);
            charaIndex_[i] = playerStatus.getHaveStatusInfo().getCharaIndex();
            if (playerStatus.getHaveStatusInfo().isDeath()) {
                charaIndex_[i] = 0x59;
            }
            break;
        }
        }
        dss::sprintf_s(path, sizeof(path), "data/chr/h%03d.pack", charaIndex_[i]);
        BillboardCharacter::setCamera(&TownCamera::getSingleton()->camera_.unk_004);
        setPlayerSize(i, charaIndex_[i]);
        partyCharacter_[i].setup(path, dq5::level::CharaData::loadSwitch_);
        partyCharacter_[i].setPosition(defaultPosition);
        partyCharacter_[i].setRotate(0);
        partyCharacter_[i].enable_ = 0;
        partyCharacter_[i].setShadowType(0);
        partyCharacter_[i].exec();
    }
    count_ = dss::clamp<int>(count_, 0, 7);
    for (int i = 0; i < count_; i++) {
        partyCharacter_[i].enable_ = 1;
    }
}

THUMB void twn::TownPartyDraw::setup()
{
    char path[128];
    for (int i = 0; i < PARTY_MAX; i++) {
        charaIndex_[i] = 0;
    }
    status::g_Party.setDisplayMode();
    count_ = status::g_Party.getCount();
    countReal_ = count_;
    taimatsuSetup_ = 0;
    taimatsuFlag_ = 0;
    separateCharaCount_ = 0;
    if (g_Global.getMapNameId() == 0xa) {
        int charaparam = dq5::level::g_LevelDataUtility.getCharaParamIndex(0x8b);
        if (dq5::level::CharaData::getRecord(charaparam)->getWidth() < 0x20) {
            dq5::level::CharaData::getRecord(charaparam)->setWidth(0x20);
        }
        BillboardCharacter::setCamera(&TownCamera::getSingleton()->camera_.unk_004);
        taimatsu_.setCharacterSize(dq5::level::CharaData::getRecord(charaparam)->getWidth(), dq5::level::CharaData::getRecord(charaparam)->getHeight());
        dss::sprintf_s(path, sizeof(path), "data/chr/h%03d.pack", 0x8b);
        taimatsu_.setup(path, dq5::level::CharaData::loadSwitch_);
        taimatsu_.setPosition(defaultPosition);
        taimatsu_.setRotate(0);
        taimatsu_.setShadowType(0);
        taimatsu_.exec();
        taimatsuSetup_ = 1;
    }
    if (status::PartyStatusUtility::isSeparate() == true && cmn::g_cmnPartyInfo.getKeepMap() == g_Global.getMapNameId()) {
        separateSetup();
    }
    if (status::g_Party.isCarriageEnter()) {
        count_ += 2;
        countReal_ = count_;
        setBashaDraw();
    } else {
        for (int i = 0; i < count_; i++) {
            status::PlayerStatus& playerStatus = status::g_Party.getPlayerStatus(i);
            charaIndex_[i] = playerStatus.getHaveStatusInfo().getCharaIndex();
            if (playerStatus.getHaveStatusInfo().isDeath()) {
                charaIndex_[i] = 0x59;
            }
            dss::sprintf_s(path, sizeof(path), "data/chr/h%03d.pack", charaIndex_[i]);
            BillboardCharacter::setCamera(&TownCamera::getSingleton()->camera_.unk_004);
            int charaparam = dq5::level::g_LevelDataUtility.getCharaParamIndex(charaIndex_[i]);
            if (dq5::level::CharaData::getRecord(charaparam)->getWidth() < 0x20) {
                dq5::level::CharaData::getRecord(charaparam)->setWidth(0x20);
            }
            partyCharacter_[i].setCharacterSize(dq5::level::CharaData::getRecord(charaparam)->getWidth(), dq5::level::CharaData::getRecord(charaparam)->getHeight());
            partyCharacter_[i].setup(path, dq5::level::CharaData::loadSwitch_);
            partyCharacter_[i].setPosition(defaultPosition);
            partyCharacter_[i].setRotate(0);
            partyCharacter_[i].setShadowType(0);
            partyCharacter_[i].exec();
        }
    }
    if (status::g_StageInfo.sepiaFlag_) {
        for (int i = 0; i < countReal_; i++) {
            setHueChange(i, 1, 1);
        }
    }
    for (int i = 0; i < count_; i++) {
        if (getMemberCharaIndex(i) == 0xe3) {
            if (g_Global.getNowAreaNo() == 0xa || g_Global.getNowAreaNo() == 0x1e) {
                setAlpha(i, 0x10);
            } else {
                setAlpha(i, 0x1f);
            }
        } else {
            setAlpha(i, 0x1f);
        }
    }
}

THUMB void twn::TownPartyDraw::separateSetup()
{
    char path[128];
    int count = 0;
    for (int i = 1; i < 5; i++) {
        int index = status::PartyStatusUtility::getCarriageOutPlayer(i);
        if (index != -1) {
            int charaIndex = status::PlayerDataAll::getPlayerData(index).getCgIndex();
            if (status::PlayerDataAll::getPlayerData(index).getHp() == 0) {
                charaIndex = 0x59;
            }
            dss::sprintf_s(path, sizeof(path), "data/chr/h%03d.pack", charaIndex);
            BillboardCharacter::setCamera(&TownCamera::getSingleton()->camera_.unk_004);
            int charaparam = dq5::level::g_LevelDataUtility.getCharaParamIndex(charaIndex);
            if (dq5::level::CharaData::getRecord(charaparam)->getWidth() < 0x20) {
                dq5::level::CharaData::getRecord(charaparam)->setWidth(0x20);
            }
            separateChara_[count].setCharacterSize(dq5::level::CharaData::getRecord(charaparam)->getWidth(), dq5::level::CharaData::getRecord(charaparam)->getHeight());
            separateChara_[count].setup(path, dq5::level::CharaData::loadSwitch_);
            dss::Fix32Vector3 pos(cmn::g_cmnPartyInfo.separatePos_[count]);
            pos.vy.value += 0x808;
            separateChara_[count].setPosition(pos);
            separateChara_[count].setRotate(cmn::g_cmnPartyInfo.getCarriageOutDir(count));
            separateChara_[count].setShadowType(0);
            separateChara_[count].exec();
            separateCharaCount_++;
            count++;
        }
    }
}

THUMB void twn::TownPartyDraw::separatePos()
{
    for (int i = 1; i < count_; i++) {
        cmn::g_cmnPartyInfo.separatePos_[i - 1] = *partyCharacter_[i].getPosition();
        cmn::g_cmnPartyInfo.separateDir_[i - 1] = partyCharacter_[i].getRotate();
    }
}

THUMB void twn::TownPartyDraw::cleanup()
{
    for (int i = 0; i < countReal_; i++) {
        partyCharacter_[i].cleanup();
        if (dataObject_[i].getAddr()) {
            dataObject_[i].cleanup();
        }
    }
    for (int i = 0; i < separateCharaCount_; i++) {
        separateChara_[i].cleanup();
    }
    if (taimatsuSetup_ == 1) {
        taimatsu_.cleanup();
    }
    separateCharaCount_ = 0;
}

THUMB void twn::TownPartyDraw::draw()
{
    for (int i = 0; i < count_; i++) {
        partyCharacter_[i].draw();
    }
    if (status::PartyStatusUtility::isSeparate() == true && g_Global.getMapNameId() == cmn::g_cmnPartyInfo.getKeepMap()) {
        for (int i = 0; i < separateCharaCount_; i++) {
            separateChara_[i].draw();
        }
    }
    if (taimatsuFlag_ == 1 && taimatsuSetup_ == 1) {
        dss::Fix32Vector3 pos(*partyCharacter_[0].getPosition());
        dss::Fix32Vector3 vec;
        TownActionCalculate::getDirByIdx(partyCharacter_[0].getRotate(), vec);
        pos += vec * dss::Fix32(unk_02151940);
        taimatsu_.setPosition(pos);
        taimatsu_.setRotate(partyCharacter_[0].getRotate());
        taimatsu_.draw();
    }
}

THUMB void twn::TownPartyDraw::setPosition(int ctrl, const dss::Fix32Vector3& pos)
{
    dss::Fix32Vector3 newPos(pos);
    newPos.vy.value += 0xc0;
    partyCharacter_[ctrl].setPosition(newPos);
}

THUMB void twn::TownPartyDraw::setRotate(int index, int dirIdx)
{
    partyCharacter_[index].setRotate(dirIdx);
}

THUMB void twn::TownPartyDraw::resetAlpha()
{
    for (int i = 0; i < count_; i++) {
        if (getMemberCharaIndex(i) == 0xe3) {
            if (g_Global.getNowAreaNo() == 0xa || g_Global.getNowAreaNo() == 0x1e) {
                setAlpha(i, 0x10);
            } else {
                setAlpha(i, 0x1f);
            }
        } else {
            setAlpha(i, 0x1f);
        }
    }
}

THUMB void twn::TownPartyDraw::resetDrawPartyCount()
{
    for (int i = 0; i < count_; i++) {
        partyCharacter_[i].setDisplayEnable(1);
    }
}

THUMB void twn::TownPartyDraw::setDrawPartyOne()
{
    for (int i = 1; i < count_; i++) {
        partyCharacter_[i].setDisplayEnable(0);
        setAlpha(i, 0);
    }
}

THUMB bool twn::TownPartyDraw::isPartyDrawNone()
{
    for (int i = 0; i < count_; i++) {
        if (partyCharacter_[i].isDisplayEnable()) {
            return false;
        }
    }
    return true;
}

THUMB void twn::TownPartyDraw::setDrawPartyNone()
{
    for (int i = 0; i < count_; i++) {
        partyCharacter_[i].setDisplayEnable(0);
        setAlpha(i, 0);
    }
}

THUMB void twn::TownPartyDraw::setAnimationOne(int flag)
{
    partyCharacter_[0].setAnimFlag(flag);
}

THUMB void twn::TownPartyDraw::setAnimation(int flag)
{
    for (int i = 0; i < PARTY_MAX; i++) {
        if (BillboardCharacter::isAllAnimation() == false) {
            partyCharacter_[i].setAnimFlag(flag);
        } else if (flag == 1) {
            partyCharacter_[i].setAnimFlag(2);
        } else {
            partyCharacter_[i].setAnimFlag(flag);
        }
    }
}

THUMB void twn::TownPartyDraw::setWriggleCharacter(int flag)
{
    partyCharacter_[0].setWriggleFlag(flag);
}

THUMB void twn::TownPartyDraw::setWriggleCharaAll(int flag)
{
    for (int i = 0; i < countReal_; i++) {
        partyCharacter_[i].setWriggleFlag(flag);
    }
}

THUMB void twn::TownPartyDraw::setAlpha(int index, char value)
{
    partyDispAlpha_[index] = value;
    partyCharacter_[index].setAlpha((unsigned char)value);
}

THUMB void twn::TownPartyDraw::addAlpha(int index, char value)
{
    char maxA = 0x1f;
    if (getMemberCharaIndex(index) == 0xe3) {
        if (g_Global.getNowAreaNo() == 0xa || g_Global.getNowAreaNo() == 0x1e) {
            maxA = 0x10;
        }
    }
    partyDispAlpha_[index] += value;
    partyDispAlpha_[index] = dss::max<char>(0, partyDispAlpha_[index]);
    partyDispAlpha_[index] = dss::min<char>(maxA, partyDispAlpha_[index]);
    partyCharacter_[index].setAlpha((unsigned char)partyDispAlpha_[index]);
}

template <> THUMB char dss::min<char>(char a, char b)
{
    return (a < b) ? a : b;
}

template <> THUMB char dss::max<char>(char a, char b)
{
    return (a > b) ? a : b;
}

THUMB void twn::TownPartyDraw::execute()
{
    if (exe_ == 0) {
        return;
    }
    if (getDisplayFrame() & 1) {
        for (int i = 0; i < PARTY_MAX; i++) {
            partyCharacter_[i].setVisibleFlag(1);
            partyCharacter_[i].setBoxTestOff(true);
        }
    } else {
        for (int i = 0; i < PARTY_MAX; i++) {
            partyCharacter_[i].setVisibleFlag(0);
            partyCharacter_[i].execute();
        }
    }
}

THUMB void twn::TownPartyDraw::setExcute(bool flag)
{
    exe_ = flag;
    if (exe_ == 0) {
        for (int i = 0; i < PARTY_MAX; i++) {
            partyCharacter_[i].setVisibleFlag(1);
            partyCharacter_[i].setBoxTestOff(true);
        }
    }
}

THUMB void twn::TownPartyDraw::changePose(int playerIndex, int set)
{
    char path[128];
    int ctrl = -1;
    for (int i = 0; i < count_; i++) {
        if (playerIndex == status::g_Party.getPlayerStatus(i).index_) {
            ctrl = i;
            break;
        }
    }
    if (ctrl >= 0) {
        charaIndex_[ctrl] = set;
        partyCharacter_[ctrl].unkfunc_02055a60();
        if (dataObject_[ctrl].getAddr()) {
            dataObject_[ctrl].cleanup();
        }
        dss::sprintf_s(path, sizeof(path), "data/chr/h%03d.pack", set);
        OS_Wait();
        dataObject_[ctrl].setup(path, dq5::level::CharaData::loadSwitch_, 0);
        partyCharacter_[ctrl].setTextureWithHead(dataObject_[ctrl].getAddr());
        setPlayerSize(ctrl, set);
    }
}

THUMB void twn::TownPartyDraw::setPlayerSize(int index, int charaIndex)
{
    int charaparam = dq5::level::g_LevelDataUtility.getCharaParamIndex(charaIndex);
    if (dq5::level::CharaData::getRecord(charaparam)->getWidth() < 0x20) {
        dq5::level::CharaData::getRecord(charaparam)->setWidth(0x20);
    }
    partyCharacter_[index].setCharacterSize(dq5::level::CharaData::getRecord(charaparam)->getWidth(), dq5::level::CharaData::getRecord(charaparam)->getHeight());
}

THUMB void twn::TownPartyDraw::setSleep(int flag)
{
    for (int i = 0; i < count_; i++) {
        partyCharacter_[i].setSleep(flag);
    }
}

THUMB void twn::TownPartyDraw::requestCharacterReload()
{
    for (int i = 0; i < count_; i++) {
        partyCharacter_[i].requestReload();
    }
}

THUMB void twn::TownPartyDraw::setVanAndBasha()
{
    cleanup();
    status::g_Party.setDisplayMode();
    count_ = 3;
    countReal_ = count_;
    setBashaDraw();
}
