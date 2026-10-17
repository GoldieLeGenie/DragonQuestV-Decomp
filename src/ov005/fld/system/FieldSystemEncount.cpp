#include "ov005/fld/FieldSystem.hpp"
#include "main/btl/Encount.hpp"
#include "main/global/Global.hpp"
#include "main/status/StageAttribute.hpp"
#include "main/status/StageInfo.hpp"
#include "main/status/StoryStatus.hpp"
#include "ov005/fld/FieldPlayerManager.hpp"

inline dq5::CHAPTER_NO status::StoryStatus::getChapter()
{
    return chapter_;
}

THUMB fld::FieldSystemEncount::FieldSystemEncount()
{
}

THUMB fld::FieldSystemEncount::~FieldSystemEncount()
{
}

THUMB void fld::FieldSystemEncount::initialize()
{
    btl::Encount::getSingleton()->setupField(status::g_Story.getChapter(), status::g_StageInfo.getTimeZone());
}

THUMB void fld::FieldSystemEncount::terminate()
{
}

THUMB void fld::FieldSystemEncount::execute()
{
    dss::Fix32Vector3 posEncount = FieldPlayerManager::getSingleton().getPosition();
    int tx = posEncount.vx.value / 0x100000;
    int ty = posEncount.vy.value / 0x100000;
    int bx = dss::clamp<int>(tx - 4, 0, 3);
    int by = dss::clamp<int>(ty - 4, 0, 3);
    dq5::LandType land = FieldPlayerManager::getSingleton().getLandType();
    status::g_StageAttribute.setBtlMapNameOnField(land);
    switch (g_Global.getFieldType()) {
        case 0:
            btl::Encount::getSingleton()->setBlock(0, land, tx, ty);
            if (land != 0) {
                if (posEncount.vx.value / 0x1000 >= 0x7a5 && posEncount.vx.value / 0x1000 <= 0x835 &&
                    posEncount.vy.value / 0x1000 >= 0xe68 && posEncount.vy.value / 0x1000 <= 0xed8) {
                    status::g_StageAttribute.setBtlMapNameOnField(dq5::LandType(9));
                }
                if (posEncount.vx.value / 0x1000 >= 0x833 && posEncount.vx.value / 0x1000 <= 0xa4b &&
                    posEncount.vy.value / 0x1000 >= 0xe28 && posEncount.vy.value / 0x1000 <= 0xf28) {
                    status::g_StageAttribute.setBtlMapNameOnField(dq5::LandType(9));
                }
            }
            break;
        case 1:
            btl::Encount::getSingleton()->setBlock(1, land, bx, by);
            break;
        case 2:
            btl::Encount::getSingleton()->setBlock(1, land, bx, by);
            break;
        case 3:
            btl::Encount::getSingleton()->setBlock(3, land, bx, by);
            break;
    }
}

THUMB void fld::FieldSystemEncount::draw()
{
}
