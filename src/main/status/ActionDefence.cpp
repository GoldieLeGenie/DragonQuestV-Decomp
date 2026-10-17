#include "main/status/ActionDefence.hpp"
#include "main/leveldata/MonsterData.hpp"
#include "main/dss/UnkRandom.hpp"

inline char dq5::level::MonsterData::getMera()
{
    return (byte_3 & 0x30) >> 4;
}

inline char dq5::level::MonsterData::getGira()
{
    return (byte_3 & 0xC0) >> 6;
}

inline char dq5::level::MonsterData::getIo()
{
    return byte_4 & 0x3;
}

inline char dq5::level::MonsterData::getHyado()
{
    return (byte_4 & 0xC) >> 2;
}

inline char dq5::level::MonsterData::getBagi()
{
    return (byte_4 & 0x30) >> 4;
}

inline char dq5::level::MonsterData::getDein()
{
    return (byte_4 & 0xC0) >> 6;
}

inline char dq5::level::MonsterData::getManusa()
{
    return byte_5 & 0x3;
}

inline char dq5::level::MonsterData::getRarihoma()
{
    return (byte_5 & 0xC) >> 2;
}

inline char dq5::level::MonsterData::getZaki()
{
    return (byte_5 & 0x30) >> 4;
}

inline char dq5::level::MonsterData::getNifram()
{
    return (byte_5 & 0xC0) >> 6;
}

inline char dq5::level::MonsterData::getMahotora()
{
    return byte_6 & 0x3;
}

inline char dq5::level::MonsterData::getMahoton()
{
    return (byte_6 & 0xC) >> 2;
}

inline char dq5::level::MonsterData::getMedapani()
{
    return (byte_6 & 0x30) >> 4;
}

inline char dq5::level::MonsterData::getRukani()
{
    return (byte_6 & 0xC0) >> 6;
}

inline char dq5::level::MonsterData::getRukanan()
{
    return byte_7 & 0x3;
}

inline char dq5::level::MonsterData::getMegante()
{
    return (byte_7 & 0xC) >> 2;
}

inline char dq5::level::MonsterData::getEmbrace()
{
    return (byte_7 & 0x30) >> 4;
}

inline char dq5::level::MonsterData::getPoison()
{
    return (byte_7 & 0xC0) >> 6;
}

inline char dq5::level::MonsterData::getVenom()
{
    return byte_8 & 0x3;
}

inline char dq5::level::MonsterData::getParalysis()
{
    return (byte_8 & 0xC) >> 2;
}

inline char dq5::level::MonsterData::getRest()
{
    return (byte_8 & 0x30) >> 4;
}

inline char dq5::level::MonsterData::getRegistBlizzard()
{
    return (byte_9 & 0xC) >> 2;
}

inline char dq5::level::MonsterData::getRegistFire()
{
    return (byte_9 & 0x30) >> 4;
}

inline char dq5::level::MonsterData::getRariho()
{
    return byte_10 & 0x3;
}

