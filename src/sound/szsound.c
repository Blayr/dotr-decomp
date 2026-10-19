/* The game's sound calls (SzSound_*). */

#include "common.h"

typedef struct State_00217410 {
    s16 slots[4];
    s8 enabled : 1;
    s8 reserved : 7;
    u8 padding[3];
} State_00217410;

extern State_00217410 soundState; /* original: gSzSound_sl */
extern u8 D_002D0930[];

/* Starts the sound system: the IOP driver, the sound effect groups, the music. */
void SzSound_Init(void) {
    extern u8 *getenv();
    State_00217410 *state = &soundState;
    s16 *slot;
    s32 i;

    RhMem_FillMemory((s8 *)&soundState, 0, 0xC);
    state->enabled = getenv(D_002D0930) ? 1 : 0;
    if (state->enabled) {
        SD_Init(0x400000);
        SD_BGMSetSourceLevel(0x80, 0x80);
        slot = state->slots;
        i = 0;
        do {
            i += 1;
            *slot++ = -1;
        } while (i < 4);
        SzSound_SetOutput(1);
    }
}

typedef struct Flags_002174D0 {
    s8 active : 1;
} Flags_002174D0;

typedef struct State_002174D0 {
    u8 pad[8];
    Flags_002174D0 flags;
} State_002174D0;

struct State_00217410;

/* Ends the sound system. */
void SzSound_Term(void) {
    extern struct State_00217410 soundState;
    extern Flags_002174D0 soundOutRelated;
    State_002174D0 *state = (State_002174D0 *)&soundState;

    if (soundOutRelated.active) {
        SD_Term();
        state->flags.active = 0;
    }
}

typedef struct {
    s8 active : 1;
} Flags_00217530;

extern Flags_00217530 soundOutRelated;

/* Whether the sound system is ready. */
s32 SzSound_IsStandby(void) {
    return soundOutRelated.active != 0 ? 1 : 0;
}

#ifndef GAME_H
/* The game translation unit already declares this global with its local type. */
typedef struct {
    signed char active : 1;
} Flags_00217530;

extern Flags_00217530 soundOutRelated;
#endif

/* The sound system's per-vertical-blank work. */
void SzSound_VSync(void) {
    if (soundOutRelated.active) {
        SD_CallEveryVSync();
    }
}

/* Loads sound effect group `group` into channel `channel` (0..3), unless it is already there (`force` reloads). */
s32 SzSound_TransferSEGrp(s32 channel, s32 group, s32 force) {
    extern char *seGroupFileNames[];
    extern void func_0019B648();
    extern s32 SD_iTransferSEGrpToIop();
    State_00217410 *state = &soundState;
    char text[0x80];

    if (!soundOutRelated.active) {
        return 0;
    }
    if (channel < 0 || channel >= 4) {
        return 0;
    }
    if (force == 0 && state->slots[channel] == group) {
        return 1;
    }
    state->slots[channel] = group;
    SD_SEStop(channel, -1);
    switch (channel) {
    case 0:
    case 1:
        func_0019B648(text, seGroupFileNames[channel], group);
        break;
    default:
        func_0019B648(text, seGroupFileNames[channel], group, group);
        break;
    }
    return SD_iTransferSEGrpToIop(channel, text);
}

#ifndef GAME_H
typedef struct {
    signed char active : 1;
} Flags_002176B0;
extern Flags_002176B0 soundOutRelated;
#endif

/* Whether a sound effect is playing. */
s32 SzSound_IsPlaySE(void) {
    extern s64 SD_iGetSDStatus();

    if (!soundOutRelated.active) {
        return 0;
    }
    return !((s32)SD_iGetSDStatus() & 0x4000) ? 1 : 0;
}

/* Plays sound effect `se` (bit 15: looping) of channel `channel` (0..3). */
s32 SzSound_PlaySE(s32 channel, s32 se) {
    extern s64 SD_iGetSDStatus();
    State_00217410 *state = &soundState;

    if (!soundOutRelated.active) {
        return 0;
    }
    if (channel < 0 || channel >= 4) {
        return 0;
    }
    if (state->slots[channel] < 0) {
        return 0;
    }
    if ((s32)SD_iGetSDStatus() & 0x4000) {
        return 0;
    }
    SD_SEPlayOnlyOnce(channel, se & 0x7FFF, (se & 0x8000) ? 1 : 0);
    return 1;
}

/* Plays sound effect `se` of channel `channel` with stereo pan `pan`. */
s32 SzSound_StereoPlaySE(s32 channel, s32 se, s32 pan) {
    extern s64 SD_iGetSDStatus();
    State_00217410 *state = &soundState;

    if (!soundOutRelated.active) {
        return 0;
    }
    if (channel < 0 || channel >= 4) {
        return 0;
    }
    if (state->slots[channel] < 0) {
        return 0;
    }
    if ((s32) SD_iGetSDStatus() & 0x4000) {
        return 0;
    }
    se &= 0x7FFF;
    pan &= 0x7FFF;
    SD_SEPlay2(channel, se, pan);
    return 1;
}

/* Stops sound effect `se` (-1: all) of channel `channel`. */
s32 SzSound_StopSE(s32 channel, s32 se) {
    State_00217410 *state = &soundState;

    if (!soundOutRelated.active) {
        return 0;
    }
    if (channel < 0 || channel >= 4) {
        return 0;
    }
    if (state->slots[channel] < 0) {
        return 0;
    }
    if ((s64)SD_iGetSDStatus() & 0x4000) {
        return 0;
    }
    SD_SEStop(channel, se);
    return 1;
}

/* Starts music `bgm` (preloading it), with `mode`. */
s32 SzSound_PlayBGM(s32 bgm, s32 mode) {
    if (soundOutRelated.active == 0) {
        return 0;
    }
    SD_BGMPreLoad(bgm, mode);
    return 1;
}

/* Whether music is still loading. */
s32 SzSound_IsLoadingBGM(void) {
    if (soundOutRelated.active == 0) {
        return 0;
    }
    return (SD_IsLoadingNow() != 0) ? 1 : 0;
}

typedef struct {
    s8 enabled : 1;
} Flags_00217A10;

extern Flags_00217A10 D_0034F6E8_2;

/* Stops the music, fading it out over `fade` frames (0: at once). */
s32 SzSound_StopBGM(s64 fade) {
    if (D_0034F6E8_2.enabled == 0) {
        return 0;
    }
    if (fade > 0) {
        SD_BGMFadeOut((s16) fade);
    } else {
        SD_BGMStop();
    }
    return 1;
}

typedef struct {
    s8 active : 1;
    s8 mode : 1;
} Flags_00217A70;

typedef struct {
    u8 pad[8];
    Flags_00217A70 flags;
} State_00217A70;

extern State_00217A70 soundState_2; /* original: gSzSound_sl */

/* Sets the sound output: stereo (`stereo` set) or mono. */
s32 SzSound_SetOutput(s32 stereo) {
    State_00217A70 *state = &soundState_2;

    if (D_0034F6E8_2.enabled == 0) {
        return 0;
    }
    state->flags.mode = (s8)(stereo ? 1 : 0);
    SD_SetOutputType(state->flags.mode ? 0 : 1);
    return 1;
}
