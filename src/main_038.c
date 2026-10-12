#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_038", func_001ADD00);

void func_001AE520(void) {
    u8 *data = D_00317490;
    s32 var_a1;
    s32 var_s0;

    var_a1 = 0;
    do {
        data[var_a1 + 0xCB2] = 0x18;
        var_a1 += 1;
    } while (var_a1 < 4);
    var_s0 = 1;
    do {
        func_001DFBB0(0, var_s0);
        func_001DFBB0(1, var_s0);
        var_s0 += 1;
    } while (var_s0 < 0xB);
}

s32 func_001AE5A0(s32 arg0) {
    if (func_001F3130(0) != 0) {
        return func_001AE5F0(arg0);
    }
    return arg0;
}

INCLUDE_ASM("asm/nonmatchings/main_038", func_001AE5F0);

void func_001AEE80(void) {
    func_00209D30(func_001AEEB0(func_00209D20()));
}

INCLUDE_ASM("asm/nonmatchings/main_038", func_001AEEB0);

s32 func_001AEFC0(s32 arg0) {
    return func_001AEFD0(arg0, 0);
}

INCLUDE_ASM("asm/nonmatchings/main_038", func_001AEFD0);

s32 func_001AF110(s32 arg0) {
    func_001FEAF0(0);
    return arg0;
}

typedef struct {
    u8 pad[0x6A0];
    s32 entries[8];
} Data_001AF140;

s32 func_001AF140(s32 arg0) {
    Data_001AF140 *data = (Data_001AF140 *)D_00317490;

    if ((arg0 < 0) || (arg0 >= 8)) {
        return 0;
    }
    return data->entries[arg0];
}

INCLUDE_ASM("asm/nonmatchings/main_038", func_001AF180);

INCLUDE_ASM("asm/nonmatchings/main_038", func_001AF5C0);

void func_001AF7B0(void) {
    func_00209D30(func_001AF7E0(func_00209D20()));
}

INCLUDE_ASM("asm/nonmatchings/main_038", func_001AF7E0);

INCLUDE_ASM("asm/nonmatchings/main_038", func_001B0CE0);

void func_001B1190(void) {
    func_00209D30(func_001B11C0(func_00209D20()));
}

INCLUDE_ASM("asm/nonmatchings/main_038", func_001B11C0);

INCLUDE_ASM("asm/nonmatchings/main_038", func_001B19F0);

INCLUDE_ASM("asm/nonmatchings/main_038", func_001B1EF0);

s32 func_001B20E0(s32 arg0, s32 arg1, s32 arg2) {
    extern s32 func_001B3C80();
    extern s32 func_001B65E0();
    extern s32 func_001B6C90();
    extern s32 func_001FEAB0();
    extern s32 func_001E08F0();
    extern s32 func_001DE4E0();
    extern s32 func_001FE7D0();
    u8 *global;
    s32 x;
    s32 xResult;
    s32 y;
    s32 yResult;
    s32 xCoord;
    s32 result;
    s32 temp;
    s32 flag;
    s32 areaX;
    s32 areaY;

    global = D_00317490;
    x = arg1 + 3;
    y = arg2 + 3;
    areaX = x + 0x6C0;
    areaY = y + 0x720;
    flag = 0;
    if (func_001DE4E0(D_003181CC) < 0x20) {
        if (func_001DE4E0(global[0xD3C] ^ 1) >= 0x64) {
            flag = 1;
        }
    }

    arg0 = func_001B4780(arg0, global[0xD54], -1, 6, arg1, arg2, 8, 3, (s64) 1);
    result = func_001B3C80(arg0, (s32) D_002909B8, areaX + 4, areaY + 3,
                           0, 1, 0, 0, 1, 0, -1);
    xCoord = x + 0x1E;
    yResult = y + 1;
    xResult = func_001B65E0(result, global[0xD54], xCoord, yResult, 3, 1, -1);
    if (flag != 0) {
        temp = func_0020F290(func_001FD680(xResult, 1, 0x1C, 0, 0x16));
        result = func_001FEAB0(1);
        *(s32 *)(result + 0xC) = 0x2C;
        result = func_001FE7D0(temp, 1, xCoord + 3, yResult + 2, 0, func_001FDFE0);
        func_001FEAF0(1);
    } else {
        temp = func_001E08F0(2, global[0xD4F] + 1, 0);
        result = func_001B6C90(xResult, xCoord + 3, yResult + 2, 2,
                             global[0xD4E] != 0 ? func_0026E950() : temp, 0);
    }
    return result;
}

INCLUDE_ASM("asm/nonmatchings/main_038", func_001B22F0);

typedef struct {
    s8 bit0 : 1;
    s8 bit1 : 1;
    s8 bit2 : 1;
    s8 bit3 : 1;
    s8 bit4 : 1;
    s8 bit5 : 1;
    s8 bit6 : 1;
    s8 bit7 : 1;
} Flags_001B3100;

typedef struct {
    u8 pad[0x44];
    u8 x;
    u8 y;
    u8 pad46[0x11];
    Flags_001B3100 flags;
} Card_001B3100;

typedef struct {
    u8 pad[0x33D];
    u8 x;
    u8 y;
    u8 pad33F[7];
    Flags_001B3100 flags;
    u8 pad347[0x381];
    Card_001B3100 *card;
    Card_001B3100 *other;
    u8 pad6D0[0x66C];
    u8 player;
    u8 padD3D[0x29];
    Flags_001B3100 state;
} State_001B3100;

typedef struct {
    u16 graphic : 10;
    u16 x : 3;
    u16 y : 3;
    u16 text;
} Entry_001B3100;

