/* Debug tools (SzDebug_*). */

#include "common.h"

typedef struct Flags_00203CD0 {
    s8 flag0 : 1;
    s8 flag1 : 1;
    s8 flag2 : 1;
    s8 unused3 : 5;
} Flags_00203CD0;

typedef struct State_00203CD0 {
    s32 f00;
    s32 f04;
    s32 f08;
    s32 f0C;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
    s32 f20;
    s32 f24;
    s32 f28;
    Flags_00203CD0 flags;
} State_00203CD0;

extern State_00203CD0 debugState; /* original: gSzDebug_dl */

/* Starts the debug menus. */
void SzDebug_Init(void) {
    extern s32 func_0019B648();
    extern u8 D_002D078C;
    extern u8 D_002D07F4[];
    extern u8 D_002D07FA[];
    extern u8 D_002D07FF[];
    State_00203CD0 *state = &debugState;
    u8 buffer[0x80];

    RhMem_FillMemory((s8 *)&debugState, 0, 0x30);
    debugState.f00 = 0;
    debugState.f04 = D_002D078C;
    debugState.f08 = 0;
    debugState.f0C = 0;
    debugState.f10 = 0;
    debugState.f14 = 0;
    debugState.f18 = 0;
    debugState.f1C = 0;
    debugState.f20 = 0;
    debugState.f24 = 0;
    debugState.f28 = 2;
    debugState.flags.flag0 = 0;
    debugState.flags.flag1 = 0;
    debugState.flags.flag2 = 0;
    func_0019B648(buffer, D_002D07F4, SzFile_GetEnv((s32)D_002D07FA), D_002D07FF);
    if (getenv((s32)D_002D07FF) != 0) {
        state->flags.flag1 = 1;
    }
}

struct DotrSmallBits {
    signed char unknown_bit_0 : 1;
    signed char unknown_bit_1 : 1;
    signed char unknown_bit_2 : 1;
    signed char unknown_bit_3 : 1;
    signed char unknown_bit_4 : 1;
    signed char unknown_bit_5 : 1;
    signed char unknown_bit_6 : 1;
    signed char unknown_bit_7 : 1;
};
struct DotrSmallFlagsOwner {
    int unknown_00[11];
    struct DotrSmallBits unknown_2c;
};
extern struct DotrSmallFlagsOwner D_00325C80_203e20;
enum {
    DOTR_DEBUG_MENU = 0,  
    DOTR_DEBUG_MODEL = 1, 
    DOTR_DEBUG_DIGIT = 2, 
    
    DOTR_DEBUG_EFF_NO = 3,     
    DOTR_DEBUG_EFF_ARG = 4,    
    DOTR_DEBUG_EFF_A_HI = 5,   
    DOTR_DEBUG_EFF_A_LO = 6,   
    DOTR_DEBUG_EFF_B_HI = 7,   
    DOTR_DEBUG_EFF_B_LO = 8,   
    DOTR_DEBUG_EFF_ROW = 9,    
    DOTR_DEBUG_EFF_COLUMN = 10 
};
struct DotrDebugCardConst {
    unsigned char unknown_00;
    unsigned char unknown_01;
    unsigned char unknown_02;
};
struct DotrDebugCard {
    struct DotrDebugCardConst *info; 
    char unknown_04[0x38];
    unsigned short unknown_3c;       
    unsigned char unknown_3e;
    unsigned char unknown_3f;
    char unknown_40[4];
    unsigned char unknown_44;        
    unsigned char unknown_45;
};
struct DotrDebugDigits {
    int d[3];
};
extern struct DotrDebugDigits D_00293D28;
extern char *gBaseStr[];
extern int func_001F2980_b(int index);
extern int func_001AAF60_b(int);
extern int func_001F2920_b(int index);
extern struct DotrDebugCard *func_001DD130_b(int a, int b);
extern struct DotrDebugCardConst *func_001DD0E0_b(int id);
extern void *func_001DF540_b(int a, int b);
extern int func_001E18A0_b(int a, int b, int value);
extern int func_001F33C0_b(int index, int value);

