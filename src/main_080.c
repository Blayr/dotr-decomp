#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_080", func_0027F700);

INCLUDE_ASM("asm/nonmatchings/main_080", func_0027F830);

INCLUDE_ASM("asm/nonmatchings/main_080", func_0027F890);

INCLUDE_ASM("asm/nonmatchings/main_080", func_0027F8B4);

INCLUDE_ASM("asm/nonmatchings/main_080", func_0027F8D8);

INCLUDE_ASM("asm/nonmatchings/main_080", func_0027F8FC);

INCLUDE_ASM("asm/nonmatchings/main_080", func_0027FA30);

INCLUDE_ASM("asm/nonmatchings/main_080", func_0027FAB0);

INCLUDE_ASM("asm/nonmatchings/main_080", func_0027FC20);

INCLUDE_ASM("asm/nonmatchings/main_080", func_0027FFC0);

INCLUDE_ASM("asm/nonmatchings/main_080", func_00280060);

typedef struct {
    u8 state;
    u8 padding01[9];
    u8 enabled;
    u8 padding0B[0x2F];
} Flags_00280670;

typedef struct {
    u8 padding00[4];
    u8 intensity;
    u8 padding05[2];
    u8 mode;
    u8 field08;
    u8 field09;
    u8 field0A;
    u8 padding0B;
    u8 red;
    u8 green;
    u8 blue;
    u8 alpha;
    f32 width;
    f32 height;
    u8 padding18[8];
    f32 x;
    f32 y;
    u8 padding28[8];
} Object_00280670;

extern Object_00280670 D_00351180[];
extern Flags_00280670 D_00351240[];
extern u8 D_00351241;
extern u8 D_00351242;
extern s16 D_00351246;

#pragma optimization_level 0

void func_00280670(void) {
    extern s32 func_00101AD0();
    s32 i;

    for (i = 0; i < 3; i++) {
        D_00351240[i].enabled = 1;
    }
    D_00351240[0].state = 1;
    func_00217710(0, 0x1E);
    for (i = 0; i < 3; i++) {
        func_00101AD0(&D_00351180[i], 0x28, 0, 0xFF);
        D_00351180[i].intensity = 0x80;
        D_00351180[i].mode = 9;
        D_00351180[i].width = 40.0f;
        D_00351180[i].height = 0.0f;
        D_00351180[i].blue = D_00351180[i].green = D_00351180[i].red = D_00351180[i].alpha = 0xF0;
        D_00351180[i].field0A = 0x40;
        D_00351180[i].field09 = 0x10;
        D_00351180[i].field08 = 0x80;
        D_00351180[i].x = (f32) (i * 0x70 + 0x78E);
        D_00351180[i].y = 2249.0f;
    }
    D_00351242 = D_00351241;
    D_00351246 = 0;
}

#pragma optimization_level reset

INCLUDE_ASM("asm/nonmatchings/main_080", func_00280920);

INCLUDE_ASM("asm/nonmatchings/main_080", func_00280CB0);

INCLUDE_ASM("asm/nonmatchings/main_080", func_002817C0);

INCLUDE_ASM("asm/nonmatchings/main_080", func_002818A0);

INCLUDE_ASM("asm/nonmatchings/main_080", func_002825F0);

INCLUDE_ASM("asm/nonmatchings/main_080", func_002831A0);

INCLUDE_ASM("asm/nonmatchings/main_080", func_00283880);

INCLUDE_ASM("asm/nonmatchings/main_080", func_00284D30);

INCLUDE_ASM("asm/nonmatchings/main_080", func_00285880);

#pragma optimization_level 0

s32 func_00284D30(s32);                             /* extern */

void func_00285EE0(void) {
    func_00209D30(func_00284D30(func_00209D20()));
}

#pragma optimization_level reset

INCLUDE_ASM("asm/nonmatchings/main_080", func_00285F20);

void func_00286900(void) {

}

void func_00286910(void *arg0, void *arg1) {
    Callback_00286910 *current = arg0;
    Callback_00286910 *end = arg1;

    if (current < end) {
        do {
            (*current)();
            current++;
        } while (current < end);
    }
}
