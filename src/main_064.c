#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_064", func_00228150);

INCLUDE_ASM("asm/nonmatchings/main_064", func_00228460);

typedef struct {
    u8 pad[0x46];
    s16 normal;
    s16 pad48;
    s16 special;
} Card_00228660;

typedef struct {
    u8 pad[0x26];
    s16 slots[7];
} Side_00228660;

typedef struct {
    f32 x[64];
    f32 z[64];
    s16 count;
    s16 value;
} Path_00228660;

typedef struct {
    u8 pad0[0x22C];
    Path_00228660 paths[2][16];
    s16 values[2][16];
    s16 rows[2][16][64];
    s16 countA[32];
    s16 countB[32];
    u8 pad536C[4];
    s16 saved;
} Work_00228660;

extern Card_00228660 D_00299020[][16];
extern s8 D_00299E13[];
extern s8 D_00299ED7;

void func_00228660(s16 player, s16 side, s8 state, s16 *items, s16 count) {
    extern Side_00228660 D_00298BA0[];
    Work_00228660 *work = (Work_00228660 *)0x01ED0000;
    s8 *status = &D_00299E10;
    s16 i;
    s16 item;
    s16 id;

    *(s16 *)0x01ED0060 = 0;
    *(s8 *)0x01ED5372 = 1;
    *(s8 *)0x01ED5373 = 0;
    *(s8 *)0x01ED537B = 0;
    *(s8 *)0x01ED53A0 = 0;
    *(s8 *)0x01ED5375 = 1;
    D_00299ED7 = side;
    *(s16 *)0x01ED01DA = 0;
    *(s16 *)0x01ED01DE = 0;
    *(s16 *)0x01ED01D8 = 0;
    *(s8 *)0x01ED546C = 0;
    D_00299E13[side] = state;

    for (i = 0; i < count; i++) {
        item = items[i];
        if (player == 0 && D_00298BA0[side].slots[i] == 2) {
            id = D_00299020[player][item].special;
        } else {
            id = D_00299020[player][item].normal;
        }
        if (status[id + 3] == 0) {
            s16 j;

            work->countA[id] = 0;
            work->countB[id] = 0;
            status[id + 3] = 0;
            work->paths[player][item].value = 0;
            work->values[player][item] = 0;
            for (j = 0; j < 64; j++) {
                work->rows[player][item][j] = 0;
            }
        }
    }

    if (player == 0 && work->paths[player][12].value == 0) {
        s16 total = 0;
        s16 index;

        for (index = 2; index <= 10; index++) {
            if (status[index + 3] >= 3) {
                total++;
                if (total >= 8) {
                    work->saved = *(s16 *)(status + 0xC2);
                    *(s16 *)(status + 0xC2) = 0x2B70;
                }
            }
        }
    }
}

void func_00228940(s16 arg0, s16 arg1) {
    *(s16 *)0x01ED01A4 = arg0;
    *(s16 *)0x01ED01B2 = arg1;
    *(s16 *)0x01ED01B0 = 0;
    *(s16 *)0x01ED01A6 = 0;
    *(s8 *)0x01ED01B4 = 1;
}