/* Runs the debug menus on pad 1 (model, camera, light and frame-buffer tools). */
void SzDebug_Act(void)
{
    struct DotrSmallFlagsOwner *p = &D_00325C80_203e20;
    int standby = SzModel_IsModelStandby(p->unknown_00[DOTR_DEBUG_MODEL]);
    int type = func_001F2980_b(p->unknown_00[DOTR_DEBUG_MODEL]);
    int menu = SzDebug_GetActiveMenu();
    int mode = func_001AAF60_b(1);

    if (standby == 0 && p->unknown_00[DOTR_DEBUG_MENU] > 0 && p->unknown_00[DOTR_DEBUG_MENU] < 12) {
        p->unknown_00[DOTR_DEBUG_MENU] = 0;
        menu = 0;
    }
    if (p->unknown_00[DOTR_DEBUG_MENU] == 2 && type != 4 && type != 5) {
        p->unknown_00[DOTR_DEBUG_MENU] = 0;
        menu = 0;
    }
    if (!(p->unknown_00[DOTR_DEBUG_MENU] != 3 && p->unknown_00[DOTR_DEBUG_MENU] != 5 && p->unknown_00[DOTR_DEBUG_MENU] != 6) && (type != 5 || mode != 5)) {
        p->unknown_00[DOTR_DEBUG_MENU] = 0;
        menu = 0;
    }
    if (p->unknown_00[DOTR_DEBUG_MENU] == 4 && (type != 6 || mode != 0)) {
        p->unknown_00[DOTR_DEBUG_MENU] = 0;
        menu = 0;
    }
    if (p->unknown_2c.unknown_bit_1) {
        if (SzPad_Check(1, 0, 0x800)) {
            p->unknown_2c.unknown_bit_2 = p->unknown_2c.unknown_bit_2 ? 0 : 1;
        }
    } else if (SzPad_Check(1, 0, 0x800)) {
        SzView_SetMode(0, (SzView_GetMode(0) + 1) % 3);
    }
    if (SzPad_Check(1, 0, 0x100)) {
        p->unknown_2c.unknown_bit_0 = p->unknown_2c.unknown_bit_0 ? 0 : 1;
    }
    if (p->unknown_2c.unknown_bit_2) {
        lSzDebug_ActEffect();
        return;
    }
    if (SzPad_Check(0, 2, 0x100)) {
        for (;;) {
            p->unknown_00[DOTR_DEBUG_MENU] = (p->unknown_00[DOTR_DEBUG_MENU] + 17) % 18;
            if (standby == 0 && p->unknown_00[DOTR_DEBUG_MENU] > 0 && p->unknown_00[DOTR_DEBUG_MENU] <= 11) {
                continue;
            }
            if (p->unknown_00[DOTR_DEBUG_MENU] == 2 && type != 4 && type != 5) {
                continue;
            }
            if (!(p->unknown_00[DOTR_DEBUG_MENU] != 3 && p->unknown_00[DOTR_DEBUG_MENU] != 5 && p->unknown_00[DOTR_DEBUG_MENU] != 6) && (type != 5 || mode != 5)) {
                continue;
            }
            if (p->unknown_00[DOTR_DEBUG_MENU] == 4 && (type != 6 || mode != 0)) {
                continue;
            }
            break;
        }
        SzSound_PlaySE(0, 0);
    }
    if (SzPad_Check(0, 2, 0x800)) {
        for (;;) {
            p->unknown_00[DOTR_DEBUG_MENU] = (p->unknown_00[DOTR_DEBUG_MENU] + 19) % 18;
            if (standby == 0 && p->unknown_00[DOTR_DEBUG_MENU] > 0 && p->unknown_00[DOTR_DEBUG_MENU] <= 11) {
                continue;
            }
            if (p->unknown_00[DOTR_DEBUG_MENU] == 2 && type != 4 && type != 5) {
                continue;
            }
            if (!(p->unknown_00[DOTR_DEBUG_MENU] != 3 && p->unknown_00[DOTR_DEBUG_MENU] != 5 && p->unknown_00[DOTR_DEBUG_MENU] != 6) && (type != 5 || mode != 5)) {
                continue;
            }
            if (p->unknown_00[DOTR_DEBUG_MENU] == 4 && (type != 6 || mode != 0)) {
                continue;
            }
            break;
        }
        SzSound_PlaySE(0, 0);
    }
    if (menu == 0) {
        int no = func_001F2920_b(p->unknown_00[DOTR_DEBUG_MODEL]);
        struct DotrDebugDigits dd = D_00293D28;
        int n;
        

        {
            int *e = dd.d;
            *e++ = (no / 100) % 10;
            *e++ = (no / 10) % 10;
            *e = no % 10;
        }
        n = no;
        if (SzPad_Check(0, 2, 0x5000)) {
            if (SzPad_Check(0, 2, 0x1000)) {
                dd.d[p->unknown_00[DOTR_DEBUG_DIGIT]] = (dd.d[p->unknown_00[DOTR_DEBUG_DIGIT]] + 11) % 10;
            } else {
                dd.d[p->unknown_00[DOTR_DEBUG_DIGIT]] = (dd.d[p->unknown_00[DOTR_DEBUG_DIGIT]] + 9) % 10;
            }
            n = dd.d[0] * 100 + dd.d[1] * 10 + dd.d[2];
        }
        if (SzPad_Check(0, 2, 2)) {
            n = (n + 1001) % 1000;
        }
        if (SzPad_Check(0, 2, 1)) {
            n = (n + 999) % 1000;
        }
        if (SzPad_Check(0, 2, 0x2000)) {
            p->unknown_00[DOTR_DEBUG_DIGIT] = (p->unknown_00[DOTR_DEBUG_DIGIT] + 4) % 3;
        }
        if (SzPad_Check(0, 2, 0x8000)) {
            p->unknown_00[DOTR_DEBUG_DIGIT] = (p->unknown_00[DOTR_DEBUG_DIGIT] + 2) % 3;
        }
        if (n == no) {
            if (SzPad_Check(0, 2, 8)) {
                p->unknown_00[DOTR_DEBUG_MODEL] = (p->unknown_00[DOTR_DEBUG_MODEL] + 45) % 44;
            }
            if (SzPad_Check(0, 2, 4)) {
                p->unknown_00[DOTR_DEBUG_MODEL] = (p->unknown_00[DOTR_DEBUG_MODEL] + 43) % 44;
            }
            type = func_001F2980_b(p->unknown_00[DOTR_DEBUG_MODEL]);
        } else if (!SzModel_IsModelLoading(p->unknown_00[DOTR_DEBUG_MODEL])) {
            struct DotrDebugCard *q = func_001DD130_b(-1, p->unknown_00[DOTR_DEBUG_MODEL]);
            if (q != 0) {
                q->unknown_3c = SzDuel_Xax2New(n);
                q->info = func_001DD0E0_b(q->unknown_3c);
                if (q->info != 0) {
                    q->unknown_3e = q->info->unknown_00;
                    q->unknown_3f = q->info->unknown_02 & 0xf;
                }
            }
            SzModel_Preset(p->unknown_00[DOTR_DEBUG_MODEL], -1, n);
        }
        if (SzPad_Check(0, 0, 0x30) && !SzModel_IsModelLoading(p->unknown_00[DOTR_DEBUG_MODEL])) {
            int flag = SzPad_Check(0, 0, 0x10) ? 1 : 0;
            int none = 0;
            if ((type == 4 || type == 5) && func_001DF540_b(-1, p->unknown_00[DOTR_DEBUG_MODEL]) == 0) {
                none = 1;
            }
            if (!none && SzModel_Load(p->unknown_00[DOTR_DEBUG_MODEL], -1, n, flag) && (type == 4 || type == 5)) {
                struct DotrDebugCard *q = func_001DD130_b(-1, p->unknown_00[DOTR_DEBUG_MODEL]);
                if (q != 0 && q->info != 0) {
                    if (mode == 5 && type == 5) {
                        SzBattle_Entry(q->unknown_44, (q->unknown_44 << 8) | q->unknown_45);
                        SzDuel_SetBusyFlag(q->unknown_44, q->unknown_45, 0);
                    }
                    func_001E18A0_b(-1, p->unknown_00[DOTR_DEBUG_MODEL], 7);
                    SzDuel_SetUnitCtlRateM(-1, p->unknown_00[DOTR_DEBUG_MODEL], 1, 0);
                }
            }
        }
        if (type == 4 || type == 5) {
            if (SzPad_Check(0, 0, 0x80)) {
                SzModel_SetDeform(p->unknown_00[DOTR_DEBUG_MODEL], 1);
            }
            if (SzPad_Check(0, 0, 0x40)) {
                SzModel_SetDeform(p->unknown_00[DOTR_DEBUG_MODEL], 0);
            }
            if (SzPad_Check(0, 0, 0x600)) {
                func_001F33C0_b(p->unknown_00[DOTR_DEBUG_MODEL], 1);
            }
        }
    }
    if (SzDebug_IsHide()) {
        return;
    }
    func_001F2920_b(p->unknown_00[DOTR_DEBUG_MODEL]);
    func_0019BEF0(gBaseStr[type]);
    {
    int none = 0;
    if ((type == 4 || type == 5) && func_001DF540_b(-1, p->unknown_00[DOTR_DEBUG_MODEL]) == 0) {
        none = 1;
    }
    if (!none && !SzModel_IsModelReady(p->unknown_00[DOTR_DEBUG_MODEL]) && !SzModel_IsModelLoading(p->unknown_00[DOTR_DEBUG_MODEL]) && SzModel_IsModelStandby(p->unknown_00[DOTR_DEBUG_MODEL])) {
        SzModel_IsModelDisp(p->unknown_00[DOTR_DEBUG_MODEL]);
    }
    }
    SzModel_GetDeform(p->unknown_00[DOTR_DEBUG_MODEL]);
    if (menu == 0) {
        int i = p->unknown_00[DOTR_DEBUG_DIGIT];
        int k = 100;
        while (i-- != 0) {
            k /= 10;
        }
    }
}

