#include "common.h"

typedef struct Vec3_0023B1F0 {
    f32 x;
    f32 y;
    f32 z;
} Vec3_0023B1F0;

typedef struct Vec4_0023B1F0 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4_0023B1F0;

typedef struct Item_0023B1F0 {
    Vec3_0023B1F0 pos;
    u8 pad0C[0x28];
} Item_0023B1F0;

void TkCamp_Act2(s32 arg0) {
    extern u8 D_00299F60[];
    extern Item_0023B1F0 D_00298BA0[];
    extern s32 D_0034F6F0;
    extern void Taku_3D_2D_Set();
    Vec4_0023B1F0 top;
    u8 *work;
    s16 show;
    s8 *state;
    s16 result;
    s16 i;
    s32 sx;
    s16 *rect;
    s32 dx;
    s16 j;
    Item_0023B1F0 *item;
    Vec4_0023B1F0 side;
    s32 *spot;
    s32 sy;
    s32 radius;

    state = &D_00299E10;
    work = (u8 *)0x01ED0000;
    result = 0;
    Taku_Coord_Set(D_00299F60);
    item = D_00298BA0;
    for (i = 0, spot = (s32 *)work; i <= 21; i++) {
        show = 0;
        top.x = item->pos.x;
        top.y = 8.65f + item->pos.y;
        top.z = item->pos.z;
        side.x = 5.0f + item->pos.x;
        side.y = 8.65f + item->pos.y;
        side.z = item->pos.z;
        if (arg0 != 0) {
            show = 1;
        }
        if (*(s8 *)(work + 0x18C) != 0) {
            show = 1;
        } else if (state[0] == 0) {
            if (i == 0 || i == 11) {
                show = 1;
            } else if (i > 0 && i < 11 && state[i + 3] != 0) {
                show = 1;
            }
        } else {
            if (i == 0 || i == 11) {
                show = 1;
            } else if (i >= 12 && i < 22 && state[i + 3] != 0) {
                show = 1;
            }
        }
        if (show) {
            Taku_3D_2D_Set(&spot[0x23], &spot[0x43], &top);
            Taku_3D_2D_Set(&sx, &sy, &side);
            radius = sx - spot[0x23];
            if (D_0034F6F0 == 0) {
                if (*(s8 *)(work + 0x5373) != 0) {
                    *(s16 *)(work + 0x0) = *(s16 *)(work + 0x8C + state[0xC6] * 4);
                    *(s16 *)(work + 0x2) = *(s16 *)(work + 0x10C + state[0xC6] * 4);
                }
                dx = *(s16 *)(work + 0x0) - spot[0x23];
                if (func_001A6C60(func_001A6C48(dx, 2.0f) + func_001A6C48(*(s16 *)(work + 0x2) - spot[0x43], 2.0f)) < radius) {
                    if (*(s16 *)(work + 0x6C) == 0 || *(s8 *)(work + 0x5373) != 0) {
                        if (i != state[0xC6]) {
                            state[0xC6] = i;
                        }
                    }
                    if (state[0xC6] == i) {
                        result = 1;
                    }
                    if (*(s8 *)(work + 0x5373) != 0) {
                        *(s16 *)(work + 0x0) = *(s16 *)(work + 0x8C + state[0xC6] * 4);
                        *(s16 *)(work + 0x2) = *(s16 *)(work + 0x10C + state[0xC6] * 4);
                    }
                }
            } else {
                result = 1;
            }
        }
        item++;
        spot++;
    }
    rect = D_00298260;
    for (j = 0; j < 4; j++) {
        if (rect[0] - 2 <= *(s16 *)(work + 0x0) && *(s16 *)(work + 0x0) <= rect[2] + 2 &&
            rect[1] - 2 <= *(s16 *)(work + 0x2) && *(s16 *)(work + 0x2) <= rect[3] + 2) {
            *(s16 *)(work + 0x80) = j;
            *(s8 *)(work + 0x547A) = 1;
            result = 2;
        }
        rect = (s16 *)((u8 *)rect + 0x26);
    }
    if (*(u16 *)0x01ED0004 != 1) {
        switch (result) {
        case 0:
            *(s8 *)0x01ED006A = 0;
            *(s8 *)0x01ED007E = 0;
            *(u16 *)0x01ED0004 = 0;
            break;
        case 1:
            if (state[0xC6] == 11) {
                switch (state[state[0xC6] + 3]) {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                    if (*(s8 *)0x01ED0072 == 0 || *(s8 *)0x01ED537A != 0) {
                        *(s8 *)0x01ED006A = 1;
                        *(s8 *)0x01ED007E = 0;
                        *(u16 *)0x01ED0004 = 0;
                        *(u16 *)0x01ED0004 = 2;
                    }
                    break;
                }
            } else {
                switch (state[state[0xC6] + 3]) {
                case 1:
                case 2:
                case 3:
                    if (*(s8 *)0x01ED0072 == 0 || *(s8 *)0x01ED537A != 0) {
                        *(s8 *)0x01ED006A = 1;
                        *(s8 *)0x01ED007E = 0;
                        *(u16 *)0x01ED0004 = 2;
                    }
                    break;
                }
            }
            break;
        case 2:
            *(s8 *)0x01ED007E = 1;
            *(s8 *)0x01ED006A = 0;
            *(u16 *)0x01ED0004 = 2;
            *(s8 *)0x01ED547A = 1;
            break;
        }
    } else {
        *(s8 *)0x01ED006A = 0;
        *(s8 *)0x01ED007E = 0;
    }
    if (*(s16 *)0x01ED0002 < 0x78) {
        *(s16 *)0x01ED0224 -= 8;
        if (*(s16 *)0x01ED0224 <= 0x60) {
            *(s16 *)0x01ED0224 = 0x60;
        }
    } else {
        *(s16 *)0x01ED0224 += 8;
        if (*(s16 *)0x01ED0224 >= 0x80) {
            *(s16 *)0x01ED0224 = 0x80;
        }
    }
    if (*(s16 *)0x01ED0002 >= 0x154) {
        *(s16 *)0x01ED0226 -= 8;
        if (*(s16 *)0x01ED0226 <= 0x60) {
            *(s16 *)0x01ED0226 = 0x60;
        }
    } else {
        *(s16 *)0x01ED0226 += 8;
        if (*(s16 *)0x01ED0226 >= 0x80) {
            *(s16 *)0x01ED0226 = 0x80;
        }
    }
    if (*(s16 *)0x01ED0000 >= 0x1C8) {
        *(s16 *)0x01ED0228 -= 8;
        if (*(s16 *)0x01ED0228 <= 0x60) {
            *(s16 *)0x01ED0228 = 0x60;
        }
    } else {
        *(s16 *)0x01ED0228 += 8;
        if (*(s16 *)0x01ED0228 >= 0x80) {
            *(s16 *)0x01ED0228 = 0x80;
        }
    }
}

typedef struct Copy_0023B920 {
    s32 words[0x3FE8];
} Copy_0023B920;

extern s8 D_0034F6F8;

void TkCamp_Term(void) {
    s32 a;
    s32 b;
    s32 c;
    s32 i;
    s32 x;
    s32 y;

    if (D_0034F6F8 != 0) {
        *(Copy_0023B920 *)0x01E301E0 = *(Copy_0023B920 *)SzData_GetData(0);
        a = SzData_GetOption(0, 0);
        b = SzData_GetOption(0, 1);
        c = SzData_GetOption(0, 2);
        switch (*(s8 *)0x01ED546B) {
        case 0:
            i = 0x20;
            x = 0x11;
            y = 0x12;
            break;
        case 1:
            i = 0x21;
            x = 0x13;
            y = 0x14;
            break;
        case 2:
            i = 0x22;
            x = 0x15;
            y = 0x16;
            break;
        case 3:
            i = 0x23;
            x = 0x17;
            y = 0x18;
            break;
        default:
            i = 0x24;
            x = 0x19;
            y = 0x1A;
            break;
        }
        SzGame_SetMenuNum(1, 0);
        SzGame_SetMenuNum(2, 0);
        SzGame_SetMenuNum(3, i);
        SzGame_SetMenuNum(4, i);
        SzData_SetupFromConstDeck(0, x);
        SzData_SetupFromConstDeck(1, y);
        for (i = 0; i < 2; i++) {
            SzData_SetOption(i, 0, a);
            SzData_SetOption(i, 1, b);
            SzData_SetOption(i, 2, c);
        }
    }
    SzDuel_CloseMsgPopup();
}

void Taku_Camp_Go_Rensyu_Duel(s32 arg0) {
    s32 var_s0;
    s32 var_s1;
    s32 var_s2;

    switch (D_0034F700) {
    case 0:
        var_s0 = 0x20;
        var_s1 = 0x11;
        var_s2 = 0x12;
        break;
    case 1:
        var_s0 = 0x21;
        var_s1 = 0x13;
        var_s2 = 0x14;
        break;
    case 2:
        var_s0 = 0x22;
        var_s1 = 0x15;
        var_s2 = 0x16;
        break;
    case 3:
        var_s0 = 0x23;
        var_s1 = 0x17;
        var_s2 = 0x18;
        break;
    case 4:
        var_s0 = 0x24;
        var_s1 = 0x19;
        var_s2 = 0x1A;
        break;
    }
    SzGame_SetMenuNum(1, 0);
    SzGame_SetMenuNum(2, 0);
    SzGame_SetMenuNum(3, var_s0);
    SzGame_SetMenuNum(4, var_s0);
    SzData_SetupFromConstDeck(0, var_s1);
    SzData_SetupFromConstDeck(1, var_s2);
    if (D_0034F700 < 3) {
        D_0034F700 += 1;
        if (D_0034F700 > 2) {
            D_0034F700 = 0;
            D_0034F708 = 1;
        }
    }
    if (arg0 != 0) {
        SzGame_Goto(1, 0);
    } else {
        SzGame_Push(1, 0);
    }
}

typedef struct Copy_0023BC80 {
    s32 words[0x3FE8];
} Copy_0023BC80;

extern s8 D_0034F6F8;

void Taku_Camp_Go_Help(void) {
    D_0034F6F8 = 1;
    *(Copy_0023BC80 *)0x01E301E0 = *(Copy_0023BC80 *)SzData_GetData(0);
    SzGame_Push(1, 0);
}

typedef int DotrHelpWord;
struct DotrHelpWindow {
    short x, y, w, h;
    char unknown_08[2];
};
struct DotrHelpWindows {
    struct DotrHelpWindow w[4];
};
extern struct DotrHelpWindows D_0029B020;
extern signed char D_00299E10_b[];
#define DOTR_HELP_BLOCK ((signed char *)0x1ed0000)
#define DOTR_HELP_OPEN (*(signed char *)0x1ed543c)
#define DOTR_HELP_STEP (*(signed char *)0x1ed543d)
#define DOTR_HELP_PICK (*(signed char *)0x1ed546b)
extern DotrHelpWord Taku_Window_Set_window(DotrHelpWord cursor, struct DotrHelpWindow *window,
                                    unsigned short flag, int a3, unsigned short x,
                                    unsigned short y, int a6, int a7, int a8);
extern DotrHelpWord func_001B6F70_b(DotrHelpWord cursor, int x, int y, int a,
                                                int flags, int n, const char *text, int c);
extern DotrHelpWord func_0021C450_b(DotrHelpWord cursor, int index, int no, int x, int y,
                                     int unused, unsigned char *col, float sx, float sy);

int Taku_Camp_Help_Window(int cursor)
{
    signed char *st;
    short y;
    short i;
    int ix;
    short yy;
    struct DotrHelpWindows win;
    unsigned char col[4];
    short xx;
    int no;
    int px;
    signed char *blk;

    st = D_00299E10_b;
    win = D_0029B020;
    col[0] = col[1] = col[2] = 128;
    col[3] = 128;
    y = 512 - ((DOTR_HELP_STEP << 9) >> 3);
    blk = DOTR_HELP_BLOCK;
    if (DOTR_HELP_OPEN != 0) {
        cursor = Taku_Window_Set_window(cursor, &win.w[0], 2, 0, 128, y + 80, 0, 128, 101);
        cursor = Taku_Window_Set_window(cursor, &win.w[1], 2, 0, 128, y + 80, 0, 128, 101);
        cursor = Taku_Window_Set_window(cursor, &win.w[3], st[0] + 10, 0, 282, y + 94, 0, 128, 128);
        cursor = func_001B6F70_b(cursor, 296, y + 102, 2, 1, 4, D_0030F113, 0);
        


        px = 160;
        xx = px;
        ix = xx;
        yy = 144;
        cursor = Taku_Window_Set_window(cursor, &win.w[2], 2, 0, px, y + ((short)(DOTR_HELP_PICK * 36) + yy), 0, 128, 0);
        yy += 2;
        for (i = 0; i < 5; i++) {
            if (i == blk[0x546b]) {
                col[0] = col[1] = col[2] = 255;
                col[3] = 128;
            } else {
                col[0] = col[1] = col[2] = 64;
                col[3] = 128;
            }
            switch (i) {
            case 0:
                no = 3049;
                break;
            case 1:
                no = 3050;
                break;
            case 2:
                no = 3051;
                break;
            case 3:
                no = 3052;
                break;
            default:
                no = 3053;
                break;
            }
            cursor = func_0021C450_b(cursor, 1, no, ix + 16, (short)(yy + y), 0, col, 1.0f, 1.0f);
            yy += 36;
        }
    }
    return cursor;
}
#undef DOTR_HELP_BLOCK
#undef DOTR_HELP_OPEN
#undef DOTR_HELP_STEP
#undef DOTR_HELP_PICK

typedef struct Flags_0023BFF0 {
    s8 unused : 4;
    s8 horizontal : 1;
    s8 enabled : 1;
    s8 colored : 1;
    s8 reserved : 1;
} Flags_0023BFF0;

typedef struct Draw_0023BFF0 {
    u8 pad00[0x10];
    s32 field10;
    s32 field14;
    s32 field18;
    s32 field1C;
    u8 vector20[0x10];
    s32 field30;
    s32 field34;
    u8 pad38[0x49];
    Flags_0023BFF0 flags;
    u8 pad82[0xE];
} Draw_0023BFF0;

typedef struct Texture_0023BFF0 {
    u8 pad00[0x44];
    u8 field44;
    u8 pad45[0x1B];
} Texture_0023BFF0;

