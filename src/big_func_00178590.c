#include "common.h"

typedef struct Tutorial_00178590 {
    u8 pad0[0x162];
    u16 timer;
    u8 pad164[0x3E];
    u16 step;
    u16 wait;
    u8 pad1A6[0xA];
    u8 text[1];
} Tutorial_00178590;

s32 func_00178590(s32 arg0, void *tutorial) {
    extern void func_00203C70();
    extern void func_00178320();
    extern void func_0027F630();
    extern void func_0027F700();
    extern s32 func_0027F890();
    extern void func_0027FA30();
    extern void func_0027FAB0();
    extern s32 func_0027FC20();
    Tutorial_00178590 *arg1 = tutorial;
    s32 x;
    s32 y;
    u16 flag = 0;
    u16 first;
    u16 last;
    u16 kind;
    s32 lo;
    s32 hi;
    s32 t;

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
        arg1->step = 2;
        break;
    case 0x1:
        if (func_001F5EC0(0) != 0) {
            if (func_001F5EC0(0x100) != 0) {
                arg1->step = 0xD0;
            }
        }
        break;
    case 0x2:
    case 0x7:
    case 0xB:
    case 0x11:
    case 0x13:
    case 0x18:
    case 0x24:
    case 0x31:
    case 0x33:
    case 0x35:
    case 0x3A:
    case 0x41:
    case 0x47:
    case 0x4E:
    case 0x52:
    case 0x57:
    case 0x59:
    case 0x5C:
    case 0x60:
    case 0x68:
    case 0x70:
    case 0x77:
    case 0x7A:
    case 0x7D:
    case 0x86:
    case 0x8D:
    case 0x97:
    case 0x9E:
    case 0xA8:
    case 0xAB:
    case 0xAF:
    case 0xB3:
    case 0xB7:
    case 0xBB:
    case 0xBF:
    case 0xC4:
    case 0xC7:
    case 0xCB:
    case 0xCF:
    case 0xD3:
    case 0xD5:
    case 0xD7:
    case 0xD9:
    case 0xDB:
    case 0xDE:
    case 0xE3:
    case 0xE6:
    case 0xEA:
    case 0xEC:
    case 0xEE:
    case 0xF1:
    case 0xF5:
    case 0xF9:
    case 0xFE:
    case 0x103:
    case 0x107:
    case 0x10A:
    case 0x110:
    case 0x114:
    case 0x116:
    case 0x11B:
    case 0x11F:
    case 0x121:
    case 0x123:
    case 0x126:
    case 0x12B:
    case 0x12F:
    case 0x132:
    case 0x136:
    case 0x139:
    case 0x13F:
    case 0x141:
        switch (arg1->step) {
        case 0x141:
            first = 0x1E4;
            last = 0x1E4;
            kind = 1;
            break;
        case 0x13F:
            first = 0x1E1;
            last = 0x1E3;
            kind = 6;
            break;
        case 0x139:
            first = 0x1E0;
            last = 0x1E0;
            kind = 0;
            break;
        case 0x136:
            first = 0x1DA;
            last = 0x1DF;
            kind = 0;
            break;
        case 0x132:
            first = 0x1D8;
            last = 0x1D9;
            kind = 1;
            break;
        case 0x12F:
            first = 0x1D3;
            last = 0x1D7;
            kind = 0;
            break;
        case 0x12B:
            first = 0x1CD;
            last = 0x1D2;
            kind = 3;
            break;
        case 0x126:
            first = 0x1CB;
            last = 0x1CC;
            kind = 3;
            break;
        case 0x123:
            first = 0x1CA;
            last = 0x1CA;
            kind = 0;
            break;
        case 0x121:
            first = 0x1C9;
            last = 0x1C9;
            kind = 0;
            break;
        case 0x11F:
            first = 0x1C8;
            last = 0x1C8;
            kind = 0;
            break;
        case 0x11B:
            first = 0x1C4;
            last = 0x1C7;
            kind = 3;
            break;
        case 0x116:
            first = 0x1C3;
            last = 0x1C3;
            kind = 5;
            break;
        case 0x114:
            first = 0x1C2;
            last = 0x1C2;
            kind = 4;
            break;
        case 0x110:
            first = 0x1C0;
            last = 0x1C1;
            kind = 3;
            break;
        case 0x10A:
            first = 0x1BC;
            last = 0x1BF;
            kind = 2;
            break;
        case 0x107:
            first = 0x1BA;
            last = 0x1BB;
            kind = 0;
            break;
        case 0x103:
            first = 0x1B9;
            last = 0x1B9;
            kind = 0;
            break;
        case 0xFE:
            first = 0x1B8;
            last = 0x1B8;
            kind = 1;
            break;
        case 0xF9:
            first = 0x1B7;
            last = 0x1B7;
            kind = 0;
            break;
        case 0xF5:
            first = 0x1B3;
            last = 0x1B6;
            kind = 0;
            break;
        case 0xF1:
            first = 0x1B1;
            last = 0x1B2;
            kind = 1;
            break;
        case 0xEE:
            first = 0x1B0;
            last = 0x1B0;
            kind = 0;
            break;
        case 0xEC:
            first = 0x1AE;
            last = 0x1AF;
            kind = 0;
            break;
        case 0xEA:
            first = 0x1AD;
            last = 0x1AD;
            kind = 0;
            break;
        case 0xE6:
            first = 0x1AC;
            last = 0x1AC;
            kind = 0;
            break;
        case 0xE3:
            first = 0x1AA;
            last = 0x1AB;
            kind = 0;
            break;
        case 0xDE:
            first = 0x1A8;
            last = 0x1A9;
            kind = 0;
            break;
        case 0xDB:
            first = 0x1A4;
            last = 0x1A7;
            kind = 0;
            break;
        case 0xD9:
            first = 0x1A0;
            last = 0x1A3;
            kind = 0;
            break;
        case 0xD7:
            first = 0x19E;
            last = 0x19F;
            kind = 0;
            break;
        case 0xD5:
            first = 0x19A;
            last = 0x19D;
            kind = 0;
            break;
        case 0xD3:
            first = 0x195;
            last = 0x199;
            kind = 0;
            break;
        case 0xCF:
            first = 0x193;
            last = 0x194;
            kind = 1;
            break;
        case 0xCB:
            first = 0x18C;
            last = 0x192;
            kind = 0;
            break;
        case 0xC7:
            first = 0x187;
            last = 0x18B;
            kind = 1;
            break;
        case 0xC4:
            first = 0x186;
            last = 0x186;
            kind = 0;
            break;
        case 0xBF:
            first = 0x185;
            last = 0x185;
            kind = 0;
            break;
        case 0xBB:
            first = 0x182;
            last = 0x184;
            kind = 0;
            break;
        case 0xB7:
            first = 0x17F;
            last = 0x181;
            kind = 0;
            break;
        case 0xB3:
            first = 0x17E;
            last = 0x17E;
            kind = 1;
            break;
        case 0xAF:
            first = 0x178;
            last = 0x17D;
            kind = 0;
            break;
        case 0xAB:
            first = 0x174;
            last = 0x177;
            kind = 1;
            break;
        case 0xA8:
            first = 0x173;
            last = 0x173;
            kind = 0;
            break;
        case 0x9E:
            first = 0x170;
            last = 0x172;
            kind = 0;
            break;
        case 0x97:
            first = 0x16F;
            last = 0x16F;
            kind = 1;
            break;
        case 0x8D:
            first = 0x16C;
            last = 0x16E;
            kind = 0;
            break;
        case 0x86:
            first = 0x168;
            last = 0x16B;
            kind = 1;
            break;
        case 0x7D:
            first = 0x166;
            last = 0x167;
            kind = 0;
            break;
        case 0x7A:
            first = 0x165;
            last = 0x165;
            kind = 0;
            break;
        case 0x77:
            first = 0x163;
            last = 0x164;
            kind = 0;
            break;
        case 0x70:
            first = 0x162;
            last = 0x162;
            kind = 1;
            break;
        case 0x68:
            first = 0x15F;
            last = 0x161;
            kind = 0;
            break;
        case 0x60:
            first = 0x15E;
            last = 0x15E;
            kind = 0;
            break;
        case 0x5C:
            first = 0x15A;
            last = 0x15D;
            kind = 1;
            break;
        case 0x59:
            first = 0x157;
            last = 0x159;
            kind = 0;
            break;
        case 0x57:
            first = 0x156;
            last = 0x156;
            kind = 0;
            break;
        case 0x52:
            first = 0x155;
            last = 0x155;
            kind = 0;
            break;
        case 0x4E:
            first = 0x151;
            last = 0x154;
            kind = 0;
            break;
        case 0x47:
            first = 0x14F;
            last = 0x150;
            kind = 1;
            break;
        case 0x41:
            first = 0x14D;
            last = 0x14E;
            kind = 0;
            break;
        case 0x3A:
            first = 0x14B;
            last = 0x14C;
            kind = 1;
            break;
        case 0x35:
            first = 0x146;
            last = 0x14A;
            kind = 0;
            break;
        case 0x33:
            first = 0x143;
            last = 0x145;
            kind = 0;
            break;
        case 0x31:
            first = 0x142;
            last = 0x142;
            kind = 0;
            break;
        case 0x24:
            first = 0x141;
            last = 0x141;
            kind = 1;
            break;
        case 0x18:
            first = 0x13E;
            last = 0x140;
            kind = 0;
            break;
        case 0x13:
            first = 0x13D;
            last = 0x13D;
            kind = 0;
            break;
        case 0x11:
            first = 0x139;
            last = 0x13C;
            kind = 0;
            break;
        case 0xB:
            first = 0x138;
            last = 0x138;
            kind = 0;
            break;
        case 0x7:
            first = 0x137;
            last = 0x137;
            kind = 0;
            break;
        case 0x2:
            first = 0x130;
            last = 0x136;
            kind = 0;
            break;
        default:
            first = 0x130;
            last = 0x130;
            kind = 0;
            break;
        }
        if (kind == 2) {
            func_0027F700(arg1, 0x1E, 3, 5);
        }
        if (kind == 5) {
            func_0027F700(arg1, 0x1E, 2, 6);
        }
        if (func_0027FC20(first + 0x9DC, last + 0x9DC, arg1) == 1) {
            switch (kind) {
            case 6:
                func_001DE7A0(0);
                return 0x20;
            case 5:
                arg1->wait = 0;
                arg1->timer = 0;
                return 0x800;
            case 4:
                return 0x8000;
            case 3:
                return 0x800;
            case 2:
                arg1->wait = 0;
                arg1->timer = 0;
                break;
            case 1:
                func_001DE7A0(0);
                break;
            }
        }
        break;
    case 0x3:
    case 0x4:
    case 0x5:
    case 0x6:
    case 0xF:
    case 0x12:
    case 0x17:
    case 0x22:
    case 0x23:
    case 0x36:
    case 0x37:
    case 0x42:
    case 0x43:
    case 0x44:
    case 0x45:
    case 0x46:
    case 0x4F:
    case 0x50:
    case 0x51:
    case 0x56:
    case 0x5A:
    case 0x5B:
    case 0x69:
    case 0x6A:
    case 0x6B:
    case 0x6C:
    case 0x6D:
    case 0x6E:
    case 0x6F:
    case 0x78:
    case 0x79:
    case 0x7B:
    case 0x7C:
    case 0x8F:
    case 0x92:
    case 0x94:
    case 0x95:
    case 0x96:
    case 0xA9:
    case 0xAA:
    case 0xB0:
    case 0xB1:
    case 0xB2:
    case 0xB8:
    case 0xB9:
    case 0xBA:
    case 0xBC:
    case 0xBD:
    case 0xBE:
    case 0xC0:
    case 0xC1:
    case 0xC2:
    case 0xC3:
    case 0xC5:
    case 0xC6:
    case 0xCC:
    case 0xCD:
    case 0xCE:
    case 0xD4:
    case 0xD6:
    case 0xD8:
    case 0xDA:
    case 0xE4:
    case 0xE5:
    case 0xEB:
    case 0xED:
    case 0x105:
    case 0x106:
    case 0x10B:
    case 0x10F:
    case 0x122:
    case 0x130:
    case 0x131:
    case 0x137:
    case 0x138:
    case 0x13B:
    case 0x13C:
    case 0x13D:
    case 0x13E:
        if (arg1->wait++ > 0xC) {
            arg1->wait = 0;
            switch (arg1->step++) {
            case 0xEB:
                return 8;
            case 0x13C:
                return 2;
            case 0x79:
            case 0xD4:
            case 0xE5:
            case 0xED:
            case 0x105:
            case 0x137:
            case 0x13E:
                return 0x10;
            case 0x3:
            case 0xB8:
                return 0x80;
            case 0x5:
            case 0x22:
            case 0x23:
            case 0x36:
            case 0x37:
            case 0x45:
            case 0x46:
            case 0x5A:
            case 0x5B:
            case 0x6E:
            case 0x6F:
            case 0x95:
            case 0x96:
            case 0xA9:
            case 0xAA:
            case 0xB0:
            case 0xB2:
            case 0xBA:
            case 0xC5:
            case 0xC6:
            case 0xCC:
            case 0xCE:
            case 0x10F:
            case 0x13B:
            case 0x13D:
                return 0x40;
            case 0x6:
            case 0x43:
            case 0x50:
            case 0x78:
            case 0xBD:
            case 0xC0:
            case 0xC1:
            case 0xC2:
            case 0xCD:
            case 0xE4:
                return 0x2000;
            case 0x6A:
            case 0x6B:
            case 0x6C:
            case 0xB1:
                return 0x8000;
            case 0x4:
            case 0xF:
            case 0x17:
            case 0x42:
            case 0x44:
            case 0x4F:
            case 0x51:
            case 0x56:
            case 0x69:
            case 0x6D:
            case 0x8F:
            case 0x92:
            case 0x94:
            case 0xB9:
            case 0xBE:
            case 0xC3:
                return 0x1000;
            case 0x12:
            case 0x7B:
            case 0x7C:
            case 0xD6:
            case 0xD8:
            case 0xDA:
            case 0x106:
            case 0x122:
            case 0x138:
                return 0x4000;
            case 0x10B:
            case 0x130:
            case 0x131:
                return 0x800;
            }
        }
        break;
    case 0x8:
    case 0x9:
    case 0xA:
    case 0xC:
    case 0xD:
    case 0xE:
    case 0x14:
    case 0x15:
    case 0x16:
    case 0x19:
    case 0x1A:
    case 0x1B:
    case 0x1C:
    case 0x1D:
    case 0x1E:
    case 0x1F:
    case 0x20:
    case 0x21:
    case 0x28:
    case 0x29:
    case 0x2A:
    case 0x2B:
    case 0x2C:
    case 0x2D:
    case 0x2E:
    case 0x2F:
    case 0x30:
    case 0x3E:
    case 0x3F:
    case 0x40:
    case 0x4B:
    case 0x4C:
    case 0x4D:
    case 0x53:
    case 0x54:
    case 0x55:
    case 0x61:
    case 0x62:
    case 0x63:
    case 0x64:
    case 0x65:
    case 0x66:
    case 0x67:
    case 0x74:
    case 0x75:
    case 0x76:
    case 0x7E:
    case 0x7F:
    case 0x80:
    case 0x81:
    case 0x82:
    case 0x83:
    case 0x84:
    case 0x85:
    case 0x8A:
    case 0x8B:
    case 0x8C:
    case 0x8E:
    case 0x90:
    case 0x91:
    case 0x93:
    case 0x9B:
    case 0x9C:
    case 0x9D:
    case 0x9F:
    case 0xA0:
    case 0xA1:
    case 0xA2:
    case 0xA3:
    case 0xA4:
    case 0xA5:
    case 0xA6:
    case 0xA7:
    case 0xDC:
    case 0xDD:
    case 0xE0:
    case 0xE1:
    case 0xE2:
    case 0xE7:
    case 0xE8:
    case 0xE9:
    case 0xEF:
    case 0xF0:
    case 0xF6:
    case 0xF7:
    case 0xF8:
    case 0xFA:
    case 0xFB:
    case 0xFC:
    case 0xFD:
    case 0xFF:
    case 0x108:
    case 0x10D:
    case 0x10E:
    case 0x118:
    case 0x119:
    case 0x11A:
    case 0x124:
    case 0x128:
    case 0x129:
    case 0x12A:
    case 0x13A:
        if (arg1->wait++ > 0x6) {
            arg1->wait = 0;
            switch (arg1->step++) {
            case 0x8:
            case 0x9:
            case 0xA:
            case 0x14:
            case 0x15:
            case 0x16:
            case 0x1E:
            case 0x1F:
            case 0x20:
            case 0x2B:
            case 0x2D:
            case 0x2E:
            case 0x2F:
            case 0x53:
            case 0x54:
            case 0x55:
            case 0x64:
            case 0x65:
            case 0x66:
            case 0x67:
            case 0x80:
            case 0x81:
            case 0x82:
            case 0x8E:
            case 0x90:
            case 0x91:
            case 0x93:
            case 0xA0:
            case 0xA2:
            case 0xA4:
            case 0xA6:
            case 0xFB:
            case 0xFC:
                return 0x2000;
            case 0xC:
            case 0xD:
            case 0xE:
            case 0x1C:
            case 0x1A:
            case 0x1B:
            case 0xF6:
                return 0x8000;
            case 0x19:
                return 0x4000;
            case 0x1D:
            case 0x21:
            case 0x29:
            case 0x2C:
            case 0x30:
            case 0x3F:
            case 0x4C:
            case 0x62:
            case 0x75:
            case 0x7F:
            case 0x83:
            case 0x8B:
            case 0x9C:
            case 0x9F:
            case 0xA1:
            case 0xA3:
            case 0xA5:
            case 0xA7:
            case 0xE1:
            case 0xF7:
            case 0x10E:
            case 0x119:
            case 0x129:
                return 0x1000;
            case 0x28:
            case 0x3E:
            case 0x4B:
            case 0x61:
            case 0x74:
            case 0x8A:
            case 0x9B:
            case 0xE0:
                return 0x80;
            case 0x2A:
            case 0x40:
            case 0x4D:
            case 0x63:
            case 0x76:
            case 0x84:
            case 0x85:
            case 0x8C:
            case 0x9D:
            case 0xE2:
            case 0x10D:
            case 0x118:
            case 0x11A:
            case 0x128:
            case 0x12A:
                return 0x40;
            case 0x7E:
            case 0xDC:
            case 0xDD:
            case 0xE7:
            case 0xE8:
            case 0xE9:
            case 0xEF:
            case 0xF0:
            case 0xFA:
            case 0xFF:
            case 0x108:
            case 0x124:
            case 0x13A:
                return 0x20;
            case 0xF8:
            case 0xFD:
                return 0x10;
            }
        }
        break;
    case 0x10:
    case 0x32:
    case 0x34:
    case 0x39:
    case 0x58:
        switch (arg1->step) {
        case 0x10:
            x = -0x9B;
            y = -0x55;
            break;
        case 0x32:
        case 0x39:
            x = -0xE8;
            y = -0x88;
            break;
        case 0x34:
        case 0x58:
            x = 0x68;
            y = -0x82;
            break;
        }
        func_0027F630(arg1, 0xA, 0x800, x, y);
        if (arg1->timer++ > 0x3C) {
            func_001E4E50();
            arg1->wait = 0;
            arg1->timer = 0;
            arg1->step++;
        }
        break;
    case 0x5D:
    case 0xAC:
    case 0xC8:
    case 0xD0:
    case 0xF2:
    case 0x133:
    case 0x140:
        if (func_0027F890(8, -1, 0) == 1) {
            arg1->wait = 0;
                switch (arg1->step++) {
            case 0x5D:
                func_001DFBB0(0, 1);
                func_001DE5E0(0, 4, 8);
                func_00178320((u16)(arg1->step - 1));
                func_001DE700(0, 1);
                func_001DE860(0, 3, 6);
                break;
            case 0xAC:
                func_001DFBB0(0, 1);
                func_001DE5E0(0, 4, 8);
                func_001DF580(0, 3, 4, 7, 0);
                func_001DF580(0, 4, 4, 0x126, 0);
                func_001E1E70(0, 1, 4, 1);
                func_001E1E70(0, 2, 4, 1);
                func_00178320((u16)(arg1->step - 1));
                func_001DE700(0, 1);
                break;
            case 0xC8:
                func_001DE5E0(0, 4, 8);
                func_001DF580(0, 2, 5, 0x11D, 0);
                func_001DF580(0, 4, 5, 5, 0);
                func_001DF580(0, 2, 6, 0x1A7, 0);
                func_001DF580(0, 4, 6, 0x141, 0);
                func_001E1E70(0, 1, 4, 1);
                func_001E1E70(0, 2, 4, 1);
                func_001E1E70(0, 3, 4, 1);
                func_001E1E70(0, 4, 4, 1);
                func_001E1E70(0, 5, 4, 1);
                break;
            case 0xD0:
                func_001DFBB0(0, 1);
                func_001DFBB0(0, 2);
                func_001DFBB0(0, 3);
                func_001DFBB0(0, 4);
                func_001DFBB0(0, 5);
                func_001DF580(0, 3, 3, 0x9C, 0);
                func_002172D0(0, 0x9C, 0xC);
                func_001E1E70(0, 1, 4, 1);
                func_00178320((u16)(arg1->step - 1));
                break;
            case 0xF2:
                func_001DFBB0(0, 1);
                func_001DF580(0, 2, 5, 0x321, 0);
                func_001DF580(0, 4, 5, 0x33B, 0);
                func_001E1E70(0, 6, 4, 1);
                func_001E1E70(0, 7, 4, 1);
                func_001DFD50(0, 0, 3, 6);
                break;
            case 0x133:
                func_001DFBB0(0, 6);
                func_001DF580(0, 2, 3, 0, 0);
                func_001DF580(0, 3, 3, 0, 0);
                func_001DF580(0, 4, 3, 0, 0);
                func_001DF580(0, 3, 4, 0x345, 0);
                func_001E1E70(0, 1, 4, 1);
                func_001E1E70(0, 2, 4, 1);
                func_001E1E70(0, 3, 4, 1);
                break;
            case 0x140:
                break;
            }
        }
        break;
    case 0x25:
    case 0x3B:
    case 0x48:
    case 0x71:
    case 0x87:
    case 0x98:
    case 0xB4:
    case 0x100:
    case 0x111:
    case 0x11C:
    case 0x12C:
        if (arg1->step == 0x111 || arg1->step == 0x11C || arg1->step == 0x12C) {
            func_001DE7A0(0);
        }
        if (func_0027F890(0x10, -1, 0) == 1) {
            arg1->wait = 0;
            switch (arg1->step++) {
            case 0x25:
                func_001DFBB0(0, 1);
                func_001DE5E0(0, 4, 8);
                func_00178320((u16)(arg1->step - 1));
                func_001DE700(0, 1);
                func_001DE860(0, 3, 6);
                break;
            case 0x3B:
                func_001DFBB0(0, 1);
                func_001DE5E0(0, 4, 8);
                func_00178320((u16)(arg1->step - 1));
                func_001DE700(0, 1);
                func_001DE860(0, 3, 6);
                break;
            case 0x48:
                func_001DFBB0(0, 1);
                func_001DE5E0(0, 4, 8);
                func_00178320((u16)(arg1->step - 1));
                func_001DE700(0, 1);
                func_001DE860(0, 3, 6);
                break;
            case 0x71:
                func_001DFBB0(0, 1);
                func_001DE5E0(0, 4, 8);
                func_00178320((u16)(arg1->step - 1));
                func_001DE700(0, 1);
                func_001DE860(0, 3, 6);
                break;
            case 0x87:
                func_001DFBB0(0, 1);
                func_001DFBB0(0, 6);
                func_001DE5E0(0, 4, 8);
                func_00178320((u16)(arg1->step - 1));
                func_001DE700(0, 1);
                func_001DE860(0, 3, 6);
                break;
            case 0x98:
                func_001DFBB0(0, 1);
                func_001DE5E0(0, 4, 8);
                func_00178320((u16)(arg1->step - 1));
                func_001DE700(0, 1);
                func_001DE860(0, 3, 6);
                break;
            case 0xB4:
                func_001DFBB0(0, 1);
                func_001DFBB0(0, 2);
                func_001DF580(0, 3, 5, 0x126, 0);
                func_001E1E70(0, 1, 4, 1);
                break;
            case 0x100:
                func_001DFBB0(0, 6);
                func_001DFBB0(0, 7);
                func_001DF580(0, 3, 5, 0x321, 0);
                func_001DF580(1, 3, 3, 3, 0);
                func_001E1E70(1, 1, 4, 1);
                break;
            case 0x111:
                func_001DFBB0(1, 1);
                func_001DF580(1, 3, 5, 3, 0);
                func_001DF580(0, 2, 6, 0x321, 0);
                func_001E1E70(1, 1, 4, 1);
                break;
            case 0x11C:
                func_001DFBB0(1, 1);
                func_001DF580(0, 0, 6, 0x33B, 0);
                func_001DF580(1, 3, 5, 3, 0);
                func_001DF580(1, 2, 4, 5, 0);
                func_001DF580(1, 2, 5, 0xC, 0);
                func_001E1E70(1, 1, 4, 1);
                func_001E1E70(1, 2, 4, 1);
                func_001E1E70(1, 3, 4, 1);
                break;
            case 0x12C:
                func_001DF580(0, 3, 3, 0x321, 0);
                func_001E1E70(0, 6, 4, 1);
                break;
            }
        }
        break;
    case 0x26:
    case 0x3C:
    case 0x49:
    case 0x5E:
    case 0x72:
    case 0x88:
    case 0x99:
        if (arg1->wait++ > 0x1E) {
            arg1->wait = 0;
            arg1->step++;
        }
        break;
    case 0xAD:
        func_001DE860(0, 4, 4);
        if ((func_001F5EC0(1) != 0) && (func_001F5EC0(2) != 0)) {
            if (arg1->wait++ > 0x1E) {
                arg1->wait = 0;
                arg1->step++;
            }
        }
        break;
    case 0xB5:
        func_001DE860(0, 3, 6);
        if (func_001F5EC0(1) != 0) {
            if (arg1->wait++ > 0x1E) {
                arg1->wait = 0;
                arg1->step++;
            }
        }
        break;
    case 0xC9:
        func_001DE860(0, 3, 6);
        if ((func_001F5EC0(2) != 0) && (func_001F5EC0(3) != 0) && (func_001F5EC0(4) != 0) && (func_001F5EC0(5) != 0)) {
            if (arg1->wait++ > 0x1E) {
                arg1->wait = 0;
                arg1->step++;
            }
        }
        break;
    case 0xD1:
        func_001DE860(0, 3, 3);
        if (func_001F5EC0(1) != 0) {
            if (arg1->wait++ > 0x1E) {
                arg1->wait = 0;
                arg1->step++;
            }
        }
        break;
    case 0xF3:
        func_001DE860(0, 3, 6);
        if (arg1->wait++ > 0x1E) {
            arg1->wait = 0;
            arg1->step++;
        }
        break;
    case 0x101:
        func_001DE860(0, 3, 3);
        if (func_001F5EC0(0x101) != 0) {
            if (arg1->wait++ > 0x1E) {
                arg1->wait = 0;
                arg1->step++;
            }
        }
        break;
    case 0x112:
        func_001DE860(0, 3, 6);
        if (func_001F5EC0(0x101) != 0) {
            if (arg1->wait++ > 0x1E) {
                arg1->wait = 0;
                arg1->step++;
            }
        }
        break;
    case 0x11D:
        func_001DE860(0, 3, 6);
        if ((func_001F5EC0(0x101) != 0) && (func_001F5EC0(0x102) != 0) && (func_001F5EC0(0x103) != 0)) {
            if (arg1->wait++ > 0x1E) {
                arg1->wait = 0;
                arg1->step++;
            }
        }
        break;
    case 0x12D:
        func_001DE860(0, 3, 3);
        if (arg1->wait++ > 0x1E) {
            arg1->wait = 0;
            arg1->step++;
        }
        break;
    case 0x134:
        func_001DE860(0, 3, 4);
        if ((func_001F5EC0(1) != 0) && (func_001F5EC0(2) != 0) && (func_001F5EC0(3) != 0)) {
            if (arg1->wait++ > 0x1E) {
                arg1->wait = 0;
                arg1->step++;
            }
        }
        break;
    case 0x5F:
    case 0xAE:
    case 0xCA:
    case 0xD2:
    case 0xF4:
    case 0x135:
        switch (arg1->step) {
        case 0x5F:
        case 0xAE:
        case 0xCA:
        case 0xD2:
        case 0xF4:
        case 0x135:
            flag = 1;
            break;
        }
        if (func_0027F890(8, 1, 1) == 1) {
            if (flag) {
                func_001DE7A0(1);
            }
            arg1->step++;
            arg1->wait = 0;
        }
        break;
    case 0x27:
    case 0x3D:
    case 0x4A:
    case 0x73:
    case 0x89:
    case 0x9A:
    case 0xB6:
    case 0x102:
    case 0x113:
    case 0x11E:
    case 0x12E:
        switch (arg1->step) {
        case 0x27:
        case 0x3D:
        case 0x4A:
        case 0x73:
        case 0x89:
        case 0x9A:
        case 0xB6:
        case 0x102:
        case 0x113:
        case 0x11E:
        case 0x12E:
            flag = 1;
            break;
        }
        if (func_0027F890(0x10, 1, 1) == 1) {
            if (flag) {
                func_001DE7A0(1);
            }
            arg1->step++;
            arg1->wait = 0;
        }
        break;
    case 0x38:
        arg1->step++;
        break;
    case 0xDF:
        lo = arg0 & 0xFF;
        t = arg0 & 0xFFFF;
        if (lo > 4) {
            return 0x8000;
        }
        if (lo <= 3) {
            return 0x2000;
        }
        hi = t >> 8;
        if (hi > 6) {
            return 0x1000;
        }
        if (hi <= 5) {
            return 0x4000;
        }
        arg1->step++;
        break;
    case 0x104:
        lo = arg0 & 0xFF;
        t = arg0 & 0xFFFF;
        if (lo > 3) {
            return 0x8000;
        }
        if (lo <= 2) {
            return 0x2000;
        }
        hi = t >> 8;
        if (hi > 5) {
            return 0x1000;
        }
        if (hi <= 4) {
            return 0x4000;
        }
        arg1->step++;
        break;
    case 0x117:
    case 0x127:
        lo = arg0 & 0xFF;
        t = arg0 & 0xFFFF;
        if (lo > 3) {
            return 0x2000;
        }
        if (lo <= 2) {
            return 0x8000;
        }
        hi = t >> 8;
        if (hi > 5) {
            return 0x4000;
        }
        if (hi <= 4) {
            return 0x1000;
        }
        arg1->step++;
        break;
    case 0x10C:
        lo = arg0 & 0xFF;
        t = arg0 & 0xFFFF;
        if (lo > 3) {
            return 0x2000;
        }
        if (lo <= 2) {
            return 0x8000;
        }
        hi = t >> 8;
        if (hi > 3) {
            return 0x4000;
        }
        if (hi <= 2) {
            return 0x1000;
        }
        arg1->step++;
        break;
    case 0x109:
        func_0027F700(arg1, 0x1E, 3, 5);
        if (arg1->wait++ > 0x3C) {
            arg1->wait = 0;
            arg1->step++;
        }
        break;
    case 0x115:
        func_0027F700(arg1, 0x1E, 2, 6);
        if (arg1->wait++ > 0x3C) {
            arg1->wait = 0;
            arg1->step++;
        }
        break;
    case 0x120:
        lo = arg0 & 0xFF;
        t = arg0 & 0xFFFF;
        if (lo > 0) {
            return 0x8000;
        }
        if (lo < 0) {
            return 0x2000;
        }
        hi = t >> 8;
        if (hi > 6) {
            return 0x1000;
        }
        if (hi <= 5) {
            return 0x4000;
        }
        func_001DE860(0, 0, 6);
        arg1->step++;
        return 0x10;
    case 0x125:
        lo = arg0 & 0xFF;
        t = arg0 & 0xFFFF;
        if (lo > 3) {
            return 0x8000;
        }
        if (lo <= 2) {
            return 0x2000;
        }
        hi = t >> 8;
        if (hi > 6) {
            return 0x1000;
        }
        if (hi <= 5) {
            return 0x4000;
        }
        arg1->step++;
        break;
    default:
        return -1;
    }
    return 0;
}
