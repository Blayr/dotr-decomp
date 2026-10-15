#include "common.h"

#define B310_ATTACK(kind, last)                                                              \
    if (func_00271F90(arg0, arg1, arg2, arg3, 0xB) != 0) {                                  \
        func_00260490(pos & 0xFF, pos >> 8, 0, func_00271740(9, side), 1, 1, 0xB);          \
        arg4[0] = 0xFE;                                                                      \
        arg4[1] = 0;                                                                         \
        arg4[2] = side << 8;                                                                 \
        arg4[3] = 0x10;                                                                      \
        return 1;                                                                            \
    }                                                                                        \
    if (func_00267700(arg0, arg1) != 0) {                                                    \
        return 0;                                                                            \
    }                                                                                        \
    arg4[0] = kind;                                                                          \
    arg4[1] = list[i];                                                                       \
    arg4[2] = (arg0 << 8) | arg1;                                                            \
    arg4[3] = last;                                                                          \
    return 0x101;

s32 func_0024B310(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 *arg4, s32 arg5) {
    extern s32 func_001E07C0();
    s32 side;
    s32 count;
    s32 maskA;
    u32 *info;
    s32 y;
    s32 pos;
    s32 maskB;
    s32 i;
    s32 ret;
    s32 list[5];
    s32 cell;
    s32 col;
    s32 row;
    s32 x;

    side = func_0024DE70(arg0, arg1);
    maskA = 0;
    maskB = 0;
    if (arg1 == 0) {
        return 0;
    }
    if (!(arg5 & 0xFFFF)) {
        if (func_00271A40((side == 0) ? 1 : 0, arg2, arg3) != 0) {
            if ((func_001E0700(arg0, arg1) >> 5) == 0) {
                if ((func_00271740(0x10, (side == 0) ? 1 : 0) != 0) && (func_002720F0((side == 0) ? 1 : 0, func_001E0700(arg0, arg1) & 0x1F) != 0)) {
                    maskA = func_0024C780(0U, arg0, arg1);
                }
                if ((func_00271740(0xF, (side == 0) ? 1 : 0) != 0) && (func_00272050((side == 0) ? 1 : 0, func_001E0700(arg0, arg1) & 0x1F) != 0)) {
                    maskB = func_0024C780(0U, arg0, arg1);
                }
                if (maskA > 0 || maskB > 0) {
                    arg4[0] = 0x71;
                    arg4[1] = maskA;
                    arg4[2] = maskB;
                    arg4[3] = 0x80000000;
                    return 0x101;
                }
            }
            maskA = 0;
            if ((func_00271740(0xD, (side == 0) ? 1 : 0) != 0) && (func_001E2100(arg0, arg1, 2) == 0) && (func_001E2100(arg0, arg1, 4) == 0)) {
                maskA = func_0024C780(0U, arg0, arg1);
            }
            if (maskA > 0) {
                arg4[0] = 0x71;
                arg4[1] = 0;
                arg4[2] = 0;
                arg4[3] = maskA | 0x80000000;
                return 0x10201;
            }
        }
    }
    info = func_00250740(arg0, arg1, 1);
    if (info != NULL && (*info >> 8) == 7) {
        return 0;
    }
    if (func_00266DF0(0xF) > 0) {
        return 0;
    }
    count = 0;
    for (i = 0; i < 5; i++) {
        list[i] = -1;
    }
    for (x = 0; x < 7; x++) {
        for (y = 0; y < 7; y++) {
            cell = func_001E3790(x, y);
            if (cell >= 0) {
                row = cell >> 8;
                col = cell & 0xFF;
                if (side != func_0024DE70(row, col)
                    && (((x < arg2) ? arg2 : x) - ((arg2 < x) ? arg2 : x)) + (((y < arg3) ? arg3 : y) - ((arg3 < y) ? arg3 : y)) < 2
                    && (func_001E0700(row, col) >> 5) == 3) {
                    if (func_0024DE70(arg0, arg1) != func_0024DE70(row, col)) {
                        if (((arg5 >> 16) & 1) != 1 || func_001E2100(row, col, 4) != 0) {
                            list[count] = cell;
                            count++;
                        }
                    }
                }
            }
        }
    }
    if (count == 0) {
        return 0;
    }
    ret = func_0026AB80(0, 0x2E);
    if (ret >= 0) {
        arg4[0] = 0x66;
        arg4[1] = 1;
        arg4[2] = ret;
        arg4[3] = 0;
        return 1;
    }
    func_0024C330(list, 0, func_00250860(0, count - 1));
    pos = func_001E1090(side, 0);
    for (i = 0; i < count; i++) {
        info = func_00250740(list[i] >> 8, list[i] & 0xFF, 0);
        switch (func_001E07C0(list[i] >> 8, list[i] & 0xFF)) {
        case 0:
            B310_ATTACK(0x2C, info[1])
        case 1:
            B310_ATTACK(0x2C, info[1])
        case 2:
            B310_ATTACK(0x2C, info[1])
        case 3:
            B310_ATTACK(0x2C, info[1])
        case 4:
            B310_ATTACK(0x2C, info[1])
        case 5:
            B310_ATTACK(0x2C, info[1])
        case 6:
            if ((func_001E0700(arg0, arg1) >> 5) == 0 && func_002509E0(arg0, arg1, arg2, arg3) < 0x3E9) {
                B310_ATTACK(0x2D, 0)
            }
            break;
        case 7:
            if ((func_001E0700(arg0, arg1) >> 5) == 0 && func_002509E0(arg0, arg1, arg2, arg3) < 0x5DD) {
                B310_ATTACK(0x2D, 0)
            }
            break;
        case 8:
            if ((func_001E0700(arg0, arg1) >> 5) == 0 && func_002509E0(arg0, arg1, arg2, arg3) < 0x7D1) {
                B310_ATTACK(0x2D, 0)
            }
            break;
        case 9:
            if ((func_001E0700(arg0, arg1) >> 5) == 0 && func_002509E0(arg0, arg1, arg2, arg3) < 0xBB9) {
                B310_ATTACK(0x2D, 0)
            }
            break;
        case 10:
            if ((func_001E0700(arg0, arg1) >> 5) == 0 && func_002509E0(arg0, arg1, arg2, arg3) < 0xFA1) {
                B310_ATTACK(0x2D, 0)
            }
            break;
        case 11:
            B310_ATTACK(0x2E, 0)
        case 12:
            if ((func_001E0700(arg0, arg1) >> 5) != 0) {
                B310_ATTACK(0x2D, 0)
            }
            break;
        }
    }
    return 0;
}