struct DotrSmallBits_2047f0 {
    signed char unknown_bit_0 : 1;
    signed char unknown_bit_1 : 1;
    signed char unknown_bit_2 : 1;
    signed char unknown_bit_3 : 1;
    signed char unknown_bit_4 : 1;
    signed char unknown_bit_5 : 1;
    signed char unknown_bit_6 : 1;
    signed char unknown_bit_7 : 1;
};
struct DotrSmallFlagsOwner_2047f0 {
    int unknown_00[11];
    struct DotrSmallBits_2047f0 unknown_2c;
};
extern struct DotrSmallFlagsOwner_2047f0 D_00325C80_2047f0;
enum {
    DOTR_DEBUG_MENU_2047f0 = 0,  
    DOTR_DEBUG_MODEL_2047f0 = 1, 
    DOTR_DEBUG_DIGIT_2047f0 = 2, 
    
    DOTR_DEBUG_EFF_NO_2047f0 = 3,     
    DOTR_DEBUG_EFF_ARG_2047f0 = 4,    
    DOTR_DEBUG_EFF_A_HI_2047f0 = 5,   
    DOTR_DEBUG_EFF_A_LO_2047f0 = 6,   
    DOTR_DEBUG_EFF_B_HI_2047f0 = 7,   
    DOTR_DEBUG_EFF_B_LO_2047f0 = 8,   
    DOTR_DEBUG_EFF_ROW_2047f0 = 9,    
    DOTR_DEBUG_EFF_COLUMN_2047f0 = 10 
};
struct DotrDebugDigits_2047f0 {
    int d[3];
};
extern struct DotrDebugDigits_2047f0 D_00293D38;
extern struct DotrDebugDigits_2047f0 D_00293D48;
int func_001F48F0_b(int a, int b, int c, int d, int e);

