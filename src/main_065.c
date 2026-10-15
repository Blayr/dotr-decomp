#include "common.h"

typedef struct State_0022F1C0 {
    u16 halves[18];
    s16 field_24;
} State_0022F1C0;

extern State_0022F1C0 D_0029ABC0;

s32 Taku_Camp_BOTAN_MATI(s32 arg0, s32 arg1, s16 arg2, s16 arg3) {
    extern s32 Taku_Obj_Set(s32, void *, s16, s16);
    s8 *slide = &D_00299E10;
    State_0022F1C0 local;
    s32 flag;
    s32 step;

    local = D_0029ABC0;
    flag = 1;
    switch (*(s8 *)0x01ED537E) {
    case 0:
        arg2 = 0x1CC;
        arg3 = 0x68;
        break;
    case 1:
        arg2 = 0x258;
        arg3 = 0x198;
        break;
    case 2:
        arg2 = 0x258;
        arg3 = 0x198;
        break;
    case 3:
        arg2 = 0x1CC;
        arg3 = 0x68;
        break;
    }
    step = *(u8 *)0x01ED53B2 % 15;
    if (step < 5) {
        local.field_24 = 0x98;
    } else if (step < 10) {
        local.field_24 = 0x99;
    } else if (step < 15) {
        local.field_24 = 0x9A;
    }
    if (slide[0] == 0 && *(s16 *)(slide + 0xC2) == 0x64) {
        flag = 0;
    }
    if (slide[0] == 1 && *(s16 *)(slide + 0xC2) == 0x69) {
        flag = 0;
    }
    if (slide[0] == 1 && *(s16 *)(slide + 0xC2) == 0x6A) {
        flag = 0;
    }
    if ((*(s8 *)0x01ED537B == 4 || *(s8 *)0x01ED53AC == 2) && flag != 0) {
        arg0 = Taku_Obj_Set(arg0, &local, arg2, arg3);
        *(u8 *)0x01ED53B2 += 1;
    }
    return arg0;
}
