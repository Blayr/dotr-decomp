#include "common.h"

/* Starts the sound driver: clears the transfer queue and sets up the IOP side (`mode`). */
s32 SD_Init(s32 mode) {
    g_SDValue = (s32 *)mode;
    g_SDBuffer = mode + 0x2A80;
    func_00198948(g_SDValue, 0, 0x2A80);
    *(s32 *)((u8 *)g_SDValue + 0x1DC) = -1;
    *(s32 *)((u8 *)g_SDValue + 0x1F4) = -1;
    *(s32 *)((u8 *)g_SDValue + 0x2248) = -1;
    *(s32 *)((u8 *)g_SDValue + 0x2254) = -1;
    *(s32 *)((u8 *)g_SDValue + 0x224C) = -1;
    *(s32 *)((u8 *)g_SDValue + 0x2258) = -1;
    *(s32 *)((u8 *)g_SDValue + 0x2250) = -1;
    *(s32 *)((u8 *)g_SDValue + 0x225C) = -1;
    SD_ClearXferQueue();
    SD_InitializeDevice();
    return 1;
}

/* Shuts the sound driver down on the IOP. */
void SD_Term(void) {
    SDRPC_SendCommand(0xF004, g_SDValue[5]);
}

/* Pauses (`suspend` 1) or resumes the sound system, muting the music while paused. */
void SD_SuspendSoundSystem(s32 suspend) {
    if (suspend != 0) {
        SD_BGMSetSourceLevel(0, 0);
        SDRPC_SendCommand(0x5004, 0x7FFF);
    }
    SDRPC_SendCommand(0xF006, suspend);
}

/* The sound driver's per-frame work: IOP commands, file reads, the streamed music's watchdog. */
void SD_CallEveryVSync(void) {
    s32 temp_v0;

    if (g_SDValue == NULL || g_SDBuffer == 0) {
        return;
    }
    if (g_SDValue[0] & 1) {
        if (SDRPC_SendCommand(0x5002) == 0) {
            func_00198790((u8 *)g_SDValue + 0x54, (u8 *)g_SDValue + 0x180, 0x10);
            g_SDValue[0x1EC / 4] = g_SDValue[0x60 / 4];
            temp_v0 = g_SDValue[0x5C / 4];
            if (temp_v0 != 0) {
                g_SDValue[0x18 / 4] = temp_v0;
            }
        }
        SD_vDoFsCommandQueue();
        SD_vAutoDMASequentialWatchDog();
        SD_vTransferSEGrpToIopProc();
        SD_vRunAmbienceOnIopProc();
    }
}

/* Preloads music `bgm` (`mode`) so it can start without a wait. */
s32 SD_BGMPreLoad(s32 bgm, s32 mode) {
    if (g_SDValue == NULL || g_SDBuffer == 0) {
        return 0;
    }
    if (!(g_SDValue[1] & 2)) {
        return 1;
    }
    if (g_SDValue[0] & 1) {
        if (mode != 0) {
            SD_iPlayBGMByAutoDMA(bgm);
        } else {
            SD_iPreparePreBlockOnIOP(bgm);
        }
    }
    return 1;
}

/* Whether the sound driver is still reading from the disc. */
s32 SD_IsLoadingNow(void) {
    if (g_SDValue == NULL || g_SDBuffer == 0) {
        return 0;
    }
    return (*g_SDValue & 0x2000) ? 1 : 0;
}

/* Sets the sound output (`type`: stereo or mono). */
void SD_SetOutputType(s32 type) {
    if (g_SDValue == NULL || g_SDBuffer == 0) {
        return;
    }
    SDRPC_SendCommand(0xF003, type);
    *(s32 *)((u8 *)g_SDValue + 0x2A6C) = type;
}

/* Stops the music and every sound effect. */
void SD_StopAll(void) {
    if (g_SDValue == NULL || g_SDBuffer == 0) {
        return;
    }
    SD_BGMStop();
    SD_SEStopAll();
}

/* Stops the streamed music. */
void SD_BGMStop(void) {
    if (g_SDValue == NULL || g_SDBuffer == 0) {
        return;
    }
    if (g_SDValue[1] & 2) {
        if (g_SDValue[0] & 1) {
            SD_iStopAutoDMA();
        }
        g_SDValue[0] &= ~0x200;
    }
}

