#include "common.h"

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


s32 func_001747D0(s32 arg0, void *tutorial) {
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

void TaTuto_FocusUnit_00175BA0(s32 arg0) {
    s32 rot[4];
    f32 vec[4];
    s32 unit;
    s32 x;
    s32 d;

    SzView_FreeRequest(0, 0);
    switch (arg0) {
    case 0x170:
        unit = SzDuel_GetUnit(0, 1);
        SzEffect_GetModelRot2(1, rot);
        rot[0] += 63;
        x = *(s32 *)(unit + 0x30);
        d = 0x47FF - x;
        if (d < 0) {
            d = 0x147FE - x;
        }
        rot[1] += d;
        rot[2] += 0x1000;
        SzView_IV2V(rot, vec);
        vec[0] += SzEffect_GetRadius2(1);
        SzView_ReqCamera(0, 0, 7, 0, SzDuel_GetUnitModelID(0, 1), NULL);
        SzView_ReqCamera(0, 0, 4, 0, 0, vec);
        break;
    case 0x1D:
        unit = SzDuel_GetUnit(1, 1);
        SzEffect_GetModelRot2(0x101, rot);
        rot[0] += 63;
        x = *(s32 *)(unit + 0x30);
        d = 0x47FF - x;
        if (d < 0) {
            d = 0x147FE - x;
        }
        rot[1] += d;
        rot[2] += 0x1000;
        SzView_IV2V(rot, vec);
        vec[0] += SzEffect_GetRadius2(0x101);
        SzView_ReqCamera(0, 0, 7, 0, SzDuel_GetUnitModelID(1, 1), NULL);
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

INCLUDE_ASM("asm/nonmatchings/main_017", func_00175E60);
