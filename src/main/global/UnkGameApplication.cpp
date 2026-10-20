#pragma ipa file
#include "main/global/UnkGameApplication.hpp"
#include "main/global/Global.hpp"
#include "main/global/GlobalGamePart.hpp"
#include "main/global/StageLink.hpp"
#include "main/global/UnkGlobalSystem.hpp"
#include "main/global/UnkProtectCheck.hpp"
#include "main/btl/Encount.hpp"
#include "main/btl/UnkBattleMapList.hpp"
#include "main/data/FileLoader.hpp"
#include "main/dss/DssCore.hpp"
#include "main/dss/UnkArrayWarning.hpp"
#include "main/dss/UnkBgText.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/dss/UnkDisplayPlugin.hpp"
#include "main/dss/UnkFog.hpp"
#include "main/dss/UnkLanguage.hpp"
#include "main/dss/UnkMemory.hpp"
#include "main/dss/UnkSystemText.hpp"
#include "main/dss/UnkTextConvert.hpp"
#include "main/dss/VramTransferManager.hpp"
#include "main/leveldata/LevelData.hpp"
#include "main/menu/UnkMenuSystem.hpp"
#include "main/object/GameMonsterData.hpp"
#include "main/part/BattlePart.hpp"
#include "main/part/BookPart.hpp"
#include "main/part/CardCheckPart.hpp"
#include "main/part/CasinoPart.hpp"
#include "main/part/CeremonyPart.hpp"
#include "main/part/FieldPart.hpp"
#include "main/part/GameEndPart.hpp"
#include "main/part/GameStartPart.hpp"
#include "main/part/MPExchangePart.hpp"
#include "main/part/SlimeRacePart.hpp"
#include "main/part/SlimeTouchPart.hpp"
#include "main/part/TownPart.hpp"
#include "main/part/UnkBattleMenuPart.hpp"
#include "main/part/UnkMenuPart.hpp"
#include "main/part/UnkTitlePart.hpp"
#include "main/sound/SoundManager.hpp"
#include "main/status/GameStatus.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/PlayerData.hpp"
#include "main/status/Status.hpp"
#include "main/text/TextAPI.hpp"
#include "main/text/TextHook.hpp"
#include "nitro/g2.hpp"
#include "nitro/g3.hpp"
#include "nitro/gx.h"
#include "ov006/mp/UnkWH.hpp"

inline UnkAppBuildDate::UnkAppBuildDate()
{
    const char* date = "Oct 24 2008";
    date_ = "Oct 24 2008";
    strcpy(time_, "21:44:36");
    strcpy(dateString_, date);
}

unsigned char data_02093480[76] = {
    0x00, 0x00, 0x69, 0x6e, 0x50, 0x5c, 0x5a, 0x6c, 0x5a, 0x78, 0x64, 0x69, 0x7b, 0x69, 0x70, 0x67,
    0x78, 0x6e, 0x69, 0x55, 0x64, 0x73, 0x73, 0x41, 0x5f, 0x55, 0x50, 0x55, 0x55, 0x4b, 0x3c, 0x5a,
    0x00, 0x00, 0x00, 0x3c, 0x73, 0x64, 0x50, 0x55, 0x55, 0x5a, 0x5a, 0x41, 0x50, 0x4b, 0x50, 0x50,
    0x5a, 0x5a, 0x64, 0x46, 0x73, 0x41, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x7f, 0x7f, 0x7f,
    0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f,
};

