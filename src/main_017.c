#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_017", func_001745F0);

typedef struct Tutorial_001747D0 {
    u8 pad0[0x162];
    u16 timer;
    u8 pad164[0x3E];
    u16 step;
    u16 wait;
    u8 pad1A6[0xA];
    u8 text[1];
} Tutorial_001747D0;

void func_001745F0(s32 arg0);
void func_0027F630(Tutorial_001747D0 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 func_0027F890(s32 arg0, s32 arg1, s32 arg2);
void func_0027FA30(void *arg0, s32 arg1);
void func_0027FAB0(void *arg0);
s32 func_0027FC20(s32 arg0, s32 arg1, Tutorial_001747D0 *arg2);

s32 func_001747D0(s32 arg0, void *tutorial) {
    extern void func_00203C70();
    extern s32 func_001E1900();
    Tutorial_001747D0 *arg1 = tutorial;
    if (func_001DE780() != 0) {
        func_001DE7E0(1);
    } else {
        func_001DE7E0(0);
    }
    func_00203C70(0, 0, 0x80);
    func_00203C70(0, 1, 0x80);
    func_00203C70(0, 2, 0x80);
    func_00203C70(0, 3, 0x80);
    if (func_00203A40(0, 0, 0x800) != 0) {
        return -2;
    }
    switch (arg1->step) {
    case 0x0:
        func_001E4E60(1);
        func_001DE7A0(1);
        arg1->step = 2;
        break;
    case 0x1:
        if (func_001F5EC0(0) != 0) {
            if (func_001F5EC0(0x100) != 0) {
                arg1->step++;
            }
        }
        break;
    case 0x2:
        if (func_0027FC20(0xA48, 0xA4A, arg1) == 1) {
            func_001DE7A0(0);
        }
        break;
    case 0x3:
        if (func_0027F890(8, -1, 0) == 1) {
            func_0027FAB0(arg1->text);
            func_001DF490(0, 4, 0xFA0);
            func_001DF490(1, 4, 0x3E8);
            func_001DF580(0, 3, 1, 0x9C, 0);
            func_001E1E70(0, 1, 4, 1);
            arg1->step++;
            arg1->wait = 0;
        }
        break;
    case 0x4:
        func_001DE860(0, 3, 1);
        if (func_001F5EC0(1) != 0) {
            if (arg1->wait++ > 0x1E) {
                arg1->wait = 0;
                arg1->step++;
            }
        }
        break;
    case 0x5:
        func_001745F0(0x9C);
        func_001DE7A0(1);
        if (func_0027F890(8, 1, 1) == 1) {
            func_001DE7A0(1);
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
            func_001E4E50();
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
            func_001DE7A0(0);
        }
        break;
    case 0xD:
        if (func_0027F890(8, -1, 0) == 1) {
            func_0027FAB0(arg1->text);
            func_001DFBB0(0, 1);
            func_001DF490(0, 4, 0x1F4);
            func_001DF490(1, 4, 0x1F4);
            func_001DF580(0, 3, 4, 0x9C, 0);
            func_001DF580(1, 3, 3, 0x15A, 0);
            func_001E1E70(0, 1, 4, 1);
            func_001E1E70(1, 1, 4, 1);
            arg1->step++;
            arg1->wait = 0;
        }
        break;
    case 0xE:
        func_001DE860(0, 3, 4);
        if (func_001F5EC0(1) != 0 && func_001F5EC0(0x101) != 0) {
            if (arg1->wait++ > 0x1E) {
                arg1->wait = 0;
                arg1->step++;
            }
        }
        break;
    case 0xF:
        func_001745F0(0x9C);
        func_001DE7A0(1);
        if (func_0027F890(8, 1, 1) == 1) {
            func_001DE7A0(1);
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
            func_001DE7A0(0);
        }
        break;
    case 0x1B:
        if (func_0027F890(8, -1, 0) == 1) {
            func_0027FAB0(arg1->text);
            func_001DFBB0(0, 1);
            func_001DFBB0(1, 1);
            func_001DFD50(0, 0, 3, 4);
            func_001DF490(0, 4, 0xFA0);
            func_001DF490(1, 4, 0xFA0);
            arg1->step++;
            arg1->wait = 0;
        }
        break;
    case 0x1C:
        func_001DE860(0, 3, 4);
        if (arg1->wait++ > 0x1E) {
            arg1->wait = 0;
            arg1->step++;
        }
        break;
    case 0x1D:
        func_001DE7A0(1);
        if (func_0027F890(8, 1, 1) == 1) {
            func_001DE7A0(1);
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
            func_001DF580(1, 3, 3, 3, 0);
            func_001DF580(1, 2, 3, 0x11D, 0);
            func_001DF580(1, 4, 3, 0x20A, 0);
            func_001DF580(1, 2, 4, 0x277, 0);
            func_001DF580(1, 4, 4, 0x15, 0);
            func_001DF580(1, 2, 5, 0x2AB, 0);
            func_001DF580(1, 3, 5, 0x2AB, 0);
            func_001DF580(1, 4, 5, 0x2AB, 0);
            func_001E1E70(1, 1, 4, 1);
            func_001E1E70(1, 2, 4, 1);
            func_001E1E70(1, 3, 4, 1);
            func_001E1E70(1, 4, 4, 1);
            func_001E1E70(1, 5, 4, 1);
            arg1->step++;
            arg1->wait = 0;
            return 0x20;
        }
        break;
    case 0x22:
        if (func_001F5EC0(0x101) != 0 && func_001F5EC0(0x102) != 0 && func_001F5EC0(0x103) != 0 && func_001F5EC0(0x104) != 0 && func_001F5EC0(0x105) != 0) {
            if (arg1->wait++ > 0x1E) {
                arg1->wait = 0;
                arg1->step++;
                func_00260740(0);
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
            func_001DE7A0(0);
        }
        break;
    case 0x25:
        if (func_0027F890(8, -1, 0) == 1) {
            func_001DFBB0(1, 6);
            func_001DFBB0(1, 7);
            func_001DFBB0(1, 8);
            func_001E1AF0(1, 1, -1, 0);
            func_001E1900(1, 1, 0);
            func_001E1AF0(1, 2, -1, 0);
            func_001E1900(1, 2, 0);
            func_001E1AF0(1, 3, -1, 0);
            func_001E1900(1, 3, 0);
            func_001E1AF0(1, 4, -1, 0);
            func_001E1900(1, 4, 0);
            func_001E1AF0(1, 5, -1, 0);
            func_001E1900(1, 5, 0);
            func_001DFD50(1, 1, 6, 0);
            func_001DFD50(1, 2, 6, 1);
            func_001DFD50(1, 3, 6, 2);
            func_001DFD50(1, 4, 6, 3);
            func_001DFD50(1, 5, 6, 4);
            func_001DFD50(0, 0, 0, 6);
            arg1->step++;
            arg1->wait = 0;
        }
        break;
    case 0x26:
        func_001DE860(0, 0, 6);
        if (arg1->wait++ > 0x1E) {
            arg1->wait = 0;
            arg1->step++;
            func_0027FFC0(0);
            return 0x80;
        }
        break;
    case 0x27:
        if (func_0027F890(8, 1, 0) == 1) {
            func_001DE7A0(1);
            arg1->step++;
            arg1->wait = 0;
        }
        break;
    case 0x28:
        func_0027FC20(0xA5D, 0xA5D, arg1);
        break;
    case 0x29:
        if (func_0027F890(0x10, -1, 0) == 1) {
            func_001E1900(1, 1, 0x80);
            func_001E1AF0(1, 1, 1, 0x80);
            func_001E1900(1, 2, 0x80);
            func_001E1AF0(1, 2, 1, 0x80);
            func_001E1900(1, 3, 0x80);
            func_001E1AF0(1, 3, 1, 0x80);
            func_001DFD50(1, 1, 0, 5);
            func_001DFD50(1, 2, 1, 5);
            func_001DFD50(1, 3, 1, 6);
            arg1->step++;
        }
        break;
    case 0x2A:
        if (func_0027F890(0x10, 1, 0) == 1 && func_0027FC20(0xA5E, 0xA5E, arg1) == 1) {
            func_001DE7A0(0);
        }
        break;
    case 0x2B:
        if (func_0027F890(0x10, -1, 0) == 1) {
            func_001DFD50(1, 1, 6, 0);
            func_001DFD50(1, 2, 6, 1);
            func_001DFD50(1, 3, 6, 2);
            func_001DFD50(0, 0, 3, 5);
            func_001E2220(3, 6, 8);
            func_001E2220(2, 6, 8);
            func_001E2220(4, 6, 8);
            func_001E2220(2, 5, 8);
            func_001E2220(4, 5, 8);
            func_001E2220(2, 4, 8);
            func_001E2220(4, 4, 8);
            arg1->step++;
            return 0x20;
        }
        break;
    case 0x2C:
        func_001DE860(0, 3, 5);
        if (arg1->wait++ > 0x1E) {
            arg1->wait = 0;
            arg1->step++;
            return 0x80;
        }
        break;
    case 0x2D:
        if (func_0027F890(8, 1, 0) == 1) {
            func_001DE7A0(1);
            arg1->step++;
            arg1->wait = 0;
        }
        break;
    case 0x2E:
        func_0027FC20(0xA5F, 0xA5F, arg1);
        break;
    case 0x2F:
        if (func_0027F890(0x10, -1, 0) == 1) {
            func_001DFD50(1, 1, 3, 4);
            arg1->step++;
        }
        break;
    case 0x30:
        if (func_0027F890(0x10, 1, 0) == 1 && func_0027FC20(0xA60, 0xA60, arg1) == 1) {
            func_001DE7A0(0);
        }
        break;
    case 0x31:
        if (func_0027F890(8, -1, 0) == 1) {
            func_001DFBB0(1, 1);
            func_001DFBB0(1, 2);
            func_001DFBB0(1, 3);
            func_001DFBB0(1, 4);
            func_001DFBB0(1, 5);
            func_001DFD50(0, 0, 3, 6);
            func_001E2220(3, 6, 7);
            func_001E2220(2, 6, 7);
            func_001E2220(4, 6, 7);
            func_001E2220(2, 5, 7);
            func_001E2220(4, 5, 7);
            func_001E2220(2, 4, 7);
            func_001E2220(4, 4, 7);
            func_001DE570(0x63);
            arg1->step++;
            return 0x20;
        }
        break;
    case 0x32:
        if (arg1->wait++ > 0x1E) {
            arg1->wait = 0;
            arg1->step++;
            func_001DE860(0, 3, 6);
        }
        break;
    case 0x33:
        if (func_0027F890(8, 1, 0) == 1) {
            func_001DE7A0(1);
            func_0027FC20(0xA61, 0xA61, arg1);
        }
        break;
    case 0x34:
        func_0027F630(arg1, 0xA, 0x800, 0x1E, -0xB4);
        if (arg1->timer++ > 0x3C) {
            func_001E4E50();
            arg1->wait = 0;
            arg1->timer = 0;
            arg1->step++;
        }
        break;
    case 0x35:
        if (func_0027FC20(0xA62, 0xA65, arg1) == 1) {
            func_001DE7A0(0);
        }
        break;
    case 0x36:
        if (func_0027F890(8, -1, 0) == 1) {
            func_001DF580(0, 6, 0, 0x39, 0);
            func_001DF580(0, 5, 0, 0x38, 0);
            func_001DF580(0, 0, 0, 0x37, 0);
            func_001DF580(0, 1, 0, 0x36, 0);
            func_001DE570(0);
            func_001E1E70(0, 1, 4, 1);
            func_001E1E70(0, 2, 4, 1);
            func_001E1E70(0, 3, 4, 1);
            func_001E1E70(0, 4, 4, 1);
            arg1->step++;
        }
        break;
    case 0x37:
        if (func_001F5EC0(1) != 0 && func_001F5EC0(2) != 0 && func_001F5EC0(3) != 0 && func_001F5EC0(4) != 0) {
            if (arg1->wait++ > 0x1E) {
                arg1->wait = 0;
                arg1->step++;
            }
        }
        break;
    case 0x38:
        if (func_0027F890(8, 1, 0) == 1) {
            func_001DE7A0(1);
            if (func_0027FC20(0xA66, 0xA6A, arg1) == 1) {
                func_001DE7A0(0);
            }
        }
        break;
    case 0x39:
        if (func_0027F890(0x10, -1, 0) == 1) {
            func_0027FAB0(arg1->text);
            func_001745F0(0x3A);
            arg1->step++;
        }
        break;
    case 0x3A:
        if (func_0027F890(0x10, 1, 0) == 1) {
            func_001E42C0(0, -0x78, 0x50, func_001DE210(0x3A));
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
            func_001DFD50(0, 1, 2, 6);
            func_001DFD50(0, 2, 4, 6);
            func_001DFD50(0, 3, 2, 5);
            func_001DFD50(0, 4, 4, 5);
            func_0027FA30(arg1->text, 0);
            arg1->step++;
        }
        break;
    case 0x3D:
        if (func_0027F890(0x10, 1, 0) == 1 && func_0027FC20(0xA6C, 0xA6E, arg1) == 1) {
            func_001DE7A0(0);
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

INCLUDE_ASM("asm/nonmatchings/main_017", func_00175BA0);

INCLUDE_ASM("asm/nonmatchings/main_017", func_00175E60);