void *Taku_Camp_Card_Get(void *arg0, f32 fparg0, s32 arg1, f32 fparg1, s32 arg2) {
    extern void SzDuel_ClearDrawCard();
    Texture_0023BFF0 texture;
    Draw_0023BFF0 draw;

    SzDuel_ClearDrawCard(&draw);
    draw.flags.enabled = 1;
    draw.flags.colored = 1;
    draw.flags.reserved = 0;
    draw.flags.horizontal = 1;
    draw.field30 = 0x3F000000;
    draw.field34 = 0x3F000000;
    SzDuel_InitCardInfo(&texture, 999);
    texture.field44 = arg1;
    Ex3d_GetLookVector((s32)draw.vector20);
    draw.field10 = 0;
    draw.field14 = arg2;
    draw.field18 = 0;
    draw.field1C = 0;
    arg0 = (void *)SzDuel_StartCardSession_Pipe((s32)arg0);
    SzDuel_SetCardDefPrioZ(0xFFFFFF);
    Ex3d_GetPointOnScreen(&draw, fparg0, fparg1);
    return (void *)SzDuel_FinishCardSessionX_Pipe(SzDuel_DrawCard_Pipe(
        SzDuel_SetupCard2_Pipe((s32)arg0, (s32)(SzDuel_GetCardNode(&draw, 1) ? &texture : NULL), &draw),
        (s32)&draw));
}

s32 Taku_Get_Duel5_flg(void) {
    return D_00299EDA;
}

void Taku_Set_Duel5_flg(void) {
    D_00299EDA = 0;
}

s32 Taku_Get_WinCount(void) {
    return (s32) D_00299E4E;
}

typedef struct State_0023C170 {
    u8 pad00[0x8];
    s32 field08;
    s32 field0C;
    s32 field10;
    s32 field14;
    s32 field18;
    s32 field1C;
    s32 field20;
    s32 field24;
    u8 pad28[4];
    s16 field2C;
    s16 field2E;
    s16 field30;
    u8 pad32[2];
    s16 field34;
    s16 field36;
    s16 field38;
    s16 field3A;
    s16 field3C;
    s16 field3E;
    s16 field40;
    s16 field42;
    u8 pad44[4];
    s32 field48;
    s32 field4C;
    s16 field50;
    s16 field52;
    s16 field54;
    s16 field56;
    u8 pad58[4];
    s32 field5C;
    s32 field60;
    s32 field64;
    s32 field68;
    u8 pad6C[0x214];
    s16 field280;
    u8 pad282[2];
    s32 field284;
    s32 field288;
    s32 field28C;
    s32 field290;
    s16 field294;
    s16 field296;
    u8 pad298[0x10];
    s16 field2A8;
    s16 field2AA;
    s16 field2AC;
    s16 field2AE;
    s16 field2B0;
    s16 field2B2;
    s16 field2B4;
    s16 field2B6;
    s16 field2B8;
    u8 pad2BA[4];
    s16 field2BE;
    u8 pad2C0[0x580];
} State_0023C170;


s32 TakuCard_inti(s32 arg0) {
    extern void *D_0034FAE8;
    extern void *D_0034FAEC;
    extern s8 D_0034FAF0;
    extern State_0023C170 D_0034FB00;
    extern s32 func_00194248(s32, s32 *, s32 *);
    extern s32 func_00194380(s32, s32, s32 *, s32 *, s32 *);
    s32 found[2];
    State_0023C170 *state = &D_0034FB00;
    s16 i;
    s32 *out;

    D_0034FAE8 = SzData_GetData(0);
    D_0034FAEC = SzData_GetData(1);
    D_0034FAF0 = 1;
    func_00195108((s32)&D_0034FB00, 0x840);
    D_0034FB00.field30 = 0;
    D_0034FB00.field34 = 0;
    D_0034FB00.field36 = 0;
    D_0034FB00.field38 = 0;
    D_0034FB00.field3A = 0;
    D_0034FB00.field3C = 0;
    D_0034FB00.field3E = 0;
    D_0034FB00.field40 = 0;
    D_0034FB00.field42 = 0;
    D_0034FB00.field54 = 0;
    D_0034FB00.field56 = 0;
    D_0034FB00.field48 = 0;
    D_0034FB00.field4C = 0;
    D_0034FB00.field50 = 0;
    D_0034FB00.field52 = 0;
    D_0034FB00.field08 = 0;
    D_0034FB00.field0C = 0;
    D_0034FB00.field10 = 0;
    D_0034FB00.field14 = 0;
    D_0034FB00.field18 = 0;
    D_0034FB00.field1C = 0;
    D_0034FB00.field20 = 0;
    D_0034FB00.field24 = 0;
    D_0034FB00.field2C = 0;
    D_0034FB00.field2E = 0;
    D_0034FB00.field5C = 0;
    D_0034FB00.field60 = 0;
    D_0034FB00.field68 = 6;
    D_0034FB00.field64 = 0;
    D_0034FB00.field284 = 0;
    D_0034FB00.field288 = 0;
    D_0034FB00.field28C = 0;
    D_0034FB00.field290 = 0;
    D_0034FB00.field294 = 0;
    D_0034FB00.field296 = 0;
    D_0034FB00.field2B4 = 0;
    D_0034FB00.field280 = 0;
    D_0034FB00.field2A8 = 0;
    D_0034FB00.field2AA = 0;
    D_0034FB00.field2AC = 0;
    D_0034FB00.field2AE = 0;
    D_0034FB00.field2B0 = 0;
    D_0034FB00.field2B2 = 0;
    D_0034FB00.field2B6 = 0;
    D_0034FB00.field2B8 = 0;

    out = found;
    for (i = 0; i < 2; i++) {
        func_00194380(i, state->field0C, &state->field10, &state->field14, &state->field18);
        func_00194248(0, &state->field20, out);
        out++;
    }

    if (arg0 == 1 && (found[0] != 0 || found[1] != 0)) {
        return 1;
    }
    return 0;
}

typedef struct State_0023C3F0 {
    u8 pad0[0x30];
    s16 mode;
    u8 pad32[2];
    s16 field34;
    u8 pad36[0xA];
    s16 field40;
    u8 pad42[0x27C];
    s16 result;
} State_0023C3F0;

typedef struct State_0023E610 {
    s32 result;
    u8 pad04[0x1C];
    s32 command;
    s32 status;
    u8 pad28[8];
    s16 field30;
    u8 pad32[2];
    s16 field34;
    u8 pad36[0xA];
    s16 field40;
} State_0023E610;

extern struct State_0023E610 D_0034FB00;

s32 TkMc_Check_Main(s32 arg0) {
    State_0023C3F0 *state = (State_0023C3F0 *)&D_0034FB00;
    s32 var_s1;

    var_s1 = 0;
    if (arg0 == 1) {
        TakuCard_inti(0);
        state->result = 0;
    }
    switch (state->mode) {
    case 0:
    case 14:
    case 11:
        var_s1 = TakuSave_card_kansi(1);
        break;
    case 1:
        var_s1 = TakuSave_card_filename_check(1);
        break;
    case 3:
        var_s1 = TakuSave_card_kansi(1);
        break;
    }
    if (arg0 == 1) {
        state->field34 = 0;
        state->field40 = 0;
        state->mode = 0;
    }
    switch (var_s1) {
    case 2:
    case 3:
    case 14:
    case 6:
    case 8:
    case 10:
        var_s1 = 0x100;
        break;
    case 0:
        break;
    }
    if (var_s1 != 0) {
        state->result = var_s1;
    }
    if (var_s1 == 0x100) {
        return 0x100;
    }
    return state->result;
}

s16 TkMc_Save_Main(s32 arg0) {
    State_0023C170 *state = (State_0023C170 *)&D_0034FB00;
    s32 result;

    result = 0;
    if (arg0 == 1) {
        TakuCard_inti(0);
        state->field2BE = 0;
    }
    switch (state->field30) {
    case 0:
        result = TakuSave_card_kansi(0);
        if (result == 2) {
            state->field30 = 0;
        }
        break;
    case 1:
        result = TakuSave_card_filename_check(0);
        break;
    case 2:
        result = TakuSave_card_file_open();
        break;
    case 3:
        result = TakuSave_card_kansi(0);
        break;
    case 4:
        result = TakuSave_make_file();
        break;
    case 5:
        result = TakuSave_card_file_kakikomi();
        break;
    case 10:
        result = TakuSave_card_format();
        break;
    case 15:
        result = TakuSave_card_unformat();
        break;
    case 11:
        result = TakuSave_card_kansi(0);
        if (state->field2BE == 0xE && arg0 == 2) {
            state->field30 = 0xA;
            state->field34 = 0;
            result = 0xB;
            state->field40 = 0;
        }
        break;
    case 13:
        result = TakuSave_card_kansi(0);
        if (state->field2BE == 1 && arg0 == 2) {
            state->field30 = 5;
            state->field34 = 0;
            result = 9;
            state->field40 = 0;
        }
        break;
    case 14:
        result = TakuSave_card_kansi(0);
        if (result == 2) {
            result = 0xA;
        }
        if (arg0 == 2) {
            state->field30 = 0;
            state->field34 = 0;
            result = 0x700;
            state->field40 = 0;
        }
        break;
    }
    if (arg0 == 1) {
        state->field34 = 0;
        state->field40 = 0;
        state->field30 = 0;
    }
    if (result != 0) {
        state->field2BE = result;
    }
    if (result == 0x100) {
        return 0x100;
    }
    return state->field2BE;
}

typedef struct State_0023C770 {
    u8 pad_00[0x30];
    s16 state;
    u8 pad_32[2];
    s16 field_34;
    u8 pad_36[0xA];
    s16 field_40;
    u8 pad_42[0x27C];
    s16 result;
} State_0023C770;

extern struct State_0023E610 D_0034FB00;

s32 TkMc_Load_Main(s32 arg0) {
    State_0023C770 *data = (State_0023C770 *)&D_0034FB00;
    s32 var_s1;

    var_s1 = 0;
    if (arg0 == 1) {
        TakuCard_inti(0);
        data->result = 0;
    }
    switch (data->state) {
    case 0:
        var_s1 = TakuLoad_card_kansi(arg0);
        if (var_s1 == 2) {
            data->state = 0;
        }
        break;
    case 1:
        var_s1 = TakuLoad_card_filename_check();
        break;
    case 2:
        var_s1 = TakuLoad_card_file_open();
        break;
    case 3:
        var_s1 = TakuLoad_card_kansi(arg0);
        if (var_s1 == 2) {
            var_s1 = 0xA;
        }
        break;
    }
    if (arg0 == 1) {
        data->field_34 = 0;
        data->field_40 = 0;
        var_s1 = 0x10;
        data->state = 0;
    }
    if (var_s1 == 3) {
        var_s1 = 7;
    }
    if (var_s1 != 0) {
        data->result = var_s1;
    }
    if (var_s1 == 0x100) {
        return 0x100;
    }
    return data->result;
}

typedef struct State_0023C8B0 {
    u8 pad0[8];
    s32 field8;
    s32 fieldC;
    u8 pad10[0x20];
    s16 field30;
    u8 pad32[2];
    s16 field34;
    u8 pad36[0xA];
    s16 field40;
    u8 pad42[0x27C];
    s16 field2BE;
} State_0023C8B0;

extern struct State_0023E610 D_0034FB00;

s32 TkMc_Trade_Load_Main(s32 arg0) {
    State_0023C8B0 *state = (State_0023C8B0 *)&D_0034FB00;
    s32 var_s1;

    var_s1 = 0;
    if (arg0 == 1) {
        TakuCard_inti(0);
        state->field2BE = 0;
    }
    switch (state->field30) {
    case 0:
        var_s1 = TakuLoad_card_kansi(arg0);
        if (var_s1 == 2) {
            state->field30 = 0;
        }
        break;
    case 1:
        var_s1 = TakuLoad_card_filename_check();
        break;
    case 2:
        var_s1 = TakuCustom_card_file_open();
        break;
    case 3:
        var_s1 = TakuLoad_card_kansi(arg0);
        if (var_s1 == 2) {
            var_s1 = 0xA;
        }
        break;
    }
    if (arg0 == 1) {
        state->field34 = 0;
        state->field40 = 0;
        state->field30 = 0;
        var_s1 = 0x10;
        state->fieldC = 0;
    }
    if (var_s1 == 3) {
        var_s1 = 7;
    }
    if (var_s1 != 0) {
        state->field2BE = var_s1;
    }
    if (var_s1 == 0x100) {
        return 0x100;
    }
    if (state->field8 == 1) {
        state->field2BE = state->field2BE | 0x80;
    }
    return state->field2BE;
}

typedef struct State_0023CA10 {
    u8 pad0[8];
    s32 field8;
    u8 padC[0x24];
    s16 field30;
    u8 pad32[2];
    s16 field34;
    u8 pad36[0xA];
    s16 field40;
    u8 pad42[0x16];
    s16 field58;
    u8 pad5A[0x264];
    s16 field2BE;
} State_0023CA10;

s16 TkMc_Trade_Save_Main(s32 arg0) {
    State_0023CA10 *state = (State_0023CA10 *)&D_0034FB00;
    s32 result;

    result = 0;
    if (arg0 == 1) {
        if (TakuCard_inti(1) != 0) {
            state->field58 = 1;
            return 0x600;
        }
        state->field2BE = 0;
    }
    if (state->field58 != 0) {
        return 0x600;
    }
    switch (state->field30) {
    case 0:
        result = TakuTrade_Save_card_kansi(arg0);
        if (result == 2) {
            state->field30 = 0;
        }
        break;
    case 1:
        result = TakuSave_card_filename_check(0);
        break;
    case 2:
        result = TakuSave_card_file_open();
        break;
    case 3:
        result = TakuSave_card_kansi(0);
        break;
    case 4:
        result = TakuSave_make_file();
        break;
    case 5:
        result = TakuTrade_Save_card_file_kakikomi_Ver2();
        break;
    case 10:
        result = TakuSave_card_format();
        break;
    case 11:
        result = TakuTrade_Save_card_kansi(arg0);
        if (state->field2BE == 0xE && arg0 == 2) {
            state->field30 = 0xA;
            state->field34 = 0;
            result = 0xB;
            state->field40 = 0;
        }
        break;
    case 13:
        result = TakuTrade_Save_card_kansi(arg0);
        if (state->field2BE == 1 && arg0 == 2) {
            state->field30 = 5;
            state->field34 = 0;
            result = 9;
            state->field40 = 0;
        }
        break;
    case 14:
        result = TakuTrade_Save_card_kansi(arg0);
        if (result == 2) {
            result = 0xA;
        }
        if (arg0 == 2) {
            state->field30 = 0;
            state->field34 = 0;
            result = 0x700;
            state->field40 = 0;
        }
        break;
    }
    if (arg0 == 1) {
        state->field34 = 0;
        state->field40 = 0;
        state->field30 = 0;
    }
    if (result != 0) {
        state->field2BE = result;
    }
    if (result == 0x100) {
        return 0x100;
    }
    if (state->field8 == 1) {
        state->field2BE = state->field2BE | 0x80;
    }
    return state->field2BE;
}