typedef struct {
    u8 pad[0xC];
    s32 width;
} Text_001B3100;

extern u8 D_00290080[];
extern Entry_001B3100 D_00291180[];
extern u8 D_003181E7;

s32 func_001B3100(s32 arg0, s32 arg1, s64 arg2, s64 arg3) {
    extern s32 func_001B3C80();
    extern s32 func_001B4780();
    extern void *func_001FEAB0();
    extern s32 func_001E24E0();
    extern s32 func_001FE660(s32, s32, s32, s32, f32, f32, s32, void (*)(void));
    State_001B3100 *state;
    State_001B3100 *player;
    s32 choice;
    s32 x;
    s32 y;
    s32 renderX;
    s32 count;
    s32 text;
    Entry_001B3100 *entry;
    s32 value;
    s32 otherValue;
    Text_001B3100 *info;
    s32 graphic;
    s32 entryX;
    s32 entryY;
    f32 scale;

    state = (State_001B3100 *)D_00317490;
    player = (State_001B3100 *)(D_00317490 + D_003181CC * 0x350);
    x = (s32)arg2 + 4;
    y = (s32)arg3 + 4;
    choice = -1;
    arg0 = func_001B4780(arg0, arg1, 2, 3, arg2, arg3, 9, 0x12, 1);
    switch (D_003181E7) {
    case 0x18:
        if (state->card != NULL) {
            value = func_00250360(state->card->x, state->card->y);
            if (state->player == value) {
                if (state->card->y == 0) {
                    value = func_001DE9C0(state->player);
                    otherValue = func_001DF110(state->player);
                    if (player->flags.bit0 && value + otherValue > 0) {
                        if (state->card->flags.bit0) {
                            choice = 3;
                        } else {
                            choice = 1;
                        }
                    } else if (otherValue != 0) {
                        if (state->card->flags.bit0) {
                            choice = 4;
                        } else {
                            choice = 2;
                        }
                    } else {
                        if (state->card->flags.bit0) {
                            choice = 11;
                        } else {
                            choice = 10;
                        }
                    }
                } else {
                    if (state->card->flags.bit0) {
                        choice = 11;
                    } else {
                        choice = 10;
                    }
                }
            } else {
                value = 0;
                if (state->card->y > 0) {
                    value = func_00267380((s32)state->card, state->player);
                }
                choice = value == 0 ? 11 : 0;
            }
        } else {
            choice = 0;
        }
        break;
    case 0x1D:
        if (state->card->y == 0) {
            choice = 5;
            if (state->other != NULL && state->other != state->card) {
                value = func_00250360(state->other->x, state->other->y);
                if (state->player == value) {
                    choice = 6;
                }
            }
        } else {
            if (state->other != NULL) {
                if (state->other == state->card) {
                    if (state->card->flags.bit4) {
                        choice = 13;
                    } else {
                        choice = 12;
                    }
                } else {
                    value = func_00250360(state->other->x, state->other->y);
                    if (state->player == value) {
                        choice = 14;
                    } else {
                        choice = 15;
                    }
                }
            } else {
                choice = 5;
            }
        }
        break;
    case 0x3E:
        if (func_001E24E0(player->x, player->y) == 0) {
            choice = 7;
        }
        break;
    case 0x43:
        choice = 8;
        break;
    case 0x53:
        choice = 17;
        break;
    case 0x46:
        choice = 9;
        break;
    case 0x29:
    case 0x25:
        choice = 18;
        break;
    case 0x2D:
        if (state->state.bit3) {
            choice = 16;
        } else {
            choice = 17;
        }
        break;
    case 0x30:
        if (func_001FA6F0(-1, -1) == NULL) {
            choice = 19;
        }
        break;
    case 0x63:
        choice = 20;
        break;
    }
    if (choice < 0) {
        return arg0;
    }
    renderX = x + 10;
    entry = D_00291180 + choice * 4;
    count = 0;
    do {
        graphic = entry->graphic;
        entryX = entry->x;
        entryY = entry->y;
        text = entry->text;
        if (graphic < 0x3FF) {
            arg0 = func_001B3C80(arg0, D_00290080 + graphic * 10,
                                  renderX + 0x6C0 + entryX, y + 0x720 + entryY,
                                  0, 1, 0, 0, 1, 0, -1);
        }
        if (text < 0xFFFF) {
            arg0 = func_0020F290(func_001FD680(arg0, 1, text, 0, 0x16));
            info = func_001FEAB0(1);
            if (info->width >= 0x2D) {
                scale = 44.0f / (f32)info->width;
            } else {
                scale = 1.0f;
            }
            arg0 = func_001FE660(arg0, 1, renderX + 0x1A, y, scale, 1.0f, 0,
                                  func_001FDFE0);
            func_001FEAF0(1);
        }
        count++;
        y += 0x16;
        entry++;
    } while (count < 4);
    return arg0;
}

INCLUDE_ASM("asm/nonmatchings/main_038", func_001B3640);

INCLUDE_ASM("asm/nonmatchings/main_038", func_001B3790);

void func_001B3CC0(s32, s32, s32, s32, s32, s32, s32, s32,
                   s64, s64, s64, s64, s64, s64);

void func_001B3C80(s32 arg0, s32 arg1, s32 arg2, s32 arg3,
                   s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                   s32 arg8, s32 arg9, s32 arg10) {
    func_001B3CC0(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
                  0, 0, (s64) arg8, (s64) arg9, (s64) arg10, 0x80);
}

INCLUDE_ASM("asm/nonmatchings/main_038", func_001B3CC0);

INCLUDE_ASM("asm/nonmatchings/main_038", func_001B4540);