static short LinkList[310][2] = {
    { 0, 0 }, { 1, 42 }, { 2, 2 }, { 3, 3 }, { 4, 40 }, { 5, 5 }, { 6, 6 }, { 7, 7 },
    { 8, 8 }, { 9, 9 }, { 10, 23 }, { 11, 11 }, { 12, 12 }, { 13, 33 }, { 14, 14 }, { 15, 15 },
    { 16, 42 }, { 17, 35 }, { 18, 18 }, { 19, 19 }, { 20, 6 }, { 21, 21 }, { 22, 8 }, { 23, 23 },
    { 24, 3 }, { 25, 25 }, { 26, 26 }, { 27, 113 }, { 28, 5 }, { 29, 11 }, { 30, 30 }, { 31, 15 },
    { 32, 19 }, { 33, 33 }, { 34, 2 }, { 35, 35 }, { 36, 36 }, { 37, 37 }, { 38, 38 }, { 39, 39 },
    { 40, 40 }, { 41, 7 }, { 42, 42 }, { 43, 8 }, { 44, 87 }, { 45, 222 }, { 46, 46 }, { 47, 35 },
    { 48, 48 }, { 49, 26 }, { 50, 152 }, { 51, 51 }, { 52, 73 }, { 53, 53 }, { 54, 93 }, { 55, 55 },
    { 0, 0 }, { 57, 18 }, { 58, 33 }, { 0, 0 }, { 60, 60 }, { 61, 61 }, { 62, 46 }, { 63, 37 },
    { 64, 64 }, { 65, 65 }, { 66, 89 }, { 67, 74 }, { 68, 68 }, { 69, 109 }, { 70, 15 }, { 71, 38 },
    { 72, 72 }, { 73, 73 }, { 74, 74 }, { 75, 9 }, { 76, 76 }, { 77, 36 }, { 78, 46 }, { 79, 53 },
    { 80, 80 }, { 81, 21 }, { 82, 152 }, { 83, 99 }, { 84, 51 }, { 85, 12 }, { 86, 120 }, { 87, 87 },
    { 88, 88 }, { 89, 89 }, { 90, 133 }, { 91, 18 }, { 92, 183 }, { 93, 93 }, { 94, 94 }, { 95, 95 },
    { 96, 96 }, { 97, 117 }, { 98, 98 }, { 99, 99 }, { 100, 61 }, { 101, 74 }, { 102, 102 }, { 103, 30 },
    { 104, 104 }, { 105, 105 }, { 106, 222 }, { 107, 107 }, { 108, 108 }, { 109, 109 }, { 110, 68 }, { 111, 215 },
    { 112, 112 }, { 113, 113 }, { 114, 193 }, { 115, 95 }, { 116, 116 }, { 117, 117 }, { 118, 140 }, { 119, 119 },
    { 120, 120 }, { 121, 94 }, { 122, 96 }, { 123, 74 }, { 124, 153 }, { 125, 105 }, { 126, 126 }, { 127, 104 },
    { 128, 128 }, { 129, 129 }, { 130, 65 }, { 131, 131 }, { 132, 132 }, { 133, 133 }, { 134, 119 }, { 135, 135 },
    { 136, 117 }, { 137, 112 }, { 138, 138 }, { 139, 139 }, { 140, 140 }, { 141, 105 }, { 142, 142 }, { 143, 143 },
    { 144, 35 }, { 145, 108 }, { 146, 113 }, { 147, 87 }, { 148, 107 }, { 149, 149 }, { 150, 128 }, { 151, 129 },
    { 152, 152 }, { 153, 153 }, { 154, 132 }, { 155, 138 }, { 156, 135 }, { 157, 142 }, { 158, 184 }, { 159, 35 },
    { 160, 160 }, { 161, 98 }, { 162, 107 }, { 163, 163 }, { 164, 164 }, { 165, 165 }, { 166, 166 }, { 167, 152 },
    { 168, 120 }, { 169, 143 }, { 170, 181 }, { 171, 135 }, { 172, 172 }, { 173, 196 }, { 174, 174 }, { 175, 142 },
    { 176, 61 }, { 177, 177 }, { 178, 178 }, { 179, 68 }, { 180, 180 }, { 181, 181 }, { 182, 166 }, { 183, 183 },
    { 184, 184 }, { 185, 143 }, { 186, 138 }, { 187, 55 }, { 188, 188 }, { 189, 21 }, { 190, 160 }, { 191, 163 },
    { 192, 192 }, { 193, 193 }, { 194, 177 }, { 195, 178 }, { 196, 196 }, { 197, 164 }, { 198, 172 }, { 199, 206 },
    { 200, 30 }, { 201, 201 }, { 202, 202 }, { 0, 0 }, { 0, 0 }, { 205, 205 }, { 206, 206 }, { 207, 60 },
    { 208, 208 }, { 209, 201 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 213, 202 }, { 214, 214 }, { 215, 215 },
    { 216, 205 }, { 217, 208 }, { 0, 0 }, { 219, 214 }, { 0, 0 }, { 0, 0 }, { 222, 222 }, { 0, 0 },
    { 224, 36 }, { 225, 18 }, { 226, 226 }, { 227, 227 }, { 228, 228 }, { 229, 229 }, { 230, 230 }, { 231, 231 },
    { 232, 232 }, { 233, 232 }, { 234, 232 }, { 235, 87 }, { 236, 240 }, { 237, 241 }, { 238, 242 }, { 239, 243 },
    { 240, 240 }, { 241, 241 }, { 242, 242 }, { 243, 243 }, { 0, 0 }, { 245, 245 },
};

UnkGameApplication data_0209ce9c;
UnkAppBuildDate data_0209ce48;
UnkBattleMapList data_0209ce6c;

