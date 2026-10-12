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

INCLUDE_ASM("asm/nonmatchings/main_064", func_002294B0);

INCLUDE_ASM("asm/nonmatchings/main_064", func_002297C0);

INCLUDE_ASM("asm/nonmatchings/main_064", func_0022A020);

extern s16 D_00299ED2;
void func_001DA2B0(void *, s32, f32, f32);

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

INCLUDE_ASM("asm/nonmatchings/main_064", func_0022A710);

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

INCLUDE_ASM("asm/nonmatchings/main_064", func_0022C450);

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