s16 TkMc_Custom_Main(s32 arg0) {
    extern struct State_0023E610 D_0034FB00;
    u8 *state = (u8 *)&D_0034FB00;
    s32 result;

    result = 0;
    if (arg0 == 1) {
        TakuCard_inti(0);
        *(s16 *)(state + 0x2BE) = 0;
    }

    switch (*(s16 *)(state + 0x30)) {
    case 0:
        result = TakuCustom_card_kansi(arg0);
        if (result == 2) {
            *(s16 *)(state + 0x30) = 0;
        }
        break;
    case 1:
        result = TakuLoad_card_filename_check();
        break;
    case 2:
        result = TakuCustom_card_file_open();
        break;
    case 3:
        result = TakuCustom_card_kansi(arg0);
        if (result == 2) {
            result = 0xA;
        }
        break;
    }

    if (arg0 == 1) {
        *(s16 *)(state + 0x34) = 0;
        *(s16 *)(state + 0x40) = 0;
        *(s16 *)(state + 0x30) = 0;
        result = 0x10;
        *(s32 *)(state + 0xC) = 0;
    }

    if (result != 0) {
        if (*(s32 *)(state + 8) == 1) {
            switch (result) {
            case 2:
                result = 0x200;
                break;
            case 3:
            case 5:
            case 6:
            case 8:
            case 10:
            case 7:
                result = 0x300;
                break;
            }
        } else if (result == 3) {
            result = 7;
        }
        *(s16 *)(state + 0x2BE) = result;
    }

    if (result == 0x100) {
        return 0x100;
    }
    if (*(s32 *)(state + 8) == 1) {
        *(s16 *)(state + 0x2BE) |= 0x80;
    }
    return *(s16 *)(state + 0x2BE);
}

typedef struct State_0023CE40 {
    s32 result;
    s32 status;
    s32 arg0;
    s32 arg1;
    s32 mode;
    s32 size;
    s32 connected;
    u8 pad1C[4];
    s32 ready;
    s32 error;
    u8 pad28[8];
    s16 state;
    u8 pad32[2];
    s16 timer;
    u8 pad36[10];
    s16 retries;
} State_0023CE40;


s32 TakuSave_card_kansi(s32 arg0) {
    extern struct State_0023E610 D_0034FB00;
    extern s32 D_0034FB04;
    extern s32 D_0034FB08;
    extern s32 D_0034FB0C;
    extern s32 D_0034FB10;
    extern s32 D_0034FB14;
    extern s32 D_0034FB18;
    extern s32 D_0034FB20;
    extern s32 D_0034FB24;

    s32 result;
    State_0023CE40 *state = (State_0023CE40 *)&D_0034FB00;

    D_0034FB00.result = func_00194380(D_0034FB08, D_0034FB0C, &D_0034FB10, &D_0034FB14, &D_0034FB18);
    D_0034FB04 = func_00194248(1, &D_0034FB20, &D_0034FB24);
    if (D_0034FB04 == 1 && state->ready == 1) {
        switch (state->error) {
        case 0:
            break;
        case -1:
            state->state = 14;
            state->timer = 0;
            state->retries = 0;
            return 0x700;
        case -2:
            state->state = 14;
            state->timer = 0;
            state->retries = 0;
            return 0x700;
        default:
            if (arg0 != 1) {
                state->state = 14;
                state->timer = 0;
                state->retries = 0;
            }
            break;
        }
        switch (state->mode) {
        case 0:
            if (arg0 == 1 && state->state == 14) {
                state->state = 14;
                state->timer = 0;
                state->retries = 0;
                return 0;
            }
            state->state = 14;
            state->timer = 0;
            state->retries = 0;
            return 2;
        case 1:
            state->state = 14;
            state->timer = 0;
            state->retries = 0;
            return 4;
        case 2:
            break;
        case 3:
            state->state = 14;
            state->timer = 0;
            state->retries = 0;
            return 4;
        default:
            state->state = 14;
            state->timer = 0;
            state->retries = 0;
            return 2;
        }
        if (state->mode == 2) {
                switch (state->connected) {
                case 0:
                    state->retries++;
                    if (state->retries >= 3) {
                        state->state = 11;
                        state->timer = 0;
                        state->retries = 3;
                        if (state->state == 11) {
                            result = 14;
                        } else {
                            result = 3;
                        }
                        return result;
                    }
                    break;
                case 1:
                    state->retries = 0;
                    if (state->state == 0) {
                        state->state = 1;
                    } else if (state->state == 3) {
                        if (state->size < 250) {
                            state->state = 14;
                            state->timer = 0;
                            state->retries = 0;
                            return 5;
                        }
                        if (arg0 == 1) {
                            state->timer = 0;
                            state->retries = 0;
                            state->state = 0;
                            return 0x100;
                        }
                        state->state = 4;
                        return 9;
                    }
                    break;
                default:
                    state->state = 14;
                    state->timer = 0;
                    state->retries = 0;
                    return 2;
                }
        }
    }
    switch (state->state) {
    case 3:
        return 17;
    case 11:
        return 14;
    case 13:
        return 1;
    default:
        return 0;
    }
}

struct State_0023E610;

typedef struct State_0023D170 {
    s32 result;
    s32 sync;
    s32 port;
    s32 slot;
    u8 pad10[0x10];
    s32 command;
    s32 status;
    u8 pad28[8];
    s16 error;
    s16 pad32;
    s16 state;
    u8 pad36[0xA];
    s16 retries;
    u8 pad42[0x1E];
    s32 mode;
    u8 pad64[0x1C];
    u8 entries[0x240];
    u8 info[1];
} State_0023D170;


extern u8 D_0029B100[];
extern u8 D_0029B1BE[];
extern s16 D_0034FB34;

s32 TakuSave_card_filename_check(s32 arg0) {
    extern struct State_0023E610 D_0034FB00;
    State_0023D170 *s = (State_0023D170 *)&D_0034FB00;

    switch (D_0034FB34) {
    case 0:
        s->result = func_00194758(s->port, s->slot, D_0029B100, s->info);
        s->sync = func_00194248(1, &s->command, &s->status);
        if (s->sync == 1 && s->command == 0xC) {
                switch (s->status) {
                case 0:
                    s->state = 1;
                    s->retries = 0;
                    return 0;
                case -2:
                    s->retries++;
                    if (s->retries >= 3) {
                        s->state = 0;
                        s->retries = 3;
                        s->error = 0xB;
                        return 3;
                    }
                    return 0;
                case -4:
                    s->error = 3;
                    s->state = 0;
                    s->retries = 0;
                    return 0x11;
                default:
                    s->state = 0;
                    s->error = 0xE;
                    s->retries = 0;
                    return 2;
                }
        } else {
            return 0;
        }
        break;
    case 1:
        s->result = func_00194578(s->port, s->slot, D_0029B1BE, s->mode, 1, s->entries);
        s->sync = func_00194248(1, &s->command, &s->status);
        if (s->sync == 1 && s->command == 0xD) {
                if (s->status < 0) {
                    switch (s->status) {
                    case -2:
                        s->retries++;
                        if (s->retries >= 3) {
                            s->state = 0;
                            s->retries = 3;
                            s->error = 0xB;
                            return 3;
                        }
                        return 0;
                    case -4:
                        s->error = 0xE;
                        s->state = 0;
                        s->retries = 0;
                        return 0xA;
                    default:
                        s->state = 0;
                        s->error = 0xE;
                        s->retries = 0;
                        return 2;
                    }
                } else {
                    if (arg0 == 1) {
                        s->state = 0;
                        s->retries = 0;
                        s->error = 0;
                        return 0x100;
                    }
                    s->retries = 0;
                    s->state = 0;
                    s->error = 2;
                    return 0x10;
                }
        } else {
            return 0;
        }
        break;
    default:
        return 0;
    }
}

typedef struct State_0023D400 {
    s32 request;
    s32 ready;
    s32 slot;
    s32 mode;
    u8 pad10[0x10];
    s32 command;
    s32 result;
    u8 pad28[8];
    s16 state;
    u8 pad32[2];
    s16 phase;
    u8 pad36[0xA];
    s16 retries;
    u8 pad42[6];
    s32 handles[2];
    u8 pad50[0x266];
    s16 field2B6;
    s16 field2B8;
} State_0023D400;

extern u8 D_0029B1BE[];
extern s16 D_0034FB34;
extern struct State_0023E610 D_0034FB00;

s32 TakuSave_card_file_open(void) {
    State_0023D400 *p = (State_0023D400 *)&D_0034FB00;

    switch (D_0034FB34) {
    case 0:
        p->request = func_00193BA8(p->slot, p->mode, D_0029B1BE, 1);
        p->ready = func_00194248(1, &p->command, &p->result);
        if ((p->ready == 1) && (p->command == 2)) {
                if (p->result < 0) {
                    switch (p->result) {
                    case -2:
                        p->retries++;
                        if (p->retries >= 3) {
                            p->phase = 0;
                            p->retries = 3;
                            p->state = 11;
                            return 3;
                        }
                        return 0;
                    case -3:
                        p->state = 14;
                        p->phase = 0;
                        p->retries = 0;
                        return 5;
                    case -4:
                        p->state = 14;
                        p->phase = 0;
                        p->retries = 0;
                        return 10;
                    case -5:
                        p->state = 14;
                        p->phase = 0;
                        p->retries = 0;
                        return 10;
                    case -7:
                        p->state = 14;
                        p->phase = 0;
                        p->retries = 0;
                        return 10;
                    default:
                        p->phase = 0;
                        p->state = 14;
                        p->retries = 0;
                        return 2;
                    }
                } else {
                    p->handles[p->slot] = p->result;
                    p->retries = 0;
                    p->phase = 1;
                    return 0;
                }
        } else {
            return 0;
        }
        break;
    case 1:
        p->request = func_00193DD0(p->handles[p->slot], p->field2B6, p->field2B8, 1);
        p->ready = func_00194248(1, &p->command, &p->result);
        if ((p->ready == 1) && (p->command == 4)) {
                switch (p->result) {
                case 0:
                    p->retries = 0;
                    p->phase = 2;
                    return 0;
                case -2:
                    p->retries++;
                    if (p->retries >= 3) {
                        p->phase = 0;
                        p->retries = 3;
                        p->state = 11;
                        return 3;
                    }
                    break;
                case -4:
                    p->state = 14;
                    p->phase = 0;
                    p->retries = 0;
                    return 10;
                default:
                    p->phase = 0;
                    p->state = 14;
                    p->retries = 0;
                    return 2;
                }
        } else {
            return 0;
        }
        break;
    case 2:
        FlushCache(0);
        p->request = func_00193F38(p->handles[p->slot], (u8 *)0x1E10000 + p->slot * 0x100F0, 0x100F0);
        p->ready = func_00194248(1, &p->command, &p->result);
        if ((p->ready == 1) && (p->command == 5)) {
                if (p->result < 0) {
                    switch (p->result) {
                    case -2:
                        p->retries++;
                        if (p->retries >= 3) {
                            p->phase = 0;
                            p->retries = 3;
                            p->state = 11;
                            return 3;
                        }
                        return 0;
                    case -4:
                        p->state = 14;
                        p->phase = 0;
                        p->retries = 0;
                        return 10;
                    default:
                        p->phase = 0;
                        p->state = 14;
                        p->retries = 0;
                        return 2;
                    }
                } else {
                    p->retries = 0;
                    p->phase = 3;
                    return 0;
                }
        } else {
            return 0;
        }
        break;
    case 3:
        p->request = sceMcClose(p->handles[p->slot]);
        p->ready = func_00194248(1, &p->command, &p->result);
        if ((p->ready == 1) && (p->command == 3)) {
            switch (p->result) {
            case 0:
                p->phase = 0;
                p->retries = 0;
                p->state = 13;
                return 1;
            case -2:
                p->retries++;
                if (p->retries >= 3) {
                    p->state = 11;
                    p->phase = 0;
                    p->retries = 3;
                    return 3;
                }
                break;
            case -4:
                p->state = 14;
                p->phase = 0;
                p->retries = 0;
                return 10;
            default:
                p->state = 14;
                p->phase = 0;
                p->retries = 0;
                return 2;
            }
        } else {
            return 0;
        }
        break;
    }
    return 0;
}

struct State_0023E610;

typedef struct State_0023D920 {
    s32 result;
    s32 status;
    s32 port;
    s32 slot;
    u8 pad10[0x10];
    s32 command;
    s32 code;
    u8 pad28[8];
    s16 state;
    u8 pad32[2];
    s16 phase;
    u8 pad36[0xA];
    s16 retries;
    u8 pad42[6];
    s32 handles[158];
    u8 buffer[1];
} State_0023D920;

extern s16 D_0034FB34;
extern u8 D_0029B100[];
extern u8 D_0029B1BE[];