/* Fades the music out over `frames` frames. */
void SD_BGMFadeOut(s16 frames) {
    if (g_SDValue == NULL || g_SDBuffer == 0) {
        return;
    }
    if (g_SDValue[1] & 2) {
        SDRPC_SendCommand(0x5003, frames);
    }
}

/* The sound driver's first status word (0 before it is set up). */
static inline u32 flags_0010A0F0(void) {
    if (g_SDValue == NULL) {
        return 0;
    }
    return *(u32 *)g_SDValue;
}

/* The music's current volume. */
s32 SD_BGMGetVolume(void) {
    if (g_SDValue == NULL || g_SDBuffer == 0) {
        return 0;
    }
    if ((u64)flags_0010A0F0() & 0x100) {
        return g_SDValue[0x1EC / sizeof(s32)];
    }
    return 0;
}

/* Sets the music's level (`level`) for channel `channel`. */
void SD_BGMSetSourceLevel(s32 channel, s32 level) {
    if (g_SDValue == NULL || g_SDBuffer == 0) {
        return;
    }
    if ((g_SDValue[1] & 2) && (g_SDValue[0] & 1)) {
        if (level < 0) {
            level = -level;
        }
        SDRPC_SendCommand(0x5005, channel, level);
    }
}

/* Plays sound effect `se` of group `group` (`param`). */
void SD_SEPlay2(s32 group, s32 se, s32 param) {
    if (g_SDValue == NULL || g_SDBuffer == 0) {
        return;
    }
    if ((g_SDValue[1] & 4) && (g_SDValue[0] & 1) && ((s64)SD_iGetSDStatus() & 0x80)) {
        SDRPC_SendCommand(0x5210, group, se, param, 0);
    }
}

/* Plays sound effect `se` of group `group` with volume, pan, pitch and flags. */
void SD_SEPlayWithParam6(s32 group, s32 se, s32 volume, s32 pan, s32 pitch, s32 flags) {
    s32 sp78;
    s32 sp7C;
    u8 *bytes;

    if (g_SDValue == NULL || g_SDBuffer == 0) {
        return;
    }
    if ((g_SDValue[1] & 4) && (g_SDValue[0] & 1) && ((s64)SD_iGetSDStatus() & 0x80)) {
        bytes = (u8 *)&sp78;
        bytes[0] = group;
        bytes[1] = se;
        bytes[2] = se;
        bytes[3] = pitch;
        bytes = (u8 *)&sp7C;
        bytes[0] = (volume == 0) ? 0 : 1;
        bytes[1] = volume & 0x7F;
        bytes[2] = pan & 0x7F;
        bytes[3] = flags;
        SDRPC_SendCommand(0x5220, sp78, sp7C);
    }
}

/* Plays sound effect `se` of group `group` unless it is already playing. */
void SD_SEPlayOnlyOnce(s32 group, s32 se, s32 param) {
    SD_SEPlayWithParam6(group, se, 0, 0, 0, param);
}

/* Stops sound effect `se` of group `group`. */
void SD_SEStop(s32 group, s32 se) {
    if (g_SDValue == NULL || g_SDBuffer == 0) {
        return;
    }
    if ((g_SDValue[1] & 4) && (g_SDValue[0] & 1) && ((s64)SD_iGetSDStatus() & 0x80)) {
        SDRPC_SendCommand(0x5201, group, se);
    }
}

/* Stops every sound effect. */
void SD_SEStopAll(void) {
    if (g_SDValue == NULL || g_SDBuffer == 0) {
        return;
    }
    if ((g_SDValue[1] & 4) && (g_SDValue[0] & 1) && ((s64)SD_iGetSDStatus() & 0x80)) {
        SDRPC_SendCommand(0x5202);
    }
}

typedef struct State_0010A4D0 {
    u32 flags;
    u32 flags4;
    u8 pad8[0xC];
    s32 source;
    u8 pad18[0x40];
    u8 busy;
    u8 pad59[0x1FF3];
    s32 pending;
    u8 pad2050[0x178];
    u8 buffer[0x40];
    s32 states[2];
    s32 indexes[2];
    s32 values[2];
    u8 pad2220[0x38];
    s32 results[2];
} State_0010A4D0;

extern u8 D_002B9090[];

/* Stores `value` as result `index` of the sound driver's IOP status block. */
static inline void set_result_0010A4D0(s32 index, s32 value) {
    State_0010A4D0 *state = (State_0010A4D0 *)g_SDValue;
    ((State_0010A4D0 *)((index << 2) + (s32)state))->results[0] = value;
}

