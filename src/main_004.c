#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_004", func_0010C940);

INCLUDE_ASM("asm/nonmatchings/main_004", func_0010CE20);

INCLUDE_ASM("asm/nonmatchings/main_004", func_0010D080);

INCLUDE_ASM("asm/nonmatchings/main_004", func_0010D490);

void func_0010D820(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28) {
    func_0027DE20(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
                  arg_sp0, arg_sp8, arg_sp10, arg_sp18, arg_sp20,
                  0, 0x960, arg_sp28);
}

INCLUDE_ASM("asm/nonmatchings/main_004", func_0010D880);

void func_0010DB00(void *arg0, s32 arg1, s32 arg2) {
    s32 i;
    s32 position;
    s32 occupant;
    s32 count;
    s32 mode;
    u16 *record = arg0;

    if (func_001DF540((s32) record[0] >> 8, record[0] & 0xFF) != 0) {
        func_0024DE70((s32) record[0] >> 8, record[0] & 0xFF);
        func_001E1090((s32) record[0] >> 8, record[0] & 0xFF);
        func_001DF540((s32) record[0] >> 8, record[0] & 0xFF);
        if ((arg2 & 0xFF) == 1) {
            mode = 3;
        } else {
            mode = 6;
        }
        record[2] = (mode << 8) | 0xFF;
        if ((arg1 & 0xFF) == 1) {
            count = 6;
        } else {
            count = 4;
        }
        for (i = 0; i < count; i++) {
            position = (u16) func_0010F850(arg1, i & 0xFF);
            occupant = func_001E3790(position & 0xFF, position >> 8);
            if (occupant == record[0] || occupant < 0) {
                *(u32 *) (record + 4) = (position << 16) | record[4];
                return;
            }
        }
    }
}

typedef struct {
    u16 coordinate;
    u16 pad2;
    u16 status;
    u16 pad6;
    u32 value;
} State_0010DC40;

s32 func_0027C770(s32, s32, s32, s32, s32, s32);