s32 TakuSave_make_file(void) {
    extern struct State_0023E610 D_0034FB00;
    State_0023D920 *state = (State_0023D920 *)&D_0034FB00;
    s32 result;

    switch (D_0034FB34) {
    case 0:
        state->result = sceMcMkdir(state->port, state->slot, D_0029B100);
        state->status = func_00194248(1, &state->command, &state->code);
        if (state->status == 1) {
            if (state->command == 0xB) {
                if (state->code != 0) {
                    switch (state->code) {
                    case -2:
                        state->retries++;
                        if (state->retries >= 3) {
                            state->state = 0xB;
                            state->phase = 0;
                            state->retries = 3;
                            return 3;
                        }
                        return 0;
                    case -3:
                        state->state = 0xE;
                        state->phase = 0;
                        state->retries = 0;
                        return 5;
                    case -4:
                        state->state = 0xE;
                        state->phase = 0;
                        state->retries = 0;
                        return 0xA;
                    default:
                        state->state = 0xE;
                        state->phase = 0;
                        state->retries = 0;
                        return 2;
                    }
                } else {
                    state->phase = 1;
                    state->retries = 0;
                    return 0;
                }
            }
        }
        return 0;
    case 1:
        state->result = func_00194758(state->port, state->slot, D_0029B100, state->buffer);
        state->status = func_00194248(1, &state->command, &state->code);
        if (state->status == 1) {
            if (state->command == 0xC) {
                switch (state->code) {
                case 0:
                    state->phase = 2;
                    state->retries = 0;
                    return 0;
                case -2:
                    state->retries++;
                    if (state->retries >= 3) {
                        state->state = 0xB;
                        state->phase = 0;
                        state->retries = 3;
                        return 3;
                    }
                    return 0;
                case -4:
                    state->state = 0xE;
                    state->phase = 0;
                    state->retries = 0;
                    return 0xA;
                default:
                    state->state = 0xE;
                    state->phase = 0;
                    state->retries = 0;
                    return 2;
                }
            }
        }
        return 0;
    case 2:
        result = card_icon_tukuru();
        if (result == 1) {
            state->retries = 0;
            state->phase = 3;
        } else if (result == 0xA) {
            return 0xA;
        }
        break;
    case 3:
        state->result = func_00193BA8(state->port, state->slot, D_0029B1BE, 0x200);
        state->status = func_00194248(1, &state->command, &state->code);
        if (state->status == 1) {
            if (state->command == 2) {
                if (state->code < 0) {
                    switch (state->code) {
                    case -2:
                        state->retries++;
                        if (state->retries >= 3) {
                            state->state = 0xB;
                            state->phase = 0;
                            state->retries = 3;
                            return 3;
                        }
                        return 0;
                    case -3:
                        state->state = 0xE;
                        state->phase = 0;
                        state->retries = 0;
                        return 5;
                    case -4:
                        state->state = 0xE;
                        state->phase = 0;
                        state->retries = 0;
                        return 0xA;
                    case -5:
                        state->state = 0xE;
                        state->phase = 0;
                        state->retries = 0;
                        return 0xA;
                    case -7:
                        state->state = 0xE;
                        state->phase = 0;
                        state->retries = 0;
                        return 0xA;
                    default:
                        state->state = 0xE;
                        state->phase = 0;
                        state->retries = 0;
                        return 2;
                    }
                } else {
                    state->handles[state->port] = state->code;
                    state->phase = 4;
                    state->retries = 0;
                    return 0;
                }
            }
        }
        return 0;
    case 4:
        state->result = sceMcClose(state->handles[state->port]);
        state->status = func_00194248(1, &state->command, &state->code);
        if (state->status == 1) {
            if (state->command == 3) {
                switch (state->code) {
                case 0:
                    state->state = 5;
                    state->retries = 0;
                    state->phase = 0;
                    return 9;
                case -2:
                    state->retries++;
                    if (state->retries >= 3) {
                        state->state = 0xB;
                        state->phase = 0;
                        state->retries = 3;
                        return 3;
                    }
                    return 0;
                case -4:
                    state->state = 0xE;
                    state->phase = 0;
                    state->retries = 0;
                    return 0xA;
                default:
                    state->state = 0xE;
                    state->phase = 0;
                    state->retries = 0;
                    return 2;
                }
            }
        }
        return 0;
    default:
        break;
    }
    return 0;
}

typedef struct Data_0023DE90 {
    s32 ret;
    s32 status;
    s32 port;
    s32 slot;
    u8 pad10[0x10];
    s32 command;
    s32 result;
    u8 pad28[8];
    s16 state;
    u8 pad32[2];
    s16 stage;
    u8 pad36[0xA];
    s16 retries;
    u8 pad42[6];
    s32 handles[2];
    u8 pad50[0x266];
    s16 format0;
    s16 format1;
} Data_0023DE90;

typedef struct Pair_0023DE90 {
    s32 first;
    s32 second;
} Pair_0023DE90;

typedef struct Header_0023DE90 {
    s16 first;
    s16 second;
} Header_0023DE90;

typedef struct Buffer_0023DE90 {
    Header_0023DE90 header;
    Pair_0023DE90 pairs[0x1FF4];
    s32 table[0x53];
} Buffer_0023DE90;

extern u8 D_0029B1BE[];
extern s16 D_0034FB34;

typedef struct Tail_0023DE90 {
    s32 words[0x53];
} Tail_0023DE90;

s32 TakuSave_card_file_kakikomi(void) {
    extern struct State_0023E610 D_0034FB00;
    extern s32 *D_0034FAE8;
    extern Header_0023DE90 D_0034FAF0;
    Data_0023DE90 *data = (Data_0023DE90 *)&D_0034FB00;
    Header_0023DE90 *header;
    s32 *var_v0;

    var_v0 = (s32 *)&D_00299E10;
    switch (D_0034FB34) {
    case 0:
        data->ret = func_00193BA8(data->port, data->slot, D_0029B1BE, 2);
        data->status = func_00194248(1, &data->command, &data->result);
        if (data->status == 1) {
            if (data->command == 2) {
                if (data->result < 0) {
                    switch (data->result) {
                    case -2:
                        data->retries = (s16) (data->retries + 1);
                        if (data->retries >= 3) {
                            data->state = 0xB;
                            data->stage = 0;
                            data->retries = 3;
                            return 3;
                        }
                        return 0;
                    case -3:
                        data->state = 0xE;
                        data->stage = 0;
                        data->retries = 0;
                        return 5;
                    case -4:
                        data->state = 0xE;
                        data->stage = 0;
                        data->retries = 0;
                        return 0xA;
                    case -5:
                        data->state = 0xE;
                        data->stage = 0;
                        data->retries = 0;
                        return 0xA;
                    case -7:
                        data->state = 0xE;
                        data->stage = 0;
                        data->retries = 0;
                        return 0xA;
                    default:
                        data->state = 0xE;
                        data->stage = 0;
                        data->retries = 0;
                        return 2;
                    }
                } else {
                    data->handles[data->port] = (s32) data->result;
                    data->stage = 1;
                    data->retries = 0;
                    return 0;
                }
            }
        }
        return 0;
    case 1:
        data->ret = func_00193DD0(data->handles[data->port], data->format0, data->format1, 2);
        data->status = func_00194248(1, &data->command, &data->result);
        if (data->status == 1) {
            if (data->command == 4) {
                switch (data->result) {
                case 0:
                    data->stage = 2;
                    data->retries = 0;
                    return 0;
                case -2:
                    data->retries = (s16) (data->retries + 1);
                    if (data->retries >= 3) {
                        data->state = 0xB;
                        data->stage = 0;
                        data->retries = 3;
                        return 3;
                    }
                    return 0;
                case -4:
                    data->state = 0xE;
                    data->stage = 0;
                    data->retries = 0;
                    return 0xA;
                default:
                    data->state = 0xE;
                    data->stage = 0;
                    data->retries = 0;
                    return 2;
                }
            }
        }
        return 0;
    case 2: {
        s32 second;
        s32 first;
        s32 count;
        s32 *dst;
        s32 *src;

        src = D_0034FAE8;
        count = 0x1FF4;
        dst = (s32 *)((Buffer_0023DE90 *)0x01E10000)[data->port].pairs;
        do {
            first = *src++;
            second = *src++;
            count--;
            dst[0] = first;
            dst[1] = second;
            dst += 2;
        } while (count > 0);
        header = &((Buffer_0023DE90 *)0x01E10000)[data->port].header;
        *header = D_0034FAF0;
        *(Tail_0023DE90 *)((Buffer_0023DE90 *)0x01E10000)[data->port].table = *(Tail_0023DE90 *)var_v0;
        LkCheckData((u16 *)&((Buffer_0023DE90 *)0x01E10000)[data->port]);
        FlushCache(0);
        data->ret = func_00194058(data->handles[data->port], &((Buffer_0023DE90 *)0x01E10000)[data->port], 0x100F0);
        data->status = func_00194248(1, &data->command, &data->result);
        if (data->status == 1) {
            if (data->command == 6) {
                if (data->result < 0) {
                    switch (data->result) {
                    case -2:
                        data->retries = (s16) (data->retries + 1);
                        if (data->retries >= 3) {
                            data->state = 0xB;
                            data->stage = 0;
                            data->retries = 3;
                            return 3;
                        }
                        return 0;
                    case -3:
                        data->state = 0xE;
                        data->stage = 0;
                        data->retries = 0;
                        return 5;
                    case -4:
                        data->state = 0xE;
                        data->stage = 0;
                        data->retries = 0;
                        return 0xA;
                    case -5:
                        data->state = 0xE;
                        data->stage = 0;
                        data->retries = 0;
                        return 0xA;
                    default:
                        data->state = 0xE;
                        data->stage = 0;
                        data->retries = 0;
                        return 2;
                    }
                } else {
                    data->stage = 4;
                    data->retries = 0;
                    return 0;
                }
            }
        }
        return 0;
    }
    case 3:
        data->ret = sceMcFlush(data->handles[data->port]);
        data->status = func_00194248(1, &data->command, &data->result);
        if (data->status == 1) {
            if (data->command == 0xA) {
                switch (data->result) {
                case 0:
                    data->stage = 4;
                    data->retries = 0;
                    return 0;
                case -2:
                    data->retries = (s16) (data->retries + 1);
                    if (data->retries >= 3) {
                        data->state = 0xB;
                        data->stage = 0;
                        data->retries = 3;
                        return 3;
                    }
                    return 0;
                case -4:
                    data->state = 0xE;
                    data->stage = 0;
                    data->retries = 0;
                    return 0xA;
                default:
                    data->state = 0xE;
                    data->stage = 0;
                    data->retries = 0;
                    return 2;
                }
            }
        }
        return 0;
    case 4:
        data->ret = sceMcClose(data->handles[data->port]);
        data->status = func_00194248(1, &data->command, &data->result);
        if (data->status == 1) {
            if (data->command == 3) {
                switch (data->result) {
                case 0:
                    data->stage = 0;
                    data->retries = 0;
                    data->state = 0;
                    return 0x100;
                case -2:
                    data->retries = (s16) (data->retries + 1);
                    if (data->retries >= 3) {
                        data->state = 0xB;
                        data->stage = 0;
                        data->retries = 3;
                        return 3;
                    }
                    return 0;
                case -4:
                    data->state = 0xE;
                    data->retries = 0;
                    data->stage = 0;
                    return 0xA;
                default:
                    data->state = 0xE;
                    data->retries = 0;
                    data->stage = 0;
                    return 2;
                }
            }
        }
        return 0;
    }
    return 0;
}

extern State_0023E610 D_0034FB00;
extern s32 D_0034FB04;
extern s32 D_0034FB08;
extern s32 D_0034FB0C;
extern s32 D_0034FB20;
extern s32 D_0034FB24;

s32 TakuSave_card_format(void) {
    State_0023E610 *state = &D_0034FB00;

    D_0034FB00.result = func_001948A8(D_0034FB08, D_0034FB0C);
    D_0034FB04 = func_00194248(1, &D_0034FB20, &D_0034FB24);
    if (D_0034FB04 == 1) {
        if (state->command == 0x10) {
            if (state->status == 0) {
                state->field30 = 0xE;
                state->field40 = 0;
                state->field34 = 0;
                return 0xC;
            }
            return 0xD;
        }
    }
    return 0;
}

s32 TakuSave_card_unformat(void) {
    State_0023E610 *state = &D_0034FB00;

    D_0034FB00.result = func_00194E90(D_0034FB08, D_0034FB0C);
    D_0034FB04 = func_00194248(1, &D_0034FB20, &D_0034FB24);
    if (D_0034FB04 == 1) {
        if (state->command == 0x11) {
            if (state->status == 0) {
                state->field30 = 0xE;
                state->field40 = 0;
                state->field34 = 0;
                return 0xC;
            }
            state->field30 = 0xE;
            state->field40 = 0;
            state->field34 = 0;
            return 0xD;
        }
    }
    return 0;
}

typedef struct State_0023E7A0 {
    s32 ret;
    s32 sync;
    s32 port;
    s32 slot;
    u8 pad10[0x10];
    s32 command;
    s32 result;
    u8 pad28[8];
    s16 state;
    u8 pad32[2];
    s16 phase;
    s16 sub;
    u8 pad38[8];
    s16 retries;
    s16 index;
    u8 pad44[4];
    s32 handles[2];
} State_0023E7A0;

typedef struct IconSys_0023E7A0 {
    char head[4];
    u16 unk04;
    u16 offset;
    u32 unk08;
    u32 trans;
    u8 bgColor[0x40];
    u8 lightDir[0x30];
    u8 lightColor[0x30];
    u8 ambient[0x10];
    char title[0x44];
    char view[0x40];
    char copy[0x40];
    char del[0x40];
} IconSys_0023E7A0;