void func_0024C330(s32 *list, s32 left, s32 right) {
    s32 cost;
    s32 i;
    s32 last;

    if (left < right) {
        func_0024C450(list, left, (left + right) >> 1);
        last = left;
        for (i = left + 1; i <= right; i++) {
            cost = func_001E13C0(list[i] >> 8, list[i] & 0xFF);
            if (cost > func_001E13C0(list[left] >> 8, list[left] & 0xFF)) {
                func_0024C450(list, ++last, i);
            }
        }
        func_0024C450(list, left, last);
        func_0024C330(list, left, last);
        func_0024C330(list, last + 1, right);
    }
}

void func_0024C450(s32 *arg0, s32 arg1, s32 arg2) {
    s32 temp_a0;
    s32 *temp_a1;
    s32 *temp_a2;

    temp_a1 = arg0 + arg1;
    temp_a2 = arg0 + arg2;
    temp_a0 = *temp_a1;
    *temp_a1 = *temp_a2;
    *temp_a2 = temp_a0;
}

s32 func_0024C480(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    switch (func_001E07C0()) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        if ((func_001E0700(arg2, arg3) >> 5) == 0) {
            return (func_00271F90(arg2, arg3, arg4, arg5, 0xB) != 0) ? 0 : 1;
        }
        break;
    case 6:
        if ((func_001E0700(arg2, arg3) >> 5) == 0 && func_002509E0(arg2, arg3, arg4, arg5) < 0x1F5) {
            return (func_00271F90(arg2, arg3, arg4, arg5, 0xB) != 0) ? 0 : 1;
        }
        break;
    case 7:
        if ((func_001E0700(arg2, arg3) >> 5) == 0 && func_002509E0(arg2, arg3, arg4, arg5) < 0x3E9) {
            return (func_00271F90(arg2, arg3, arg4, arg5, 0xB) != 0) ? 0 : 1;
        }
        break;
    case 8:
        if ((func_001E0700(arg2, arg3) >> 5) == 0 && func_001E0290(arg2, arg3, 0) < 0x5DD) {
            return (func_00271F90(arg2, arg3, arg4, arg5, 0xB) != 0) ? 0 : 1;
        }
        break;
    case 9:
        if ((func_001E0700(arg2, arg3) >> 5) == 0 && func_002509E0(arg2, arg3, arg4, arg5) < 0x7D1) {
            return (func_00271F90(arg2, arg3, arg4, arg5, 0xB) != 0) ? 0 : 1;
        }
        break;
    case 10:
        if ((func_001E0700(arg2, arg3) >> 5) == 0 && func_002509E0(arg2, arg3, arg4, arg5) < 0xBB9) {
            return (func_00271F90(arg2, arg3, arg4, arg5, 0xB) != 0) ? 0 : 1;
        }
        break;
    case 11:
        return 1;
    case 12:
        if ((func_001E0700(arg2, arg3) >> 5) != 0) {
            return (func_00271F90(arg2, arg3, arg4, arg5, 0xB) != 0) ? 0 : 1;
        }
        break;
    default:
        return 0;
    }
    return 0;
}

s32 func_0024C780(u32 arg0, s32 arg1, s32 arg2) {
    if (arg1 == 0) {
        return (arg0 & 0x7FF) | (((arg0 >> 0xB) | (1 << (0xA - arg2))) << 0xB);
    }
    return arg0 | (1 << (0xA - arg2));
}

s32 func_0024C7D0(u32 arg0, s32 arg1, s32 arg2) {
    s32 temp_a0;
    s32 temp_s2;

    if (arg1 == 0) {
        temp_a0 = 0x15 - arg2;
        return ((((u32) (arg0 >> 0xB) >> (0xA - arg2)) & ~1) << temp_a0) | (arg0 & func_0024C870(temp_a0));
    }
    temp_s2 = arg0 & ~func_0024C870(0xB - arg2);
    return temp_s2 | (arg0 & func_0024C870(0xA - arg2));
}

s32 func_0024C870(s32 arg0) {
    extern s32 func_001A2858(s32, s32);
    extern s32 func_001A2EB0(s32);
    extern s32 func_001A2F68(s32);
    s32 temp_s0;
    s32 var_s0;
    s32 var_s1;

    var_s1 = 0;
    var_s0 = 0;
    for (; var_s1 < arg0; var_s1++) {
        temp_s0 = func_001A6BE8(0x4000000000000000LL, func_001A2EB0(var_s1));
        var_s0 = func_001A2F68(func_001A2858(func_001A2EB0(var_s0), temp_s0));
    }
    return var_s0;
}