/* Runs the debug effect player. */
void lSzDebug_ActEffect(void)
{
    struct DotrSmallFlagsOwner_2047f0 *p = &D_00325C80_2047f0;

    if ((SzPad_Check(0, 1, 3) & 0xffff) != 3) {
    struct DotrDebugDigits_2047f0 a = D_00293D38;
    int no = p->unknown_00[DOTR_DEBUG_EFF_NO_2047f0];
    struct DotrDebugDigits_2047f0 b;
    int arg;
    
    {
        int *e = a.d;
        *e++ = (no / 100) % 10;
        *e++ = (no / 10) % 10;
        *e = no % 10;
    }
    b = D_00293D48;
    arg = p->unknown_00[DOTR_DEBUG_EFF_ARG_2047f0];
    {
        int *e = b.d;
        *e++ = (arg / 100) % 10;
        *e++ = (arg / 10) % 10;
        *e = arg % 10;
    }
    switch (p->unknown_00[DOTR_DEBUG_EFF_ROW_2047f0]) {
    case 0:
        if (SzPad_Check(0, 2, 0x2000)) {
            if (++p->unknown_00[DOTR_DEBUG_EFF_COLUMN_2047f0] > 2) {
                p->unknown_00[DOTR_DEBUG_EFF_ROW_2047f0] = 1;
                p->unknown_00[DOTR_DEBUG_EFF_COLUMN_2047f0] = 0;
            }
        } else if (SzPad_Check(0, 2, 0x8000)) {
            if (--p->unknown_00[DOTR_DEBUG_EFF_COLUMN_2047f0] < 0) {
                p->unknown_00[DOTR_DEBUG_EFF_ROW_2047f0] = 5;
                p->unknown_00[DOTR_DEBUG_EFF_COLUMN_2047f0] = 0;
            }
        } else if (SzPad_Check(0, 2, 0x5000)) {
            int i = p->unknown_00[DOTR_DEBUG_EFF_COLUMN_2047f0];
            if (SzPad_Check(0, 2, 0x1000)) {
                a.d[i] = (a.d[i] + 11) % 10;
            } else {
                a.d[i] = (a.d[i] + 9) % 10;
            }
            p->unknown_00[DOTR_DEBUG_EFF_NO_2047f0] = a.d[0] * 100 + a.d[1] * 10 + a.d[2];
        }
        break;
    case 1:
        if (SzPad_Check(0, 2, 0x2000)) {
            if (++p->unknown_00[DOTR_DEBUG_EFF_COLUMN_2047f0] > 2) {
                p->unknown_00[DOTR_DEBUG_EFF_ROW_2047f0] = 2;
                p->unknown_00[DOTR_DEBUG_EFF_COLUMN_2047f0] = 0;
            }
        } else if (SzPad_Check(0, 2, 0x8000)) {
            if (--p->unknown_00[DOTR_DEBUG_EFF_COLUMN_2047f0] < 0) {
                p->unknown_00[DOTR_DEBUG_EFF_ROW_2047f0] = 0;
                p->unknown_00[DOTR_DEBUG_EFF_COLUMN_2047f0] = 2;
            }
        } else if (SzPad_Check(0, 2, 0x5000)) {
            int i = p->unknown_00[DOTR_DEBUG_EFF_COLUMN_2047f0];
            if (SzPad_Check(0, 2, 0x1000)) {
                b.d[i] = (b.d[i] + 11) % 10;
            } else {
                b.d[i] = (b.d[i] + 9) % 10;
            }
            p->unknown_00[DOTR_DEBUG_EFF_ARG_2047f0] = b.d[0] * 100 + b.d[1] * 10 + b.d[2];
        }
        break;
    case 2:
        if (SzPad_Check(0, 2, 0x2000)) {
            if (++p->unknown_00[DOTR_DEBUG_EFF_COLUMN_2047f0] > 0) {
                p->unknown_00[DOTR_DEBUG_EFF_ROW_2047f0] = 3;
                p->unknown_00[DOTR_DEBUG_EFF_COLUMN_2047f0] = 0;
            }
        } else if (SzPad_Check(0, 2, 0x8000)) {
            if (--p->unknown_00[DOTR_DEBUG_EFF_COLUMN_2047f0] < 0) {
                p->unknown_00[DOTR_DEBUG_EFF_ROW_2047f0] = 1;
                p->unknown_00[DOTR_DEBUG_EFF_COLUMN_2047f0] = 2;
            }
        } else if (SzPad_Check(0, 2, 0x5000)) {
            if (SzPad_Check(0, 2, 0x1000)) {
                p->unknown_00[DOTR_DEBUG_EFF_A_HI_2047f0] = (p->unknown_00[DOTR_DEBUG_EFF_A_HI_2047f0] + 3) % 2;
            } else {
                p->unknown_00[DOTR_DEBUG_EFF_A_HI_2047f0] = (p->unknown_00[DOTR_DEBUG_EFF_A_HI_2047f0] + 1) % 2;
            }
        }
        break;
    case 3:
        if (SzPad_Check(0, 2, 0x2000)) {
            if (++p->unknown_00[DOTR_DEBUG_EFF_COLUMN_2047f0] > 0) {
                p->unknown_00[DOTR_DEBUG_EFF_ROW_2047f0] = 4;
                p->unknown_00[DOTR_DEBUG_EFF_COLUMN_2047f0] = 0;
            }
        } else if (SzPad_Check(0, 2, 0x8000)) {
            if (--p->unknown_00[DOTR_DEBUG_EFF_COLUMN_2047f0] < 0) {
                p->unknown_00[DOTR_DEBUG_EFF_ROW_2047f0] = 2;
                p->unknown_00[DOTR_DEBUG_EFF_COLUMN_2047f0] = 0;
            }
        } else if (SzPad_Check(0, 2, 0x5000)) {
            if (SzPad_Check(0, 2, 0x1000)) {
                p->unknown_00[DOTR_DEBUG_EFF_A_LO_2047f0] = (p->unknown_00[DOTR_DEBUG_EFF_A_LO_2047f0] + 12) % 11;
            } else {
                p->unknown_00[DOTR_DEBUG_EFF_A_LO_2047f0] = (p->unknown_00[DOTR_DEBUG_EFF_A_LO_2047f0] + 10) % 11;
            }
        }
        break;
    case 4:
        if (SzPad_Check(0, 2, 0x2000)) {
            if (++p->unknown_00[DOTR_DEBUG_EFF_COLUMN_2047f0] > 0) {
                p->unknown_00[DOTR_DEBUG_EFF_ROW_2047f0] = 5;
                p->unknown_00[DOTR_DEBUG_EFF_COLUMN_2047f0] = 0;
            }
        } else if (SzPad_Check(0, 2, 0x8000)) {
            if (--p->unknown_00[DOTR_DEBUG_EFF_COLUMN_2047f0] < 0) {
                p->unknown_00[DOTR_DEBUG_EFF_ROW_2047f0] = 3;
                p->unknown_00[DOTR_DEBUG_EFF_COLUMN_2047f0] = 0;
            }
        } else if (SzPad_Check(0, 2, 0x5000)) {
            if (SzPad_Check(0, 2, 0x1000)) {
                p->unknown_00[DOTR_DEBUG_EFF_B_HI_2047f0] = (p->unknown_00[DOTR_DEBUG_EFF_B_HI_2047f0] + 3) % 2;
            } else {
                p->unknown_00[DOTR_DEBUG_EFF_B_HI_2047f0] = (p->unknown_00[DOTR_DEBUG_EFF_B_HI_2047f0] + 1) % 2;
            }
        }
        break;
    case 5:
        if (SzPad_Check(0, 2, 0x2000)) {
            if (++p->unknown_00[DOTR_DEBUG_EFF_COLUMN_2047f0] > 0) {
                p->unknown_00[DOTR_DEBUG_EFF_ROW_2047f0] = 0;
                p->unknown_00[DOTR_DEBUG_EFF_COLUMN_2047f0] = 0;
            }
        } else if (SzPad_Check(0, 2, 0x8000)) {
            if (--p->unknown_00[DOTR_DEBUG_EFF_COLUMN_2047f0] < 0) {
                p->unknown_00[DOTR_DEBUG_EFF_ROW_2047f0] = 4;
                p->unknown_00[DOTR_DEBUG_EFF_COLUMN_2047f0] = 0;
            }
        } else if (SzPad_Check(0, 2, 0x5000)) {
            if (SzPad_Check(0, 2, 0x1000)) {
                p->unknown_00[DOTR_DEBUG_EFF_B_LO_2047f0] = (p->unknown_00[DOTR_DEBUG_EFF_B_LO_2047f0] + 12) % 11;
            } else {
                p->unknown_00[DOTR_DEBUG_EFF_B_LO_2047f0] = (p->unknown_00[DOTR_DEBUG_EFF_B_LO_2047f0] + 10) % 11;
            }
        }
        break;
    }
    if (SzPad_Check(0, 2, 8)) {
        p->unknown_00[DOTR_DEBUG_EFF_A_LO_2047f0] = (p->unknown_00[DOTR_DEBUG_EFF_A_LO_2047f0] + 12) % 11;
    }
    if (SzPad_Check(0, 2, 4)) {
        p->unknown_00[DOTR_DEBUG_EFF_A_LO_2047f0] = (p->unknown_00[DOTR_DEBUG_EFF_A_LO_2047f0] + 10) % 11;
    }
    if (SzPad_Check(0, 0, 0x10)) {
        SzEffect_Clear();
    }
    if (SzPad_Check(0, 0, 0x40)) {
        SzEffect_Destroy2(0, p->unknown_00[DOTR_DEBUG_EFF_NO_2047f0]);
    }
    if (SzPad_Check(0, 0, 0x20)) {
        func_001F48F0_b(0, p->unknown_00[DOTR_DEBUG_EFF_NO_2047f0], p->unknown_00[DOTR_DEBUG_EFF_ARG_2047f0],
                       (p->unknown_00[DOTR_DEBUG_EFF_A_HI_2047f0] << 8) | p->unknown_00[DOTR_DEBUG_EFF_A_LO_2047f0],
                       (p->unknown_00[DOTR_DEBUG_EFF_B_HI_2047f0] << 8) | p->unknown_00[DOTR_DEBUG_EFF_B_LO_2047f0]);
    }
    if (SzPad_Check(0, 0, 0x80)) {
        SzEffect_Erase2(0, -1);
    }
    if (SzPad_Check(0, 0, 0x800)) {
        SzEffect_Sleep2(0, p->unknown_00[DOTR_DEBUG_EFF_NO_2047f0], 0);
    }
    if (SzPad_Check(0, 0, 0x100)) {
        SzEffect_Sleep2(0, p->unknown_00[DOTR_DEBUG_EFF_NO_2047f0], 1);
    }
    }
    {
        int i = p->unknown_00[DOTR_DEBUG_EFF_COLUMN_2047f0];
        int k = 100;
        while (i-- != 0) {
            k /= 10;
        }
    }
}

