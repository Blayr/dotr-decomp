/* Sound driver: PCM decoding, BGM streaming and the auto-DMA to the IOP. */

#include "common.h"

/* Decodes the music block in buffer `buf` (LPCM) for the IOP. */
s32 _iDecodeLPCM(s32 buf) {
    s16 left;
    s16 *src;
    s16 *dst;
    s32 row;
    u32 column;
    s16 *dst2;
    s16 right;

    FlushCache(0);
    row = 0;
    src = (s16 *)(g_SDBuffer + 0x800);
    src += buf >> 1;
    dst = (s16 *)((u8 *)g_SDBuffer + 0x181800);
    do {
        dst2 = dst + 0x100;
        column = 0;
        do {
            s16 *end;

            left = src[0];
            right = src[1];
            src += 2;
            if (g_SDValue[0x2A6C / 4] != 0) {
                right = (left + right) >> 1;
                left = right;
            }
            dst[0] = left;
            dst[1] = left;
            dst2[0] = right;
            dst2[1] = right;
            dst += 2;
            dst2 += 2;
            end = (s16 *)(g_SDBuffer + 0x800);
            end = (s16 *)((s32)end + 0x100000);
            if ((s32)src >= (s32)end) {
                src = (s16 *)((s32)src - 0x100000);
            }
            column++;
        } while (column < 0x80U);
        buf += 0x200;
        dst = dst2;
        buf %= 0x100000;
        row++;
    } while (row < 0x80);
    return buf;
}

/* The sound driver's status word. */
s32 SD_iGetSDStatus(void) {
    return *g_SDValue;
}

/* Reads the sound driver's file table from the disc. */
void SD_vInitializeFileHandler(void) {
    extern s32 SDFS_ReadToEEBlock();

    SDFS_ReadToEEBlock(s_szReadPCMListAtFirst, g_SDValue + 0x84, 0, 0x1000);
}

extern u8 D_002B90A0[];

typedef struct Entry_0010A8D0 {
    s32 size;
    s32 id;
    s32 start;
    s32 end;
} Entry_0010A8D0;

typedef struct Table_0010A8D0 {
    u8 header[0x210];
    Entry_0010A8D0 entries[0x100];
} Table_0010A8D0;

/* The music-file table entry with id `id`, or -1. */
static inline s32 find_0010A8D0(s32 id) {
    s32 i = 0;
    do {
        if (((Table_0010A8D0 *) g_SDValue)->entries[i].id == id) {
            return i;
        }
        i++;
    } while (i < 0x100);
    return -1;
}

/* Clears `count` bytes (at most 128 KB) of the music ring buffer from the write point plus `offset`, wrapping at 1
   MB. */
static inline void clear_0010A8D0(s32 count, s32 offset) {
    __int128 *ptr;

    if (count > 0x20000) {
        count = 0x20000;
    }
    ptr = (__int128 *) ((u8 *) g_SDBuffer + 0x800);
    count >>= 4;
    ptr = (__int128 *) ((u8 *) ptr + (*(s32 *) ((u8 *) g_SDValue + 0x1D0) + offset));
    if (count != 0) {
        do {
            *ptr = 0;
            ptr++;
            if ((u8 *) ptr >= (u8 *) g_SDBuffer + 0x100800) {
                ptr = (__int128 *) ((u8 *) ptr - 0x100000);
            }
            count--;
        } while (count != 0);
    }
}

