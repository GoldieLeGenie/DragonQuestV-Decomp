#pragma ipa file
#include "ov001/town/TownImageMap.hpp"
#include "ov001/town/TownCamera.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "main/dss/RenderObject.hpp"
#include "main/data/FileLoader.hpp"
#include "main/global/Global.hpp"
#include "main/leveldata/LevelDataUtility.hpp"
#include "main/leveldata/MapCamera.hpp"
#include "main/status/StageAttribute.hpp"
#include "main/status/StageInfo.hpp"
#include "main/window/UnkMapPoint.hpp"

inline dq5::level::MapCamera* dq5::level::MapCamera::getRecord(int index)
{
    return (MapCamera*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline int Global::getMapNameId()
{
    return nextMapNameId;
}

inline int Global::getPrevMapNameId()
{
    return prevMapNameId;
}

inline int Global::getNowAreaNo()
{
    return areaNo_;
}

inline void status::StageInfo::setOverviewTempPosition(dss::Fix32Vector3& pos)
{
    overviewTempPosition_ = pos;
}

THUMB twn::TownImageMap::TownImageMap()
{
    isEnable_ = false;
    frame_ = 0;
    map2d_ = 0;
}

THUMB twn::TownImageMap::~TownImageMap()
{
}

THUMB void twn::TownImageMap::setup()
{
    checkData();
    map2d_ = 0;
    if (isEnable_) {
        black_.setSize(0x100, 0xc0);
        black_.setAlpha(0);
        black_.setSubScreen();
        black_.setColor(0, 0, 0);
        black_.setPolygonID(0x3f);
        map_.loadFile(fileName_, 0);
        map_.setSubScreen();
        map_.setAlpha(0);
        map_.setPolygonID(0x3f);
        map_.sprite_.color0Opaque_ = 1;
        point_.loadFile("data/field/2d/point_s.tex", 0);
        point_.setSubScreen();
        point_.setAlpha(0);
        point_.setPolygonID(0x3d);
        point_.setDepth(0x18);
        point_.setTexCoords(0, 0, 0x10, 0x10);
        point_.setSize(0x10, 0x10);
    }
}

THUMB void twn::TownImageMap::cleanup()
{
    if (isEnable_) {
        map_.unload();
        point_.unload();
    }
    isEnable_ = false;
}

THUMB void twn::TownImageMap::execute()
{
    if (isEnable_) {
        switch (map2d_) {
        case 0:
            frame_ = 0;
            break;
        case 1:
            data_02101da4 = true;
            calcTargetPos();
            map_.setEnabled(true);
            if (frame_ >= 2) {
                point_.setEnabled(true);
                getTargetPos();
            }
            frame_++;
            if (frame_ == 0x1f) {
                map2d_ = 2;
            }
            map_.setAlpha(frame_);
            point_.setAlpha(frame_);
            break;
        case 3:
            frame_--;
            map_.setAlpha(frame_);
            point_.setAlpha(frame_);
            if (frame_ <= 0) {
                data_02101da4 = false;
                map_.setEnabled(false);
                cleanup();
                map2d_ = 0;
                black_.setAlpha(0);
            }
            break;
        case 5:
            frame_--;
            black_.setAlpha(0x1f - frame_);
            if (frame_ <= 0) {
                data_02101da4 = false;
                map_.setEnabled(false);
                cleanup();
                map2d_ = 0;
                map_.setAlpha(0);
                point_.setAlpha(0);
            }
            break;
        }
        int x = targetPos_.vx;
        int y = targetPos_.vy;
        if (x > 0xf0) {
            x = 0xf0;
        }
        if (y > 0xc0) {
            y = 0xc0;
        }
        if (y < 0x10 && y > 0) {
            y = 0x10;
        }
        point_.setPosition(x, y - 0x10);
    }
}

THUMB void twn::TownImageMap::exitFloor()
{
    int index = dq5::level::g_LevelDataUtility.getOverviewFloor(g_Global.getPrevMapNameId());
    if (index >= 0) {
        dss::Fix32Vector3& pos = TownPlayerManager::getSingleton().getPosition();
        status::g_StageInfo.setOverviewTempPosition(pos);
    }
}

THUMB void twn::TownImageMap::checkData()
{
    if (status::g_StageAttribute.isMapIcon()) {
        int index = dq5::level::g_LevelDataUtility.getOverviewArea(g_Global.getNowAreaNo());
        if (index >= 0) {
            dss::sprintf_s(fileName_, 0x80, "data/2d/map/%s.tex", dq5::level::MapCamera::getRecord(index)->fileNo);
            if (dss::g_File.isExist(fileName_, dss::File::None)) {
                isEnable_ = true;
            } else {
                isEnable_ = false;
            }
        }
    } else {
        isEnable_ = false;
    }
}

THUMB void twn::TownImageMap::draw()
{
    if (isEnable_) {
        setupOrtho2D();
        map_.draw();
        point_.draw();
        setupOrtho2DFine();
        black_.draw();
        camera_.applyCamera();
    }
}

THUMB void twn::TownImageMap::open()
{
    setup();
    camera_.applyCamera();
    setupOrtho2D();
    map2d_ = 1;
}

THUMB void twn::TownImageMap::close()
{
    map2d_ = 3;
}

THUMB void twn::TownImageMap::closeBlack()
{
    map2d_ = 5;
}

THUMB bool twn::TownImageMap::isOpen()
{
    return map2d_ == 2;
}

THUMB bool twn::TownImageMap::isClose()
{
    return map2d_ == 0;
}

THUMB void twn::TownImageMap::calcTargetPos()
{
    dss::Fix32Vector3 pos;
    int index = dq5::level::g_LevelDataUtility.getOverviewFloor(g_Global.getMapNameId());
    if (index >= 0) {
        pos = TownPlayerManager::getSingleton().getPosition();
    } else {
        pos = dss::Fix32Vector3(status::g_StageInfo.overviewTempPosition_);
    }
    setProjectedPointPos(2, pos);
}

THUMB void twn::TownImageMap::getTargetPos()
{
    targetPos_ = *getProjectedPointScreenPos(2);
}

THUMB void twn::TownImageMap::setOverview()
{
    dss::Fix32Vector3 target(0, 0, 0);
    dss::Fix32Vector3 angleFx;
    dss::Fix32 distance(0L);
    dss::Vector3<short> angle;
    dss::Fix32Vector3 pos;
    camera_ = TownCamera::getSingleton()->camera_.unk_004;
    camera_.setTarget(target);
    int index = dq5::level::g_LevelDataUtility.getOverviewArea(g_Global.getNowAreaNo());
    if (index >= 0) {
        angleFx.vx = dq5::level::MapCamera::getRecord(index)->angleX;
        angleFx.vy = dq5::level::MapCamera::getRecord(index)->angleY;
        angleFx.vz = dq5::level::MapCamera::getRecord(index)->angleZ;
        distance = dq5::level::MapCamera::getRecord(index)->distance;
        pos.vx = dq5::level::MapCamera::getRecord(index)->x;
        pos.vy = dq5::level::MapCamera::getRecord(index)->y;
        pos.vz = dq5::level::MapCamera::getRecord(index)->z;
    }
    angle.vx = angleFx.vx.value * 0xb6 / 0x1000;
    angle.vy = angleFx.vy.value * 0xb6 / 0x1000;
    angle.vz = angleFx.vz.value * 0xb6 / 0x1000;
    camera_.setTarget(pos);
    camera_.setAngle(angle);
    camera_.setDistance(distance);
}

ARM int twn::TownImageMap::isEnable()
{
    return isEnable_;
}
