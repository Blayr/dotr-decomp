#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_007", func_00124610);

INCLUDE_ASM("asm/nonmatchings/main_007", func_00124810);

INCLUDE_ASM("asm/nonmatchings/main_007", func_00124A30);

INCLUDE_ASM("asm/nonmatchings/main_007", func_00124C10);

void func_0026FD30(s32, s32 *);
void func_00123D70(s32, s32 *);

typedef struct {
    u8 pad0[6];
    u8 slot[5];
} Obj1_00124C90;

typedef struct {
    u8 pad0[0x3C];
    u16 id;
} Obj2_00124C90;

s32 func_00124C90(s32 arg0, void *arg1, void *arg2, s32 arg3) {
    Obj1_00124C90 *o1 = arg1;
    Obj2_00124C90 *o2 = arg2;
    s32 list[8];
    s32 i;
    u8 t;

    for (i = 0; i < 5; i++) {
        o1->slot[i] = 0xFF;
    }
    func_0026FD30(arg0, list);
    if (o2 == NULL) {
        return -1;
    }
    if ((arg3 & 0xFF) == 0) {
        for (i = 0; i < func_0026FE20(arg0); i++) {
            if (i != o1->slot[0] && i != o1->slot[1]) {
                if (o2->id == list[i] && func_0026FB10(arg0, list[i]) == 1) {
                    o1->slot[0] = i;
                }
            }
        }
        return 0;
    }
    func_00123D70(arg0, list);
    for (i = 0; i < func_0026FE20(arg0); i++) {
        t = func_0026FCE0(list[i]);
        if ((t >> 5) == 0 && (t & 0x1F) == 0 && func_0026FB10(arg0, list[i]) == 1) {
            o1->slot[0] = i;
        }
    }
    for (i = 0; i < func_0026FE20(arg0); i++) {
        t = func_0026FCE0(list[i]);
        if ((t >> 5) == 0 && (t & 0x1F) == 0x12 && func_0026FB10(arg0, list[i]) == 1) {
            o1->slot[1] = i;
        }
    }
    for (i = 0; i < func_0026FE20(arg0); i++) {
        t = func_0026FCE0(list[i]);
        if ((t >> 5) == 0 && (t & 0x1F) == 0xF && func_0026FB10(arg0, list[i]) == 1) {
            o1->slot[2] = i;
        }
    }
    return 0;
}

void func_00124F50(void) {
    func_0024E410();
}

INCLUDE_ASM("asm/nonmatchings/main_007", func_00124F60);

INCLUDE_ASM("asm/nonmatchings/main_007", func_001254A0);

INCLUDE_ASM("asm/nonmatchings/main_007", func_00125500);

INCLUDE_ASM("asm/nonmatchings/main_007", func_00125B70);

INCLUDE_ASM("asm/nonmatchings/main_007", func_00126380);

INCLUDE_ASM("asm/nonmatchings/main_007", func_00126840);

INCLUDE_ASM("asm/nonmatchings/main_007", func_00126940);

INCLUDE_ASM("asm/nonmatchings/main_007", func_001269C0);

INCLUDE_ASM("asm/nonmatchings/main_007", func_00126AB0);

INCLUDE_ASM("asm/nonmatchings/main_007", func_00126C80);

INCLUDE_ASM("asm/nonmatchings/main_007", func_001271F0);

INCLUDE_ASM("asm/nonmatchings/main_007", func_001273E0);

INCLUDE_ASM("asm/nonmatchings/main_007", func_001277C0);

INCLUDE_ASM("asm/nonmatchings/main_007", func_00127A30);

INCLUDE_ASM("asm/nonmatchings/main_007", func_00127A90);

INCLUDE_ASM("asm/nonmatchings/main_007", func_00127B00);

INCLUDE_ASM("asm/nonmatchings/main_007", func_00127D20);

INCLUDE_ASM("asm/nonmatchings/main_007", func_00127E30);

INCLUDE_ASM("asm/nonmatchings/main_007", func_001280C0);

INCLUDE_ASM("asm/nonmatchings/main_007", func_00128430);

INCLUDE_ASM("asm/nonmatchings/main_007", func_00128520);

INCLUDE_ASM("asm/nonmatchings/main_007", func_00128720);

INCLUDE_ASM("asm/nonmatchings/main_007", func_00128900);

s32 func_00128AE0(s32 arg0) {
    if ((func_0026FCE0(arg0) >> 5) != 0) {
        return 1;
    }
    if (arg0 == 0x6C || arg0 == 0x6F || arg0 == 0x68) {
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_007", func_00128B50);

INCLUDE_ASM("asm/nonmatchings/main_007", func_00128D40);

INCLUDE_ASM("asm/nonmatchings/main_007", func_001291C0);

INCLUDE_ASM("asm/nonmatchings/main_007", func_00129700);

INCLUDE_ASM("asm/nonmatchings/main_007", func_00129D00);

INCLUDE_ASM("asm/nonmatchings/main_007", func_0012A2E0);

INCLUDE_ASM("asm/nonmatchings/main_007", func_0012AAC0);

INCLUDE_ASM("asm/nonmatchings/main_007", func_0012B000);

INCLUDE_ASM("asm/nonmatchings/main_007", func_0012B1B0);

INCLUDE_ASM("asm/nonmatchings/main_007", func_0012B210);

INCLUDE_ASM("asm/nonmatchings/main_007", func_0012B730);

INCLUDE_ASM("asm/nonmatchings/main_007", func_0012B830);

INCLUDE_ASM("asm/nonmatchings/main_007", func_0012B8B0);

INCLUDE_ASM("asm/nonmatchings/main_007", func_0012B9A0);

INCLUDE_ASM("asm/nonmatchings/main_007", func_0012BB70);

INCLUDE_ASM("asm/nonmatchings/main_007", func_0012C1A0);

INCLUDE_ASM("asm/nonmatchings/main_007", func_0012C3F0);

INCLUDE_ASM("asm/nonmatchings/main_007", func_0012C7F0);

INCLUDE_ASM("asm/nonmatchings/main_007", func_0012CB80);

INCLUDE_ASM("asm/nonmatchings/main_007", func_0012CBE0);