/* Starts ambience streams on the IOP when their files are ready. */
void SD_vRunAmbienceOnIopProc(void) {
    s32 i;
    State_0010A4D0 *slot;

    if (g_SDValue != NULL && (((State_0010A4D0 *)g_SDValue)->flags4 & 8)) {
        i = 0;
        do {
            switch (((State_0010A4D0 *)g_SDValue)->states[i]) {
            case 1:
                if (SD_DoesExistAnyCDReq() == 0 && ((State_0010A4D0 *)g_SDValue)->busy == 0 && ((State_0010A4D0 *)g_SDValue)->pending == 0) {
                    func_0019B648(((State_0010A4D0 *)g_SDValue)->buffer, D_002B9090, ((State_0010A4D0 *)g_SDValue)->values[i]);
                    if (RhFile_ExistFile((s32)((State_0010A4D0 *)g_SDValue)->buffer) == 0) {
                        ((State_0010A4D0 *)g_SDValue)->states[i] = 0;
                        break;
                    }
                    SD_AddReadToEeReq(((State_0010A4D0 *)g_SDValue)->buffer, (u8 *)(g_SDBuffer + (i << 12)) + 0x101800, 0, 0x1000);
                    slot = (State_0010A4D0 *)g_SDValue;
                    slot = (State_0010A4D0 *)((i << 2) + (s32)slot);
                    slot->states[0]++;
                }
                return;
            case 2:
                if (SD_DoesExistAnyCDReq() == 0) {
                    slot = (State_0010A4D0 *)g_SDValue;
                    slot = (State_0010A4D0 *)((i << 2) + (s32)slot);
                    slot->states[0]++;
                }
                return;
            case 3:
                if (SD_DoesExistAnySIFReq() == 0) {
                    SD_AddEeToIopReq((s32)((u8 *)(g_SDBuffer + (i << 12)) + 0x101800), ((State_0010A4D0 *)g_SDValue)->source + 0xC0800, 0x1000);
                    slot = (State_0010A4D0 *)g_SDValue;
                    slot = (State_0010A4D0 *)((i << 2) + (s32)slot);
                    slot->states[0]++;
                }
                return;
            case 4:
                if (SD_DoesExistAnySIFReq() == 0) {
                    SDRPC_SendCommand(0x5401, ((State_0010A4D0 *)((i << 2) + (s32)g_SDValue))->indexes[0], ((State_0010A4D0 *)g_SDValue)->source + 0xC0800);
                    ((State_0010A4D0 *)((i << 2) + (s32)g_SDValue))->states[0]++;
                }
                return;
            case 5:
                if (!(((State_0010A4D0 *)g_SDValue)->busy & 8)) {
                    ((State_0010A4D0 *)((i << 2) + (s32)g_SDValue))->states[0] = 0;
                    slot = ((State_0010A4D0 *)((i << 2) + (s32)g_SDValue));
                    set_result_0010A4D0(slot->indexes[0], slot->values[0]);
                }
                return;
            default:
                ((State_0010A4D0 *)g_SDValue)->states[i] = 0;
                break;
            }
            i++;
        } while (i < 2);
        if (!(((State_0010A4D0 *)g_SDValue)->flags & 0x200000)) {
            ((State_0010A4D0 *)g_SDValue)->flags &= ~0x8000;
        }
    }
}

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

