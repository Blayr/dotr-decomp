/* Sound driver: file reads (SDFS_*). */

#include "common.h"

/* Whether the sound driver's file reader is busy. */
s32 SDFS_IsUsingNow(void) {
    return s_iUsingNow;
}

/* Starts reading file `file` (`position`, `size`) into `destination`; finishes by callback. */
s32 SDFS_ReadToEE(s32 file, s32 destination, s32 position, s32 size) {
    if (!(destination & 0xF)) {
        if ((position % 2048) == 0) {
            if ((size % 2048) == 0) {
                D_0030FFA0.src = 0;
                D_0030FFA0.offset = 0;
                D_0030FFA0.size = 0;
                D_0030FFA0.position = 0;
                D_0030FFA0.left = 0;
                func_00199B50(D_002B90C0, file, destination);
                if (RhFile_ReadAndCallbackByFileName(file, position, size, destination, lSDFS_FinishCallback, 0, 0x20) == 0) {
                    return -1;
                }
            }
        }
    }
    s_iUsingNow = 1;
    return 1;
}

/* Reads file `file` (`position`, `size`) into `destination` and waits. */
s32 SDFS_ReadToEEBlock(s32 file, s32 destination, s32 position, s32 size) {
    s32 handle;
    s32 blockStart;
    s32 blockOffset;
    s32 blockSize;
    s32 totalSize;
    s32 copySize;

    func_00199B50(D_002B90DA, file, destination, position, size);
    func_00199B50(D_002B9102);
    if ((handle = RhFile_OpenFile(file)) < 0) {
        return 0;
    }
    if ((destination & 0xF) || (position % 0x800) || (size % 0x800)) {
        while (size > 0) {
            blockStart = (position >> 11) << 11;
            totalSize = position - blockStart;
            totalSize += size;
            blockSize = totalSize < 0x80001 ? totalSize : 0x80000;
            blockOffset = position - blockStart;
            size = totalSize - blockSize;
            position = blockStart + blockSize;
            func_00199B50(D_002B9112, file, handle);
            RhFile_ReadAndBlock(handle, blockStart, ((blockSize + 0x7FF) >> 11) << 11, 0x04000000);
            copySize = blockSize - blockOffset;
            func_00198790((void *)destination, (u8 *)0x04000000 + blockOffset, copySize);
            destination += copySize;
        }
    } else {
        func_00199B50(D_002B9127);
        RhFile_ReadAndBlock(handle, position, size, destination);
    }
    func_00199B50(D_002B9135);
    RhFile_CloseFile(handle);
    return 1;
}

/* Called when a sound-driver file read finishes. */
void lSDFS_FinishCallback(void) {
    s32 position;
    s32 size;

    func_00199B50(D_002B9141);
    if (s_iUsingNow != 0) {
        if (D_0030FFA0.src != 0) {
            func_00198790((void *)D_0030FFA0.src, (u8 *)0x04000000 + D_0030FFA0.offset, D_0030FFA0.size);
        }
        if (D_0030FFA0.left != 0) {
            position = D_0030FFA0.position;
            D_0030FFA0.src += D_0030FFA0.size;
            D_0030FFA0.offset = 0;
            if (D_0030FFA0.left > 0x80000) {
                D_0030FFA0.size = 0x80000;
            } else {
                D_0030FFA0.size = D_0030FFA0.left;
            }
            if (D_0030FFA0.left > D_0030FFA0.size) {
                D_0030FFA0.position += D_0030FFA0.size;
                D_0030FFA0.left -= D_0030FFA0.size;
            } else {
                D_0030FFA0.position = 0;
                D_0030FFA0.left = 0;
            }
            size = ((D_0030FFA0.size + 0x7FF) >> 11) << 11;
            func_00199B50(D_002B9168, gSdfs_sa, 0x04000000);
            RhFile_ReadAndCallbackByFileName((s32)gSdfs_sa, position, size, 0x04000000, lSDFS_FinishCallback, 0, 0x20);
        } else {
            s_iUsingNow = 0;
        }
    }
}

typedef char *VaList_0010C720;
#define VA_START_0010C720(ap, parm) \
    ((ap) = (char *)__builtin_next_arg(parm) - (__builtin_args_info(2) >= 8 ? 0 : (8 - __builtin_args_info(2)) * 8))
#define VA_ARG_0010C720(ap, T) (*(T *)((ap += 8) - 8))

/* Sends command `cmd` with its arguments to the IOP sound driver. */
s32 SDRPC_SendCommand(s32 cmd, ...) {
    s32 id;
    s32 i;
    VaList_0010C720 ap;

    if (g_SDValue == NULL) {
        return 0;
    }
    id = cmd;
    VA_START_0010C720(ap, cmd);
    g_SDValue[0x20] = (s32)&g_SDValue[0x20];
    for (i = 1; i < 7; i++) {
        g_SDValue[0x20 + i] = VA_ARG_0010C720(ap, s32);
    }
    return sceSifCallRpc(&g_SDValue[7], id, 0, &g_SDValue[0x20], 0x40, &g_SDValue[0x60], 0x10, 0, 0);
}
