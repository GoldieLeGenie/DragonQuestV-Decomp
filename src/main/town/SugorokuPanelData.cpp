#include "main/town/SugorokuPanelData.hpp"

THUMB void twn::PanelData::setData(unsigned short uid, unsigned short panelID, unsigned short attr, unsigned short warpMapNo, unsigned short warpUid)
{
    uid_ = uid;
    panelID_ = panelID;
    attr_ = attr;
    warpMapNo_ = warpMapNo;
    warpUid_ = warpUid;
}

THUMB void twn::PanelData::pushLinkPanel(int no, PanelData* panel)
{
    link_[no] = panel;
    link_[no]->setBack(this);
}

THUMB void twn::PanelData::setBack(PanelData* panel)
{
    for (int i = 1; i < PANEL_LINK_MAX_NUM; i++) {
        if (reverce_[i] == NULL) {
            reverce_[i] = panel;
            return;
        }
    }
}

THUMB void twn::PanelData::clear()
{
    for (int i = 0; i < PANEL_LINK_MAX_NUM; i++) {
        link_[i] = NULL;
        reverce_[i] = NULL;
    }
    loopPanel_ = NULL;
    uid_ = 0;
    panelID_ = 0;
    warpMapNo_ = 0;
    warpUid_ = 0;
    attr_ = 0;
}