s32 card_icon_tukuru(void) {
    extern struct State_0023E610 D_0034FB00;
    extern s16 D_0034FB36;
    extern u8 D_0034F720[];
    extern char D_0034F7E0[];
    extern u16 D_0034F726;
    extern u32 D_0034F72C;
    extern u8 D_0034F730[];
    extern u8 D_0034F770[];
    extern u8 D_0034F7A0[];
    extern u8 D_0034F7D0[];
    extern char D_0034F824[];
    extern char D_0034F864[];
    extern char D_0034F8A4[];
    extern char *D_0029B06C;
    extern char *D_0029B070;
    extern u8 D_0029B100[];
    extern char D_0030F321[];
    extern char D_0030F32B[];
    extern char D_0030F330[];
    extern u8 D_0029B200[];
    extern u8 D_0029B240[];
    extern u8 D_0029B270[];
    extern u8 D_0029B2A0[];
    extern char *D_0029B068[];
    extern u32 D_0029B050[];
    extern u32 D_0029B054[];
    State_0023E7A0 *s;
    char path[0x40];
    char *end;

    s = (State_0023E7A0 *)&D_0034FB00;
    func_0019BDD8(path, D_0029B100);
    end = path + func_0019BEF0(path);
    func_0019BDD8(end, D_0030F321);
    switch (D_0034FB36) {
    case 0:
        s->ret = func_00193BA8(s->port, s->slot, path, 0x203);
        s->sync = func_00194248(0, &s->command, &s->result);
        if (s->sync == 1) {
            if (s->command == 2) {
                if (0 <= s->result) {
                    s->handles[s->port] = s->result;
                    s->retries = 0;
                    s->sub = 1;
                } else {
                    switch (s->result) {
                    case -2:
                        s->retries++;
                        if (s->retries >= 3) {
                            s->phase = 0;
                            s->sub = 0;
                            s->retries = 3;
                            s->state = 0xB;
                        }
                        break;
                    case -3:
                        s->phase = 0;
                        s->sub = 0;
                        s->state = 0xE;
                        s->retries = 0;
                        return 0xA;
                    case -4:
                        s->phase = 0;
                        s->sub = 0;
                        s->state = 0xE;
                        s->retries = 0;
                        return 0xA;
                    case -5:
                        s->phase = 0;
                        s->sub = 0;
                        s->state = 0xE;
                        s->retries = 0;
                        return 0xA;
                    case -7:
                        s->phase = 0;
                        s->sub = 0;
                        s->state = 0xE;
                        s->retries = 0;
                        return 0xA;
                    default:
                        s->phase = 0;
                        s->sub = 0;
                        s->state = 0xE;
                        s->retries = 0;
                        return 0xA;
                    }
                }
            }
        }
        break;
    case 1:
        func_00198948(D_0034F720, 0, 0x3C4);
        func_0019BDD8((char *)D_0034F720, D_0030F32B);
        func_0019BDD8(D_0034F7E0, D_0030F330);
        D_0034F726 = 0x1E;
        D_0034F72C = 0x60;
        func_00198790(D_0034F730, D_0029B200, 0x40);
        func_00198790(D_0034F770, D_0029B240, 0x30);
        func_00198790(D_0034F7A0, D_0029B270, 0x30);
        func_00198790(D_0034F7D0, D_0029B2A0, 0x10);
        func_0019BDD8(D_0034F824, D_0029B068[0]);
        func_0019BDD8(D_0034F864, D_0029B06C);
        func_0019BDD8(D_0034F8A4, D_0029B070);
        s->ret = func_00194058(s->handles[s->port], D_0034F720, 0x3C4);
        s->sync = func_00194248(0, &s->command, &s->result);
        if (s->sync == 1) {
            if (s->command == 6) {
                if (0 <= s->result) {
                    s->retries = 0;
                    s->sub = 2;
                } else {
                    switch (s->result) {
                    case -2:
                        s->retries++;
                        if (s->retries >= 3) {
                            s->phase = 0;
                            s->sub = 0;
                            s->retries = 3;
                            s->state = 0xB;
                        }
                        break;
                    case -3:
                        s->phase = 0;
                        s->sub = 0;
                        s->state = 0xE;
                        s->retries = 0;
                        return 0xA;
                    case -4:
                        s->phase = 0;
                        s->sub = 0;
                        s->state = 0xE;
                        s->retries = 0;
                        return 0xA;
                    case -5:
                        s->phase = 0;
                        s->sub = 0;
                        s->state = 0xE;
                        s->retries = 0;
                        return 0xA;
                    default:
                        s->phase = 0;
                        s->sub = 0;
                        s->state = 0xE;
                        s->retries = 0;
                        return 0xA;
                    }
                }
            }
        }
        break;
    case 2:
        s->ret = func_00193D18(s->handles[s->port]);
        s->sync = func_00194248(0, &s->command, &s->result);
        if (s->sync == 1) {
            if (s->command == 3) {
                switch (s->result) {
                case 0:
                    s->sub = 3;
                    s->retries = 0;
                    break;
                case -2:
                    s->retries++;
                    if (s->retries >= 3) {
                        s->phase = 0;
                        s->sub = 0;
                        s->retries = 3;
                        s->state = 0xB;
                    }
                    break;
                case -4:
                    s->phase = 0;
                    s->sub = 0;
                    s->state = 0xE;
                    s->retries = 0;
                    return 0xA;
                default:
                    s->phase = 0;
                    s->sub = 0;
                    s->state = 0xE;
                    s->retries = 0;
                    return 0xA;
                }
            }
        }
        break;
    case 3:
        *end = '/';
        func_0019BDD8(end + 1, D_0029B068[s->index]);
        s->ret = func_00193BA8(s->port, s->slot, path, 0x203);
        s->sync = func_00194248(1, &s->command, &s->result);
        if (s->sync == 1) {
            if (s->command == 2) {
                if (0 <= s->result) {
                    s->handles[s->port] = s->result;
                    s->retries = 0;
                    s->sub = 4;
                } else {
                    switch (s->result) {
                    case -2:
                        s->retries++;
                        if (s->retries >= 3) {
                            s->phase = 0;
                            s->sub = 0;
                            s->retries = 3;
                            s->state = 0xB;
                        }
                        break;
                    case -3:
                        s->phase = 0;
                        s->sub = 0;
                        s->state = 0xE;
                        s->retries = 0;
                        return 0xA;
                    case -4:
                        s->phase = 0;
                        s->sub = 0;
                        s->state = 0xE;
                        s->retries = 0;
                        return 0xA;
                    case -5:
                        s->phase = 0;
                        s->sub = 0;
                        s->state = 0xE;
                        s->retries = 0;
                        return 0xA;
                    case -7:
                        s->phase = 0;
                        s->sub = 0;
                        s->state = 0xE;
                        s->retries = 0;
                        return 0xA;
                    default:
                        s->phase = 0;
                        s->sub = 0;
                        s->state = 0xE;
                        s->retries = 0;
                        return 0xA;
                    }
                }
            }
        }
        break;
    case 4:
        {
            s32 size = D_0029B054[s->index] - D_0029B050[s->index];
            s->ret = func_00194058(s->handles[s->port], (u8 *)0x1E301E0 + D_0029B050[s->index], size);
        }
        s->sync = func_00194248(1, &s->command, &s->result);
        if (s->sync == 1) {
            if (s->command == 6) {
                if (0 <= s->result) {
                    s->retries = 0;
                    s->sub = 5;
                } else {
                    switch (s->result) {
                    case -2:
                        s->retries++;
                        if (s->retries >= 3) {
                            s->phase = 0;
                            s->sub = 0;
                            s->retries = 3;
                            s->state = 0xB;
                        }
                        break;
                    case -3:
                        s->phase = 0;
                        s->sub = 0;
                        s->state = 0xE;
                        s->retries = 0;
                        return 0xA;
                    case -4:
                        s->phase = 0;
                        s->sub = 0;
                        s->state = 0xE;
                        s->retries = 0;
                        return 0xA;
                    case -5:
                        s->phase = 0;
                        s->sub = 0;
                        s->state = 0xE;
                        s->retries = 0;
                        return 0xA;
                    default:
                        s->phase = 0;
                        s->sub = 0;
                        s->state = 0xE;
                        s->retries = 0;
                        return 0xA;
                    }
                }
            }
        }
        break;
    case 5:
        s->ret = func_00193D18(s->handles[s->port]);
        s->sync = func_00194248(1, &s->command, &s->result);
        if (s->sync == 1) {
            if (s->command == 3) {
                switch (s->result) {
                case 0:
                    s->index++;
                    if (s->index >= 3) {
                        s->sub = 0;
                        s->retries = 0;
                        return 1;
                    }
                    s->sub = 3;
                    s->retries = 0;
                    break;
                case -2:
                    s->retries++;
                    if (s->retries >= 3) {
                        s->state = 0xB;
                        s->phase = 0;
                        s->sub = 0;
                        s->retries = 3;
                    }
                    break;
                case -4:
                    s->phase = 0;
                    s->sub = 0;
                    s->state = 0xE;
                    s->retries = 0;
                    return 0xA;
                default:
                    s->phase = 0;
                    s->sub = 0;
                    s->state = 0xE;
                    s->retries = 0;
                    return 0xA;
                }
            }
        }
        break;
    }
    return 0;
}

s32 TakuLoad_card_kansi(s32 arg0) {
    extern s32 D_0034FB10;
    extern s32 D_0034FB14;
    extern s32 D_0034FB18;
    u8 *state = (u8 *)&D_0034FB00;
    s32 result;

    D_0034FB00.result = func_00194380(D_0034FB08, D_0034FB0C,
                               &D_0034FB10, &D_0034FB14, &D_0034FB18);
    D_0034FB04 = func_00194248(1, &D_0034FB20, &D_0034FB24);
    if (D_0034FB04 == 1) {
        if (*(s32 *)(state + 0x20) == 1) {
            switch (*(s32 *)(state + 0x24)) {
            case 0:
                goto mode_switch;
            case -1:
                *(s16 *)(state + 0x30) = 3;
                *(s16 *)(state + 0x34) = 0;
                *(s16 *)(state + 0x40) = 0;
                result = 0x700;
                goto done;
            case -2:
                *(s16 *)(state + 0x30) = 3;
                *(s16 *)(state + 0x34) = 0;
                *(s16 *)(state + 0x40) = 0;
                result = 0x700;
                goto done;
            default:
                *(s16 *)(state + 0x30) = 3;
                *(s16 *)(state + 0x34) = 0;
                *(s16 *)(state + 0x40) = 0;
                /* fall through */
            }
mode_switch:
            switch (*(s32 *)(state + 0x10)) {
                case 0:
                    *(s16 *)(state + 0x30) = 3;
                    *(s16 *)(state + 0x34) = 0;
                    *(s16 *)(state + 0x40) = 0;
                    result = 2;
                    goto done;
                case 1:
                    *(s16 *)(state + 0x30) = 3;
                    *(s16 *)(state + 0x34) = 0;
                    *(s16 *)(state + 0x40) = 0;
                    result = 4;
                    goto done;
                case 2:
                    goto state2;
                case 3:
                    *(s16 *)(state + 0x30) = 3;
                    *(s16 *)(state + 0x34) = 0;
                    *(s16 *)(state + 0x40) = 0;
                    result = 4;
                    goto done;
                default:
                    *(s16 *)(state + 0x30) = 3;
                    *(s16 *)(state + 0x34) = 0;
                    *(s16 *)(state + 0x40) = 0;
                    result = 2;
                    goto done;
                }
state2:
                if (*(s32 *)(state + 0x10) == 2) {
                    switch (*(s32 *)(state + 0x18)) {
                    case 0:
                        *(s16 *)(state + 0x40) = *(s16 *)(state + 0x40) + 1;
                        if (*(s16 *)(state + 0x40) >= 3) {
                            *(s16 *)(state + 0x30) = 3;
                            *(s16 *)(state + 0x34) = 0;
                            *(s16 *)(state + 0x40) = 3;
                            result = 3;
                            goto done;
                        }
                        break;
                    case 1:
                        if (*(s16 *)(state + 0x30) == 0) {
                            *(s16 *)(state + 0x30) = 1;
                            *(s16 *)(state + 0x34) = 0;
                            *(s16 *)(state + 0x40) = 0;
                            result = 0x10;
                            goto done;
                        }
                        break;
                    default:
                        *(s16 *)(state + 0x30) = 3;
                        *(s16 *)(state + 0x34) = 0;
                        *(s16 *)(state + 0x40) = 0;
                        result = 2;
                        goto done;
                }
            }
        }
    }
    result = 0;
done:
    return result;
}

typedef struct {
    s32 result;
    s32 status;
    s32 input0;
    s32 input1;
    u8 pad_10[0x10];
    s32 event;
    s32 value;
    u8 pad_28[8];
    s16 action;
    u8 pad_32[2];
    s16 mode;
    u8 pad_36[0xA];
    s16 attempts;
    u8 pad_42[0x1E];
    s32 input2;
    u8 pad_64[0x1C];
    u8 pad_80[0x240];
} State_0023F340;

extern s16 D_0034FB34;
extern u8 D_0029B100[];
extern u8 D_0029B1BE[];


s32 TakuLoad_card_filename_check(void) {
    extern struct State_0023E610 D_0034FB00;
    State_0023F340 *state = (State_0023F340 *)&D_0034FB00;

    switch (D_0034FB34) {
    case 0:
    state->result = func_00194758(state->input0, state->input1,
                                 D_0029B100, (u8 *)state + 0x2C0);
    state->status = func_00194248(1, &state->event, &state->value);
    if (state->status == 1 && state->event == 0xC) {
        switch (state->value) {
        case 0:
            state->mode = 1;
            state->attempts = 0;
            return 0;
        case -2:
            state->attempts++;
            if (state->attempts >= 3) {
                state->action = 3;
                state->mode = 0;
                state->attempts = 3;
                return 3;
            }
            return 0;
        case -4:
            state->action = 3;
            state->mode = 0;
            state->attempts = 0;
            return 7;
        default:
            state->action = 3;
            state->mode = 0;
            state->attempts = 0;
            return 2;
        }
    } else {
        return 0;
    }
    break;

    case 1:
    state->result = func_00194578(state->input0, state->input1,
                                 D_0029B1BE, state->input2, 1,
                                 (u8 *)state + 0x80);
    state->status = func_00194248(1, &state->event, &state->value);
    if (state->status == 1 && state->event == 0xD) {
            if (state->value < 0) {
                switch (state->value) {
                case -2:
                    state->attempts++;
                    if (state->attempts >= 3) {
                        state->action = 3;
                        state->mode = 0;
                        state->attempts = 3;
                        return 3;
                    }
                    return 0;
                case -4:
                    state->action = 3;
                    state->mode = 0;
                    state->attempts = 0;
                    return 10;
                default:
                    state->action = 3;
                    state->attempts = 0;
                    state->mode = 0;
                    return 2;
                }
            }
            state->action = 2;
            state->mode = 0;
            return 9;
    } else {
        return 0;
    }
    break;

    default:
        return 0;
    }
}

typedef struct State_0023F5A0 {
    s32 result;
    s32 status;
    s32 index;
    s32 parameter;
    u8 pad10[0x10];
    s32 command;
    s32 response;
    u8 pad28[8];
    s16 state;
    u8 pad32[2];
    s16 phase;
    u8 pad36[0xA];
    s16 retries;
    u8 pad42[6];
    s32 handles[2];
    u8 pad50[0x266];
    s16 mode;
    s16 length;
} State_0023F5A0;

typedef struct Pair_0023F5A0 {
    s32 first;
    s32 second;
} Pair_0023F5A0;

typedef struct Header_0023F5A0 {
    s16 first;
    s16 second;
} Header_0023F5A0;

typedef struct Save_0023F5A0 {
    Header_0023F5A0 header;
    Pair_0023F5A0 pairs[0x1FF4];
    s32 tail[0x53];
} Save_0023F5A0;

typedef struct Tail_0023F5A0 {
    s32 words[0x53];
} Tail_0023F5A0;

extern u8 D_0029B1BE[];
extern s32 *D_0034FAE8;
extern Header_0023F5A0 D_0034FAF0;
extern s16 D_0034FB34;