void func_0024C910(s32 arg0, s32 arg1, s16 *arg2) {
    s16 *var_s0;
    s32 criteria;
    s32 player;
    s32 var_s3;
    u16 player_bits;
    s32 var_v1;

    var_s3 = 1;
    var_s0 = arg2;
    criteria = arg1;
    player = arg0;
    player_bits = (u16)(player << 8);
    do {
        if ((func_001DF540(player, var_s3) != 0) && (func_0024DD80(player, func_0024DE70(player, var_s3), criteria) == 1)) {
            *var_s0 = player_bits | var_s3;
            var_s0++;
        }
        var_s3 += 1;
    } while (var_s3 < 0xB);
    var_s3 = 1;
    do {
        if (func_001DF540((player == 0) ? 1 : 0, var_s3) != 0) {
            if (func_0024DD80(player, func_0024DE70((player == 0) ? 1 : 0, var_s3), criteria) == 1) {
                if (player == 0) {
                    var_v1 = 1;
                } else {
                    var_v1 = 0;
                }
                *var_s0 = var_s3 | (var_v1 << 8);
                var_s0++;
            }
        }
        var_s3 += 1;
    } while (var_s3 < 0xB);
}

INCLUDE_ASM("asm/nonmatchings/main_072", func_0024CA40);

s32 func_0024DD80(s32 arg0, s32 arg1, s32 arg2) {
    switch (arg2) {
    case 0:
        return 0;
    case 1:
        return (arg0 == arg1) ? 1 : 0;
    case 2:
        if (arg0 == ((arg1 == 0) ? 1 : 0)) {
            return 1;
        }
        return 0;
    case 3:
        return 1;
    default:
        return 0;
    }
}

s32 func_0024DE20(s32 arg0, s32 arg1) {
    switch (arg1) {
    case 1:
        return arg0;
    case 2:
        return (arg0 == 0) ? 1 : 0;
    default:
        return -1;
    }
}

s32 func_0024DE70(s32 arg0, s32 arg1) {
    if (func_001E2100(arg0, arg1, 1) != 0) {
        return (arg0 == 0) ? 1 : 0;
    }
    return arg0;
}

s32 func_0024DEB0(s32 arg0, void *arg1) {
    if (((s32) *((u8 *)arg1 + 0x3E) >> 5) != 0 ||
        *((u8 *)arg1 + 0x45) == 0) {
        return 0;
    }
    return func_0024DF80(arg0, arg1);
}

s32 func_0024DF00(s32 arg0, s32 arg1, s32 arg2) {
    if ((func_001E0700(arg1, arg2) >> 5) != 0 || arg2 == 0) {
        return 0;
    }
    return func_0024DF80(arg0, (void *)func_001DF540(arg1, arg2));
}

struct jp_6537d {
    unsigned char bKind;
    unsigned char bKindOfs;
    unsigned char bAttr : 4;
    unsigned char bLevel : 4;
    unsigned char bDeckCost;
    unsigned short wEffIdx;
    unsigned short wEffNo;
    unsigned short wAP : 13;
    unsigned short fPermanent : 1;
    unsigned short fGetPasswd : 1;
    unsigned short fGetRecycle : 1;
    unsigned short wDP : 13;
    unsigned short fGetSlot : 1;
    unsigned short fGetFever : 1;
    unsigned short fAlternate : 1;
    unsigned char abPasswd[8];
};
struct jp_65648 {
    unsigned int dwID;
    unsigned int dwParam;
};
struct jp_65767;
struct jp_64b6d {
    struct jp_6537d *pConstInfo;
    struct jp_65767 *pCardReq;
    struct jp_65648 aVarEffIdx[5];
    int nRotY;
    short sOfsX;
    short sOfsZ;
    short sVarAP;
    short sVarDP;
    unsigned short wCardNo;
    unsigned char bVarKind;
    unsigned char bVarAttr;
    unsigned char bMapX;
    unsigned char bMapZ;
    unsigned char bPosX;
    unsigned char bPosZ;
    unsigned char bOwner;
    unsigned char bID;
    unsigned char bModelID;
    unsigned char bSummonOrder;
    unsigned char bSummonCost;
    unsigned char bCurseRest;
    unsigned char bSpellRest;
    unsigned char bDelayCount;
    unsigned char bMovable;
    unsigned char bDarkRate;
    unsigned char bCtlModeC;
    unsigned char bCtlModeM;
    unsigned char bCtlGoalC;
    unsigned char bCtlGoalM;
    unsigned char bCtlRateC;
    unsigned char bCtlRateM;
    unsigned char bOpenRate;
    unsigned char bDefenseRate;
    int nCtlFlipC : 2;
    int nCtlFlipM : 2;
    int nOpenFlip : 2;
    int nDefenseFlip : 2;
    int fFinish : 1;
    int fRevolt : 1;
    int fOpen : 1;
    int fDefense : 1;
    int fOpenF : 1;
    int fDefenseF : 1;
    int fPickup : 1;
    int fCardBusy : 1;
    int fModelBusy : 1;
    int fCardColBusy : 1;
    int fHand : 1;
    int fCurse : 1;
    int nEffHandle : 6;
};

