#pragma once
#include <globaldefs.h>
#include "nnsys/g3d.hpp"

// model file of a model object: binds its textures (loaded in VRAM) to its model set
struct UnkModelMember {
    void* modelFile_;                               // 0x00 model file
    NNSG3dResMdl* model_;                       // 0x04 last model of the set
    NNSG3dResTex* texture_;                       // 0x08 textures

    UnkModelMember();
    void setModelFile(void* data);          // set the model file
    void release();                    // release
    void reloadTextures();                    // reload the textures
    void bindModelFile(void* data);
    void releaseModelFile();
    void loadTextures();                    // load the textures
    void releaseTextures();                    // release the textures
    void* getModelFile();
    NNSG3dResMdl* getModel();
};

extern NNSG3dResTex* data_020f3e84;             // last loaded textures
extern int data_020f3e88;                       // skip the next texture load

NNSG3dResTex* getLastModelTexture();