s32 TakuLoad_card_file_open(void) {
    extern struct State_0023E610 D_0034FB00;
    State_0023F5A0 *state = (State_0023F5A0 *)&D_0034FB00;
    s32 *destination = (s32 *)&D_00299E10;

    switch (D_0034FB34) {
    case 0:
        state->result = func_00193BA8(state->index, state->parameter, D_0029B1BE, 1);
        state->status = func_00194248(1, &state->command, &state->response);
        if (state->status == 1 && state->command == 2) {
                if (state->response < 0) {
                    switch (state->response) {
                    case -2:
                        state->retries++;
                        if (state->retries >= 3) {
                            state->state = 3;
                            state->phase = 0;
                            state->retries = 3;
                            return 3;
                        }
                        return 0;
                    case -3:
                        state->state = 3;
                        state->phase = 0;
                        state->retries = 0;
                        return 5;
                    case -4:
                        state->state = 3;
                        state->phase = 0;
                        state->retries = 0;
                        return 10;
                    case -5:
                        state->state = 3;
                        state->phase = 0;
                        state->retries = 0;
                        return 10;
                    case -7:
                        state->state = 3;
                        state->phase = 0;
                        state->retries = 0;
                        return 10;
                    default:
                        state->state = 3;
                        state->phase = 0;
                        state->retries = 0;
                        return 2;
                    }
                } else {
                    state->handles[state->index] = state->response;
                    state->phase = 1;
                    state->retries = 0;
                    return 0;
                }
        } else {
            return 0;
        }
        break;
    case 1:
        state->result = func_00193DD0(state->handles[state->index], state->mode, state->length, 1);
        state->status = func_00194248(1, &state->command, &state->response);
        if (state->status == 1 && state->command == 4) {
                switch (state->response) {
                case 0:
                    state->phase = 2;
                    state->retries = 0;
                    return 0;
                case -2:
                    state->retries++;
                    if (state->retries >= 3) {
                        state->state = 3;
                        state->phase = 0;
                        state->retries = 3;
                        return 3;
                    }
                    return 0;
                case -4:
                    state->state = 3;
                    state->phase = 0;
                    state->retries = 0;
                    return 10;
                default:
                    state->state = 3;
                    state->phase = 0;
                    state->retries = 0;
                    return 2;
                }
        } else {
            return 0;
        }
        break;
    case 2:
        FlushCache(0);
        state->result = func_00193F38(state->handles[state->index], &((Save_0023F5A0 *)0x1E10000)[state->index], 0x100F0);
        state->status = func_00194248(1, &state->command, &state->response);
        if (state->status == 1 && state->command == 5) {
                if (state->response < 0) {
                    switch (state->response) {
                    case -2:
                        state->retries++;
                        if (state->retries >= 3) {
                            state->state = 3;
                            state->phase = 0;
                            state->retries = 3;
                            return 3;
                        }
                        return 0;
                    case -4:
                        state->state = 3;
                        state->phase = 0;
                        state->retries = 0;
                        return 10;
                    default:
                        state->state = 3;
                        state->phase = 0;
                        state->retries = 0;
                        return 2;
                    }
                } else {
                    state->phase = 3;
                    state->retries = 0;
                    return 0;
                }
        } else {
            return 0;
        }
        break;
    case 3:
        state->result = sceMcClose(state->handles[state->index]);
        state->status = func_00194248(1, &state->command, &state->response);
        if (state->status == 1 && state->command == 3) {
                switch (state->response) {
                case 0:
                {
                    s32 second;
                    s32 first;
                    s32 count;
                    s32 *dst;
                    s32 *src;

                    state->state = 0;
                    state->phase = 0;
                    state->retries = 0;
                    dst = D_0034FAE8;
                    count = 0x1FF4;
                    src = (s32 *)((Save_0023F5A0 *)0x1E10000)[state->index].pairs;
                    do {
                        first = *src++;
                        second = *src++;
                        count--;
                        dst[0] = first;
                        dst[1] = second;
                        dst += 2;
                    } while (count > 0);
                    D_0034FAF0 = ((Save_0023F5A0 *)0x1E10000)[state->index].header;
                    *(Tail_0023F5A0 *)destination = *(Tail_0023F5A0 *)((Save_0023F5A0 *)0x1E10000)[state->index].tail;
                    if (LkCheckData((u16 *)&((Save_0023F5A0 *)0x1E10000)[state->index]) != 0) {
                        TakuLoad_Name_Set(state->parameter);
                        return 0x100;
                    }
                    state->state = 3;
                    state->phase = 0;
                    state->retries = 0;
                    return 10;
                }
                case -2:
                    state->retries++;
                    if (state->retries >= 3) {
                        state->state = 3;
                        state->phase = 0;
                        state->retries = 3;
                        return 3;
                    }
                    return 0;
                case -4:
                    state->state = 3;
                    state->phase = 0;
                    state->retries = 0;
                    return 10;
                default:
                    state->state = 3;
                    state->phase = 0;
                    state->retries = 0;
                    return 2;
                }
        } else {
            return 0;
        }
        break;
    default:
        return 0;
    }
}

void TakuLoad_Name_Set(s32 side) {
    extern volatile s32 D_002D19D8;
    extern s32 D_002D19E0;
    extern u16 D_002D49D4[];
    s16 i;
    u16 *dest;
    s32 offset;
    u8 *src;
    u16 v;
    s32 off2;

    src = (u8 *)&D_00299E10;
    if (side == 0) {
        i = 0;
        offset = 0;
        while (i < 12) {
            if (i == 0) {
                dest = (u16 *)((u8 *)&D_002D49D4[D_002D19D8] + offset);
                *dest = *(u16 *)(src + 0x24);
            }
            v = *(u16 *)(src + 0x24);
            dest = (u16 *)((u8 *)&D_002D49D4[D_002D19D8] + offset + 4);
            offset += 2;
            *dest = v;
            src += 2;
            i++;
        }
    } else {
        i = 0;
        off2 = 0;
        while (i < 12) {
            v = *(u16 *)(src + 0x24);
            dest = (u16 *)((u8 *)&D_002D49D4[D_002D19E0] + off2);
            off2 += 2;
            *dest = v;
            src += 2;
            i++;
        }
    }
}

typedef struct State_0023FCE0 {
    s32 field_0;
    s32 field_4;
    s32 field_8;
    s32 field_C;
    s32 field_10;
    s32 field_14;
    s32 field_18;
    s32 field_1C;
    s32 field_20;
    s32 field_24;
    u8 pad_28[8];
    s16 field_30;
    s16 field_32;
    s16 field_34;
    u8 pad_36[10];
    s16 field_40;
} State_0023FCE0;

extern s32 D_0034FB04;
extern s32 D_0034FB08;
extern s32 D_0034FB0C;
extern s32 D_0034FB10;
extern s32 D_0034FB14;
extern s32 D_0034FB18;
extern s32 D_0034FB20;
extern s32 D_0034FB24;

static inline void reset_0023FCE0(State_0023FCE0 *state, s32 value) {
    state->field_30 = value;
    state->field_34 = 0;
    state->field_40 = 0;
}

s32 TakuCustom_card_kansi(s32 arg0) {
    extern struct State_0023E610 D_0034FB00;
    State_0023FCE0 *state = (State_0023FCE0 *)&D_0034FB00;
    s32 var_v0;
    s32 var_v0_2;

    *(s32 *)0x0034FB00 = func_00194380(D_0034FB08, D_0034FB0C, &D_0034FB10, &D_0034FB14, &D_0034FB18);
    D_0034FB04 = func_00194248(1, &D_0034FB20, &D_0034FB24);
    if (D_0034FB04 == 1) {
        if (state->field_20 == 1) {
            switch (state->field_24) { /* switch 1; irregular */
            case 0:
                break;
            case -1:
                reset_0023FCE0(state, 3);
                return 0x700;
            case -2:                                /* switch 1 */
                reset_0023FCE0(state, 3);
                return 0x700;
            default:                                /* switch 1 */
                reset_0023FCE0(state, 3);
                break;
            }
                switch (state->field_10) {
                case 0:                             /* switch 2 */
                    reset_0023FCE0(state, 3);
                    return 2;
                case 1:                             /* switch 2 */
                    reset_0023FCE0(state, 3);
                    if (state->field_8 == 1) {
                        var_v0 = 0x400;
                    } else {
                        var_v0 = 4;
                    }
                    return var_v0;
                case 2:
                    break;
                case 3:
                    reset_0023FCE0(state, 3);
                    if (state->field_8 == 1) {
                        var_v0_2 = 0x500;
                    } else {
                        var_v0_2 = 4;
                    }
                    return var_v0_2;
                default:                            /* switch 2 */
                    reset_0023FCE0(state, 3);
                    return 2;
                }
                    if (state->field_10 == 2) {
                        switch (state->field_18) { /* switch 3; irregular */
                        case 0:                     /* switch 3 */
                            state->field_40 = (s16) (state->field_40 + 1);
                            if (state->field_40 >= 3) {
                                state->field_30 = 3;
                                state->field_34 = 0;
                                state->field_40 = 3;
                                return 3;
                            }
                            break;
                        case 1:                     /* switch 3 */
                            if (state->field_30 == 0) {
                                reset_0023FCE0(state, 1);
                                return 0x10;
                            }
                            break;
                        default:                    /* switch 3 */
                            reset_0023FCE0(state, 3);
                            return 2;
                        }
                    }
        }
    }
    return 0;
}

typedef struct State_0023FF30 {
    s32 request;
    s32 status;
    s32 port;
    s32 slot;
    u8 pad10[0x10];
    s32 operation;
    s32 result;
    u8 pad28[8];
    s16 state;
    u8 pad32[2];
    s16 step;
    u8 pad36[0xA];
    s16 retries;
    u8 pad42[2];
    s16 ready[2];
    s32 handles[2];
    u8 pad50[0x266];
    s16 mode;
    s16 offset;
} State_0023FF30;

s32 TakuCustom_card_file_open(void) {
    extern struct State_0023E610 D_0034FB00;
    extern void *D_0034FAEC;
    State_0023FF30 *state;
    s32 *destination;

    state = (State_0023FF30 *)&D_0034FB00;
    destination = (s32 *)&D_00299E10;
    switch (D_0034FB34) {
    case 0:
        state->request = func_00193BA8(state->port, state->slot, D_0029B1BE, 1);
        state->status = func_00194248(1, &state->operation, &state->result);
        if (state->status == 1) {
            if (state->operation == 2) {
                if (state->result < 0) {
                    switch (state->result) {
                    case -2:
                        state->retries = (s16) (state->retries + 1);
                        if (state->retries >= 3) {
                            state->state = 3;
                            state->step = 0;
                            state->retries = 3;
                            return 3;
                        }
                        return 0;
                    case -3:
                        state->state = 3;
                        state->step = 0;
                        state->retries = 0;
                        return 5;
                    case -4:
                        state->state = 3;
                        state->step = 0;
                        state->retries = 0;
                        return 0xA;
                    case -5:
                        state->state = 3;
                        state->step = 0;
                        state->retries = 0;
                        return 0xA;
                    case -7:
                        state->state = 3;
                        state->step = 0;
                        state->retries = 0;
                        return 0xA;
                    default:
                        state->state = 3;
                        state->step = 0;
                        state->retries = 0;
                        return 2;
                    }
                } else {
                    state->handles[state->port] = (s32) state->result;
                    state->step = 1;
                    state->retries = 0;
                    return 0;
                }
            }
        }
        return 0;
    case 1:
        state->request = func_00193DD0(state->handles[state->port], state->mode, state->offset, 1);
        state->status = func_00194248(1, &state->operation, &state->result);
        if (state->status == 1) {
            if (state->operation == 4) {
                switch (state->result) {
                case 0:
                    state->step = 2;
                    state->retries = 0;
                    return 0;
                case -2:
                    state->retries = (s16) (state->retries + 1);
                    if (state->retries >= 3) {
                        state->state = 3;
                        state->step = 0;
                        state->retries = 3;
                        return 3;
                    }
                    return 0;
                case -4:
                    state->state = 3;
                    state->step = 0;
                    state->retries = 0;
                    return 0xA;
                default:
                    state->state = 3;
                    state->step = 0;
                    state->retries = 0;
                    return 2;
                }
            }
        }
        return 0;
    case 2:
        FlushCache(0);
        state->request = func_00193F38(state->handles[state->port], (u8 *)0x01E10000 + state->port * 0x100F0, 0x100F0);
        state->status = func_00194248(1, &state->operation, &state->result);
        if (state->status == 1) {
            if (state->operation == 5) {
                if (state->result < 0) {
                    switch (state->result) {
                    case -2:
                        state->retries = (s16) (state->retries + 1);
                        if (state->retries >= 3) {
                            state->state = 3;
                            state->step = 0;
                            state->retries = 3;
                            return 3;
                        }
                        return 0;
                    case -4:
                        state->state = 3;
                        state->step = 0;
                        state->retries = 0;
                        return 0xA;
                    default:
                        state->state = 3;
                        state->step = 0;
                        state->retries = 0;
                        return 2;
                    }
                } else {
                    state->step = 3;
                    state->retries = 0;
                    return 0;
                }
            }
        }
        return 0;
    case 3:
        state->request = sceMcClose(state->handles[state->port]);
        state->status = func_00194248(1, &state->operation, &state->result);
        if (state->status == 1) {
            if (state->operation == 3) {
                switch (state->result) {
                case 0:
                    state->state = 0;
                    state->step = 0;
                    state->retries = 0;
                    if (state->port == 0) {
                        {
                            s32 second;
                            s32 first;
                            s32 count;
                            s32 *dst;
                            s32 *src;

                            dst = (s32 *)D_0034FAE8;
                            src = (s32 *)((u8 *)0x01E10004 + state->port * 0x100F0);
                            count = 0x1FF4;
                            do {
                                first = *src++;
                                second = *src++;
                                count--;
                                dst[0] = first;
                                dst[1] = second;
                                dst += 2;
                            } while (count > 0);
                        }
                        D_0034FAF0 = *(Header_0023F5A0 *)((u8 *)0x01E10000 + state->port * 0x100F0);
                        *(Tail_0023F5A0 *)destination = *(Tail_0023F5A0 *)((u8 *)0x01E1FFA4 + state->port * 0x100F0);
                        if (LkCheckData((u16 *)((u8 *)0x01E10000 + state->port * 0x100F0)) != 0) {
                            TakuLoad_Name_Set(state->port);
                            state->ready[state->port] = 1;
                            state->port = 1;
                            return 0x10;
                        }
                        state->state = 3;
                        state->step = 0;
                        state->retries = 0;
                        return 0xA;
                    }
                    {
                        s32 second;
                        s32 first;
                        s32 count;
                        s32 *dst;
                        s32 *src;

                        dst = (s32 *)D_0034FAEC;
                        src = (s32 *)((u8 *)0x01E10004 + state->port * 0x100F0);
                        count = 0x1FF4;
                        do {
                            first = *src++;
                            second = *src++;
                            count--;
                            dst[0] = first;
                            dst[1] = second;
                            dst += 2;
                        } while (count > 0);
                    }
                    D_0034FAF0 = *(Header_0023F5A0 *)((u8 *)0x01E10000 + state->port * 0x100F0);
                    *(Tail_0023F5A0 *)destination = *(Tail_0023F5A0 *)((u8 *)0x01E1FFA4 + state->port * 0x100F0);
                    if (LkCheckData((u16 *)((u8 *)0x01E10000 + state->port * 0x100F0)) != 0) {
                        TakuLoad_Name_Set(state->port);
                        state->ready[state->port] = 1;
                        state->port = 1;
                        return 0x100;
                    }
                    state->state = 3;
                    state->step = 0;
                    state->retries = 0;
                    return 0xA;
                case -2:
                    state->retries = (s16) (state->retries + 1);
                    if (state->retries >= 3) {
                        state->state = 3;
                        state->step = 0;
                        state->retries = 3;
                        return 3;
                    }
                    return 0;
                case -4:
                    state->state = 3;
                    state->step = 0;
                    state->retries = 0;
                    return 0xA;
                default:
                    state->state = 3;
                    state->step = 0;
                    state->retries = 0;
                    return 2;
                }
            }
        }
        return 0;
    default:
        return 0;
    }
}