int func_0024DF80(int land, void *vInfo_v)
{
    struct jp_64b6d * vInfo = vInfo_v;
    int kind;
    int ret;

    if ((vInfo->bVarKind >> 5) != 0) {
        return 0;
    }
    kind = vInfo->bVarKind & 0x1f;
    switch (land) {
    case 9:
        if (kind == 20) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 7:
    case 8:
        ret = 0;
        break;
    case 6:
        if (func_002492F0(vInfo->wCardNo) != 0) {
            ret = 1;
        } else {
            ret = 2;
        }
        break;
    case 3:
        switch (kind) {
        case 3:
        case 4:
            ret = 1;
            break;
        case 1:
            ret = 2;
            break;
        default:
            ret = 0;
            break;
        }
        break;
    case 0:
        switch (kind) {
        case 4:
        case 5:
        case 9:
        case 17:
        case 19:
            ret = 1;
            break;
        case 7:
            ret = 2;
            break;
        default:
            ret = 0;
            break;
        }
        break;
    case 2:
        switch (kind) {
        case 0:
        case 6:
        case 8:
        case 15:
            ret = 1;
            break;
        case 2:
            ret = 2;
            break;
        default:
            ret = 0;
            break;
        }
        break;
    case 1:
        switch (kind) {
        case 2:
        case 10:
        case 14:
        case 18:
            ret = 1;
            break;
        case 19:
        case 12:
        case 13:
        case 16:
            ret = 2;
            break;
        default:
            ret = 0;
            break;
        }
        break;
    case 4:
        switch (kind) {
        case 12:
        case 13:
        case 15:
        case 16:
            ret = 1;
            break;
        case 14:
        case 17:
            ret = 2;
            break;
        default:
            ret = 0;
            break;
        }
        break;
    case 5:
        switch (kind) {
        case 2:
        case 1:
        case 7:
            ret = 1;
            break;
        case 8:
            ret = 2;
            break;
        default:
            ret = 0;
            break;
        }
        break;
    default:
        ret = 0;
        break;
    }
    return ret;
}

s32 func_0024E220(s32 arg0, s32 arg1) {
    s32 index;
    s32 result;
    u8 filter;
    s32 high;
    s32 low;

    filter = arg1;
    for (index = 0; index < 8; index++) {
        if ((result = func_0024E410(arg0, index)) < 0) {
            continue;
        }
        if (!filter) {
            if (func_001E3790(result & 0xFF, result >> 8) < 0) {
                return result;
            }
        } else {
            low = result & 0xFF;
            high = result >> 8;
            if (func_001E22B0(low, high) != 8 &&
                func_001E3790(low, high) < 0) {
                return result;
            }
        }
    }
    return -1;
}

s32 func_0024E300(s32 arg0, s32 arg1, s32 arg2) {
    s32 index;
    s32 count;
    s32 value;
    s32 mode;
    s32 high;
    s32 low;

    mode = arg2 & 0xFF;
    index = 0;
    count = 0;
    do {
        if ((value = func_0024E410(arg0, index)) < 0) {
            continue;
        }
        if (mode == 0) {
            if (func_001E3790(value & 0xFF, value >> 8) >= 0) {
                continue;
            }
            if (arg1 == count) {
                return value;
            }
            count++;
        } else {
            low = value & 0xFF;
            high = value >> 8;
            if ((func_001E22B0(low, high) != 8) && (func_001E3790(low, high) < 0)) {
                if (arg1 == count) {
                    return value;
                }
                count++;
            }
        }
    } while (++index < 8);
    return -1;
}

s32 func_0024E410(s32 arg0, u32 arg1) {
    u32 pos;
    u32 next;
    u32 row;

    pos = func_001E1090(arg0, 0);
    switch (arg0) {
    case 0:
        switch (arg1) {
        case 0:
            return (((pos >> 8) - 1) << 8) | (pos & 0xFF);
        case 1:
            next = (pos >> 8) + 1;
            return (next < 7) ? ((next << 8) | (pos & 0xFF)) : -1;
        case 2:
            next = (pos & 0xFF) + 1;
            return (next < 7) ? (((pos >> 8) << 8) | next) : -1;
        case 3:
            return ((pos >> 8) << 8) | ((pos & 0xFF) - 1);
        case 4:
            next = (pos & 0xFF) + 1;
            return (next < 7) ? ((((pos >> 8) - 1) << 8) | next) : -1;
        case 5:
            return (((pos >> 8) - 1) << 8) | ((pos & 0xFF) - 1);
        case 6:
            next = (pos & 0xFF) + 1;
            if (next < 7) {
                row = (pos >> 8) + 1;
                if (row < 7) {
                    return (row << 8) | next;
                }
            }
            return -1;
        case 7:
            next = (pos >> 8) + 1;
            return (next < 7) ? ((next << 8) | ((pos & 0xFF) - 1)) : -1;
        default:
            return -1;
        }
    case 1:
        switch (arg1) {
        case 0:
            next = (pos >> 8) + 1;
            return (next < 7) ? ((next << 8) | (pos & 0xFF)) : -1;
        case 1:
            return (((pos >> 8) - 1) << 8) | (pos & 0xFF);
        case 2:
            return ((pos >> 8) << 8) | ((pos & 0xFF) - 1);
        case 3:
            next = (pos & 0xFF) + 1;
            return (next < 7) ? (((pos >> 8) << 8) | next) : -1;
        case 4:
            next = (pos >> 8) + 1;
            return (next < 7) ? ((next << 8) | ((pos & 0xFF) - 1)) : -1;
        case 5:
            next = (pos & 0xFF) + 1;
            if (next < 7) {
                row = (pos >> 8) + 1;
                if (row < 7) {
                    return (row << 8) | next;
                }
            }
            return -1;
        case 6:
            return (((pos >> 8) - 1) << 8) | ((pos & 0xFF) - 1);
        case 7:
            next = (pos & 0xFF) + 1;
            return (next < 7) ? ((((pos >> 8) - 1) << 8) | next) : -1;
        default:
            return -1;
        }
    default:
        return -1;
    }
}

s32 func_0024E780(s32 arg0, u8 arg1) {
    s32 count = 0;
    s32 index;
    s32 end;

    switch (arg1) {
    case 0:
        index = 0;
        end = 11;
        break;
    case 1:
        index = 0;
        end = 6;
        break;
    case 2:
        index = 6;
        end = 11;
        break;
    case 3:
        index = 1;
        end = 11;
        break;
    case 4:
        index = 1;
        end = 6;
        break;
    default:
        return -1;
    }

    for (; index < end; index++) {
        if (func_001DF540(arg0, index) != 0) {
            count++;
        }
    }
    return count;
}

