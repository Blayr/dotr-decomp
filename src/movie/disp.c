/* Movie player: display set-up and the v-blank handler. */

#include "common.h"
#include "campaign.h"

typedef struct {
    u16 nloop : 15;
    u16 eop : 1;
    u8 reserved[5];
    u8 pad7 : 4;
    u8 nreg : 4;
    u8 reg : 4;
    u8 pad8 : 4;
    u8 tail[7];
} GifTag_00241C20;

typedef struct {
    void *base;
    s32 size;
    void *current;
    void *giftag;
} Packet_00241C20;

typedef struct {
    __int128 value;
} Quad_00241C20;

/* Clears a rectangle of GS memory to colour (r, g, b). */
void clearGsMem(s32 red, s32 green, s32 blue, s32 width, s32 height) {
    void sceGsSetDefDrawEnv(void *, s32, s64, s64, s32, s32);
    void sceDmaSend(s32, s32);
    extern void sceGifPkInit();
    extern Quad_00241C20 D_0029B2C0;
    extern GifTag_00241C20 D_00350410;
    extern u8 D_00350420[];
    extern u8 D_00350440[];
    Quad_00241C20 tag;
    Packet_00241C20 packet;
    u32 data[24];
    s32 channel;

    tag = D_0029B2C0;
    channel = sceDmaGetChan(2);
    *(__int128 *)&D_00350410 = 0;
    D_00350410.nloop = 8;
    D_00350410.eop = 1;
    D_00350410.nreg = 1;
    D_00350410.reg = 14;
    sceGsSetDefDrawEnv(D_00350420, 0, (s64)(s16)width,
                 (s64)(s16)(((((height >> 1) + 31) >> 5) + ((height + 31) >> 5)) << 6),
                 0, 0);
    *(s64 *)D_00350440 = 0;
    FlushCache(0);
    sceGsSyncPath(0, 0);
    sceGsPutDrawEnv(&D_00350410);
    sceGifPkInit(&packet, (__int128 *)data);
    sceGifPkReset(&packet);
    sceGifPkEnd(&packet, 0, 0, 0);
    sceGifPkOpenGifTag(&packet, *(__int128 *)&tag);
    sceGifPkAddGsAD(&packet, 0, 6);
    sceGifPkAddGsAD(&packet, 1, ((s64)blue << 16) | ((s64)red | ((s64)green << 8)));
    sceGifPkAddGsAD(&packet, 5, 0);
    sceGifPkAddGsAD(&packet, 5, ((s64)0xB400 << 16) | 0x2D00);
    sceGifPkCloseGifTag(&packet);
    sceGifPkTerminate(&packet);
    FlushCache(0);
    sceGsSyncPath(0, 0);
    sceDmaSend(channel, packet.size);
    sceGsSyncPath(0, 0);
}

typedef struct {
    u32 words[4];
} Tag_00241E80;

extern Tag_00241E80 D_0029B2D0;
extern Tag_00241E80 D_0029B2E0;

