#include "ov019/materielmenu/MaterielMenu_WINDOW_MANAGER.hpp"
#include "ov019/materielmenu/MaterielMenuPlayerControl.hpp"
#include "ov019/materielmenu/common/MaterielMenu_ChildName.hpp"
#include "ov019/materielmenu/common/MaterielMenu_SCRIPT.hpp"
#include "ov019/leveldata/ChurchMessage.hpp"
#include "ov019/townmenu/town_item/TownMenuItemSelectChara.hpp"
#include "ov019/townmenu/town_item/UnkTownMenuItemCharaSelect.hpp"
#include "ov012/materielmenu/MaterielMenuPokerBetcoin.hpp"
#include "ov001/town/TownCharacterManager.hpp"
#include "ov001/town/TownSugorokuManager.hpp"
#include "ov012/materielmenu/MaterielMenu_SLOT.hpp"
#include "ov012/materielmenu/MaterielMenuPokerChangecard.hpp"
#include "ov012/materielmenu/MaterielMenu_POKER_HIGHANDLOW.hpp"
#include "ov023/leveldata/InnMessage.hpp"
#include "ov023/materielmenu/inn/MaterielMenu_INN_ROOT.hpp"
#include "ov024/materielmenu/casino/MaterielMenu_SlimeTouch.hpp"
#include "ov024/materielmenu/casino/MaterielMenu_TouchResult.hpp"
#include "ov025/materielmenu/surechigai/UnkMaterielMenu_02187c60.hpp"
#include "ov025/materielmenu/surechigai/UnkMaterielMenu_02187c7c.hpp"
#include "ov025/materielmenu/surechigai/UnkMaterielMenu_02187c98.hpp"
#include "ov025/materielmenu/surechigai/UnkMaterielMenu_02187cb4.hpp"
#include "ov025/materielmenu/surechigai/UnkMaterielMenu_02187cec.hpp"
#include "ov026/materielmenu/church/MaterielMenu_CHURCH_ROOT.hpp"
#include "ov026/materielmenu/church/MaterielMenu_CHURCH_MIRACLE.hpp"
#include "ov026/materielmenu/common/MaterielMenu_SAVE.hpp"
#include "ov027/leveldata/GiftMessage.hpp"
#include "ov027/leveldata/MedalMessage.hpp"
#include "ov027/leveldata/ShopMessage.hpp"
#include "ov027/materielmenu/changegift/MaterielMenu_CHANGEGIFT_ROOT.hpp"
#include "ov027/materielmenu/medalking/MaterielMenu_MEDALKING_ROOT.hpp"
#include "ov027/materielmenu/shop/MaterielMenu_SHOP_MANAGER.hpp"
#include "ov027/materielmenu/shop/MaterielMenu_SHOP_ROOT.hpp"
#include "ov028/materielmenu/sugoroku/MaterielMenu_SUGOROKU_GETITEM.hpp"
#include "ov028/materielmenu/sugoroku/MaterielMenu_SUGOROKU_ROOT.hpp"
#include "ov029/leveldata/CoinMessage.hpp"
#include "ov029/materielmenu/coinsaleroom/MaterielMenu_COINSALEROOM_BUY.hpp"
#include "ov029/materielmenu/coinsaleroom/MaterielMenu_COINSALEROOM_ROOT.hpp"
#include "ov030/leveldata/GoldMessage.hpp"
#include "ov030/materielmenu/bank/MaterielMenu_BANK_ROOT.hpp"
#include "ov030/materielmenu/bank/MaterielMenu_BANK_DRAW.hpp"
#include "ov030/materielmenu/bank/MaterielMenu_BANK_PUTIN.hpp"
#include "ov031/leveldata/HukubikiMessage.hpp"
#include "ov031/materielmenu/hukubiki/MaterielMenu_HUKUBIKI_ROOT.hpp"
#include "ov031/materielmenu/hukubiki/MaterielMenu_HUKUBIKI_SELECTCHARA.hpp"
#include "ov032/leveldata/JisanMessage.hpp"
#include "ov032/materielmenu/jisan/MaterielMenu_JISAN_LEAVE_SCRIPT.hpp"
#include "ov032/materielmenu/jisan/MaterielMenu_JISAN_ROOT.hpp"
#include "ov033/leveldata/LuidaMessage.hpp"
#include "ov033/materielmenu/luida/MaterielMenu_LUIDA_ROOT.hpp"
#include "ov034/materielmenu/casino/MaterielMenu_RaceEntrance.hpp"
#include "ov034/materielmenu/casino/MaterielMenu_RaceResult.hpp"
#include "ov034/materielmenu/casino/MaterielMenu_SlimeRace.hpp"
#include "ov035/materielmenu/meisanhin/MaterielMenu_MEISANHIN_ROOT.hpp"
#include "ov035/materielmenu/meisanhin/MaterielMenu_MIMI_DETAIL.hpp"
#include "ov035/materielmenu/meisanhin/MaterielMenu_MIMI_ROOT.hpp"
#include "ov037/materielmenu/casino/MaterielMenu_FIGHT_STADIUM.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/cmn/TalkSoundManager.hpp"
#include "main/global/Global.hpp"
#include "main/leveldata/HukubikiPrize.hpp"
#include "main/leveldata/MeisanhinData.hpp"
#include "main/leveldata/SurechigaiData.hpp"
#include "main/menu/MaterielMenu_SlotEnter.hpp"
#include "main/menu/UiMsg.hpp"
#include "main/menu/UnkMenuOverlay.hpp"
#include "main/status/MenuStatus.hpp"
#include "main/status/StageInfo.hpp"

