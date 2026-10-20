#include "main/global/Global.hpp"

GlobalGamePartManager data_02101d14;

ARM GlobalGamePartManager::GlobalGamePartManager()
{
    for (int i = 0; i < 8; i++) {
        part_[i] = 0;
    }
}

ARM GlobalGamePartManager::~GlobalGamePartManager()
{
}

ARM void GlobalGamePartManager::updateParts()
{
    for (int i = 0; i < 8; i++) {
        if (part_[i] != 0) {
            part_[i]->update();
            if (part_[i]->isEnd()) {
                part_[i] = 0;
            }
        }
    }
}

ARM void GlobalGamePartManager::drawParts()
{
    for (int i = 0; i < 8; i++) {
        if (part_[i] != 0) {
            part_[i]->draw();
            if (part_[i]->isEnd()) {
                part_[i] = 0;
            }
        }
    }
}

ARM void GlobalGamePartManager::addPart(UnkGlobalPart* part)
{
    for (int i = 0; i < 8; i++) {
        if (part_[i] == 0) {
            part_[i] = part;
            return;
        }
    }
}

ARM void GlobalGamePartManager::removePart(UnkGlobalPart* part)
{
    for (int i = 0; i < 8; i++) {
        if (part_[i] == part) {
            part_[i] = 0;
            return;
        }
    }
}