/* Builds the DMA tags that send a decoded movie picture to the GS. */
void setImageTag(u64 tags, u8 *image, s32 width, s32 height, s32 dbp) {
    void sceGifPkRef(void *, u64, s32, s32, s32, s32);
    u8 spB0[16];
    Tag_00241E80 spC0;
    Tag_00241E80 spD0;
    s32 temp_s0;
    s32 temp_s7;
    s32 i;
    s32 j;
    s32 var_s3;
    u64 rowBits;
    s32 var_s5;
    u64 *sceGifPkReserve2;

    spC0 = D_0029B2D0;
    temp_s7 = height >> 4;
    temp_s0 = dbp >> 4;
    spD0 = D_0029B2E0;
    sceGifPkInit(&spB0, (tags & 0x0FFFFFFF) | 0x20000000);
    sceGifPkReset(&spB0);
    if (width == 0) {
        sceGifPkCnt(&spB0, 0, 0, 0);
        sceGifPkOpenGifTag(&spB0, *(__int128 *) &spC0);
        sceGifPkAddGsAD(&spB0, 0x50, 0xC1B00ULL << 0x20);
        sceGifPkAddGsAD(&spB0, 0x52, 0x10 | (0x10ULL << 0x20));
        sceGifPkCloseGifTag(&spB0);
        i = 0;
        if (i < temp_s7) {
            var_s5 = 0;
            do {
                j = 0;
                if (j < temp_s0) {
                    var_s3 = 0;
                    rowBits = (u64) (u32) var_s5 << 0x20;
                    do {
                        sceGifPkCnt(&spB0, 0, 0, 0);
                        sceGifPkOpenGifTag(&spB0, *(__int128 *) &spC0);
                        sceGifPkAddGsAD(&spB0, 0x51, rowBits | ((u64) (u32) var_s3 << 0x30));
                        sceGifPkAddGsAD(&spB0, 0x53, 0);
                        sceGifPkCloseGifTag(&spB0);
                        sceGifPkReserve2 = sceGifPkReserve(&spB0, 4);
                        sceGifPkReserve2[0] = 0x40 | (0x08000000ULL << 0x20);
                        sceGifPkReserve2[1] = 0;
                        sceGifPkRef(&spB0, (u64) (u32) image & 0x0FFFFFFF, 0x40, 0, 0, 0);
                        j += 1;
                        image += 0x400;
                        var_s3 += 0x10;
                    } while (j < temp_s0);
                }
                i += 1;
                var_s5 += 0x10;
            } while (i < temp_s7);
        }
    }
    sceGifPkEnd(&spB0, 0, 0, 0);
    sceGifPkOpenGifTag(&spB0, *(__int128 *) &spD0);
    sceGifPkAddGsAD(&spB0, 0x3F, 0);
    sceGifPkAddGsAD(&spB0, 0x14, 0x60);
    sceGifPkAddGsAD(&spB0, 6, (0xA803ULL << 0x10) | 0x1B00 | (0xAULL << 0x20));
    sceGifPkAddGsAD(&spB0, 0, 0x116);
    sceGifPkAddGsAD(&spB0, 3, 0x80008);
    sceGifPkAddGsAD(&spB0, 5, 0x79006C00);
    sceGifPkAddGsAD(&spB0, 3, (s64) ((height * 0x10) + 8) | ((s64) ((dbp * 0x10) + 8) << 0x10));
    sceGifPkAddGsAD(&spB0, 5, (0x8700ULL << 0x10) | 0x9400);
    sceGifPkCloseGifTag(&spB0);
    sceGifPkTerminate(&spB0);
}

/* The movie player's vertical-blank handler: flips to the next decoded picture. */
s32 vblankHandler(s32 val) {
    extern volatile s32 vblankCount;
    extern s32 handler_error;
    extern u8 D_00350420[];
    extern u8 D_00350510[];
    void *dmaGif;
    s32 *tag;

    dmaGif = (void *)sceDmaGetChan(2);
    (&isCountVblank)[6] = (*(volatile u64 *)GS_CSR_ADDR >> 13) & 1;
    if (isCountVblank) {
        vblankCount++;
        handler_error = sceGsSyncPath(1, 0);
        if (!handler_error) {
            tag = (s32 *)voBufGetTag(voBuf);
            if (!tag) {
                frd++;
                asm("sync"); asm("ei");
                return 0;
            }
            sceGsSetHalfOffset(((&isCountVblank)[6] & 1) ? (u8 *)(((u32)D_00350510 & 0x0FFFFFFF) | 0x20000000)
                                                : (u8 *)(((u32)D_00350420 & 0x0FFFFFFF) | 0x20000000),
                               0x800, 0x800, (&isCountVblank)[6] ^ 1);
            if ((&isCountVblank)[6] == 0 && *tag == 2) {
                sceGsSwapDBuff(D_003503C0, 0);
                sceGsSyncPath(0, 0);
                sceDmaSend(dmaGif, (u8 *)tag + 0x40);
                *tag = 1;
            } else if ((&isCountVblank)[6] == 1 && *tag == 1) {
                sceGsSwapDBuff(D_003503C0, 1);
                sceGsSyncPath(0, 0);
                sceDmaSend(dmaGif, (u8 *)tag + 0x26740);
                *tag = 0;
                isFrameEnd = 1;
            }
        }
    }
    asm("sync"); asm("ei");
    return 0;
}

/* The movie player's end-of-picture DMA handler. */
s32 handler_endimage(void) {
    if (isFrameEnd != 0) {
        voBufDecCount(&voBuf);
        isFrameEnd = 0;
    }
    asm("sync"); asm("ei");
    return 0;
}

/* Starts showing movie pictures from the next vertical blank. */
void startDisplay(s32 field) {
    do {
    } while (field == sceGsSyncV(0));
    frd = 0;
    isCountVblank = 1;
    (&isCountVblank)[2] = 0;
}

/* Stops showing movie pictures. */
void endDisplay(void) {
    isCountVblank = 0;
    frd = 0;
}
