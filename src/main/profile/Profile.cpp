#include "main/profile/Profile.hpp"
#include "main/status/GameFlag.hpp"

THUMB void profile::Profile::setup()
{
    pSYSTEM = profiledata_.system;
    pASSETS = profiledata_.assets;
    pPLAYER = profiledata_.player;
    pLOCATION = profiledata_.location;
    pPARTY = profiledata_.party;
    pMONSTER = profiledata_.monster;
    pTAISHI = profiledata_.taishi;
    dss::memset(&profiledata_, 0xd5, sizeof(profiledata_));
    dss::memset(profiledummy_, 0xc5, sizeof(profiledummy_));
}

THUMB void profile::Profile::collectGameFlag(unsigned char* WRITE, status::GameFlag* flag)
{
    for (int i = 0; i < 128; i++) {
        int W = 0;
        for (int j = 0; j < 8; j++) {
            W <<= 1;
            W |= flag->check(i * 8 + j);
        }
        WRITE[i] = W;
    }
}

THUMB void profile::Profile::deliverGameFlag(status::GameFlag* flag, unsigned char* WRITE)
{
    for (int i = 0; i < 128; i++) {
        int W = WRITE[i];
        int F = 0x80;
        for (int j = 0; j < 8; j++) {
            if (W & F) {
                flag->set(i * 8 + j);
            } else {
                flag->remove(i * 8 + j);
            }
            F >>= 1;
        }
    }
}

THUMB bool profile::Profile::calcCheckSum()
{
    PROFILE_SYSTEM* pSYS = profiledata_.system;
    unsigned char* ptr;
    unsigned int keep = pSYS->CHECKSUM;
    unsigned int sum = 0;
    pSYS->CHECKSUM = 0;
    ptr = (unsigned char*)&profiledata_;
    for (int i = 0; i < sizeof(profiledata_); i++) {
        sum += *ptr++;
    }
    pSYS->CHECKSUM = sum;
    if (sum == keep) {
        return true;
    }
    return false;
}

THUMB bool profile::Profile::isValidData()
{
    PROFILE_SYSTEM* pSYS = profiledata_.system;
    if (pSYS->MAGIC != 0x65747261) {
        return false;
    }
    if (pSYS->VER == 200804302) {
        return true;
    }
    return false;
}

THUMB void profile::Profile::nameCopy(unsigned char* dst, int size, unsigned char* src)
{
    dss::strcpy_s((char*)dst, size, (const char*)src);
}

THUMB void profile::Profile::collectFx32Vector3(int* prof, dss::Fix32Vector3* vec)
{
    prof[0] = vec->vx.value;
    prof[1] = vec->vy.value;
    prof[2] = vec->vz.value;
}

THUMB void profile::Profile::deliverFx32Vector3(dss::Fix32Vector3* vec, int* prof)
{
    vec->vx.value = prof[0];
    vec->vy.value = prof[1];
    vec->vz.value = prof[2];
}