/* Moves loaded sound-effect groups from main memory to the IOP, one step per call. */
void SD_vTransferSEGrpToIopProc(void) {
    u8 request[0x1C];
    s32 command;

    if (g_SDValue != NULL && (g_SDValue[1] & 4)) {
        switch (g_SDValue[0x82C]) {
        case 1:
            if (SDFS_IsUsingNow() == 0) {
                SD_AddEeToIopReq((s32)((u8 *)g_SDBuffer + 0x101800),
                             g_SDValue[5] + 0x40000, 0x80800);
                g_SDValue[0x82C]++;
            }
            break;
        case 2:
            if (SD_DoesExistAnySIFReq() == 0) {
                SDRPC_SendCommand(0x5100, g_SDValue[0x82D],
                             g_SDValue[5] + 0x40000);
                g_SDValue[0x82C]++;
            }
            break;
        case 3:
            if (((u8 *)g_SDValue)[0x5A] == 0) {
                g_SDValue[0x82C] = 0;
                g_SDValue[0] &= ~0x4000;
            }
            break;
        case 20:
            if (SD_IsAnyJobOnCD() == 0) {
                g_SDValue[0x82C] = 1;
            }
            break;
        case 30:
            if (SD_IsAnyJobOnCD() == 0) {
                g_SDValue[0x82C]++;
            }
            break;
        case 31:
            if (SDFS_IsUsingNow() == 0) {
                g_SDValue[0x82E] = *(s32 *)((u8 *)g_SDBuffer + 0x101804) + 0x800;
                g_SDValue[0x82F] = 0;
                if (g_SDValue[0x82E] <= 0x80800) {
                    g_SDValue[0x830] = g_SDValue[0x82E];
                } else {
                    g_SDValue[0x830] = 0x80800;
                }
                SD_AddEeToIopReq((s32)((u8 *)g_SDBuffer + 0x101800),
                             g_SDValue[5] + 0x40000, g_SDValue[0x830]);
                g_SDValue[0x82E] -= g_SDValue[0x830];
                *(u32 *)&g_SDValue[0x82F] += g_SDValue[0x830];
                g_SDValue[0x82C]++;
            }
            break;
        case 32:
            if (SD_DoesExistAnySIFReq() == 0) {
                SDRPC_SendCommand(0x5102, g_SDValue[0x82D],
                             g_SDValue[5] + 0x40000, g_SDValue[0x830], 0);
                if (g_SDValue[0x82E] > 0) {
                    g_SDValue[0x82C]++;
                } else {
                    g_SDValue[0x82C] = 3;
                }
            }
            break;
        case 33:
            if (((u8 *)g_SDValue)[0x5A] == 0) {
                if (g_SDValue[0x82E] <= 0x80800) {
                    g_SDValue[0x830] = g_SDValue[0x82E];
                } else {
                    g_SDValue[0x830] = 0x80800;
                }
                SD_AddReadToEeReq(g_SDValue + 0x81C,
                             (u8 *)g_SDBuffer + 0x101800,
                             g_SDValue[0x82F], g_SDValue[0x830]);
                g_SDValue[0x82C]++;
            }
            break;
        case 34:
            if (SD_IsAnyJobOnCD() == 0) {
                g_SDValue[0x82C]++;
            }
            break;
        case 35:
            if (SDFS_IsUsingNow() == 0) {
                SD_AddEeToIopReq((s32)((u8 *)g_SDBuffer + 0x101800),
                             g_SDValue[5] + 0x40000, g_SDValue[0x830]);
                g_SDValue[0x82E] -= g_SDValue[0x830];
                *(u32 *)&g_SDValue[0x82F] += g_SDValue[0x830];
                g_SDValue[0x82C]++;
            }
            break;
        case 36:
            if (SD_DoesExistAnySIFReq() == 0) {
                SDRPC_SendCommand(0x5102, g_SDValue[0x82D],
                             g_SDValue[5] + 0x40000, g_SDValue[0x830],
                             g_SDValue[0x82F] - g_SDValue[0x830] - 0x800);
                if (g_SDValue[0x82E] > 0) {
                    g_SDValue[0x82C] = 33;
                } else {
                    g_SDValue[0x82C] = 3;
                }
            }
            break;
        default:
            g_SDValue[0x82C] = 0;
            if (SD_FetchFromXferQueue(&command, request) != 0) {
                SD_KickSEGroupReadSequence(command, (s32)request);
            }
            break;
        }
    }
}

/* Queues a sound-effect group transfer to the IOP. */
s32 SD_iTransferSEGrpToIop(void) {
    extern s32 SD_AddToXferQueue();

    if (g_SDValue == NULL) {
        return 0;
    }
    if (!(g_SDValue[1] & 4)) {
        return 0;
    }
    if (g_SDValue[0] & 1) {
        return SD_AddToXferQueue();
    }
    return 0;
}

/* Starts reading sound-effect group `group` from the disc into slot `slot`. */
void SD_KickSEGroupReadSequence(s32 group, s32 slot) {
    *(s32 *)((u8 *)g_SDValue + 0x20B4) = group;
    func_0019B648((u8 *)g_SDValue + 0x2070, D_002B90B0, slot);
    SD_AddReadToEeReq((u8 *)g_SDValue + 0x2070, (u8 *)g_SDBuffer + 0x101800, 0, 0x80800);
    *g_SDValue |= 0x4000;
    *(s32 *)((u8 *)g_SDValue + 0x20B0) = 0x1E;
}

