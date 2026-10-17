#pragma ipa file
#include "ov001/town/command/TownCommandScope.hpp"
#include "ov001/town/TownCamera.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov001/town/TownStageManager.hpp"
#include "main/town/TownCommandEncount.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/cmn/ExtraMapLink.hpp"
#include "main/window/NormalControl.hpp"
#include "main/dss/Pad.hpp"

#pragma thumb on

inline cmn::MENU_ACTION cmn::CommonPartyInfo::getMenuAction()
{
    return menuAction_;
}

inline short cmn::CommonPartyInfo::getBackupDirIdx()
{
    return backupDirIdx_;
}

inline void fld::FLDObject::SetBBoxFar(fx32 val)
{
    m_bbox_far = val;
}

inline void FldStage::SetBBoxFar(fx32 val)
{
    m_fld.SetBBoxFar(val);
}

inline void twn::TownStageManager::SetBBoxFar(dss::Fix32 val)
{
    stage_.SetBBoxFar(val.value);
}

const dss::Fix32 twn::farLen(0x44000);
const dss::Fix32 twn::defaultLen(0x3c000);

int twn::TownCommandScope::isExec()
{
    if (cmn::g_cmnPartyInfo.getMenuAction() == cmn::SCOPE) {
        dss::Fix32Vector3 pos(0, 0, 0);
        TownPlayerManager::getSingleton().setPosition(pos);
        dss::Vector3<short> angle(-0x333, 0, 0);
        TownCamera::getSingleton()->setDefaultAngle(angle);
        TownPlayerManager::getSingleton().setLock(true);
        TownPlayerManager::getSingleton().setDrawPartyNone();
        cmn::g_cmnPartyInfo.setMenuAction(cmn::MENU_ACTION_NONE);
        TownStageManager::getSingleton()->SetBBoxFar(farLen);
        return true;
    }
    return false;
}

int twn::TownCommandScope::isEnd()
{
    window::gNormalControl.checkCamera();
    if ((dss::g_Pad.edge() & 1) || (dss::g_Pad.edge() & 2) || (dss::g_Pad.edge() & 0x800) || (dss::g_Pad.edge() & 0x400)) {
        cmn::g_extraMapLink.setExtraLinkTown(0xa9, cmn::g_cmnPartyInfo.backupPos_, cmn::g_cmnPartyInfo.getBackupDirIdx());
        TownStageManager::getSingleton()->SetBBoxFar(defaultLen);
        return true;
    }
    return false;
}

void twn::TownCommandScope::exec()
{
    CommandObjectDefineTownSystem::setScope();
}
