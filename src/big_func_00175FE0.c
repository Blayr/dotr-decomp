#include "common.h"

typedef struct Tutorial_00175FE0 {
    u8 pad0[0x162];
    u16 timer;
    u8 pad164[0x3E];
    u16 step;
    u16 wait;
    u8 pad1A6[0xA];
    u8 text[1];
} Tutorial_00175FE0;

/* Runs one frame of tutorial lesson 3 (sets up its own board, hands and life points). `event` is the duel event
   (kind in bits 8-15). */
s32 TaTuto_Lesson3(s32 event, void *tutorial) {
    extern void SzPad_SetAnalogInfo();
    extern void TaTuto_FocusUnit_00175BA0();
    extern void func_00175E60();
    extern void func_0027F630();
    extern s32 func_0027F890();
    extern void func_0027FA30();
    extern void func_0027FAB0();
    extern s32 func_0027FC20();
    Tutorial_00175FE0 *arg1 = tutorial;
    u16 flag = 0;
    u16 kind;
    u16 first;
    u16 last;
    s32 i;
    s32 j;
    s32 x;
    s32 y;

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
    case 0x6:
    case 0x8:
    case 0x10:
    case 0x14:
    case 0x16:
    case 0x1F:
    case 0x23:
    case 0x28:
    case 0x2C:
    case 0x30:
    case 0x34:
    case 0x3A:
    case 0x3E:
    case 0x42:
    case 0x46:
    case 0x4B:
    case 0x51:
    case 0x57:
    case 0x5B:
    case 0x60:
    case 0x67:
    case 0x6B:
    case 0x6F:
    case 0x71:
    case 0x75:
    case 0x79:
    case 0x7B:
    case 0x7D:
    case 0x81:
    case 0x85:
    case 0x87:
    case 0x8E:
    case 0x9C:
    case 0xA1:
    case 0xA8:
    case 0xAC:
    case 0xB0:
    case 0xB1:
    case 0xB5:
    case 0xB9:
    case 0xBD:
    case 0xC2:
    case 0xC9:
    case 0xCD:
    case 0xD1:
    case 0xD6:
    case 0xDA:
    case 0xDC:
    case 0xE1:
    case 0xE5:
    case 0xE9:
    case 0xEB:
    case 0xEF:
    case 0xF3:
    case 0xF5:
    case 0xF9:
    case 0xFE:
    case 0x102:
    case 0x106:
    case 0x108:
    case 0x10D:
    case 0x114:
    case 0x119:
    case 0x11D:
    case 0x11F:
        kind = 0;
        switch (arg1->step) {
        case 0x2:
            first = 0x94;
            last = 0x95;
            kind = 1;
            break;
        case 0x6:
            first = 0x96;
            last = 0x96;
            kind = 2;
            break;
        case 0x8:
            first = 0x97;
            last = 0x99;
            kind = 2;
            break;
        case 0x10:
            first = 0x9A;
            last = 0x9C;
            kind = 1;
            break;
        case 0x14:
            first = 0x9D;
            last = 0x9F;
            kind = 2;
            break;
        case 0x16:
            first = 0xA0;
            last = 0xA0;
            break;
        case 0x1F:
            first = 0xA1;
            last = 0xA3;
            break;
        case 0x23:
            first = 0xA4;
            last = 0xA4;
            kind = 1;
            break;
        case 0x28:
            first = 0xA5;
            last = 0xA6;
            break;
        case 0x2C:
            first = 0xA7;
            last = 0xA7;
            kind = 1;
            break;
        case 0x30:
            first = 0xA8;
            last = 0xAA;
            kind = 1;
            break;
        case 0x34:
            first = 0xAB;
            last = 0xAC;
            break;
        case 0x3A:
            first = 0xAD;
            last = 0xAD;
            kind = 1;
            break;
        case 0x3E:
            first = 0xAE;
            last = 0xAF;
            break;
        case 0x42:
            first = 0xB0;
            last = 0xB1;
            kind = 1;
            break;
        case 0x46:
            first = 0xB2;
            last = 0xB2;
            break;
        case 0x4B:
            first = 0xB3;
            last = 0xB4;
            break;
        case 0x51:
            first = 0xB5;
            last = 0xB6;
            break;
        case 0x57:
            first = 0xB7;
            last = 0xB9;
            kind = 1;
            break;
        case 0x5B:
            first = 0xBA;
            last = 0xBC;
            break;
        case 0x60:
            first = 0xBD;
            last = 0xC0;
            break;
        case 0x67:
            first = 0xC1;
            last = 0xC5;
            kind = 1;
            break;
        case 0x6B:
            first = 0xC6;
            last = 0xC9;
            kind = 1;
            break;
        case 0x6F:
            first = 0xCA;
            last = 0xCA;
            break;
        case 0x71:
            first = 0xCB;
            last = 0xCC;
            break;
        case 0x75:
            first = 0xCD;
            last = 0xCF;
            kind = 1;
            break;
        case 0x79:
            first = 0xD0;
            last = 0xD2;
            break;
        case 0x7B:
            first = 0xD3;
            last = 0xD3;
            break;
        case 0x7D:
            first = 0xD4;
            last = 0xD4;
            break;
        case 0x81:
            first = 0xD5;
            last = 0xD5;
            kind = 1;
            break;
        case 0x85:
            first = 0xD6;
            last = 0xD6;
            break;
        case 0x87:
            first = 0xD7;
            last = 0xD8;
            break;
        case 0x8E:
            first = 0xD9;
            last = 0xDA;
            kind = 1;
            break;
        case 0x9C:
            first = 0xDB;
            last = 0xDB;
            kind = 1;
            break;
        case 0xA1:
            first = 0xDC;
            last = 0xDE;
            kind = 1;
            break;
        case 0xA8:
            first = 0xDF;
            last = 0xE1;
            kind = 1;
            break;
        case 0xAC:
            first = 0xE2;
            last = 0xE7;
            kind = 1;
            break;
        case 0xB0:
            first = 0xE8;
            last = 0xE8;
            kind = 3;
            break;
        case 0xB1:
            first = 0xE9;
            last = 0xE9;
            break;
        case 0xB5:
            first = 0xEA;
            last = 0xEB;
            kind = 1;
            break;
        case 0xB9:
            first = 0xEC;
            last = 0xEF;
            kind = 1;
            break;
        case 0xBD:
            first = 0xF0;
            last = 0xF0;
            break;
        case 0xC2:
            first = 0xF1;
            last = 0xF1;
            break;
        case 0xC9:
            first = 0xF2;
            last = 0xF6;
            kind = 1;
            break;
        case 0xCD:
            first = 0xF7;
            last = 0xFA;
            kind = 1;
            break;
        case 0xD1:
            first = 0xFB;
            last = 0xFD;
            break;
        case 0xD6:
            first = 0xFE;
            last = 0xFF;
            kind = 1;
            break;
        case 0xDA:
            first = 0x100;
            last = 0x102;
            break;
        case 0xDC:
            first = 0x103;
            last = 0x105;
            kind = 1;
            break;
        case 0xE1:
            first = 0x106;
            last = 0x106;
            kind = 1;
            break;
        case 0xE5:
            first = 0x107;
            last = 0x107;
            break;
        case 0xE9:
            first = 0x108;
            last = 0x109;
            break;
        case 0xEB:
            first = 0x10A;
            last = 0x10D;
            kind = 1;
            break;
        case 0xEF:
            first = 0x10E;
            last = 0x111;
            kind = 1;
            break;
        case 0xF3:
            first = 0x112;
            last = 0x114;
            break;
        case 0xF5:
            first = 0x115;
            last = 0x116;
            break;
        case 0xF9:
            first = 0x117;
            last = 0x117;
            break;
        case 0xFE:
            first = 0x118;
            last = 0x118;
            kind = 4;
            break;
        case 0x102:
            first = 0x119;
            last = 0x11E;
            kind = 1;
            break;
        case 0x106:
            first = 0x11F;
            last = 0x120;
            break;
        case 0x108:
            first = 0x121;
            last = 0x122;
            break;
        case 0x10D:
            first = 0x123;
            last = 0x124;
            break;
        case 0x114:
            first = 0x125;
            last = 0x128;
            kind = 5;
            break;
        case 0x119:
            first = 0x129;
            last = 0x12A;
            break;
        case 0x11D:
            first = 0x12B;
            last = 0x12E;
            kind = 1;
            break;
        case 0x11F:
            first = 0x12F;
            last = 0x12F;
            break;
        default:
            first = 0x94;
            last = 0x94;
            break;
        }
        if (func_0027FC20(first + 0x9DC, last + 0x9DC, arg1) == 1) {
            switch (kind) {
            case 1:
                SzDuel_SetWindowDisp(0);
                break;
            case 2:
                arg1->wait = 0;
                arg1->timer = 0;
                break;
            case 3:
                return 0x4000;
            case 4:
                arg1->step = 0x94;
                break;
            case 5:
                SzDuel_SetWindowDisp(0);
                return 0x20;
            }
        }
        break;
    case 0x3:
    case 0x11:
    case 0x2D:
    case 0x31:
    case 0x68:
    case 0x8F:
    case 0xA9:
    case 0xB6:
    case 0xBA:
    case 0xCA:
    case 0xDD:
    case 0xEC:
    case 0xFF:
    case 0x103:
    case 0x11E:
        if (func_0027F890(8, -1, 0) == 1) {
            arg1->wait = 0;
            switch (arg1->step++) {
            case 0x3:
                SzDuel_AddUnit(0, 3, 4, 0x9C, 0);
                SzDuel_AddUnit(0, 2, 4, 5, 0);
                SzDuel_AddUnit(0, 4, 4, 0xA0, 0);
                SzDuel_AddUnit(0, 2, 5, 0x141, 0);
                SzDuel_AddUnit(0, 4, 5, 0x20A, 0);
                SzDuel_AddUnit(0, 2, 6, 0x2AB, 0);
                SzDuel_AddUnit(0, 4, 6, 0x2AB, 0);
                SzDuel_AddUnit(0, 1, 6, 0x2AB, 0);
                SzDuel_AddUnit(0, 5, 6, 0x2AB, 0);
                SzDuel_AddUnit(0, 1, 5, 0x2AB, 0);
                SzDuel_SetUnitStatus(0, 1, 4, 1);
                SzDuel_SetUnitStatus(0, 2, 4, 1);
                SzDuel_SetUnitStatus(0, 3, 4, 1);
                SzDuel_SetUnitStatus(0, 4, 4, 1);
                SzDuel_SetUnitStatus(0, 5, 4, 1);
                break;
            case 0x11:
                for (i = 1; i < 0xB; i++) {
                    SzDuel_DelUnit(0, i);
                    SzDuel_DelUnit(1, i);
                }
                func_00175E60(1);
                SzDuel_CalcSummonPower(0, 4, 4);
                SzDuel_CalcSummonPower(1, 4, 4);
                SzDuel_SetHandPhase(0, 1);
                break;
            case 0x2D:
                for (i = 1; i < 0xB; i++) {
                    SzDuel_DelUnit(0, i);
                    SzDuel_DelUnit(1, i);
                }
                func_00175E60(1);
                SzDuel_CalcSummonPower(0, 4, 4);
                SzDuel_CalcSummonPower(1, 4, 4);
                SzDuel_SetTurnCount(0);
                break;
            case 0x31:
                SzDuel_AddUnit(0, 3, 4, 0x9C, 0);
                SzDuel_AddUnit(1, 3, 3, 0x2AB, 0);
                SzDuel_SetUnitStatus(0, 1, 4, 1);
                SzDuel_SetUnitStatus(1, 6, 4, 1);
                break;
            case 0x68:
                SzDuel_DelUnit(1, 1);
                SzDuel_DelUnit(0, 6);
                SzDuel_DelUnit(0, 7);
                for (i = 2; i <= 4; i++) {
                    for (j = 2; j <= 4; j++) {
                        SzDuel_SetField(i, j, 3);
                    }
                }
                break;
            case 0x8F:
                SzDuel_DelUnit(0, 1);
                SzDuel_AddUnit(0, 3, 5, 0x170, 0);
                for (i = 2; i <= 4; i++) {
                    for (j = 2; j <= 4; j++) {
                        SzDuel_SetField(i, j, 5);
                    }
                }
                SzDuel_SetUnitStatus(0, 1, 4, 1);
                return 0x20;
            case 0xA9:
                SzDuel_DelUnit(0, 1);
                for (i = 2; i <= 4; i++) {
                    for (j = 2; j <= 4; j++) {
                        SzDuel_SetField(i, j, 8);
                    }
                }
                break;
            case 0xB6:
                SzDuel_DelUnit(0, 1);
                for (i = 2; i <= 4; i++) {
                    for (j = 2; j <= 4; j++) {
                        SzDuel_SetField(i, j, 9);
                    }
                }
                break;
            case 0xBA:
                SzDuel_AddUnit(0, 2, 5, 0x9C, 0);
                SzDuel_AddUnit(0, 4, 5, 0x97, 0);
                SzDuel_SetUnitStatus(0, 1, 4, 1);
                SzDuel_SetUnitStatus(0, 2, 4, 1);
                break;
            case 0xCA:
                SzDuel_MoveUnit(0, 1, 3, 3);
                SzDuel_SetUnitStatus(0, 1, 0, 0);
                for (i = 2; i <= 4; i++) {
                    for (j = 2; j <= 4; j++) {
                        SzDuel_SetField(i, j, 7);
                    }
                }
                break;
            case 0xDD:
                SzDuel_MoveUnit(0, 1, 3, 4);
                SzDuel_SetUnitCurseRest(0, 1, 0);
                SzDuel_AddUnit(1, 3, 3, 0x1D, 0);
                SzDuel_SetUnitStatus(1, 1, 4, 1);
                SzDuel_SetPlayerCur(0, 3, 4);
                break;
            case 0xEC:
                SzDuel_DelUnit(1, 1);
                SzDuel_AddUnit(1, 2, 5, 3, 0);
                SzDuel_SetUnitStatus(1, 1, 4, 1);
                SzDuel_CalcLP(0, 4, 0x190);
                break;
            case 0xFF:
                SzDuel_DelUnit(1, 1);
                return 0x20;
            case 0x103:
                SzData_SetRankDirect(0, 0x3C, 0xC);
                SzData_SetRankDirect(1, 0x15, 0xC);
                break;
            case 0x11E:
                break;
            }
        }
        break;
    case 0x24:
    case 0x3B:
    case 0x43:
    case 0x58:
    case 0x6C:
    case 0x76:
    case 0x82:
    case 0x9D:
    case 0xA2:
    case 0xAD:
    case 0xCE:
    case 0xD7:
    case 0xE2:
    case 0xF0:
    case 0x116:
        if (arg1->step == 0x116) {
            SzDuel_SetWindowDisp(0);
        }
        if (func_0027F890(0x10, -1, 0) == 1) {
            arg1->wait = 0;
            switch (arg1->step++) {
            case 0x24:
                break;
            case 0x3B:
                SzDuel_DelUnit(0, 1);
                SzDuel_AddUnit(0, 3, 4, 0x9C, 0);
                SzDuel_AddUnit(1, 3, 3, 0x2AB, 0);
                SzDuel_SetUnitStatus(1, 6, 4, 1);
                break;
            case 0x43:
                SzDuel_DelUnit(0, 1);
                SzDuel_AddUnit(0, 2, 4, 0x2AB, 0);
                SzDuel_AddUnit(1, 2, 3, 3, 0);
                SzDuel_AddUnit(0, 3, 4, 0x2AB, 0);
                SzDuel_AddUnit(1, 3, 3, 3, 0);
                SzDuel_AddUnit(0, 4, 4, 0x2AB, 0);
                SzDuel_AddUnit(1, 4, 3, 3, 0);
                SzDuel_SetUnitStatus(0, 6, 4, 1);
                SzDuel_SetUnitStatus(0, 7, 4, 1);
                SzDuel_SetUnitStatus(0, 8, 4, 1);
                SzDuel_SetUnitStatus(1, 1, 4, 1);
                SzDuel_SetUnitStatus(1, 2, 4, 1);
                SzDuel_SetUnitStatus(1, 2, 3, 1);
                SzDuel_SetUnitStatus(1, 2, 5, 1);
                break;
            case 0x58:
                SzDuel_DelUnit(1, 2);
                SzDuel_DelUnit(1, 3);
                SzDuel_MoveUnit(1, 1, 3, 3);
                SzDuel_AddUnit(0, 2, 4, 0x2AB, 0);
                SzDuel_AddUnit(0, 4, 4, 0x2AB, 0);
                SzDuel_AddUnit(1, 2, 3, 0x2AB, 0);
                SzDuel_AddUnit(1, 4, 3, 0x2AB, 0);
                SzDuel_SetUnitStatus(0, 6, 4, 0);
                SzDuel_SetUnitStatus(0, 7, 4, 1);
                SzDuel_SetUnitStatus(1, 1, 0, 0);
                SzDuel_SetUnitStatus(1, 1, 4, 1);
                SzDuel_SetUnitStatus(1, 6, 4, 1);
                SzDuel_SetUnitStatus(1, 7, 3, 1);
                SzDuel_SetUnitStatus(1, 7, 5, 1);
                return 0x8000;
            case 0x6C:
                SzDuel_AddUnit(0, 3, 5, 0x9C, 0);
                SzDuel_SetUnitStatus(0, 1, 4, 1);
                SzDuel_SetPlayerCur(0, 3, 5);
                break;
            case 0x76:
                SzDuel_SetUnitStatus(0, 1, 0, 0);
                break;
            case 0x82:
                SzDuel_DelUnit(0, 1);
                SzDuel_AddUnit(0, 3, 3, 0x9C, 0);
                break;
            case 0x9D:
                func_0027FAB0(arg1->text);
                break;
            case 0xA2:
                func_0027FA30(arg1->text, 0);
                break;
            case 0xAD:
                SzDuel_AddUnit(0, 3, 5, 0x97, 0);
                SzDuel_AddUnit(1, 3, 4, 0x90, 0);
                SzDuel_SetUnitStatus(0, 1, 4, 1);
                SzDuel_SetUnitStatus(1, 1, 4, 1);
                SzDuel_SetPlayerCur(0, 3, 4);
                break;
            case 0xCE:
                Ta_SetUnitCurseRest(0, 1, 1);
                break;
            case 0xD7:
                Ta_SetUnitCurseRest(0, 1, 0xFF);
                break;
            case 0xE2:
                func_0027FA30(arg1->text, 0);
                break;
            case 0xF0:
                SzDuel_SetHandPhase(0, 1);
                SzDuel_SetDestinyFlag(0, 2);
                break;
            case 0x116:
                SzDuel_AddUnit(0, 3, 2, 0x9C, 0);
                break;
            }
        }
        break;
    case 0x117:
        SzDuel_SetPlayerCur(0, 3, 2);
        if (SzEffect_IsModelStandby2(1) != 0) {
            if (arg1->wait++ > 0x1E) {
                func_0027FAB0(arg1->text);
                arg1->wait = 0;
                arg1->step++;
            }
        }
        break;
    case 0x100:
        if (arg1->wait++ > 0x1E) {
            func_0027FAB0(arg1->text);
            arg1->wait = 0;
            arg1->step++;
            return 0x20;
        }
        break;
    case 0xED:
        SzDuel_SetPlayerCur(0, 3, 6);
        if (SzEffect_IsModelStandby2(0x101) != 0) {
            if (arg1->wait++ > 0x1E) {
                func_0027FAB0(arg1->text);
                arg1->wait = 0;
                arg1->step++;
            }
        }
        break;
    case 0x104:
        SzDuel_SetPlayerCur(0, 3, 6);
        if (arg1->wait++ > 0x1E) {
            func_0027FAB0(arg1->text);
            arg1->wait = 0;
            arg1->step++;
        }
        break;
    case 0xAE:
    case 0xDE:
    case 0xE3:
        if (SzEffect_IsModelStandby2(1) != 0 && SzEffect_IsModelStandby2(0x101) != 0) {
            if (arg1->wait++ > 0x1E) {
                func_0027FAB0(arg1->text);
                arg1->wait = 0;
                arg1->step++;
            }
        }
        break;
    case 0x4:
        if (SzEffect_IsModelStandby2(1) != 0 && SzEffect_IsModelStandby2(2) != 0 && SzEffect_IsModelStandby2(3) != 0 && SzEffect_IsModelStandby2(4) != 0 && SzEffect_IsModelStandby2(5) != 0) {
            if (arg1->wait++ > 0x1E) {
                arg1->wait = 0;
                arg1->step++;
            }
        }
        break;
    case 0x12:
    case 0x2E:
    case 0x3C:
    case 0x59:
    case 0x83:
    case 0xF1:
        if (arg1->wait++ > 0x1E) {
            arg1->wait = 0;
            if (arg1->step == 0x83) {
                SzDuel_SetPlayerCur(0, 3, 3);
            } else if (arg1->step == 0x3C || arg1->step == 0x59) {
                SzDuel_SetPlayerCur(0, 3, 4);
            } else {
                SzDuel_SetPlayerCur(0, 3, 6);
            }
            arg1->step++;
        }
        break;
    case 0x44:
        if (SzEffect_IsModelStandby2(0x101) != 0 && SzEffect_IsModelStandby2(0x102) != 0 && SzEffect_IsModelStandby2(0x103) != 0) {
            if (arg1->wait++ > 0x1E) {
                arg1->wait = 0;
                arg1->step++;
                SzDuel_SetPlayerCur(0, 3, 4);
            }
        }
        break;
    case 0x25:
        if (arg1->wait++ > 0x1E) {
            SzDuel_CalcSummonPower(0, 4, 0xC);
            SzDuel_CalcSummonPower(1, 4, 0xC);
            arg1->wait = 0;
            arg1->step++;
        }
        break;
    case 0x32:
    case 0x77:
    case 0x90:
    case 0xA3:
        if (SzEffect_IsModelStandby2(1) != 0) {
            if (arg1->wait++ > 0x1E) {
                arg1->wait = 0;
                arg1->step++;
            }
        }
        break;
    case 0x6D:
        if (SzEffect_IsModelStandby2(1) != 0) {
            if (arg1->wait++ > 0x1E) {
                arg1->wait = 0;
                arg1->step++;
            }
        }
        break;
    case 0xBB:
        SzDuel_SetPlayerCur(0, 3, 5);
        if (SzEffect_IsModelStandby2(1) != 0 && SzEffect_IsModelStandby2(2) != 0) {
            if (arg1->wait++ > 0x1E) {
                arg1->wait = 0;
                arg1->step++;
            }
        }
        break;
    case 0x9E:
        SzDuel_SetPlayerCur(0, 3, 5);
        if (arg1->wait++ > 0x1E) {
            func_0027FAB0(arg1->text);
            arg1->wait = 0;
            arg1->step++;
        }
        break;
    case 0x69:
    case 0xAA:
    case 0xB7:
    case 0xCB:
    case 0xCF:
    case 0xD8:
        SzDuel_SetPlayerCur(0, 3, 3);
        if (arg1->wait++ > 0x1E) {
            arg1->wait = 0;
            arg1->step++;
        }
        break;
    case 0x5:
    case 0x13:
    case 0x2F:
    case 0x33:
    case 0x3D:
    case 0x45:
    case 0x5A:
    case 0x6A:
    case 0x91:
    case 0x9B:
    case 0xAB:
    case 0xAF:
    case 0xB8:
    case 0xBC:
    case 0xCC:
    case 0xEE:
    case 0x101:
    case 0x105:
        switch (arg1->step) {
        case 0x5:
        case 0x13:
        case 0x2F:
        case 0x45:
        case 0x5A:
        case 0x6A:
        case 0x9B:
        case 0xAB:
        case 0xAF:
        case 0xB8:
        case 0xBC:
        case 0xCC:
        case 0xEE:
        case 0x101:
        case 0x105:
            break;
        case 0x33:
        case 0x3D:
            TaTuto_FocusUnit_00175BA0(0x9C);
            break;
        case 0x91:
            arg1->step = 0x9B;
            break;
        }
        if (func_0027F890(8, 1, 1) == 1) {
            SzDuel_SetWindowDisp(1);
            arg1->step++;
            arg1->wait = 0;
        }
        break;
    case 0x26:
    case 0x6E:
    case 0x78:
    case 0x84:
    case 0x9F:
    case 0xA4:
    case 0xD0:
    case 0xD9:
    case 0xDF:
    case 0xE4:
    case 0xF2:
    case 0x118:
        switch (arg1->step) {
        case 0x26:
        case 0x6E:
        case 0x78:
        case 0x84:
        case 0xA4:
        case 0xD0:
        case 0xD9:
        case 0xE4:
        case 0xF2:
        case 0x118:
            flag = 1;
            break;
        case 0x9F:
            flag = 0;
            TaTuto_FocusUnit_00175BA0(0x170);
            break;
        case 0xDF:
            flag = 0;
            TaTuto_FocusUnit_00175BA0(0x1D);
            break;
        }
        if (func_0027F890(0x10, 1, 1) == 1) {
            if (flag) {
                SzDuel_SetWindowDisp(1);
            }
            arg1->step++;
            arg1->wait = 0;
            if (arg1->step == 0xD1) {
                arg1->step = 0x92;
            }
        }
        break;
    case 0x7:
    case 0x15:
    case 0x1E:
    case 0x22:
    case 0x27:
    case 0x2B:
    case 0x70:
    case 0x7A:
    case 0x92:
    case 0xDB:
    case 0xE8:
    case 0xF4:
    case 0x107:
        switch (arg1->step) {
        case 0x7:
            x = -0xE8;
            y = -0x78;
            break;
        case 0x15:
        case 0x1E:
        case 0x22:
        case 0x27:
        case 0x2B:
            x = -0xE8;
            y = -0x88;
            break;
        case 0x70:
            x = 0xA0;
            y = 0xC8;
            break;
        case 0x7A:
            x = 0xD2;
            y = 0xB4;
            break;
        case 0x92:
        case 0xDB:
            x = 0xD8;
            y = 0xD2;
            break;
        case 0xE8:
            x = -0x28;
            y = 0xD2;
            break;
        case 0xF4:
            x = 0xB4;
            y = 0xB4;
            break;
        case 0x107:
            x = 0x78;
            y = 0xB4;
            break;
        default:
            y = 0;
            x = 0;
            break;
        }
        func_0027F630(arg1, 0xA, 0x800, x, y);
        if (arg1->timer++ > 0x3C) {
            SzDuel_CloseHandCursor();
            arg1->wait = 0;
            arg1->timer = 0;
            arg1->step++;
        }
        break;
    case 0x9:
    case 0xA:
    case 0xB:
    case 0xC:
    case 0xD:
    case 0xE:
    case 0xF:
    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1A:
    case 0x1B:
    case 0x1C:
    case 0x1D:
    case 0x20:
    case 0x21:
    case 0x29:
    case 0x2A:
    case 0x35:
    case 0x36:
    case 0x37:
    case 0x38:
    case 0x39:
    case 0x3F:
    case 0x40:
    case 0x41:
    case 0x47:
    case 0x48:
    case 0x49:
    case 0x4A:
    case 0x4C:
    case 0x4D:
    case 0x4E:
    case 0x4F:
    case 0x50:
    case 0x52:
    case 0x53:
    case 0x54:
    case 0x55:
    case 0x56:
    case 0x5C:
    case 0x5D:
    case 0x5E:
    case 0x5F:
    case 0x61:
    case 0x62:
    case 0x63:
    case 0x64:
    case 0x65:
    case 0x66:
    case 0x72:
    case 0x73:
    case 0x74:
    case 0x7C:
    case 0x7E:
    case 0x7F:
    case 0x80:
    case 0x86:
    case 0xA5:
    case 0xA6:
    case 0xA7:
    case 0xB2:
    case 0xB3:
    case 0xB4:
    case 0xBE:
    case 0xBF:
    case 0xC0:
    case 0xC1:
    case 0xC3:
    case 0xC4:
    case 0xC5:
    case 0xC6:
    case 0xC7:
    case 0xC8:
    case 0xD2:
    case 0xD3:
    case 0xD4:
    case 0xD5:
    case 0xE6:
    case 0xE7:
    case 0xEA:
    case 0xF6:
    case 0xF7:
    case 0xF8:
    case 0xFA:
    case 0xFB:
    case 0xFC:
    case 0xFD:
    case 0x10F:
    case 0x11A:
    case 0x11B:
    case 0x11C:
        if (arg1->wait++ > 0xC) {
            arg1->wait = 0;
            switch (arg1->step++) {
            case 0x9:
            case 0x17:
            case 0xF6:
                return 0x80;
            case 0xA:
            case 0x18:
            case 0x35:
            case 0x36:
            case 0x38:
            case 0x40:
            case 0x49:
            case 0x4F:
            case 0x55:
            case 0x5E:
            case 0x65:
            case 0x73:
            case 0x7E:
            case 0x7F:
            case 0xA6:
            case 0xB3:
            case 0xC0:
            case 0xC7:
            case 0xE7:
            case 0xF7:
            case 0x11B:
                return 0x1000;
            case 0xB:
            case 0xE:
            case 0xF:
            case 0x19:
            case 0x1C:
            case 0x1D:
            case 0x37:
            case 0x39:
            case 0x3F:
            case 0x41:
            case 0x48:
            case 0x4A:
            case 0x4E:
            case 0x50:
            case 0x54:
            case 0x56:
            case 0x5D:
            case 0x5F:
            case 0x64:
            case 0x66:
            case 0x72:
            case 0x74:
            case 0x7C:
            case 0x80:
            case 0x86:
            case 0xA5:
            case 0xA7:
            case 0xB2:
            case 0xB4:
            case 0xBF:
            case 0xC1:
            case 0xC6:
            case 0xC8:
            case 0xE6:
            case 0xEA:
            case 0xF8:
            case 0x11A:
            case 0x11C:
                return 0x40;
            case 0xC:
            case 0xD:
            case 0x1A:
            case 0x1B:
            case 0x4C:
            case 0x52:
            case 0x62:
            case 0x63:
            case 0xC4:
            case 0xC5:
            case 0xFA:
            case 0xFB:
            case 0xFC:
            case 0xFD:
                return 0x2000;
            case 0x47:
            case 0x5C:
            case 0xBE:
                return 0x8000;
            case 0x4D:
            case 0x53:
            case 0x61:
            case 0xC3:
                return 0x4000;
            case 0x20:
            case 0x21:
            case 0x29:
            case 0x2A:
            case 0xD2:
            case 0xD3:
            case 0xD4:
            case 0xD5:
            case 0x10F:
                return 0x800;
            }
        }
        break;
    case 0x88:
    case 0x89:
    case 0x8A:
    case 0x8B:
    case 0x8C:
    case 0x109:
    case 0x10A:
    case 0x10B:
    case 0x10C:
    case 0x10E:
    case 0x110:
    case 0x111:
    case 0x112:
    case 0x113:
    case 0x115:
        if (arg1->wait++ > 0x3C) {
            arg1->wait = 0;
            switch (arg1->step++) {
            case 0x88:
            case 0x8A:
            case 0x8C:
                return 2;
            case 0x89:
            case 0x8B:
                return 1;
            case 0x109:
            case 0x110:
                return 0x10;
            case 0x10A:
            case 0x10B:
            case 0x10C:
            case 0x111:
            case 0x112:
            case 0x113:
                return 0x4000;
            case 0x10E:
                return 0x20;
            case 0x115:
                return 0x800;
            }
        }
        break;
    case 0xA0:
        SzDuel_OpenMsgPopup(0, -0x78, 0x50, SzDuel_GetMsgName(0x170));
        if (arg1->wait++ > 0x3C) {
            SzDuel_SetWindowDisp(1);
            arg1->wait = 0;
            arg1->step++;
        }
        break;
    case 0xE0:
        SzDuel_OpenMsgPopup(0, -0x78, 0x50, SzDuel_GetMsgName(0x1D));
        if (arg1->wait++ > 0x3C) {
            arg1->wait = 0;
            arg1->step++;
        }
        break;
    case 0x8D:
        arg1->step++;
        break;
    case 0x93:
        arg1->step = 0xD1;
        break;
    case 0x94:
        arg1->step++;
        return 0x20;
    case 0x95:
        arg1->step = 0xFF;
        return 0x20;
    default:
        return -1;
    }
    return 0;
}