typedef struct {
    s32 unused;
    s32 first;
    s32 second;
} Masks_0024E880;

void func_0024E880(void *arg0, s32 *arg1) {
    Masks_0024E880 *masks = arg0;
    s32 temp_v1;
    s32 var_t3;

    masks->first = 0;
    masks->second = 0;
    var_t3 = 0;
    while ((temp_v1 = *arg1) < 0) {
        if (((temp_v1 & 0xFF) + ((temp_v1 >> 8) * 7)) < 0x1D) {
            masks->first |= 1 << (0x1C - var_t3);
        } else {
            masks->second |= 1 << (0x15 - (var_t3 - 0x1D));
        }
        arg1++;
        var_t3 += 1;
    }
}

s32 func_0024E910(s32 arg0) {
    s32 count = 0;
    s32 bit = 0;

    do {
        if ((((u32) arg0 >> bit) & 1) == 1) {
            count += 1;
        }
        bit += 1;
    } while (bit < 0x16);
    return count;
}

s32 func_0024E950(s32 arg0, s32 arg1, s32 arg2) {
    s32 x;
    s32 y;
    s32 nextY;

    x = arg0 & 0xFF;
    y = arg0 >> 8;
    switch (arg2) {
    case 0:
        x -= arg1;
        if (x >= 0) {
            return (y << 8) | x;
        }
        break;
    case 1:
        nextY = y - arg1;
        if (nextY < 0) {
            break;
        }
        return x | (nextY << 8);
    case 2:
        x += arg1;
        if (x >= 7) {
            break;
        }
        return (y << 8) | x;
    case 3:
        nextY = y + arg1;
        if (nextY >= 7) {
            break;
        }
        return x | (nextY << 8);
    default:
        return -1;
    }
    return -1;
}

s32 func_0024EA10(s32 arg0, u32 arg1) {
    u32 var_v0;

    if ((arg0 >> 8) == 0) {
        var_v0 = ((arg1 >> 0xB) >> (0xA - (arg0 & 0xFF))) & 1;
    } else {
        var_v0 = (arg1 >> (0xA - (arg0 & 0xFF))) & 1;
    }
    return var_v0;
}

s32 func_0024EA60(void) {
    return 0;
}

s32 func_0024EA70(s32 arg0, s32 arg1) {
    switch (arg0) {
    case 0:
        if (arg1 == 1) {
            return -1;
        }
        return (arg1 == 4) ? 1 : 0;
    case 1:
        if (arg1 == 5) {
            return -1;
        }
        return (arg1 == 0) ? 1 : 0;
    case 2:
        if (arg1 == 4) {
            return -1;
        }
        return (arg1 == 3) ? 1 : 0;
    case 3:
        if (arg1 == 2) {
            return -1;
        }
        return (arg1 == 5) ? 1 : 0;
    case 4:
        if (arg1 == 0) {
            return -1;
        }
        return (arg1 == 2) ? 1 : 0;
    case 5:
        if (arg1 == 3) {
            return -1;
        }
        return (arg1 == 1) ? 1 : 0;
    default:
        return 0;
    }
}

s32 func_0024EBD0(s32 arg0) {
    s32 count;
    s32 result;

    count = func_0024E910(arg0);
    if (count == 0) {
        return -1;
    }
    result = func_0024EC50(arg0, func_0019A5C8() % count);
    if (result >= 0) {
        return result;
    }
    return -1;
}

s32 func_0024EC50(s32 mask, s32 ordinal) {
    s32 index;
    s32 count;

    index = 0;
    count = 0;
    do {
        if (((mask >> (21 - index)) & 1) == 1) {
            if (count == ordinal) {
                if (index < 11) {
                    return index;
                } else {
                    return (index - 11) | 0x100;
                }
            }
            count++;
        }
        index++;
    } while (index < 22);
    return -1;
}

typedef struct {
    s8 unused0 : 1;
    s8 invert : 1;
    s8 unused2 : 6;
} Flags_0024ECD0;

s32 func_0024ECD0(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    extern s32 func_0024DD80();
    s32 temp_s0;
    s32 temp_s1;
    s32 var_v1;
    s32 var_a0;

    temp_s0 = *(u8 *)((u8 *)arg0 + 0x3E);
    if (((s32)temp_s0 >> 5) != 0) {
        return 0;
    }
    if (((Flags_0024ECD0 *)((u8 *)arg0 + 0x57))->invert == 0) {
        var_a0 = *(u8 *)((u8 *)arg0 + 0x44);
    } else {
        var_a0 = (*(u8 *)((u8 *)arg0 + 0x44) == 0) ? 1 : 0;
    }
    temp_s1 = func_0024DD80(var_a0);
    switch (arg3) {
    case 21:
        if (*(u8 *)((u8 *)arg0 + 0x3F) == 1) {
            var_v1 = 1;
        } else {
            var_v1 = 0;
        }
        break;
    case 20:
        var_v1 = (*(u8 *)((u8 *)arg0 + 0x3F) == 0) ? 1 : 0;
        break;
    case 29:
        var_v1 = 1;
        break;
    case 49:
        if (func_002487A0(*(u16 *)((u8 *)arg0 + 0x3C), 0x2FF) != 0x3E7) {
            var_v1 = 1;
        } else {
            var_v1 = 0;
        }
        break;
    case 14:
        if ((temp_s0 & 0x1F) == 14) {
            var_v1 = 1;
        } else {
            var_v1 = 0;
        }
        break;
    case 15:
        if ((temp_s0 & 0x1F) == 15) {
            var_v1 = 1;
        } else {
            var_v1 = 0;
        }
        break;
    case 2:
        if ((temp_s0 & 0x1F) == 2) {
            var_v1 = 1;
        } else {
            var_v1 = 0;
        }
        break;
    case 6:
        if ((temp_s0 & 0x1F) == 6) {
            var_v1 = 1;
        } else {
            var_v1 = 0;
        }
        break;
    case 7:
        if ((temp_s0 & 0x1F) == 7) {
            var_v1 = 1;
        } else {
            var_v1 = 0;
        }
        break;
    case 25:
        if (*(u8 *)((u8 *)arg0 + 0x3F) == 5) {
            var_v1 = 1;
        } else {
            var_v1 = 0;
        }
        break;
    case 16:
        if ((temp_s0 & 0x1F) == 16) {
            var_v1 = 1;
        } else {
            var_v1 = 0;
        }
        break;
    case 17:
        if ((temp_s0 & 0x1F) == 17) {
            var_v1 = 1;
        } else {
            var_v1 = 0;
        }
        break;
    case 19:
        if ((temp_s0 & 0x1F) == 19) {
            var_v1 = 1;
        } else {
            var_v1 = 0;
        }
        break;
    default:
        var_v1 = 0;
        break;
    }
    if (temp_s1 != 0 && var_v1 != 0) {
        return 1;
    }
    return 0;
}