/* Loads music block `block` of file `file` into main memory (`mode`). */
void _vLoadBGMFileToEE(s32 file, s32 block, s32 mode) {
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_s2;
    s32 temp_s3;
    s32 temp_s3_2;
    s32 temp_s4;
    s32 temp_s5;
    s32 temp_s6;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_s0;
    s32 var_s1;
    s32 var_s2;
    s32 var_s3;
    s32 var_s7;

    var_s0 = mode;
    var_s1 = block;
    var_a0 = find_0010A8D0(file);
    if (var_a0 >= 0) {
        temp_s3 = g_SDValue[var_a0 * 4 + 0x84];
        temp_s4 = g_SDValue[var_a0 * 4 + 0x86] * 4;
        temp_s5 = g_SDValue[var_a0 * 4 + 0x87] * 4;
        temp_s3 &= ~0xF;
        temp_s4 &= ~0xF;
        temp_s5 &= ~0xF;
        if (var_s1 < temp_s3) {
            func_0019B648((u8 *) g_SDValue + 0x1210, D_002B90A0, file);
            if (temp_s5 != 0) {
                while (var_s1 + var_s0 > temp_s5) {
                    temp_s3_2 = temp_s5 - var_s1;
                    var_s7 = temp_s3_2;
                    func_0019B648((u8 *) g_SDValue + 0x1210, D_002B90A0, file);
                    temp_a1 = *(s32 *) ((u8 *) g_SDValue + 0x1D0);
                    if ((temp_a1 + temp_s3_2) >= 0x100000) {
                        temp_s6 = 0x100000 - temp_a1;
                        SD_AddReadToEeReq((u8 *) g_SDValue + 0x1210, (void *) (g_SDBuffer + temp_a1 + 0x800), var_s1 + 0x800, temp_s6);
                        var_s1 += temp_s6;
                        var_s7 -= temp_s6;
                        *(s32 *) ((u8 *) g_SDValue + 0x1D0) = 0;
                    }
                    if (var_s7 != 0) {
                        SD_AddReadToEeReq((u8 *) g_SDValue + 0x1210, (void *) (g_SDBuffer + *(s32 *) ((u8 *) g_SDValue + 0x1D0) + 0x800), var_s1 + 0x800, var_s7);
                        *(s32 *) ((u8 *) g_SDValue + 0x1D0) += var_s7;
                    }
                    var_s0 -= temp_s3_2;
                    var_s1 = temp_s4;
                }
            } else if (temp_s3 < var_s1 + var_s0) {
                var_a0_2 = var_s1 + var_s0 - temp_s3;
                var_s0 -= var_a0_2;
                clear_0010A8D0(var_a0_2, var_s0);
            }
            var_s3 = var_s0;
            var_s2 = var_s1;
            func_0019B648((u8 *) g_SDValue + 0x1210, D_002B90A0, file);
            temp_a1_2 = *(s32 *) ((u8 *) g_SDValue + 0x1D0);
            if ((temp_a1_2 + var_s0) >= 0x100000) {
                temp_s2 = 0x100000 - temp_a1_2;
                SD_AddReadToEeReq((u8 *) g_SDValue + 0x1210, (void *) (g_SDBuffer + temp_a1_2 + 0x800), var_s1 + 0x800, temp_s2);
                var_s3 = var_s0 - temp_s2;
                var_s2 = var_s1 + temp_s2;
                *(s32 *) ((u8 *) g_SDValue + 0x1D0) = 0;
            }
            if (var_s3 != 0) {
                SD_AddReadToEeReq((u8 *) g_SDValue + 0x1210, (void *) (g_SDBuffer + *(s32 *) ((u8 *) g_SDValue + 0x1D0) + 0x800), var_s2 + 0x800, var_s3);
                *(s32 *) ((u8 *) g_SDValue + 0x1D0) += var_s3;
            }
            var_s1 += var_s0;
            *(s32 *) ((u8 *) g_SDValue + 0x1CC) = var_s1;
        }
    }
}

/* The music block entry (of 256) holding `value`, or -1. */
static inline s32 find_0010AC20(s32 *base, s32 value) {
    u8 *entry;
    s32 i;

    for (i = 0, entry = (u8 *)base; i < 0x100; i++, entry += 0x10) {
        if (*(s32 *)(entry + 0x214) == value) {
            return i;
        }
    }
    return -1;
}

/* Decodes music buffer `buf` and sends it to the IOP. */
void _vDecodeLPCMThenSendToIOP(s32 buf) {
    s32 index;
    s32 end;

    FlushCache(0);
    if (g_SDValue[0x1DC / 4] == 0x23A7) {
        SD_BGMFadeOut(0x100);
        g_SDValue[0x2248 / 4] = 0x23A7;
        return;
    }
    index = find_0010AC20(g_SDValue, g_SDValue[0x1DC / 4]);
    if (index == -1) {
        return;
    }
    g_SDValue[0x1C8 / 4] = _iDecodeLPCM(g_SDValue[0x1C8 / 4]);
    g_SDValue[0x1D4 / 4] += 0x4000;
    end = g_SDValue[index * 4 + 0x87];
    if (end != 0) {
        if (end < g_SDValue[0x1D4 / 4]) {
            g_SDValue[0x1D4 / 4] -= end;
            g_SDValue[0x1D4 / 4] += g_SDValue[index * 4 + 0x86];
        }
    } else if (g_SDValue[0x1D4 / 4] > (g_SDValue[index * 4 + 0x84] >> 2)) {
        SD_iStopAutoDMA();
        return;
    }
    SD_AddEeToIopReq((s32)((u8 *)g_SDBuffer + 0x181800), g_SDValue[5] + (g_SDValue[0x1D8 / 4] << 17), 0x20000);
    g_SDValue[0x1D8 / 4] = 1 - g_SDValue[0x1D8 / 4];
}