/* The open debug menu. */
s32 SzDebug_GetActiveMenu(void) {
    return debugState.f00;
}

/* The model slot the debug menu works on. */
s32 SzDebug_GetActiveModel(void) {
    return debugState.f04;
}

typedef struct Flags_00205170 {
    s8 flag0 : 1;
    s8 unused1 : 1;
    s8 flag2 : 1;
    s8 unused3 : 5;
} Flags_00205170;

typedef struct State_00205170 {
    u8 padding[0x2C];
    Flags_00205170 flags;
} State_00205170;

/* Whether the debug display is hidden. */
s32 SzDebug_IsHide(void) {
    extern Flags_00205170 D_00325CAC;
    State_00205170 *state = (State_00205170 *)&debugState;

    if (D_00325CAC.flag2 != 0) {
        return 1;
    }
    return state->flags.flag0 != 0 ? 1 : 0;
}

typedef struct {
    s8 enabled : 1;
} Flags_002051C0;

/* Hides or shows the debug display. */
void SzDebug_SetHideFlag(s64 on) {
    extern Flags_002051C0 D_00325CAC;

    D_00325CAC.enabled = (s8)on;
}

typedef struct {
    s8 : 2;
    s8 flag : 1;
} Flags_002051F0;

extern Flags_002051F0 D_00325CAC;

