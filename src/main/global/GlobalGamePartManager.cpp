#include "main/global/Global.hpp"

UnkGlobalGamePartManager data_02101d14;

ARM UnkGlobalGamePartManager::UnkGlobalGamePartManager()
{
    for (int i = 0; i < 8; i++) {
        part_[i] = 0;
    }
}

ARM UnkGlobalGamePartManager::~UnkGlobalGamePartManager()
{
}

ARM void UnkGlobalGamePartManager::unkfunc_02051908()
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

ARM void UnkGlobalGamePartManager::unkfunc_02051958()
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

ARM void UnkGlobalGamePartManager::unkfunc_020519a8(UnkGlobalPart* part)
{
    for (int i = 0; i < 8; i++) {
        if (part_[i] == 0) {
            part_[i] = part;
            return;
        }
    }
}

ARM void UnkGlobalGamePartManager::unkfunc_020519cc(UnkGlobalPart* part)
{
    for (int i = 0; i < 8; i++) {
        if (part_[i] == part) {
            part_[i] = 0;
            return;
        }
    }
}
