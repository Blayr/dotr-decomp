#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_060", func_00214FD0);

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

INCLUDE_ASM("asm/nonmatchings/main_060", func_00215920);

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

INCLUDE_ASM("asm/nonmatchings/main_060", func_002170A0);

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