/* Keeps the streamed music fed: loads and decodes the next blocks, restarts the stream when it stops. */
void SD_vAutoDMASequentialWatchDog(void) {
    s32 flags;
    s32 input;
    s32 mode;

    if ((g_SDValue[1] & 2) &&
        ((flags = g_SDValue[0]) & 0x10) &&
        (flags & 0x20) && (flags & 0x40)) {
        if (g_SDValue[0x7B] == 0) {
            SD_iStopAutoDMA();
        }
        switch (g_SDValue[0x79]) {
        default:
            g_SDValue[0x79] = 0;
            break;
        case 100:
            if (SD_BGMGetVolume() == 0) {
                SD_iStopAutoDMA();
                g_SDValue[0x72] = 0;
                g_SDValue[0x73] = 0;
                g_SDValue[0x74] = 0;
                g_SDValue[0x79]++;
            }
            break;
        case 101:
        case 102:
        case 103:
            g_SDValue[0x79]++;
            break;
        case 104:
            if (g_SDValue[0x892] == 0x23A7) {
                g_SDValue[0] &= ~0x100;
                g_SDValue[0] &= ~0x2000;
                g_SDValue[0] &= ~0x200;
                g_SDValue[0x77] = 0x23A7;
                g_SDValue[0x79] = 0;
            } else {
                g_SDValue[0x79] = 1;
                g_SDValue[0x77] = g_SDValue[0x892];
            }
            break;
        case 1:
            if (g_SDValue[0x7F] & 2) {
                _vLoadBGMFileToEE(g_SDValue[0x77], 0, 0x90000);
            } else {
                _vLoadBGMFileToEE(g_SDValue[0x77], 0, 0x100000);
            }
            g_SDValue[0x79]++;
            return;
        case 2:
            if (SD_DoesExistAnyCDReq() == 0) {
                g_SDValue[6] = 0;
                g_SDValue[0x71] = 0;
                g_SDValue[0x70] = 0;
                g_SDValue[0x76] = 0;
                _vDecodeLPCMThenSendToIOP(0);
                g_SDValue[0x79]++;
            }
            return;
        case 3:
            if (SD_DoesExistAnySIFReq() == 0) {
                _vDecodeLPCMThenSendToIOP(0);
                g_SDValue[0x79]++;
            }
            return;
        case 4:
            if (SD_DoesExistAnySIFReq() == 0) {
                if (g_SDValue[0x7F] & 2) {
                    g_SDValue[0x7F] &= ~2;
                    g_SDValue[0x79]++;
                } else {
                    g_SDValue[0x7F] = 4;
                    g_SDValue[0x79] = 0;
                    g_SDValue[0] &= ~0x2000;
                }
            }
            break;
        case 5:
            _vLoadBGMFileToEE(g_SDValue[0x77], 0x90000, 0x70000);
            SD_iStopAutoDMA();
            SD_iStartAutoDMA();
            g_SDValue[0x79]++;
            return;
        case 6:
            if (SD_DoesExistAnyCDReq() == 0) {
                g_SDValue[0x79] = 0;
                g_SDValue[0] &= ~0x2000;
            }
            break;
        }
        if (g_SDValue[0] & 0x100) {
            if ((g_SDValue[0x71] & 0x01000000) !=
                ((input = g_SDValue[6]) & 0x01000000)) {
                g_SDValue[0x71] = input;
                g_SDValue[0x70] = g_SDValue[0x71];
                g_SDValue[0x76] = (g_SDValue[0x70] & 0x01000000) ? 0 : 1;
                _vDecodeLPCMThenSendToIOP(0);
                if ((g_SDValue[0] & 0x100) &&
                    ((mode = g_SDValue[0x72]) == 0 || mode == 0xA0000)) {
                    _vLoadBGMFileToEE(g_SDValue[0x77], g_SDValue[0x73], 0x80000);
                }
                g_SDValue[0x70] = 0;
            }
        }
    }
}

/* Starts the music stream's automatic DMA on the IOP. */
s32 SD_iStartAutoDMA(void) {
    g_SDValue[0] |= 0x100;
    g_SDValue[0x1FC / 4] &= ~4;
    g_SDValue[0x1D4 / 4] = 0;
    g_SDValue[0x2254 / 4] = g_SDValue[0x1DC / 4];
    SDRPC_SendCommand(0x1020, g_SDValue[0x14 / 4], 0x40000, 1);
    return 1;
}

