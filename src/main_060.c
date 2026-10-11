#include "common.h"

typedef struct {
    u32 value0 : 31;
    u8 flag : 1;
    u32 value4 : 30;
    u8 flags : 2;
} Flags_00214FD0;

s32 func_00214FD0(void *arg0) {
    Flags_00214FD0 *flags = arg0;

    if (arg0 == NULL) {
        return 0;
    }
    flags->value0 = 0;
    flags->value4 = 0;
    flags->flags = 3;
    flags->flag = 0;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_060", func_00215060);

INCLUDE_ASM("asm/nonmatchings/main_060", func_002151D0);

INCLUDE_ASM("asm/nonmatchings/main_060", func_00215280);

INCLUDE_ASM("asm/nonmatchings/main_060", func_002153D0);

INCLUDE_ASM("asm/nonmatchings/main_060", func_002154E0);

INCLUDE_ASM("asm/nonmatchings/main_060", func_00215770);

typedef struct {
    u8 pad[0xFF9C];
    u8 flags;
    u8 tail[3];
} State_002158B0;

extern State_002158B0 D_0032F790[];
extern u8 D_0034F6D0;

s32 func_002158B0(s32 arg0) {
    s32 var_v1;
    State_002158B0 *state;

    if (D_0034F6D0 == arg0) {
        var_v1 = 0;
    } else {
        var_v1 = 1;
    }
    state = &D_0032F790[var_v1];
    if ((arg0 < 0) || (arg0 >= 2)) {
        return -1;
    }
    return state->flags & 3;
}

extern u8 D_0034F6D0;

typedef struct {
    u8 padding[0xFF9C];
    u8 mode : 2;
    u8 : 6;
} Flags_00215920;

s32 func_00215920(s32 arg0, s32 arg1) {
    s32 var_v1;
    u8 *temp_a2;

    if (D_0034F6D0 == arg0) {
        var_v1 = 0;
    } else {
        var_v1 = 1;
    }
    temp_a2 = (u8 *)D_0032F790 + (var_v1 * 0xFFA0);
    if ((arg0 < 0) || (arg0 >= 2)) {
        return 0;
    }
    if ((arg1 < 0) || (arg1 >= 3)) {
        return 0;
    }
    ((Flags_00215920 *)temp_a2)->mode = arg1;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_060", func_002159D0);

INCLUDE_ASM("asm/nonmatchings/main_060", func_00215A60);

INCLUDE_ASM("asm/nonmatchings/main_060", func_00215B10);

INCLUDE_ASM("asm/nonmatchings/main_060", func_00215C40);

INCLUDE_ASM("asm/nonmatchings/main_060", func_00215D30);

INCLUDE_ASM("asm/nonmatchings/main_060", func_00215DE0);

INCLUDE_ASM("asm/nonmatchings/main_060", func_00215F00);

INCLUDE_ASM("asm/nonmatchings/main_060", func_00215F90);

INCLUDE_ASM("asm/nonmatchings/main_060", func_00216040);

INCLUDE_ASM("asm/nonmatchings/main_060", func_00216280);

INCLUDE_ASM("asm/nonmatchings/main_060", func_00216490);

INCLUDE_ASM("asm/nonmatchings/main_060", func_00216580);

INCLUDE_ASM("asm/nonmatchings/main_060", func_002166D0);

INCLUDE_ASM("asm/nonmatchings/main_060", func_00216800);

INCLUDE_ASM("asm/nonmatchings/main_060", func_00216920);

INCLUDE_ASM("asm/nonmatchings/main_060", func_002169F0);

INCLUDE_ASM("asm/nonmatchings/main_060", func_00216AC0);

INCLUDE_ASM("asm/nonmatchings/main_060", func_00216BC0);

INCLUDE_ASM("asm/nonmatchings/main_060", func_00216C70);

INCLUDE_ASM("asm/nonmatchings/main_060", func_00216D30);

INCLUDE_ASM("asm/nonmatchings/main_060", func_00216DF0);

INCLUDE_ASM("asm/nonmatchings/main_060", func_00216EC0);

INCLUDE_ASM("asm/nonmatchings/main_060", func_00216F80);

typedef struct Entry_002170A0 {
    u8 id;
    u8 x : 4;
    u8 y : 4;
    u16 value;
} Entry_002170A0;

extern Entry_002170A0 D_002D08D0[];
extern u16 D_002D08D2[];

u16 func_002170A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 i;
    Entry_002170A0 *entry;
    s32 dx;
    s32 dy;

    if (arg3 <= 0) {
        return 999;
    }
    if (arg0 < 0 || arg0 >= 22) {
        return 999;
    }
    if (arg1 < 0 || arg1 >= 7 || arg2 < 0 || arg2 >= 7) {
        return 999;
    }

    entry = D_002D08D0;
    i = 0;
    do {
        if (arg0 == entry->id) {
            dx = entry->x - arg1;
            dx = dx >= 0 ? dx : -dx;
            if (dx < arg3) {
                dy = entry->y - arg2;
                dy = dy >= 0 ? dy : -dy;
                if (dy < arg3) {
                    return D_002D08D2[i * 2];
                }
            }
        }
        i++;
        entry++;
    } while (i < 22);

    return 999;
}

INCLUDE_ASM("asm/nonmatchings/main_060", func_002171B0);

INCLUDE_ASM("asm/nonmatchings/main_060", func_00217230);

INCLUDE_ASM("asm/nonmatchings/main_060", func_002172D0);

s32 func_002173D0(void) {
    func_00193808();
    return 1;
}

s32 func_002173F0(void) {
    return 1;
}

s32 func_00217400(void) {
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_060", func_00217410);

INCLUDE_ASM("asm/nonmatchings/main_060", func_002174D0);

typedef struct {
    s8 active : 1;
} Flags_00217530;

extern Flags_00217530 D_0034F6E8;

s32 func_00217530(void) {
    return D_0034F6E8.active != 0 ? 1 : 0;
}

INCLUDE_ASM("asm/nonmatchings/main_060", func_00217550);

INCLUDE_ASM("asm/nonmatchings/main_060", func_00217590);

INCLUDE_ASM("asm/nonmatchings/main_060", func_002176B0);

INCLUDE_ASM("asm/nonmatchings/main_060", func_00217710);

INCLUDE_ASM("asm/nonmatchings/main_060", func_002177E0);

INCLUDE_ASM("asm/nonmatchings/main_060", func_002178C0);

INCLUDE_ASM("asm/nonmatchings/main_060", func_00217980);

INCLUDE_ASM("asm/nonmatchings/main_060", func_002179C0);
