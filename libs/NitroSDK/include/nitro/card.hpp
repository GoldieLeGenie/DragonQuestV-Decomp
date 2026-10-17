#pragma once
#include <stddef.h>

#define CARD_BACKUP_TYPE_EEPROM_512KBITS 0x1001

extern "C" {
    void CARD_LockBackup(unsigned short lockID);                                       // CARD_LockBackup
    void CARD_UnlockBackup(unsigned short lockID);                                       // CARD_UnlockBackup
    int CARD_IdentifyBackup(unsigned int type);                                           // CARD_IdentifyBackup
    int CARD_GetResultCode(void);                                                        // CARD_GetResultCode
    int CARD_TryWaitBackupAsync(void);                                                        // CARD_TryWaitBackupAsync
    int CARD_ReadWriteBackupAsync(unsigned int src, unsigned int dst, unsigned int len, void* callback, void* arg,
                      int isAsync, int reqType, int reqRetry, int reqMode);         // CARDi_RequestStreamCommand
}

inline int CARD_ReadBackup(unsigned int src, void* dst, unsigned int len)
{
    return CARD_ReadWriteBackupAsync(src, (unsigned int)dst, len, NULL, NULL, 0, 6, 1, 0);
}

inline int CARD_WriteAndVerifyBackup(unsigned int dst, const void* src, unsigned int len)
{
    return CARD_ReadWriteBackupAsync((unsigned int)src, dst, len, NULL, NULL, 0, 8, 10, 2);
}

inline int CARD_WriteAndVerifyBackupAsync(unsigned int dst, const void* src, unsigned int len, void* callback, void* arg)
{
    return CARD_ReadWriteBackupAsync((unsigned int)src, dst, len, callback, arg, 1, 8, 10, 2);
}
