/* The tutorial's scripted opponent: lessons 1 and 2. */

#include "common.h"

s32 func_00172510(s32);                     /* extern */
s32 func_0027F630(void *, s32, s32, s32, s32); /* extern */
s32 func_0027F890(s32, s32, s32);       /* extern */
s32 func_0027FA30(void *, s32);             /* extern */
s32 func_0027FAB0(void *);                      /* extern */
s32 func_0027FC20(s32, s32, void *);        /* extern */
#pragma global_optimizer off

/* Runs one frame of tutorial lesson 1: shows its messages step by step and waits for the moves it asks for.
   `event` is the duel event (kind in bits 8-15). */
s32 TaTuto_Lesson1(s32 event, u8 *tutorial) {
    extern void SzPad_SetAnalogInfo();
    s32 temp_a0;
    u16 temp_a0_2;
    u16 temp_a0_3;
    u16 temp_a0_4;
    u16 temp_a0_5;
    u16 temp_a0_6;
    u16 temp_a0_7;
    u16 temp_a0_8;
    u16 temp_v1;
    u16 temp_v1_10;
    u16 temp_v1_11;
    u16 temp_v1_12;
    u16 temp_v1_13;
    u16 temp_v1_14;
    u16 temp_v1_15;
    u16 temp_v1_16;
    u16 temp_v1_17;
    u16 temp_v1_18;
    u16 temp_v1_19;
    u16 temp_v1_20;
    u16 temp_v1_21;
    u16 temp_v1_22;
    u16 temp_v1_23;
    u16 temp_v1_24;
    u16 temp_v1_25;
    u16 temp_v1_26;
    u16 temp_v1_27;
    u16 temp_v1_28;
    u16 temp_v1_29;
    u16 temp_v1_2;
    u16 temp_v1_30;
    u16 temp_v1_31;
    u16 temp_v1_32;
    u16 temp_v1_33;
    u16 temp_v1_34;
    u16 temp_v1_35;
    u16 temp_v1_36;
    u16 temp_v1_37;
    u16 temp_v1_3;
    u16 temp_v1_4;
    u16 temp_v1_5;
    u16 temp_v1_6;
    u16 temp_v1_7;
    u16 temp_v1_8;
    u16 temp_v1_9;

    if (SzDuel_GetWindowDisp() != 0) {
        SzDuel_SetWindowDraw(1);
    } else {
        SzDuel_SetWindowDraw(0);
    }
    SzPad_SetAnalogInfo(0, 0, 0x80);
    SzPad_SetAnalogInfo(0, 1, 0x80);
    SzPad_SetAnalogInfo(0, 2, 0x80);
    SzPad_SetAnalogInfo(0, 3, 0x80);
    if (SzPad_Check(0, 0, 0x800) != 0) {
        return -2;
    }
    temp_a0 = (*(u16 *)((u8 *)(tutorial) + 0x1A2));
    switch (temp_a0) {                              /* switch 1 */
    case 0x0:                                       /* switch 1 */
        (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = 2U;
        goto block_296;
    case 0x1:                                       /* switch 1 */
        if (SzEffect_IsModelStandby2(0) != 0) {
            if (SzEffect_IsModelStandby2(0x100) != 0) {
                (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) ((*(u16 *)((u8 *)(tutorial) + 0x1A2)) + 1);
            }
        }
        /* Duplicate return node #297. Try simplifying control flow for better match */
        goto block_296;
    case 0x2:                                       /* switch 1 */
        if (func_0027FC20(0x9DC, 0x9DF, tutorial) == 1) {
            SzDuel_SetWindowDisp(0);
        }
        goto block_296;
    case 0x3:                                       /* switch 1 */
        if (func_0027F890(0x10, -1, 0) == 1) {
            func_0027FAB0(tutorial + 0x1B0);
            func_00172510(0x3C);
            (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) ((*(u16 *)((u8 *)(tutorial) + 0x1A2)) + 1);
        }
        goto block_296;
    case 0x4:                                       /* switch 1 */
        if (func_0027F890(0x10, 1, 0) == 1) {
            SzDuel_OpenMsgPopup(0, -0x78, 0x50, SzDuel_GetMsgName(0x3C));
            if (((*(u16 *)((u8 *)(tutorial) + 0x1A4)))++ > 0x3c) {
                (*(u16 *)((u8 *)(tutorial) + 0x1A4)) = 0U;
                (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) ((*(u16 *)((u8 *)(tutorial) + 0x1A2)) + 1);
            }
        }
        goto block_296;
    case 0x5:                                       /* switch 1 */
        func_0027FC20(0x9E0, 0x9E1, tutorial);
        goto block_296;
    case 0x6:                                       /* switch 1 */
        if (func_0027F890(0x10, -1, 0) == 1) {
            func_0027FA30(tutorial + 0x1B0, 0);
            (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) ((*(u16 *)((u8 *)(tutorial) + 0x1A2)) + 1);
        }
        goto block_296;
    case 0x7:                                       /* switch 1 */
        SzDuel_SetWindowDisp(1);
        if (func_0027F890(0x10, 1, 0) == 1) {
            func_0027FC20(0x9E2, 0x9E2, tutorial);
        }
        goto block_296;
    case 0x8:                                       /* switch 1 */
        if (((*(u16 *)((u8 *)(tutorial) + 0x1A4)))++ > 0xc) {
            (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) ((*(u16 *)((u8 *)(tutorial) + 0x1A2)) + 1);
            (*(u16 *)((u8 *)(tutorial) + 0x1A4)) = 0U;
            return 0x80;
        }
        goto block_296;
    case 0x9:                                       /* switch 1 */
        if (((*(u16 *)((u8 *)(tutorial) + 0x1A4)))++ > 0x1e) {
            (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) ((*(u16 *)((u8 *)(tutorial) + 0x1A2)) + 1);
            (*(u16 *)((u8 *)(tutorial) + 0x1A4)) = 0U;
        }
        goto block_296;
    case 0xA:                                       /* switch 1 */
        func_0027FC20(0x9E3, 0x9E5, tutorial);
        goto block_296;
    case 0xB:                                       /* switch 1 */
        if (((*(u16 *)((u8 *)(tutorial) + 0x1A4)))++ > 0xc) {
            (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) ((*(u16 *)((u8 *)(tutorial) + 0x1A2)) + 1);
            (*(u16 *)((u8 *)(tutorial) + 0x1A4)) = 0U;
            return 0x1000;
        }
        goto block_296;
    case 0xC:                                       /* switch 1 */
        if (((*(u16 *)((u8 *)(tutorial) + 0x1A4)))++ > 0xc) {
            (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) ((*(u16 *)((u8 *)(tutorial) + 0x1A2)) + 1);
            (*(u16 *)((u8 *)(tutorial) + 0x1A4)) = 0U;
            return 0x40;
        }
        goto block_296;
    case 0xD:                                       /* switch 1 */
        func_0027FC20(0x9E6, 0x9E8, tutorial);
        (*(u16 *)((u8 *)(tutorial) + 0x162)) = 0U;
        goto block_296;
    case 0xE:                                       /* switch 1 */
        func_0027F630(tutorial, 0xA, 0x800, -0xE8, -0x8C);
        if (((*(u16 *)((u8 *)(tutorial) + 0x162)))++ > 0x3c) {
            SzDuel_CloseHandCursor();
            (*(u16 *)((u8 *)(tutorial) + 0x1A4)) = 0U;
            (*(u16 *)((u8 *)(tutorial) + 0x162)) = 0U;
            (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) ((*(u16 *)((u8 *)(tutorial) + 0x1A2)) + 1);
        }
        goto block_296;
    case 0xF:                                       /* switch 1 */
        func_0027FC20(0x9E9, 0x9EC, tutorial);
        goto block_296;
    case 0x10:                                      /* switch 1 */
        func_0027F630(tutorial, 0xA, 0x800, 0x3C, 0x4B);
        if (((*(u16 *)((u8 *)(tutorial) + 0x162)))++ > 0x3c) {
            SzDuel_CloseHandCursor();
            (*(u16 *)((u8 *)(tutorial) + 0x1A4)) = 0U;
            (*(u16 *)((u8 *)(tutorial) + 0x162)) = 0U;
            (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) ((*(u16 *)((u8 *)(tutorial) + 0x1A2)) + 1);
        }
        goto block_296;
    case 0x11:                                      /* switch 1 */
        func_0027FC20(0x9ED, 0x9F0, tutorial);
        goto block_296;
    case 0x12:                                      /* switch 1 */
    case 0x13:                                      /* switch 1 */
    case 0x14:                                      /* switch 1 */
        if (((*(u16 *)((u8 *)(tutorial) + 0x1A4)))++ > 0xc) {
            (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) ((*(u16 *)((u8 *)(tutorial) + 0x1A2)) + 1);
            (*(u16 *)((u8 *)(tutorial) + 0x1A4)) = 0U;
            return 0x2000;
        }
        goto block_296;
    case 0x15:                                      /* switch 1 */
        if (((*(u16 *)((u8 *)(tutorial) + 0x1A4)))++ > 0xc) {
            (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) ((*(u16 *)((u8 *)(tutorial) + 0x1A2)) + 1);
            (*(u16 *)((u8 *)(tutorial) + 0x1A4)) = 0U;
            return 0x8000;
        }
        goto block_296;
    case 0x16:                                      /* switch 1 */
        func_0027FC20(0x9F1, 0x9F1, tutorial);
        goto block_296;
    case 0x17:                                      /* switch 1 */
        if (((*(u16 *)((u8 *)(tutorial) + 0x1A4)))++ > 0xc) {
            (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) ((*(u16 *)((u8 *)(tutorial) + 0x1A2)) + 1);
            (*(u16 *)((u8 *)(tutorial) + 0x1A4)) = 0U;
            return 0x40;
        }
        goto block_296;
    case 0x18:                                      /* switch 1 */
        func_0027FC20(0x9F2, 0x9F3, tutorial);
        goto block_296;
    case 0x19:                                      /* switch 1 */
        if (((*(u16 *)((u8 *)(tutorial) + 0x1A4)))++ > 0xc) {
            (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) ((*(u16 *)((u8 *)(tutorial) + 0x1A2)) + 1);
            (*(u16 *)((u8 *)(tutorial) + 0x1A4)) = 0U;
            return 0x40;
        }
        goto block_296;
    case 0x1A:                                      /* switch 1 */
        if (func_0027FC20(0x9F4, 0x9F6, tutorial) == 1) {
            func_0027FAB0(tutorial + 0x1B0);
            TaView_ReqStdCompleteView(0x1E);
        }
        goto block_296;
    case 0x1B:                                      /* switch 1 */
        if (((*(u16 *)((u8 *)(tutorial) + 0x1A4)))++ > 0x3c) {
            SzDuel_SetWindowDisp(0);
            if (func_0027F890(0x10, -1, 0) == 1) {
                func_00172510(0);
                (*(u16 *)((u8 *)(tutorial) + 0x1A4)) = 0U;
                (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) ((*(u16 *)((u8 *)(tutorial) + 0x1A2)) + 1);
            }
        }
        goto block_296;
    case 0x1C:                                      /* switch 1 */
        if (func_0027F890(0x10, 1, 0) == 1) {
            SzDuel_OpenMsgPopup(0, -0x78, 0x50, SzDuel_GetMsgName(0));
            if (((*(u16 *)((u8 *)(tutorial) + 0x1A4)))++ > 0x3c) {
                (*(u16 *)((u8 *)(tutorial) + 0x1A4)) = 0U;
                (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) ((*(u16 *)((u8 *)(tutorial) + 0x1A2)) + 1);
            }
        }
        goto block_296;
    case 0x1D:                                      /* switch 1 */
        func_0027FC20(0x9F7, 0x9F7, tutorial);
        goto block_296;
    case 0x1E:                                      /* switch 1 */
        if (func_0027F890(0x10, -1, 0) == 1) {
            func_0027FA30(tutorial + 0x1B0, 0);
            (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) ((*(u16 *)((u8 *)(tutorial) + 0x1A2)) + 1);
            (*(u16 *)((u8 *)(tutorial) + 0x1A4)) = 0U;
        }
        goto block_296;
    case 0x1F:                                      /* switch 1 */
        SzDuel_SetWindowDisp(1);
        if (func_0027F890(0x10, 1, 0) == 1) {
            func_0027FC20(0x9F8, 0x9F8, tutorial);
        }
        goto block_296;
    case 0x20:                                      /* switch 1 */
        if (((*(u16 *)((u8 *)(tutorial) + 0x1A4)))++ > 0xc) {
            (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) ((*(u16 *)((u8 *)(tutorial) + 0x1A2)) + 1);
            (*(u16 *)((u8 *)(tutorial) + 0x1A4)) = 0U;
            return 0x40;
        }
        goto block_296;
    case 0x21:                                      /* switch 1 */
        func_0027FC20(0x9F9, 0x9FB, tutorial);
        goto block_296;
    case 0x22:                                      /* switch 1 */
    case 0x23:                                      /* switch 1 */
        if (((*(u16 *)((u8 *)(tutorial) + 0x1A4)))++ > 0xc) {
            (*(u16 *)((u8 *)(tutorial) + 0x1A4)) = 0U;
            temp_a0_2 = (*(u16 *)((u8 *)(tutorial) + 0x1A2));
            (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) (temp_a0_2 + 1);
            switch (temp_a0_2) {                    /* switch 2; irregular */
            case 34:                                /* switch 2 */
                return 0x1000;
            case 35:                                /* switch 2 */
                /* fallthrough */
            default:                                /* switch 2 */
                return 0x40;
            }
        } else {
            goto block_296;
        }
        break;
    case 0x24:                                      /* switch 1 */
        if (func_0027FC20(0x9FC, 0xA00, tutorial) == 1) {
            return 0x800;
        }
        goto block_296;
    case 0x25:                                      /* switch 1 */
        func_0027FC20(0xA01, 0xA01, tutorial);
        goto block_296;
    case 0x26:                                      /* switch 1 */
    case 0x27:                                      /* switch 1 */
    case 0x28:                                      /* switch 1 */
    case 0x29:                                      /* switch 1 */
    case 0x2A:                                      /* switch 1 */
    case 0x2B:                                      /* switch 1 */
    case 0x2C:                                      /* switch 1 */
    case 0x2D:                                      /* switch 1 */
    case 0x2E:                                      /* switch 1 */
    case 0x2F:                                      /* switch 1 */
    case 0x30:                                      /* switch 1 */
    case 0x31:                                      /* switch 1 */
        if (((*(u16 *)((u8 *)(tutorial) + 0x1A4)))++ > 6) {
            (*(u16 *)((u8 *)(tutorial) + 0x1A4)) = 0U;
            temp_v1_17 = (*(u16 *)((u8 *)(tutorial) + 0x1A2));
            (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) (temp_v1_17 + 1);
            switch (temp_v1_17) {                   /* switch 3 */
            case 38:                                /* switch 3 */
            case 40:                                /* switch 3 */
            case 43:                                /* switch 3 */
            case 44:                                /* switch 3 */
            case 45:                                /* switch 3 */
            case 46:                                /* switch 3 */
            case 48:                                /* switch 3 */
                return 0x40;
            case 39:                                /* switch 3 */
            case 42:                                /* switch 3 */
            case 47:                                /* switch 3 */
                return 0x1000;
            case 41:                                /* switch 3 */
                return 0x80;
            case 49:
            default:                                /* switch 3 */
                return 0x800;
            }
        } else {
            goto block_296;
        }
        break;
    case 0x32:                                      /* switch 1 */
        func_0027FC20(0xA02, 0xA05, tutorial);
        goto block_296;
    case 0x33:                                      /* switch 1 */
    case 0x34:                                      /* switch 1 */
    case 0x36:                                      /* switch 1 */
        if (((*(u16 *)((u8 *)(tutorial) + 0x1A4)))++ > 0xc) {
            (*(u16 *)((u8 *)(tutorial) + 0x1A4)) = 0U;
            temp_a0_3 = (*(u16 *)((u8 *)(tutorial) + 0x1A2));
            (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) (temp_a0_3 + 1);
            switch (temp_a0_3) {                    /* switch 4; irregular */
            case 0x33:                              /* switch 4 */
                /* fallthrough */
            case 0x36:                              /* switch 4 */
                return 0x40;
            case 0x34:                              /* switch 4 */
                return 0x1000;
            }
        } else {
            goto block_296;
        }
        break;
    case 0x35:                                      /* switch 1 */
        func_0027FC20(0xA06, 0xA06, tutorial);
        goto block_296;
    case 0x37:                                      /* switch 1 */
        if (func_0027FC20(0xA07, 0xA09, tutorial) == 1) {
            SzDuel_SetWindowDisp(0);
        }
        goto block_296;
    case 0x38:                                      /* switch 1 */
        if (func_0027F890(8, -1, 0) == 1) {
            func_0027FAB0(tutorial + 0x1B0);
            SzDuel_CalcLP(0, 4, 0xFA0);
            SzDuel_CalcLP(1, 4, 0xFA0);
            SzDuel_DelUnit(0, 1);
            SzDuel_DelUnit(1, 1);
            SzDuel_AddUnit(0, 3, 4, 0x9C, 0);
            SzDuel_AddUnit(1, 3, 3, 0x15, 0);
            SzDuel_SetUnitStatus(0, 1, 4, 1);
            SzDuel_SetUnitStatus(1, 1, 4, 1);
            (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) ((*(u16 *)((u8 *)(tutorial) + 0x1A2)) + 1);
            (*(u16 *)((u8 *)(tutorial) + 0x1A4)) = 0U;
        }
        goto block_296;
    case 0x39:                                      /* switch 1 */
        if ((SzEffect_IsModelStandby2(1) != 0) && (SzEffect_IsModelStandby2(0x101) != 0)) {
            if (((*(u16 *)((u8 *)(tutorial) + 0x1A4)))++ > 0x1e) {
                (*(u16 *)((u8 *)(tutorial) + 0x1A4)) = 0U;
                (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) ((*(u16 *)((u8 *)(tutorial) + 0x1A2)) + 1);
                SzDuel_SetPlayerCur(0, 3, 4);
            }
        }
        goto block_296;
    case 0x3A:                                      /* switch 1 */
        func_00172510(0x9C);
        SzDuel_SetWindowDisp(1);
        if (func_0027F890(8, 1, 1) == 1) {
            SzDuel_SetWindowDisp(1);
            (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) ((*(u16 *)((u8 *)(tutorial) + 0x1A2)) + 1);
            (*(u16 *)((u8 *)(tutorial) + 0x1A4)) = 0U;
        }
        goto block_296;
    case 0x3B:                                      /* switch 1 */
        func_0027FC20(0xA0A, 0xA0E, tutorial);
        goto block_296;
    case 0x3C:                                      /* switch 1 */
    case 0x3D:                                      /* switch 1 */
        if (((*(u16 *)((u8 *)(tutorial) + 0x1A4)))++ > 0xc) {
            (*(u16 *)((u8 *)(tutorial) + 0x1A4)) = 0U;
            temp_a0_4 = (*(u16 *)((u8 *)(tutorial) + 0x1A2));
            (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) (temp_a0_4 + 1);
            switch (temp_a0_4) {                    /* switch 5; irregular */
            case 0x3C:                              /* switch 5 */
                return 0x1000;
            case 0x3D:                              /* switch 5 */
                return 0x4000;
            }
        } else {
            goto block_296;
        }
        break;
    case 0x3E:                                      /* switch 1 */
        if (func_0027FC20(0xA0F, 0xA0F, tutorial) == 1) {
            return 0x40;
        }
        goto block_296;
    case 0x3F:                                      /* switch 1 */
    case 0x40:                                      /* switch 1 */
    case 0x46:                                      /* switch 1 */
    case 0x47:                                      /* switch 1 */
    case 0x4D:                                      /* switch 1 */
    case 0x4E:                                      /* switch 1 */
    case 0x54:                                      /* switch 1 */
    case 0x55:                                      /* switch 1 */
    case 0x5B:                                      /* switch 1 */
    case 0x5C:                                      /* switch 1 */
    case 0x62:                                      /* switch 1 */
    case 0x63:                                      /* switch 1 */
    case 0x69:                                      /* switch 1 */
    case 0x6A:                                      /* switch 1 */
        if (((*(u16 *)((u8 *)(tutorial) + 0x1A4)))++ > 0xc) {
            (*(u16 *)((u8 *)(tutorial) + 0x1A4)) = 0U;
            temp_a0_5 = (*(u16 *)((u8 *)(tutorial) + 0x1A2));
            (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) (temp_a0_5 + 1);
            switch (temp_a0_5) {
            case 0x3F:
            case 0x46:
            case 0x4D:
            case 0x54:
            case 0x5B:
            case 0x62:
            case 0x69:
                return 0x1000;
            case 0x40:
            case 0x47:
            case 0x4E:
            case 0x55:
            case 0x5C:
            case 0x63:
            case 0x6A:
                return 0x40;
            }
        } else {
            goto block_296;
        }
        break;
    case 0x41:                                      /* switch 1 */
        if (func_0027FC20(0xA10, 0xA11, tutorial) == 1) {
            SzDuel_SetWindowDisp(0);
        }
        goto block_296;
    case 0x42:                                      /* switch 1 */
        if (func_0027F890(8, -1, 1) == 1) {
            func_0027FAB0(tutorial + 0x1B0);
            SzDuel_DelUnit(0, 1);
            SzDuel_DelUnit(1, 1);
            SzDuel_AddUnit(0, 3, 4, 0x9C, 0);
            SzDuel_AddUnit(1, 3, 3, 5, 0);
            SzDuel_SetUnitStatus(0, 1, 4, 1);
            SzDuel_SetUnitStatus(1, 1, 4, 1);
            (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) ((*(u16 *)((u8 *)(tutorial) + 0x1A2)) + 1);
            (*(u16 *)((u8 *)(tutorial) + 0x1A4)) = 0U;
        }
        goto block_296;
    case 0x43:                                      /* switch 1 */
        if ((SzEffect_IsModelStandby2(1) != 0) && (SzEffect_IsModelStandby2(0x101) != 0)) {
            if (((*(u16 *)((u8 *)(tutorial) + 0x1A4)))++ > 0x1e) {
                (*(u16 *)((u8 *)(tutorial) + 0x1A4)) = 0U;
                (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) ((*(u16 *)((u8 *)(tutorial) + 0x1A2)) + 1);
                SzDuel_SetPlayerCur(0, 3, 4);
            }
        }
        goto block_296;
    case 0x44:                                      /* switch 1 */
        func_00172510(0x9C);
        SzDuel_SetWindowDisp(1);
        if (func_0027F890(8, 1, 1) == 1) {
            (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) ((*(u16 *)((u8 *)(tutorial) + 0x1A2)) + 1);
            (*(u16 *)((u8 *)(tutorial) + 0x1A4)) = 0U;
        }
        goto block_296;
    case 0x45:                                      /* switch 1 */
        if (func_0027FC20(0xA12, 0xA13, tutorial) != 0) {
            return 0x40;
        }
        goto block_296;
    case 0x48:                                      /* switch 1 */
        if (func_0027FC20(0xA14, 0xA14, tutorial) == 1) {
            SzDuel_SetWindowDisp(0);
        }
        goto block_296;
    case 0x49:                                      /* switch 1 */
        if (func_0027F890(8, -1, 1) == 1) {
            func_0027FAB0(tutorial + 0x1B0);
            SzDuel_CalcLP(0, 4, 0xFA0);
            SzDuel_CalcLP(1, 4, 0xFA0);
            SzDuel_DelUnit(0, 1);
            SzDuel_DelUnit(1, 1);
            SzDuel_AddUnit(0, 3, 4, 0x9C, 0);
            SzDuel_AddUnit(1, 3, 3, 0x16, 0);
            SzDuel_SetUnitStatus(0, 1, 4, 1);
            SzDuel_SetUnitStatus(1, 1, 4, 1);
            (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) ((*(u16 *)((u8 *)(tutorial) + 0x1A2)) + 1);
            (*(u16 *)((u8 *)(tutorial) + 0x1A4)) = 0U;
        }
        goto block_296;
    case 0x4A:                                      /* switch 1 */
        if ((SzEffect_IsModelStandby2(1) != 0) && (SzEffect_IsModelStandby2(0x101) != 0)) {
            if (((*(u16 *)((u8 *)(tutorial) + 0x1A4)))++ > 0x1e) {
                (*(u16 *)((u8 *)(tutorial) + 0x1A4)) = 0U;
                (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) ((*(u16 *)((u8 *)(tutorial) + 0x1A2)) + 1);
                SzDuel_SetPlayerCur(0, 3, 4);
            }
        }
        goto block_296;
    case 0x4B:                                      /* switch 1 */
        SzDuel_SetWindowDisp(1);
        func_00172510(0x9C);
        if (func_0027F890(8, 1, 1) == 1) {
            (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) ((*(u16 *)((u8 *)(tutorial) + 0x1A2)) + 1);
            (*(u16 *)((u8 *)(tutorial) + 0x1A4)) = 0U;
        }
        goto block_296;
    case 0x4C:                                      /* switch 1 */
        if (func_0027FC20(0xA15, 0xA16, tutorial) != 0) {
            return 0x40;
        }
        goto block_296;
    case 0x4F:                                      /* switch 1 */
        if (func_0027FC20(0xA17, 0xA18, tutorial) == 1) {
            SzDuel_SetWindowDisp(0);
        }
        goto block_296;
    case 0x50:                                      /* switch 1 */
        if (func_0027F890(8, -1, 1) == 1) {
            func_0027FAB0(tutorial + 0x1B0);
            SzDuel_CalcLP(0, 4, 0xFA0);
            SzDuel_CalcLP(1, 4, 0xFA0);
            SzDuel_DelUnit(0, 1);
            SzDuel_DelUnit(1, 1);
            SzDuel_AddUnit(0, 3, 4, 0x9C, 0);
            SzDuel_AddUnit(1, 3, 3, 0xA9, 0);
            SzDuel_SetUnitStatus(0, 1, 4, 1);
            SzDuel_SetUnitStatus(1, 1, 4, 1);
            SzDuel_SetUnitStatus(1, 1, 3, 1);
            SzDuel_SetUnitStatus(1, 1, 5, 1);
            (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) ((*(u16 *)((u8 *)(tutorial) + 0x1A2)) + 1);
            (*(u16 *)((u8 *)(tutorial) + 0x1A4)) = 0U;
        }
        goto block_296;
    case 0x51:                                      /* switch 1 */
        if ((SzEffect_IsModelStandby2(1) != 0) && (SzEffect_IsModelStandby2(0x101) != 0)) {
            if (((*(u16 *)((u8 *)(tutorial) + 0x1A4)))++ > 0x1e) {
                (*(u16 *)((u8 *)(tutorial) + 0x1A4)) = 0U;
                (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) ((*(u16 *)((u8 *)(tutorial) + 0x1A2)) + 1);
                SzDuel_SetPlayerCur(0, 3, 4);
            }
        }
        goto block_296;
    case 0x52:                                      /* switch 1 */
        SzDuel_SetWindowDisp(1);
        func_00172510(0x9C);
        if (func_0027F890(8, 1, 1) == 1) {
            (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) ((*(u16 *)((u8 *)(tutorial) + 0x1A2)) + 1);
            (*(u16 *)((u8 *)(tutorial) + 0x1A4)) = 0U;
        }
        goto block_296;
    case 0x53:                                      /* switch 1 */
        if (func_0027FC20(0xA19, 0xA1C, tutorial) != 0) {
            return 0x40;
        }
        goto block_296;
    case 0x56:                                      /* switch 1 */
        if (func_0027FC20(0xA1D, 0xA1D, tutorial) == 1) {
            SzDuel_SetWindowDisp(0);
        }
        goto block_296;
    case 0x57:                                      /* switch 1 */
        if (func_0027F890(8, -1, 1) == 1) {
            func_0027FAB0(tutorial + 0x1B0);
            SzDuel_CalcLP(0, 4, 0xFA0);
            SzDuel_CalcLP(1, 4, 0xFA0);
            SzDuel_DelUnit(0, 1);
            SzDuel_DelUnit(1, 1);
            SzDuel_AddUnit(0, 3, 4, 0x9C, 0);
            SzDuel_AddUnit(1, 3, 3, 0x64, 0);
            SzDuel_SetUnitStatus(0, 1, 4, 1);
            SzDuel_SetUnitStatus(1, 1, 4, 1);
            SzDuel_SetUnitStatus(1, 1, 3, 1);
            SzDuel_SetUnitStatus(1, 1, 5, 1);
            (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) ((*(u16 *)((u8 *)(tutorial) + 0x1A2)) + 1);
            (*(u16 *)((u8 *)(tutorial) + 0x1A4)) = 0U;
        }
        goto block_296;
    case 0x58:                                      /* switch 1 */
        if ((SzEffect_IsModelStandby2(1) != 0) && (SzEffect_IsModelStandby2(0x101) != 0)) {
            if (((*(u16 *)((u8 *)(tutorial) + 0x1A4)))++ > 0x1e) {
                (*(u16 *)((u8 *)(tutorial) + 0x1A4)) = 0U;
                (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) ((*(u16 *)((u8 *)(tutorial) + 0x1A2)) + 1);
                SzDuel_SetPlayerCur(0, 3, 4);
            }
        }
        goto block_296;
    case 0x59:                                      /* switch 1 */
        SzDuel_SetWindowDisp(1);
        func_00172510(0x9C);
        if (func_0027F890(8, 1, 1) == 1) {
            (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) ((*(u16 *)((u8 *)(tutorial) + 0x1A2)) + 1);
            (*(u16 *)((u8 *)(tutorial) + 0x1A4)) = 0U;
        }
        goto block_296;
    case 0x5A:                                      /* switch 1 */
        if (func_0027FC20(0xA1E, 0xA1F, tutorial) != 0) {
            return 0x40;
        }
        goto block_296;
    case 0x5D:                                      /* switch 1 */
        if (func_0027FC20(0xA20, 0xA21, tutorial) == 1) {
            SzDuel_SetWindowDisp(0);
        }
        goto block_296;
    case 0x5E:                                      /* switch 1 */
        if (func_0027F890(8, -1, 1) == 1) {
            func_0027FAB0(tutorial + 0x1B0);
            SzDuel_CalcLP(0, 4, 0xFA0);
            SzDuel_CalcLP(1, 4, 0xFA0);
            SzDuel_DelUnit(0, 1);
            SzDuel_DelUnit(1, 1);
            SzDuel_AddUnit(0, 3, 4, 0x9C, 0);
            SzDuel_AddUnit(1, 3, 3, 0x277, 0);
            SzDuel_SetUnitStatus(0, 1, 4, 1);
            SzDuel_SetUnitStatus(1, 1, 4, 1);
            SzDuel_SetUnitStatus(1, 1, 3, 1);
            SzDuel_SetUnitStatus(1, 1, 5, 1);
            (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) ((*(u16 *)((u8 *)(tutorial) + 0x1A2)) + 1);
            (*(u16 *)((u8 *)(tutorial) + 0x1A4)) = 0U;
        }
        goto block_296;
    case 0x5F:                                      /* switch 1 */
        if ((SzEffect_IsModelStandby2(1) != 0) && (SzEffect_IsModelStandby2(0x101) != 0)) {
            if (((*(u16 *)((u8 *)(tutorial) + 0x1A4)))++ > 0x1e) {
                (*(u16 *)((u8 *)(tutorial) + 0x1A4)) = 0U;
                (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) ((*(u16 *)((u8 *)(tutorial) + 0x1A2)) + 1);
                SzDuel_SetPlayerCur(0, 3, 4);
            }
        }
        goto block_296;
    case 0x60:                                      /* switch 1 */
        SzDuel_SetWindowDisp(1);
        func_00172510(0x9C);
        if (func_0027F890(8, 1, 1) == 1) {
            (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) ((*(u16 *)((u8 *)(tutorial) + 0x1A2)) + 1);
            (*(u16 *)((u8 *)(tutorial) + 0x1A4)) = 0U;
        }
        goto block_296;
    case 0x61:                                      /* switch 1 */
        if (func_0027FC20(0xA22, 0xA22, tutorial) != 0) {
            return 0x40;
        }
        goto block_296;
    case 0x64:                                      /* switch 1 */
        if (func_0027FC20(0xA23, 0xA25, tutorial) == 1) {
            SzDuel_SetWindowDisp(0);
        }
        goto block_296;
    case 0x65:                                      /* switch 1 */
        if (func_0027F890(8, -1, 1) == 1) {
            func_0027FAB0(tutorial + 0x1B0);
            SzDuel_CalcLP(0, 4, 0xFA0);
            SzDuel_CalcLP(1, 4, 0xED8);
            SzDuel_DelUnit(0, 1);
            SzDuel_DelUnit(1, 1);
            SzDuel_AddUnit(0, 3, 2, 0x9C, 0);
            SzDuel_SetUnitStatus(0, 1, 4, 1);
            (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) ((*(u16 *)((u8 *)(tutorial) + 0x1A2)) + 1);
            (*(u16 *)((u8 *)(tutorial) + 0x1A4)) = 0U;
        }
        goto block_296;
    case 0x66:                                      /* switch 1 */
        if (SzEffect_IsModelStandby2(1) != 0) {
            if (((*(u16 *)((u8 *)(tutorial) + 0x1A4)))++ > 0x1e) {
                (*(u16 *)((u8 *)(tutorial) + 0x1A4)) = 0U;
                (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) ((*(u16 *)((u8 *)(tutorial) + 0x1A2)) + 1);
                SzDuel_SetPlayerCur(0, 3, 2);
            }
        }
        goto block_296;
    case 0x67:                                      /* switch 1 */
        SzDuel_SetWindowDisp(1);
        func_00172510(0x9C);
        if (func_0027F890(8, 1, 1) == 1) {
            (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) ((*(u16 *)((u8 *)(tutorial) + 0x1A2)) + 1);
            (*(u16 *)((u8 *)(tutorial) + 0x1A4)) = 0U;
        }
        goto block_296;
    case 0x68:                                      /* switch 1 */
        if (func_0027FC20(0xA26, 0xA2A, tutorial) != 0) {
            return 0x40;
        }
        goto block_296;
    case 0x6B:                                      /* switch 1 */
        if (func_0027FC20(0xA2B, 0xA2C, tutorial) == 1) {
            SzDuel_SetWindowDisp(0);
        }
        goto block_296;
    case 0x6C:                                      /* switch 1 */
        if (func_0027F890(8, -1, 1) == 1) {
            SzDuel_AddUnit(0, 3, 5, 0x272, 0);
            (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) ((*(u16 *)((u8 *)(tutorial) + 0x1A2)) + 1);
            (*(u16 *)((u8 *)(tutorial) + 0x1A4)) = 0U;
        }
        goto block_296;
    case 0x6D:                                      /* switch 1 */
        SzDuel_SetPlayerCur(0, 3, 5);
        if (SzEffect_IsModelStandby2(2) != 0) {
            if (((*(u16 *)((u8 *)(tutorial) + 0x1A4)))++ > 0x1e) {
                (*(u16 *)((u8 *)(tutorial) + 0x1A4)) = 0U;
                (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) ((*(u16 *)((u8 *)(tutorial) + 0x1A2)) + 1);
            }
        }
        goto block_296;
    case 0x6E:                                      /* switch 1 */
        SzDuel_SetWindowDisp(1);
        if (func_0027F890(8, 1, 1) == 1) {
            (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) ((*(u16 *)((u8 *)(tutorial) + 0x1A2)) + 1);
            (*(u16 *)((u8 *)(tutorial) + 0x1A4)) = 0U;
        }
        goto block_296;
    case 0x6F:                                      /* switch 1 */
        if (func_0027FC20(0xA2D, 0xA2F, tutorial) == 1) {
            return 0x40;
        }
        goto block_296;
    case 0x70:                                      /* switch 1 */
        func_0027FC20(0xA30, 0xA30, tutorial);
        goto block_296;
    case 0x71:                                      /* switch 1 */
    case 0x72:                                      /* switch 1 */
    case 0x73:                                      /* switch 1 */
    case 0x74:                                      /* switch 1 */
    case 0x76:                                      /* switch 1 */
    case 0x77:                                      /* switch 1 */
    case 0x78:                                      /* switch 1 */
    case 0x79:                                      /* switch 1 */
    case 0x7A:                                      /* switch 1 */
    case 0x7B:                                      /* switch 1 */
    case 0x7D:                                      /* switch 1 */
    case 0x7E:                                      /* switch 1 */
    case 0x7F:                                      /* switch 1 */
    case 0x80:                                      /* switch 1 */
    case 0x82:                                      /* switch 1 */
    case 0x83:                                      /* switch 1 */
    case 0x84:                                      /* switch 1 */
        if (((*(u16 *)((u8 *)(tutorial) + 0x1A4)))++ > 0xc) {
            (*(u16 *)((u8 *)(tutorial) + 0x1A4)) = 0U;
            temp_v1_30 = (*(u16 *)((u8 *)(tutorial) + 0x1A2));
            (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) (temp_v1_30 + 1);
            switch (temp_v1_30) {                   /* switch 7 */
            case 0x84:                              /* switch 7 */
                return 0x40;
            case 0x72:                              /* switch 7 */
            case 0x74:                              /* switch 7 */
                return 4;
            case 0x71:                              /* switch 7 */
            case 0x73:                              /* switch 7 */
            case 0x76:                              /* switch 7 */
            case 0x79:                              /* switch 7 */
            case 0x82:                              /* switch 7 */
                return 8;
            case 0x77:                              /* switch 7 */
                return 0x1000;
            case 0x78:                              /* switch 7 */
                return 0x4000;
            case 0x7A:                              /* switch 7 */
                return 0x2000;
            case 0x7B:                              /* switch 7 */
                return 0x8000;
            case 0x7D:                              /* switch 7 */
            case 0x7F:                              /* switch 7 */
            case 0x83:                              /* switch 7 */
                return 2;
            case 0x7E:                              /* switch 7 */
            case 0x80:                              /* switch 7 */
                return 1;
            }
        } else {
            goto block_296;
        }
        break;
    case 0x75:                                      /* switch 1 */
        func_0027FC20(0xA31, 0xA31, tutorial);
        goto block_296;
    case 0x7C:                                      /* switch 1 */
        func_0027FC20(0xA32, 0xA35, tutorial);
        goto block_296;
    case 0x81:                                      /* switch 1 */
        func_0027FC20(0xA36, 0xA36, tutorial);
        goto block_296;
    case 0x85:                                      /* switch 1 */
        if (func_0027FC20(0xA37, 0xA38, tutorial) == 1) {
            SzDuel_SetWindowDisp(0);
        }
        goto block_296;
    case 0x86:                                      /* switch 1 */
        if (func_0027F890(8, -1, 1) == 1) {
            func_0027FAB0(tutorial + 0x1B0);
            SzDuel_AddUnit(1, 2, 2, 3, 0);
            SzDuel_AddUnit(0, 2, 6, 0x2AB, 0);
            SzDuel_SetUnitStatus(1, 1, 4, 1);
            (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) ((*(u16 *)((u8 *)(tutorial) + 0x1A2)) + 1);
            (*(u16 *)((u8 *)(tutorial) + 0x1A4)) = 0U;
        }
        goto block_296;
    case 0x87:                                      /* switch 1 */
        SzDuel_SetPlayerCur(0, 2, 2);
        if (SzEffect_IsModelStandby2(0x101) != 0) {
            if (((*(u16 *)((u8 *)(tutorial) + 0x1A4)))++ > 0x1e) {
                (*(u16 *)((u8 *)(tutorial) + 0x1A4)) = 0U;
                (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) ((*(u16 *)((u8 *)(tutorial) + 0x1A2)) + 1);
            }
        }
        goto block_296;
    case 0x88:                                      /* switch 1 */
        SzDuel_SetWindowDisp(1);
        func_00172510(3);
        if (func_0027F890(8, 1, 1) == 1) {
            (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) ((*(u16 *)((u8 *)(tutorial) + 0x1A2)) + 1);
            (*(u16 *)((u8 *)(tutorial) + 0x1A4)) = 0U;
        }
        goto block_296;
    case 0x89:                                      /* switch 1 */
        func_0027FC20(0xA39, 0xA3B, tutorial);
        goto block_296;
    case 0x8A:                                      /* switch 1 */
        if (((s32) (event & 0xFFFF) >> 8) == 6) {
            (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) (temp_a0 + 1);
            return 0x10;
        }
        if (((*(u16 *)((u8 *)(tutorial) + 0x1A4)))++ > 3) {
            (*(u16 *)((u8 *)(tutorial) + 0x1A4)) = 0U;
            return 0x4000;
        }
        goto block_296;
    case 0x8B:                                      /* switch 1 */
    case 0x8D:                                      /* switch 1 */
        if (((*(u16 *)((u8 *)(tutorial) + 0x1A4)))++ > 0x3c) {
            (*(u16 *)((u8 *)(tutorial) + 0x1A4)) = 0U;
            temp_a0_6 = (*(u16 *)((u8 *)(tutorial) + 0x1A2));
            (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) (temp_a0_6 + 1);
            switch (temp_a0_6) {                    /* switch 8; irregular */
            case 0x8B:                              /* switch 8 */
                return 0x4000;
            case 0x8D:                              /* switch 8 */
                return 0x20;
            }
        } else {
            goto block_296;
        }
        break;
    case 0x8C:                                      /* switch 1 */
        func_0027FC20(0xA3C, 0xA40, tutorial);
        goto block_296;
    case 0x8E:                                      /* switch 1 */
    case 0x8F:                                      /* switch 1 */
    case 0x90:                                      /* switch 1 */
        if (((*(u16 *)((u8 *)(tutorial) + 0x1A4)))++ > 0xc) {
            (*(u16 *)((u8 *)(tutorial) + 0x1A4)) = 0U;
            temp_a0_7 = (*(u16 *)((u8 *)(tutorial) + 0x1A2));
            (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) (temp_a0_7 + 1);
            switch (temp_a0_7) {                    /* switch 9; irregular */
            case 0x8E:                              /* switch 9 */
                /* fallthrough */
            case 0x90:                              /* switch 9 */
                return 0x40;
            case 0x8F:                              /* switch 9 */
                return 2;
            }
        } else {
            goto block_296;
        }
        break;
    case 0x91:                                      /* switch 1 */
        if (((s32) (event & 0xFFFF) >> 8) == 2) {
            (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) (temp_a0 + 1);
            goto block_296;
        }
        if (((*(u16 *)((u8 *)(tutorial) + 0x1A4)))++ > 3) {
            (*(u16 *)((u8 *)(tutorial) + 0x1A4)) = 0U;
            return 0x1000;
        }
        goto block_296;
    case 0x92:                                      /* switch 1 */
        if (func_0027FC20(0xA41, 0xA41, tutorial) == 1) {
            SzDuel_SetWindowDisp(0);
        }
        goto block_296;
    case 0x93:                                      /* switch 1 */
        if (func_0027F890(8, -1, 1) == 1) {
            func_0027FAB0(tutorial + 0x1B0);
            SzDuel_DelUnit(0, 1);
            SzDuel_DelUnit(0, 2);
            SzDuel_DelUnit(1, 1);
            SzDuel_CalcLP(0, 4, 0x320);
            SzDuel_AddUnit(1, 2, 6, 0, 0);
            SzDuel_AddUnit(1, 3, 5, 0xA0, 0);
            SzDuel_AddUnit(1, 4, 5, 0x82, 0);
            SzDuel_AddUnit(0, 4, 6, 0x9D, 0);
            SzDuel_SetUnitStatus(0, 1, 4, 1);
            SzDuel_SetUnitStatus(1, 1, 4, 1);
            SzDuel_SetUnitStatus(1, 2, 4, 1);
            SzDuel_SetUnitStatus(1, 3, 4, 1);
            (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) ((*(u16 *)((u8 *)(tutorial) + 0x1A2)) + 1);
            (*(u16 *)((u8 *)(tutorial) + 0x1A4)) = 0U;
        }
        goto block_296;
    case 0x94:                                      /* switch 1 */
        SzDuel_SetPlayerCur(0, 3, 6);
        (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) ((*(u16 *)((u8 *)(tutorial) + 0x1A2)) + 1);
        goto block_296;
    case 0x95:                                      /* switch 1 */
        if ((SzEffect_IsModelStandby2(0x101) != 0) && (SzEffect_IsModelStandby2(0x102) != 0) && (SzEffect_IsModelStandby2(0x103) != 0) && (SzEffect_IsModelStandby2(1) != 0)) {
            if (((*(u16 *)((u8 *)(tutorial) + 0x1A4)))++ > 0x1e) {
                (*(u16 *)((u8 *)(tutorial) + 0x1A4)) = 0U;
                (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) ((*(u16 *)((u8 *)(tutorial) + 0x1A2)) + 1);
            }
        }
        goto block_296;
    case 0x96:                                      /* switch 1 */
        SzDuel_SetWindowDisp(1);
        if (func_0027F890(8, 1, 1) == 1) {
            (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) ((*(u16 *)((u8 *)(tutorial) + 0x1A2)) + 1);
            (*(u16 *)((u8 *)(tutorial) + 0x1A4)) = 0U;
        }
        goto block_296;
    case 0x97:                                      /* switch 1 */
        func_0027FC20(0xA42, 0xA44, tutorial);
        goto block_296;
    case 0x98:                                      /* switch 1 */
    case 0x99:                                      /* switch 1 */
    case 0x9A:                                      /* switch 1 */
        if (((*(u16 *)((u8 *)(tutorial) + 0x1A4)))++ > 0xc) {
            (*(u16 *)((u8 *)(tutorial) + 0x1A4)) = 0U;
            temp_a0_8 = (*(u16 *)((u8 *)(tutorial) + 0x1A2));
            (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) (temp_a0_8 + 1);
            switch (temp_a0_8) {                    /* switch 10; irregular */
            case 0x98:                              /* switch 10 */
                return 0x100;
            case 0x99:                              /* switch 10 */
                return 0x8000;
            case 0x9A:                              /* switch 10 */
                return 0x20;
            }
        } else {
            goto block_296;
        }
        break;
    case 0x9B:                                      /* switch 1 */
        (*(u16 *)((u8 *)(tutorial) + 0x1A2)) = (u16) (temp_a0 + 1);
        goto block_296;
    case 0x9C:                                      /* switch 1 */
        func_0027FC20(0xA45, 0xA46, tutorial);
        SzDuel_SetWindowDisp(0);
        goto block_296;
    case 0x9D:                                      /* switch 1 */
        if ((func_0027F890(8, -1, 0) == 1) && (func_0027FC20(0xA47, 0xA47, tutorial) == 1)) {
            return -1;
        }
        goto block_296;
    default:                                        /* switch 1 */
        return -1;
    }
block_296:
    return 0;
}

#pragma global_optimizer reset

/* Moves the camera to a tutorial unit's model. */
void TaTuto_FocusUnit_001745F0(s32 arg0) {
    s32 rot[4];
    f32 vec[4];
    s32 unit;
    s32 x;
    s32 d;

    SzView_FreeRequest(0, 0);
    switch (arg0) {
    case 0x3A:
        unit = SzDuel_GetUnit(0, 0);
        SzEffect_GetModelRot2(0, rot);
        rot[0] += 63;
        x = *(s32 *)(unit + 0x30);
        d = 0x47FF - x;
        if (d < 0) {
            d = 0x147FE - x;
        }
        rot[1] += d;
        rot[2] += 0x1000;
        SzView_IV2V(rot, vec);
        vec[0] += SzEffect_GetRadius2(0);
        SzView_ReqCamera(0, 0, 7, 0, SzDuel_GetUnitModelID(0, 0), NULL);
        SzView_ReqCamera(0, 0, 4, 0, 0, vec);
        break;
    case 0x9C:
        unit = SzDuel_GetUnit(0, 1);
        SzEffect_GetModelRot2(1, rot);
        rot[0] += 63;
        x = *(s32 *)(unit + 0x30);
        d = 0xC7FF - x;
        if (d < 0) {
            d = 0x1C7FE - x;
        }
        rot[1] += d;
        rot[2] += 0x1000;
        SzView_IV2V(rot, vec);
        vec[0] += SzEffect_GetRadius2(1);
        SzView_ReqCamera(0, 0, 7, 0, SzDuel_GetUnitModelID(0, 1), NULL);
        SzView_ReqCamera(0, 0, 4, 0, 0, vec);
        break;
    }
}

typedef struct Tutorial_001747D0 {
    u8 pad0[0x162];
    u16 timer;
    u8 pad164[0x3E];
    u16 step;
    u16 wait;
    u8 pad1A6[0xA];
    u8 text[1];
} Tutorial_001747D0;

/* Runs one frame of tutorial lesson 2. `event` is the duel event (kind in bits 8-15). */
s32 TaTuto_Lesson2(s32 event, void *tutorial) {
    extern void SzPad_SetAnalogInfo();
    extern s32 SzDuel_SetUnitCtlGoal();
    Tutorial_001747D0 *arg1 = tutorial;
    if (SzDuel_GetWindowDisp() != 0) {
        SzDuel_SetWindowDraw(1);
    } else {
        SzDuel_SetWindowDraw(0);
    }
    SzPad_SetAnalogInfo(0, 0, 0x80);
    SzPad_SetAnalogInfo(0, 1, 0x80);
    SzPad_SetAnalogInfo(0, 2, 0x80);
    SzPad_SetAnalogInfo(0, 3, 0x80);
    if (SzPad_Check(0, 0, 0x800) != 0) {
        return -2;
    }
    switch (arg1->step) {
    case 0x0:
        SzDuel_SetIgnoreJudge(1);
        SzDuel_SetWindowDisp(1);
        arg1->step = 2;
        break;
    case 0x1:
        if (SzEffect_IsModelStandby2(0) != 0) {
            if (SzEffect_IsModelStandby2(0x100) != 0) {
                arg1->step++;
            }
        }
        break;
    case 0x2:
        if (func_0027FC20(0xA48, 0xA4A, arg1) == 1) {
            SzDuel_SetWindowDisp(0);
        }
        break;
    case 0x3:
        if (func_0027F890(8, -1, 0) == 1) {
            func_0027FAB0(arg1->text);
            SzDuel_CalcLP(0, 4, 0xFA0);
            SzDuel_CalcLP(1, 4, 0x3E8);
            SzDuel_AddUnit(0, 3, 1, 0x9C, 0);
            SzDuel_SetUnitStatus(0, 1, 4, 1);
            arg1->step++;
            arg1->wait = 0;
        }
        break;
    case 0x4:
        SzDuel_SetPlayerCur(0, 3, 1);
        if (SzEffect_IsModelStandby2(1) != 0) {
            if (arg1->wait++ > 0x1E) {
                arg1->wait = 0;
                arg1->step++;
            }
        }
        break;
    case 0x5:
        TaTuto_FocusUnit_001745F0(0x9C);
        SzDuel_SetWindowDisp(1);
        if (func_0027F890(8, 1, 1) == 1) {
            SzDuel_SetWindowDisp(1);
            arg1->step++;
            arg1->wait = 0;
        }
        break;
    case 0x6:
        if (func_0027FC20(0xA4B, 0xA4B, arg1) == 1) {
            arg1->wait = 0;
            arg1->timer = 0;
        }
        break;
    case 0x7:
        func_0027F630(arg1, 0xA, 0x800, 0x12C, -0x9C);
        if (arg1->timer++ > 0x3C) {
            SzDuel_CloseHandCursor();
            arg1->wait = 0;
            arg1->timer = 0;
            arg1->step++;
        }
        break;
    case 0x8:
        func_0027FC20(0xA4C, 0xA4C, arg1);
        break;
    case 0x9:
    case 0xA:
    case 0xB:
    case 0x11:
    case 0x12:
    case 0x16:
    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1F:
        if (arg1->wait++ > 0xC) {
            arg1->wait = 0;
            switch (arg1->step++) {
            case 9:
            case 11:
            case 23:
            case 25:
                return 0x40;
            case 10:
            case 17:
            case 24:
                return 0x1000;
            case 18:
                return 0x10;
            case 22:
                return 0x4000;
            case 31:
                return 0x80;
            }
        }
        break;
    case 0xC:
        if (func_0027FC20(0xA4D, 0xA4E, arg1) == 1) {
            SzDuel_SetWindowDisp(0);
        }
        break;
    case 0xD:
        if (func_0027F890(8, -1, 0) == 1) {
            func_0027FAB0(arg1->text);
            SzDuel_DelUnit(0, 1);
            SzDuel_CalcLP(0, 4, 0x1F4);
            SzDuel_CalcLP(1, 4, 0x1F4);
            SzDuel_AddUnit(0, 3, 4, 0x9C, 0);
            SzDuel_AddUnit(1, 3, 3, 0x15A, 0);
            SzDuel_SetUnitStatus(0, 1, 4, 1);
            SzDuel_SetUnitStatus(1, 1, 4, 1);
            arg1->step++;
            arg1->wait = 0;
        }
        break;
    case 0xE:
        SzDuel_SetPlayerCur(0, 3, 4);
        if (SzEffect_IsModelStandby2(1) != 0 && SzEffect_IsModelStandby2(0x101) != 0) {
            if (arg1->wait++ > 0x1E) {
                arg1->wait = 0;
                arg1->step++;
            }
        }
        break;
    case 0xF:
        TaTuto_FocusUnit_001745F0(0x9C);
        SzDuel_SetWindowDisp(1);
        if (func_0027F890(8, 1, 1) == 1) {
            SzDuel_SetWindowDisp(1);
            arg1->step++;
            arg1->wait = 0;
        }
        break;
    case 0x10:
        func_0027FC20(0xA4F, 0xA51, arg1);
        break;
    case 0x14:
        func_0027FC20(0xA52, 0xA54, arg1);
        break;
    case 0x13:
    case 0x15:
        if (arg1->wait++ > 0xC) {
            arg1->wait = 0;
            switch (arg1->step++) {
            case 19:
                return 0x4000;
            case 21:
                return 0x20;
            }
        }
        break;
    case 0x1A:
        if (func_0027FC20(0xA55, 0xA57, arg1) == 1) {
            SzDuel_SetWindowDisp(0);
        }
        break;
    case 0x1B:
        if (func_0027F890(8, -1, 0) == 1) {
            func_0027FAB0(arg1->text);
            SzDuel_DelUnit(0, 1);
            SzDuel_DelUnit(1, 1);
            SzDuel_MoveUnit(0, 0, 3, 4);
            SzDuel_CalcLP(0, 4, 0xFA0);
            SzDuel_CalcLP(1, 4, 0xFA0);
            arg1->step++;
            arg1->wait = 0;
        }
        break;
    case 0x1C:
        SzDuel_SetPlayerCur(0, 3, 4);
        if (arg1->wait++ > 0x1E) {
            arg1->wait = 0;
            arg1->step++;
        }
        break;
    case 0x1D:
        SzDuel_SetWindowDisp(1);
        if (func_0027F890(8, 1, 1) == 1) {
            SzDuel_SetWindowDisp(1);
            arg1->step++;
            arg1->wait = 0;
        }
        break;
    case 0x1E:
        func_0027FC20(0xA58, 0xA58, arg1);
        break;
    case 0x20:
        func_0027FC20(0xA59, 0xA59, arg1);
        break;
    case 0x21:
        if (func_0027F890(0x10, -1, 0) == 1) {
            func_0027FAB0(arg1->text);
            SzDuel_AddUnit(1, 3, 3, 3, 0);
            SzDuel_AddUnit(1, 2, 3, 0x11D, 0);
            SzDuel_AddUnit(1, 4, 3, 0x20A, 0);
            SzDuel_AddUnit(1, 2, 4, 0x277, 0);
            SzDuel_AddUnit(1, 4, 4, 0x15, 0);
            SzDuel_AddUnit(1, 2, 5, 0x2AB, 0);
            SzDuel_AddUnit(1, 3, 5, 0x2AB, 0);
            SzDuel_AddUnit(1, 4, 5, 0x2AB, 0);
            SzDuel_SetUnitStatus(1, 1, 4, 1);
            SzDuel_SetUnitStatus(1, 2, 4, 1);
            SzDuel_SetUnitStatus(1, 3, 4, 1);
            SzDuel_SetUnitStatus(1, 4, 4, 1);
            SzDuel_SetUnitStatus(1, 5, 4, 1);
            arg1->step++;
            arg1->wait = 0;
            return 0x20;
        }
        break;
    case 0x22:
        if (SzEffect_IsModelStandby2(0x101) != 0 && SzEffect_IsModelStandby2(0x102) != 0 && SzEffect_IsModelStandby2(0x103) != 0 && SzEffect_IsModelStandby2(0x104) != 0 && SzEffect_IsModelStandby2(0x105) != 0) {
            if (arg1->wait++ > 0x1E) {
                arg1->wait = 0;
                arg1->step++;
                TaView_ReqStdCompleteView(0);
            }
        }
        break;
    case 0x23:
        if (func_0027F890(0x10, 1, 1) == 1) {
            arg1->step++;
            arg1->wait = 0;
        }
        break;
    case 0x24:
        if (func_0027FC20(0xA5A, 0xA5C, arg1) == 1) {
            SzDuel_SetWindowDisp(0);
        }
        break;
    case 0x25:
        if (func_0027F890(8, -1, 0) == 1) {
            SzDuel_DelUnit(1, 6);
            SzDuel_DelUnit(1, 7);
            SzDuel_DelUnit(1, 8);
            SzDuel_SetUnitCtlRate(1, 1, -1, 0);
            SzDuel_SetUnitCtlGoal(1, 1, 0);
            SzDuel_SetUnitCtlRate(1, 2, -1, 0);
            SzDuel_SetUnitCtlGoal(1, 2, 0);
            SzDuel_SetUnitCtlRate(1, 3, -1, 0);
            SzDuel_SetUnitCtlGoal(1, 3, 0);
            SzDuel_SetUnitCtlRate(1, 4, -1, 0);
            SzDuel_SetUnitCtlGoal(1, 4, 0);
            SzDuel_SetUnitCtlRate(1, 5, -1, 0);
            SzDuel_SetUnitCtlGoal(1, 5, 0);
            SzDuel_MoveUnit(1, 1, 6, 0);
            SzDuel_MoveUnit(1, 2, 6, 1);
            SzDuel_MoveUnit(1, 3, 6, 2);
            SzDuel_MoveUnit(1, 4, 6, 3);
            SzDuel_MoveUnit(1, 5, 6, 4);
            SzDuel_MoveUnit(0, 0, 0, 6);
            arg1->step++;
            arg1->wait = 0;
        }
        break;
    case 0x26:
        SzDuel_SetPlayerCur(0, 0, 6);
        if (arg1->wait++ > 0x1E) {
            arg1->wait = 0;
            arg1->step++;
            TaView_ReqHalfFarView(0);
            return 0x80;
        }
        break;
    case 0x27:
        if (func_0027F890(8, 1, 0) == 1) {
            SzDuel_SetWindowDisp(1);
            arg1->step++;
            arg1->wait = 0;
        }
        break;
    case 0x28:
        func_0027FC20(0xA5D, 0xA5D, arg1);
        break;
    case 0x29:
        if (func_0027F890(0x10, -1, 0) == 1) {
            SzDuel_SetUnitCtlGoal(1, 1, 0x80);
            SzDuel_SetUnitCtlRate(1, 1, 1, 0x80);
            SzDuel_SetUnitCtlGoal(1, 2, 0x80);
            SzDuel_SetUnitCtlRate(1, 2, 1, 0x80);
            SzDuel_SetUnitCtlGoal(1, 3, 0x80);
            SzDuel_SetUnitCtlRate(1, 3, 1, 0x80);
            SzDuel_MoveUnit(1, 1, 0, 5);
            SzDuel_MoveUnit(1, 2, 1, 5);
            SzDuel_MoveUnit(1, 3, 1, 6);
            arg1->step++;
        }
        break;
    case 0x2A:
        if (func_0027F890(0x10, 1, 0) == 1 && func_0027FC20(0xA5E, 0xA5E, arg1) == 1) {
            SzDuel_SetWindowDisp(0);
        }
        break;
    case 0x2B:
        if (func_0027F890(0x10, -1, 0) == 1) {
            SzDuel_MoveUnit(1, 1, 6, 0);
            SzDuel_MoveUnit(1, 2, 6, 1);
            SzDuel_MoveUnit(1, 3, 6, 2);
            SzDuel_MoveUnit(0, 0, 3, 5);
            SzDuel_SetField(3, 6, 8);
            SzDuel_SetField(2, 6, 8);
            SzDuel_SetField(4, 6, 8);
            SzDuel_SetField(2, 5, 8);
            SzDuel_SetField(4, 5, 8);
            SzDuel_SetField(2, 4, 8);
            SzDuel_SetField(4, 4, 8);
            arg1->step++;
            return 0x20;
        }
        break;
    case 0x2C:
        SzDuel_SetPlayerCur(0, 3, 5);
        if (arg1->wait++ > 0x1E) {
            arg1->wait = 0;
            arg1->step++;
            return 0x80;
        }
        break;
    case 0x2D:
        if (func_0027F890(8, 1, 0) == 1) {
            SzDuel_SetWindowDisp(1);
            arg1->step++;
            arg1->wait = 0;
        }
        break;
    case 0x2E:
        func_0027FC20(0xA5F, 0xA5F, arg1);
        break;
    case 0x2F:
        if (func_0027F890(0x10, -1, 0) == 1) {
            SzDuel_MoveUnit(1, 1, 3, 4);
            arg1->step++;
        }
        break;
    case 0x30:
        if (func_0027F890(0x10, 1, 0) == 1 && func_0027FC20(0xA60, 0xA60, arg1) == 1) {
            SzDuel_SetWindowDisp(0);
        }
        break;
    case 0x31:
        if (func_0027F890(8, -1, 0) == 1) {
            SzDuel_DelUnit(1, 1);
            SzDuel_DelUnit(1, 2);
            SzDuel_DelUnit(1, 3);
            SzDuel_DelUnit(1, 4);
            SzDuel_DelUnit(1, 5);
            SzDuel_MoveUnit(0, 0, 3, 6);
            SzDuel_SetField(3, 6, 7);
            SzDuel_SetField(2, 6, 7);
            SzDuel_SetField(4, 6, 7);
            SzDuel_SetField(2, 5, 7);
            SzDuel_SetField(4, 5, 7);
            SzDuel_SetField(2, 4, 7);
            SzDuel_SetField(4, 4, 7);
            SzDuel_SetTurnCount(0x63);
            arg1->step++;
            return 0x20;
        }
        break;
    case 0x32:
        if (arg1->wait++ > 0x1E) {
            arg1->wait = 0;
            arg1->step++;
            SzDuel_SetPlayerCur(0, 3, 6);
        }
        break;
    case 0x33:
        if (func_0027F890(8, 1, 0) == 1) {
            SzDuel_SetWindowDisp(1);
            func_0027FC20(0xA61, 0xA61, arg1);
        }
        break;
    case 0x34:
        func_0027F630(arg1, 0xA, 0x800, 0x1E, -0xB4);
        if (arg1->timer++ > 0x3C) {
            SzDuel_CloseHandCursor();
            arg1->wait = 0;
            arg1->timer = 0;
            arg1->step++;
        }
        break;
    case 0x35:
        if (func_0027FC20(0xA62, 0xA65, arg1) == 1) {
            SzDuel_SetWindowDisp(0);
        }
        break;
    case 0x36:
        if (func_0027F890(8, -1, 0) == 1) {
            SzDuel_AddUnit(0, 6, 0, 0x39, 0);
            SzDuel_AddUnit(0, 5, 0, 0x38, 0);
            SzDuel_AddUnit(0, 0, 0, 0x37, 0);
            SzDuel_AddUnit(0, 1, 0, 0x36, 0);
            SzDuel_SetTurnCount(0);
            SzDuel_SetUnitStatus(0, 1, 4, 1);
            SzDuel_SetUnitStatus(0, 2, 4, 1);
            SzDuel_SetUnitStatus(0, 3, 4, 1);
            SzDuel_SetUnitStatus(0, 4, 4, 1);
            arg1->step++;
        }
        break;
    case 0x37:
        if (SzEffect_IsModelStandby2(1) != 0 && SzEffect_IsModelStandby2(2) != 0 && SzEffect_IsModelStandby2(3) != 0 && SzEffect_IsModelStandby2(4) != 0) {
            if (arg1->wait++ > 0x1E) {
                arg1->wait = 0;
                arg1->step++;
            }
        }
        break;
    case 0x38:
        if (func_0027F890(8, 1, 0) == 1) {
            SzDuel_SetWindowDisp(1);
            if (func_0027FC20(0xA66, 0xA6A, arg1) == 1) {
                SzDuel_SetWindowDisp(0);
            }
        }
        break;
    case 0x39:
        if (func_0027F890(0x10, -1, 0) == 1) {
            func_0027FAB0(arg1->text);
            TaTuto_FocusUnit_001745F0(0x3A);
            arg1->step++;
        }
        break;
    case 0x3A:
        if (func_0027F890(0x10, 1, 0) == 1) {
            SzDuel_OpenMsgPopup(0, -0x78, 0x50, SzDuel_GetMsgName(0x3A));
            if (arg1->wait++ > 0x3C) {
                arg1->wait = 0;
                arg1->step++;
            }
        }
        break;
    case 0x3B:
        func_0027FC20(0xA6B, 0xA6B, arg1);
        break;
    case 0x3C:
        if (func_0027F890(0x10, -1, 0) == 1) {
            SzDuel_MoveUnit(0, 1, 2, 6);
            SzDuel_MoveUnit(0, 2, 4, 6);
            SzDuel_MoveUnit(0, 3, 2, 5);
            SzDuel_MoveUnit(0, 4, 4, 5);
            func_0027FA30(arg1->text, 0);
            arg1->step++;
        }
        break;
    case 0x3D:
        if (func_0027F890(0x10, 1, 0) == 1 && func_0027FC20(0xA6C, 0xA6E, arg1) == 1) {
            SzDuel_SetWindowDisp(0);
            return 0x800;
        }
        break;
    case 0x3E:
        arg1->step++;
        return 0x800;
    case 0x3F:
        if (func_0027FC20(0xA6F, 0xA6F, arg1) == 1) {
            return -1;
        }
        break;
    default:
        return -1;
    }
    return 0;
}