/* Stops the music stream's automatic DMA. */
s32 SD_iStopAutoDMA(void) {
    s32 temp_v1;

    if (!(g_SDValue[1] & 2)) {
        return 0;
    }
    temp_v1 = g_SDValue[0];
    if (temp_v1 & 0x100) {
        g_SDValue[0] = temp_v1 & ~0x100;
        g_SDValue[0] &= ~0x200;
        *(s32 *)((u8 *)g_SDValue + 0x18) = 0;
        *(s32 *)((u8 *)g_SDValue + 0x1C4) = 0;
        *(s32 *)((u8 *)g_SDValue + 0x1C0) = 0;
        SDRPC_SendCommand(0x1021);
        *(s32 *)((u8 *)g_SDValue + 0x1D4) = 0;
        *(s32 *)((u8 *)g_SDValue + 0x1D8) = 0;
        *(s32 *)((u8 *)g_SDValue + 0x2254) = -1;
    }
    return 1;
}

/* Sets up the sound driver's thread state. */
void SD_vInitSDThread(void) {
    s32 temp_a0;

    temp_a0 = *g_SDValue;
    if (!(temp_a0 & 0x10)) {
        *g_SDValue = temp_a0 | 0x10;
    }
}

/* Sets up the music stream's automatic DMA on the IOP. */
void SD_vInitializeAutoDMA(void) {
    if (!(g_SDValue[0] & 0x40)) {
        SDRPC_SendCommand(0x5000);
        g_SDValue[0] |= 0x40;
        g_SDValue[0x7A] = -1;
    }
}

/* The music block entry (of 256) holding `value`, or -1. */
static inline s32 find_0010B3C0(s32 *base, s32 value) {
    u8 *entry;
    s32 i;

    for (i = 0, entry = (u8 *)&base[i * 4]; i < 0x100; i++, entry += 0x10) {
        if (*(s32 *)(entry + 0x214) == value) {
            return i;
        }
    }
    return -1;
}

/* Sends the first block of music `bgm` to the IOP ahead of play. */
s32 SD_iPreparePreBlockOnIOP(s32 bgm) {
    if (!(g_SDValue[1] & 2)) {
        return 0;
    }

    SD_BGMFadeOut(0x100);
    *(s32 *)((u8 *)g_SDValue + 0x2248) = bgm;

    if (find_0010B3C0(g_SDValue, bgm) < 0) {
        if (bgm != 0x23A7) {
            return 0;
        }
    }

    *(s32 *)((u8 *)g_SDValue + 0x1FC) = 1;
    *(s32 *)((u8 *)g_SDValue + 0x1E4) = 0x64;
    g_SDValue[0] |= 0x2000;
    return 1;
}

/* The music-file table entry with id `id`, or -1. */
static inline s32 find_0010B490(s32 id) {
    s32 *entry;
    s32 i;

    i = 0;
    entry = &g_SDValue[i * 4];

    do {
        if (entry[0x85] == id) {
            return i;
        }
        i++;
        entry += 4;
    } while (i < 0x100);
    return -1;
}

/* Starts music `bgm` streaming by automatic DMA. */
s32 SD_iPlayBGMByAutoDMA(s32 bgm) {
    s32 i;
    s32 current;

    if ((g_SDValue[1] & 2) == 0) {
        return 0;
    }

    i = find_0010B490(bgm);
    if (i < 0 && bgm != 0x23A7) {
        return 0;
    }

    g_SDValue[0x892] = bgm;
    current = g_SDValue[0x77];
    if (current == bgm && (g_SDValue[0] & 0x100) != 0) {
        if (g_SDValue[0x7B] < 0x7FFF) {
            SDRPC_SendCommand(0x5004, 0x100);
        }
        if ((g_SDValue[0] & 0x2000) != 0) {
            g_SDValue[0] &= ~0x2000;
        }
        return 1;
    }

    if (g_SDValue[0x7F] == 4 && current == bgm) {
        g_SDValue[0] |= 0x100;
        g_SDValue[0x7F] &= ~4;
        g_SDValue[0x75] = 0;
        g_SDValue[0x895] = g_SDValue[0x77];
        SDRPC_SendCommand(0x1020, g_SDValue[5], 0x40000, 1);
        return 1;
    }

    if ((g_SDValue[1] & 2) != 0) {
        s32 j;

        SD_BGMFadeOut(0x100);
        g_SDValue[0x892] = bgm;
        j = find_0010B490(bgm);
        if (j >= 0 || bgm == 0x23A7) {
            g_SDValue[0x7F] = 1;
            g_SDValue[0x79] = 0x64;
            g_SDValue[0] |= 0x2000;
        }
    }

    g_SDValue[0x7F] |= 2;
    return 1;
}