/* Whether the debug effect player is running. */
s32 SzDebug_IsEffect(void) {
    return D_00325CAC.flag ? 1 : 0;
}

#pragma pack(2)
typedef struct BitmapFileHeader_00205210 {
    s16 type;
    u16 sizeLow;
    u16 sizeHigh;
    s16 reserved1;
    s16 reserved2;
    u16 offsetLow;
    u16 offsetHigh;
} BitmapFileHeader_00205210;
#pragma pack()

typedef struct BitmapInfo_00205210 {
    s32 size;
    s32 width;
    s32 height;
    s16 planes;
    s16 bits;
    s32 compression;
    s32 imageSize;
    s32 horizontalResolution;
    s32 verticalResolution;
    s32 colorsUsed;
    s32 colorsImportant;
} BitmapInfo_00205210;

extern u8 D_002D07FA[];
extern u8 D_002D0806[];
extern s32 nSaveCount;

/* Debug: writes the frame buffer to a file on the host. */
void SzDebug_OutputFrameBuffer(void) {
    u8 buffer[0x780];
    BitmapInfo_00205210 info;
    BitmapFileHeader_00205210 fileHeader;
    s32 fd;
    u32 fileSize;
    extern s32 func_0019B648();

    while (SzFile_InqRequest(-1) != 0) {
        SzFile_DoRequestS();
    }
    RhBase_CopyFrameBuffer(0x04000000);
    fileHeader.type = 0x4D42;
    fileSize = 0x280 * 0x1C0 * 3 + 0x36;
    fileHeader.sizeLow = fileSize;
    fileHeader.sizeHigh = fileSize >> 16;
    fileHeader.reserved1 = 0;
    fileHeader.reserved2 = 0;
    fileHeader.offsetLow = 0x36;
    fileHeader.offsetHigh = 0;
    info.size = 0x28;
    info.width = 0x280;
    info.height = 0x1C0;
    info.planes = 1;
    info.bits = 0x18;
    info.compression = 0;
    info.imageSize = 0xD2000;
    info.horizontalResolution = 1;
    info.verticalResolution = 1;
    info.colorsUsed = 0;
    info.colorsImportant = 0;

    for (;;) {
        func_0019B648(buffer, D_002D0806,
                     SzFile_GetEnv((s32)D_002D07FA), nSaveCount);
        fd = func_0017FA98(buffer, 1);
        if (fd < 0) {
            break;
        }
        func_0017FD20(fd);
        nSaveCount += 1;
    }
    nSaveCount += 1;
    fd = func_0017FA98(buffer, 0x202);
    if (fd >= 0) {
        s32 y;
        u16 *row;

        func_00180348(fd, &fileHeader, 0xE);
        func_00180348(fd, &info, 0x28);
        y = 0x1BF;
        row = (u16 *)0x0408BB00;
        do {
            s32 x;
            u16 *src;
            u8 *dst;

            dst = buffer;
            x = 0;
            src = row;
            do {
                x += 1;
                dst[0] = ((*src >> 7) & 0xF8) | ((*src >> 12) & 7);
                dst[1] = ((*src >> 2) & 0xF8) | ((*src >> 7) & 7);
                dst[2] = ((*src << 3) & 0xF8) | ((*src >> 2) & 7);
                src++;
                dst += 3;
            } while (x < 0x280);
            func_00180348(fd, buffer, 0x780);
            y -= 1;
            row -= 0x280;
        } while (y >= 0);
        func_0017FD20(fd);
    }
}
