/* Textures: binding and flushing (RhText_*). */

#include "common.h"

/* Relocates the TIM2 file at `address` (its offsets become pointers). */
void RhText_BindAddress(s32 address) {
    u8 *entry;
    s32 i;
    s32 count;

    *(s32 *)((u8 *)address + 0xC) = address;
    count = *(s32 *)((u8 *)address + 0x58);
    entry = (u8 *)address + *(s32 *)((u8 *)address + 0x10);
    for (i = 0; i < count; i += 1) {
        *(s32 *)(entry + 4) = address + *(s32 *)(entry + 4);
        entry += 0x30;
    }
}

/* Adds a texture-cache flush to the packet. */
s32 RhText_SetTextureFlush(s32 cursor) {
    sceVif1PkInit(D_0032A5E0, cursor);
    sceVif1PkCnt(D_0032A5E0, 0);
    sceVif1PkAddCode(D_0032A5E0, 0x11000000);
    sceVif1PkAlign(D_0032A5E0, 2, 3);
    sceVif1PkOpenDirectHLCode(D_0032A5E0, 0);
    *(u64 *)&D_0032A600 = 0x8000 | ((u64)0x10000000 << 32);
    *((u64 *)&D_0032A600 + 1) = 0xE;
    sceVif1PkOpenGifTag(D_0032A5E0, D_0032A600);
    sceVif1PkAddGsAD(D_0032A5E0, 0x3F, 1);
    sceVif1PkCloseGifTag(D_0032A5E0);
    sceVif1PkCloseDirectHLCode(D_0032A5E0);
    return sceVif1PkTerminate(D_0032A5E0);
}
