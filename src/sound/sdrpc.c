/* Sound driver: calls to the IOP (SDRPC_*). */

#include "common.h"

/* Starts a DMA of `size` bytes from `src` to IOP address `dst`. */
s32 SDRPC_StartTransferToIop(s32 src, s32 dst, s32 size) {
    FlushCache(0);
    g_SDValue[0x11] = src;
    g_SDValue[0x12] = dst;
    g_SDValue[0x13] = size;
    g_SDValue[0x14] = 0;
    g_SDValue[0x19] = sceSifSetDma(&g_SDValue[0x11], 1);
    return g_SDValue[0x19];
}

/* Whether the last DMA to the IOP is still running. */
s32 SDRPC_TranserToIopStatus(void) {
    return sceSifDmaStat(g_SDValue[0x64 / sizeof(s32)]);
}

/* Binds the IOP sound driver's remote call server. */
s32 SDRPC_Init(void) {
    s32 count;

    do {
        if (sceSifBindRpc((u8 *)g_SDValue + 0x1C, 0x05730601, 0) < 0) {
            for (;;) {
            }
        }
        count = 1000000;
        while (count-- != 0) {
        }
    } while (g_SDValue[0x10] == 0);
    FlushCache(0);
    return 1;
}