inline dq5::level::MonsterData* dq5::level::MonsterData::getRecord(int index)
{
    return (MonsterData*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline dq5::level::ActionParam* dq5::level::ActionParam::getRecord(int index)
{
    return (ActionParam*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned char dq5::level::ActionParam::getMagictype2()
{
    return magictype2;
}

inline char dq5::level::ActionParam::getManusa()
{
    return (byte_1 & 0x4) >> 2;
}

inline char dq5::level::ActionParam::getDefencetypePlayer()
{
    return byte_5 & 0x7;
}

inline char dq5::level::ActionParam::getDefencetype()
{
    return (byte_5 & 0x38) >> 3;
}

using namespace dq5::level;

THUMB status::ActionDefence::ActionDefence()
{
}

THUMB status::ActionDefence::~ActionDefence()
{
}

THUMB void status::ActionDefence::setup(unsigned short index, CharacterType type)
{
    disable_ = false;
    if (type == PLAYER) {
        setupPlayer(index);
    } else {
        setupMonster(index);
    }
}

THUMB void status::ActionDefence::setupPlayer(unsigned short index)
{
    characterType_ = PLAYER;
    io_ = 0;
    gira_ = 0;
    mera_ = 0;
    dein_ = 0;
    bagi_ = 0;
    hyado_ = 0;
    manusa_ = 0;
    rariho_ = 0;
    rarihoma_ = 0;
    zaki_ = 0;
    nifram_ = 3;
    mahotora_ = 0;
    mahotone_ = 0;
    medapani_ = 0;
    rukani_ = 3;
    rukanan_ = 0;
    megante_ = 0;
    fire_ = 0;
    blizzard_ = 0;
    poison_ = 0;
    venom_ = 0;
    rest_ = 0;
    spazz_ = 0;
    all_ = 0;
    half_ = 0;
    success_1_4_ = 0;
    success_1_6_ = 0;
    success_3_4_ = 0;
    success_3_8_ = 0;
    success_5_8_ = 0;
}

THUMB void status::ActionDefence::setupMonster(unsigned short index)
{
    characterType_ = MONSTER;
    MonsterData* monsterData = MonsterData::getRecord(index);
    io_ = monsterData->getIo();
    gira_ = monsterData->getGira();
    mera_ = monsterData->getMera();
    dein_ = monsterData->getDein();
    bagi_ = monsterData->getBagi();
    hyado_ = monsterData->getHyado();
    manusa_ = monsterData->getManusa();
    rariho_ = monsterData->getRariho();
    rarihoma_ = monsterData->getRarihoma();
    zaki_ = monsterData->getZaki();
    nifram_ = monsterData->getNifram();
    mahotora_ = monsterData->getMahotora();
    mahotone_ = monsterData->getMahoton();
    medapani_ = monsterData->getMedapani();
    rukani_ = monsterData->getRukani();
    rukanan_ = monsterData->getRukanan();
    megante_ = monsterData->getMegante();
    poison_ = monsterData->getPoison();
    venom_ = monsterData->getVenom();
    rest_ = monsterData->getRest();
    fire_ = monsterData->getRegistFire();
    blizzard_ = monsterData->getRegistBlizzard();
    spazz_ = monsterData->getParalysis();
    embrace_ = monsterData->getEmbrace();
}

THUMB int status::ActionDefence::getEffect(ActionParam::DEFENCETYPE type, unsigned char value)
{
    int ret = 0;
    if (characterType_ == PLAYER && disable_) {
        switch (value) {
        case 0:
            break;
        case 1:
            value = 0;
            break;
        case 2:
            value = 1;
            break;
        case 3:
            value = 2;
            break;
        case 4:
            value = 3;
            break;
        case 5:
            value = 4;
            break;
        case 6:
            value = 5;
            break;
        case 7:
            break;
        }
    }
    if (characterType_ == MONSTER && disable_) {
        switch (type) {
        case ActionParam::DEFENCETYPE_TYPE_A:
        case ActionParam::DEFENCETYPE_TYPE_B:
        case ActionParam::DEFENCETYPE_TYPE_C:
            type = ActionParam::DEFENCETYPE_TYPE_B;
            break;
        case ActionParam::DEFENCETYPE_TYPE_D:
        case ActionParam::DEFENCETYPE_TYPE_E:
        case ActionParam::DEFENCETYPE_TYPE_F:
            type = ActionParam::DEFENCETYPE_TYPE_E;
            break;
        }
    }
    switch (type) {
    case ActionParam::DEFENCETYPE_TYPE_A: {
        int rd = UnkDssRand::rand(1000);
        ret = 0;
        if (value == 0 && rd < 1000) {
            ret = 1000;
        }
        if (value == 1 && rd < 800) {
            ret = 1000;
        }
        if (value == 2 && rd < 330) {
            ret = 1000;
        }
        if (value == 3 && rd < 0) {
            ret = 1000;
        }
        break;
    }
    case ActionParam::DEFENCETYPE_TYPE_B: {
        int rd = UnkDssRand::rand(1000);
        ret = 0;
        if (value == 0 && rd < 1000) {
            ret = 1000;
        }
        if (value == 1 && rd < 1000) {
            ret = 1000;
        }
        if (value == 2 && rd < 660) {
            ret = 1000;
        }
        if (value == 3 && rd < 0) {
            ret = 1000;
        }
        break;
    }
    case ActionParam::DEFENCETYPE_TYPE_C: {
        int rd = UnkDssRand::rand(1000);
        ret = 0;
        if (value == 0 && rd < 1000) {
            ret = 1000;
        }
        if (value == 1 && rd < 750) {
            ret = 1000;
        }
        if (value == 2 && rd < 250) {
            ret = 1000;
        }
        if (value == 3 && rd < 100) {
            ret = 1000;
        }
        break;
    }
    case ActionParam::DEFENCETYPE_TYPE_D:
        if (value == 0) {
            ret = 1000;
        }
        if (value == 1) {
            ret = 800;
        }
        if (value == 2) {
            ret = 330;
        }
        if (value == 3) {
            ret = 0;
        }
        break;
    case ActionParam::DEFENCETYPE_TYPE_E:
        if (value == 0) {
            ret = 1000;
        }
        if (value == 1) {
            ret = 1000;
        }
        if (value == 2) {
            ret = 660;
        }
        if (value == 3) {
            ret = 0;
        }
        break;
    case ActionParam::DEFENCETYPE_TYPE_F:
        if (value == 0) {
            ret = 1000;
        }
        if (value == 1) {
            ret = 750;
        }
        if (value == 2) {
            ret = 250;
        }
        if (value == 3) {
            ret = 100;
        }
        break;
    case ActionParam::DEFENCETYPE_TYPE_Z: {
        int rd = UnkDssRand::rand(1000);
        ret = 0;
        if (value == 0 && rd < 1000) {
            ret = 1000;
        }
        if (value == 1 && rd < 750) {
            ret = 1000;
        }
        if (value == 2 && rd < 660) {
            ret = 1000;
        }
        if (value == 3 && rd < 500) {
            ret = 1000;
        }
        if (value == 4 && rd < 330) {
            ret = 1000;
        }
        if (value == 5 && rd < 250) {
            ret = 1000;
        }
        if (value == 6 && rd < 100) {
            ret = 1000;
        }
        if (value == 7 && rd < 0) {
            ret = 1000;
        }
        break;
    }
    }
    return ret;
}

THUMB int status::ActionDefence::calc(ActionParam::DEFENCE kind, ActionParam::DEFENCETYPE type, int actionIndex)
{
    int ret = 0;
    if (characterType_ == PLAYER && disable_) {
        return 1000;
    }
    switch (kind) {
    case ActionParam::DEFENCE_IO:
        ret = getEffect(type, io_);
        break;
    case ActionParam::DEFENCE_GIRA:
        ret = getEffect(type, gira_);
        break;
    case ActionParam::DEFENCE_MERA:
        ret = getEffect(type, mera_);
        break;
    case ActionParam::DEFENCE_DEIN:
        ret = getEffect(type, dein_);
        break;
    case ActionParam::DEFENCE_BAGI:
        ret = getEffect(type, bagi_);
        break;
    case ActionParam::DEFENCE_HYADO:
        ret = getEffect(type, hyado_);
        break;
    case ActionParam::DEFENCE_MANUSA:
        ret = getEffect(type, manusa_);
        break;
    case ActionParam::DEFENCE_RARIHO:
        ret = getEffect(type, rariho_);
        break;
    case ActionParam::DEFENCE_RARIHOMA:
        ret = getEffect(type, rarihoma_);
        break;
    case ActionParam::DEFENCE_ZAKI:
        ret = getEffect(type, zaki_);
        break;
    case ActionParam::DEFENCE_NIFRAM:
        ret = getEffect(type, nifram_);
        break;
    case ActionParam::DEFENCE_MAHOTORA:
        ret = getEffect(type, mahotora_);
        break;
    case ActionParam::DEFENCE_MAHOTOON:
        ret = getEffect(type, mahotone_);
        break;
    case ActionParam::DEFENCE_MEDAPANI:
        ret = getEffect(type, medapani_);
        break;
    case ActionParam::DEFENCE_SUKARA:
        ret = getEffect(type, sukara_);
        break;
    case ActionParam::DEFENCE_RUKANI:
        ret = getEffect(type, rukani_);
        break;
    case ActionParam::DEFENCE_RUKANAN:
        ret = getEffect(type, rukanan_);
        break;
    case ActionParam::DEFENCE_MEGANTE:
        ret = getEffect(type, megante_);
        break;
    case ActionParam::DEFENCE_POISON:
        ret = getEffect(type, poison_);
        break;
    case ActionParam::DEFENCE_VENOM:
        ret = getEffect(type, venom_);
        break;
    case ActionParam::DEFENCE_REST:
        ret = getEffect(type, rest_);
        break;
    case ActionParam::DEFENCE_FIRE:
        ret = getEffect(type, fire_);
        break;
    case ActionParam::DEFENCE_BLIZZARD:
        ret = getEffect(type, blizzard_);
        break;
    case ActionParam::DEFENCE_PARALYSIS:
        ret = getEffect(type, spazz_);
        break;
    case ActionParam::DEFENCE_ALL:
        ret = 1000;
        break;
    case ActionParam::DEFENCE_HALF:
        ret = 0;
        if (UnkDssRand::rand(1000) < 500) {
            ret = 1000;
        }
        break;
    case ActionParam::DEFENCE_SUCCESS_4TH:
        ret = 0;
        if (UnkDssRand::rand(1000) < 250) {
            ret = 1000;
        }
        break;
    case ActionParam::DEFENCE_SUCCESS_6TH:
        ret = 0;
        if (UnkDssRand::rand(1000) < 166) {
            ret = 1000;
        }
        break;
    case ActionParam::DEFENCE_SUCCESS_8TH:
        ret = 0;
        if (UnkDssRand::rand(1000) < 125) {
            ret = 1000;
        }
        break;
    case ActionParam::DEFENCE_SUCCESS_3_4:
        ret = 0;
        if (UnkDssRand::rand(1000) < 750) {
            ret = 1000;
        }
        break;
    case ActionParam::DEFENCE_SUCCESS_3_8:
        ret = 0;
        if (UnkDssRand::rand(1000) < 375) {
            ret = 1000;
        }
        break;
    case ActionParam::DEFENCE_SUCCESS_5_8:
        ret = 0;
        if (UnkDssRand::rand(1000) < 625) {
            ret = 1000;
        }
        break;
    case ActionParam::DEFENCE_ENCOUNT:
        break;
    }
    return ret;
}

THUMB int status::ActionDefence::getEffectAI(ActionParam::DEFENCETYPE type, unsigned char value)
{
    int ret = 0;
    switch (type) {
    case ActionParam::DEFENCETYPE_TYPE_A: {
        int rd = UnkDssRand::rand(1000);
        ret = 0;
        if (value == 0 && rd < 1000) {
            ret = 1000;
        }
        if (value == 1) {
            ret = 800;
        }
        if (value == 2) {
            ret = 330;
        }
        if (value == 3) {
            ret = 0;
        }
        break;
    }
    case ActionParam::DEFENCETYPE_TYPE_B:
        UnkDssRand::rand(1000);
        ret = 0;
        if (value == 0) {
            ret = 1000;
        }
        if (value == 1) {
            ret = 1000;
        }
        if (value == 2) {
            ret = 660;
        }
        if (value == 3) {
            ret = 0;
        }
        break;
    case ActionParam::DEFENCETYPE_TYPE_C:
        UnkDssRand::rand(1000);
        ret = 0;
        if (value == 0) {
            ret = 1000;
        }
        if (value == 1) {
            ret = 750;
        }
        if (value == 2) {
            ret = 250;
        }
        if (value == 3) {
            ret = 0;
        }
        break;
    case ActionParam::DEFENCETYPE_TYPE_D:
        if (value == 0) {
            ret = 1000;
        }
        if (value == 1) {
            ret = 800;
        }
        if (value == 2) {
            ret = 330;
        }
        if (value == 3) {
            ret = 0;
        }
        break;
    case ActionParam::DEFENCETYPE_TYPE_E:
        if (value == 0) {
            ret = 1000;
        }
        if (value == 1) {
            ret = 1000;
        }
        if (value == 2) {
            ret = 660;
        }
        if (value == 3) {
            ret = 0;
        }
        break;
    case ActionParam::DEFENCETYPE_TYPE_F:
        if (value == 0) {
            ret = 1000;
        }
        if (value == 1) {
            ret = 750;
        }
        if (value == 2) {
            ret = 250;
        }
        if (value == 3) {
            ret = 100;
        }
        break;
    }
    return ret;
}

THUMB int status::ActionDefence::calcAI(ActionParam::DEFENCE kind, ActionParam::DEFENCETYPE type, int actionIndex)
{
    int ret;
    switch (kind) {
    case ActionParam::DEFENCE_IO:
        ret = getEffectAI(type, io_);
        break;
    case ActionParam::DEFENCE_GIRA:
        ret = getEffectAI(type, gira_);
        break;
    case ActionParam::DEFENCE_MERA:
        ret = getEffectAI(type, mera_);
        break;
    case ActionParam::DEFENCE_DEIN:
        ret = getEffectAI(type, dein_);
        break;
    case ActionParam::DEFENCE_BAGI:
        ret = getEffectAI(type, bagi_);
        break;
    case ActionParam::DEFENCE_HYADO:
        ret = getEffectAI(type, hyado_);
        break;
    case ActionParam::DEFENCE_MANUSA:
        ret = getEffectAI(type, manusa_);
        break;
    case ActionParam::DEFENCE_RARIHO:
        ret = getEffectAI(type, rariho_);
        break;
    case ActionParam::DEFENCE_RARIHOMA:
        ret = getEffectAI(type, rarihoma_);
        break;
    case ActionParam::DEFENCE_ZAKI:
        ret = getEffectAI(type, zaki_);
        break;
    case ActionParam::DEFENCE_NIFRAM:
        ret = getEffectAI(type, nifram_);
        break;
    case ActionParam::DEFENCE_MAHOTORA:
        ret = getEffectAI(type, mahotora_);
        break;
    case ActionParam::DEFENCE_MAHOTOON:
        ret = getEffectAI(type, mahotone_);
        break;
    case ActionParam::DEFENCE_MEDAPANI:
        ret = getEffectAI(type, medapani_);
        break;
    case ActionParam::DEFENCE_SUKARA:
        ret = getEffectAI(type, sukara_);
        break;
    case ActionParam::DEFENCE_RUKANI:
        ret = getEffectAI(type, rukani_);
        break;
    case ActionParam::DEFENCE_RUKANAN:
        ret = getEffectAI(type, rukanan_);
        break;
    case ActionParam::DEFENCE_MEGANTE:
        ret = getEffectAI(type, megante_);
        break;
    case ActionParam::DEFENCE_POISON:
        ret = getEffectAI(type, poison_);
        break;
    case ActionParam::DEFENCE_VENOM:
        ret = getEffectAI(type, venom_);
        break;
    case ActionParam::DEFENCE_REST:
        ret = getEffectAI(type, rest_);
        break;
    case ActionParam::DEFENCE_FIRE:
        ret = getEffectAI(type, fire_);
        break;
    case ActionParam::DEFENCE_BLIZZARD:
        ret = getEffectAI(type, blizzard_);
        break;
    case ActionParam::DEFENCE_PARALYSIS:
        ret = getEffectAI(type, spazz_);
        break;
    case ActionParam::DEFENCE_ALL:
        ret = 1000;
        break;
    case ActionParam::DEFENCE_HALF:
        ret = 500;
        break;
    case ActionParam::DEFENCE_SUCCESS_4TH:
        ret = 250;
        break;
    case ActionParam::DEFENCE_SUCCESS_6TH:
        ret = 166;
        break;
    case ActionParam::DEFENCE_SUCCESS_8TH:
        ret = 125;
        break;
    case ActionParam::DEFENCE_SUCCESS_3_4:
        ret = 750;
        break;
    case ActionParam::DEFENCE_SUCCESS_3_8:
        ret = 375;
        break;
    case ActionParam::DEFENCE_SUCCESS_5_8:
        ret = 625;
        break;
    case ActionParam::DEFENCE_ENCOUNT:
        break;
    }
    return ret;
}

THUMB int status::ActionDefence::getEffectValue(int actionIndex)
{
    ActionParam::DEFENCE kind = (ActionParam::DEFENCE)ActionParam::getRecord(actionIndex)->getMagictype2();
    ActionParam::DEFENCETYPE type = (ActionParam::DEFENCETYPE)ActionParam::getRecord(actionIndex)->getDefencetype();
    if (characterType_ == PLAYER) {
        ActionParam::getRecord(actionIndex);
        int value = ActionParam::getRecord(actionIndex)->getDefencetypePlayer();
        return getEffect(ActionParam::DEFENCETYPE_TYPE_Z, value);
    }
    return calc(kind, type, actionIndex);
}

THUMB int status::ActionDefence::getEffectValueAI(int actionIndex)
{
    ActionParam::DEFENCE kind = (ActionParam::DEFENCE)ActionParam::getRecord(actionIndex)->getMagictype2();
    ActionParam::DEFENCETYPE type = (ActionParam::DEFENCETYPE)ActionParam::getRecord(actionIndex)->getDefencetype();
    if (characterType_ == PLAYER) {
        ActionParam::getRecord(actionIndex);
        int value = ActionParam::getRecord(actionIndex)->getDefencetypePlayer();
        return getEffect(ActionParam::DEFENCETYPE_TYPE_Z, value);
    }
    return calcAI(kind, type, actionIndex);
}
