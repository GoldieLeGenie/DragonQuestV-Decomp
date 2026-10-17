#pragma once
#include <globaldefs.h>
#include "nnsys/g3d.hpp"

// model file of a model object: binds its textures (loaded in VRAM) to its model set
struct UnkModelMember {
    void* unk_00;                               // 0x00 model file
    NNSG3dResMdl* unk_04;                       // 0x04 last model of the set
    NNSG3dResTex* unk_08;                       // 0x08 textures

    UnkModelMember();
    void unkfunc_02046c3c(void* data);          // set the model file
    void unkfunc_02046c48();                    // release
    void unkfunc_02046c54();                    // reload the textures
    void unkfunc_02046c6c(void* data);
    void unkfunc_02046dbc();
    void unkfunc_02046dc8();                    // load the textures
    void unkfunc_02046e98();                    // release the textures
    void* unkfunc_02046f30();
    NNSG3dResMdl* unkfunc_02046f38();
};

extern NNSG3dResTex* data_020f3e84;             // last loaded textures
extern int data_020f3e88;                       // skip the next texture load

NNSG3dResTex* unkfunc_02046f40();
