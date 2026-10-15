#include "common.h"

s32 func_0026EA80(s32 arg0, s32 arg1) {
    s32 temp_s0;
    u8 *temp_v0;
    u8 temp_s1;

    temp_v0 = func_001DD0E0(arg1);
    if (temp_v0 == NULL) {
        return 0;
    }
    temp_s1 = *temp_v0;
    temp_s0 = temp_s1 & 0x1F;
    if (temp_s0 == (func_001E0700(arg0, 0) & 0x1F)) {
        if (((s32) temp_s1 >> 5) == 0) {
            return func_00271830(arg0);
        }
    }
    return 0;
}

struct jp_87592;
struct jp_87b56;
struct jp_88243 {
    unsigned int dwID;
    unsigned int dwParam;
};
struct jp_86d82 {
    struct jp_87592 *pConstInfo;
    struct jp_87b56 *pCardReq;
    struct jp_88243 aVarEffIdx[5];
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

int func_0026EB10(int nSide, int nCardNo, int nCardNo2)
{
    int Ret;
    int Num;
    int Combo[6];
    struct jp_86d82 nVarInfo;
    int temp;
    int bKind1;
    int bKind0;
    int cBuf;
    int Hand;
    int i;

    Hand = func_001DF110(nSide);
    for (i = 0; i < 6; i++) {
        Combo[i] = 999;
    }
    if (nCardNo != 999) {
        Combo[0] = nCardNo;
    }
    if (nCardNo != 999 && nCardNo2 != 999) {
        func_001DCD70(&nVarInfo, nCardNo);
        bKind0 = nVarInfo.bVarKind >> 5;
        func_001DCD70(&nVarInfo, nCardNo2);
        bKind1 = nVarInfo.bVarKind >> 5;
        if (bKind0 == 0 && bKind1 == 0) {
            Num = func_002495A0(nCardNo, nCardNo2);
            if (Num != 999) {
                temp = Num;
            } else {
                temp = nCardNo2;
            }
        } else if (bKind0 == 2 && bKind1 == 0) {
            Num = func_002487A0(nCardNo2, nCardNo);
            if (Num != 999) {
                if ((Num >> 30) & 1) {
                    temp = (Num >> 14) & 0x3FFF;
                } else {
                    temp = nCardNo2;
                }
            } else {
                temp = nCardNo2;
            }
        } else if (bKind1 == 2 && bKind0 == 0) {
            Num = func_002487A0(nCardNo, nCardNo2);
            if (Num != 999) {
                if ((Num >> 30) & 1) {
                    temp = (Num >> 14) & 0x3FFF;
                } else {
                    temp = nCardNo;
                }
            } else {
                temp = nCardNo2;
            }
        } else {
            temp = nCardNo2;
        }
        return temp;
    } else {
    for (i = 0; i < Hand; i++) {
        cBuf = func_001DF0C0(nSide, i);
        temp = (cBuf & 0xF000) >> 12;
        if (temp > 0) {
            Combo[temp] = cBuf & 0xFFF;
        }
    }
    Ret = Combo[0];
    for (i = 0; i < 5; i++) {
        if (Ret != 999) {
            func_001DCD70(&nVarInfo, Ret);
            bKind0 = nVarInfo.bVarKind >> 5;
        } else {
            bKind0 = -1;
        }
        if (Combo[i + 1] != 999) {
            func_001DCD70(&nVarInfo, Combo[i + 1]);
            bKind1 = nVarInfo.bVarKind >> 5;
        } else {
            return Ret;
        }
        if (bKind0 == 0 && bKind1 == 0) {
            Num = func_002495A0(Ret, Combo[i + 1]);
            if (Num != 999) {
                temp = Num;
            } else {
                temp = Combo[i + 1];
            }
        } else if (bKind0 == 2 && bKind1 == 0) {
            Num = func_002487A0(Combo[i + 1], Ret);
            if (Num != 999) {
                if ((Num >> 30) & 1) {
                    temp = (Num >> 14) & 0x3FFF;
                } else {
                    temp = Combo[i + 1];
                }
            } else {
                temp = Combo[i + 1];
            }
        } else if (bKind1 == 2 && bKind0 == 0) {
            Num = func_002487A0(Ret, Combo[i + 1]);
            if (Num != 999) {
                if ((Num >> 30) & 1) {
                    temp = (Num >> 14) & 0x3FFF;
                } else {
                    temp = Ret;
                }
            } else {
                temp = Combo[i + 1];
            }
        } else {
            temp = Combo[i + 1];
        }
        Ret = temp;
    }
    }
    return Ret;
}

s32 func_0026EEA0(void *arg0, s32 arg1, s32 arg2) {
    ((s32 *)arg0)[0] = 0x96;
    ((s32 *)arg0)[1] = 0;
    ((s32 *)arg0)[2] = (arg1 << 8) | arg2;
    ((s32 *)arg0)[3] = 0;
    return 1;
}

s32 func_0026EED0(s32 arg0) {
    extern s32 func_001DE4E0();
    extern s32 func_00215D30();
    extern s32 func_0026EFD0(s32);
    s32 state;
    s32 value;

    state = func_001DE4E0(func_001DE540());
    if (state < 0x20 && state != 0x13 && state != 1) {
        return -1;
    }
    value = func_00215D30(arg0, func_002159D0(arg0, func_002158B0(arg0)));
    if (state > 99 && func_00271740(3, arg0) == 0) {
        return -1;
    }
    if (func_001DF470(arg0) < 1000) {
        if ((state = func_0026EFD0(arg0)) >= 0) {
            return state | (func_00250860(0, value - 8) << 4);
        }
    }
    return -1;
}

struct jp_88243_26efd0 {
    unsigned int dwID;
    unsigned int dwParam;
};
extern int func_001DE4E0_b(int index);
extern unsigned *func_00250740_b(int a, int b, int n);
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int func_0026EFD0(int nSide)
{
    int i;
    int j;
    int Unit;
    int Loc;
    int Loc2;
    int Num;
    int Num2;
    int tempAP;
    int AP;
    int temp;
    struct jp_88243_26efd0 *eInfo;
    int Player;
    unsigned int eObj;

    Player = func_001DE4E0_b(func_001DE540());
    if (Player > 99) {
        eObj = func_0024CA40(0, 0, nSide, 3, 33, 14);
        Unit = func_0024EC50(eObj, 0);
        if (func_00250360(Unit >> 8, Unit & 0xff) != nSide) {
            if ((func_001E0700(Unit >> 8, Unit & 0xff) == 7) & 0x1f) {
                Loc = func_001E1090(Unit >> 8, Unit & 0xff);
                Loc2 = func_001E1090(nSide, 0);
                if ((MAX(Loc & 0xff, Loc2 & 0xff) - MIN(Loc & 0xff, Loc2 & 0xff)) +
                        (MAX(Loc >> 8, Loc2 >> 8) - MIN(Loc >> 8, Loc2 >> 8)) <= 2) {
                    if (func_0024E910(func_0024CA40(0, 0, nSide, 2, 7, 14)) >= 3) {
                        return 1;
                    }
                }
            }
        }
        eObj = func_0024CA40(0, 0, nSide, 2, 29, 14);
        Num = 0;
        if (func_0024E910(eObj) >= 3) {
            if ((func_001E0700(nSide, 0) == 9) & 0x1f) {
                for (i = 0; i < func_0024E910(eObj); i++) {
                    Unit = func_0024EC50(eObj, i);
                    Loc = func_001E1090(Unit >> 8, Unit & 0xff);
                    if (func_0024DF00(0, Unit >> 8, Unit & 0xff) != 1) {
                        if (func_002509E0(Unit >> 8, Unit & 0xff, Loc & 0xff, Loc >> 8) >= 3000 &&
                            func_002509E0(Unit >> 8, Unit & 0xff, Loc & 0xff, Loc >> 8) <= 3999) {
                            Num++;
                        }
                    }
                }
                if (Num >= 3) {
                    return 2;
                }
            }
        }
        eObj = func_0024CA40(0, 0, nSide, 3, 29, 14);
        Num2 = 0;
        Num = 0;
        if (func_0024E910(eObj) >= 3) {
            for (i = 0; i < 7; i++) {
                for (j = 0; j < 7; j++) {
                    if (func_001E22B0(i, j) == 8) {
                        Num++;
                    }
                }
            }
            if (Num > 30) {
                i = 0;
                for (j = 0; j < func_0024E910(eObj); j++) {
                    Unit = func_0024EC50(eObj, j);
                    eInfo = (struct jp_88243_26efd0 *)func_00250740_b(Unit >> 8, Unit & 0xff, 1);
                    if (eInfo != 0) {
                        if (eInfo->dwID >> 8 == 8 || eInfo->dwID >> 8 == 9 || eInfo->dwID >> 8 == 10) {
                            if (func_00250360(Unit >> 8, Unit & 0xff) == nSide) {
                                i++;
                            } else {
                                Num2++;
                            }
                        }
                    }
                }
                if (i == 0 && Num2 >= 3) {
                    return 3;
                }
            }
        }
        eObj = func_0024CA40(0, 0, nSide, 3, 33, 14);
        Unit = func_0024EC50(eObj, 0);
        if (func_00250360(Unit >> 8, Unit & 0xff) != nSide) {
            Loc = func_001E1090(Unit >> 8, Unit & 0xff);
            AP = -1;
            for (i = 0; i < 5; i++) {
                temp = func_001DF0C0(nSide, i);
                if (temp != 999) {
                    tempAP = (unsigned int)func_0026FBB0(temp) >> 16;
                    if (tempAP > AP) {
                        AP = tempAP;
                    }
                }
            }
            if (func_002509E0(Unit >> 8, Unit & 0xff, Loc & 0xff, Loc >> 8) > AP) {
                tempAP = func_002509E0(Unit >> 8, Unit & 0xff, Loc & 0xff, Loc >> 8) - AP;
                if (func_001DF470(nSide == 0 ? 1 : 0) >> 1 > tempAP) {
                    return 4;
                }
            }
        }
        eObj = func_0024CA40(0, 0, nSide, 3, 33, 14);
        Unit = func_0024EC50(eObj, 0);
        Num = 0;
        if (func_00250360(Unit >> 8, Unit & 0xff) == nSide) {
            eObj = func_0024CA40(0, 0, nSide, 2, 30, 14);
            for (i = 0; i < func_0024E910(eObj); i++) {
                Unit = func_0024EC50(eObj, i);
                if (func_001DE020(func_001E0700(Unit >> 8, Unit & 0xff) >> 5) == 2) {
                    Num++;
                }
            }
            if (Num >= 4) {
                return 5;
            }
        }
    }
    if (Player > 99) {
        if (func_001DF470(nSide) <= 249) {
            return func_0019A5C8() % 2 == 0 ? 6 : 7;
        }
    } else {
        return func_0019A5C8() % 2 == 0 ? 6 : 7;
    }
    return -1;
}
#undef MAX
#undef MIN

s32 func_0026F600(s32 arg0, s32 *arg1) {
    extern s32 func_001DE740(s32);
    s32 flags;

    flags = func_001DE740(arg0);
    arg1[0] = 0x3E7;
    arg1[1] = 0;
    arg1[2] = 0;
    arg1[3] = 0;
    if (!(flags & 0x80) && func_001DF110(arg0) < 5) {
        if (arg1 != NULL) {
            arg1[0] = 0x72;
            arg1[1] = func_001DE540();
            arg1[2] = 0;
            arg1[3] = 0;
        }
        return 1;
    }
    return 0;
}

s32 func_0026F690(s32 arg0, u16 *arg1, s16 *arg2, s32 arg3) {
    extern u16 D_002B8700[];
    extern u16 D_002B8702[];
    extern u16 D_002B8704[];
    extern void func_001DE760(s32, u8);
    extern s32 func_001DE740(s32);
    s32 flags;
    s32 kind;
    s32 bonus;
    s32 index;

    flags = func_001DE740(arg0);
    kind = func_001E0700(arg0, 0) & 0x1F;
    bonus = (flags & 0xF0) * 5;
    arg1[0] = 999;
    arg1[1] = 999;
    arg1[2] = 999;
    switch (kind) {
    case 0:
        arg2[0] = 0;
        arg2[1] = 0;
        arg2[2] = 0;
        break;
    case 1:
        arg2[0] = 2;
        arg2[1] = 1;
        arg2[2] = -3;
        break;
    case 2:
        arg2[0] = 12;
        arg2[1] = 6;
        arg2[2] = -18;
        break;
    case 3:
        arg2[0] = 2;
        arg2[1] = 1;
        arg2[2] = -3;
        break;
    case 4:
        arg2[0] = 5;
        arg2[1] = 3;
        arg2[2] = -8;
        break;
    case 5:
        arg2[0] = 8;
        arg2[1] = 4;
        arg2[2] = -12;
        break;
    case 6:
        arg2[0] = 6;
        arg2[1] = 3;
        arg2[2] = -9;
        break;
    case 7:
        arg2[0] = 0;
        arg2[1] = 0;
        arg2[2] = 0;
        break;
    case 8:
        arg2[0] = 12;
        arg2[1] = 6;
        arg2[2] = -18;
        break;
    case 9:
        arg2[0] = 10;
        arg2[1] = 5;
        arg2[2] = -15;
        break;
    case 10:
        arg2[0] = 14;
        arg2[1] = 7;
        arg2[2] = -21;
        break;
    case 11:
        arg2[0] = 15;
        arg2[1] = 8;
        arg2[2] = -23;
        break;
    case 12:
        arg2[0] = 8;
        arg2[1] = 4;
        arg2[2] = -12;
        break;
    case 13:
        arg2[0] = 14;
        arg2[1] = 7;
        arg2[2] = -21;
        break;
    case 14:
        arg2[0] = 3;
        arg2[1] = 1;
        arg2[2] = -4;
        break;
    case 15:
        arg2[0] = 10;
        arg2[1] = 5;
        arg2[2] = -15;
        break;
    case 16:
        arg2[0] = 2;
        arg2[1] = 1;
        arg2[2] = -3;
        break;
    case 17:
        arg2[0] = 13;
        arg2[1] = 6;
        arg2[2] = -19;
        break;
    case 18:
        arg2[0] = 10;
        arg2[1] = 5;
        arg2[2] = -15;
        break;
    case 19:
        arg2[0] = 10;
        arg2[1] = 5;
        arg2[2] = -15;
        break;
    case 20:
        arg2[0] = -5;
        arg2[1] = -2;
        arg2[2] = 7;
        break;
    default:
        return -1;
    }
    if (!(flags & 0x80)) {
        index = (flags & 0xF) * 3;
        arg1[0] = D_002B8700[index];
        arg1[1] = D_002B8702[index];
        arg1[2] = D_002B8704[index];
        arg2[0] += bonus;
        arg2[1] += (s16)(bonus >> 1);
        arg2[2] = -(arg2[0] + arg2[1]);
        arg2[0] += 10;
        arg2[1] += 20;
        arg2[2] += 70;
        flags |= 0x80;
        func_001DE760(arg0, flags);
        if (arg3 != 0) {
            ((s32 *)arg3)[0] = 0x72;
            ((s32 *)arg3)[1] = func_001DE540();
            ((s32 *)arg3)[2] = 0;
            ((s32 *)arg3)[3] = 0;
        }
        return 1;
    }
    return -1;
}

s32 func_0026FA70(s32 arg0, s32 arg1) {
    return func_0026FA80(arg0 & 0xFFF, arg1);
}

typedef struct {
    u8 flags;
    u8 pad;
    u8 unused : 4;
    u8 value : 4;
} Flags_0026FA80;


s32 func_0026FA80(s32 arg0, s32 arg1) {
    s32 owner;
    s32 value;
    Flags_0026FA80 *data;

    data = (Flags_0026FA80 *)func_001DD0E0(arg0);
    if (data == NULL) {
        return 0xFF;
    }
    value = data->value;
    if ((data->flags >> 5) == 0) {
        owner = data->flags & 0x1F;
        if (owner == (func_001E0700(arg1, 0) & 0x1F)) {
            value -= func_00271830(arg1);
        }
    }
    return value;
}

s32 func_0026FB10(s32 arg0, s32 arg1) {
    s32 temp_s0;

    temp_s0 = func_0026FA80(arg1, arg0);
    return (func_001DE5C0(arg0) < temp_s0) ? 0 : 1;
}

s32 func_0026FB60(s32 arg0, s32 arg1) {
    s32 temp_s0;

    temp_s0 = func_0026FA80(arg1 & 0xFFF, arg0);
    return (func_001DE5C0(arg0) < temp_s0) ? 0 : 1;
}

typedef struct CardStats_0026FBB0 {
    u8 padding[8];
    u16 attack;
    u16 defense;
} CardStats_0026FBB0;

u32 func_0026FBB0(s32 arg0) {
    CardStats_0026FBB0 *card;

    if (arg0 == 0x3E7) {
        return 0U;
    }
    card = (CardStats_0026FBB0 *)func_001DD0E0(arg0);
    if (card == NULL) {
        return 0U;
    }
    return ((card->attack & 0x1FFF) << 16) | (card->defense & 0x1FFF);
}

s32 func_0026FC10(s32 arg0) {
    u8 *p;

    if (arg0 == 0x3E7) {
        return 0;
    }
    p = func_001DD0E0(arg0);
    if (p == NULL) {
        return 0;
    }
    if ((p[0] >> 5) == 0) {
        if (*(u16 *)(p + 4) == 0xFFFF) {
            return 2;
        }
        return 1;
    }
    return 0;
}

void *func_0026FC90(s32 arg0, s32 arg1) {
    u8 data[0x60];

    if (arg0 == 0x3E7) {
        return NULL;
    }
    func_001DCD70(data, arg0);
    return data + 8 + arg1 * 8;
}

s32 func_0026FCE0(s32 arg0) {
    u8 *temp_v0;

    if (arg0 == 0x3E7) {
        return 0U;
    }
    temp_v0 = func_001DD0E0(arg0);
    if (temp_v0 == NULL) {
        return 0U;
    }
    return *temp_v0;
}

void func_0026FD30(s32 arg0, s32 *arg1) {
    s32 index;
    s32 count;
    s32 value;

    index = 0;
    count = 0;
    do {
        value = func_001DF0C0(arg0, index) & 0xFFF;
        if (value != 0x3E7) {
            arg1[count] = value;
            count++;
        }
        index++;
    } while (index < 5);
    index = func_001DF110(arg0);
    count = 0;
    while (index < func_0026FE20(arg0)) {
        arg1[index] = func_001DE9E0(arg0, count);
        index++;
        count++;
    }
}

s32 func_0026FE20(s32 arg0) {
    s32 temp_s0;
    s32 var_v0;

    temp_s0 = func_001DF110(arg0);
    var_v0 = temp_s0 + func_001DE9C0(arg0);
    if (var_v0 >= 5) {
        var_v0 = 5;
    }
    return var_v0;
}

typedef struct {
    u32 unused;
    u32 value1;
    u32 value2;
    s32 flags;
} Input_0026FE70;

typedef struct {
    u8 pad0[4];
    u16 state;
    u8 type;
    u8 pad7;
    u8 pad8[0x18];
    s32 once;
    u8 pad24[0xAC];
    s32 count;
} Object_0026FE70;

s32 func_0026FE70(void *src, void *obj, s32 mode) {
    extern void func_0024F430(u32, s32);
    s32 words[4];
    s32 *message = words;
    Input_0026FE70 *input = src;
    Object_0026FE70 *target = obj;
    s32 count;
    u32 color;

    message[0] = 0x3E7;
    message[1] = 0;
    message[2] = 0;
    message[3] = 0;

    if (mode >= 0) {
        func_00255960(obj);
        func_00255AC0(obj, 0x21A);
        message[0] = 0x25A;
        message[1] = input->value1;
        message[2] = input->value2;
        message[3] = 0;
        func_0027EB00((u8 *)obj + 0x110, message, 0);
        goto common_return;
    }

    switch (target->state) {
    case 0:
        goto no_state;
    default:
        goto active;
    }

no_state:
    if (func_00255B50(obj) == 1) {
        message[0] = 0x21A;
        message[1] = input->value1;
        message[2] = input->value2;
        message[3] = 0;
        *(u8 *)((u8 *)obj + 6) = func_00255A30(message, obj);
        target->once = 0;
        target->state = target->state + 1;
    }

    message[0] = 0x25A;
    message[1] = input->value1;
    message[2] = input->value2;
    message[3] = 0;
    func_0027EB00((u8 *)obj + 0x110, message, -1);
    return 1;

active:
    if (func_001F51D0(target->type) != 0) {
        count = target->count;
        target->count = count + 1;
        switch (count) {
        case 1:
            func_00217710(1, 0x4C);
            break;
        case 0xF:
            func_00217710(1, 0x4A);
            break;
        }
        return 1;
    } else {
        color = input->value1;
        func_0024F430(color >> 8, color & 0xFF);
        func_001E4530();
        return 0;
    }

common_return:
    return 1;
}

typedef struct {
    u32 unused;
    u32 value1;
    u32 value2;
    s32 flags;
} Input_00270030;

typedef struct {
    u8 pad0[4];
    u16 state;
    u8 type;
    u8 pad7;
    u8 pad8[0x18];
    s32 once;
    u8 pad24[0xAC];
    s32 count;
} Object_00270030;

extern void func_0024F430(u32, s32);

s32 func_00270030(void *src, void *obj, s32 mode) {
    s32 words[4];
    s32 *message = words;
    Input_00270030 *input = src;
    Object_00270030 *target = obj;
    s32 count;
    u32 color;

    message[0] = 0x3E7;
    message[1] = 0;
    message[2] = 0;
    message[3] = 0;

    if (mode >= 0) {
        func_00255960(obj);
        func_00255AC0(obj, 0x258);
        message[0] = 0x25A;
        message[1] = input->value1;
        message[2] = input->value2;
        message[3] = 0;
        func_0027EB00((u8 *)obj + 0x110, message, 0);
        goto common_return;
    }

    switch (target->state) {
    case 0:
        goto no_state;
    default:
        goto active;
    }

no_state:
    if (func_00255B50(obj) == 1) {
        message[0] = 0x258;
        message[1] = input->value1;
        message[2] = input->value2;
        message[3] = 0;
        *(u8 *)((u8 *)obj + 6) = func_00255A30(message, obj);
        target->once = 0;
        target->state = target->state + 1;
    }

    message[0] = 0x25A;
    message[1] = input->value1;
    message[2] = input->value2;
    message[3] = 0;
    func_0027EB00((u8 *)obj + 0x110, message, -1);
    return 1;

active:
    if (func_001F51D0(target->type) != 0) {
        count = target->count;
        target->count = count + 1;
        switch (count) {
        case 1:
            func_00217710(1, 0x4C);
            break;
        case 0x12:
            func_00217710(1, 0x3A);
            break;
        case 0x50:
            func_00217710(1, 0x3B);
            break;
        }

        if (func_001F52D0(target->type) == 2 && target->once == 0) {
            target->once = 1;
            color = input->value1;
            func_0024F430(color >> 8, color & 0xFF);
            color = input->value2;
            func_0024F430(color >> 8, color & 0xFF);
            return (input->flags << 16) | 2;
        }
        return 1;
    } else {
        func_001E4530();
        return 0;
    }

common_return:
    return 1;
}

typedef struct Source_00270260 {
    s32 unused;
    u32 position;
    s32 entries;
    s32 card;
} Source_00270260;

typedef struct State_00270260 {
    u16 flag;
    u16 position;
    u16 stage;
    u8 commands[0x16];
    u32 results[0x2D];
    s32 timer;
    u8 count;
    u8 padD5[0x3B];
    u8 queue[1];
} State_00270260;

typedef struct Event_00270260 {
    s32 id;
    s32 from;
    s32 to;
    s32 mode;
} Event_00270260;

void func_0024F430(u32, s32);

static inline s32 mode_00270260(u32 position) {
    if ((func_001E0700(position >> 24, (position >> 16) & 0xFF) >> 5) == 0) {
        return 0;
    } else {
        return 3;
    }
}

s32 func_00270260(void *src, void *state, s32 mode) {
    extern s32 func_001E1E10();
    extern s32 func_001E1030();
    extern s32 func_001E1CB0();
    extern s32 func_001E1A30();
    Event_00270260 event;
    Event_00270260 *message = &event;
    State_00270260 *temp_s1;
    Source_00270260 *temp_s2;
    s32 temp_s3;
    s32 temp_a1;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_s3_2;
    s32 temp_v0;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 var_v0;
    u16 temp_v0_5;
    u16 temp_v0_6;
    u16 temp_v1;
    u32 temp_a1_2;
    u32 temp_a1_3;
    u32 temp_v0_10;
    u32 temp_v0_2;
    u32 temp_v0_7;
    u32 side;
    u32 temp_v0_8;
    u32 temp_v0_9;
    u32 temp_v1_5;
    s32 var_s3;

    event.id = 0x3E7;
    event.from = 0;
    event.to = 0;
    temp_s2 = src;
    event.mode = 0;
    temp_s1 = state;
    temp_s3 = mode;
    if ((func_00249200(((Source_00270260 *)src)->card) & 0xFFFF) == 0x219) {
        return func_00270C30(temp_s2, temp_s1, temp_s3);
    }
    if (temp_s3 >= 0) {
        func_00255960(temp_s1);
        temp_v0 = func_00249200(temp_s2->card) & 0xFFFF;
        switch (temp_v0) {
        case 0x218:
            func_00255AC0(temp_s1, 0x218);
            break;
        case 0x21C:
            func_00255AC0(temp_s1, 0x21C);
            break;
        case 0x21D:
            func_00255AC0(temp_s1, 0x21D);
            break;
        case 0x21E:
            func_00255AC0(temp_s1, 0x21E);
            break;
        default:
            func_00255AC0(temp_s1, 0x218);
            break;
        }
        temp_v0_2 = temp_s2->position;
        if ((((func_001E0700((s32) (temp_v0_2 >> 0x18), (temp_v0_2 >> 0x10) & 0xFF) >> 5) == 0) ? 0 : 3) == 0) {
            var_s3 = (u32) temp_s2->position >> 0x10;
        } else {
            var_s3 = (u32) (u16) temp_s2->position;
        }
        if ((temp_v0_3 = func_0026AB80(temp_s2->entries, 0x2B)) < 0 ||
            (func_00249560((s32)(u16)temp_s2->card) == 0 &&
             func_00271740(0xB, func_001DE540()) == 1 &&
             (temp_s3_2 = func_001E0700((s32)var_s3 >> 8, var_s3 & 0xFF) & 0x1F) ==
             (func_001E0700(func_001DE540(), 0) & 0x1F))) {
            temp_s1->stage = 2;
            temp_s1->flag = 0;
        } else {
            func_001DE7E0(0);
            func_00255AC0(temp_s1, 0x25A);
            temp_v0_4 = func_0026AB80(temp_s2->entries, 0x2E);
            if (temp_v0_4 >= 0) {
                temp_s1->stage = 0U;
                temp_s1->flag = 0U;
                temp_s1->position = (u16) temp_v0_4;
            } else {
                temp_s1->stage = 0U;
                temp_s1->flag = 1U;
                temp_s1->position = (u16) temp_v0_3;
            }
            temp_v0_5 = temp_s1->position;
            func_002516D0((s32) temp_v0_5 >> 8, temp_v0_5 & 0xFF, 1);
        }
        message->id = 0x25A;
        message->from = (u32) ((u32) temp_s2->position >> 0x10);
        message->to = (s32) (u16) temp_s2->position;
        message->mode = 0;
        func_0027EB00(temp_s1->queue, message, 0);
        return 1;
    }
    if (func_00255B50(temp_s1) != 1) {
        if ((s32) temp_s1->position > 0) {
            func_001DE7E0(0);
        }
        message->id = 0x25A;
        message->from = (u32) ((u32) temp_s2->position >> 0x10);
        message->to = (s32) (u16) temp_s2->position;
        message->mode = 0;
        func_0027EB00(temp_s1->queue, message, -1);
        return 1;
    }
    temp_v1 = temp_s1->stage;
    switch (temp_v1) {
    case 0:
        func_001DE7E0(0);
        message->id = 0x25A;
        message->from = (u32) ((u32) temp_s2->position >> 0x10);
        message->to = (s32) (u16) temp_s2->position;
        message->mode = 0;
        if (func_001E1E10((s32)temp_s1->position >> 8, temp_s1->position & 0xFF) == 0xFF) {
            if (temp_s1->flag == 0) {
                func_001E42C0(0, -0x78, 0x50, func_001DE210(0x339));
            } else {
                func_001E42C0(0, -0x78, 0x50, 0x103);
            }
            func_001DE820(1);
            func_00260AF0(0, (s32) temp_s1->position, 0xB4, 0xB4);
            message->id = 0x25A;
            message->from = 0U;
            message->to = (s32) temp_s1->position;
            message->mode = 0;
            temp_s1->commands[temp_s1->count] = func_00255A30(message, temp_s1);
            temp_s1->count = (u8) (temp_s1->count + 1);
            temp_s1->stage = (u16) (temp_s1->stage + 1);
        } else {
            func_0027EB00(temp_s1->queue, message, -1);
        }
        break;
    case 1:
        if (func_001F51D0((s32) ((u8 *)(temp_s1->count + (u32)temp_s1))[5]) != 0) {
            if ((s32) temp_s1->position > 0) {
                func_001DE7E0(0);
            }
            return 1;
        }
        temp_v0_6 = temp_s1->position;
        func_001E1E70((s32) temp_v0_6 >> 8, temp_v0_6 & 0xFF, 0, 1);
        func_001E4530();
        message->id = 5;
        message->from = (u32) ((u32) temp_s2->position >> 0x10);
        message->to = (s32) (u16) temp_s2->position;
        message->mode = 0;
        func_0027EB00(temp_s1->queue, message, -1);
        func_001DE820(0);
        func_00260A70(temp_s1, 0);
        temp_s1->stage = (u16) (temp_s1->stage + 1);
        break;
    case 2:
        message->id = 5;
        message->from = (u32) ((u32) temp_s2->position >> 0x10);
        message->to = (s32) (u16) temp_s2->position;
        message->mode = 0;
        func_0027EB00(temp_s1->queue, message, -1);
        temp_v1_2 = func_00249200(temp_s2->card) & 0xFFFF;
        switch (temp_v1_2) {
        case 0x218:
            if (temp_s1->flag != 0) {
                func_001E42C0(0, 0, -0xA0, func_001DE210(func_001E1030((s32)temp_s1->position >> 8, temp_s1->position & 0xFF)));
            } else {
                func_001E42C0(0, 0, -0xA0, 0x106);
            }
            message->id = 0x218;
            message->from = (u32) ((u32) temp_s2->position >> 0x10);
            message->to = (s32) (u16) temp_s2->position;
            message->mode = 0;
            break;
        case 0x21C:
            message->id = 0x21C;
            message->from = (u32) ((u32) temp_s2->position >> 0x10);
            message->to = (s32) (u16) temp_s2->position;
            message->mode = 0;
            break;
        case 0x21D:
            message->id = 0x21D;
            message->from = (u32) ((u32) temp_s2->position >> 0x10);
            message->to = (s32) (u16) temp_s2->position;
            message->mode = 0;
            break;
        case 0x21E:
            message->id = 0x21E;
            message->from = (u32) ((u32) temp_s2->position >> 0x10);
            message->to = (s32) (u16) temp_s2->position;
            message->mode = 0;
            break;
        default:
            message->id = 0x218;
            message->from = (u32) ((u32) temp_s2->position >> 0x10);
            message->to = (s32) (u16) temp_s2->position;
            message->mode = 0;
            break;
        }
        temp_v0_7 = temp_s2->position;
        if ((func_001E0700(temp_v0_7 >> 24, (temp_v0_7 >> 16) & 0xFF) >> 5) == 0) {
            side = 0;
        } else {
            side = 3;
        }
        message->mode = side;
        temp_s1->commands[temp_s1->count] = func_00255A30(message, temp_s1);
        temp_s1->results[temp_s1->count + 1] = 0;
        temp_s1->count = (u8) (temp_s1->count + 1);
        temp_s1->stage = (u16) (temp_s1->stage + 1);
        break;
    case 3:
        if (func_001F51D0((s32) ((u8 *)(temp_s1->count + (u32)temp_s1))[5]) != 0) {
            temp_a1 = temp_s1->timer;
            temp_s1->timer = (s32) (temp_a1 + 1);
            switch (temp_a1) {
            case 1:
                func_00217710(1, 0x4C);
                break;
            case 15:
                temp_v1_3 = func_00249200(temp_s2->card) & 0xFFFF;
                switch (temp_v1_3) {
                case 0x218:
                    func_00217710(1, 0x3B);
                    break;
                case 0x21C:
                    func_00217710(1, 0x4B);
                    break;
                case 0x21D:
                    func_00217710(1, 0x4E);
                    break;
                case 0x21E:
                    func_00217710(1, 0x4F);
                    break;
                }
                break;
            case 16:
                temp_v1_4 = func_00249200(temp_s2->card) & 0xFFFF;
                switch (temp_v1_4) {
                case 0x21D:
                case 0x21E:
                    func_00217710(1, 0x3B);
                    break;
                }
                break;
            }
            if (func_001F52D0((s32) ((u8 *)(temp_s1->count + (u32)temp_s1))[5]) == 2) {
                if (((u8 *)(((u32)temp_s1->count << 2) + (u32)temp_s1))[0x1C] == 0) {
                    temp_v0_8 = temp_s2->position;
                    if ((func_001E0700((s32) (temp_v0_8 >> 0x18), (temp_v0_8 >> 0x10) & 0xFF) >> 5) == 0) {
                        temp_a1_2 = temp_s2->position;
                        func_00248460(temp_a1_2 >> 0x18, (temp_a1_2 >> 0x10) & 0xFF, (temp_s1->flag << 0x10) | temp_s2->card, 0);
                    } else {
                        temp_a1_3 = temp_s2->position;
                        func_00248460((u32) (temp_a1_3 & 0xFFFF) >> 8, temp_a1_3 & 0xFF, (temp_s1->flag << 0x10) | temp_s2->card, 0);
                    }
                    temp_s1->results[temp_s1->count] = 0xFFFF;
                }
            }
            return 1;
        }
        func_001E4530();
        temp_v0_9 = temp_s2->position;
        if ((func_001E0700((s32) (temp_v0_9 >> 0x18), (temp_v0_9 >> 0x10) & 0xFF) >> 5) == 0) {
            temp_v1_5 = temp_s2->position;
            temp_s0 = func_001E1CB0((temp_v1_5 & 0xFFFF) >> 8, temp_v1_5 & 0xFF);
            if (temp_s0 != func_001E1A30((temp_s2->position & 0xFFFF) >> 8, temp_s2->position & 0xFF)) {
                return 1;
            }
            temp_v1_5 = temp_s2->position;
            func_0024F430((u32) (temp_v1_5 & 0xFFFF) >> 8, temp_v1_5 & 0xFF);
        } else {
            temp_v0_10 = temp_s2->position;
            temp_s0_2 = func_001E1CB0(temp_v0_10 >> 0x18, (temp_v0_10 >> 0x10) & 0xFF);
            if (temp_s0_2 != func_001E1A30(temp_s2->position >> 0x18, (temp_s2->position >> 0x10) & 0xFF)) {
                return 1;
            }
            temp_v0_10 = temp_s2->position;
            func_0024F430(temp_v0_10 >> 0x18, (temp_v0_10 >> 0x10) & 0xFF);
        }
        if (func_001DE780() != 0) {
            func_001DE7E0(1);
        }
        func_001E4530();
        return 0;
    default:
        return 1;
    }
    return 1;
}

struct jp_8b329 {
    int eNO;
    unsigned int dwFrom;
    unsigned int dwTo;
    unsigned int dwPar;
};
struct jp_8b5bb {
    int fLoad : 1;
    unsigned char bModNum : 5;
    unsigned short wModule[24];
    unsigned char bModCond[24];
};
struct jp_8b3ce {
    unsigned short wCount_1;
    unsigned short wCount_2;
    unsigned short wLvl;
    unsigned char eID[24];
    int ePos[24];
    struct jp_8b5bb eMod;
    unsigned int fObj;
    unsigned int fObj2;
    unsigned char oNum;
    unsigned char unknown_d5[0x2b];
    unsigned char bCamLvl;
    unsigned short wCamTime;
    unsigned char unknown_104[0xc];
    int nTasakiEfc[0x10c];
};
extern int func_00255AC0_270c30(struct jp_8b3ce *q, int id);
extern int func_0024F430_270c30(int a, int b);
extern int func_001E1E10_b(int a, int b);
extern int func_001E1030_b(int a, int b);
extern void func_00260AF0_b(unsigned char who, int packed, int add, int value);
extern void func_002610D0_b(unsigned char who, int packed, int add, int value);
extern void func_00260A70_270c30(struct jp_8b3ce *Temp, unsigned char b);
extern int func_00261570_b(int a, int b, unsigned char c, unsigned char d);

int func_00270C30(void *eInfo_v, void *Temp_v, int ID)
{
    struct jp_8b329 * eInfo = eInfo_v;
    struct jp_8b3ce * Temp = Temp_v;
    int stored;
    struct jp_8b329 eCall;
    struct jp_8b329 *pCall = &eCall;
    int Unit2;
    int Unit;

    eCall.eNO = 999;
    eCall.dwFrom = 0;
    eCall.dwTo = 0;
    eCall.dwPar = 0;
    if (ID >= 0) {
        func_00255960(Temp);
        Temp->wCount_1 = func_00248E30(eInfo->dwTo, func_00248EA0());
        if ((func_001E0700(eInfo->dwFrom >> 24, (eInfo->dwFrom >> 16) & 0xff) >> 5 == 0 ? 0 : 3) == 0) {
            Unit = eInfo->dwFrom >> 16;
        } else {
            Unit = eInfo->dwFrom & 0xffff;
        }
        if (func_00271740(11, func_001DE540()) == 1 &&
            (func_001E0700(Unit >> 8, Unit & 0xff) & 0x1f) == (func_001E0700(func_001DE540(), 0) & 0x1f)) {
            func_00255AC0_270c30(Temp, 537);
            Temp->wLvl = 2;
            Temp->wCount_2 = 0;
        } else if ((Unit = func_0026AB80(eInfo->dwTo, 41)) < 0) {
            if ((Unit = func_0026AB80(eInfo->dwTo, 43)) < 0) {
                func_00255AC0_270c30(Temp, 537);
                Temp->wLvl = 2;
                Temp->wCount_2 = 0;
            } else if ((Unit2 = func_0026AB80(eInfo->dwTo, 46)) >= 0) {
                func_00255AC0_270c30(Temp, 602);
                func_00255AC0_270c30(Temp, 537);
                func_001F5970(Unit2, 0);
                func_002516D0(Unit2 >> 8, Unit2 & 0xff, 1);
                Temp->fObj = Unit2;
                Temp->wLvl = 0;
                Temp->wCount_2 = 0;
            } else {
                func_00255AC0_270c30(Temp, 602);
                func_00255AC0_270c30(Temp, 537);
                func_001F5970(Unit, 0);
                func_002516D0(Unit >> 8, Unit & 0xff, 1);
                Temp->fObj = Unit;
                Temp->wLvl = 0;
                Temp->wCount_2 = 1;
            }
        } else if ((Unit2 = func_0026AB80(eInfo->dwTo, 46)) >= 0) {
            func_00255AC0_270c30(Temp, 602);
            func_00255AC0_270c30(Temp, 537);
            func_001F5970(Unit2, 0);
            func_002516D0(Unit2 >> 8, Unit2 & 0xff, 1);
            Temp->fObj = Unit2;
            Temp->wLvl = 0;
            Temp->wCount_2 = 0;
        } else {
            func_001DE7E0(0);
            func_00255AC0_270c30(Temp, 602);
            func_00255AC0_270c30(Temp, 547);
            func_001F5970(Unit, 0);
            func_002516D0(Unit >> 8, Unit & 0xff, 1);
            Temp->fObj = Unit;
            Temp->fObj2 = 1;
            Temp->wLvl = 0;
            Temp->wCount_2 = 0;
        }
        pCall->eNO = 602;
        pCall->dwFrom = eInfo->dwFrom >> 16;
        pCall->dwTo = eInfo->dwFrom & 0xffff;
        pCall->dwPar = 0;
        func_0027EB00(&Temp->nTasakiEfc, pCall, 0);
        return 1;
    }
    if (Temp->eMod.fLoad == 0) {
        pCall->eNO = 602;
        pCall->dwFrom = eInfo->dwFrom >> 16;
        pCall->dwTo = eInfo->dwFrom & 0xffff;
        pCall->dwPar = 0;
        func_0027EB00(&Temp->nTasakiEfc, pCall, -1);
        if (func_00255B50(Temp) == 1) {
            Temp->eMod.fLoad = -1;
        }
        



        goto one;
    } else {
        switch (Temp->wLvl) {
        case 0:
            func_001DE7E0(0);
            pCall->eNO = 602;
            pCall->dwFrom = eInfo->dwFrom >> 16;
            pCall->dwTo = eInfo->dwFrom & 0xffff;
            pCall->dwPar = 0;
            if (func_001E1E10_b(Temp->fObj >> 8, Temp->fObj & 0xff) == 255) {
                if (Temp->wCount_2 == 0 && Temp->fObj2 == 0) {
                    func_001E42C0(0, -120, 80, func_001DE210(825));
                } else {
                    func_001E42C0(0, -120, 80, 259);
                }
                func_001DE820(1);
                func_00260AF0_b(0, Temp->fObj, 180, 180);
                pCall->eNO = 602;
                pCall->dwFrom = 0;
                pCall->dwTo = Temp->fObj;
                pCall->dwPar = 0;
                

                if ((stored = (Temp->eID[Temp->oNum] = func_00255A30(pCall, Temp))) >= 0) {
                    Temp->ePos[Temp->oNum] = 0;
                    Temp->oNum++;
                    Temp->wLvl++;
                } else {
                    func_001E4530();
                    return 0;
                }
            } else {
                func_0027EB00(&Temp->nTasakiEfc, pCall, -1);
            }
            break;
        case 1:
            func_001DE7E0(0);
            if (func_001F51D0(Temp->eID[Temp->oNum - 1]) != 0) {
                return 1;
            }
            func_001E1E70(Temp->fObj >> 8, Temp->fObj & 0xff, 0, 1);
            if (Temp->fObj2 != 0) {
                func_001DE820(1);
                func_002610D0_b(0, (eInfo->dwTo == 0 ? 1 : 0) << 8, 180, 180);
                Temp->wLvl = 16;
            } else {
                func_001DE7E0(1);
                pCall->eNO = 5;
                pCall->dwFrom = eInfo->dwFrom >> 16;
                pCall->dwTo = eInfo->dwFrom & 0xffff;
                pCall->dwPar = 0;
                func_0027EB00(&Temp->nTasakiEfc, pCall, -1);
                func_001DE820(0);
                func_00260A70_270c30(Temp, 0);
                Temp->wLvl++;
            }
            break;
        case 2:
            pCall->eNO = 5;
            pCall->dwFrom = eInfo->dwFrom >> 16;
            pCall->dwTo = eInfo->dwFrom & 0xffff;
            pCall->dwPar = 0;
            func_0027EB00(&Temp->nTasakiEfc, pCall, -1);
            if (Temp->wCount_2 == 1) {
                func_001E42C0(0, 0, -160, func_001DE210(func_001E1030_b(Temp->fObj >> 8, Temp->fObj & 0xff)));
            } else {
                func_001E42C0(0, 0, -160, 268);
            }
            pCall->eNO = 537;
            pCall->dwFrom = eInfo->dwFrom >> 16;
            pCall->dwTo = eInfo->dwFrom & 0xffff;
            pCall->dwPar = Temp->wCount_1 << 16 | (Temp->wCount_2 << 8 | (func_001E0700(eInfo->dwFrom >> 24, (eInfo->dwFrom >> 16) & 0xff) >> 5 ? 3 : 0));
            if ((stored = (Temp->eID[Temp->oNum] = func_00255A30(pCall, Temp))) >= 0) {
                Temp->ePos[Temp->oNum] = 0;
                Temp->oNum++;
                Temp->wLvl++;
            } else {
                func_001E4530();
                return 0;
            }
            break;
        case 3:
            if (func_001F51D0(Temp->eID[Temp->oNum - 1]) != 0) {
                switch (Temp->fObj2++) {
                case 1:
                    func_00217710(1, 76);
                    break;
                case 15:
                    func_00217710(1, 77);
                    break;
                case 16:
                    func_00217710(1, 59);
                    break;
                }
                if (func_001F52D0(Temp->eID[Temp->oNum - 1]) == 2) {
                    if ((unsigned char)Temp->ePos[Temp->oNum - 1] == 0) {
                        if (func_001E0700(eInfo->dwFrom >> 24, (eInfo->dwFrom >> 16) & 0xff) >> 5 == 0) {
                            func_00248460(eInfo->dwFrom >> 24, (eInfo->dwFrom >> 16) & 0xff, Temp->wCount_2 << 16 | eInfo->dwPar, eInfo->dwTo & 0xff);
                            func_0024F430_270c30((eInfo->dwFrom & 0xffff) >> 8, eInfo->dwFrom & 0xff);
                        } else {
                            func_00248460((eInfo->dwFrom & 0xffff) >> 8, eInfo->dwFrom & 0xff, Temp->wCount_2 << 16 | eInfo->dwPar, eInfo->dwTo & 0xff);
                            func_0024F430_270c30(eInfo->dwFrom >> 24, (eInfo->dwFrom >> 16) & 0xff);
                        }
                        Temp->ePos[Temp->oNum - 1] = 0xffff;
                    }
                }
                return 1;
            }
            func_001E4530();
            return 0;
        case 16:
            func_001DE7E0(0);
            func_001E42C0(0, -120, 80, func_001DE210(814));
            pCall->eNO = 547;
            pCall->dwFrom = (eInfo->dwTo == 0 ? 1 : 0) << 8;
            pCall->dwTo = eInfo->dwTo << 8;
            pCall->dwPar = Temp->wCount_1;
            if ((stored = (Temp->eID[Temp->oNum] = func_00255A30(pCall, Temp))) >= 0) {
                Temp->oNum++;
                Temp->wLvl++;
            } else {
                func_001E4530();
                return 0;
            }
            break;
        case 17:
            func_001DE7E0(0);
            if (func_001F51D0(Temp->eID[Temp->oNum - 1]) != 0) {
                if (Temp->wCamTime++ == 6) {
                    func_00261570_b(30, eInfo->dwTo << 8, 100, 180);
                }
                break;
            }
            if (func_001E0700(eInfo->dwFrom >> 24, (eInfo->dwFrom >> 16) & 0xff) >> 5 == 0) {
                func_0024F430_270c30((eInfo->dwFrom & 0xffff) >> 8, eInfo->dwFrom & 0xff);
            } else {
                func_0024F430_270c30(eInfo->dwFrom >> 24, (eInfo->dwFrom >> 16) & 0xff);
            }
            func_001DF490(eInfo->dwTo, 1, Temp->wCount_1);
            func_001E4530();
            func_001DE820(0);
            func_00260A70_270c30(Temp, 0);
            if (func_001DE780() != 0) {
                func_001DE7E0(1);
            }
            return 0;
        }
    one:
        return 1;
    }
}

typedef struct State_00271630 {
    u8 pad[4];
    u16 count;
    u8 handle;
} State_00271630;

void func_0024F430(u32, s32);

s32 func_00271630(void *arg0, void *arg1, s32 arg2) {
    s32 values[4];
    State_00271630 *state = arg1;
    s32 *packet = values;
    u32 value;

    values[0] = 0x3E7;
    values[1] = 0;
    values[2] = 0;
    values[3] = 0;

    if (arg2 >= 0) {
        func_00255960(state);
        func_00255AC0(state, 0x25B);
        return 1;
    }

    switch (state->count) {
    case 0:
        if (func_00255B50(state) == 1) {
            packet[0] = 0x25B;
            packet[1] = 0;
            packet[2] = *(u32 *)((u8 *)arg0 + 8);
            packet[3] = 0;
            state->handle = func_00255A30(packet, state);
            state->count++;
        }
        break;
    default:
        if (func_001F51D0(state->handle) != 0) {
            return 1;
        }
        value = *(u32 *)((u8 *)arg0 + 8);
        func_0024F430(value >> 8, value & 0xFF);
        func_001E4530();
        return 0;
    }
    return 1;
}

s32 func_00271740(s32 arg0, s32 arg1) {
    if (func_00266F70(0x58, (arg1 == 0) ? 1 : 0) > 0) {
        return 0;
    }
    return func_001E0C00(arg1, 0, arg0, 0);
}

s32 func_002717A0(s32 arg0) {
    s32 ret;

    switch (arg0) {
    case 1:
    case 7:
        ret = 5;
        break;
    case 9:
        ret = 0;
        break;
    case 10:
        ret = 1;
        break;
    case 16:
        ret = 4;
        break;
    case 20:
        ret = 9;
        break;
    default:
        ret = 7;
        break;
    }

    return ret;
}

s32 func_00271830(s32 arg0) {
    extern s32 func_001E08F0(s32, s32, s32);

    if (func_00271740(8, arg0) != 0) {
        switch (func_001E0690(arg0, 0) & 0x1F) {
        case 0:
        case 6:
        case 12:
        case 14:
            return func_001E08F0(arg0, 0, 0) > 6 ? 2 : 1;
        case 4:
        case 13:
            if (func_001E08F0(arg0, 0, 0) > 5) {
                return 2;
            }
            return 1;
        case 20:
            return 1;
        default:
            return 0;
        }
    }
    return 0;
}

s32 func_00271950(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 x;
    s32 half;
    s32 xEnd;
    s32 yStart;
    s32 yEnd;
    s32 y;

    half = arg4 >> 1;
    x = func_00250860(0, arg0 - half);
    if (arg0 + half >= 7) {
        xEnd = 6;
    } else {
        xEnd = arg0 + half;
    }
    yStart = func_00250860(0, arg1 - half);
    if (arg1 + half >= 7) {
        yEnd = 6;
    } else {
        yEnd = arg1 + half;
    }
    for (; x <= xEnd; x++) {
        for (y = yStart; y <= yEnd; y++) {
            if (x == arg2 && y == arg3) {
                return 1;
            }
        }
    }
    return 0;
}

s32 func_00271A40(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_s0;

    temp_s0 = func_001E1090(arg0, 0);
    if (func_00271740(9, arg0) != 0) {
        return (func_00271950(temp_s0 & 0xFF, temp_s0 >> 8, arg1, arg2, 5) != 0) ? 1 : 0;
    } else {
        return (func_00271950(temp_s0 & 0xFF, temp_s0 >> 8, arg1, arg2, 3) != 0) ? 1 : 0;
    }
}

s32 func_00271AF0(void *arg0, s32 arg1, s32 arg2) {
    extern s32 func_001E08F0();
    s32 score;
    s32 kind;
    s32 player;
    s32 other;

    score = 0;
    if (arg0 == NULL) {
        return 0;
    }
    player = func_00250370(arg0);
    kind = ((u8 *)arg0)[0x3E] & 0x1F;
    other = player == 0 ? 1 : 0;
    if (func_00271F00((arg2 << 8) | arg1, player, kind, 10)) {
        score += func_001E08F0(player, 0, 0) * 100 >= 500 ? 500 : func_001E08F0(player, 0, 0) * 100;
    }
    if (func_00271A40(other, arg1, arg2)) {
        if (func_00271740(14, other) && func_00271C90(other, kind)) {
            score -= func_001E08F0(other, 0, 0) * 100 >= 500 ? 500 : func_001E08F0(other, 0, 0) * 100;
        }
    }
    return score;
}

s32 func_00271C90(s32 arg0, s32 arg1) {
    s32 result;

    switch (func_001E0690(arg0, 0) & 0x1F) {
    case 1:
        if (arg1 == 7) {
            result = 1;
        } else {
            result = 0;
        }
        return result;
    case 2:
        if (arg1 == 3) {
            result = 1;
        } else {
            result = 0;
        }
        return result;
    case 3:
        return ((u32)arg1 < 2) ? 1 : 0;
    case 5:
        if (arg1 == 12) {
            result = 1;
        } else {
            result = 0;
        }
        return result;
    case 6:
        if (arg1 == 9 || arg1 == 12) {
            return 1;
        }
        return 0;
    case 7:
        if (arg1 == 1) {
            result = 1;
        } else {
            result = 0;
        }
        return result;
    case 9:
        if (arg1 == 13) {
            result = 1;
        } else {
            result = 0;
        }
        return result;
    case 11:
        return ((u32)(arg1 - 5) < 2) ? 1 : 0;
    case 12:
        if (arg1 == 15) {
            result = 1;
        } else {
            result = 0;
        }
        return result;
    case 15:
        if (arg1 == 2 || arg1 == 14) {
            return 1;
        }
        return 0;
    case 16:
        if (arg1 == 14 || arg1 == 17) {
            return 1;
        }
        return 0;
    case 17:
        if (arg1 == 4) {
            result = 1;
        } else {
            result = 0;
        }
        return result;
    default:
        return 0;
    }
    return result;
}

s32 func_00271E40(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_s0;
    s32 temp_s1;
    s32 temp_s2;

    temp_s0 = func_001E1090(arg0, arg1);
    temp_s2 = func_0024DE70(arg0, arg1);
    temp_s1 = func_001E0700(arg0, arg1) & 0x1F;
    if (func_00271A40(temp_s2, temp_s0 & 0xFF, temp_s0 >> 8) != 0 && func_00271740(arg2, temp_s2) != 0 &&
        temp_s1 == (func_001E0690(temp_s2, 0) & 0x1F)) {
        return 1;
    }
    return 0;
}

s32 func_00271F00(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {

    if (func_00271A40(arg1, arg0 & 0xFF, arg0 >> 8) != 0 && func_00271740(arg3, arg1) != 0 &&
        arg2 == (func_001E0690(arg1, 0) & 0x1F)) {
        return 1;
    }
    return 0;
}

s32 func_00271F90(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 temp_s0;
    s32 temp_s1;

    temp_s1 = func_0024DE70(arg0, arg1);
    temp_s0 = func_001E0700(arg0, arg1) & 0x1F;
    if (func_00271A40(temp_s1, arg2, arg3) != 0 && func_00271740(arg4, temp_s1) != 0 &&
        temp_s0 == (func_001E0690(temp_s1, 0) & 0x1F)) {
        return 1;
    }
    return 0;
}

s32 func_00272050(s32 arg0, s32 arg1) {

    switch (func_001E0690(arg0, 0) & 0x1F) {
    case 8:
        return (arg1 == 2) ? 1 : 0;
    case 11:
        return (arg1 == 0x10) ? 1 : 0;
    case 17:
        return ((u32)(arg1 - 5) < 2U) ? 1 : 0;
    case 19:
        return (arg1 == 0) ? 1 : 0;
    }
    return 0;
}

s32 func_002720F0(s32 arg0, s32 arg1) {
    s32 result;

    switch (func_001E0690(arg0, 0) & 0x1F) {
    case 8:
        result = (arg1 == 7) ? 1 : 0;
        break;
    case 11:
        result = (arg1 == 9) ? 1 : 0;
        break;
    case 17:
        if (arg1 == 2 || arg1 == 19) {
            result = 1;
        } else {
            result = 0;
        }
        break;
    case 18:
        result = (arg1 == 10) ? 1 : 0;
        break;
    case 19:
        result = (arg1 == 18) ? 1 : 0;
        break;
    default:
        result = 0;
        break;
    }
    return result;
}

u32 func_00272210(s32 arg0, s32 arg1) {
    s32 i;
    s32 count;
    s32 result;
    s32 owner;
    s32 y;
    s32 x;
    s32 position;

    count = func_0024E910(arg0);
    result = arg0;
    for (i = 0; i < count; i++) {
            position = func_0024EC50(arg0, i);
            x = position >> 8;
            y = position & 0xFF;
            owner = func_0024DE70(x, y);
            if ((func_00271E40(x, y, 0xB) != 0) && (owner != arg1)) {
                result = func_0024C7D0((u32) result, x, y);
            } else if ((func_00267700(x, y) != 0) && (owner != arg1)) {
                result = func_0024C7D0((u32) result, x, y);
            }
    }
    return (u32) result;
}

u32 func_00272330(s32 arg0, s32 arg1) {
    s32 i;
    s32 remaining;
    s32 card;
    s32 position;
    s32 y;
    s32 x;
    s32 count;
    s32 packed;

    count = func_0024E910(arg0);
    remaining = arg0;
    for (i = 0; i < count; i++) {
            packed = func_0024EC50(arg0, i);
            x = packed >> 8;
            y = packed & 0xFF;
            card = func_0024DE70(x, y);
            position = func_001E1090(card, 0);
            if (func_00271E40(x, y, 0xB) != 0 && card != arg1) {
                func_001E42C0(0, -0x78, 0x50, 0x10E);
                func_00260490(position & 0xFF, position >> 8, 0,
                             func_00271740(9, card), 1, 1, 0xB);
                remaining = func_0024C7D0((u32) remaining, x, y);
            } else if (func_00267700(x, y) != 0 && card != arg1) {
                func_001E42C0(0, 0, 0x50, func_001DE210(0x53));
                remaining = func_0024C7D0((u32) remaining, x, y);
            }
    }
    return (u32) remaining;
}

s32 func_002724C0(s32 arg0) {
    return func_00271740(9, arg0) ? 5 : 3;
}

s32 func_002724F0(s32 phase, s32 *res) {
    extern s32 func_001E1640();
    extern s32 func_001E1580();
    extern s32 func_001E14B0();
    extern s32 func_001E1030();
    extern s32 func_001E1520();
    extern s32 func_001E15E0();
    extern s32 func_001DE550();
    extern s32 func_001DE560();
    s32 row;
    s32 a;
    s32 v;
    s32 pos;
    s32 col;
    s32 player;
    s32 b;
    s32 c;
    s32 vy;
    s32 other;
    s32 hp;
    s32 hi;
    s32 lo;
    s32 n;
    s32 vx;
    s32 i;
    s32 mine;
    s32 w;

    player = func_001DE540();
    switch (phase) {
    case 0:
        if (func_00271740(5, player)) {
            res[0] = 8;
            res[1] = 0;
            res[2] = player;
            res[3] = 100;
            return ((phase + 1) << 16) | 1;
        }
        return (phase + 1) << 16;
    case 1:
        return ((phase + 1) << 16) | func_0024FEB0(res);
    case 2:
        pos = func_001E1090(player, 0);
        row = 0;
        a = 0;
        b = 0;
        c = 0;
        hi = pos >> 8;
        lo = pos & 0xFF;
        for (; row < 7; row++) {
            for (col = 0; col < 7; col++) {
                v = func_001E3790(row, col);
                if (v < 0) {
                    continue;
                }
                vx = v >> 8;
                vy = v & 0xFF;
                if (player == func_0024DE70(vx, vy)) {
                    continue;
                }
                if (func_00271950(lo, hi, row, col, func_002724C0(player)) == 0) {
                    continue;
                }
                if ((func_001E0700(vx, vy) >> 5) == 0) {
                    if (func_00271740(0x10, player)) {
                        if (func_002720F0(player, func_001E0700(vx, vy) & 0x1F) && vy != 0) {
                            a = func_0024C780(a, vx, vy);
                        }
                    }
                    if (func_00271740(0xF, player) && func_00272050(player, func_001E0700(vx, vy) & 0x1F) &&
                        vy != 0 && func_001E1640(vx, vy) == 0) {
                        b = func_0024C780(b, vx, vy);
                    }
                }
                if (func_00271740(0xD, player) && func_001E2100(vx, vy, 4) == 0 && vy != 0) {
                    c = func_0024C780(c, vx, vy);
                }
            }
        }
        if (a > 0 || b > 0 || c > 0) {
            res[0] = 0x71;
            res[1] = a | 0x80000000;
            res[2] = b;
            res[3] = c;
            return ((phase + 1) << 16) | 1;
        }
        return (phase + 1) << 16;
    case 3:
        for (i = 1; i <= 5; i++) {
            if (func_001E2100(player, i, 4) == 1) {
                func_00215B10(player, func_001E1030(player, i), 0, 4);
            } else {
                func_00215B10(player, func_001E1030(player, i), 0, 2);
            }
        }
        n = func_00266DF0(0x55);
        for (i = 1; i <= 11; i++) {
            mine = func_001E1090(player, i);
            if (func_00266DF0(0x47) <= 0) {
                if ((hp = func_001E1580(player, i)) > 0 && player == func_00250360(player, i) && func_001E14B0(player, i) == 0 && hp < 0xFF) {
                    if (n > 0) {
                        func_001E1520(player, i, func_00250860(0, hp - 2));
                    } else {
                        func_001E1520(player, i, hp - 1);
                    }
                }
                if ((hp = func_001E1580((player == 0) ? 1 : 0, i)) > 0 && player == func_00250360((player == 0) ? 1 : 0, i) &&
                    func_001E14B0((player == 0) ? 1 : 0, i) == 0 && hp < 0xFF) {
                    if (n > 0) {
                        func_001E1520((player == 0) ? 1 : 0, i, func_00250860(0, hp - 2));
                    } else {
                        func_001E1520((player == 0) ? 1 : 0, i, hp - 1);
                    }
                }
            }
            other = func_001E1090((player == 0) ? 1 : 0, 0);
            if (func_001DF540(player, i)) {
                if (!(func_00271740(0xF, (player == 0) ? 1 : 0) &&
                      func_00272050((player == 0) ? 1 : 0, func_001E0700(player, i) & 0x1F) &&
                      func_00271950(other & 0xFF, other >> 8, mine & 0xFF, mine >> 8,
                                    func_002724C0((player == 0) ? 1 : 0))) &&
                    func_00266A80(player, i) == 0) {
                    func_001E15E0(player, i, 0);
                }
            }
            mine = func_001E1090((player == 0) ? 1 : 0, i);
            other = func_001E1090(player, 0);
            if (func_001DF540((player == 0) ? 1 : 0, i)) {
                if (!(func_00271740(0xF, player) &&
                      func_00272050(player, func_001E0700((player == 0) ? 1 : 0, i) & 0x1F) &&
                      func_00271950(other & 0xFF, other >> 8, mine & 0xFF, mine >> 8, func_002724C0(player))) &&
                    func_00266A80((player == 0) ? 1 : 0, i) == 0) {
                    func_001E15E0((player == 0) ? 1 : 0, i, 0);
                }
            }
        }
        for (i = 0; i <= 11; i++) {
            func_001E1420(player, i, 0);
            func_001E1420((player == 0) ? 1 : 0, i, 0);
        }
        return (phase + 1) << 16;
    case 4:
        for (i = 0; i < 8; i++) {
            v = func_0024E410(player, i);
            if (v < 0) {
                continue;
            }
            vy = v & 0xFF;
            vx = v >> 8;
            w = func_001E3790(vy, vx);
            if (w >= 0) {
                if (player == func_00250360(w >> 8, w & 0xFF)) {
                    if (func_001E22B0(vy, vx) != 8) {
                        return (phase + 1) << 16;
                    }
                }
            } else {
                if (func_001E22B0(vy, vx) != 8) {
                    return (phase + 1) << 16;
                }
            }
        }
        return ((phase + 1) << 16) | 5;
    case 5:
        if (player != func_001DE550()) {
            if (func_001DE560() >= 100) {
                return 0xFF0008;
            }
        }
        return 0xFF0000;
    }
    return 0xFF0000;
}

INCLUDE_ASM("asm/nonmatchings/main_077", func_00272CC0);

typedef struct Context_00273460 {
    u8 pad0[8];
    s32 cards;
} Context_00273460;

typedef struct State_00273460 {
    u16 alpha;
    u16 pad2;
    u16 phase;
    u8 ids[0x1A];
    s32 cards[45];
    u8 count;
    u8 padD5[0x2D];
    u16 timer;
} State_00273460;

typedef struct Setup_00273460 {
    s32 card;
    s32 x;
    s32 y;
    s32 z;
} Setup_00273460;

void func_0024F370(s32, s32);

s32 func_00273460(void *arg0, void *arg1, s32 arg2) {
    Setup_00273460 setup;
    s32 complete;
    Setup_00273460 *config = &setup;
    State_00273460 *walk;
    u8 *id;
    s32 index;
    s32 card;
    State_00273460 *state = arg1;
    Context_00273460 *context = arg0;

    setup.card = 999;
    setup.x = 0;
    setup.y = 0;
    setup.z = 0;
    complete = 0;
    func_001DE7E0(0);
    if (arg2 >= 0) {
        func_00255960(state);
        func_00260020(context, state, arg2, -1, 1, 1);
        state->alpha = 128;
        func_00255AC0(state, 612);
        for (arg2 = 0; arg2 < func_0024E910(context->cards); arg2++) {
            card = func_0024EC50(context->cards, arg2);
            func_001F5970(card, 0);
            func_002516D0(card >> 8, card & 255, 1);
        }
        func_00260740(30);
        return 1;
    }
    switch (state->phase) {
    case 0:
        arg2 = 0;
        if (state->alpha > 48) {
            state->alpha -= 15;
        } else {
            for (arg2 = 0; arg2 < func_0024E910(context->cards); arg2++) {
                if (func_001F5EC0(func_0024EC50(context->cards, arg2)) != 0) {
                    complete++;
                }
            }
            if (complete == func_0024E910(context->cards)) {
                if (func_00255B50(state) == 1) {
                    if (state->timer++ >= 46) {
                        if (complete == 1) {
                            func_00260AF0(0, func_0024EC50(context->cards, 0), 100, 180);
                        }
                        func_001E42C0(0, -120, 80, 276);
                        func_0025F720(context, state, config, 612);
                        state->timer = 0;
                        state->phase++;
                    }
                }
            }
            state->alpha = 48;
        }
        if (state->alpha < 48) {
            state->alpha = 48;
        }
        func_001F6CF0((u8)state->alpha);
        break;
    case 1:
        index = 0;
        walk = state;
        for (; index < state->count; index++) {
            id = &state->ids[index];
            if (func_001F51D0(*id) == 1) {
                func_00261680((u16)walk->cards[0]);
                if ((walk->cards[0] >> 16) == 0) {
                    if (state->timer++ >= 32) {
                        card = walk->cards[0];
                        func_002500C0((card & 65535) >> 8, card & 255, -1, 1, 3);
                        walk->cards[0] |= 0x10000;
                    }
                }
                if (func_001F52D0(*id) == 2) {
                    card = walk->cards[0];
                    if (card >= 0) {
                        func_001F5970(card & 65535, 1);
                        card = walk->cards[0];
                        func_0024F370((card & 65535) >> 8, card & 255);
                        walk->cards[0] = -1;
                    }
                }
            } else {
                complete++;
            }
            walk = (State_00273460 *)((u8 *)walk + 4);
        }
        if (complete >= state->count) {
            func_00260020(context, state, arg2, 1, 0, 1);
            state->timer = 0;
            func_001E4530();
            func_00260A70(state, 16);
            state->phase++;
        }
        break;
    default:
        state->alpha += 15;
        if (state->alpha > 128) {
            state->alpha = 128;
        }
        func_001F6CF0((u8)state->alpha);
        if (state->alpha == 128) {
            if (state->timer++ > 16 && func_0025FD90() == 1) {
                if (func_001DE780() != 0) {
                    func_001DE7E0(1);
                }
                func_001E4530();
                return 0;
            }
        }
        break;
    }
    return 1;
}

typedef struct Masks_002738B0 {
    u32 unknown;
    u32 first : 22;
    u32 firstFlags : 10;
    s32 second;
    u32 third : 22;
    u32 thirdFlags : 9;
    u32 inverted : 1;
} Masks_002738B0;

typedef struct State_002738B0 {
    u16 player;
    u16 unknown02;
    u16 step;
    u8 handles[0x1A];
    s32 counter;
    u8 unknown24[0xB0];
    u8 count;
    u8 unknownD5[0x2D];
    u16 ticks;
} State_002738B0;

typedef struct Command_002738B0 {
    s32 id;
    s32 flags;
    s32 position;
    s32 argument;
} Command_002738B0;

void func_0024F370(s32, s32);

s32 func_002738B0(void *arg0, void *arg1, s32 arg2) {
    extern s32 func_001E15E0();
    Command_002738B0 command;
    Command_002738B0 *cmd = &command;
    Masks_002738B0 *masks = arg0;
    State_002738B0 *state = arg1;
    s32 position;
    s32 player;
    s32 position0;
    s32 i;
    s32 ready;
    s32 column;
    s32 row;
    s32 secondIndex;
    s32 secondCount;
    s32 thirdIndex;
    s32 thirdCount;
    s32 firstCount;
    s32 firstIndex;
    s32 packed;

    command.id = 999;
    command.flags = 0;
    command.position = 0;
    command.argument = 0;
    func_001DE7E0(0);
    if (arg2 >= 0) {
        func_00255960(state);
        if (((u32 *)masks)[3] >> 31) {
            player = (func_001DE540() == 0) ? 1 : 0;
        } else {
            player = func_001DE540();
        }
        state->player = player;
        position = func_001E1090(state->player, 0);
        func_00260AF0(0, state->player << 8, 300, 300);
        func_001E42C0(0, -120, 80, 270);
        if (masks->first) {
            func_00260490(position & 0xFF, position >> 8, 0,
                         func_00271740(9, state->player), 1, 1, 16);
        } else if (masks->second) {
            func_00260490(position & 0xFF, position >> 8, 0,
                         func_00271740(9, state->player), 1, 1, 15);
        } else if (masks->third) {
            func_00260490(position & 0xFF, position >> 8, 0,
                         func_00271740(9, state->player), 1, 1, 13);
        }
        func_00255AC0(state, 0x265);
        if (masks->first) {
            func_00255AC0(state, 0x25B);
        }
        if (masks->second) {
            func_00255AC0(state, 0x1F4);
        }
        if (masks->third) {
            func_00255AC0(state, 0x201);
        }
        return 1;
    }

    switch (state->step) {
    case 0:
        if (func_00255B50(state) == 1) {
            position0 = func_001E1090(state->player, 0);
            func_00260490(position0 & 0xFF, position0 >> 8, 0,
                         func_00271740(9, state->player), 0, -1, 16);
            cmd->id = 0x265;
            cmd->flags = 0;
            cmd->position = state->player << 8;
            cmd->argument = 0;
            state->handles[0] = func_00255A30((s32 *)cmd, state);
            state->counter = 0;
            state->step++;
        }
        break;
    case 1:
        if (func_001F51D0(state->handles[0]) == 1) {
            return 1;
        }
        func_00260740(16);
        state->step++;
        return 1;
    case 2:
        if (state->ticks++ >= 16) {
            if (masks->first) {
                func_0025F990(masks, state, (s32 *)cmd, 0x25B);
            }
            if (masks->second) {
                func_0025F720(masks, state, (s32 *)cmd, 0x1F4);
            }
            if (masks->third) {
                func_0025F820(masks, state, (s32 *)cmd, 0x201);
            }
            state->step++;
        }
        return 1;
    case 3:
        i = 0;
        ready = 0;
        while (i < state->count) {
            if (func_001F51D0(state->handles[i]) == 0) {
                ready++;
            }
            i++;
        }
        if (state->count == ready) {
            state->step++;
        }
        return 1;
    case 4:
        firstCount = func_0024E910(masks->first);
        for (firstIndex = 0; firstIndex < firstCount; firstIndex++) {
            packed = func_0024EC50(masks->first, firstIndex);
            func_0024F370(packed >> 8, packed & 0xFF);
        }
        secondCount = func_0024E910(masks->second);
        for (secondIndex = 0; secondIndex < secondCount; secondIndex++) {
            packed = func_0024EC50(masks->second, secondIndex);
            row = packed >> 8;
            column = packed & 0xFF;
            func_001E15E0(row, column, 255);
            func_001E1E70(row, column, 0, 1);
        }
        thirdCount = func_0024E910(masks->third);
        for (thirdIndex = 0; thirdIndex < thirdCount; thirdIndex++) {
            packed = func_0024EC50(masks->third, thirdIndex);
            func_002516D0(packed >> 8, packed & 0xFF, 1);
        }
        func_001E4530();
        func_00260A70(state, 16);
        state->ticks = 0;
        state->step++;
        break;
    default:
        if (state->ticks++ > 16) {
            if (func_001DE780() != 0) {
                func_001DE7E0(1);
            }
            func_001E4530();
            return 0;
        }
        break;
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_077", func_00273E60);

struct jp_6989c {
    int eNO;
    unsigned int dwFrom;
    unsigned int dwTo;
    unsigned int dwPar;
};
struct jp_68cb4 {
    int fLoad : 1;
    unsigned char bModNum : 5;
    unsigned short wModule[24];
    unsigned char bModCond[24];
};
struct jp_69942 {
    unsigned short wCount_1;
    unsigned short wCount_2;
    unsigned short wLvl;
    unsigned char eID[24];
    int ePos[24];
    struct jp_68cb4 eMod;
    unsigned int fObj;
    unsigned int fObj2;
    unsigned char oNum;
    unsigned char unknown_d5[0xb];
    int camDat[8];
    unsigned char bCamLvl;
    unsigned short wCamTime;
    unsigned char unknown_104[0xc];
    int nTasakiEfc[0x10c];
};
extern int func_00255AC0_b(struct jp_69942 *q, int id);
extern void func_00260AF0_b(unsigned char who, int packed, int add, int value);
extern void func_00260A70_b(struct jp_69942 *Temp, unsigned char b);
extern void func_002503B0_b(int a, int b, unsigned char n);
extern int func_001E1E10_b(int a, int b);
extern int func_001E1CB0_b(int a, int b);
extern int func_001DE2A0_b(int side);

int func_002747A0(void *eInfo_v, void *Temp_v, int ID)
{
    struct jp_6989c * eInfo = eInfo_v;
    struct jp_69942 * Temp = Temp_v;
    int stored;
    struct jp_6989c eCall;
    struct jp_6989c *pCall = &eCall;
    int temp;
    int i;
    eCall.eNO = 999;
    eCall.dwFrom = 0;
    eCall.dwTo = 0;
    eCall.dwPar = 0;
    func_001DE7E0(0);
    if (eInfo == 0 || Temp == 0 || pCall == 0) {
        func_001E4530();
        return 0;
    }
    if (ID >= 0) {
        func_00255960(Temp);
        Temp->wCount_1 = 128;
        if (((eInfo->dwPar >> 20) & 3) != 0 || ((eInfo->dwPar >> 22) & 3) != 0) {
            func_00255AC0_b(Temp, 513);
        }
        func_00255AC0_b(Temp, 604);
        func_00255AC0_b(Temp, 605);
        func_00260AF0_b(0, (unsigned short)eInfo->dwFrom, 300, 280);
        return 1;
    }
    switch (Temp->bCamLvl) {
    case 0:
        if (Temp->wCamTime++ == 0) {
            func_00217710(0, 39);
            func_001A86A0(6);
            func_00260AF0_b(12, (unsigned short)eInfo->dwFrom, 100, 180);
            return 1;
        }
        if (Temp->wCamTime >= 12) {
            func_001A86A0(4);
        }
        if (Temp->wCamTime >= 24) {
            if (func_001E1E10_b((eInfo->dwFrom & 0xFFFF) >> 8, eInfo->dwFrom & 0xFF) == 255) {
                if (func_001E1CB0_b((eInfo->dwFrom & 0xFFFF) >> 8, eInfo->dwFrom & 0xFF) == 128) {
                    if (func_001F5EC0((unsigned short)eInfo->dwFrom) != 0) {
                        func_001A86A0(0);
                        func_00260AF0_b(0, (unsigned short)eInfo->dwTo, 300, 280);
                        Temp->wCamTime = 0;
                        Temp->bCamLvl++;
                    }
                }
            }
        }
        return 1;
    case 1:
        if (Temp->wCamTime++ == 0) {
            func_00217710(0, 39);
            func_001A86A0(6);
            func_00260AF0_b(12, (unsigned short)eInfo->dwTo, 100, 180);
            return 1;
        }
        if (Temp->wCamTime >= 12) {
            func_001A86A0(4);
        }
        if (Temp->wCamTime >= 24) {
            if (func_001E1E10_b((eInfo->dwTo & 0xFFFF) >> 8, eInfo->dwTo & 0xFF) == 255) {
                if (func_001E1CB0_b((eInfo->dwTo & 0xFFFF) >> 8, eInfo->dwTo & 0xFF) == 128) {
                    if (func_001F5EC0((unsigned short)eInfo->dwTo) != 0) {
                        func_001A86A0(0);
                        func_00260A70_b(Temp, 0);
                        Temp->wCamTime = 0;
                        Temp->bCamLvl++;
                    }
                }
            }
        }
        return 1;
    }
    switch (Temp->wLvl) {
    case 0:
        if (func_00255B50(Temp) == 1) {
            func_001F5970((unsigned short)eInfo->dwFrom, 1);
            func_001F5970((unsigned short)eInfo->dwTo, 1);
            if (((eInfo->dwPar >> 20) & 3) != 0) {
                func_001E42C0(0, -120, 80, 260);
                pCall->eNO = 513;
                pCall->dwFrom = 0;
                pCall->dwTo = (unsigned short)eInfo->dwFrom;
                pCall->dwPar = 0;
                

                if ((stored = (Temp->eID[Temp->oNum] = func_00255A30(pCall, Temp))) >= 0) {
                    Temp->oNum++;
                }
            }
            if (((eInfo->dwPar >> 22) & 3) != 0) {
                func_001E42C0(0, -120, 80, 260);
                pCall->eNO = 513;
                pCall->dwFrom = 0;
                pCall->dwTo = (unsigned short)eInfo->dwTo;
                pCall->dwPar = 0;
                if ((stored = (Temp->eID[Temp->oNum] = func_00255A30(pCall, Temp))) > 0) {
                    Temp->oNum++;
                }
            }
            Temp->wLvl++;
        }
        return 1;
    case 1:
        if (Temp->oNum > 0) {
            for (i = 0; i < Temp->oNum; i++) {
                if (func_001F51D0(Temp->eID[i]) != 0) {
                    return 1;
                }
            }
        }
        func_001E4530();
        Temp->oNum = 0;
        Temp->wLvl++;
        return 1;
    case 2:
        Temp->wCamTime++;
        if ((Temp->wCount_1 = func_00250300(Temp->wCount_1, 15, -1)) > 0) {
            func_001F6CF0((unsigned char)Temp->wCount_1);
            func_001F6CE0((unsigned char)Temp->wCount_1);
        } else {
            func_001F6CF0((unsigned char)Temp->wCount_1);
            func_001F6CE0((unsigned char)Temp->wCount_1);
            if (Temp->wCamTime >= 8) {
                if ((unsigned short)eInfo->dwPar == 0xFFFF) {
                    temp = 0;
                } else {
                    temp = func_002670F0(44, (unsigned short)eInfo->dwPar);
                }
                if (temp == 0) {
                    if (((eInfo->dwPar >> 28) & 1) == 1) {
                        pCall->eNO = 604;
                        pCall->dwFrom = (unsigned short)eInfo->dwFrom;
                        pCall->dwTo = (unsigned short)eInfo->dwTo;
                        pCall->dwPar = (((eInfo->dwPar >> 20) & 1) << 19) | (temp | 0x20000) | (((eInfo->dwPar >> 22) & 1) << 20);
                    } else {
                        pCall->eNO = 604;
                        pCall->dwFrom = (unsigned short)eInfo->dwFrom;
                        pCall->dwTo = (unsigned short)eInfo->dwTo;
                        pCall->dwPar = (((eInfo->dwPar >> 20) & 1) << 19) | (temp | 0x30000) | (((eInfo->dwPar >> 22) & 1) << 20);
                    }
                } else {
                    if (((eInfo->dwPar >> 28) & 1) == 1) {
                        pCall->eNO = 604;
                        pCall->dwFrom = (unsigned short)eInfo->dwFrom;
                        pCall->dwTo = (unsigned short)eInfo->dwTo;
                        pCall->dwPar = (((eInfo->dwPar >> 20) & 1) << 19) | (temp | 0x10000) | (((eInfo->dwPar >> 22) & 1) << 20);
                    } else {
                        pCall->eNO = 604;
                        pCall->dwFrom = (unsigned short)eInfo->dwFrom;
                        pCall->dwTo = (unsigned short)eInfo->dwTo;
                        pCall->dwPar = (((eInfo->dwPar >> 20) & 1) << 19) | temp | (((eInfo->dwPar >> 22) & 1) << 20);
                    }
                }
                if ((stored = (Temp->eID[0] = func_00255A30(pCall, Temp))) >= 0) {
                    Temp->ePos[0] = 0;
                    Temp->oNum++;
                }
                pCall->eNO = 605;
                pCall->dwFrom = (unsigned short)eInfo->dwFrom;
                pCall->dwTo = (unsigned short)eInfo->dwTo;
                pCall->dwPar = (((eInfo->dwPar >> 19) & 1) << 1) | ((eInfo->dwPar >> 18) & 1);
                Temp->eID[Temp->oNum] = func_00255A30(pCall, Temp);
                Temp->ePos[Temp->oNum] = 0;
                func_001F4F10(Temp->eID[Temp->oNum], 1);
                Temp->wLvl++;
            }
        }
        return 1;
    case 3:
        if (func_001F51D0(Temp->eID[0]) != 0) {
            if (func_001F52D0(Temp->eID[0]) == 2) {
                switch (Temp->ePos[0]) {
                case 0:
                    Temp->ePos[0]++;
                    if (func_001DE2A0_b(func_001DE540()) != 0) {
                        if ((unsigned short)eInfo->dwPar != 0xFFFF) {
                            if (func_0027F830(func_001DE540()) == 0) {
                                func_001F4F10(Temp->eID[0], 1);
                                return 4;
                            }
                        }
                    }
                    break;
                case 1:
                case 2:
                    func_00255AC0_b(Temp, 500);
                    Temp->ePos[0]++;
                    func_00217710(1, 65);
                    break;
                }
            }
            return 1;
        }
        Temp->wCount_1 = 0;
        func_001F6CF0((unsigned char)Temp->wCount_1);
        func_001F6CE0((unsigned char)Temp->wCount_1);
        if (((eInfo->dwPar >> 16) & 1) == 1 && (temp = (unsigned short)eInfo->dwPar) != 0xFFFF) {
            func_001DF490(func_00250360((eInfo->dwTo & 0xFFFF) >> 8, eInfo->dwTo & 0xFF), 1, func_002670F0(44, temp));
        } else if (((eInfo->dwPar >> 17) & 1) == 1 && (temp = (unsigned short)eInfo->dwPar) != 0xFFFF) {
            func_001DF490(func_00250360((eInfo->dwFrom & 0xFFFF) >> 8, eInfo->dwFrom & 0xFF), 1, func_002670F0(44, temp));
        }
        func_001F4F10(Temp->eID[Temp->oNum++], 0);
        Temp->fObj2 = 0;
        Temp->wLvl++;
        return 1;
    case 4:
        if ((Temp->wCount_1 = func_00250300(Temp->wCount_1, 15, 1)) < 128) {
            func_001F6CF0((unsigned char)Temp->wCount_1);
            func_001F6CE0((unsigned char)Temp->wCount_1);
        }
        if (func_001F51D0(Temp->eID[Temp->oNum - 1]) != 0) {
            switch (Temp->fObj2++) {
            case 0:
                if (((eInfo->dwPar >> 19) & 1) != 0) {
                    Temp->ePos[Temp->oNum - 1]++;
                    func_00217710(1, 66);
                    func_00217710(1, 45);
                }
                if (((eInfo->dwPar >> 18) & 1) != 0) {
                    Temp->ePos[Temp->oNum - 1]++;
                    func_00217710(1, 66);
                    func_00217710(1, 45);
                }
                break;
            case 20:
                if (Temp->ePos[Temp->oNum - 1] == 0) {
                    if (((eInfo->dwPar >> 19) & 1) == 0) {
                        func_00217710(0, 2);
                    }
                    if (((eInfo->dwPar >> 18) & 1) == 0) {
                        func_00217710(0, 2);
                    }
                }
                break;
            case 40:
                if (Temp->ePos[Temp->oNum - 1] > 0) {
                    if (((eInfo->dwPar >> 19) & 1) == 0) {
                        func_00217710(0, 2);
                    }
                    if (((eInfo->dwPar >> 18) & 1) == 0) {
                        func_00217710(0, 2);
                    }
                }
                break;
            }
            return 1;
        }
        if ((eInfo->dwPar >> 25) != 0) {
            if (((eInfo->dwPar >> 26) & 1) == 1 && ((eInfo->dwPar >> 19) & 1) == 0) {
                func_002503B0_b((eInfo->dwFrom & 0xFFFF) >> 8, eInfo->dwFrom & 0xFF, 1);
                func_00260AF0_b(0, (unsigned short)eInfo->dwFrom, 180, 180);
                func_001E42C0(0, -120, 80, 264);
                pCall->eNO = 500;
                pCall->dwFrom = 0;
                pCall->dwTo = (unsigned short)eInfo->dwFrom;
                pCall->dwPar = 0;
                Temp->eID[0] = func_00255A30(pCall, Temp);
            } else if (((eInfo->dwPar >> 25) & 1) == 1 && ((eInfo->dwPar >> 18) & 1) == 0) {
                func_001E42C0(0, -120, 80, 264);
                func_002503B0_b((eInfo->dwTo & 0xFFFF) >> 8, eInfo->dwTo & 0xFF, 1);
                pCall->eNO = 500;
                pCall->dwFrom = 0;
                pCall->dwTo = (unsigned short)eInfo->dwTo;
                pCall->dwPar = 0;
                func_00260AF0_b(0, (unsigned short)eInfo->dwTo, 180, 180);
                Temp->eID[0] = func_00255A30(pCall, Temp);
            }
            Temp->wLvl = 5;
        }
        Temp->wLvl = 16;
        return 1;
    case 5:
        if ((Temp->wCount_1 = func_00250300(Temp->wCount_1, 15, 1)) < 128) {
            func_001F6CF0((unsigned char)Temp->wCount_1);
            func_001F6CE0((unsigned char)Temp->wCount_1);
        }
        

        if (func_001F51D0(Temp->eID[0]) == 0) {
            (void)Temp->wLvl;
        }
        break;
    default:
        if ((Temp->wCount_1 = func_00250300(Temp->wCount_1, 15, 1)) < 128) {
            func_001F6CF0((unsigned char)Temp->wCount_1);
            func_001F6CE0((unsigned char)Temp->wCount_1);
            return 1;
        }
        if (func_001F51D0(Temp->eID[0]) == 1) {
            return 1;
        }
        func_001E4530();
        func_00260A70_b(Temp, 0);
        if ((eInfo->dwFrom >> 16) != 0) {
            if ((eInfo->dwFrom >> 31) == 0) {
                func_00250CA0((eInfo->dwFrom & 0xFFFF) >> 8, eInfo->dwFrom & 0xFF, 1, (eInfo->dwFrom >> 16) & 0x7FFF);
                func_00250E80((eInfo->dwFrom & 0xFFFF) >> 8, eInfo->dwFrom & 0xFF, 1, (eInfo->dwFrom >> 16) & 0x7FFF);
            } else {
                func_00250CA0((eInfo->dwFrom & 0xFFFF) >> 8, eInfo->dwFrom & 0xFF, 0, (eInfo->dwFrom >> 16) & 0x7FFF);
                func_00250E80((eInfo->dwFrom & 0xFFFF) >> 8, eInfo->dwFrom & 0xFF, 0, (eInfo->dwFrom >> 16) & 0x7FFF);
            }
        }
        if ((eInfo->dwTo >> 16) != 0) {
            if ((eInfo->dwTo >> 31) == 0) {
                func_00250CA0((eInfo->dwTo & 0xFFFF) >> 8, eInfo->dwTo & 0xFF, 1, (eInfo->dwTo >> 16) & 0x7FFF);
                func_00250E80((eInfo->dwTo & 0xFFFF) >> 8, eInfo->dwTo & 0xFF, 1, (eInfo->dwTo >> 16) & 0x7FFF);
            } else {
                func_00250CA0((eInfo->dwTo & 0xFFFF) >> 8, eInfo->dwTo & 0xFF, 0, (eInfo->dwTo >> 16) & 0x7FFF);
                func_00250E80((eInfo->dwTo & 0xFFFF) >> 8, eInfo->dwTo & 0xFF, 0, (eInfo->dwTo >> 16) & 0x7FFF);
            }
        }
        if (func_001DE780() != 0) {
            func_001DE7E0(1);
        }
        func_001E4530();
        return 0;
    }
    return 1;
}

typedef struct {
    u32 unknown;
    u16 first;
    u16 padding6;
    u16 second;
    u16 paddingA;
    u32 flags;
} Source_002755D0;

typedef struct {
    u16 first;
    u16 second;
    u8 padding[0xFE];
    u16 counter;
} State_002755D0;

typedef struct {
    s32 id;
    s32 x;
    s32 y;
    s32 z;
} Params_002755D0;

void func_0024F370(s32, s32);

static inline s32 update_002755D0(void *arg0, void *arg1, void *params_arg, s32 arg2) {
    State_002755D0 *state = arg1;
    Source_002755D0 *source = arg0;
    Params_002755D0 *values = params_arg;
    s32 card;
    s32 position;
    u16 counter;

    if (source == NULL || state == NULL || values == NULL) {
        func_001E4530();
        return 0;
    }
    if (arg2 >= 0) {
        func_00255960(state);
        if ((source->flags & 1) == 1) {
            state->first = source->second;
            state->second = source->first;
        } else {
            state->first = source->first;
            state->second = source->second;
        }
        if ((source->flags >> 1) != 0) {
            card = func_0024DE70((s32) state->second >> 8, state->second & 0xFF);
            position = func_001E1090(card, 0);
            func_00260490(position & 0xFF, position >> 8, 0,
                         func_00271740(9, card), 1, 1, 11);
        }
        func_002500C0((s32) state->first >> 8, state->first & 0xFF, -1, 1, 3);
        return 1;
    }
    counter = state->counter;
    state->counter = counter + 1;
    if ((s32) counter < 16) {
        return 1;
    }
    func_0024F370((s32) state->first >> 8, state->first & 0xFF);
    func_001E4530();
    return 0;
}

static inline void init_params_002755D0(void *params_arg) {
    Params_002755D0 *values = params_arg;

    values->id = 999;
    values->x = 0;
    values->y = 0;
    values->z = 0;
}

s32 func_002755D0(void *arg0, void *arg1, s32 arg2) {
    Params_002755D0 values;
    Params_002755D0 *params = &values;

    init_params_002755D0(params);
    return update_002755D0(arg0, arg1, params, arg2);
}

typedef struct State_00275740 {
    u8 pad0[4];
    u16 phase;
    u8 handle;
    u8 pad7[0xFB];
    u16 timer;
} State_00275740;

typedef struct Request_00275740 {
    s32 command;
    s32 value;
    u32 cell;
    s32 flag;
} Request_00275740;

void func_0024F370(s32, s32);

s32 func_00275740(u32 *arg0, void *arg1, s32 arg2) {
    extern s32 func_001E1E10();
    extern s32 func_001E1030();
    Request_00275740 data;
    Request_00275740 *request = &data;
    State_00275740 *state = arg1;
    u32 cell;

    data.command = 999;
    data.value = 0;
    data.cell = 0;
    data.flag = 0;
    func_001DE7E0(0);
    if (arg2 >= 0) {
        func_00255960(arg1);
        func_00255AC0(arg1, 0x259);
        func_00255AC0(arg1, 0x25A);
        cell = arg0[1];
        func_002516D0(cell >> 8, cell & 0xFF, 1);
        func_00260AF0(0, arg0[1], 100, 180);
        return 1;
    }

    switch (state->phase) {
    case 0:
        if (func_00255B50(arg1) == 1) {
            cell = arg0[1];
            if (func_001E1E10(cell >> 8, cell & 0xFF) == 0xFF) {
                func_001E42C0(0, -120, 80, 0x103);
                request->command = 0x25A;
                request->value = 0;
                request->cell = arg0[1];
                request->flag = 0;
                state->handle = func_00255A30((s32 *)request, arg1);
                state->phase++;
            }
        }
        break;
    case 1:
        if (func_001F51D0(state->handle) == 1) {
            return 1;
        }
        cell = arg0[1];
        func_001E1E70(cell >> 8, cell & 0xFF, 0, 1);
        cell = arg0[1];
        func_001E42C0(0, -120, 80, func_001DE210(func_001E1030(cell >> 8, cell & 0xFF)));
        request->command = 0x259;
        request->value = 0;
        request->cell = arg0[1];
        request->flag = 1;
        state->handle = func_00255A30((s32 *)request, arg1);
        state->phase++;
        break;
    case 2:
        if (func_001F51D0(state->handle) == 1) {
            return 1;
        }
        cell = arg0[1];
        func_0024F370(cell >> 8, cell & 0xFF);
        state->phase++;
        func_001E4530();
        func_00260A70(arg1, 16);
        break;
    default:
        if (state->timer++ > 16) {
            if (func_001DE780() != 0) {
                func_001DE7E0(1);
            }
            func_001E4530();
            return 0;
        }
        break;
    }
    return 1;
}

typedef struct {
    u32 unused;
    u32 source;
    u32 destination;
    s32 flag;
} Data_002759D0;

typedef struct {
    u8 unused[4];
    u16 phase;
    u8 id;
    u8 padding[0xFB];
    u16 timer;
} State_002759D0;

typedef struct {
    s32 code;
    s32 unused;
    s32 position;
    s32 flags;
} Command_002759D0;


s32 func_002759D0(void *arg0, void *arg1, s32 arg2) {
    Command_002759D0 storage;
    Command_002759D0 *command = &storage;
    Data_002759D0 *data = arg0;
    State_002759D0 *state = arg1;
    u32 position;
    u16 timer;
    extern s32 func_001DDAC0();
    extern s32 func_001E1E10();
    extern s32 func_001E1030();

    command->code = 0x3E7;
    command->unused = 0;
    command->position = 0;
    command->flags = 0;
    func_001DE7E0(0);
    if (arg2 >= 0) {
        func_00255960(arg1);
        position = data->source;
        func_002516D0(position >> 8, position & 0xFF, 1);
        func_00260AF0(0, data->source, 0x64, 0xB4);
        func_00255AC0(arg1, 0x25A);
        if (data->flag != 0) {
            func_00255AC0(arg1, 0x1F4);
        } else {
            func_00255AC0(arg1, 0x201);
        }
        return 1;
    }
    switch (state->phase) {
    case 0:
        position = data->source;
        if (func_001E1E10(position >> 8, position & 0xFF) == 0xFF) {
            if (func_00255B50(arg1) == 1) {
                func_001E42C0(0, -0x78, 0x50, 0x103);
                command->code = 0x25A;
                command->unused = 0;
                command->position = data->source;
                command->flags = 0;
                state->id = func_00255A30((s32 *)command, arg1);
                state->phase++;
            }
        }
        break;
    case 1:
        if (func_001F51D0(state->id) == 1) {
            return 1;
        }
        position = data->source;
        func_001E1E70(position >> 8, position & 0xFF, 0, 1);
        func_00260AF0(0, data->destination, 0x64, 0xB4);
        if (data->flag != 0) {
            command->code = 0x1F4;
            command->unused = 0;
            command->position = data->destination;
            command->flags = 0;
        } else {
            command->code = 0x201;
            command->unused = 0;
            command->position = data->destination;
            command->flags = 0;
        }
        position = data->source;
        func_001E42C0(0, -0x78, 0x50,
            func_001DE210(func_001E1030(position >> 8, position & 0xFF)));
        state->id = func_00255A30((s32 *)command, arg1);
        state->phase++;
        return 1;
    case 2:
        if (func_001F51D0(state->id) == 1) {
            return 1;
        }
        if (data->flag != 0) {
            position = data->destination;
            func_002503B0(position >> 8, position & 0xFF, 0xFF);
        } else {
            position = data->destination;
            func_001E1E70(position >> 8, position & 0xFF, 3, 0);
            position = data->destination;
            func_001E1E70(position >> 8, position & 0xFF, 5, 0);
        }
        state->phase++;
        func_001E4530();
        func_00260A70(arg1, 0x10);
        break;
    default:
        timer = state->timer;
        state->timer = timer + 1;
        if (timer > 0x10) {
            if (func_001DE780() != 0) {
                func_001DE7E0(1);
            }
            func_001E4530();
            return 0;
        }
        break;
    }
    return 1;
}

typedef struct Entry_00275D00 {
    u16 id;
    u16 value;
    u16 other;
    u16 pad6;
    s32 index;
    u8 flags : 2;
    u8 rest : 6;
    u8 padD[3];
} Entry_00275D00;

typedef struct Data_00275D00 {
    Entry_00275D00 entries[22];
    u16 list[32];
    u8 idx : 5;
    u8 pad1A0 : 3;
    u8 sel : 4;
    u8 pad1A1 : 4;
    u16 count;
} Data_00275D00;

s32 func_00275D00(s32 arg0, void *arg1) {
    Data_00275D00 *data = arg1;
    s32 i;

    if (func_0027F830(arg0) == 1) {
        func_0027F3E0(func_001DE4E0(arg0) & 0xFF, (s32) arg1);
        return 1;
    }
    if (data != NULL) {
        for (i = 0; i < 22; i++) {
            data->entries[i].id = 0xFFFF;
            data->entries[i].value = 0xFF;
            data->entries[i].index = -1;
            data->entries[i].other = 0xFFFF;
            data->entries[i].flags = 0;
        }
        for (i = 0; i < 32; i++) {
            data->list[i] = 0xFFFF;
        }
        data->idx = 0;
        data->sel = 0;
        data->count = 0;
        data->entries[0].id = arg0 << 8;
        data->entries[0].value = func_001E13C0(arg0, 0);
        return 1;
    }
    return -1;
}

s32 func_00275E30(void *arg0) {
    if (func_0027F830(func_001DE540()) == 1) {
        return 1;
    }
    *(s16 *)((u8 *)arg0 + 0x1A2) = 0;
    return func_00275E80(arg0);
}

typedef struct Entry_00275E80 {
    u16 id;
    u16 value;
    u16 other;
    u16 pad6;
    s32 index;
    u8 flags : 2;
    u8 rest : 6;
    u8 padD[3];
} Entry_00275E80;

typedef struct Data_00275E80 {
    Entry_00275E80 entries[22];
    u16 list[32];
    u8 idx : 5;
    u8 pad1A0 : 3;
} Data_00275E80;

s32 func_00275E80(void *arg0) {
    Data_00275E80 *data = arg0;
    s32 owner;
    s32 i;

    owner = func_001DE540();
    if (func_0027F830(owner) == 1) {
        return 1;
    }
    if (data != NULL) {
        data->idx = 0;
        for (i = 0; i < 32; i++) {
            data->list[i] = 0xFFFF;
        }
        for (i = 0; i < 22; i++) {
            if (data->entries[i].id < 0xFFFF) {
                if (func_001DF540(data->entries[i].id >> 8, data->entries[i].id & 0xFF) == 0 ||
                    owner != func_0024DE70(data->entries[i].id >> 8, data->entries[i].id & 0xFF)) {
                    data->entries[i].id = 0xFFFF;
                    data->entries[i].value = 0xFF;
                    data->entries[i].index = -1;
                    data->entries[i].other = 0xFFFF;
                    data->entries[i].flags = 0;
                } else if (func_001E13C0(data->entries[i].id >> 8,
                                         (data->entries[i].id & 0xFF) != data->entries[i].value) != 0) {
                    data->entries[i].value = func_001E13C0(data->entries[i].id >> 8, data->entries[i].id & 0xFF);
                    data->entries[i].index = -1;
                    data->entries[i].other = 0xFFFF;
                    data->entries[i].flags = 0;
                }
            }
        }
        for (i = 0; i < 11; i++) {
            if (owner == func_0024DE70(0, i)) {
                if (func_002760E0(i, (u16 *)data) == 0 && func_001DF540(0, i) != 0) {
                    func_00276120(i, data);
                }
            }
            if (owner == func_0024DE70(1, i)) {
                if (func_002760E0(i | 0x100, (u16 *)data) == 0 && func_001DF540(1, i) != 0) {
                    func_00276120(i | 0x100, data);
                }
            }
        }
        func_002761D0(data);
        return 1;
    }
    return -1;
}

s32 func_002760E0(u16 value, u16 *entries) {
    s32 i = 0;

    do {
        if (value == *entries) {
            return 1;
        }
        i++;
        entries += 8;
    } while (i < 22);

    return 0;
}