s32 func_0024EFB0(s32 mask) {
    extern s32 func_001E13C0(s32, s32);
    s32 i;
    s32 best;
    s32 bestPair;
    s32 pair;
    s32 value;

    best = 0xFF;
    bestPair = -1;
    for (i = 0; i < func_0024E910(mask); i++) {
        pair = func_0024EC50(mask, i);
        value = func_001E13C0(pair >> 8, pair & 0xFF);
        if (value < best) {
            bestPair = pair;
            best = value;
        }
    }
    return bestPair;
}

s32 func_0024F060(s32 arg0, s32 arg1) {
    s32 i;
    s32 min;
    s32 result;
    s32 card;
    s32 lo;
    s32 hi;
    s32 cost;

    min = 0xFF;
    result = -1;
    for (i = 0; i < func_0024E910(arg0); i++) {
        card = func_0024EC50(arg0, i);
        hi = card >> 8;
        lo = card & 0xFF;
        cost = func_001E13C0(hi, lo);
        if (cost <= min) {
            min = cost;
            if (result < 0) {
                result = card;
            } else if (arg1 == func_0024DE70(hi, lo)) {
                result = card;
            }
        }
    }
    return result;
}

s32 func_0024F150(s32 mask) {
    extern s32 func_001E13C0(s32, s32);
    s32 i;
    s32 best;
    s32 bestPair;
    s32 pair;
    s32 value;

    best = -1;
    bestPair = -1;
    for (i = 0; i < func_0024E910(mask); i++) {
        pair = func_0024EC50(mask, i);
        value = func_001E13C0(pair >> 8, pair & 0xFF);
        if (best < value) {
            bestPair = pair;
            best = value;
        }
    }
    return bestPair;
}

u32 func_0024F200(s32 arg0) {
    s32 i;
    s32 best;
    s32 mask;
    s32 score;
    s32 low;
    s32 high;
    s32 value;

    best = 0xFFFF;
    mask = 0;
    i = 0;
    if (i < func_0024E910(arg0)) {
        do {
            value = func_0024EC50(arg0, i);
            high = value >> 8;
            low = value & 0xFF;
            if ((score = func_0024F2F0(high, low)) < best) {
                mask = func_0024C780(0U, high, low);
                best = score;
            } else if (score == best) {
                mask = func_0024C780((u32) mask, high, low);
            }
            i += 1;
        } while (i < func_0024E910(arg0));
    }
    return (u32) mask;
}

s32 func_0024F2F0(s32 arg0, s32 arg1) {
    s32 temp_v0;
    s32 temp_s1;
    s32 temp_s0;

    temp_v0 = func_001E1090(arg0, arg1);
    temp_s1 = temp_v0 & 0xFF;
    temp_s0 = func_002509E0(arg0, arg1, temp_s1, temp_s1);
    return temp_s0 + func_00250B40(arg0, arg1, temp_s1, temp_v0 >> 8);
}

/* From the dotr-decomp CC0 bundle (commit 88c32bb2), chatC/imp/conv.py. */

struct DotrStateEntry8 {
    int unknown_words[2];
};
int func_001E1030_b(int a, int b);
struct DotrStateEntry8 *func_00250740_b(int a, int b, int n);
extern int func_001E1030_b(int a, int b);

int func_0024F370(int a, int b)
{
    struct DotrStateEntry8 *entry;
    func_00215B10(a, func_001E1030_b(a, b), 0, -4);
    func_001DEE70(a, func_001E1030_b(a, b));
    func_001DFBB0(a, b);
    if ((entry = func_00250740_b(a, b, 4)) != 0 && (unsigned)entry->unknown_words[0] >> 8 == 81) {
        func_001DEE70((unsigned)entry->unknown_words[1] >> 24, entry->unknown_words[1] & 0xffff);
        func_00215B10((unsigned)entry->unknown_words[1] >> 24, entry->unknown_words[1] & 0xffff, 0, -4);
    }
    return 0;
}

/* From the dotr-decomp CC0 bundle (commit 88c32bb2), chatC/imp/conv.py. */

struct DotrStateEntry8_24f430 {
    int unknown_words[2];
};
int func_001E1030_b(int a, int b);
struct DotrStateEntry8_24f430 *func_00250740_24f430(int a, int b, int n);
extern int func_001E1030_b(int a, int b);

int func_0024F430(int a, int b)
{
    struct DotrStateEntry8_24f430 *entry;
    func_00215B10(func_001DE540(), func_001E1030_b(a, b), 0, -4);
    func_001DEE70(func_001DE540(), func_001E1030_b(a, b));
    func_001DFBB0(a, b);
    if ((entry = func_00250740_24f430(a, b, 4)) != 0 && (unsigned)entry->unknown_words[0] >> 8 == 81) {
        func_001DEE70((unsigned)entry->unknown_words[1] >> 24, entry->unknown_words[1] & 0xffff);
        func_00215B10((unsigned)entry->unknown_words[1] >> 24, entry->unknown_words[1] & 0xffff, 0, -4);
    }
    return 0;
}

