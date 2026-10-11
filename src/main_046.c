#include "common.h"

static inline u8 *lookup_001E19D0(void) {
    u8 *entry = func_001DD130();

    if (entry == NULL) {
        return NULL;
    }
    if (entry[0x45] >= 11) {
        return NULL;
    }
    return entry;
}

s32 func_001E19D0(s32 arg0, s32 arg1, s8 arg2) {
    u8 *entry = lookup_001E19D0();

    if (entry == NULL) {
        return 0;
    }
    entry[0x51] = arg2;
    return 1;
}

static inline u8 *get_entry_001E1A30(void) {
    u8 *entry;

    entry = func_001DD130();
    if (entry == NULL) {
        return NULL;
    }
    if (entry[0x45] >= 0xB) {
        return NULL;
    }
    return entry;
}

s32 func_001E1A30(void) {
    u8 *entry;

    entry = get_entry_001E1A30();
    if (entry != NULL) {
        return entry[0x50];
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/main_046", func_001E1A90);

INCLUDE_ASM("asm/nonmatchings/main_046", func_001E1AF0);

INCLUDE_ASM("asm/nonmatchings/main_046", func_001E1B70);

INCLUDE_ASM("asm/nonmatchings/main_046", func_001E1C10);

static inline void *get_entry_001E1CB0(void) {
    void *entry;

    entry = func_001DD130();
    if (entry == NULL) {
        return NULL;
    }
    if (*(u8 *)((u8 *)entry + 0x45) >= 0xB) {
        return NULL;
    }
    return entry;
}

s32 func_001E1CB0(void) {
    void *entry;

    entry = get_entry_001E1CB0();
    if (entry != NULL) {
        return *(u8 *)((u8 *)entry + 0x52);
    }
    return -1;
}

s32 func_001E1D10(void) {
    u8 *ptr;

    ptr = func_001DD130();
    if (ptr == NULL) {
        ptr = NULL;
    } else if ((s32) ptr[0x45] >= 0xB) {
        ptr = NULL;
    }
    if (ptr != NULL) {
        return ptr[0x53];
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/main_046", func_001E1D70);

INCLUDE_ASM("asm/nonmatchings/main_046", func_001E1E10);

INCLUDE_ASM("asm/nonmatchings/main_046", func_001E1E70);

INCLUDE_ASM("asm/nonmatchings/main_046", func_001E2100);

INCLUDE_ASM("asm/nonmatchings/main_046", func_001E2220);

INCLUDE_ASM("asm/nonmatchings/main_046", func_001E22B0);

void func_001E2340(void) {
    s32 x;
    s32 y;

    y = 0;
    do {
        x = 0;
        do {
            func_001E23A0(x, y, 0);
            x++;
        } while (x < 7);
        y++;
    } while (y < 7);
}

INCLUDE_ASM("asm/nonmatchings/main_046", func_001E23A0);

INCLUDE_ASM("asm/nonmatchings/main_046", func_001E2450);

INCLUDE_ASM("asm/nonmatchings/main_046", func_001E24E0);

INCLUDE_ASM("asm/nonmatchings/main_046", func_001E2570);

INCLUDE_ASM("asm/nonmatchings/main_046", func_001E27D0);

INCLUDE_ASM("asm/nonmatchings/main_046", func_001E2A60);

INCLUDE_ASM("asm/nonmatchings/main_046", func_001E2FB0);

INCLUDE_ASM("asm/nonmatchings/main_046", func_001E2FC0);

INCLUDE_ASM("asm/nonmatchings/main_046", func_001E3060);

INCLUDE_ASM("asm/nonmatchings/main_046", func_001E3070);

INCLUDE_ASM("asm/nonmatchings/main_046", func_001E3230);

INCLUDE_ASM("asm/nonmatchings/main_046", func_001E3650);

INCLUDE_ASM("asm/nonmatchings/main_046", func_001E36E0);

INCLUDE_ASM("asm/nonmatchings/main_046", func_001E3790);

INCLUDE_ASM("asm/nonmatchings/main_046", func_001E3850);

INCLUDE_ASM("asm/nonmatchings/main_046", func_001E3900);

INCLUDE_ASM("asm/nonmatchings/main_046", func_001E3990);

INCLUDE_ASM("asm/nonmatchings/main_046", func_001E3A20);

INCLUDE_ASM("asm/nonmatchings/main_046", func_001E3AB0);

INCLUDE_ASM("asm/nonmatchings/main_046", func_001E3B50);

INCLUDE_ASM("asm/nonmatchings/main_046", func_001E3BF0);

INCLUDE_ASM("asm/nonmatchings/main_046", func_001E3C90);

INCLUDE_ASM("asm/nonmatchings/main_046", func_001E3D30);

INCLUDE_ASM("asm/nonmatchings/main_046", func_001E3DD0);

INCLUDE_ASM("asm/nonmatchings/main_046", func_001E3E70);

INCLUDE_ASM("asm/nonmatchings/main_046", func_001E3F10);

INCLUDE_ASM("asm/nonmatchings/main_046", func_001E3FB0);

INCLUDE_ASM("asm/nonmatchings/main_046", func_001E3FE0);

INCLUDE_ASM("asm/nonmatchings/main_046", func_001E3FF0);

INCLUDE_ASM("asm/nonmatchings/main_046", func_001E40A0);

INCLUDE_ASM("asm/nonmatchings/main_046", func_001E42B0);

INCLUDE_ASM("asm/nonmatchings/main_046", func_001E42C0);

INCLUDE_ASM("asm/nonmatchings/main_046", func_001E4430);

INCLUDE_ASM("asm/nonmatchings/main_046", func_001E4530);

INCLUDE_ASM("asm/nonmatchings/main_046", func_001E4540);