ARM void UnkGameApplication::vf00()
{
    initHeap(&data_020fd24c, 0x20000, 0x8000, 0x280000, 0);
    dss::g_File.unkfunc_0204b1cc(0);
    vf04();
    bgChar_.setup("data/G2D/SYSTEM/bg.bgc", 0, 0);
    bgChar2_.setup("data/G2D/SYSTEM/bg.bgc", 0, 0);
    bgPltt_.setup("data/G2D/SYSTEM/bg.bgp", 0, 0);
    objChar_.setup("data/G2D/SYSTEM/obj.bgc", 0, 0);
    objPltt_.setup("data/G2D/SYSTEM/obj.bgp", 0, 0);
    initSystemText(bgChar_.getAddr(), bgChar2_.getAddr(), bgPltt_.getAddr(), objChar_.getAddr(), objPltt_.getAddr());
    font12_.setup("data/G2D/FONT/zen12.nftr", 0, 0);
    font12Half_.setup("data/G2D/FONT/han12.nftr", 0, 0);
    font10_.setup("data/G2D/FONT/zen10.nftr", 0, 0);
    font10Half_.setup("data/G2D/FONT/han10.nftr", 0, 0);
    unkfunc_0204df4c();
    unkfunc_0204df60(font12_.getAddr(), font12Half_.getAddr());
    unkfunc_0204df84(font10_.getAddr(), font10Half_.getAddr());
    table81_.setup("DATA/G2D/BIN/81_9F.bin", 0, 0);
    tableE0_.setup("DATA/G2D/BIN/E0_EF.bin", 0, 0);
    initSjisTables((unsigned short*)table81_.getAddr(), table81_.getSize(), (unsigned short*)tableE0_.getAddr(), tableE0_.getSize());
    data_020f6f9c.unkfunc_0204aff4();
    unkfunc_0206c6bc("MESS5", "MENULIST");
    func_020624a8();
    TextAPI::unkfunc_0206cb34();
    g_text_env.m_text_hook = &gTextHook;
    g_text_extractor.unkfunc_0206d9ec(&data_020ef2e0);
    int region = getGameRegion();
    OSOwnerInfo info;
    func_020887c8(&info);
    if (region == 1) {
        status::g_Game.setLanguage(Japanese);
        TextAPI::setLanguage(Japanese);
    }
    if (region == 2) {
        switch (info.language) {
        case 1:
            status::g_Game.setLanguage(English);
            break;
        case 2:
            status::g_Game.setLanguage(French);
            break;
        case 5:
            status::g_Game.setLanguage(Spanish);
            break;
        default:
            status::g_Game.setLanguage(English);
            break;
        }
    }
    if (region == 3) {
        switch (info.language) {
        case 1:
            status::g_Game.setLanguage(English);
            break;
        case 2:
            status::g_Game.setLanguage(French);
            break;
        case 3:
            status::g_Game.setLanguage(German);
            break;
        case 4:
            status::g_Game.setLanguage(Italian);
            break;
        case 5:
            status::g_Game.setLanguage(Spanish);
            break;
        default:
            status::g_Game.setLanguage(English);
            break;
        }
    }
    SoundManager::initialize((void*)"data/sound/sound_data.sdat", dssAlloc(&data_020fd24c, 0xb0400, 0x20), 0xb0400, 0, 0x5a, 0x5b, data_02093480);
    vf0c();
    vf08();
    unkfunc_02008d5c();
    unkfunc_0204c0b4(2);
}

ARM void UnkGameApplication::vf04()
{
    GX_SetGraphicsMode((GXDisplayMode)1, (GXBGMode)0, (GX2D3D)1);
    GX_SetBankForTex((GXVRam)3);
    GX_SetBankForTexPltt((GXVRam)0x40);
    GX_SetBankForBg((GXVRam)0x10);
    GX_SetBankForObj((GXVRam)0x20);
    GX_SetBGScrOffset(0);
    GX_SetBGCharOffset(0);
    G2_SetBG1Control(0, 0, 0xe, 0, 0);
    G2_SetBG2ControlText(0, 0, 0xf, 0);
    G2_SetBG3ControlText(0, 0, 7, 0);
    GXS_SetGraphicsMode(0);
    GX_SetBankForSubBg((GXVRam)0x80);
    GX_SetBankForSubObj((GXVRam)0x100);
    G2S_SetBG0Control(0, 0, 7, 0, 0);
    G2S_SetBG1Control(0, 0, 7, 0, 0);
    G2S_SetBG2ControlText(0, 0, 7, 0);
    G2S_SetBG3ControlText(0, 0, 7, 0);
    *(vu16*)0x04000060 = (u16)((*(vu16*)0x04000060 & ~0x3000) | 8);
    func_02075ecc(0, 31, 0x7fff, 63, 1);
    initFog();
    data_020f4f74.initTransferQueue();
    GX_DispOn();
    GXS_DispOn();
    GX_SetDispSelect(0);
}