s32 func_0024F520(s32 arg0, s32 arg1, s32 arg2, s32 arg3, void *arg4) {
    extern s32 func_0024FD10();
    s32 temp_s0;
    s32 temp_s1;
    s32 var_s1;
    s32 var_s2;
    s32 var_s3;

    temp_s0 = func_00250360(arg0, arg1);
    temp_s1 = func_001E0700(arg0, arg1);
    var_s2 = var_s3 = 0;
    if (func_001DF540(arg0, arg1) == 0 || arg1 == 0) {
        return 0;
    }
    if (func_001E22B0(arg2, arg3) == 9) {
        if (func_0024FD10(arg0, arg1, arg4) == 1) {
            return 1;
        }
    }
    if (func_00271A40((temp_s0 == 0) ? 1 : 0, arg2, arg3) != 0) {
        if (func_00271740(0x10, (temp_s0 == 0) ? 1 : 0) != 0) {
            if ((func_002720F0((temp_s0 == 0) ? 1 : 0, temp_s1 & 0x1F) != 0) && ((temp_s1 >> 5) == 0)) {
                var_s2 = func_0024C780(var_s2, arg0, arg1);
            }
        }
        if ((func_00271740(0xF, (temp_s0 == 0) ? 1 : 0) != 0) && (func_00272050((temp_s0 == 0) ? 1 : 0, temp_s1 & 0x1F) != 0) && ((temp_s1 >> 5) == 0)) {
            var_s3 = func_0024C780(0U, arg0, arg1);
        }
        if (var_s2 > 0 || var_s3 > 0) {
            ((s32 *)arg4)[0] = 0x71;
            ((s32 *)arg4)[1] = var_s2;
            ((s32 *)arg4)[2] = var_s3;
            ((s32 *)arg4)[3] = 0x80000000;
            return 1;
        }
        var_s1 = 0;
        if ((func_00271740(0xD, (temp_s0 == 0) ? 1 : 0) != 0) && (func_001E2100(arg0, arg1, 4) == 0)) {
            var_s1 = func_0024C780(0U, arg0, arg1);
        }
        if (var_s1 > 0) {
            ((s32 *)arg4)[0] = 0x71;
            ((s32 *)arg4)[1] = 0;
            ((s32 *)arg4)[2] = 0;
            ((s32 *)arg4)[3] = (s32) (var_s1 | 0x80000000);
            return 1;
        }
    }
    return 0;
}

s32 func_0024F780(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    if (func_001E22B0(arg2, arg3) == 9) {
        if (func_0024FD10(arg0, arg1, arg4) == 1) {
            return 0x10001;
        }
    }
    return func_0024F830(arg0, arg1, arg2, arg3, arg4);
}

INCLUDE_ASM("asm/nonmatchings/main_072", func_0024F830);

s32 func_0024FD10(s32 arg0, s32 arg1, s32 arg2) {
    extern s32 func_0024FDA0(s32, s32);
    extern void func_002516D0(s32, s32, s32);
    s32 *out = (s32 *)arg2;
    s32 mask;

    if (func_0024FDA0(arg0, arg1) == 1) {
        mask = func_0024C780(0, arg0, arg1);
        out[0] = 0x70;
        out[1] = 0;
        out[2] = mask;
        out[3] = 0;
        func_002516D0(arg0, arg1, 1);
        return 1;
    }
    return 0;
}

void func_0024FDA0(s32 arg0, s32 arg1) {
    func_0024FDD0(func_001DF540(arg0, arg1));
}

s32 func_0024FDD0(s32 arg0) {
    u8 temp_v1;

    if (arg0 == 0) {
        return 0;
    }
    temp_v1 = *(u8 *)((u8 *)arg0 + 0x3E);
    if ((((s32) temp_v1 >> 5) != 0) ||
        (*(u8 *)((u8 *)arg0 + 0x45) == 0) ||
        ((temp_v1 & 0x1F) == 0x14)) {
        return 0;
    }
    return (func_00250A60(arg0, *(u8 *)((u8 *)arg0 + 0x40), *(u8 *)((u8 *)arg0 + 0x41)) < 0x5DC) ? 0 : 1;
}

s32 func_0024FE40(void *arg0, s32 arg1, s32 arg2) {
    u8 temp_v1;

    if (arg0 == NULL) {
        return 0;
    }
    temp_v1 = *((u8 *)arg0 + 0x3E);
    if ((((s32)temp_v1 >> 5) != 0) ||
        (*((u8 *)arg0 + 0x45) == 0) ||
        ((temp_v1 & 0x1F) == 0x14)) {
        return 0;
    }
    return (func_00250A60((s32)arg0, arg1, arg2) < 0x5DC) ? 0 : 1;
}

s32 func_0024FEB0(void *arg0) {
    extern s32 func_0024FDA0(s32, s32);
    extern void func_002516D0(s32, s32, s32);
    u32 mask;
    s32 *out = (s32 *)arg0;
    s32 i;
    s32 info;

    mask = 0;
    i = 1;
    do {
        info = func_001E1090(0, i);
        if (func_0024FDA0(0, i) == 1) {
            if (func_001E22B0(info & 0xFF, info >> 8) == 9) {
                mask = func_0024C780(mask, 0, i);
                func_002516D0(0, i, 1);
            }
        }
        info = func_001E1090(1, i);
        if (func_0024FDA0(1, i) == 1 && func_001E22B0(info & 0xFF, info >> 8) == 9) {
            mask = func_0024C780(mask, 1, i);
            func_002516D0(1, i, 1);
        }
        i++;
    } while (i < 0xB);
    if (func_0024E910((s32)mask) > 0) {
        out[0] = 0x70;
        out[1] = 0;
        out[2] = mask;
        out[3] = 0;
        return 1;
    }
    return 0;
}