/* Adds transfer `value` (data `src`) to the transfer queue. */
s32 SD_AddToXferQueue(s32 value, void *src) {
    s32 next;
    s32 offset;
    s8 index;

    index = *(s8 *)((u8 *)g_SDValue + 0x20C4);
    next = (index + 1) & 7;
    if (next == *(s8 *)((u8 *)g_SDValue + 0x20C5)) {
        return 0;
    }
    offset = index << 5;
    *(s32 *)(offset + (u32)g_SDValue + 0x20C8) = value;
    func_0019C2B8((u8 *)g_SDValue + offset + 0x20CC, src, 0x1C);
    *(s8 *)((u8 *)g_SDValue + 0x20C4) = next;
    return 1;
}

/* Takes the next transfer off the queue into `outValue` and `outData`. */
s32 SD_FetchFromXferQueue(s32 *outValue, void *outData) {
    s32 temp_v1_2;
    s8 temp_v1;

    temp_v1 = *(s8 *)((u8 *)g_SDValue + 0x20C5);
    if (temp_v1 == *(s8 *)((u8 *)g_SDValue + 0x20C4)) {
        return 0;
    }
    *(s8 *)((u8 *)g_SDValue + 0x20C5) = (s8)((temp_v1 + 1) & 7);
    temp_v1_2 = temp_v1 << 5;
    *outValue = *(s32 *)(temp_v1_2 + (u32)g_SDValue + 0x20C8);
    func_0019C2B8(outData, (u8 *)g_SDValue + temp_v1_2 + 0x20CC, 0x1C);
    return 1;
}

/* Empties the transfer queue. */
void SD_ClearXferQueue(void) {
    *((s8 *)g_SDValue + 0x20C5) = 0;
    *((s8 *)g_SDValue + 0x20C4) = 0;
}

/* Whether any disc read is waiting. */
s32 SD_DoesExistAnyCDReq(void) {
    s32 temp_v0;
    s32 temp_v0_2;

    temp_v0_2 = g_SDValue[0x1710 / sizeof(s32)];
    if (temp_v0_2 != 0) {
        return temp_v0_2;
    }
    temp_v0 = g_SDValue[0x171C / sizeof(s32)];
    if (temp_v0 != 0) {
        return temp_v0;
    }
    return 0;
}

/* Whether any IOP transfer is waiting. */
s32 SD_DoesExistAnySIFReq(void) {
    s32 temp_v0;
    s32 temp_v0_2;

    temp_v0_2 = *(s32 *)((u8 *)g_SDValue + 0x1820);
    if (temp_v0_2 != 0) {
        return temp_v0_2;
    }
    temp_v0 = *(s32 *)((u8 *)g_SDValue + 0x182C);
    if (temp_v0 != 0) {
        return temp_v0;
    }
    return 0;
}

typedef struct {
    u8 data[0x40];
    s32 arg1;
    s32 arg2;
    s32 arg3;
} Request_0010BE60;

typedef struct {
    s32 arg0;
    s32 arg1;
    s32 arg2;
    s32 reserved;
} Request2_0010BE60;

typedef struct {
    s32 flags;
    u8 padding[0x124C];
    Request_0010BE60 requests[16];
    s32 pending;
    s32 write;
    s32 read;
    s32 state;
    Request2_0010BE60 requests2[16];
    s32 pending2;
    s32 write2;
    s32 read2;
    s32 state2;
} Queues_0010BE60;

