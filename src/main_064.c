#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_064", func_00228150);

INCLUDE_ASM("asm/nonmatchings/main_064", func_00228460);

INCLUDE_ASM("asm/nonmatchings/main_064", func_00228660);

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

INCLUDE_ASM("asm/nonmatchings/main_064", func_00229140);

INCLUDE_ASM("asm/nonmatchings/main_064", func_002294B0);

INCLUDE_ASM("asm/nonmatchings/main_064", func_002297C0);

INCLUDE_ASM("asm/nonmatchings/main_064", func_0022A020);

INCLUDE_ASM("asm/nonmatchings/main_064", func_0022A140);

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

INCLUDE_ASM("asm/nonmatchings/main_064", func_0022CC40);
