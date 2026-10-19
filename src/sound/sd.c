/* Sound driver, EE side (SD_*): start-up, BGM and sound-effect calls. */

#include "common.h"

/* Starts the sound driver on the IOP. */
void SD_InitializeDevice(void) {
    if (g_SDValue == NULL || g_SDBuffer == 0) {
        return;
    }
    if (!(g_SDValue[0] & 1)) {
        SDRPC_Init();
        SDRPC_SendCommand(0xF005);
        if (!(g_SDValue[0] & 0x20)) {
            SDRPC_SendCommand(0xF002, 0xC1800);
            g_SDValue[5] = g_SDValue[0x60];
            g_SDValue[0] |= 0x20;
        }
        SDRPC_SendCommand(0x5F10, 0, 0x5010);
        SDRPC_SendCommand(0x5F10, 1, 0x9F810);
        SDRPC_SendCommand(0x5F10, 2, 0x199810);
        SDRPC_SendCommand(0x5F10, 3, 0x1CB810);
        SDRPC_SendCommand(0x5F10, 4, 0x1FD810);
        SDRPC_SendCommand(0x5F10, 5, 0x8F810);
        SDRPC_SendCommand(0x5F10, 6, 0x9F810);
        SDRPC_SendCommand(0x5F10, 7, 0xAF810);
        SDRPC_SendCommand(0x5F10, 8, 0xBF810);
        SDRPC_SendCommand(0x5F10, 9, 0xD7810);
        SDRPC_SendCommand(0x5F10, 0xA, 0xEF810);
        SDRPC_SendCommand(0x5F10, 0xB, 0x107810);
        SDRPC_SendCommand(0x5F12, 0x150000, 0x38000);
        SD_vInitializeFileHandler();
        SD_vInitSDThread();
        SD_vInitializeAutoDMA();
        g_SDValue[0] |= 1;
        g_SDValue[1] |= 0xE;
        g_SDValue[0xA9B] = 0;
    }
    g_SDValue[0] |= 0x80;
}

/* Starts the sound driver in the work area at `work` (0x2A80 bytes of status, then its buffer): clears the
   transfer queue and sets up the IOP side. */
s32 SD_Init(s32 work) {
    g_SDValue = (s32 *)work;
    g_SDBuffer = work + 0x2A80;
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

/* Plays sound effect `se` of the group loaded in slot `slot` (0..3; `param`). */
void SD_SEPlay2(s32 slot, s32 se, s32 param) {
    if (g_SDValue == NULL || g_SDBuffer == 0) {
        return;
    }
    if ((g_SDValue[1] & 4) && (g_SDValue[0] & 1) && ((s64)SD_iGetSDStatus() & 0x80)) {
        SDRPC_SendCommand(0x5210, slot, se, param, 0);
    }
}

/* Plays sound effect `se` of the group loaded in slot `slot` (0..3) with volume, pan, pitch and flags. */
void SD_SEPlayWithParam6(s32 slot, s32 se, s32 volume, s32 pan, s32 pitch, s32 flags) {
    s32 sp78;
    s32 sp7C;
    u8 *bytes;

    if (g_SDValue == NULL || g_SDBuffer == 0) {
        return;
    }
    if ((g_SDValue[1] & 4) && (g_SDValue[0] & 1) && ((s64)SD_iGetSDStatus() & 0x80)) {
        bytes = (u8 *)&sp78;
        bytes[0] = slot;
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

/* Plays sound effect `se` of slot `slot` at default volume, pan and pitch; `flags` is the flags byte (1 = loop). */
void SD_SEPlayOnlyOnce(s32 slot, s32 se, s32 flags) {
    SD_SEPlayWithParam6(slot, se, 0, 0, 0, flags);
}

/* Stops sound effect `se` of the group loaded in slot `slot`. */
void SD_SEStop(s32 slot, s32 se) {
    if (g_SDValue == NULL || g_SDBuffer == 0) {
        return;
    }
    if ((g_SDValue[1] & 4) && (g_SDValue[0] & 1) && ((s64)SD_iGetSDStatus() & 0x80)) {
        SDRPC_SendCommand(0x5201, slot, se);
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
