#pragma ipa file
#include "main/global/StageLink.hpp"

inline int CMapLink::get_exit_id()
{
    return m_exit_id;
}

int util::StageLink::fieldSymbolIndex_ = -1;
int util::StageLink::townExitIndex_ = -1;
CMapLink util::StageLink::mapLink_;
DataObject util::StageLink::mapLinkData_;

THUMB void util::StageLink::initialize()
{
    mapLinkData_.setup("data/map/map_link.bin", 1, 0);
    mapLink_.setup(mapLinkData_.getAddr());
}

THUMB int util::StageLink::getNameId(int id, int exit)
{
    if (id == 999) {
        return mapLink_.search(id, exit | 0x70000);
    }
    return mapLink_.search(id, exit);
}

THUMB int util::StageLink::getSymbolIndex()
{
    return mapLink_.get_exit_id();
}

THUMB void util::StageLink::setTownExitIndex(int index)
{
    townExitIndex_ = index;
}

THUMB void util::StageLink::resetTownExitIndex()
{
    townExitIndex_ = -1;
}

THUMB int util::StageLink::getTownExitIndex()
{
    return townExitIndex_;
}

THUMB void util::StageLink::setFieldSymbolIndex(int index)
{
    fieldSymbolIndex_ = index;
}

THUMB int util::StageLink::getFieldSymbolIndex()
{
    return fieldSymbolIndex_;
}
