/* Screen fades (SzFade_*). */

#include "common.h"

/* Clears the two fades. */
void SzFade_Init(void) {
    Entry_0031C050 *entry;
    s32 count;

    entry = fadeSlots;
    count = 2;
    while (count--) {
        entry->flag = 1;
        entry++;
    }
}

typedef struct {
    u8 r, g, b, a;
} Color_001FCC70;

typedef struct {
    u8 value : 6;
    u8 unused : 2;
} Value_001FCC70;

typedef struct {
    s8 flag : 1;
    s8 unused : 7;
} Flags_001FCC70;

/* Starts fade `fade` (0 or 1): towards `color` (or black) when `toColor` is 1 (a fade out), away from it when 0 (a fade in); `step` per frame from `start` to `length`. */
s32 SzFade_Entry(s32 fade, s32 toColor, u8 step, u8 start, u8 length, void *color) {
    Entry_0031C050 *entry;

    entry = &fadeSlots[fade];
    if (entry->flag == 0) {
        return 0;
    }
    ((Value_001FCC70 *)((u8 *)entry + 7))->value = toColor;
    entry->pad0[4] = step;
    entry->lo = start;
    entry->hi = length;
    entry->flag = 0;
    entry->pad7b = 0;
    ((Flags_001FCC70 *)entry->pad8)->flag = 0;
    if (color != 0) {
        *(Color_001FCC70 *)entry->pad0 = *(Color_001FCC70 *)color;
    } else {
        entry->pad0[2] = 0;
        entry->pad0[1] = 0;
        entry->pad0[0] = 0;
        entry->pad0[3] = 0x80;
    }
    return 1;
}

/* Stops fade `fade`. */
s32 SzFade_Destroy(s32 fade) {
    Entry_0031C050 *temp_a2;

    temp_a2 = &fadeSlots[fade];
    temp_a2->flag = 1;
    return 1;
}

/* Draws and advances both fades. */
void SzFade_DispAll(void) {
    s32 i;

    i = 0;
    do {
        SzFade_Disp(i);
        i += 1;
    } while (i < 2);
}

typedef struct {
    s8 paused : 1;
    s8 unused : 7;
} Flags_001FCDE0;

/* Draws fade `fade` at its current level and advances it. */
s32 SzFade_Disp(s32 fade) {
    u8 color[4];
    Entry_0031C050 *entry;
    s32 next;
    u8 amount;

    if ((fade < 0) || (fade >= 2)) {
        return 0;
    }
    entry = &fadeSlots[fade];
    if (entry->flag != 0) {
        return 0;
    }
    amount = entry->lo;
    if (!(*(u8 *)((u8 *)entry + 7) & 0x3F)) {
        amount = entry->hi - amount;
    }
    color[2] = entry->pad0[2];
    color[1] = entry->pad0[1];
    color[0] = entry->pad0[0];
    color[3] = (entry->pad0[3] * (amount & 0xFF)) / entry->hi;
    SzFade_Draw(0, (s32)color, 0xFFFFFF);
    if (entry->lo >= entry->hi) {
        if (entry->pad7b != 0) {
            entry->flag = 1;
        }
    } else if (((Flags_001FCDE0 *)&entry->pad8[0])->paused == 0) {
        next = entry->lo + entry->pad0[4];
        if (entry->hi < next) {
            entry->lo = entry->hi;
        } else {
            entry->lo = next;
        }
    }
    return 1;
}

/* Draws a full-screen rectangle in colour `color` with alpha mode `alpha` at depth `z`. */
void SzFade_Draw(s32 alpha, s32 color, s32 z) {
    RhBase_SetVifPacketArea(SzFade_Draw_Pipe(RhBase_GetVifPacketArea(), alpha, color, z));
}

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 reserved : 8;
} Vertex_001FCF90;

typedef struct {
    u16 count;
    u16 flags;
    u32 reserved;
    u64 registers;
} Header_001FCF90;

typedef struct {
    u64 tag[2];
    u8 color[4];
    f32 q;
    Vertex_001FCF90 vertices[2];
} Packet_001FCF90;

/* Fills a GIF tag. */
static inline void init_001FCF90(void *tag) {
    ((Header_001FCF90 *)tag)->flags = 6;
    ((Header_001FCF90 *)tag)->count = 3;
    ((Header_001FCF90 *)tag)->registers = 0x441;
    ((Header_001FCF90 *)tag)->reserved = 0;
}

/* Draws a full-screen rectangle in colour `color` with alpha mode `alpha` at depth `z`. */
s32 SzFade_Draw_Pipe(s32 cursor, s32 alpha, s32 color, s32 z) {
    Packet_001FCF90 packet;

    init_001FCF90((Header_001FCF90 *)packet.tag);
    ExAssignAlpha(&packet, ExGetAlphaVal(alpha));
    packet.color[0] = ((u8 *)color)[2];
    packet.color[1] = ((u8 *)color)[1];
    packet.color[2] = ((u8 *)color)[0];
    packet.color[3] = ((u8 *)color)[3];
    packet.q = 1.0f;
    packet.vertices[0].x = 0x6C00;
    packet.vertices[0].y = 0x7200;
    packet.vertices[0].z = (u32)z;
    packet.vertices[0].reserved = 0;
    packet.vertices[1].x = 0x9400;
    packet.vertices[1].y = 0x8E00;
    packet.vertices[1].z = (u32)z;
    packet.vertices[1].reserved = 0;
    return ExSortPrim_Pipe(cursor, (s32)&packet, 0, 0);
}

/* Makes fade `fade` stop by itself when it is done. */
s32 SzFade_SetKillFlag(s32 fade) {
    Entry_0031C050 *entry;

    if (fade < 0 || fade >= 2) {
        return 0;
    }
    entry = &fadeSlots[fade];
    if (entry->flag) {
        return 0;
    }
    entry->pad7b = -1;
    return 1;
}

typedef struct {
    s8 enabled : 1;
    s8 pad : 7;
} Flags_001FD130;

/* Pauses (`on`) or resumes fade `fade`. */
s32 SzFade_SetPauseFlag(s32 fade, s64 on) {
    Entry_0031C050 *temp_a2;

    if (fade < 0 || fade >= 2) {
        return 0;
    }
    temp_a2 = &fadeSlots[fade];
    if (temp_a2->flag != 0) {
        return 0;
    }
    ((Flags_001FD130 *) temp_a2->pad8)->enabled = (s8) on;
    return 1;
}

/* How many steps fade `fade` has left, or 0. */
s32 SzFade_GetRestCount(s32 fade) {
    Entry_0031C050 *e;

    if (fade < 0 || fade >= 2) {
        return -1;
    }
    e = &fadeSlots[fade];
    if (e->flag != 0) {
        return -1;
    }
    return e->hi - e->lo;
}

/* The steps a fade has left. */
static inline s32 calc_001FD220(s32 idx) {
    Entry_0031C050 *e;

    if (idx < 0 || idx >= 2) {
        return -1;
    }
    e = &fadeSlots[idx];
    if (e->flag) {
        return -1;
    }
    return e->hi - e->lo;
}

/* Whether fade `fade` is running. */
s32 SzFade_IsDoing(s32 fade) {
    s32 i;
    s32 want = fade ? 1 : 0;

    for (i = 0; i < 2; i++) {
        if (calc_001FD220(i) >= want) {
            return 1;
        }
    }
    return 0;
}