s32 func_00250000(s32 arg0, s32 arg1, s32 arg2) {
    extern s32 func_001DEE50(s32);
    s32 card;

    if (func_001DEE50(arg0) < arg1) {
        return 0;
    }
    card = func_001DEE00(arg0, arg1);
    if (card != 999) {
        switch (arg2) {
        case 0:
            return 1;
        case 1:
            return card < 0x2AB ? 1 : 0;
        case 2:
            if (card >= 0x2AB) {
                return 1;
            }
            return 0;
        }
    }
    return 0;
}

void func_002500C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    extern s32 func_001E1840();
    extern s32 func_001E18A0();
    extern s32 func_001E1970();
    extern s32 func_001E19D0();
    extern s32 func_001E1CB0();
    extern s32 func_001E1D10();
    s32 temp_s0;
    s32 temp_s1;

    func_001F5970((arg0 << 8) | arg1, 0);
    temp_s0 = func_001E1CB0(arg0, arg1);
    temp_s1 = func_001E1D10(arg0, arg1);
    if ((arg1 != 0) && ((func_001E0700(arg0, arg1) >> 5) != 0)) {
        arg4 = ((arg4 >> 1) & 1) * 2;
    }
    if (arg2 > 0) {
        if (arg4 & 1) {
            if (temp_s1 < 0x80) {
                func_001E18A0(arg0, arg1, arg3);
                func_001E19D0(arg0, arg1, 0x80);
                if ((func_001E2100(arg0, arg1, 4) != 0) || (arg1 == 0)) {
                    func_001E1C10(arg0, arg1, 1, -1);
                } else {
                    func_001E1C10(arg0, arg1, 0, -1);
                }
            }
        }
        if (((arg4 >> 1) & 1) && (temp_s0 < 0x80)) {
            func_001E1840(arg0, arg1, arg3);
            func_001E1970(arg0, arg1, 0x80);
            func_001E1B70(arg0, arg1, 1, -1);
        }
    } else {
        if ((arg4 & 1) && (temp_s1 > 0)) {
            func_001E18A0(arg0, arg1, arg3);
            func_001E19D0(arg0, arg1, 0);
            func_001E1C10(arg0, arg1, -1, -1);
        }
        if (((arg4 >> 1) & 1) && (temp_s0 > 0)) {
            func_001E1840(arg0, arg1, arg3);
            func_001E1970(arg0, arg1, 0);
            func_001E1B70(arg0, arg1, -1, -1);
        }
    }
}

s32 func_00250300(u16 arg0, s32 arg1, s32 arg2) {
    if (arg2 > 0) {
        arg0 += arg1;
        if (arg0 > 0x80) {
            arg0 = 0x80;
        }
        return arg0;
    }
    if (arg1 < arg0) {
        arg0 -= arg1;
    } else {
        arg0 = 0;
    }
    return arg0;
}

s32 func_00250360(s32 arg0, s32 arg1) {
    return func_0024DE70(arg0, arg1);
}

typedef struct {
    s8 unused : 1;
    s8 inverted : 1;
    s8 reserved : 6;
} Flags_00250370;

typedef struct {
    u8 pad_00[0x44];
    u8 value;
    u8 pad_45[0x12];
    Flags_00250370 flags;
} Data_00250370;

s32 func_00250370(void *arg0) {
    Data_00250370 *data = arg0;

    if (arg0 == NULL) {
        return -1;
    }
    if (data->flags.inverted == 0) {
        return data->value;
    }
    return (data->value == 0) ? 1 : 0;
}

void func_002503B0(s32 arg0, s32 arg1, s32 arg2) {
    /* called unprototyped: the byte goes out zero-extended, not as s8 */
    s32 func_001E1520();
    u8 value = arg2;

    if (value > 0) {
        if (func_001E1580() <= value) {
            func_001E1520(arg0, arg1, value);
            func_001E1420(arg0, arg1, 1);
        }
    } else {
        func_001E1520(arg0, arg1, value);
    }
}

typedef struct {
    u8 kind;
    u8 pad1[2];
    u8 level;
    u8 pad4[5];
    u8 pad9 : 7;
    u8 flag : 1;
} Card_00250430;


s32 func_00250430(s32 arg0, s32 arg1) {
    s32 list[0x356];
    Card_00250430 *card;
    s32 count;
    s32 level;
    s32 flag;
    s32 done;
    s32 i;

    for (i = 0; i < 0x356; i++) {
        list[i] = 999;
    }
    card = (Card_00250430 *)func_001DD0E0(arg1);
    if ((card->kind >> 5) == 0) {
        flag = (func_0019A5C8() % 10 < 8) ? 1 : 0;
    } else {
        flag = (func_0019A5C8() % 10 < 4) ? 0 : 1;
    }
    done = 0;
    count = 0;
    level = func_00250620(arg0, card->level);
    if (level > 0) {
        do {
            for (i = flag ? 0 : 0x2AB; i < (flag ? 0x2AB : 0x356); i++) {
                if (i != arg1) {
                    card = (Card_00250430 *)func_001DD0E0(i);
                    if (card != NULL && card->level == level && card->flag) {
                        list[count++] = i;
                    }
                }
            }
            if (count > 0 || --level == 0) {
                done = 1;
            } else {
                count = 0;
            }
        } while (!done);
    }
    if (count == 0) {
        return 0x334;
    }
    return list[func_0019A5C8() % count];
}