/* Runs the next waiting disc read or IOP transfer. */
void SD_vDoFsCommandQueue(void) {
    extern s32 s_iHowManyTimesCDAreUsed;
    Queues_0010BE60 *queues;
    Queues_0010BE60 *queues2;
    s32 state2;
    s32 state;
    Request_0010BE60 *request;
    Request2_0010BE60 *request2;
    s32 *stateField;
    s32 *state2Field;

    queues = (Queues_0010BE60 *)g_SDValue;
    stateField = &queues->state;
    state = *stateField;
    if (state != 0) {
        request = &queues->requests[queues->read];
        switch (state) {
        case 1:
            if (SDFS_IsUsingNow() == 0) {
                SDFS_ReadToEE((s32)request, request->arg1, request->arg2, request->arg3);
                ((Queues_0010BE60 *)g_SDValue)->state++;
                ((Queues_0010BE60 *)g_SDValue)->flags |= 0x800000;
            }
            break;
        case 2:
            if (SDFS_IsUsingNow() == 0) {
                s_iHowManyTimesCDAreUsed++;
                ((Queues_0010BE60 *)g_SDValue)->flags &= 0xFF7FFFFF;
                ((Queues_0010BE60 *)g_SDValue)->read = (((Queues_0010BE60 *)g_SDValue)->read + 1) % 16;
                ((Queues_0010BE60 *)g_SDValue)->state++;
            }
            break;
        default:
            *stateField = 0;
            break;
        }
    } else if (queues->pending != 0) {
        *stateField = 1;
        ((Queues_0010BE60 *)g_SDValue)->pending--;
    }
    queues2 = (Queues_0010BE60 *)g_SDValue;
    state2Field = &queues2->state2;
    state2 = *state2Field;
    if (state2 != 0) {
        request2 = &queues2->requests2[queues2->read2];
        switch (state2) {
        case 1:
            if (SDRPC_TranserToIopStatus() < 0) {
                SDRPC_StartTransferToIop(request2->arg0, request2->arg1, request2->arg2);
                ((Queues_0010BE60 *)g_SDValue)->state2++;
                ((Queues_0010BE60 *)g_SDValue)->flags |= 0x08000000;
                return;
            }
            break;
        case 2:
            if (SDRPC_TranserToIopStatus() < 0) {
                ((Queues_0010BE60 *)g_SDValue)->flags &= 0xF7FFFFFF;
                ((Queues_0010BE60 *)g_SDValue)->read2 = (((Queues_0010BE60 *)g_SDValue)->read2 + 1) % 16;
                ((Queues_0010BE60 *)g_SDValue)->state2++;
                return;
            }
            break;
        default:
            *state2Field = 0;
            return;
        }
    } else if (queues2->pending2 != 0) {
        *state2Field = 1;
        ((Queues_0010BE60 *)g_SDValue)->pending2--;
    }
}

typedef struct {
    char name[0x40];
    u8 *data;
    s32 offset;
    s32 size;
} Request_0010C110;

typedef struct {
    u8 padding[0x1250];
    Request_0010C110 requests[16];
    s32 count;
    s32 index;
} Queue_0010C110;

/* Queues a disc read of file `name` into `dst` (`offset`, `size`). */
void SD_AddReadToEeReq(void *name, void *dst, s32 offset, s32 size) {
    Request_0010C110 *request;

    request = &((Queue_0010C110 *)g_SDValue)->requests[((Queue_0010C110 *)g_SDValue)->index];
    func_0019BDD8(request->name, (const char *)name);
    request->data = dst;
    request->offset = offset;
    request->size = size;
    request->offset &= ~0x7FF;
    request->data -= offset - request->offset;
    request->size += offset - request->offset;
    request->size += 0x7FF;
    request->size &= ~0x7FF;
    ((Queue_0010C110 *)g_SDValue)->index = (((Queue_0010C110 *)g_SDValue)->index + 1) % 16;
    ((Queue_0010C110 *)g_SDValue)->count++;
}

typedef struct QueueEntry_0010C220 {
    s32 value0;
    s32 value1;
    s32 value2;
    s32 unused;
} QueueEntry_0010C220;

typedef struct Queue_0010C220 {
    u8 padding[0x1720];
    QueueEntry_0010C220 entries[16];
    s32 count;
    s32 write_index;
} Queue_0010C220;

/* Queues a transfer of `size` bytes from `src` to IOP address `dst`. */
void SD_AddEeToIopReq(s32 src, s32 dst, s32 size) {
    QueueEntry_0010C220 *entry;

    entry = &((Queue_0010C220 *)g_SDValue)->entries[((Queue_0010C220 *)g_SDValue)->write_index];
    entry->value0 = src;
    entry->value1 = dst;
    entry->value2 = size;
    ((Queue_0010C220 *)g_SDValue)->write_index = (((Queue_0010C220 *)g_SDValue)->write_index + 1) % 16;
    ((Queue_0010C220 *)g_SDValue)->count++;
}

/* Whether the sound driver has a disc job running. */
s32 SD_IsAnyJobOnCD(void) {
    s32 var_v0;

    var_v0 = 1;
    if ((g_SDValue[0x5C4] == 0) && (g_SDValue[0x5C7] == 0)) {
        var_v0 = 0;
    }
    return var_v0;
}

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