ARM void UnkGameApplication::vf08()
{
}

ARM void UnkGameApplication::vf0c()
{
    data_0209aea0 = 0;
    data_02101c88.unkfunc_020517c0(TITLE_PART, &data_0209cf9c);
    data_02101c88.unkfunc_020517c0(BOOK_PART, &g_BookPart);
    data_02101c88.unkfunc_020517c0(CASINO_PART, &g_CasinoPart);
    data_02101c88.unkfunc_020517c0(SLIME_RACE_PART, &g_SlimeRacePart);
    data_02101c88.unkfunc_020517c0(SLIME_TOUCH_PART, &g_SlimeTouchPart);
    data_02101c88.unkfunc_020517c0(MENU_PART, &data_0209cfd0);
    data_02101c88.unkfunc_020517c0(CEREMONY_PART, &g_CeremonyPart);
    data_02101c88.unkfunc_020517c0(GAME_START_PART, &g_GameStartPart);
    data_02101c88.unkfunc_020517c0(TOWN_PART, &g_TownPart);
    data_02101c88.unkfunc_020517c0(BATTLE_PART, &g_BattlePart);
    data_02101c88.unkfunc_020517c0(FIELD_PART, &g_FieldPart);
    data_02101c88.unkfunc_020517c0(BATTLE_MENU_PART, &data_0209cf54);
    data_02101c88.unkfunc_020517c0(CARDCHECK_PART, &g_CardCheckPart);
    data_02101c88.unkfunc_020517c0(GAME_END_PART, &g_GameEndPart);
    data_02101c88.unkfunc_020517c0(MPEXCHANGE_PART, &g_MPExchangePart);
    UnkGlobalSystem::unkfunc_0205183c(unkfunc_02008e54);
    UnkGlobalSystem::unkfunc_0205182c(unkfunc_02008e6c);
    UnkGlobalSystem::unkfunc_0205184c(unkfunc_02008e84);
    unkfunc_02067b00(unkfunc_02008e98);
    data_02101c88.unk_78 = 0;
}

ARM void UnkGameApplication::unkfunc_02008d5c()
{
    GameMonsterData::unkfunc_02058098(LinkList);
    data_0209ce6c.unkfunc_0206da18("data/btlmap/_list.txt");
    unkfunc_0204c9d8(&dss::g_DISPLAYPLUGIN_SINGLE3D);
    dq5::level::levelData.setup();
    status::PlayerDataAll::initialize(true);
    const char* name = "BAG";
    switch (status::g_Game.language_) {
    case Japanese:
        name = "\xe3\x81\xb5\xe3\x81\x8f\xe3\x82\x8d";
        break;
    case English:
        name = "Bag";
        break;
    case French:
        name = "Sac";
        break;
    case German:
        name = "Beutel";
        break;
    case Italian:
        name = "Borsa";
        break;
    case Spanish:
        name = "Bolsa";
        break;
    }
    status::g_Party.haveItemSack_.setNameString(name);
    g_Global.initialize();
    status::Status::initialize_character();
    util::StageLink::initialize();
    btl::Encount::getSingleton()->enable_ = 1;
    unkfunc_02086df0();
}

ARM void UnkGameApplication::vf14()
{
}

ARM void UnkGameApplication::unkfunc_02008e54()
{
    g_Global.initialize();
    status::Status::initialize_character();
}

ARM void UnkGameApplication::unkfunc_02008e6c()
{
    status::g_Game.addPlayTime(1);
}

ARM void UnkGameApplication::unkfunc_02008e84()
{
    g_Global.partChangeFlag_ = 0;
}

ARM void UnkGameApplication::unkfunc_02008e98()
{
    SoundManager::update();
}

ARM int UnkGameApplication::vf10()
{
    return CARDCHECK_PART;
}

ARM UnkGameApplication::~UnkGameApplication()
{
}

ARM void DssApplication::vf14()
{
}

ARM int DssApplication::vf10()
{
    return 0;
}

ARM void DssApplication::vf0c()
{
}

ARM void DssApplication::vf08()
{
}

ARM void DssApplication::vf04()
{
}

ARM void DssApplication::vf00()
{
}