s32 func_00228970(void) {
    s16 temp_v1;
    s16 temp_v1_2;

    if (*(s16 *)0x01ED0060 == 0) {
        *(f32 *)0x01ED0050 = *(f32 *)0x01ED0040;
        *(f32 *)0x01ED0058 = *(f32 *)0x01ED0048;
    }
    *(s16 *)0x01ED0060 += 0x10;
    if (*(s16 *)0x01ED0060 >= 0x100) {
        *(s16 *)0x01ED0060 = 0x100;
    }
    temp_v1 = *(s16 *)0x01ED0060;
    *(f32 *)0x01ED0040 = ((*(f32 *)0x01ED0050 * (f32)(0x100 - temp_v1)) / 256.0f) + ((*(f32 *)0x01ED01B8 * (f32)temp_v1) / 256.0f);
    temp_v1_2 = *(s16 *)0x01ED0060;
    *(f32 *)0x01ED0048 = ((*(f32 *)0x01ED0058 * (f32)(0x100 - temp_v1_2)) / 256.0f) + ((*(f32 *)0x01ED01C0 * (f32)temp_v1_2) / 256.0f);
    if (*(s16 *)0x01ED0060 >= 0x100) {
        *(s16 *)0x01ED0060 = 0;
        *(f32 *)0x01ED0050 = *(f32 *)0x01ED0040;
        *(f32 *)0x01ED0058 = *(f32 *)0x01ED0048;
        *(s8 *)0x01ED5372 = 0;
        *(s8 *)0x01ED5375 = 0;
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_064", func_00228AD0);

INCLUDE_ASM("asm/nonmatchings/main_064", func_00228F50);

typedef struct State_00229140 {
    s8 pad0[3];
    s8 levels[17];
    u8 pad14[0xAE];
    s16 fieldC2;
    u8 padC4[2];
    s8 selection;
    s8 padC7;
    s8 previous;
    s8 snapshot;
} State_00229140;

extern f32 D_00298BA0[];
extern f32 D_00298BA8[];

s32 func_00229140(s32 arg0, s32 arg1, s16 arg2) {
    State_00229140 *state = (State_00229140 *)&D_00299E10;
    f32 startX;
    f32 startZ;
    s32 index;

    if ((*(s8 *)0x01ED5372 == 0 &&
         arg2 <= *(s16 *)0x01ED536C &&
         *(s8 *)0x01ED537B != 0) ||
        state->levels[state->selection] >= 2 ||
        (state->selection == 15 && state->levels[16] == 0)) {
        switch (*(s8 *)0x01ED5373) {
        case 1:
            state->previous = state->selection;
            *(f32 *)0x01ED0050 = *(f32 *)0x01ED0040;
            *(f32 *)0x01ED0058 = *(f32 *)0x01ED0048;
            *(s16 *)0x01ED0076 = *(s16 *)0x01ED0000;
            *(s16 *)0x01ED0078 = *(s16 *)0x01ED0002;
            *(s16 *)0x01ED0060 = 0;
            *(s8 *)0x01ED5373 += 1;
            *(s16 *)0x01ED01DA = 0;
            *(s16 *)0x01ED01DE = 0;
            *(s16 *)0x01ED01D8 = 1;
            state->snapshot = *(s8 *)0x01ED53C2;
            break;
        case 2:
            *(s16 *)0x01ED0060 += 8;
            startX = *(f32 *)0x01ED0050;
            *(f32 *)0x01ED0040 = startX +
                ((f32)*(s16 *)0x01ED0060 *
                 (D_00298BA0[state->selection * 13] - startX)) / 256.0f;
            startZ = *(f32 *)0x01ED0058;
            *(f32 *)0x01ED0048 = startZ +
                ((f32)*(s16 *)0x01ED0060 *
                 (D_00298BA8[state->selection * 13] - startZ)) / 256.0f;
            index = state->selection * 13;
            if (*(f32 *)0x01ED0040 == D_00298BA0[index]) {
                if (*(f32 *)0x01ED0048 == D_00298BA8[index]) {
                    *(s16 *)0x01ED0060 = 256;
                }
            }
            if (*(s16 *)0x01ED0060 >= 256) {
                *(s16 *)0x01ED0060 = 0;
                *(f32 *)0x01ED0040 = D_00298BA0[state->selection * 13];
                *(f32 *)0x01ED0048 = D_00298BA8[state->selection * 13];
                *(s8 *)0x01ED5373 = 3;
                if (state->selection == 15 && state->levels[16] == 0) {
                    state->fieldC2 = 0x2F08;
                }
                return 1;
            }
            break;
        case 3:
            if (*(s8 *)0x01ED53A0 <= 0 && *(s16 *)0x01ED01D8 == 3) {
                func_002336F0();
            }
            break;
        }
    }
    return 0;
}

static inline s16 isSpecial_002294B0(State_00229140 *state) {
    s16 result = 0;

    if (state->pad0[0] == 0) {
        switch (state->selection) {
        case 2:
        case 4:
        case 5:
        case 6:
        case 8:
        case 9:
        case 10:
            result = 1;
            break;
        case 11:
            if (state->snapshot == 0) {
                result = 1;
            }
            break;
        }
    } else {
        switch (state->selection) {
        case 12:
        case 13:
        case 14:
        case 18:
        case 19:
        case 20:
        case 21:
        case 0:
            result = 1;
            break;
        }
    }
    return result;
}

s32 func_002294B0(s32 arg0, s16 arg1) {
    State_00229140 *state = (State_00229140 *)&D_00299E10;

    *(s8 *)0x01ED53C0 = arg1;
    switch (*(s8 *)0x01ED537A) {
    case 0:
        if (state->levels[arg1] == 0) {
            state->levels[arg1] = 1;
        }
        *(s8 *)0x01ED5375 = 1;
        *(f32 *)0x01ED0040 = D_00298BA0[arg1 * 13];
        *(f32 *)0x01ED0048 = D_00298BA8[arg1 * 13];
        *(s16 *)0x01ED0000 = 0x140;
        *(s16 *)0x01ED0002 = 0xBE;
        *(s16 *)0x01ED0070 = 0;
        *(s16 *)0x01ED006C = 0;
        *(s8 *)0x01ED537B = 0;
        *(s8 *)0x01ED537D = 0;
        *(s8 *)0x01ED5440 = 100;
        state->selection = arg1;
        state->padC7 = arg1;
        state->previous = arg1;
        *(s16 *)0x01ED01DA = 0;
        *(s16 *)0x01ED01DE = 0;
        *(s16 *)0x01ED01D8 = 0;
        *(s8 *)0x01ED5406 = 0;
        *(s8 *)0x01ED53AB = 0;
        *(s8 *)0x01ED5472 = 0;
        *(s8 *)0x01ED537A = 1;
        break;
    case 1:
        if (*(s16 *)0x01ED006C >= 0x100) {
            *(s8 *)0x01ED537B = 1;
            *(s8 *)0x01ED537D = 1;
            *(s16 *)0x01ED5478 = 0;
            if (state->fieldC2 >= 300) {
                if (isSpecial_002294B0(state)) {
                    *(s8 *)0x01ED537A = 2;
                } else {
                    *(s8 *)0x01ED537A = 3;
                }
            } else {
                *(s8 *)0x01ED537A = 3;
            }
        }
        break;
    case 2:
        if (*(s8 *)0x01ED5440 <= 0) {
            *(s8 *)0x01ED5472 = 1;
            *(s32 *)0x01ED5474 += 0x1000;
            if (*(s16 *)0x01ED5478 < 0x1000) {
                *(s16 *)0x01ED5478 += 0x20;
                if (*(s16 *)0x01ED5478 >= 0x1000) {
                    *(s16 *)0x01ED5478 = 0x1000;
                    *(s8 *)0x01ED537A = 3;
                    *(s8 *)0x01ED5472 = 0;
                }
            }
        }
        break;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_064", func_002297C0);

typedef union {
    __int128 value;
    s32 axis[4];
} Rotation_0022A020;

extern Rotation_0022A020 D_0029ABB0;

s32 func_0022A020(s32 arg0) {
    Rotation_0022A020 rotation;
    s8 *state = (s8 *)0x01ED0000;
    s16 i;

    rotation = D_0029ABB0;
    rotation.axis[1] = *(s16 *)0x01ED53F4;
    for (i = 0; i <= 9; i++) {
        switch (state[0x53B3]) {
        case 1:
            arg0 = func_001EE4B0(arg0, i + 0x22, 0, (s32)&rotation, 0, 0, 0);
            break;
        default:
            arg0 = func_001EE4B0(arg0, i + 0x22, 0, 0, 0, 0, 0);
            break;
        }
    }
    for (i = 0; i < 2; i++) {
        func_001F30B0(i + 0x1E, 0);
    }
    return arg0;
}

extern s16 D_00299ED2;

typedef struct State_0022A140 {
    u8 pad_0000[0x53A6];
    s8 mode;
    u8 pad_53A7;
    s8 selection;
    s8 transition;
    s8 direction;
    u8 pad_53AB[0x53];
    s16 ids[3];
    u8 pad_5404[0x90];
    s8 phase;
    s8 completed;
    s8 sound[3];
    u8 pad_5499;
    s16 value;
} State_0022A140;

s32 func_0022A140(s32 arg0) {
    s32 texture[24];
    s32 draw[36];
    State_0022A140 *progress;
    s32 index;
    s32 packet;
    State_0022A140 *state = (State_0022A140 *)0x01ED0000;
    s16 i;
    s16 id;
    s16 offset;
    s16 slot;
    s8 *context = &D_00299E10;

    extern s32 func_001D9A20();
    extern void func_001CD560();

    if (D_00299ED2 >= 0x2756 &&
        *(s16 *)(context + 0xC2) < 0x2761 &&
        state->phase < 4) {
        packet = func_001D9A20();
        func_001D9ED0(0xFFFFF8);
        func_001CD560(draw);
        draw[12] = 0x3EF00000;
        draw[13] = 0x3EFA6F4E;
        draw[14] = 0x3F800000;
        draw[15] = 0;
        i = 0;
        progress = state;
        for (; (index = i) < 3; i++) {
            s8 selection = state->selection;
            s8 direction = state->direction;
            slot = (selection + 2 - index) % 3;
            if (direction != 0) {
                if ((s8)direction == 1) {
                    switch (index) {
                    case 0:
                        slot = selection % 3;
                        offset = state->transition * 36 / 100;
                        break;
                    case 1:
                        slot = (selection + 2) % 3;
                        offset = 36 - state->transition * 18 / 100;
                        break;
                    case 2:
                        slot = (selection + 1) % 3;
                        offset = 18 - state->transition * 18 / 100;
                        break;
                    }
                } else {
                    switch (index) {
                    case 0:
                        offset = 36 - state->transition * 36 / 100;
                        break;
                    case 1:
                        offset = 18 + state->transition * 18 / 100;
                        break;
                    case 2:
                        offset = state->transition * 18 / 100;
                        break;
                    }
                }
            } else {
                switch (index) {
                case 0:
                    offset = 36;
                    break;
                case 1:
                    offset = 18;
                    break;
                case 2:
                    offset = 0;
                    break;
                }
            }
            id = state->ids[slot];
            func_001DA2B0(draw, 0,
                         -10.0f + (f32)offset +
                             (f32)(progress->value * 640 / 100 - 640),
                         10.0f);
            func_001DCD70(texture, id);
            packet = func_001DBD30(func_001DBC40(packet, (s32)texture, draw), (s32)draw);
            if (state->mode < 2) {
                state->completed = 0;
            }
            if (state->mode == 2 && state->phase == 0) {
                progress->value += 18;
                if (0 < progress->value &&
                    state->sound[index] == 0) {
                    func_00217710(0, 9);
                    state->sound[index] = 1;
                }
                if (progress->value >= 100) {
                    state->completed = i;
                    progress->value = 100;
                    if (index == 2) {
                        state->phase = 1;
                    }
                }
            } else if (state->mode == 2) {
                progress->value = 100;
            } else if (state->mode >= 3) {
                if (index == 2) {
                    if (state->phase == 3) {
                        progress->value -= 6;
                        if (progress->value <= 0) {
                            progress->value = 0;
                            if (state->phase < 4) {
                                state->phase = 4;
                            }
                        }
                    } else {
                        progress->value = 100;
                    }
                } else {
                    progress->value += 6;
                    if (progress->value >= 400) {
                        progress->value = 400;
                        if (state->phase < 3) {
                            state->phase = 3;
                        }
                    }
                }
            }
            progress = (State_0022A140 *)((u8 *)progress + 2);
        }
        arg0 = func_001D9E70(packet);
    }
    return arg0;
}

typedef struct Item_0022A710 {
    f32 x, y, z;
    s32 pad0C;
    s16 draw0, draw1;
    u8 pad14[0x20];
} Item_0022A710;

typedef struct Vector_0022A710 {
    f32 x, y, z, w;
} Vector_0022A710;

typedef struct State_0022A710 {
    u8 pad00[0x6E];
    s8 enabled;
    u8 pad6F[0x11D];
    s8 all;
    u8 pad18D[0x17];
    s16 active;
    u8 pad1A6[6];
    s8 kind;
    u8 pad1AD[5];
    s16 mode;
    u8 pad1B4[0x5138];
    s16 anim[0x20];
    s16 time[0x20];
    u8 pad536C[6];
    s8 busy;
    u8 pad5373[3];
    s8 ready;
    u8 pad5377[0xD1];
    s8 sound[0x20];
    u8 pad5468[0x19];
    s8 shown;
    s8 hidden;
} State_0022A710;

extern s16 D_00298BB0;
extern s16 D_00298BB2;
extern Item_0022A710 D_00298BD4;
extern Vector_0022A710 D_00298DDC;
extern s16 D_00298DEC;
extern s16 D_00298DEE;
extern Item_0022A710 D_00298E10;
void func_0022B060(s32);
s32 func_0022C570(s32);

void func_0022A710(s32 packet) {
    extern s32 func_001EE4B0();
    extern f32 D_00298BA0[];
    s16 side;
    s16 choice;
    s16 kind;
    s16 animating;
    Vector_0022A710 positions[32];
    s8 *control = &D_00299E10;
    s16 i;
    Item_0022A710 *src;
    Vector_0022A710 *dst;
    State_0022A710 *row;
    State_0022A710 *state = (State_0022A710 *)0x01ED0000;
    s8 *sound;
    f32 height;

    animating = 0;
    packet = func_001EE4B0(packet, 0x22, 0, 0, 0, 0, 0);
    packet = func_001EE4B0(packet, 0x23, 0, 0, 0, 0, 0);
    packet = func_001EE4B0(packet, 0x24, 0, 0, 0, 0, 0);
    packet = func_001EE4B0(packet, 0x25, 0, 0, 0, 0, 0);
    packet = func_001EE4B0(packet, 0x26, 0, 0, 0, 0, 0);
    packet = func_001EE4B0(packet, 0x27, 0, 0, 0, 0, 0);
    packet = func_001EE4B0(packet, D_00298DEC + 0x22, &D_00298DDC, 0, 0, 0, 0);
    packet = func_001EE4B0(packet, D_00298DEE + 0x22, &D_00298DDC, 0, 0, 0, 0);
    src = (Item_0022A710 *)D_00298BA0;
    dst = positions;
    i = 0;
    row = state;
    for (; i <= 21; i++, src++, dst++, row = (State_0022A710 *)((u8 *)row + 2)) {
        height = 12.0f;
        if (i == 16) {
            height = 18.0f;
        }
        if (control[i + 3] != 0) {
            dst->x = src->x;
            dst->y = src->y;
            dst->z = src->z;
        } else if (row->anim[0] != 0) {
            animating = 1;
            dst->x = 0.4f * (f32)((row->time[0] >> 2) % 2) + src->x;
            dst->y = (src->y - height) + height * (f32)row->time[0] / 256.0f;
            dst->z = src->z;
            sound = &state->sound[i];
            if (*sound == 0 && row->time[0] != 0 && i != 11) {
                func_001F48F0(0, 0x194, i, 0, 0);
                *sound = 1;
            }
        } else {
            dst->x = src->x;
            dst->y = src->y - height;
            dst->z = src->z;
        }
        if (control[0] == 0) {
            if (row->anim[0] != 0) {
                row->time[0] += 4;
                if (row->time[0] >= 256) {
                    row->time[0] = 0;
                    control[i + 3] = 1;
                    row->anim[0] = 0;
                    state->active = 0;
                }
            }
        } else if (i == 16) {
            if (row->anim[0] == 2) {
                row->time[0] += 4;
                if (row->time[0] >= 256) {
                    row->time[0] = 0;
                    control[i + 3] = 1;
                    row->anim[0] = 0;
                    state->active = 0;
                }
            }
        } else if (row->anim[0] != 0) {
            row->time[0] += 4;
            if (row->time[0] >= 256) {
                row->time[0] = 0;
                control[i + 3] = 1;
                row->anim[0] = 0;
                state->active = 0;
            }
        }
    }
    if (state->all != 0) {
        state->enabled = 1;
    } else if (*(s16 *)(control + 0xC2) >= 10000) {
        state->enabled = 0;
    } else if (animating == 0 && state->shown != 0 && func_001F5240(-1, -1) == 0 && state->ready != 0 && state->hidden == 0) {
        if (control[0] == 0) {
            if (state->busy == 0) {
                switch (*(s16 *)(control + 0xC2)) {
                case 100:
                case 101:
                    state->enabled = 0;
                    break;
                default:
                    state->enabled = 1;
                    break;
                }
            } else {
                state->enabled = 0;
            }
        } else if (state->busy == 0) {
            switch (*(s16 *)(control + 0xC2)) {
            case 104:
            case 105:
            case 111:
                state->enabled = 0;
                break;
            default:
                state->enabled = 1;
                break;
            }
        } else {
            state->enabled = 0;
        }
    } else {
        if (*(s16 *)(control + 0xC2) != 0) {
            goto disabled;
        }
        if (state->shown == 0 || func_001F5240(-1, -1) != 0 || state->ready == 0 || state->hidden != 0) {
            goto disabled;
        }
        state->enabled = 1;
        goto control_updated;
disabled:
        state->enabled = 0;
    }
control_updated:
    packet = func_001EE4B0(packet, D_00298BB0 + 0x22, positions, 0, 0, 0, 0);
    packet = func_001EE4B0(packet, D_00298BB2 + 0x22, positions, 0, 0, 0, 0);
    if (state->all != 0) {
        s32 first = 1;
        Vector_0022A710 *firstPos = &positions[1];
        Item_0022A710 *firstSrc = &D_00298BD4;
        while (1) {
            packet = func_001EE4B0(packet, firstSrc->draw0 + 0x22, firstPos, 0, 0, 0, 0);
            packet = func_001EE4B0(packet, firstSrc->draw1 + 0x22, firstPos, 0, 0, 0, 0);
            first++;
            firstPos++;
            firstSrc++;
            if (first <= 10) {
                continue;
            }
            break;
        }
        {
        Vector_0022A710 *secondPos;
        Item_0022A710 *secondSrc;
        s32 second;
        second = 12;
        secondPos = &positions[12];
        secondSrc = &D_00298E10;
        while (1) {
            packet = func_001EE4B0(packet, secondSrc->draw0 + 0x22, secondPos, 0, 0, 0, 0);
            packet = func_001EE4B0(packet, secondSrc->draw1 + 0x22, secondPos, 0, 0, 0, 0);
            second++;
            secondPos++;
            secondSrc++;
            if (second <= 21) {
                continue;
            }
            break;
        }
        }
    } else if (control[0] == 0) {
        Vector_0022A710 *firstPos;
        Item_0022A710 *firstSrc;
        s32 first;
        first = 1;
        firstPos = &positions[1];
        firstSrc = &D_00298BD4;
        while (1) {
            packet = func_001EE4B0(packet, firstSrc->draw0 + 0x22, firstPos, 0, 0, 0, 0);
            packet = func_001EE4B0(packet, firstSrc->draw1 + 0x22, firstPos, 0, 0, 0, 0);
            first++;
            firstPos++;
            firstSrc++;
            if (first <= 10) {
                continue;
            }
            break;
        }
    } else if (control[0] == 1) {
        Vector_0022A710 *secondPos;
        Item_0022A710 *secondSrc;
        s32 second;
        second = 12;
        secondPos = &positions[12];
        secondSrc = &D_00298E10;
        while (1) {
            packet = func_001EE4B0(packet, secondSrc->draw0 + 0x22, secondPos, 0, 0, 0, 0);
            packet = func_001EE4B0(packet, secondSrc->draw1 + 0x22, secondPos, 0, 0, 0, 0);
            second++;
            secondPos++;
            secondSrc++;
            if (second <= 21) {
                continue;
            }
            break;
        }
    }
    packet = func_0022C570(packet);
    switch (state->mode) {
    case 0:
        choice = 15;
        side = 0;
        kind = 27;
        break;
    case 1:
        side = 0;
        choice = 0;
        kind = 27;
        break;
    case 2:
        choice = 4;
        side = 1;
        kind = 30;
        break;
    case 3:
        side = 1;
        choice = 5;
        kind = 30;
        break;
    case 4:
        side = 1;
        choice = 11;
        kind = 27;
        break;
    }
    if (kind == 27) {
        state->kind = 0;
    } else {
        state->kind = 1;
    }
    packet = func_0022CC40(packet, side, choice, kind);
    packet = func_001EE4B0(packet, 0x29, 0, 0, 0, 0, 0);
    packet = func_001EE4B0(packet, 0x28, 0, 0, 0, 0, 0);
    func_0022B060(packet);
}

INCLUDE_ASM("asm/nonmatchings/main_064", func_0022B060);

s32 func_0022C3C0(s32 arg0) {
    switch (arg0) {
    case 0:
        *(s16 *)0x01ED547C -= 4;
        if (*(s16 *)0x01ED547C <= 0) {
            *(s16 *)0x01ED547C = 0;
            return 1;
        }
        break;
    case 1:
        *(s16 *)0x01ED547C += 4;
        if (*(s16 *)0x01ED547C >= 0x80) {
            *(s16 *)0x01ED547C = 0x80;
            return 1;
        }
        break;
    }
    return 0;
}

typedef struct PointList_0022C450 {
    s16 coordinates[32];
    s16 count;
    s16 mode;
    u8 padding[8];
} PointList_0022C450;

void func_0022C450(void) {
    f32 positions[64][2];
    f32 weights[64];
    s32 item;
    s32 bank;
    PointList_0022C450 *list;
    u8 *output;
    PointList_0022C450 *bankLists;
    u8 *bankOutput;
    s32 count;
    s32 point;
    s16 *source;
    f32 *position;
    f32 *weight;

    bankLists = (PointList_0022C450 *)D_00299020;
    bank = 0;
    bankOutput = (u8 *)0x1ED0000;
    do {
        item = 0;
        list = bankLists;
        output = bankOutput;
        do {
            count = list->count;
            point = 0;
            if (point < count) {
                position = &positions[0][0];
                weight = weights;
                source = list->coordinates;
                do {
                    position[0] = (f32)source[0];
                    position[1] = (f32)source[1];
                    *weight = 1.0f;
                    source += 2;
                    position += 2;
                    weight++;
                    point++;
                } while (point < count);
            }
            func_0021BC10((f32 *)(output + 0x22C), (f32 *)(output + 0x32C), (s16 *)(output + 0x42C),
                          &positions[0][0], weights, count, list->mode, 4.0f);
            item++;
            list++;
            output += 0x204;
        } while (item < 16);
        bank++;
        bankLists += 16;
        bankOutput += 0x2040;
    } while (bank < 2);
}

INCLUDE_ASM("asm/nonmatchings/main_064", func_0022C570);

s32 func_0022CC40(s32 arg0, s16 arg1, s16 arg2, s16 arg3) {
    extern s32 func_001A22C0(f32);
    extern s16 D_00299066[][16][38];
    f32 (*xData)[16][129] = (f32 (*)[16][129])0x01ED022C;
    f32 (*zData)[16][129] = (f32 (*)[16][129])0x01ED032C;
    s16 (*countData)[16][258] = (s16 (*)[16][258])0x01ED042C;
    s32 rotation[3];
    f32 dx1;
    f32 dz1;
    f32 dx0;
    f32 dz0;
    s16 point;
    f32 *x;
    f32 *z;
    s32 angle;

    point = *(s16 *)0x01ED01B0;
    dx1 = xData[arg1][arg2][point + 2] - xData[arg1][arg2][point + 1];
    dz1 = zData[arg1][arg2][point + 2] - zData[arg1][arg2][point + 1];
    func_001A6C18(dx1, dz1);
    dx0 = xData[arg1][arg2][point + 1] - xData[arg1][arg2][point];
    dz0 = zData[arg1][arg2][point + 1] - zData[arg1][arg2][point];
    x = &xData[arg1][arg2][point];
    z = &zData[arg1][arg2][point];
    angle = func_001A22C0(65536.0f * (func_001A6C18(dx0, dz0) / 6.2831855f)) % 65536;
    *(f32 *)0x01ED01B8 = *x + dx0 * (f32)*(s16 *)0x01ED01A6 / 1024.0f;
    *(f32 *)0x01ED01BC = D_00298BA4;
    *(f32 *)0x01ED01C0 = *z + dz0 * (f32)*(s16 *)0x01ED01A6 / 1024.0f;
    if (countData[arg1][arg2][0] <= point) {
        s32 previousAngle = func_001A22C0(65536.0f * (func_001A6C18(
            *x - xData[arg1][arg2][point - 1],
            *z - zData[arg1][arg2][point - 1]) / 6.2831855f)) % 65536;
        rotation[0] = 0;
        rotation[1] = previousAngle;
        rotation[2] = 0;
    } else if (countData[arg1][arg2][0] - 1 <= point) {
        rotation[0] = 0;
        rotation[1] = angle;
        rotation[2] = 0;
    } else {
        s16 progress = *(s16 *)0x01ED01A6;
        rotation[0] = 0;
        rotation[1] = func_001A22C0(65536.0f * (func_001A6C18(
            dx0 * (f32)(1024 - progress) / 1024.0f
                + dx1 * (f32)progress / 1024.0f,
            dz0 * (f32)(1024 - progress) / 1024.0f
                + dz1 * (f32)progress / 1024.0f) / 6.2831855f)) % 65536;
        rotation[2] = 0;
    }
    *(s32 *)0x01ED01A8 = rotation[1];
    if (*(s8 *)0x01ED01B4 != 0) {
        arg0 = func_001EE4B0(arg0, arg3 + 0x22, 0x01ED01B8, (s32)rotation, 0, 0, 0);
    }
    if (*(s16 *)0x01ED01A4 > 0) {
        if (*(s16 *)0x01ED01A6 < 1024 && *(s16 *)0x01ED01B0 < countData[arg1][arg2][0]) {
            if (*(s16 *)0x01ED01A4 == 1) {
                func_001F48F0(0, 0x193, 0, 0, 0);
                *(s16 *)0x01ED01A4 = 2;
            }
            if (*(s16 *)0x01ED01A4 == 2) {
                *(s16 *)0x01ED01A6 += 256;
                if (*(s16 *)0x01ED01A6 >= 1024) {
                    *(s16 *)0x01ED01B0 += 1;
                    if (countData[arg1][arg2][0] <= *(s16 *)0x01ED01B0) {
                        *(s16 *)0x01ED01A6 = 0;
                        *(s16 *)0x01ED01A4 = 3;
                        *(s16 *)0x01ED01B0 = countData[arg1][arg2][0];
                        ((s16 *)0x01ED52EC)[D_00299066[arg1][arg2][0]] = 1;
                    } else {
                        *(s16 *)0x01ED01A6 = 0;
                    }
                }
            }
        }
    }
    return arg0;
}