typedef struct State_002406C0 {
    s32 result;
    s32 result4;
    s32 index;
    s32 slot;
    s32 status;
    s32 value;
    s32 ready;
    s32 unused1C;
    s32 status20;
    s32 status24;
    u8 unused28[8];
    s16 mode;
    s16 unused32;
    s16 count;
    u8 unused36[10];
    s16 retries;
    s16 unused42;
    s16 flags[2];
} State_002406C0;

extern s32 D_0034FB04;
extern s32 D_0034FB08;
extern s32 D_0034FB0C;
extern s32 D_0034FB10;
extern s32 D_0034FB14;
extern s32 D_0034FB18;
extern s32 D_0034FB20;
extern s32 D_0034FB24;

s32 TakuTrade_Save_card_kansi(s32 arg0) {
    State_002406C0 *state = (State_002406C0 *)&D_0034FB00;
    s32 ret;

    D_0034FB00.result = func_00194380(D_0034FB08, D_0034FB0C,
                                    &D_0034FB10, &D_0034FB14, &D_0034FB18);
    D_0034FB04 = func_00194248(1, &D_0034FB20, &D_0034FB24);
    if ((D_0034FB04 == 1) && (state->status20 == 1)) {
        switch (state->status24) {
        case 0:
            break;
        case -1:
            state->mode = 14;
            state->count = 0;
            state->retries = 0;
            ret = 0x700;
            goto done;
        case -2:
            state->mode = 14;
            state->count = 0;
            state->retries = 0;
            ret = 0x700;
            goto done;
        default:
            state->mode = 14;
            state->count = 0;
            state->retries = 0;
            break;
        }
        switch (state->status) {
        case 0:
            state->mode = 14;
            state->count = 0;
            state->retries = 0;
            ret = 2;
            goto done;
        case 1:
            state->mode = 14;
            state->count = 0;
            state->retries = 0;
            ret = 4;
            goto done;
        case 2:
            break;
        case 3:
            state->mode = 14;
            state->count = 0;
            state->retries = 0;
            ret = 4;
            goto done;
        default:
            state->mode = 14;
            state->count = 0;
            state->retries = 0;
            ret = 2;
            goto done;
        }
        if (state->status == 2) {
            switch (state->ready) {
            case 0:
                state->retries++;
                if (state->retries >= 3) {
                    state->mode = 11;
                    state->count = 0;
                    state->retries = 3;
                    if (state->mode == 11) {
                        ret = 14;
                    } else {
                        ret = 3;
                    }
                    return ret;
                }
                break;
            case 1:
                state->retries = 0;
                if (state->mode == 0) {
                    if (state->index == 0) {
                        state->flags[state->index] = 1;
                        state->index = 1;
                        ret = 0;
                        goto done;
                    }
                    state->flags[0] = 0;
                    state->flags[1] = 0;
                    state->index = 0;
                    state->mode = 5;
                    ret = 9;
                    goto done;
                }
                if (state->mode == 3) {
                    if (state->value < 250) {
                        state->mode = 14;
                        state->count = 0;
                        state->retries = 0;
                        ret = 5;
                        goto done;
                    }
                    state->mode = 4;
                    ret = 9;
                    goto done;
                }
                break;
            default:
                state->mode = 14;
                state->count = 0;
                state->retries = 0;
                ret = 2;
                goto done;
            }
        }
    }
    switch (state->mode) {
    case 0:
        ret = 9;
        break;
    case 3:
        ret = 17;
        break;
    case 11:
        ret = 14;
        break;
    case 13:
        ret = 1;
        break;
    default:
        ret = 0;
        break;
    }
done:
    return ret;
}

typedef struct IOState_002409E0 {
    s32 call_result;
    s32 sync_result;
    s32 slot;
    s32 path;
    u8 pad10[0x10];
    s32 command;
    s32 result;
    u8 pad28[8];
    s16 state;
    u8 pad32[2];
    s16 step;
    u8 pad36[0xA];
    s16 retries;
    u8 pad42[6];
    s32 handles[2];
    u8 pad50[0x266];
    s16 first_block;
    s16 block_count;
} IOState_002409E0;

extern u8 D_0029B1BE[];
extern s16 D_0034FB34;

s32 TakuTrade_Save_card_file_kakikomi_Ver2(void) {
    extern s32 func_00193DD0();
    extern s32 *D_0034FAE8;
    extern struct State_0023E610 D_0034FB00;
    s32 second;
    s32 first;
    s32 count;
    s32 *dest;
    s32 *source;
    IOState_002409E0 *io = (IOState_002409E0 *)&D_0034FB00;

    switch (D_0034FB34) {
    case 0:
        io->call_result = func_00193BA8(io->slot, io->path, D_0029B1BE, 2);
        io->sync_result = func_00194248(1, &io->command, &io->result);
        if (io->sync_result == 1) {
            if (io->command == 2) {
                if (io->result < 0) {
                    switch (io->result) {
                    case -2:
                        io->retries = (s16) (io->retries + 1);
                        if (io->retries >= 3) {
                            io->state = 0xB;
                            io->step = 0;
                            io->retries = 3;
                            return 3;
                        }
                        return 0;
                    case -3:
                        io->state = 0xE;
                        io->step = 0;
                        io->retries = 0;
                        return 5;
                    case -4:
                        io->state = 0xE;
                        io->step = 0;
                        io->retries = 0;
                        return 0xA;
                    case -5:
                        io->state = 0xE;
                        io->step = 0;
                        io->retries = 0;
                        return 0xA;
                    case -7:
                        io->state = 0xE;
                        io->step = 0;
                        io->retries = 0;
                        return 0xA;
                    default:
                        io->state = 0xE;
                        io->step = 0;
                        io->retries = 0;
                        return 2;
                    }
                } else {
                    io->handles[io->slot] = (s32) io->result;
                    io->step = 1;
                    io->retries = 0;
                    io->step = 0;
                    io->retries = 0;
                    if (io->slot == 0) {
                        io->slot = 1;
                    } else {
                        io->slot = 0;
                        io->step = 1;
                    }
                    return 0;
                }
            }
        }
        return 0;
    case 1:
        io->call_result = func_00193DD0(io->handles[io->slot], io->first_block, io->block_count);
        io->sync_result = func_00194248(1, &io->command, &io->result);
        if (io->sync_result == 1) {
            if (io->command == 4) {
                switch (io->result) {
                case 0:
                    io->step = 2;
                    io->retries = 0;
                    io->step = 1;
                    io->retries = 0;
                    if (io->slot == 0) {
                        io->slot = 1;
                    } else {
                        io->slot = 0;
                        io->step = 2;
                    }
                    return 0;
                case -2:
                    io->retries = (s16) (io->retries + 1);
                    if (io->retries >= 3) {
                        io->state = 0xB;
                        io->step = 0;
                        io->retries = 3;
                        return 3;
                    }
                    return 0;
                case -4:
                    io->state = 0xE;
                    io->step = 0;
                    io->retries = 0;
                    return 0xA;
                default:
                    io->state = 0xE;
                    io->step = 0;
                    io->retries = 0;
                    return 2;
                }
            }
        }
        return 0;
    case 2:
        source = (&D_0034FAE8)[io->slot];
        count = 0x1FF4;
        dest = (s32 *)((u8 *)0x01E10004 + io->slot * 0x100F0);
        do {
            first = *source++;
            second = *source++;
            count--;
            dest[0] = first;
            dest[1] = second;
            dest += 2;
        } while (count > 0);
        LkCheckData((u16 *)((u8 *)0x01E10000 + io->slot * 0x100F0));
        FlushCache(0);
        io->call_result = func_00194058(io->handles[io->slot], (u8 *)0x01E10000 + io->slot * 0x100F0, 0x100F0);
        io->sync_result = func_00194248(1, &io->command, &io->result);
        if (io->sync_result == 1) {
            if (io->command == 6) {
                if (io->result < 0) {
                    switch (io->result) {
                    case -2:
                        io->retries = (s16) (io->retries + 1);
                        if (io->retries >= 3) {
                            io->state = 0xB;
                            io->step = 0;
                            io->retries = 3;
                            return 3;
                        }
                        return 0;
                    case -3:
                        io->state = 0xE;
                        io->step = 0;
                        io->retries = 0;
                        return 5;
                    case -4:
                        io->state = 0xE;
                        io->step = 0;
                        io->retries = 0;
                        return 0xA;
                    case -5:
                        io->state = 0xE;
                        io->step = 0;
                        io->retries = 0;
                        return 0xA;
                    default:
                        io->state = 0xE;
                        io->step = 0;
                        io->retries = 0;
                        return 2;
                    }
                } else {
                    io->step = 4;
                    io->retries = 0;
                    io->step = 2;
                    io->retries = 0;
                    if (io->slot == 0) {
                        io->slot = 1;
                    } else {
                        io->slot = 0;
                        io->step = 4;
                    }
                    return 0;
                }
            }
        }
        return 0;
    case 3:
        io->call_result = sceMcFlush(io->handles[io->slot]);
        io->sync_result = func_00194248(1, &io->command, &io->result);
        if (io->sync_result == 1) {
            if (io->command == 0xA) {
                switch (io->result) {
                case 0:
                    io->step = 4;
                    io->retries = 0;
                    return 0;
                case -2:
                    io->retries = (s16) (io->retries + 1);
                    if (io->retries >= 3) {
                        io->state = 0xB;
                        io->step = 0;
                        io->retries = 3;
                        return 3;
                    }
                    return 0;
                case -4:
                    io->state = 0xE;
                    io->step = 0;
                    io->retries = 0;
                    return 0xA;
                default:
                    io->state = 0xE;
                    io->step = 0;
                    io->retries = 0;
                    return 2;
                }
            }
        }
        return 0;
    case 4:
        io->call_result = sceMcClose(io->handles[io->slot]);
        io->sync_result = func_00194248(1, &io->command, &io->result);
        if (io->sync_result == 1) {
            if (io->command == 3) {
                switch (io->result) {
                case 0:
                    io->step = 0;
                    io->retries = 0;
                    io->state = 0;
                    io->step = 4;
                    io->retries = 0;
                    io->state = 5;
                    if (io->slot == 0) {
                        io->slot = 1;
                        return 0;
                    }
                    io->slot = 0;
                    io->step = 0;
                    return 0x100;
                case -2:
                    io->retries = (s16) (io->retries + 1);
                    if (io->retries >= 3) {
                        io->state = 0xB;
                        io->step = 0;
                        io->retries = 3;
                        return 3;
                    }
                    return 0;
                case -4:
                    io->state = 0xE;
                    io->retries = 0;
                    io->step = 0;
                    return 0xA;
                default:
                    io->state = 0xE;
                    io->retries = 0;
                    io->step = 0;
                    return 2;
                }
            }
        }
        return 0;
    }
    return 0;
}

s32 LkCheckData(u16 *arg0) {
    u16 checksum;
    u16 saved;
    u16 i;
    u16 *p;

    saved = arg0[1];
    checksum = 0;
    i = 0;
    p = arg0;
    arg0[1] = 0;
    while (i < 0x8078) {
        checksum ^= *p++;
        i++;
    }
    checksum ^= 0x4C6B;
    arg0[1] = checksum;
    if (checksum == saved) {
        return 1;
    }
    return 0;
}

struct DotrColorBytes {
    unsigned char v[3];
};
union DotrColorChannels {
    struct DotrColorBytes bytes;
    struct {
        unsigned char r;
        unsigned char g;
        unsigned char b;
    } rgb;
};
extern struct DotrColorBytes D_0029B2B0;

void SzColor_RGB2HLS(float *hls, int r, int g, int b, int max)
{
    

    union DotrColorChannels t;
    int hi;
    int lo;
    int i;
    int sum;
    int diff;
    int mn;
    int mx;

    t.bytes = D_0029B2B0;
    t.rgb.r = r;
    t.rgb.g = g;
    t.rgb.b = b;
    hi = 0;
    lo = 0;
    for (i = 1; i < 3; i++) {
        if (t.bytes.v[hi] < t.bytes.v[i]) {
            hi = i;
        }
        if (t.bytes.v[i] < t.bytes.v[lo]) {
            lo = i;
        }
    }
    mx = t.bytes.v[hi];
    mn = t.bytes.v[lo];
    sum = mx + mn;
    diff = mx - mn;
    hls[0] = 0.0f;
    hls[1] = (float)sum / (float)((unsigned char)max * 2);
    hls[2] = hls[1];
    if (diff != 0 && hls[1] > 0.0f && hls[1] < 1.0f) {
        if (hls[1] <= 0.5f) {
            hls[2] = (float)diff / (float)sum;
        } else {
            hls[2] = (float)diff / (float)((unsigned char)max * 2 - sum);
        }
        hls[0] = (float)(hi * 2) + (float)(t.bytes.v[(hi + 1) % 3] - t.bytes.v[(hi + 2) % 3]) / (float)diff;
        if (hls[0] < 0.0f) {
            hls[0] += 6.0f;
        }
    }
}

#define MIN_002413F0(a, b) ((a) < (b) ? (a) : (b))
#define MAX_002413F0(a, b) ((a) > (b) ? (a) : (b))