using menu::MaterielMenuPlayerControl;

MaterielMenu_WINDOW_MANAGER data_ov019_02186704;

THUMB MaterielMenu_WINDOW_MANAGER* MaterielMenu_WINDOW_MANAGER::getSingleton()
{
    return &data_ov019_02186704;
}

THUMB void MaterielMenu_WINDOW_MANAGER::openMaterielWindow(int menuType)
{
    int ctrlID;
    menuType_ = menuType;
    ctrlID = cmn::g_cmnPartyInfo.ctrlID_;
    switch (menuType) {
        case MENU_INN:
        case MENU_INN_TYPE2:
        case MENU_EXTRA_INN:
        case MENU_SUGOROKU_INN: {
            int innType = 0;
            MaterielMenuPlayerControl::getSingleton()->initialize();
            int voice = 0x32;
            if (menuType == MENU_SUGOROKU_INN) {
                ui_MsgSndSet(voice);
            } else {
                if (status::g_Menu.ownerVoice_ == 0x30) {
                    voice = cmn::g_talkSound.getCharacterVoice(ctrlID);
                    status::g_Menu.ownerVoice_ = voice;
                }
                ui_MsgSndSet(voice);
            }
            loadMaterielMenuOverlay(1);
            dq5::level::InnMessage::setup();
            if (menuType == MENU_SUGOROKU_INN) {
                innType = 2;
            } else if (TownCharacterManager::getSingleton()->getCharaIndex(ctrlID) == 0xf) {
                innType = 1;
            }
            gMaterielMenu_INN_ROOT.innType_ = (MaterielMenu_INN_ROOT::INN_TYPE)innType;
            gMaterielMenu_INN_ROOT.open();
            break;
        }
        case MENU_CHURCH:
        case MENU_CHURCH_TYPE2:
            loadMaterielMenuOverlay(2);
            ui_MsgSndSet(cmn::g_talkSound.getCharacterVoice(ctrlID));
            dq5::level::ChurchMessage::setup();
            gMaterielMenu_CHURCH_ROOT.open();
            break;
        case MENU_CHURCH_MIRACLE:
            loadMaterielMenuOverlay(2);
            dq5::level::ChurchMessage::setup();
            gMaterielMenu_CHURCH_MIRACLE.open();
            break;
        case MENU_SHOP_WEAPON:
        case MENU_SHOP_PROTECTOR:
        case MENU_SHOP_ITEM:
        case MENU_SHOP_YOROZU:
        case MENU_SHOP_WEAPON_TYPE2:
        case MENU_SHOP_PROTECTOR_TYPE2:
        case MENU_SHOP_ITEM_TYPE2:
        case MENU_SHOP_YOROZU_TYPE2:
        case MENU_SUGOROKU_SHOP:
            loadMaterielMenuOverlay(3);
            dq5::level::ShopMessage::setup();
            if (menuType == MENU_SUGOROKU_SHOP) {
                ui_MsgSndSet(0x32);
                twn::TownSugorokuManager::getSingleton().returnMenuFlag_ = 1;
            } else {
                ui_MsgSndSet(cmn::g_talkSound.getCharacterVoice(ctrlID));
            }
            MaterielMenu_SHOP_MANAGER::getSingleton()->initialize();
            MaterielMenu_SHOP_MANAGER::getSingleton()->openShopMenu(menuType);
            break;
        case MENU_CHANGE_GIFT:
        case MENU_CHANGE_GIFT_TYPE2:
            loadMaterielMenuOverlay(3);
            dq5::level::GiftMessage::setup();
            ui_MsgSndSet(cmn::g_talkSound.getCharacterVoice(ctrlID));
            MaterielMenu_SHOP_MANAGER::getSingleton()->initialize();
            MaterielMenu_SHOP_MANAGER::getSingleton()->setShopType(menuType);
            gMaterielMenu_CHANGEGIFT_ROOT.open();
            break;
        case MENU_COIN_SALEROOM:
            loadMaterielMenuOverlay(4);
            dq5::level::CoinMessage::setup();
            ui_MsgSndSet(cmn::g_talkSound.getCharacterVoice(ctrlID));
            gMaterielMenu_COINSALEROOM_ROOT.open();
            break;
        case MENU_CASINO_SLOT_ENTER:
            menu::gMaterielMenu_SlotEnter.open();
            break;
        case MENU_CASINO_SLOT:
            gMaterielMenu_SLOT.open();
            break;
        case MENU_CASINO_POKER:
            gMaterielMenu_POKER_BETCOIN.open();
            break;
        case MENU_CASINO_FIGHTSTADIUM:
            loadMaterielMenuOverlay(15);
            gMaterielMenu_FIGHT_STADIUM.open();
            break;
        case MENU_BANK:
            loadMaterielMenuOverlay(5);
            dq5::level::GoldMessage::setup();
            ui_MsgSndSet(cmn::g_talkSound.getCharacterVoice(ctrlID));
            gMaterielMenu_BANK_ROOT.open();
            break;
        case MENU_MEDAL_KING:
            loadMaterielMenuOverlay(3);
            dq5::level::MedalMessage::setup();
            ui_MsgSndSet(cmn::g_talkSound.getCharacterVoice(ctrlID));
            MaterielMenu_SHOP_MANAGER::getSingleton()->initialize();
            MaterielMenu_SHOP_MANAGER::getSingleton()->setShopType(MENU_MEDAL_KING);
            gMaterielMenu_MEDALKING_ROOT.open();
            break;
        case MENU_SAVE:
            loadMaterielMenuOverlay(2);
            gMaterielMenu_SAVE.open();
            dq5::level::ChurchMessage::setup();
            if (status::g_Menu.bookingFlag_ == 1) {
                gMaterielMenu_SAVE.saveType_ = 4;
                status::g_Menu.bookingFlag_ = 0;
                type_ = 3;
            } else if (type_ == 0) {
                gMaterielMenu_SAVE.saveType_ = 1;
            } else if (type_ == 1) {
                gMaterielMenu_SAVE.saveType_ = 3;
            } else if (type_ == 2) {
                gMaterielMenu_SAVE.saveType_ = 4;
            }
            break;
        case MENU_SURECHIGAI_MAKE_TAISHI:
            loadMaterielMenuOverlay(6);
            dq5::level::SurechigaiData::setup();
            dq5::level::MeisanhinData::setup();
            data_ov019_021854d4.open();
            break;
        case MENU_SURECHIGAI_ROOT:
            loadMaterielMenuOverlay(6);
            ui_MsgSndSet(cmn::g_talkSound.getCharacterVoice(ctrlID));
            dq5::level::SurechigaiData::setup();
            dq5::level::MeisanhinData::setup();
            data_ov019_02184d4c.open();
            surechigaiStart_ = 0;
            changeTaishi_ = 0;
            break;
        case MENU_SURECHIGAI_MESSAGE:
            loadMaterielMenuOverlay(6);
            dq5::level::SurechigaiData::setup();
            dq5::level::MeisanhinData::setup();
            data_ov019_0218616c.unk_af = 1;
            data_ov019_0218616c.open();
            break;
        case MENU_MONSTAR_JISAN:
            loadMaterielMenuOverlay(8);
            ui_MsgSndSet(cmn::g_talkSound.getCharacterVoice(ctrlID));
            dq5::level::JisanMessage::setup();
            gMaterielMenu_JISAN_ROOT.active_ = 0;
            gMaterielMenu_JISAN_ROOT.open();
            break;
        case MENU_LUIDANO_SAKABA:
            loadMaterielMenuOverlay(9);
            ui_MsgSndSet(cmn::g_talkSound.getCharacterVoice(ctrlID));
            dq5::level::LuidaMessage::setup();
            gMaterielMenu_LUIDA_ROOT.active_ = 0;
            gMaterielMenu_LUIDA_ROOT.open();
            break;
        case MENU_HUKUBIKIJO:
            loadMaterielMenuOverlay(7);
            ui_MsgSndSet(cmn::g_talkSound.getCharacterVoice(ctrlID));
            dq5::level::HukubikiMessage::setup();
            dq5::level::HukubikiPrize::setup();
            gMaterielMenu_HUKUBIKI_ROOT.open();
            break;
        case MENU_SUGOROKU_ROOT:
            loadMaterielMenuOverlay(10);
            MaterielMenuPlayerControl::getSingleton()->initialize();
            gMaterielMenu_SUGOROKU_ROOT.open();
            break;
        case MENU_SUGOROKU_GETITEM:
            loadMaterielMenuOverlay(10);
            MaterielMenuPlayerControl::getSingleton()->initialize();
            gMaterielMenu_SUGOROKU_GETITEM.itemID_ = sugorokuItem_;
            gMaterielMenu_SUGOROKU_GETITEM.open();
            break;
        case MENU_SET_NAME:
            data_ov019_02183e74.open();
            if (nameType_ == 1) {
                data_ov019_02183e74.setChildType(0xd);
            } else {
                data_ov019_02183e74.setChildType(0xe);
            }
            break;
        case MENU_SLIME_RACE:
            loadMaterielMenuOverlay(11);
            gMaterielMenu_RaceEntrance.open();
            break;
        case MENU_SLIME_RACE_MAIN:
            loadMaterielMenuOverlay(11);
            gMaterielMenu_SlimeRace.open();
            break;
        case MENU_SLIME_RACE_RESULT:
            loadMaterielMenuOverlay(11);
            gMaterielMenu_RaceResult.open();
            break;
        case MENU_SLIME_TOUCH:
            loadMaterielMenuOverlay(13);
            gMaterielMenu_SlimeTouch.open();
            break;
        case MENU_SLIME_TOUCH_RESULT:
            loadMaterielMenuOverlay(13);
            gMaterielMenu_TouchResult.open();
            break;
        case MENU_SET_MEISANHIN_ITEM:
            loadMaterielMenuOverlay(12);
            MaterielMenuPlayerControl::getSingleton()->initialize();
            gMaterielMenu_MEISANHIN_ROOT.open();
            break;
        case MENU_MIMI_MEMO:
            loadMaterielMenuOverlay(12);
            ui_MsgSndSet(0x31);
            dq5::level::MeisanhinData::setup();
            MaterielMenuPlayerControl::getSingleton()->initialize();
            gMaterielMenu_MIMI_ROOT.mode_ = MaterielMenu_MIMI_ROOT::MODE_MEMO;
            gMaterielMenu_MIMI_ROOT.open();
            break;
        case MENU_MIMI_HINT:
            loadMaterielMenuOverlay(12);
            ui_MsgSndSet(0x31);
            dq5::level::MeisanhinData::setup();
            MaterielMenuPlayerControl::getSingleton()->initialize();
            gMaterielMenu_MIMI_ROOT.mode_ = MaterielMenu_MIMI_ROOT::MODE_HINT;
            gMaterielMenu_MIMI_ROOT.open();
            break;
        case MENU_TAISHI_INFO:
            loadMaterielMenuOverlay(6);
            dq5::level::SurechigaiData::setup();
            data_ov019_02185604.open();
            break;
        case MENU_MONSTER_AZUKE:
            loadMaterielMenuOverlay(8);
            dq5::level::JisanMessage::setup();
            gMaterielMenu_JISAN_LEAVE_SCRIPT.open();
            break;
    }
    endWindow_ = 0;
}

