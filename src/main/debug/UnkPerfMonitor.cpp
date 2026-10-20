#include "main/debug/UnkPerfMonitor.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/dss/UnkMemory.hpp"
#include "main/dss/VramTransferManager.hpp"
#include "main/fld/FldCollision.hpp"
#include "main/fld/FldStage.hpp"
#include "main/global/Global.hpp"

THUMB UnkPerfRecord::UnkPerfRecord()
{
    clear();
}

THUMB void UnkPerfRecord::clear()
{
    mapId_ = -1;
    value_ = -1;
}

THUMB void UnkPerfRecord::set(int mapId, int value)
{
    mapId_ = mapId;
    value_ = value;
}

THUMB int UnkPerfRecord::getMapId()
{
    return mapId_;
}

THUMB int UnkPerfRecord::getValue()
{
    return value_;
}

THUMB void unkfunc_02045f14(UnkPerfRecord* records, int count, int mapId, int value)
{
    int max = -1;
    int index = -1;
    for (int i = 0; i < count; i++) {
        int v = records[i].getValue();
        if (v == -1) {
            index = i;
            break;
        }
        if (value < v && v > max) {
            max = v;
            index = i;
        }
    }
    if (index != -1) {
        records[index].set(mapId, value);
    }
}

THUMB void unkfunc_02045f74(UnkPerfRecord* records, int count, int mapId, int value)
{
    int min = -1;
    int index = -1;
    for (int i = 0; i < count; i++) {
        int v = records[i].getValue();
        if (v == -1) {
            index = i;
            break;
        }
        if (value > v && v < min) {
            min = v;
            index = i;
        }
    }
    if (index != -1) {
        records[index].set(mapId, value);
    }
}

THUMB void unkfunc_02045fd4(UnkPerfRecord* records, int count)
{
    for (int n = count - 1; n >= 1; n--) {
        for (int i = 0; i < n; i++) {
            if (records[i].getValue() < records[i + 1].getValue()) {
                int mapId = records[i].getMapId();
                int value = records[i].getValue();
                records[i].set(records[i + 1].getMapId(), records[i + 1].getValue());
                records[i + 1].set(mapId, value);
            }
        }
    }
}

THUMB void unkfunc_02046050(UnkPerfRecord* records, int count)
{
    for (int n = count - 1; n >= 1; n--) {
        for (int i = 0; i < n; i++) {
            if (records[i].getValue() > records[i + 1].getValue()) {
                int mapId = records[i].getMapId();
                int value = records[i].getValue();
                records[i].set(records[i + 1].getMapId(), records[i + 1].getValue());
                records[i + 1].set(mapId, value);
            }
        }
    }
}

THUMB void unkfunc_020460cc(UnkPerfRecord* record, const char* label)
{
    char name[0x80];
    g_Global.getMapNameById(name, record->mapId_);
}

THUMB void UnkPerfMonitor::initialize()
{
    done_ = 0;
    active_ = 0;
    for (int i = 0; i < 16; i++) {
        draw0_[i].clear();
        draw1_[i].clear();
        collision0_[i].clear();
        collision1_[i].clear();
        heap_[i].clear();
        vram_[i].clear();
    }
    drawTick0_ = 0;
    drawTick1_ = 0;
    collisionTick0_ = 0;
    collisionTick1_ = 0;
    freeHeap_ = 0;
    freeVram_ = 0;
}

THUMB void UnkPerfMonitor::update()
{
    if (active_ && fadeEffector.isFadeEnd()) {
        if (wait_ != 0) {
            wait_--;
            return;
        }
        measure();
    }
}

THUMB void UnkPerfMonitor::start()
{
    active_ = 1;
    wait_ = 2;
    drawTick0_ = 0;
    drawTick1_ = 0;
    collisionTick0_ = 0;
    collisionTick1_ = 0;
    freeHeap_ = 0x7fffffff;
    freeVram_ = 0x7fffffff;
}

THUMB void UnkPerfMonitor::stop()
{
    active_ = 0;
    int mapId = g_Global.nextMapNameId;
    unkfunc_02045f74(draw0_, 16, mapId, drawTick0_);
    unkfunc_02045f74(draw1_, 16, mapId, drawTick1_);
    unkfunc_02045f74(collision0_, 16, mapId, collisionTick0_);
    unkfunc_02045f74(collision1_, 16, mapId, collisionTick1_);
    unkfunc_02045f14(heap_, 16, mapId, freeHeap_);
    unkfunc_02045f14(vram_, 16, mapId, freeVram_);
}

THUMB void UnkPerfMonitor::finish()
{
    unkfunc_02045fd4(draw0_, 16);
    unkfunc_02045fd4(draw1_, 16);
    unkfunc_02045fd4(collision0_, 16);
    unkfunc_02045fd4(collision1_, 16);
    unkfunc_02046050(heap_, 16);
    unkfunc_02046050(vram_, 16);
    for (int i = 0; i < 16; i++) {
        unkfunc_020460cc(&draw0_[i], "");
    }
    for (int i = 0; i < 16; i++) {
        unkfunc_020460cc(&draw1_[i], "");
    }
    for (int i = 0; i < 16; i++) {
        unkfunc_020460cc(&collision0_[i], "");
    }
    for (int i = 0; i < 16; i++) {
        unkfunc_020460cc(&collision1_[i], "");
    }
    for (int i = 0; i < 16; i++) {
        unkfunc_020460cc(&heap_[i], "");
    }
    for (int i = 0; i < 16; i++) {
        unkfunc_020460cc(&vram_[i], "");
    }
    done_ = 1;
}

THUMB void UnkPerfMonitor::measure()
{
    if (getDisplayFrame() & 1) {
        int draw = FldStage::getDrawTick();
        int collision = FldCollision::getCollisionTick();
        if (drawTick0_ < draw) {
            drawTick0_ = draw;
        }
        if (collisionTick0_ < collision) {
            collisionTick0_ = collision;
        }
    } else {
        int draw = FldStage::getDrawTick();
        int collision = FldCollision::getCollisionTick();
        if (drawTick1_ < draw) {
            drawTick1_ = draw;
        }
        if (collisionTick1_ < collision) {
            collisionTick1_ = collision;
        }
    }
    int heap = (int)unkfunc_0204c5f4(&data_020fd24c) / 1024;
    int vram = (int)data_020f4f74.unk_08 / 1024;
    if (freeHeap_ > heap) {
        freeHeap_ = heap;
    }
    if (freeVram_ > vram) {
        freeVram_ = vram;
    }
}