void func_0010DC40(void *arg0) {
    State_0010DC40 *state = arg0;
    s32 coordinate;
    s32 result;
    u32 *record;

    if (func_001DF540((s32) state->coordinate >> 8, state->coordinate & 0xFF) != 0) {
        record = func_00250740((s32) state->coordinate >> 8, state->coordinate & 0xFF, 0);
        if (record != NULL) {
            switch (*record >> 8) {
        case 13:
            state->status = 0x5FF;
            return;
        case 2:
            coordinate = func_001E1090((s32) state->coordinate >> 8, state->coordinate & 0xFF) & 0xFFFF;
            result = func_0027C770(func_001DF540((s32) state->coordinate >> 8, state->coordinate & 0xFF), coordinate & 0xFF, coordinate >> 8, 0, 6, 2) & 0xFFFF;
            state->status = 0x6FF;
            if (result < 0) {
                state->value = ((coordinate & 0xFFFF) << 16) | *(u16 *) &state->value;
                return;
            }
            state->value = ((result & 0xFFFF) << 16) | *(u16 *) &state->value;
            break;
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/main_004", func_0010DD50);

INCLUDE_ASM("asm/nonmatchings/main_004", func_0010DFC0);

INCLUDE_ASM("asm/nonmatchings/main_004", func_0010E320);

s32 func_0010E540(s32 arg0, void *arg1, s32 arg2, s32 arg3) {
    s32 count;
    s32 *p;
    s32 i;
    s32 values[8];
    s32 j;
    s32 value;
    u8 *slot;
    u8 *out = (u8 *)arg1;

    if (arg2 == 0) return -1;
    j = 0;
    do {
        out[j + 6] = 255;
        j++;
    } while (j < 5);
    func_0026FD30(arg0, values);
    if (!(arg3 & 255)) {
        func_0010F290(arg0, arg1, arg2, 0);
        count = 2;
        if (func_0023C160() > 3) {
            i = 0;
            if (i < func_0026FE20(arg0)) {
                p = values;
                do {
                    if (i != out[6] && i != out[7] && func_00248F60(427, *p) >= 0 && (func_0026FCE0(*p) >> 5) == 2) {
                        value = *p;
                        if (value != 795 && value != 796) {
                            slot = out + count;
                            count++;
                            slot[6] = i;
                        }
                    }
                    p++;
                    i++;
                } while (i < func_0026FE20(arg0));
            }
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_004", func_0010E6B0);

INCLUDE_ASM("asm/nonmatchings/main_004", func_0010E890);

void func_0010ED90(void) {
    func_0024E410();
}

s32 func_0010EDA0(s32 arg0) {
    if (func_001DF470() > 0x5DC) {
        if (func_001E0150(arg0) >= 4) {
            return 0;
        }
        return 0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_004", func_0010EE00);

INCLUDE_ASM("asm/nonmatchings/main_004", func_0010F030);

s32 func_0010F220(s32 arg0) {
    if ((func_0026FCE0(arg0) >> 5) != 0) {
        return 0;
    }
    if (func_00248F60(arg0, 0x31E) >= 0) {
        return 1;
    }
    if (arg0 == 0x18E) {
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_004", func_0010F290);

INCLUDE_ASM("asm/nonmatchings/main_004", func_0010F450);

s32 func_0010F6F0(s32 arg0) {
    s32 temp_s2;
    s32 temp_s2_2;
    s32 var_s3;
    s32 temp_s3;
    s32 temp_s4;
    u16 temp_v0;
    s32 temp_v0_2;
    u16 temp_v0_3;
    s32 temp_v0_4;
    s32 var_s0;
    s32 var_s4;

    var_s0 = 0;
    if ((arg0 & 0xFF) == 1) {
        var_s3 = 0;
        do {
            temp_v0 = func_0010F850(arg0, var_s3 & 0xFF);
            temp_v0_2 = func_001E3790(temp_v0 & 0xFF, temp_v0 >> 8);
            if (temp_v0_2 >= 0) {
                temp_s4 = temp_v0_2 & 0xFF;
                temp_s2 = func_00250360(temp_v0_2 >> 8, temp_s4);
                if ((temp_s2 == func_001DE540()) && (temp_s4 != 0)) {
                    var_s0 += 1;
                }
            }
            var_s3 += 1;
        } while (var_s3 < 6);
        if (var_s0 >= 2) {
            return 1;
        } else {
            return 0;
        }
    }
    var_s4 = 0;
    do {
        temp_v0_3 = func_0010F850(arg0, var_s4 & 0xFF);
        temp_v0_4 = func_001E3790(temp_v0_3 & 0xFF, temp_v0_3 >> 8);
        if (temp_v0_4 >= 0) {
            temp_s3 = temp_v0_4 & 0xFF;
            temp_s2_2 = func_00250360(temp_v0_4 >> 8, temp_s3);
            if ((temp_s2_2 == func_001DE540()) && (temp_s3 != 0)) {
                var_s0 += 1;
            }
        }
        var_s4 += 1;
    } while (var_s4 < 4);
    if (var_s0 > 0) {
        return 1;
    } else {
        return 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_004", func_0010F850);

INCLUDE_ASM("asm/nonmatchings/main_004", func_0010F940);

INCLUDE_ASM("asm/nonmatchings/main_004", func_0010FA60);

INCLUDE_ASM("asm/nonmatchings/main_004", func_0010FFF0);

INCLUDE_ASM("asm/nonmatchings/main_004", func_001106F0);

INCLUDE_ASM("asm/nonmatchings/main_004", func_00110F00);

INCLUDE_ASM("asm/nonmatchings/main_004", func_001110D0);

INCLUDE_ASM("asm/nonmatchings/main_004", func_00111320);

INCLUDE_ASM("asm/nonmatchings/main_004", func_001123C0);

INCLUDE_ASM("asm/nonmatchings/main_004", func_00112600);

INCLUDE_ASM("asm/nonmatchings/main_004", func_00112850);

s32 func_00112960(s32 arg0) {
    s32 result;

    result = (u32) (arg0 - 0x36) < 4U ? 1 : 0;
    return result;
}

INCLUDE_ASM("asm/nonmatchings/main_004", func_00112980);

INCLUDE_ASM("asm/nonmatchings/main_004", func_00112A40);

INCLUDE_ASM("asm/nonmatchings/main_004", func_00112B90);

INCLUDE_ASM("asm/nonmatchings/main_004", func_00113140);

INCLUDE_ASM("asm/nonmatchings/main_004", func_00113370);

INCLUDE_ASM("asm/nonmatchings/main_004", func_00113760);

void func_00113A00(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28) {
    func_0027DE20(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
                  arg_sp0, arg_sp8, arg_sp10, arg_sp18, arg_sp20,
                  0, 3000, arg_sp28);
}

typedef struct {
    u16 position;
    u8 pad2[2];
    u16 state;
    u8 pad6[2];
    union {
        u16 low;
        u32 value;
    } flags;
} Data_00113A60;

void func_00113A60(void *arg0) {
    Data_00113A60 *data = arg0;
    s32 pair;
    s32 low;

    func_00250360(data->position >> 8, data->position & 0xFF);
    pair = func_001E1090(data->position >> 8, data->position & 0xFF);
    if (func_0024DF00(3, data->position >> 8, data->position & 0xFF) == 1) {
        data->state = 0x6FF;
        data->flags.value = data->flags.low | (func_00113B60(pair & 0xFF, pair >> 8) << 16);
    } else {
        low = pair & 0xFF;
        data->state = 0x6FF;
        if (low < 3 && (pair >> 8) < 3) {
            data->flags.value = data->flags.low | 0x03030000;
        } else if (low >= (pair >> 8)) {
            data->flags.value = data->flags.low | 0x03050000;
        } else {
            data->flags.value = data->flags.low | 0x05030000;
        }
    }
}

s32 func_00113B60(s32 arg0, s32 arg1) {
    s32 result;

    if (arg1 >= 5) {
        result = 0x602;
    } else if (arg0 >= 5) {
        result = 0x206;
    } else if (arg0 >= arg1) {
        result = 0x105;
    } else {
        result = 0x501;
    }
    return result;
}

INCLUDE_ASM("asm/nonmatchings/main_004", func_00113BB0);

INCLUDE_ASM("asm/nonmatchings/main_004", func_00113ED0);

INCLUDE_ASM("asm/nonmatchings/main_004", func_00114080);

INCLUDE_ASM("asm/nonmatchings/main_004", func_00114310);

s32 func_001146C0(s32 arg0, void *arg1, void *arg2, s32 arg3) {
    s32 entries[8];
    s32 i;

    func_0026FD30(arg0, entries);
    for (i = 0; i < func_0026FE20(arg0); i++) {
        if ((arg3 & 0xFFFF) == entries[i] && func_0026FB10(arg0, entries[i]) == 1) {
            *((s8 *)arg1 + 6) = i;
            func_001DCD70(arg2, entries[i]);
            return func_0026FCE0(entries[i]) >> 5;
        }
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/main_004", func_001147B0);

INCLUDE_ASM("asm/nonmatchings/main_004", func_00114B40);