void SzColor_HLS2RGB(u8 *out, u8 value, f32 hue, f32 light, f32 sat) {
    f32 color[3];
    f32 frac;
    s32 max;
    s32 mid;
    s32 low;

    while (hue < 0.0f) {
        hue += 6.0f;
    }
    while (hue >= 6.0f) {
        hue -= 6.0f;
    }
    light = MIN_002413F0(MAX_002413F0(light, 0.0f), 1.0f);
    sat = MIN_002413F0(MAX_002413F0(sat, 0.0f), 1.0f);
    max = ((s32)(hue + 0.5f) % 6) >> 1;
    if (hue >= (f32)(max * 2)) {
        mid = (max + 1) % 3;
        low = (max + 2) % 3;
    } else {
        low = (max + 1) % 3;
        mid = (max + 2) % 3;
    }
    if (light <= 0.5f) {
        color[low] = value * (light * (1.0f - sat));
        color[max] = light * (value * 2) - color[low];
    } else {
        color[max] = value * (sat + light * (1.0f - sat));
        color[low] = light * (value * 2) - color[max];
    }
    frac = hue - (f32)(max * 2);
    color[mid] = color[low] + frac * (color[max] - color[low]);
    out[0] = MIN_002413F0((s32)(color[0] + 0.5f), 0xFF);
    out[1] = MIN_002413F0((s32)(color[1] + 0.5f), 0xFF);
    out[2] = MIN_002413F0((s32)(color[2] + 0.5f), 0xFF);
}

typedef struct Vec_00241840 {
    f32 x;
    f32 y;
    f32 z;
} Vec_00241840;

void SzColor_RGB2SEP(u8 *color, s32 r, s32 g, s32 b, s32 arg4, u8 max, f32 scale) {
    extern void SzColor_RGB2HLS(void *, s32, s32, s32, u8);
    Vec_00241840 vec;
    s32 flip;
    s32 isSix;
    s32 mode;
    u8 flags;

    flags = arg4;
    if (flags & 8) {
        flip = 1;
    } else {
        flip = 0;
    }
    mode = flags & 7;
    if (mode == 6) {
        isSix = 1;
    } else {
        isSix = 0;
    }
    SzColor_RGB2HLS(&vec, r, g, b, max);
    if (mode < 7) {
        arg4 &= 7;
        if (flip) {
            arg4 = (u8)(((u8)arg4 + 3) % 6);
        }
        vec.x = (u32)arg4;
    }
    if (isSix) {
        vec.z = 0.0f;
    } else {
        vec.z = vec.z * scale;
    }
    SzColor_HLS2RGB(color, max, vec.x, vec.y, vec.z);
    if (flip) {
        color[0] = max - color[0];
        color[1] = max - color[1];
        color[2] = max - color[2];
    }
    color[0] = (color[0] > 1) ? color[0] : 1;
    color[1] = (color[1] > 1) ? color[1] : 1;
    color[2] = (color[2] > 1) ? color[2] : 1;
}

s32 SzColor_CLUT2SEP(s32 arg0, s32 arg1, f32 scale) {
    u8 color[4];
    s32 temp_v1;

    temp_v1 = arg0 & 0xFFFF;
    if (!(temp_v1 & 0xFFFF7FFF)) {
        return arg0;
    }
    SzColor_RGB2SEP(color, temp_v1 & 0x1F, (temp_v1 >> 5) & 0x1F, (temp_v1 >> 0xA) & 0x1F, arg1, 0x1F, scale);
    return (arg0 & 0x8000) | (((color[2] & 0x1F) << 0xA) | ((color[0] & 0x1F) | ((color[1] & 0x1F) << 5)));
}

typedef struct Buffer_00241A90 {
    u8 data[0x50000];
    s32 field_50000;
    s32 field_50004;
    s32 field_50008;
} Buffer_00241A90;

void readBufCreate(void *arg0) {
    Buffer_00241A90 *buffer = arg0;

    buffer->field_50004 = 0;
    buffer->field_50000 = 0;
    buffer->field_50008 = 0x50000;
}

void readBufDelete(void) {

}

typedef struct Header_00241AD0 {
    u8 padding[0x50000];
    s32 offset;
    s32 start;
    s32 end;
} Header_00241AD0;

s32 readBufBeginPut(void *arg0, void **arg1) {
    s32 size = ((Header_00241AD0 *)arg0)->end - ((Header_00241AD0 *)arg0)->start;

    if (size != 0) {
        *arg1 = (u8 *)arg0 + ((Header_00241AD0 *)arg0)->offset;
    }
    return size;
}

typedef struct {
    u8 padding[0x50000];
    s32 position;
    s32 count;
    s32 capacity;
} Buffer_00241B10;

s32 readBufEndPut(void *arg0, s32 arg1) {
    Buffer_00241B10 *buffer = arg0;
    s32 capacity;
    s32 available;

    capacity = buffer->capacity;
    available = capacity - buffer->count;
    arg1 = (arg1 < available) ? arg1 : available;
    buffer->position = (buffer->position + arg1) % capacity;
    buffer->count = buffer->count + arg1;
    return arg1;
}

typedef struct {
    u8 data[0x50000];
    s32 write_index;
    s32 count;
    s32 capacity;
} Buffer_00241B80;

s32 readBufBeginGet(void *arg0, void **arg1) {
    Buffer_00241B80 *buffer = arg0;
    s32 count;
    s32 capacity;

    count = buffer->count;
    if (count != 0) {
        capacity = buffer->capacity;
        *arg1 = (u8 *)arg0 + ((capacity + (buffer->write_index - count)) % capacity);
    }
    return buffer->count;
}

s32 readBufEndGet(s32 *arg0, s32 arg1) {
    s32 remaining;

    remaining = arg0[0x14001];
    arg1 = (arg1 < remaining) ? arg1 : remaining;
    arg0[0x14001] -= arg1;
    return arg1;
}

typedef struct {
    u16 nloop : 15;
    u16 eop : 1;
    u8 reserved[5];
    u8 pad7 : 4;
    u8 nreg : 4;
    u8 reg : 4;
    u8 pad8 : 4;
    u8 tail[7];
} GifTag_00241C20;

typedef struct {
    void *base;
    s32 size;
    void *current;
    void *giftag;
} Packet_00241C20;

typedef struct {
    __int128 value;
} Quad_00241C20;



void clearGsMem(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    void sceGsSetDefDrawEnv(void *, s32, s64, s64, s32, s32);
    void sceDmaSend(s32, s32);
    extern void sceGifPkInit();
    extern Quad_00241C20 D_0029B2C0;
    extern GifTag_00241C20 D_00350410;
    extern u8 D_00350420[];
    extern u8 D_00350440[];
    Quad_00241C20 tag;
    Packet_00241C20 packet;
    u32 data[24];
    s32 channel;

    tag = D_0029B2C0;
    channel = sceDmaGetChan(2);
    *(__int128 *)&D_00350410 = 0;
    D_00350410.nloop = 8;
    D_00350410.eop = 1;
    D_00350410.nreg = 1;
    D_00350410.reg = 14;
    sceGsSetDefDrawEnv(D_00350420, 0, (s64)(s16)arg3,
                 (s64)(s16)(((((arg4 >> 1) + 31) >> 5) + ((arg4 + 31) >> 5)) << 6),
                 0, 0);
    *(s64 *)D_00350440 = 0;
    FlushCache(0);
    sceGsSyncPath(0, 0);
    sceGsPutDrawEnv(&D_00350410);
    sceGifPkInit(&packet, (__int128 *)data);
    sceGifPkReset(&packet);
    sceGifPkEnd(&packet, 0, 0, 0);
    sceGifPkOpenGifTag(&packet, *(__int128 *)&tag);
    sceGifPkAddGsAD(&packet, 0, 6);
    sceGifPkAddGsAD(&packet, 1, ((s64)arg2 << 16) | ((s64)arg0 | ((s64)arg1 << 8)));
    sceGifPkAddGsAD(&packet, 5, 0);
    sceGifPkAddGsAD(&packet, 5, ((s64)0xB400 << 16) | 0x2D00);
    sceGifPkCloseGifTag(&packet);
    sceGifPkTerminate(&packet);
    FlushCache(0);
    sceGsSyncPath(0, 0);
    sceDmaSend(channel, packet.size);
    sceGsSyncPath(0, 0);
}

typedef struct {
    u32 words[4];
} Tag_00241E80;

extern Tag_00241E80 D_0029B2D0;
extern Tag_00241E80 D_0029B2E0;

void setImageTag(u64 arg0, u8 *arg1, s32 arg2, s32 arg3, s32 arg4) {
    void sceGifPkRef(void *, u64, s32, s32, s32, s32);
    u8 spB0[16];
    Tag_00241E80 spC0;
    Tag_00241E80 spD0;
    s32 temp_s0;
    s32 temp_s7;
    s32 var_s1;
    s32 var_s2;
    s32 var_s3;
    u64 rowBits;
    s32 var_s5;
    u64 *temp_v0;

    spC0 = D_0029B2D0;
    temp_s7 = arg3 >> 4;
    temp_s0 = arg4 >> 4;
    spD0 = D_0029B2E0;
    sceGifPkInit(&spB0, (arg0 & 0x0FFFFFFF) | 0x20000000);
    sceGifPkReset(&spB0);
    if (arg2 == 0) {
        sceGifPkCnt(&spB0, 0, 0, 0);
        sceGifPkOpenGifTag(&spB0, *(__int128 *) &spC0);
        sceGifPkAddGsAD(&spB0, 0x50, 0xC1B00ULL << 0x20);
        sceGifPkAddGsAD(&spB0, 0x52, 0x10 | (0x10ULL << 0x20));
        sceGifPkCloseGifTag(&spB0);
        var_s1 = 0;
        if (var_s1 < temp_s7) {
            var_s5 = 0;
            do {
                var_s2 = 0;
                if (var_s2 < temp_s0) {
                    var_s3 = 0;
                    rowBits = (u64) (u32) var_s5 << 0x20;
                    do {
                        sceGifPkCnt(&spB0, 0, 0, 0);
                        sceGifPkOpenGifTag(&spB0, *(__int128 *) &spC0);
                        sceGifPkAddGsAD(&spB0, 0x51, rowBits | ((u64) (u32) var_s3 << 0x30));
                        sceGifPkAddGsAD(&spB0, 0x53, 0);
                        sceGifPkCloseGifTag(&spB0);
                        temp_v0 = sceGifPkReserve(&spB0, 4);
                        temp_v0[0] = 0x40 | (0x08000000ULL << 0x20);
                        temp_v0[1] = 0;
                        sceGifPkRef(&spB0, (u64) (u32) arg1 & 0x0FFFFFFF, 0x40, 0, 0, 0);
                        var_s2 += 1;
                        arg1 += 0x400;
                        var_s3 += 0x10;
                    } while (var_s2 < temp_s0);
                }
                var_s1 += 1;
                var_s5 += 0x10;
            } while (var_s1 < temp_s7);
        }
    }
    sceGifPkEnd(&spB0, 0, 0, 0);
    sceGifPkOpenGifTag(&spB0, *(__int128 *) &spD0);
    sceGifPkAddGsAD(&spB0, 0x3F, 0);
    sceGifPkAddGsAD(&spB0, 0x14, 0x60);
    sceGifPkAddGsAD(&spB0, 6, (0xA803ULL << 0x10) | 0x1B00 | (0xAULL << 0x20));
    sceGifPkAddGsAD(&spB0, 0, 0x116);
    sceGifPkAddGsAD(&spB0, 3, 0x80008);
    sceGifPkAddGsAD(&spB0, 5, 0x79006C00);
    sceGifPkAddGsAD(&spB0, 3, (s64) ((arg3 * 0x10) + 8) | ((s64) ((arg4 * 0x10) + 8) << 0x10));
    sceGifPkAddGsAD(&spB0, 5, (0x8700ULL << 0x10) | 0x9400);
    sceGifPkCloseGifTag(&spB0);
    sceGifPkTerminate(&spB0);
}

s32 vblankHandler(s32 val) {
    extern volatile s32 D_00350348;
    extern s32 D_00350360;
    extern u8 D_00350420[];
    extern u8 D_00350510[];
    void *dmaGif;
    s32 *tag;

    dmaGif = (void *)sceDmaGetChan(2);
    (&D_00350340)[6] = (*(volatile u64 *)0x12001000 >> 13) & 1;
    if (D_00350340) {
        D_00350348++;
        D_00350360 = sceGsSyncPath(1, 0);
        if (!D_00350360) {
            tag = (s32 *)voBufGetTag(D_00350600);
            if (!tag) {
                D_003505F8++;
                asm("sync"); asm("ei");
                return 0;
            }
            sceGsSetHalfOffset(((&D_00350340)[6] & 1) ? (u8 *)(((u32)D_00350510 & 0x0FFFFFFF) | 0x20000000)
                                                : (u8 *)(((u32)D_00350420 & 0x0FFFFFFF) | 0x20000000),
                               0x800, 0x800, (&D_00350340)[6] ^ 1);
            if ((&D_00350340)[6] == 0 && *tag == 2) {
                sceGsSwapDBuff(D_003503C0, 0);
                sceGsSyncPath(0, 0);
                sceDmaSend(dmaGif, (u8 *)tag + 0x40);
                *tag = 1;
            } else if ((&D_00350340)[6] == 1 && *tag == 1) {
                sceGsSwapDBuff(D_003503C0, 1);
                sceGsSyncPath(0, 0);
                sceDmaSend(dmaGif, (u8 *)tag + 0x26740);
                *tag = 0;
                D_00350350 = 1;
            }
        }
    }
    asm("sync"); asm("ei");
    return 0;
}

s32 handler_endimage(void) {
    if (D_00350350 != 0) {
        voBufDecCount(&D_00350600);
        D_00350350 = 0;
    }
    asm("sync"); asm("ei");
    return 0;
}

void startDisplay(s32 arg0) {
    do {
    } while (arg0 == sceGsSyncV(0));
    D_003505F8 = 0;
    D_00350340 = 1;
    (&D_00350340)[2] = 0;
}

void endDisplay(void) {
    D_00350340 = 0;
    D_003505F8 = 0;
}

void movie_play(s32 arg0, s32 arg1, s32 arg2) {
    D_0029B2F0 = arg1;
    D_003503B0 = arg2;
    clearGsMem(0, 0, 0, 0x280, 0x1C0);
    sceGsSetDefDBuff(D_003503C0, 0, 0x280, 0xE0, 0, 0, 1);
    FlushCache(0);
    D_00350368 = 0x01200000;
    D_00350370 = 0x0152A000;
    D_00350378 = 0x015C3C80;
    D_00350380 = 0x015C4CC0;
    D_00350388 = 0x0178DE40;
    D_00350788 = 0x0178E640;
    D_00350390 = 0x017DE680;
    D_00350398 = 0x017EA680;
    D_003503A0 = 0x0186A680;
    D_003503A8 = 0x0186E680;
    movie(arg0);
}
