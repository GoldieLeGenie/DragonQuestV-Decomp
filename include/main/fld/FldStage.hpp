#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"
#include "main/data/DataObject.hpp"
#include "main/fld/FLDObject.hpp"
#include "main/fld/Coll.hpp"
#include "main/object/ModelObject.hpp"
#include "main/dss/Render.hpp"
#include "nitro/g3.hpp"

struct FldStage;
struct FldCollision;

int unkfunc_020484ec(VecFx32* pos, VecFx32* rot, VecFx32* scale, VecFx32* box, dss::Fix32* rate);
int fldBoxTest(dss::Fix32Vector3* pos, dss::Fix32Vector3* rot, dss::Fix32Vector3* scale, GXBoxTestParam* box, dss::Fix32* rate);    // box test

struct FldStage : UnkRenderModel {
    int flag_;                                  // 0x008
    Render* m_render;                           // 0x00C
    UnkFileDataObject m_data;                      // 0x010
    DataObject m_model;                         // 0x020
    DataObject m_texture;                       // 0x030
    DataObject m_coll;                          // 0x040
    UnkModelMember m_anim;                      // 0x050
    fld::FLDObject m_fld;                       // 0x05C
    dss::Fix32Vector3 scale_;                   // 0x674
    int collisionFlag_;                         // 0x680
    int collisionDrawFlag_;                     // 0x684
    int exitType_;                              // 0x688
    char path_[32];                             // 0x68C
    int obj_index[128];                         // 0x6AC
    int pool_counter;                           // 0x8AC
    int extraObjectNum_;                        // 0x8B0
    int unk_8b4;                                // 0x8B4
    int unk_8b8;                                // 0x8B8
    int unk_8bc;                                // 0x8BC

    FldStage();
    ~FldStage();
    void initialize(Render* render);
    void SetBBoxFar(fx32 val);
    void resettingTexture();
    void setMainCameraFlag(int flag);
    void SetRGBRate(dss::Fix32Vector3& fldrate, int real_time);
    void eraseCollision(int objectID);
    void resetCollision(int objectID);
    void addMapGroupPosFX32(int gid, dss::Fix32Vector3& pos);
    void addMapGroupRotFX32(int gid, dss::Fix32Vector3& rot);
    void terminate();
    virtual void setup();
    void setup(bool flag);
    virtual void cleanup();
    void setPath(const char* path);
    bool isExist(char* name);
    void load(const char* name);
    void setSepiarEnable(int flag);
    virtual void draw();
    void execAnime();
    dss::Fix32 getCameraLimitR();
    dss::Fix32 getCameraLimitL();
    void eraseObject(int uid, int flag);
    void setMapUidOnOff(int uid, int flag);
    int eventAnim(int anim, int frame);
    static int getDrawTick();
    void repop(int uid);
    void commonAnim(int obj, int frame);
    void animLocation(int id, int frame, int uidFlag);
    void setAnimLocation(int obj, int frame);
    void setAlpha(int obj, int alpha);
    void setFldColl(FldCollision* coll);
    bool collGetPolygonPos(int poly, dss::Fix32Vector3* pos);
    int collCrossCheckPoly(dss::Fix32Vector3& start, dss::Fix32Vector3& end, dss::Fix32* dist, int all);
    int collCrossCheckOtherNo(dss::Fix32Vector3& start, dss::Fix32Vector3& end, int no, dss::Fix32* dist);
    void setRotObjectUid(int uid, dss::Fix32Vector3& rot);
    int collGetPoly(int poly, COLL_POLY* out);
    int collGetObjId(int polygonNo);
    void setPosByObjectID(int id, dss::Fix32Vector3& pos);
    static dss::Fix32Vector3 getFx32Vector3(const VecFx32& vec);
    static VecFx32 getVecFx32(const dss::Fix32Vector3& vec);
    bool getObjectIn(int uid, dss::Fix32Vector3& pos);
    int getObjWallNo(int obj, int wall);
    int getObjWallPolyNo(int obj, int wall);
    short getObjectRotIdxY(int obj);
    VecFx32 getUidPos(int uid);
    int* GetMapUidObj(int uid);
    int IsCommonAnimationEnd(int uid);
    COLL_ADD_RESULT_TYPE addBoxCollistion(dss::Fix32Vector3& center, short dir, dss::Fix32Vector3& vec, int& extraId, int& allocFlag);
    int getPolyNoBySurfaceId(int surface, int index);
    void addMovePosByObjNo(int obj, dss::Fix32Vector3& move);
    int getCrossPolygonOtherSurface(dss::Fix32Vector3& start, dss::Fix32Vector3& end, int* surface, int count, int& poly, dss::Fix32* dist, int all);
    void dropModelTexture();                    // drops the textures from the loaded model file
    void setSepiarExecute();
};