THUMB void MaterielMenu_WINDOW_MANAGER::closeMaterielWindow()
{
    switch (menuType_) {
        case MENU_INN:
        case MENU_INN_TYPE2:
        case MENU_EXTRA_INN:
        case MENU_SUGOROKU_INN:
            gMaterielMenu_INN_ROOT.close();
            gMaterielMenu_INN_ROOT.stat_ = menu::MenuBase::MENUBASE_STAT_OK;
            dq5::level::InnMessage::cleanup();
            break;
        case MENU_CHURCH:
        case MENU_CHURCH_TYPE2:
        case MENU_CHURCH_MIRACLE:
            gMaterielMenu_CHURCH_ROOT.close();
            gMaterielMenu_CHURCH_MIRACLE.close();
            gMaterielMenu_CHURCH_ROOT.stat_ = menu::MenuBase::MENUBASE_STAT_OK;
            dq5::level::ChurchMessage::cleanup();
            break;
        case MENU_SHOP_WEAPON:
        case MENU_SHOP_PROTECTOR:
        case MENU_SHOP_ITEM:
        case MENU_SHOP_YOROZU:
        case MENU_SHOP_WEAPON_TYPE2:
        case MENU_SHOP_PROTECTOR_TYPE2:
        case MENU_SHOP_ITEM_TYPE2:
        case MENU_SHOP_YOROZU_TYPE2:
        case MENU_SUGOROKU_SHOP:
            gMaterielMenu_SHOP_ROOT.close();
            gMaterielMenu_SHOP_ROOT.stat_ = menu::MenuBase::MENUBASE_STAT_OK;
            dq5::level::ShopMessage::cleanup();
            break;
        case MENU_CHANGE_GIFT:
        case MENU_CHANGE_GIFT_TYPE2:
            gMaterielMenu_CHANGEGIFT_ROOT.close();
            gMaterielMenu_CHANGEGIFT_ROOT.stat_ = menu::MenuBase::MENUBASE_STAT_OK;
            dq5::level::GiftMessage::cleanup();
            break;
        case MENU_COIN_SALEROOM:
            gMaterielMenu_COINSALEROOM_ROOT.close();
            gMaterielMenu_COINSALEROOM_BUY.close();
            gMaterielMenu_COINSALEROOM_ROOT.stat_ = menu::MenuBase::MENUBASE_STAT_OK;
            dq5::level::CoinMessage::cleanup();
            break;
        case MENU_CASINO_SLOT_ENTER:
            menu::gMaterielMenu_SlotEnter.close();
            menu::gMaterielMenu_SlotEnter.stat_ = menu::MenuBase::MENUBASE_STAT_OK;
            status::g_StageInfo.returnBookFlag_ = 1;
            break;
        case MENU_CASINO_SLOT:
            gMaterielMenu_SLOT.close();
            gMaterielMenu_SLOT.stat_ = menu::MenuBase::MENUBASE_STAT_OK;
            g_Global.startTown(g_Global.prevMapNameId);
            status::g_StageInfo.returnBookFlag_ = 1;
            break;
        case MENU_CASINO_POKER:
            gMaterielMenu_POKER_BETCOIN.close();
            gMaterielMenu_POKER_CHANGECARD.close();
            gMaterielMenu_POKER_HIGHANDLOW.close();
            gMaterielMenu_POKER_BETCOIN.stat_ = menu::MenuBase::MENUBASE_STAT_OK;
            gMaterielMenu_POKER_CHANGECARD.stat_ = menu::MenuBase::MENUBASE_STAT_OK;
            gMaterielMenu_POKER_HIGHANDLOW.stat_ = menu::MenuBase::MENUBASE_STAT_OK;
            g_Global.startTown(g_Global.prevMapNameId);
            status::g_StageInfo.returnBookFlag_ = 1;
            break;
        case MENU_BANK:
            gMaterielMenu_BANK_ROOT.close();
            gMaterielMenu_BANK_DRAW.close();
            gMaterielMenu_BANK_PUTIN.close();
            gMaterielMenu_BANK_ROOT.stat_ = menu::MenuBase::MENUBASE_STAT_OK;
            dq5::level::GoldMessage::cleanup();
            break;
        case MENU_MEDAL_KING:
            gMaterielMenu_MEDALKING_ROOT.close();
            gMaterielMenu_MEDALKING_ROOT.stat_ = menu::MenuBase::MENUBASE_STAT_OK;
            dq5::level::MedalMessage::cleanup();
            break;
        case MENU_SAVE:
            gMaterielMenu_SAVE.close();
            gMaterielMenu_SAVE.stat_ = menu::MenuBase::MENUBASE_STAT_OK;
            dq5::level::ChurchMessage::cleanup();
            break;
        case MENU_SURECHIGAI_MAKE_TAISHI:
            dq5::level::SurechigaiData::cleanup();
            dq5::level::MeisanhinData::cleanup();
            data_ov019_021854d4.close();
            data_ov019_021854d4.stat_ = menu::MenuBase::MENUBASE_STAT_OK;
            data_ov019_02185900.close();
            data_ov019_02185900.stat_ = menu::MenuBase::MENUBASE_STAT_OK;
            data_ov019_02184d4c.close();
            data_ov019_02184d4c.stat_ = menu::MenuBase::MENUBASE_STAT_OK;
            data_ov019_0218616c.close();
            data_ov019_0218616c.stat_ = menu::MenuBase::MENUBASE_STAT_OK;
            break;
        case MENU_SURECHIGAI_ROOT:
            dq5::level::SurechigaiData::cleanup();
            dq5::level::MeisanhinData::cleanup();
            data_ov019_021854d4.close();
            data_ov019_021854d4.stat_ = menu::MenuBase::MENUBASE_STAT_OK;
            data_ov019_02184d4c.close();
            data_ov019_02184d4c.stat_ = menu::MenuBase::MENUBASE_STAT_OK;
            break;
        case MENU_SURECHIGAI_MESSAGE:
            dq5::level::SurechigaiData::cleanup();
            dq5::level::MeisanhinData::cleanup();
            data_ov019_0218616c.close();
            data_ov019_0218616c.stat_ = menu::MenuBase::MENUBASE_STAT_OK;
            break;
        case MENU_MONSTAR_JISAN:
            dq5::level::JisanMessage::cleanup();
            gMaterielMenu_JISAN_ROOT.close();
            break;
        case MENU_LUIDANO_SAKABA:
            dq5::level::LuidaMessage::cleanup();
            gMaterielMenu_LUIDA_ROOT.close();
            break;
        case MENU_HUKUBIKIJO:
            dq5::level::HukubikiMessage::cleanup();
            dq5::level::HukubikiPrize::cleanup();
            gMaterielMenu_HUKUBIKI_ROOT.close();
            gMaterielMenu_HUKUBIKI_ROOT.stat_ = menu::MenuBase::MENUBASE_STAT_OK;
            gMaterielMenu_HUKUBIKI_SELECTCHARA.close();
            gMaterielMenu_HUKUBIKI_SELECTCHARA.stat_ = menu::MenuBase::MENUBASE_STAT_OK;
            break;
        case MENU_SUGOROKU_ROOT:
            gMaterielMenu_SUGOROKU_ROOT.close();
            gMaterielMenu_SUGOROKU_ROOT.stat_ = menu::MenuBase::MENUBASE_STAT_OK;
            break;
        case MENU_SUGOROKU_GETITEM:
            gMaterielMenu_SUGOROKU_GETITEM.close();
            gMaterielMenu_SUGOROKU_GETITEM.stat_ = menu::MenuBase::MENUBASE_STAT_OK;
            break;
        case MENU_SLIME_RACE:
            gMaterielMenu_RaceEntrance.close();
            gMaterielMenu_RaceEntrance.stat_ = menu::MenuBase::MENUBASE_STAT_OK;
            break;
        case MENU_SLIME_RACE_MAIN:
            gMaterielMenu_SlimeRace.close();
            gMaterielMenu_SlimeRace.stat_ = menu::MenuBase::MENUBASE_STAT_OK;
            g_Global.startTown(g_Global.prevMapNameId);
            break;
        case MENU_SLIME_RACE_RESULT:
            gMaterielMenu_RaceResult.close();
            gMaterielMenu_RaceResult.stat_ = menu::MenuBase::MENUBASE_STAT_OK;
            break;
        case MENU_SLIME_TOUCH:
            gMaterielMenu_SlimeTouch.close();
            gMaterielMenu_SlimeTouch.stat_ = menu::MenuBase::MENUBASE_STAT_OK;
            break;
        case MENU_SLIME_TOUCH_RESULT:
            gMaterielMenu_TouchResult.close();
            gMaterielMenu_TouchResult.stat_ = menu::MenuBase::MENUBASE_STAT_OK;
            break;
        case MENU_SET_MEISANHIN_ITEM:
            gMaterielMenu_MEISANHIN_ROOT.close();
            gMaterielMenu_MEISANHIN_ROOT.stat_ = menu::MenuBase::MENUBASE_STAT_OK;
            data_ov019_02183524.close();
            data_ov019_02183524.fromMateriel_ = 1;
            data_ov019_02183524.stat_ = menu::MenuBase::MENUBASE_STAT_OK;
            gTownMenuItemSelectChara.close();
            gTownMenuItemSelectChara.meisanhinFlag_ = 1;
            gTownMenuItemSelectChara.stat_ = menu::MenuBase::MENUBASE_STAT_OK;
            break;
        case MENU_MIMI_MEMO:
        case MENU_MIMI_HINT:
            gMaterielMenu_MIMI_ROOT.close();
            gMaterielMenu_MIMI_ROOT.stat_ = menu::MenuBase::MENUBASE_STAT_OK;
            gMaterielMenu_MIMI_DETAIL.close();
            gMaterielMenu_MIMI_DETAIL.stat_ = menu::MenuBase::MENUBASE_STAT_OK;
            dq5::level::MeisanhinData::cleanup();
            break;
        case MENU_TAISHI_INFO:
            data_ov019_02185604.close();
            data_ov019_02185604.stat_ = menu::MenuBase::MENUBASE_STAT_OK;
            dq5::level::SurechigaiData::cleanup();
            break;
        case MENU_MONSTER_AZUKE:
            gMaterielMenu_JISAN_LEAVE_SCRIPT.close();
            gMaterielMenu_JISAN_LEAVE_SCRIPT.stat_ = menu::MenuBase::MENUBASE_STAT_OK;
            dq5::level::JisanMessage::cleanup();
            break;
        case MENU_CASINO_FIGHTSTADIUM:
        case MENU_SET_NAME:
            break;
    }
    MaterielMenuPlayerControl::getSingleton()->initialize();
    status::g_Menu.drawFlag_ = 0;
    endWindow_ = 1;
    menuType_ = MENU_NONE;
}

THUMB void MaterielMenu_WINDOW_MANAGER::openBasicMenu(int menu)
{
    data_ov019_02183ed4.drawMode_ = menu;
    data_ov019_02183ed4.open();
}
