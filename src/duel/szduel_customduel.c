/* The duel screen, part 6 of 15: custom duel set-up menus. */

#include "common.h"
extern u8 duelIcons[]; /* original: gSzDuel_Icon */
extern s32 D_002908E6;
extern u8 D_002908F0[];

/* From the dotr-decomp CC0 bundle (commit 88c32bb2), chatC/imp/conv.py. */

struct DotrMiscLargeEntry {
    int unknown_words[16360];
};
struct DotrMiscLargeEntry *SzData_GetData_b(int value);
struct DotrMiscControlPair {
    unsigned short top;
    unsigned short count;
};
struct DotrMiscControlLists {
    unsigned char unknown_000[0x6d4];
    void *table;
    short *lists[2];
    unsigned char *counts[2];
    unsigned char unknown_6e8[0x5a2];
    struct DotrMiscControlPair pairs[2];
    short unknown_c92;
    short unknown_c94;
    short unknown_c96;
    short unknown_c98;
    unsigned char unknown_c9a[0x1c];
    unsigned char unknown_cb6[6];
    unsigned char unknown_cbc[2];
    unsigned char unknown_cbe[2];
    unsigned char modes[2];
    unsigned char unknown_cc2[0x9a];
    unsigned char side;         
    unsigned char unknown_d5d;
    unsigned char rows[2];
};
extern struct DotrMiscControlLists D_00317490_1c5d70;
struct DotrCustomDuelSide {
    unsigned char unknown_000[0x33a];
    unsigned short lp;
    unsigned char deck;
    unsigned char unknown_33d[5];
    unsigned char n;
    unsigned char unknown_343[0xd];
};
struct DotrCustomDuelControl {
    struct DotrCustomDuelSide side[2];
    unsigned char unknown_6a0[0x692];
    unsigned char a;
    unsigned char b;
};
struct DotrCustomDuel {
    unsigned char f0[2];
    unsigned char f2[2];
    unsigned char deck[2];
    unsigned char f6[2];
    unsigned char f8[2];
    unsigned char fa[2];
    unsigned char fc[2];
    unsigned char fe[2];
    unsigned short lp[2];
    unsigned short lp2[2];
    unsigned short list[56];
    unsigned char mode;
    unsigned char last;
    unsigned char count;
    unsigned char f8b;
    unsigned char f8c;
    unsigned char f8d;
};
#define DOTR_CUSTOM_DUEL ((struct DotrCustomDuel *)CUSTOM_DUEL_ADDR)
struct DotrCustomDuelFlags {
    unsigned char unknown_0000[0xff9c];
    unsigned int b0 : 5;
    unsigned int b5 : 1;
};
extern unsigned char *RhMem_CopyMemory_b(unsigned char *destination, unsigned char *source, int count);

/* Sets up the custom duel from its saved settings: decks, leaders and the message text. */
void func_001C5D70(int mode)
{
    struct DotrCustomDuelControl *c = (struct DotrCustomDuelControl *)&D_00317490_1c5d70;
    unsigned short *p = DOTR_CUSTOM_DUEL->list;
    int deck = 101;
    int i;
    struct DotrMiscLargeEntry *src;
    struct DotrMiscLargeEntry *dst;

    if (mode >= 0) {
        DOTR_CUSTOM_DUEL->mode = mode;
    }
    switch (DOTR_CUSTOM_DUEL->mode) {
    case 0:
        break;
    case 1:
        src = SzData_GetData_b(0);
        dst = SzData_GetData_b(1);
        RhMem_CopyMemory_b((unsigned char *)dst, (unsigned char *)src, 0xffa0);
        ((struct DotrCustomDuelFlags *)dst)->b5 = 0;
        deck = 22;
        break;
    case 2:
        SzData_SetupFromConstDeck(1, 50);
        deck = 25;
        break;
    case 3:
        SzData_SetupFromConstDeck(1, 49);
        deck = 24;
        break;
    case 4:
        SzData_SetupFromConstDeck(1, 48);
        deck = 23;
        break;
    }
    SzText_Free(0, 1);
    SzText_Free(0, 0);
    SzText_Free(1, -1);
    if (mode >= 0) {
        c->side[0].deck = 100;
        c->side[0].lp = 4000;
        c->side[0].n = 3;
        c->side[1].deck = deck;
        c->side[1].lp = 4000;
        c->side[1].n = 3;
        DOTR_CUSTOM_DUEL->f0[0] = 0;
        DOTR_CUSTOM_DUEL->f2[0] = 0;
        DOTR_CUSTOM_DUEL->deck[0] = SzData_GetCurrentDeck(0);
        DOTR_CUSTOM_DUEL->lp[0] = 4000;
        DOTR_CUSTOM_DUEL->lp2[0] = 4000;
        DOTR_CUSTOM_DUEL->f6[0] = 3;
        DOTR_CUSTOM_DUEL->f8[0] = 1;
        DOTR_CUSTOM_DUEL->fa[0] = 1;
        DOTR_CUSTOM_DUEL->fc[0] = 1;
        DOTR_CUSTOM_DUEL->fe[0] = 1;
        DOTR_CUSTOM_DUEL->f0[1] = 0;
        DOTR_CUSTOM_DUEL->f2[1] = 0;
        DOTR_CUSTOM_DUEL->deck[1] = SzData_GetCurrentDeck(1);
        DOTR_CUSTOM_DUEL->lp[1] = 4000;
        DOTR_CUSTOM_DUEL->lp2[1] = 4000;
        DOTR_CUSTOM_DUEL->f6[1] = 3;
        DOTR_CUSTOM_DUEL->f8[1] = 1;
        DOTR_CUSTOM_DUEL->fa[1] = 1;
        DOTR_CUSTOM_DUEL->fc[1] = 1;
        DOTR_CUSTOM_DUEL->fe[1] = 1;
        DOTR_CUSTOM_DUEL->f8c = 0;
        DOTR_CUSTOM_DUEL->f8d = 0;
        DOTR_CUSTOM_DUEL->count = 24;
        for (i = 0; i < 24; i++) {
            *p++ = i | 0x200;
        }
        if (SzData_GetMapEditFlag(0)) {
            DOTR_CUSTOM_DUEL->count += 5;
            for (i = 0; i < 5; i++) {
                *p++ = i;
            }
            DOTR_CUSTOM_DUEL->f8d = 5;
            DOTR_CUSTOM_DUEL->f8c = DOTR_CUSTOM_DUEL->f8d - 2;
        }
        if (SzData_GetMapEditFlag(1)) {
            DOTR_CUSTOM_DUEL->count += 5;
            for (i = 0; i < 5; i++) {
                *p++ = i | 0x100;
            }
        }
        DOTR_CUSTOM_DUEL->last = DOTR_CUSTOM_DUEL->count - 2;
        DOTR_CUSTOM_DUEL->f8b = 0;
    } else {
        c->side[0].deck = 100;
        c->side[0].lp = DOTR_CUSTOM_DUEL->lp2[0];
        c->side[1].deck = deck;
        c->side[1].lp = DOTR_CUSTOM_DUEL->lp2[1];
    }
    SzText_LoadMerge(4, 1);
    SzText_LoadMerge(7, 1);
    c->a = 0;
    c->b = 0;
}
#undef DOTR_CUSTOM_DUEL

/* Ends the custom duel setup (nothing to do). */
void SzDuel_TermCustomDuel(void) {

}

/* Runs the custom duel setup for side 0, then side 1 unless side 0 decided or both are ready. */
s32 SzDuel_ActCustomDuel(void) {
    s32 result = lSzDuel_ActCustomDuelProc(0);

    if (result != 0 || *(u8 *)(CUSTOM_DUEL_ADDR + 0x88) != 0) {
        return result;
    }
    return lSzDuel_ActCustomDuelProc(1);
}

/* From the dotr-decomp CC0 bundle (commit 88c32bb2), chatC/imp/conv.py. */

struct DotrCustomProcControlSide {
    unsigned char unknown_000[0x33c];
    unsigned char deck;                 
    unsigned char unknown_33d[0x13];
};
struct DotrCustomProcControl {
    struct DotrCustomProcControlSide side[2];
    unsigned char unknown_6a0[0x692];
    unsigned char reload[2];            
};
extern signed char D_00317490_b[];
struct DotrCustomProc {
    unsigned char cur[2];               
    unsigned char menu[2];              
    unsigned char deck[2];              
    unsigned char charge[2];            
    unsigned char f8[2];                
    unsigned char fa[2];                
    unsigned char fc[2];                
    unsigned char fe[2];                
    short lp[2];                        
    short lp2[2];                       
    unsigned short list[56];            
    unsigned char mode;                 
    unsigned char last;                 
    unsigned char count;                
    unsigned char f8b;                  
    unsigned char map;                  
    unsigned char maps;                 
    unsigned char yes;                  
};
struct DotrCustomProcAt {
    unsigned char pad[CUSTOM_DUEL_ADDR];
    unsigned char cur;
    unsigned char pad01;
    unsigned char menu;
    unsigned char pad03;
    unsigned char deck;
    unsigned char pad05;
    unsigned char charge;
    unsigned char pad07;
    unsigned char f8;
    unsigned char pad09;
    unsigned char fa;
    unsigned char pad0b;
    unsigned char fc;
    unsigned char pad0d;
    unsigned char fe;
    unsigned char pad0f;
    short lp;
    short pad12;
    short lp2;
};
#define DOTR_CUSTOM_PROC ((struct DotrCustomProc *)CUSTOM_DUEL_ADDR)
#define DOTR_CUSTOM_PROC_BYTES_AT(i) ((struct DotrCustomProcAt *)(i))
#define DOTR_CUSTOM_PROC_WORDS_AT(i) ((struct DotrCustomProcAt *)((i) * 2))
struct DotrCustomProcSave {
    unsigned char pad[0xfea3];
    unsigned char map[1][7][7];
};
extern unsigned char D_002BEAC0_1c6170[2][2][5];
extern void func_00215920_b(int side, int deck);
extern void func_002029B0_b(int a, int b);
extern int func_001DE690_b(int index);
extern void func_001DE6B0_b(int index, int value);
extern int func_001E2220_b(int x, int y, int value);
#define MENU(i) (DOTR_CUSTOM_PROC_BYTES_AT(i)->menu)
#define LP(i) (DOTR_CUSTOM_PROC_WORDS_AT(i)->lp)
#define LP2(i) (DOTR_CUSTOM_PROC_WORDS_AT(i)->lp2)
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define CLAMP(v, lo, hi) MIN(MAX(v, lo), hi)
/* Whether deck `list` of `side` has 40 cards and a leader. */
static inline int DotrCustomProcIsDeckReady(int side, int list)
{
    int count = SzData_GetDeckCount(side, list);
    int value = SzData_GetLeader(side, list);

    if (count >= 40) {
        if (value == 999) {
            if (!list && !count) {
            }
        } else {
            return 1;
        }
    }
    return 0;
}

/* Runs side `side`'s custom duel menus: deck, life points, summon charge, leader ability, card display, map. */
int lSzDuel_ActCustomDuelProc(int side)
{
    struct DotrCustomProcControl *c = (struct DotrCustomProcControl *)D_00317490_b;
    int deck = SzData_GetCurrentDeck(side);
    unsigned char *reload = side ? &c->reload[1] : &c->reload[0];
    

    struct DotrCustomProcAt *w = (struct DotrCustomProcAt *)side;

    int m;
    int old;
    int x;
    int y;
    int v;
    int row;

    if (SzFile_InqRequestEx() == 0 && *reload) {
        SzText_LoadMerge(side + 5, 1);
        *reload = 0;
        if (DOTR_CUSTOM_PROC->mode == 1) {
            SzText_LoadMerge(6, 1);
        }
    }
    

    m = w->menu;
    if (m & 0xf0) {
    switch (m & 0xf0) {
    case 0x10:
        switch (m & 0xf) {
        case 0:
            if (SzPad_Check(side, 2, 0xa000) || SzPad_Check(side, 2, 12)) {
                if (SzPad_Check(side, 2, 0x8004)) {
                    w->deck = (w->deck + 2) % 3;
                } else {
                    w->deck = (w->deck + 4) % 3;
                }
                SzSound_PlaySE(0, 3);
            } else if (SzPad_Check(side, 0, 192)) {
                if (DotrCustomProcIsDeckReady(side, w->deck)) {
                    if (deck != w->deck) {
                        SzSound_PlaySE(0, 4);
                        func_00215920_b(side, w->deck);
                        func_002029B0_b(2, side);
                        *reload = 1;
                        if (DOTR_CUSTOM_PROC->mode == 1) {
                            func_00215920_b(1, w->deck);
                            func_002029B0_b(2, 1);
                        }
                    }
                } else {
                    SzSound_PlaySE(0, 6);
                }
            } else if (SzPad_Check(side, 0, 32)) {
                SzSound_PlaySE(0, 5);
                w->menu &= 0xf;
            }
            break;
        case 1:
            if (SzPad_Check(side, 2, 0xa000) || SzPad_Check(side, 2, 12)) {
                short *p = &LP(side);

                old = *p;
                if (SzPad_Check(side, 2, 0x8004)) {
                    *p = ((*p + 50) / 100 - 1) * 100;
                } else {
                    *p = ((*p + 50) / 100 + 1) * 100;
                }
                *p = CLAMP(*p, 1, 9999);
                if (*p == old) {
                    SzSound_PlaySE(0, 6);
                } else {
                    SzSound_PlaySE(0, 3);
                }
            } else if (SzPad_Check(side, 0, 192)) {
                short *p = &LP(side);

                if (*p != SzDuel_GetLP(side)) {
                    SzSound_PlaySE(0, 4);
                    SzDuel_CalcLP(side, 4, *p);
                    LP2(side) = *p;
                    if (DOTR_CUSTOM_PROC->mode) {
                        

                        v = MAX(*p, 4000);
                        side ^= 1;
                        SzDuel_CalcLP(side, 4, v);
                        LP2(side) = MAX(*p, 4000);
                    }
                }
            } else if (SzPad_Check(side, 0, 32)) {
                SzSound_PlaySE(0, 5);
                w->menu &= 0xf;
            }
            break;
        case 2:
            if (SzPad_Check(side, 2, 0xa000) || SzPad_Check(side, 2, 12)) {
                old = w->charge;
                if (SzPad_Check(side, 2, 0x8004)) {
                    w->charge = MAX(w->charge - 1, 1);
                } else {
                    w->charge = MIN(w->charge + 1, 12);
                }
                if (w->charge == old) {
                    SzSound_PlaySE(0, 6);
                } else {
                    SzSound_PlaySE(0, 3);
                }
            } else if (SzPad_Check(side, 0, 192)) {
                if (w->charge != func_001DE690_b(side)) {
                    SzSound_PlaySE(0, 4);
                    func_001DE6B0_b(side, w->charge);
                    if (DOTR_CUSTOM_PROC->mode) {
                        func_001DE6B0_b(side ^ 1, (unsigned char)MAX(w->charge, 3));
                    }
                }
            } else if (SzPad_Check(side, 0, 32)) {
                SzSound_PlaySE(0, 5);
                w->menu &= 0xf;
            }
            break;
        case 3:
            if (SzPad_Check(side, 2, 0xa000)) {
                old = w->f8;
                if (SzPad_Check(side, 2, 0x8000)) {
                    w->f8 = 0;
                } else {
                    w->f8 = 1;
                }
                if (w->f8 != old) {
                    SzSound_PlaySE(0, 3);
                }
            } else if (SzPad_Check(side, 0, 192)) {
                if (w->f8 != w->fa) {
                    SzSound_PlaySE(0, 4);
                    w->fa = w->f8;
                }
            } else if (SzPad_Check(side, 0, 32)) {
                SzSound_PlaySE(0, 5);
                w->menu &= 0xf;
            }
            break;
        case 4:
            if (SzPad_Check(side, 2, 0xa000)) {
                old = w->fc;
                if (SzPad_Check(side, 2, 0x8000)) {
                    w->fc = 0;
                } else {
                    w->fc = 1;
                }
                if (w->fc != old) {
                    SzSound_PlaySE(0, 3);
                }
            } else if (SzPad_Check(side, 0, 192)) {
                if (w->fc != w->fe) {
                    SzSound_PlaySE(0, 4);
                    w->fe = w->fc;
                }
            } else if (SzPad_Check(side, 0, 32)) {
                SzSound_PlaySE(0, 5);
                w->menu &= 0xf;
            }
            break;
        case 5:
            w->menu &= 0xf;
            break;
        case 6:
            if (SzGame_ActMemCardProc() < 0) {
                w->menu &= 0xf;
            }
            break;
        case 7:
            if (SzPad_Check(side, 2, 0x5000)) {
                if (SzPad_Check(side, 2, 0x1000)) {
                    DOTR_CUSTOM_PROC->map = (DOTR_CUSTOM_PROC->map + DOTR_CUSTOM_PROC->maps - 1) % DOTR_CUSTOM_PROC->maps;
                } else {
                    DOTR_CUSTOM_PROC->map = (DOTR_CUSTOM_PROC->map + DOTR_CUSTOM_PROC->maps + 1) % DOTR_CUSTOM_PROC->maps;
                }
                SzSound_PlaySE(0, 3);
            } else if (SzPad_Check(side, 0, 192)) {
                struct DotrCustomProcSave *d = SzData_GetData(side);
                int n = (DOTR_CUSTOM_PROC->map + 2) % DOTR_CUSTOM_PROC->maps;

                for (y = 0; y < 7; y++) {
                    for (x = 0; x < 7; x++) {
                        func_001E2220_b(x, y, d->map[n][y][x]);
                    }
                }
                SzSound_PlaySE(0, 4);
                SzGame_SetMenuNum(13, 0);
                SzGame_Push(13, 2);
            } else if (SzPad_Check(side, 0, 32)) {
                SzSound_PlaySE(0, 5);
                w->menu &= 0xf;
            }
            break;
        }
        break;
    case 0x20:
        if (SzPad_Check(side, 0, 32)) {
            SzSound_PlaySE(0, 5);
            w->menu &= 0xf;
        }
        break;
    case 0x30:
        if (SzPad_Check(side, 0, 0xa000)) {
            old = DOTR_CUSTOM_PROC->yes;
            if (SzPad_Check(side, 0, 0x8000)) {
                DOTR_CUSTOM_PROC->yes = 1;
            } else {
                DOTR_CUSTOM_PROC->yes = 0;
            }
            if (DOTR_CUSTOM_PROC->yes != old) {
                SzSound_PlaySE(0, 3);
            }
        } else if (SzPad_Check(side, 0, 192)) {
            SzSound_PlaySE(0, 4);
            if (DOTR_CUSTOM_PROC->yes) {
                SzGame_Pop();
            } else {
                DOTR_CUSTOM_PROC->menu[0] &= 0xf;
                DOTR_CUSTOM_PROC->menu[1] &= 0xf;
            }
        } else if (SzPad_Check(side, 0, 32)) {
            SzSound_PlaySE(0, 5);
            DOTR_CUSTOM_PROC->menu[0] &= 0xf;
            DOTR_CUSTOM_PROC->menu[1] &= 0xf;
        }
        break;
    case 0x40:
        if (SzPad_Check(side, 2, 12)) {
            if (SzPad_Check(side, 2, 4)) {
                DOTR_CUSTOM_PROC->last = (DOTR_CUSTOM_PROC->last + DOTR_CUSTOM_PROC->count - 5) % DOTR_CUSTOM_PROC->count;
            } else {
                DOTR_CUSTOM_PROC->last = (DOTR_CUSTOM_PROC->last + DOTR_CUSTOM_PROC->count + 5) % DOTR_CUSTOM_PROC->count;
            }
            SzSound_PlaySE(0, 3);
        } else if (SzPad_Check(side, 2, 0x5000)) {
            if (SzPad_Check(side, 2, 0x1000)) {
                DOTR_CUSTOM_PROC->last = (DOTR_CUSTOM_PROC->last + DOTR_CUSTOM_PROC->count - 1) % DOTR_CUSTOM_PROC->count;
            } else {
                DOTR_CUSTOM_PROC->last = (DOTR_CUSTOM_PROC->last + DOTR_CUSTOM_PROC->count + 1) % DOTR_CUSTOM_PROC->count;
            }
            SzSound_PlaySE(0, 3);
        } else if (SzPad_Check(side, 0, 192)) {
            
            v = DOTR_CUSTOM_PROC->list[(DOTR_CUSTOM_PROC->last + 2) % DOTR_CUSTOM_PROC->count];
            row = v >> 8;
            v = v & 0xff;
            if (row < 2) {
                v += row * 5 + 46;
            } else {
                v += 22;
            }
            SzGame_SetMenuNum(2, 0);
            SzGame_SetMenuNum(1, v);
            SzGame_SetMenuNum(3, c->side[0].deck + 1000);
            SzGame_SetMenuNum(4, c->side[1].deck + 1000);
            SzGame_SetMenuNum(28, (DOTR_CUSTOM_PROC->f8[0] ? 1 : 0) | (DOTR_CUSTOM_PROC->f8[1] ? 2 : 0));
            SzGame_SetMenuNum(29, (DOTR_CUSTOM_PROC->fc[0] ? 1 : 0) | (DOTR_CUSTOM_PROC->fc[1] ? 2 : 0));
            SzGame_Push(1, 1);
            SzSound_PlaySE(0, 4);
            return 1;
        } else if (SzPad_Check(side, 0, 32)) {
            SzSound_PlaySE(0, 5);
            DOTR_CUSTOM_PROC->menu[0] &= 0xf;
            DOTR_CUSTOM_PROC->menu[1] &= 0xf;
            if (DOTR_CUSTOM_PROC->mode == 0) {
                MENU(side ^ 1) |= 0x20;
            }
        }
        break;
    }
    return 0;
    }
    switch (m) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            if (SzPad_Check(side, 2, 0xf000)) {
                
                int row;
                int col;
                unsigned char (*t)[5];

                row = w->cur / 5;
                col = w->cur % 5;
                t = D_002BEAC0_1c6170[DOTR_CUSTOM_PROC->mode ? 1 : 0];
                do {
                    if (SzPad_Check(side, 2, 0x1000)) {
                        col = (col + 4) % 5;
                    } else if (SzPad_Check(side, 2, 0x4000)) {
                        col = (col + 6) % 5;
                    } else if (SzPad_Check(side, 2, 0x8000)) {
                        row = (row + 1) % 2;
                    } else if (SzPad_Check(side, 2, 0x2000)) {
                        row = (row + 3) % 2;
                    }
                    v = t[row][col];
                } while (v == 255 || (v == 7 && !SzData_GetMapEditFlag(side)));
                if (w->menu != v) {
                    w->cur = col + row * 5;
                    w->menu = v;
                    SzSound_PlaySE(0, 3);
                }
            } else if (SzPad_Check(side, 0, 2048)) {
                unsigned char *q = &MENU(side ^ 1);

                if ((*q & 0xf0) == 0x20) {
                    SzSound_PlaySE(0, 4);
                    *q &= 0xf;
                    DOTR_CUSTOM_PROC->menu[0] |= 0x40;
                    DOTR_CUSTOM_PROC->menu[1] |= 0x40;
                } else {
                    SzSound_PlaySE(0, 4);
                    if (DOTR_CUSTOM_PROC->mode) {
                        DOTR_CUSTOM_PROC->menu[0] |= 0x40;
                        DOTR_CUSTOM_PROC->menu[1] |= 0x40;
                    } else {
                        w->menu |= 0x20;
                    }
                }
            } else if (SzPad_Check(side, 0, 192)) {
                SzSound_PlaySE(0, 4);
                switch (w->menu) {
                case 5:
                    SzGame_SetMenuNum(6, 0);
                    SzGame_Push(6, 1);
                    break;
                case 6:
                    SzGame_InitMemCardProc(1);
                    break;
                }
                w->menu |= 0x10;
            } else if (SzPad_Check(side, 0, 32)) {
                if (MENU(side ^ 1) < 8) {
                    SzSound_PlaySE(0, 5);
                    DOTR_CUSTOM_PROC->menu[0] |= 0x30;
                    DOTR_CUSTOM_PROC->menu[1] |= 0x30;
                    DOTR_CUSTOM_PROC->yes = 0;
                } else {
                    SzSound_PlaySE(0, 6);
                }
            }
            break;
        }
    return 0;
}
#undef DOTR_CUSTOM_PROC
#undef DOTR_CUSTOM_PROC_BYTES_AT
#undef DOTR_CUSTOM_PROC_WORDS_AT
#undef MENU
#undef LP
#undef LP2
#undef MAX
#undef MIN
#undef CLAMP

/* Draws the custom duel setup screen. */
void SzDuel_DrawCustomDuel(void) {
    RhBase_SetVifPacketArea(SzDuel_DrawCustomDuel_Pipe(RhBase_GetVifPacketArea()));
}
#pragma opt_propagation off
#pragma opt_lifetimes off

/* Draws the custom duel setup screen: background, title, both sides' info and menus, the fade. */
s32 SzDuel_DrawCustomDuel_Pipe(s32 packet) {
    extern char D_002BF03A[];
    extern s32 lSzDuel_DrawCustomDuel_Title_Pipe();
    extern s32 lSzDuel_DrawCustomDuel_PlayerInfo_Pipe();
    extern s32 lSzDuel_DrawCustomDuel_Menu_Pipe();
    extern s32 lSzDuel_DrawCustomDuel_Menu_SelectMap_Pipe();
    extern s32 lSzDuel_DrawCustomDuel_Exit_Pipe();
    extern s32 lSzDuel_DrawWindow_Frame_Pipe();
    extern s32 SzDuel_DrawWindow_Font_Pipe();
    extern s32 lSzDuel_Draw_Fade_Pipe();
    s8 *text;
    s32 id;
    s32 textY;
    s32 height;
    s32 width;
    s32 height2;
    s32 width2;
    s32 mode;
    s32 fy;

    id = lSzDuel_DrawCustomDuel_PlayerInfo_Pipe(lSzDuel_DrawCustomDuel_PlayerInfo_Pipe(lSzDuel_DrawCustomDuel_Title_Pipe(lSzDuel_DrawCustomDuel_Base_Pipe(SzDuel_StartWindowSessionWithPalette_Pipe(packet, 2)), 0, 0), 0, 0x10, 0x40), 1, 0x140, 0x40);
    mode = *(u8 *)(CUSTOM_DUEL_ADDR + 0x2) & 0xF0;
    if (mode == 0x40 || (*(u8 *)(CUSTOM_DUEL_ADDR + 0x3) & 0xF0) == 0x40) {
        id = lSzDuel_DrawCustomDuel_Menu_SelectMap_Pipe(id, 0, 0x1E, 0xE0);
    } else {
        if (mode == 0x20) {
            text = D_002BF03A;
            lSzDuel_GetFontSize(2, 3, strlen(text), text, &width, &height);
            width += 0x18;
            height += 0xC;
            fy = 0x144 - height / 2;
            id = lSzDuel_DrawWindow_Frame_Pipe(id, 0xC, -1, 0xB, 0xA0 - width / 2, fy, -width, -height, 1);
            textY = 0x14C - height / 2;
            id = SzDuel_DrawWindow_Font_Pipe(id, 0xA0, textY, 2, 3, strlen(text), text, 0);
        } else {
            id = lSzDuel_DrawCustomDuel_Menu_Pipe(id, 0, 0x10, 0xE6);
        }
        if (*(u8 *)(CUSTOM_DUEL_ADDR + 0x88) == 0) {
            if ((*(u8 *)(CUSTOM_DUEL_ADDR + 0x3) & 0xF0) == 0x20) {
                text = D_002BF03A;
                lSzDuel_GetFontSize(2, 3, strlen(text), text, &width2, &height2);
                width2 += 0x18;
                height2 += 0xC;
                fy = 0x144 - height2 / 2;
                id = lSzDuel_DrawWindow_Frame_Pipe(id, 0xC, -1, 0xB, 0x1E0 - width2 / 2, fy, -width2, -height2, 1);
                textY = 0x14C - height2 / 2;
                id = SzDuel_DrawWindow_Font_Pipe(id, 0x1E0, textY, 2, 3, strlen(text), text, 0);
            } else {
                id = lSzDuel_DrawCustomDuel_Menu_Pipe(id, 1, 0x140, 0xE6);
            }
        }
    }
    if ((*(u8 *)(CUSTOM_DUEL_ADDR + 0x2) & 0xF0) == 0x30 || (*(u8 *)(CUSTOM_DUEL_ADDR + 0x3) & 0xF0) == 0x30) {
        id = lSzDuel_DrawCustomDuel_Exit_Pipe(lSzDuel_Draw_Fade_Pipe(id, 0, 0, 0x280, 0x1C0, 0x40), 0, 0);
    }
    SzMsg_Free(0);
    return id;
}

typedef struct {
    u16 count;
    u16 flags;
    u32 padding;
    u64 registers;
} Tag_001C7790;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Color_001C7790;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Vertex_001C7790;

typedef struct {
    Color_001C7790 color;
    Vertex_001C7790 xyz;
} Point_001C7790;

typedef struct {
    u64 tag[2];
    Point_001C7790 points[4];
    u64 end;
} Packet_001C7790;

typedef struct {
    u8 b, g, r, a;
} Source_001C7790;

/* Sets two vertex colours from `src`. */
static inline void set_color_001C7790(Color_001C7790 *a, Color_001C7790 *b,
                                      Source_001C7790 *src) {
    a->r = b->r = src->r;
    a->g = b->g = src->g;
    a->b = b->b = src->b;
    a->a = b->a = src->a;
    a->q = b->q = 1.0f;
}

/* Sets a screen vertex at (x, y) at the windows' depth. */
static inline void set_xyz_001C7790(Vertex_001C7790 *v, s32 x, s32 y) {
    v->x = (x + 0x6C0) << 4;
    v->y = (y + 0x720) << 4;
    v->z = duelState.s.depth;
    v->fog = 0;
}
#pragma opt_lifetimes reset
#pragma opt_propagation reset

/* Draws the custom duel screen's background gradient. */
s32 lSzDuel_DrawCustomDuel_Base_Pipe(s32 out) {
    extern u8 D_002BE860[];
    Source_001C7790 *colors = (Source_001C7790 *)D_002BE860;
    s32 width = 0x140;
    s32 height = 0x1C0;
    Packet_001C7790 packet __attribute__((aligned(8)));

    ((Tag_001C7790 *)packet.tag)->flags = 0x14;
    ((Tag_001C7790 *)packet.tag)->count = 8;
    ((Tag_001C7790 *)packet.tag)->registers = 0x41414141;
    ((Tag_001C7790 *)packet.tag)->padding = 0;
    set_color_001C7790(&packet.points[0].color, &packet.points[2].color, &colors[0]);
    set_color_001C7790(&packet.points[1].color, &packet.points[3].color, &colors[1]);
    set_xyz_001C7790(&packet.points[0].xyz, 0, 0);
    set_xyz_001C7790(&packet.points[1].xyz, width, 0);
    set_xyz_001C7790(&packet.points[2].xyz, 0, height);
    set_xyz_001C7790(&packet.points[3].xyz, width, height);
    out = ExSortPrim_Pipe(out, (s32)packet.tag, 0, 0);
    set_color_001C7790(&packet.points[0].color, &packet.points[2].color, &colors[1]);
    set_color_001C7790(&packet.points[1].color, &packet.points[3].color, &colors[0]);
    set_xyz_001C7790(&packet.points[0].xyz, width, 0);
    set_xyz_001C7790(&packet.points[1].xyz, width * 2, 0);
    set_xyz_001C7790(&packet.points[2].xyz, width, height);
    set_xyz_001C7790(&packet.points[3].xyz, width * 2, height);
    return ExSortPrim_Pipe(out, (s32)packet.tag, 0, 0);
}

/* Draws the custom duel screen's title bar. */
void lSzDuel_DrawCustomDuel_Title_Pipe(s32 packet, s32 left, s32 top) {
    extern char D_002BF047[];
    extern char D_002BF04E[];
    extern s32 SzDuel_DrawWindow_Font_Pipe(s32, s32, s32, s32, s32, s32, s8 *, s32);
    s32 text = (s32)D_002BF047;
    s32 text2 = (s32)D_002BF04E;
    s32 hint = 0;
    s32 x = left + 0xE0;
    s32 y = top + 0x20;
    s32 tx;
    s32 ty;
    s32 element;

    packet = lSzDuel_DrawWindow_Base_Pipe(packet, x, y, 6, 1);
    element = lSzDuel_DrawWindow_Frame_Pipe(packet, -1, 0x73, 4, x, y, 0x15, 2, 1);
    tx = left + 0x140;
    ty = top + 0x27;
    element = SzDuel_DrawWindow_Font_Pipe(element, tx, ty, 2, 3, func_0019BEF0((const char *)text), (s8 *)text,
                            hint != 0 ? (s32)D_002BE944 : 0);
    SzDuel_DrawWindow_Font_Pipe(element, left + 0x140, top + 0x46, 2, 3, func_0019BEF0((const char *)text2),
                  (s8 *)text2, hint != 0 ? (s32)D_002BE944 : 0);
}
extern s32 D_00290A1C;
extern char D_002BF051[];
extern char D_002BF056[];
extern u8 D_0029099A[];

typedef struct TextInfo_001C7D20 {
    u8 pad[12];
    s32 width;
} TextInfo_001C7D20;

/* The scale that fits text `index` into `limit` pixels. */
static inline f32 scale_001C7D20(s32 index, s32 limit) {
    extern void *func_001FEAB0();
    s32 width = ((TextInfo_001C7D20 *)func_001FEAB0(index))->width;
    if (width > limit) {
        return (f32)limit / (f32)width;
    }
    return 1.0f;
}

/* Whether a text is wider than 200 pixels. */
static inline s32 wide_001C7D20(TextInfo_001C7D20 *text) {
    return text->width > 200;
}

/* Draws side `side`'s info panel at (left, top): leader portrait and card, deck, life points, summon charge. */
s32 lSzDuel_DrawCustomDuel_PlayerInfo_Pipe(s32 packet, s32 side, s32 left, s32 top) {
    extern s32 func_001B3CC0(s32, void *, s32, s32, s32, s32, s32, s32, s64, s64, s64, s64, s64, s64);
    extern s32 func_001B4540(s32, s32, s32, s32, s32, s32);
    extern s32 func_001B65F0(s32, s32, s32, s32, s32, s32, s32, s32);
    extern s32 func_001B6EA0(s32, s32, s32, s32, s32, s32, s32);
    extern s32 func_001B6F70(s32, s32, s32, s32, s32, s32, s8 *, s32);
    extern s32 func_001DE690();
    extern s32 func_00215D30();
    extern void *func_001FEAB0();
    extern s32 func_001FE660(s32, s32, s32, s32, f32, f32, s32, void (*)(void));
    s32 ret;
    s32 nx;
    s32 ny;
    s32 tx;
    s32 px;
    s32 py;
    s32 ty;
    u8 *spD0;
    s32 spEC;
    s32 frame_x;
    s32 temp_v0;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_s0_3;
    s32 temp_s0_4;
    s32 temp_s0_5;
    s32 temp_s0_6;
    s32 temp_s0_7;
    s32 image_x;
    s32 temp_v0_2;
    s32 temp_s1;
    s32 image_y;
    s32 temp_s2;
    s32 temp_s2_2;
    s32 first_x;
    s32 first_y;
    s32 var_s3;
    s8 *var_s7;
    u8 *temp_fp;
    s32 temp_fp_2;
    s32 var_a2;
    TextInfo_001C7D20 *first_text;
    f32 first_scale;
    s32 hint = 0;
    s32 number_x;
    s32 number_y;

    spD0 = duelState.b;
    temp_v0 = func_002158B0(side);
    temp_v0_2 = func_002159D0(side, temp_v0);
    temp_fp = func_001DD0E0(temp_v0_2);
    if (*((u8 *)side + (CUSTOM_DUEL_ADDR + 0xE)) != 0) {
        var_s7 = (s8 *)D_002BF051;
    } else {
        var_s7 = (s8 *)D_002BF056;
    }
    var_a2 = 3;
    if (side != 0) {
        u8 mode = *(u8 *)(CUSTOM_DUEL_ADDR + 0x88);
        switch (mode) {
        case 0:
            var_a2 = 4;
            break;
        default:
            var_a2 = mode + 0x8C;
            break;
        }
    }
    packet = func_001FD680(packet, 1, var_a2, 0, 0x16);
    temp_s1 = func_0020F290(packet);
    tx = left + 0x6C0 + ((side != 0) ? 0x110 : 0);
    temp_s1 = func_001B3CC0(temp_s1, duelIcons + ((side + 0xF3) * 10), tx, top + 0x720, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    frame_x = left + 0x20;
    (void)frame_x; /* keeps the x add at its own statement: the original computes it before side + 5 */
    spEC = func_001B4780(temp_s1, side, side + 5, 0xB, frame_x, top, -0xF0, -0x20, 1);
    first_x = left + 0x40;
    first_y = top + 5;
    first_text = (TextInfo_001C7D20 *)func_001FEAB0(1);
    if (wide_001C7D20(first_text)) {
        first_scale = 200.0f / (f32)first_text->width;
    } else {
        first_scale = 1.0f;
    }
    temp_s2 = func_001FE660(spEC, 1, first_x, first_y, first_scale, 1.0f, 0, SzMsg_DrawRect_Pipe);
    func_001FEAF0(1);
    var_s3 = func_001B65F0(func_001B4780(temp_s2, side, -1, 4, left, top + 0x20, -0x130, -0x80, 1), side, left + 0xD, top + 0x25, -0x116, -0x5E, -1, 0);
    if (temp_fp != NULL) {
        temp_s2_2 = *temp_fp & 0x1F;
        temp_s1 = func_001DE210(temp_v0_2);
        temp_fp_2 = func_00215D30(side, temp_v0_2);
        var_s3 = func_001B3CC0(func_001B3CC0(func_001B3CC0(func_001B4780(func_0020F290(func_001FD680(func_001FD680(func_001FD680(var_s3, 1, temp_s1, 0, 0x16), 2, temp_s2_2 + 0x25, 0, 0x2C), 3, temp_fp_2 + 0x52, 0, 0x42)), 0xC, -1, 0xB, left + 0x11, top + 0x29, -0x6E, -0x56, 1), D_0029099A, left + 0x6D9, top + 0x751, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80), duelIcons + ((temp_v0 + 0xE3) * 10), left + 0x6E4, top + 0x764, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80), D_002908F0, left + 0x6E0, top + 0x784, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
        number_x = left + 0x35;
        number_y = top + 0x65;
        var_s3 = func_001B6EA0(var_s3, number_x, number_y, 0, hint != 0 ? 1 : 0, 4, func_00215F00(side, temp_v0));
        image_x = left + 0x4A;
        image_y = top + 0x2E;
        temp_s0 = func_001B4780(func_001B7F90(var_s3, side, image_x, image_y, 0x30, 0x30, *(s32 *)(spD0 + 0xC58), 1), -1, -1, 4, image_x, image_y, 3, 6, 1);
        temp_s0_2 = func_001FE660(temp_s0, 1, left + 0x81, top + 0x2B, scale_001C7D20(1, 156), 1.0f, 0, SzMsg_DrawRect_Pipe);
        func_001FEAF0(1);
        px = left + 0x741;
        py = top + 0x767;
        temp_s0_3 = func_001B3CC0(temp_s0_2, duelIcons + (temp_s2_2 * 10), px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
        var_s3 = func_001FE660(temp_s0_3, 2, left + 0x9B, top + 0x47, scale_001C7D20(2, 138), 1.0f, 0, SzMsg_DrawRect_Pipe);
        func_001FEAF0(2);
        if (*(u8 *)(CUSTOM_DUEL_ADDR + 0x88) != 0 || *((u8 *)side + (CUSTOM_DUEL_ADDR + 0xA)) != 0) {
            temp_s0_4 = func_001B4540(var_s3, left + 0x81, top + 0x65, temp_fp_2, 1, 0);
            var_s3 = func_001FE660(temp_s0_4, 3, left + 0x9B, top + 0x65, scale_001C7D20(3, 138), 1.0f, 0, SzMsg_DrawRect_Pipe);
        }
        func_001FEAF0(3);
    }
    ret = func_001B3CC0(func_001B4780(var_s3, 0xC, -1, 5, left + 0x14, top + 0x86, -0x70, -0x14, 1), &D_00290A1C, left + 0x6D6, top + 0x7A8, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    nx = left + 0x3E;
    ny = top + 0x8A;
    ret = func_001B3CC0(func_001B4780(func_001B6EA0(ret, nx, ny, 0, hint != 0 ? 1 : 0, 4, func_001DF470(side)), 0xC, -1, 5, left + 0x94, top + 0x86, -0x3C, -0x14, 1), &D_002908E6, left + 0x756, top + 0x7A8, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    nx = left + 0xAC;
    ny = top + 0x8A;
    ret = func_001B6EA0(ret, nx, ny, 0, hint != 0 ? 1 : 0, 2, func_001DE690(side));
    if (*(u8 *)(CUSTOM_DUEL_ADDR + 0x88) == 0) {
        nx = left + 0x100;
        ny = top + 0x8A;
        ret = func_001B6F70(ret, nx, ny, 0, 2, func_0019BEF0((const char *)var_s7), var_s7, hint != 0 ? (s32)D_002BE944 : 0);
    }
    return ret;
}

/* Draws side `side`'s open custom-duel menu at (left, top). */
s32 lSzDuel_DrawCustomDuel_Menu_Pipe(s32 packet, u8 *side, s32 left, s32 top) {
    extern s32 lSzDuel_DrawCustomDuel_Menu_SelectMapEdit_Pipe(s32, u8 *, s32, s32);
    u8 kind;

    kind = side[CUSTOM_DUEL_ADDR + 0x2];
    if ((kind & 0xF0) == 0x10) {
        switch (kind & 0xF) {
        case 0:
            packet = lSzDuel_DrawCustomDuel_Menu_SelectDeck_Pipe(packet, side, left + 0xE, top + 0xB);
            break;
        case 1:
            packet = lSzDuel_DrawCustomDuel_Menu_LifeSet_Pipe(packet, (s32)side, left + 0xE, top + 0xB);
            break;
        case 2:
            packet = lSzDuel_DrawCustomDuel_Menu_SummonCharge_Pipe(packet, side, left + 0xE, top + 0xB);
            break;
        case 3:
            packet = lSzDuel_DrawCustomDuel_Menu_LeaderAbility_Pipe(packet, side, left + 0xE, top + 0xB);
            break;
        case 4:
            packet = lSzDuel_DrawCustomDuel_Menu_CardDisp_Pipe(packet, side, left + 0xE, top + 0xB);
            break;
        case 5:
        case 6:
            packet = lSzDuel_DrawCustomDuel_Menu_Top_Pipe(packet, side, left, top);
            break;
        case 7:
            packet = lSzDuel_DrawCustomDuel_Menu_SelectMapEdit_Pipe(packet, side, left + 0xE, top - 6);
            break;
        }
    } else {
        packet = lSzDuel_DrawCustomDuel_Menu_Top_Pipe(packet, side, left, top);
    }
    return packet;
}

/* Draws the custom duel's top menu (its eight items) for `side`. */
s32 lSzDuel_DrawCustomDuel_Menu_Top_Pipe(s32 packet, u8 *side, s32 x, s32 y) {
    extern s32 *SzMsg_GetInfo(s32);
    extern s32 SzMsg_DrawRatioX_Pipe(s32, s32, s32, s32, f32, f32, s32, void (*)(void));
    extern s32 SzDuel_DrawWindow_Font_Pipe(s32, s32, s32, s32, s32, s32, s8 *, s32);
    extern s32 lSzDuel_DrawWindow_ExBoard_Pipe(s32, s32, s32, s32, s32, s32, s32, s32);
    extern s32 lSzDuel_DrawWindow_ExIcon_Pipe(s32, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
    extern s32 lSzDuel_DrawWindow_Frame_Pipe();
    extern u8 D_002BEAC0[2][10];
    extern char D_002BF05B[];
    extern char D_002BF03A[];
    extern s32 D_00290A58;
    extern s32 D_00290A62;
    extern s32 D_00290A6C;
    extern s32 D_00290A76;
    u8 *cursor = (u8 *)CUSTOM_DUEL_ADDR;
    s8 *text1 = D_002BF05B;
    s8 *text2 = D_002BEF98;
    s8 *text3 = D_002BF03A;
    s32 row;
    s32 enabled;
    s32 width = 0x25A;
    u8 *list;
    s32 hint = 0;
    s32 col;
    s32 item;
    s32 sel;
    s32 w;
    s32 *info;
    f32 scale;
    s32 px;
    s32 py;

    width = (*(u8 *)(CUSTOM_DUEL_ADDR + 0x88) != 0) ? width : 0x12A;
    list = D_002BEAC0[(*(u8 *)(CUSTOM_DUEL_ADDR + 0x88) != 0) ? 1 : 0];
    packet = SzMsg_LoadFont_Pipe(packet, 1, 0x81, 0, 0x16);
    packet = SzMsg_LoadFont_Pipe(packet, 2, 0x82, 0, 0x2C);
    packet = SzMsg_LoadFont_Pipe(packet, 3, 0x83, 0, 0x42);
    packet = SzMsg_LoadFont_Pipe(packet, 4, 0x84, 0, 0x58);
    packet = SzMsg_LoadFont_Pipe(packet, 5, 0x85, 0, 0x6E);
    packet = SzMsg_LoadFont_Pipe(packet, 6, 0x86, 0, 0x84);
    packet = SzMsg_LoadFont_Pipe(packet, 7, 0x87, 0, 0x9A);
    packet = SzMsg_LoadFont_Pipe(packet, 8, 0x88, 0, 0xB0);
    packet = lSzDuel_DrawWindow_Frame_Pipe(RhText_SetTextureFlush(packet), (s32)side, (s32)side, 0, x, y, -(width - 0x14), -0xAE, 1);
    for (row = 0; row < 2; row++) {
        for (col = 0; col < 5; col++) {
            item = list[row * 5 + col];
            enabled = 1;
            if (item == 0xFF) {
                continue;
            }
            if (item == 7) {
                if (SzData_GetMapEditFlag((s32)side) == 0) {
                    enabled = 0;
                }
            }
            if (enabled) {
                info = SzMsg_GetInfo(item + 1);
                if (cursor[0x88]) {
                    w = info[3];
                    scale = 1.0f;
                    if (w > 0xAC) {
                        scale = 172.0f / (f32)w;
                    }
                    packet = SzMsg_DrawRatioX_Pipe(packet, item + 1, x + (width / 3) * (row + 1) - (s32)((f32)(w >> 1) * scale),
                                         y + 0x20 + col * 0x20,
                                         scale, 1.0f, 0, SzMsg_DrawRect_Pipe);
                } else {
                    w = info[3];
                    scale = 1.0f;
                    if (w > 0xAC) {
                        scale = 172.0f / (f32)w;
                    }
                    packet = SzMsg_DrawRatioX_Pipe(packet, item + 1, x + (width >> 1) - (s32)((f32)(w >> 1) * scale),
                                         y + 0x1A + col * 0x14,
                                         scale, 0.90909094f, 0, SzMsg_DrawRect_Pipe);
                }
                sel = cursor[(s32)side + 2] & 0xF;
                if (sel == item) {
                    if (cursor[0x88]) {
                        packet = lSzDuel_DrawWindow_Frame_Pipe(packet, -1, -1, 6, x + (width / 3) * (row + 1) - 0x62,
                                             y + 0x1C + col * 0x20, -0xBE, -0x1A, 1);
                    } else {
                        packet = lSzDuel_DrawWindow_Frame_Pipe(packet, -1, -1, 6, x + (width >> 1) - 0x62,
                                             y + 0x16 + col * 0x14, -0xBE, -0x18, 1);
                    }
                }
            }
            SzMsg_Free(item + 1);
        }
    }
    packet = lSzDuel_DrawWindow_ExBoard_Pipe(packet, (s32)side, x + 0x20, y + 0x85, -(width - 0x3A), -0x34, -1, 0);
    px = x + 0x6D0 + ((width - 0x3A) >> 2);
    py = y + 0x7AC;
    packet = lSzDuel_DrawWindow_ExIcon_Pipe(packet, &D_00290A58, px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    px = x + 0x6E0 + ((width - 0x3A) >> 2);
    py = y + 0x7AC;
    packet = lSzDuel_DrawWindow_ExIcon_Pipe(packet, &D_00290A62, px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    px = x + 0x20 + ((width - 0x3A) >> 2);
    py = y + 0xA7;
    packet = SzDuel_DrawWindow_Font_Pipe(packet, px, py, 1, 2, func_0019BEF0((char *)text1), text1,
                         hint != 0 ? (s32)D_002BE944 : 0);
    px = x + 0x6D8 + (((width - 0x3A) * 2) >> 2);
    py = y + 0x7AC;
    packet = lSzDuel_DrawWindow_ExIcon_Pipe(packet, &D_00290A6C, px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    px = x + 0x20 + (((width - 0x3A) * 2) >> 2);
    py = y + 0xA7;
    packet = SzDuel_DrawWindow_Font_Pipe(packet, px, py, 1, 2, func_0019BEF0((char *)text2), text2,
                         hint != 0 ? (s32)D_002BE944 : 0);
    px = x + 0x6D8 + (((width - 0x3A) * 3) >> 2);
    py = y + 0x7AC;
    packet = lSzDuel_DrawWindow_ExIcon_Pipe(packet, &D_00290A76, px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    px = x + 0x20 + (((width - 0x3A) * 3) >> 2);
    py = y + 0xA7;
    return SzDuel_DrawWindow_Font_Pipe(packet, px, py, 1, 2, func_0019BEF0((char *)text3), text3,
                         hint != 0 ? (s32)D_002BE944 : 0);
}

/* Where a side's custom-duel settings are kept (CUSTOM_DUEL_ADDR + the side). */
static inline u8 *save_001C8DC0(u8 *save) {
    return save + CUSTOM_DUEL_ADDR;
}

/* Draws the deck-choice menu for `side`. */
s32 lSzDuel_DrawCustomDuel_Menu_SelectDeck_Pipe(s32 packet, u8 *side, s32 x, s32 y) {
    extern s32 *SzMsg_GetInfo(s32);
    extern s32 SzMsg_DrawRatioX_Pipe(s32, s32, s32, s32, f32, f32, s32, void (*)(void));
    extern s32 SzDuel_DrawWindow_Font_Pipe(s32, s32, s32, s32, s32, s32, s8 *, s32);
    extern s32 lSzDuel_DrawWindow_ExBoard_Pipe(s32, s32, s32, s32, s32, s32, s32, s32);
    extern s32 lSzDuel_DrawWindow_ExIcon_Pipe(s32, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
    extern u8 duelIcons[];
    extern char D_002BF05B[];
    extern char D_002BEF93[];
    extern s32 D_00290A58;
    extern s32 D_00290A62;
    extern s32 D_00290A6C;
    u8 *state = duelState.b;
    s8 *text3 = D_002BF05B;
    s8 *text4 = D_002BEF93;
    s32 color = (side[CUSTOM_DUEL_ADDR + 0x2] & 0xF) + 0x81;
    s32 width = 0x244;
    f32 scale;
    s32 hint = 0;
    s32 cx;
    s32 w;
    s32 id;
    u8 *p;
    s32 i;
    s32 a;
    s32 b;
    s32 ok;
    s32 sel;
    s32 okColor;
    s32 selColor;
    s32 base;
    s32 off;
    s32 bx;
    s32 px;
    s32 py;
    s32 by;

    width = (*(u8 *)(CUSTOM_DUEL_ADDR + 0x88) != 0) ? width : 0x114;
    scale = 1.0f;
    id = RhText_SetTextureFlush(SzMsg_LoadFont_Pipe(packet, 1, color, 0, 0x16));
    cx = x + (width >> 1);
    id = lSzDuel_DrawWindow_Frame_Pipe(id, 0xC, 3, 4, cx - 0x59, y, -0xB2, -0x20, 1);
    w = SzMsg_GetInfo(1)[3];
    if (w > 0x9A) {
        scale = 154.0f / (f32)w;
    }
    id = SzMsg_DrawRatioX_Pipe(id, 1, cx - (s32)((f32)(w >> 1) * scale), y + 5, scale, 1.0f, 0, SzMsg_DrawRect_Pipe);
    SzMsg_Free(1);
    id = lSzDuel_DrawWindow_Frame_Pipe(id, (s32)side, -1, 0xB, x, y + 0x20, -width, -0x96, 1);
    i = 0;
    p = save_001C8DC0(side);
    do {
        a = SzData_GetDeckCount((s32)side, i);
        b = SzData_GetLeader((s32)side, i);
        ok = (a >= 0x28 && b != 0x3E7) ? 1 : 0;
        sel = (p[4] == i) ? 1 : 0;
        selColor = sel ? 4 : 7;
        okColor = ok ? -1 : 5;
        base = side ? 0x14 : 0xA;
        off = (width * (i + 1)) >> 2;
        px = x + 0x6B4 + off;
        py = y + 0x74B;
        id = lSzDuel_DrawWindow_ExIcon_Pipe(id, duelIcons + (i + 0xE3) * 10, px, py, 0, 1, 0, 0, 0, 0, sel, 0, -1,
                           hint != 0 ? 0x40 : 0x80);
        bx = x + off - 0x18;
        by = y + 0x46;
        id = lSzDuel_DrawWindow_PicMini_Pipe(id, i + base, bx, by, 0x30, 0x30, *(s32 *)(state + 0xC58), sel);
        id = lSzDuel_DrawWindow_Frame_Pipe(id, okColor, -1, selColor, bx, by, -0x30, -0x30, 1);
        i++;
    } while (i < 3);
    id = lSzDuel_DrawWindow_ExBoard_Pipe(id, (s32)side, x + 0x12, y + 0x7A, -(width - 0x24), -0x34, -1, 0);
    px = x + 0x6C2 + ((width - 0x24) >> 2);
    py = y + 0x7A1;
    id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290A58, px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    px = x + 0x6D2 + ((width - 0x24) >> 2);
    py = y + 0x7A1;
    id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290A62, px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    px = x + 0x12 + ((width - 0x24) >> 2);
    py = y + 0x9C;
    id = SzDuel_DrawWindow_Font_Pipe(id, px, py, 1, 2, func_0019BEF0((char *)text3), text3,
                       hint != 0 ? (s32)D_002BE944 : 0);
    px = x + 0x6CA + (((width - 0x24) * 2) >> 2);
    py = y + 0x7A1;
    id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290A6C, px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    px = x + 0x12 + (((width - 0x24) * 2) >> 2);
    py = y + 0x9C;
    return SzDuel_DrawWindow_Font_Pipe(id, px, py, 1, 2, func_0019BEF0((char *)text4), text4,
                         hint != 0 ? (s32)D_002BE944 : 0);
}

typedef struct {
    u16 count;
    u16 flags;
    u32 padding;
    u64 registers;
} Tag_001C92C0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Color_001C92C0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Vertex_001C92C0;

typedef struct {
    Color_001C92C0 color;
    Vertex_001C92C0 xyz;
} Point_001C92C0;

typedef struct {
    u64 tag[2];
    Point_001C92C0 points[4];
    u64 end;
} Packet_001C92C0;

typedef struct {
    u8 b, g, r, a;
} Source_001C92C0;

typedef struct {
    Source_001C92C0 c[2];
} Pair_001C92C0;

/* Sets two vertex colours from `src`. */
static inline void set_color_001C92C0(Color_001C92C0 *a, Color_001C92C0 *b,
                                      Source_001C92C0 *src) {
    a->r = b->r = src->r;
    a->g = b->g = src->g;
    a->b = b->b = src->b;
    a->a = b->a = src->a;
    a->q = b->q = 1.0f;
}

/* Sets a screen vertex at (x, y) at the windows' depth. */
static inline void set_xyz_001C92C0(Vertex_001C92C0 *v, s32 x, s32 y, u8 *state) {
    v->x = x << 4;
    v->y = y << 4;
    v->z = *(s32 *)(state + 0xC58);
    v->fog = 0;
}

/* Draws the starting-life-points menu for `player`. */
s32 lSzDuel_DrawCustomDuel_Menu_LifeSet_Pipe(s32 out, s32 player, s32 x, s32 y) {
    extern s32 *SzMsg_GetInfo(s32);
    extern s32 SzMsg_DrawX_Pipe(s32, s32, s32, s32, s32, void (*)(void));
    extern s32 SzDuel_DrawWindow_Font_Pipe(s32, s32, s32, s32, s32, s32, s8 *, s32);
    extern s32 SzDuel_DrawWindow_FontDigit_Pipe(s32, s32, s32, s32, s32, s32, s32);
    extern s32 lSzDuel_DrawWindow_ExBoard_Pipe(s32, s32, s32, s32, s32, s32, s32, s32);
    extern s32 lSzDuel_DrawWindow_ExIcon_Pipe(s32, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
    extern char D_002BF05B[];
    extern char D_002BEF93[];
    extern s32 D_00290A1C;
    extern s32 D_00290896;
    extern s32 D_002908A0;
    extern s32 D_00290A58;
    extern s32 D_00290A62;
    extern s32 D_00290A6C;
    extern Pair_001C92C0 D_002914A0;
    u8 *state = duelState.b;
    s8 *text3 = D_002BF05B;
    s8 *text4 = D_002BEF93;
    s32 tmp = (((u8 *)player)[CUSTOM_DUEL_ADDR + 0x2] & 0xF) + 0x81;
    s32 width;
    s32 hint = 0;
    s32 cx;
    s32 id;
    s16 *life;
    s32 px;
    s32 py;
    s32 w;
    s32 h;
    Pair_001C92C0 colors;
    Packet_001C92C0 packet __attribute__((aligned(8)));

    if (*(u8 *)(CUSTOM_DUEL_ADDR + 0x88) != 0) {
        width = 0x244;
    } else {
        width = 0x114;
    }
    id = RhText_SetTextureFlush(SzMsg_LoadFont_Pipe(out, 1, tmp, 0, 0x16));
    cx = x + (width >> 1);
    id = lSzDuel_DrawWindow_Frame_Pipe(id, 0xC, 3, 4, cx - 0x59, y, -0xB2, -0x20, 1);
    id = SzMsg_DrawX_Pipe(id, 1, cx - (((s32 *)SzMsg_GetInfo(1))[3] >> 1), y + 5, 0, SzMsg_DrawRect_Pipe);
    SzMsg_Free(1);
    id = lSzDuel_DrawWindow_Frame_Pipe(id, player, -1, 0xB, x, y + 0x20, -width, -0x96, 1);
    id = lSzDuel_DrawWindow_Frame_Pipe(id, 0xC, -1, 5, cx - 0x38, y + 0x38, -0x70, -0x14, 1);
    px = x + 0x68A + (width >> 1);
    py = y + 0x75A;
    id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290A1C, px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    life = &((s16 *)(CUSTOM_DUEL_ADDR + 0x10))[player];
    id = SzDuel_DrawWindow_FontDigit_Pipe(id, cx - 0xE, y + 0x3C, 0, 0, 4, *life);
    px = x + 0x64E + (width >> 1);
    py = y + 0x76C;
    id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290896, px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    tmp = cx - 0x58;
    id = lSzDuel_DrawWindow_Frame_Pipe(id, 0xD, -1, 7, tmp, y + 0x50, -0xB0, -0x10, 1);
    px = x + 0x668 + (width >> 1);
    py = y + 0x770;
    w = (s32)((f32)*life * 176.0f / 9999.0f);
    h = 8;
    colors = D_002914A0;
    if (player == 0) {
        colors.c[1].b = 0;
        colors.c[1].g = 0;
        colors.c[0].b = 0;
        colors.c[0].g = 0;
    }
    ((Tag_001C92C0 *)packet.tag)->flags = 0x14;
    ((Tag_001C92C0 *)packet.tag)->count = 8;
    ((Tag_001C92C0 *)packet.tag)->registers = 0x41414141;
    ((Tag_001C92C0 *)packet.tag)->padding = 0;
    set_color_001C92C0(&packet.points[0].color, &packet.points[1].color, &colors.c[0]);
    set_color_001C92C0(&packet.points[2].color, &packet.points[3].color, &colors.c[1]);
    set_xyz_001C92C0(&packet.points[0].xyz, px, py, state);
    set_xyz_001C92C0(&packet.points[1].xyz, px + w, py, state);
    set_xyz_001C92C0(&packet.points[2].xyz, px, py + h, state);
    set_xyz_001C92C0(&packet.points[3].xyz, px + w, py + h, state);
    id = ExSortPrim_Pipe(id, (s32)packet.tag, 0, 0);
    set_color_001C92C0(&packet.points[0].color, &packet.points[1].color, &colors.c[1]);
    set_color_001C92C0(&packet.points[2].color, &packet.points[3].color, &colors.c[0]);
    set_xyz_001C92C0(&packet.points[0].xyz, px, py + h, state);
    set_xyz_001C92C0(&packet.points[1].xyz, px + w, py + h, state);
    set_xyz_001C92C0(&packet.points[2].xyz, px, py + h * 2, state);
    set_xyz_001C92C0(&packet.points[3].xyz, px + w, py + h * 2, state);
    id = ExSortPrim_Pipe(id, (s32)packet.tag, 0, 0);
    id = lSzDuel_DrawWindow_Frame_Pipe(id, -1, -1, 7, tmp, y + 0x50, -0xB0, -0x10, 1);
    px = x + 0x71A + (width >> 1);
    py = y + 0x76C;
    id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_002908A0, px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    id = lSzDuel_DrawWindow_ExBoard_Pipe(id, player, x + 0x12, y + 0x7A, -(width - 0x24), -0x34, -1, 0);
    px = x + 0x6C2 + ((width - 0x24) >> 2);
    py = y + 0x7A1;
    id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290A58, px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    px = x + 0x6D2 + ((width - 0x24) >> 2);
    py = y + 0x7A1;
    id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290A62, px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    px = x + 0x12 + ((width - 0x24) >> 2);
    py = y + 0x9C;
    id = SzDuel_DrawWindow_Font_Pipe(id, px, py, 1, 2, func_0019BEF0((char *)text3), text3,
                       hint != 0 ? (s32)D_002BE944 : 0);
    px = x + 0x6CA + (((width - 0x24) * 2) >> 2);
    py = y + 0x7A1;
    id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290A6C, px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    px = x + 0x12 + (((width - 0x24) * 2) >> 2);
    py = y + 0x9C;
    return SzDuel_DrawWindow_Font_Pipe(id, px, py, 1, 2, func_0019BEF0((char *)text4), text4,
                         hint != 0 ? (s32)D_002BE944 : 0);
}

/* Draws the summon-charge menu for `side`. */
s32 lSzDuel_DrawCustomDuel_Menu_SummonCharge_Pipe(s32 packet, u8 *side, s32 x, s32 y) {
    extern s32 *SzMsg_GetInfo(s32);
    extern s32 SzMsg_DrawRatioX_Pipe(s32, s32, s32, s32, f32, f32, s32, void (*)(void));
    extern s32 SzDuel_DrawWindow_Font_Pipe(s32, s32, s32, s32, s32, s32, s8 *, s32);
    extern s32 SzDuel_DrawWindow_FontDigit_Pipe(s32, s32, s32, s32, s32, s32, s32);
    extern s32 lSzDuel_DrawWindow_ExBoard_Pipe(s32, s32, s32, s32, s32, s32, s32, s32);
    extern s32 lSzDuel_DrawWindow_ExIcon_Pipe(s32, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
    extern char D_002BF05B[];
    extern char D_002BEF93[];
    extern s32 D_00290896;
    extern s32 D_002908E6;
    extern s32 D_002908A0;
    extern s32 D_00290A58;
    extern s32 D_00290A62;
    extern s32 D_00290A6C;
    s8 *text3 = D_002BF05B;
    s8 *text4 = D_002BEF93;
    s32 color = (side[CUSTOM_DUEL_ADDR + 0x2] & 0xF) + 0x81;
    s32 width;
    f32 scale;
    s32 hint = 0;
    s32 cx;
    s32 w;
    s32 id;
    s32 px;
    s32 py;

    if (*(u8 *)(CUSTOM_DUEL_ADDR + 0x88) != 0) {
        width = 0x244;
    } else {
        width = 0x114;
    }
    scale = 1.0f;
    id = RhText_SetTextureFlush(SzMsg_LoadFont_Pipe(packet, 1, color, 0, 0x16));
    cx = x + (width >> 1);
    id = lSzDuel_DrawWindow_Frame_Pipe(id, 0xC, 3, 4, cx - 0x59, y, -0xB2, -0x20, 1);
    w = SzMsg_GetInfo(1)[3];
    if (w > 0x9A) {
        scale = 154.0f / (f32)w;
    }
    id = SzMsg_DrawRatioX_Pipe(id, 1, cx - (s32)((f32)(w >> 1) * scale), y + 5, scale, 1.0f, 0, SzMsg_DrawRect_Pipe);
    SzMsg_Free(1);
    id = lSzDuel_DrawWindow_Frame_Pipe(id, (s32)side, -1, 0xB, x, y + 0x20, -width, -0x96, 1);
    px = x + 0x688 + (width >> 1);
    py = y + 0x764;
    id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290896, px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    id = lSzDuel_DrawWindow_Frame_Pipe(id, 0xC, -1, 5, cx - 0x1E, y + 0x46, -0x3C, -0x14, 1);
    px = x + 0x6A4 + (width >> 1);
    py = y + 0x768;
    id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_002908E6, px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    id = SzDuel_DrawWindow_FontDigit_Pipe(id, cx - 6, y + 0x4A, 0, 0, 2, side[CUSTOM_DUEL_ADDR + 0x6]);
    px = x + 0x6E0 + (width >> 1);
    py = y + 0x764;
    id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_002908A0, px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    id = lSzDuel_DrawWindow_ExBoard_Pipe(id, (s32)side, x + 0x12, y + 0x7A, -(width - 0x24), -0x34, -1, 0);
    px = x + 0x6C2 + ((width - 0x24) >> 2);
    py = y + 0x7A1;
    id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290A58, px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    px = x + 0x6D2 + ((width - 0x24) >> 2);
    py = y + 0x7A1;
    id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290A62, px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    px = x + 0x12 + ((width - 0x24) >> 2);
    py = y + 0x9C;
    id = SzDuel_DrawWindow_Font_Pipe(id, px, py, 1, 2, func_0019BEF0((char *)text3), text3,
                       hint != 0 ? (s32)D_002BE944 : 0);
    px = x + 0x6CA + (((width - 0x24) * 2) >> 2);
    py = y + 0x7A1;
    id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290A6C, px, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    px = x + 0x12 + (((width - 0x24) * 2) >> 2);
    return SzDuel_DrawWindow_Font_Pipe(id, px, y + 0x9C, 1, 2, func_0019BEF0((char *)text4), text4,
                         hint != 0 ? (s32)D_002BE944 : 0);
}

/* Draws the leader-ability on/off menu for `side`. */
s32 lSzDuel_DrawCustomDuel_Menu_LeaderAbility_Pipe(s32 packet, u8 *side, s32 x, s32 y) {
    extern s32 *SzMsg_GetInfo(s32);
    extern s32 SzMsg_DrawX_Pipe(s32, s32, s32, s32, s32, void (*)(void));
    extern s32 SzDuel_DrawWindow_Font_Pipe(s32, s32, s32, s32, s32, s32, s8 *, s32);
    extern s32 lSzDuel_DrawWindow_ExBoard_Pipe(s32, s32, s32, s32, s32, s32, s32, s32);
    extern s32 lSzDuel_DrawWindow_ExIcon_Pipe(s32, void *, s32, s32, s32, s32, s32, s32, s64, s64, s64, s64, s64, s64);
    extern char D_002BF05B[];
    extern char D_002BEF93[];
    extern char D_002BF062[];
    extern char D_002BF066[];
    extern s32 D_00290A58;
    extern s32 D_00290A62;
    extern s32 D_00290A6C;
    s8 *text3 = D_002BF05B;
    s8 *text4 = D_002BEF93;
    s8 *text2 = D_002BF062;
    s8 *text1 = D_002BF066;
    s32 hint = 0;
    s32 win;
    s32 tx;
    s32 ty;
    s32 id;

    id = RhText_SetTextureFlush(SzMsg_LoadFont_Pipe(packet, 1, (side[CUSTOM_DUEL_ADDR + 0x2] & 0xF) + 0x81, 0, 0x16));
    id = lSzDuel_DrawWindow_Frame_Pipe(id, 0xC, 3, 4, x + 0x31, y, -0xB2, -0x20, 1);
    id = SzMsg_DrawX_Pipe(id, 1, x + 0x8A - (((s32 *)SzMsg_GetInfo(1))[3] >> 1), y + 5, 0,
                       SzMsg_DrawRect_Pipe);
    SzMsg_Free(1);
    win = lSzDuel_DrawWindow_Frame_Pipe(id, (s32)side, -1, 0xB, x, y + 0x20, -0x114, -0x96, 1);
    tx = x + 0x5C;
    ty = y + 0x4D;
    id = SzDuel_DrawWindow_Font_Pipe(win, tx, ty, 0, 3, func_0019BEF0((char *)text1), text1,
                       side[CUSTOM_DUEL_ADDR + 0x8] != 0 ? (s32)D_002BE944 : 0);
    tx = x + 0xB8;
    ty = y + 0x4D;
    id = SzDuel_DrawWindow_Font_Pipe(id, tx, ty, 0, 3, func_0019BEF0((char *)text2), text2,
                       side[CUSTOM_DUEL_ADDR + 0x8] != 0 ? 0 : (s32)D_002BE944);
    id = lSzDuel_DrawWindow_ExBoard_Pipe(id, (s32)side, x + 0x12, y + 0x7A, -0xF0, -0x34, -1, 0);
    id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290A58, x + 0x6FE, y + 0x7A1, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290A62, x + 0x70E, y + 0x7A1, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    tx = x + 0x4E;
    ty = y + 0x9C;
    id = SzDuel_DrawWindow_Font_Pipe(id, tx, ty, 1, 2, func_0019BEF0((char *)text3), text3,
                       hint != 0 ? (s32)D_002BE944 : 0);
    id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290A6C, x + 0x742, y + 0x7A1, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    tx = x + 0x8A;
    ty = y + 0x9C;
    return SzDuel_DrawWindow_Font_Pipe(id, tx, ty, 1, 2, func_0019BEF0((char *)text4), text4,
                         hint != 0 ? (s32)D_002BE944 : 0);
}

/* Draws the card-display on/off menu for `side`. */
s32 lSzDuel_DrawCustomDuel_Menu_CardDisp_Pipe(s32 packet, u8 *side, s32 x, s32 y) {
    extern s32 *SzMsg_GetInfo(s32);
    extern s32 SzMsg_DrawX_Pipe(s32, s32, s32, s32, s32, void (*)(void));
    extern s32 SzDuel_DrawWindow_Font_Pipe(s32, s32, s32, s32, s32, s32, s8 *, s32);
    extern s32 lSzDuel_DrawWindow_ExBoard_Pipe(s32, s32, s32, s32, s32, s32, s32, s32);
    extern s32 lSzDuel_DrawWindow_ExIcon_Pipe(s32, void *, s32, s32, s32, s32, s32, s32, s64, s64, s64, s64, s64, s64);
    extern char D_002BF05B[];
    extern char D_002BEF93[];
    extern char D_002BF051[];
    extern char D_002BF056[];
    extern s32 D_00290A58;
    extern s32 D_00290A62;
    extern s32 D_00290A6C;
    s8 *text3 = D_002BF05B;
    s8 *text4 = D_002BEF93;
    s8 *text2 = D_002BF051;
    s8 *text1 = D_002BF056;
    s32 hint = 0;
    s32 win;
    s32 tx;
    s32 ty;
    s32 id;

    id = RhText_SetTextureFlush(SzMsg_LoadFont_Pipe(packet, 1, (side[CUSTOM_DUEL_ADDR + 0x2] & 0xF) + 0x81, 0, 0x16));
    id = lSzDuel_DrawWindow_Frame_Pipe(id, 0xC, 3, 4, x + 0x31, y, -0xB2, -0x20, 1);
    id = SzMsg_DrawX_Pipe(id, 1, x + 0x8A - (((s32 *)SzMsg_GetInfo(1))[3] >> 1), y + 5, 0,
                       SzMsg_DrawRect_Pipe);
    SzMsg_Free(1);
    win = lSzDuel_DrawWindow_Frame_Pipe(id, (s32)side, -1, 0xB, x, y + 0x20, -0x114, -0x96, 1);
    tx = x + 0x5C;
    ty = y + 0x4D;
    id = SzDuel_DrawWindow_Font_Pipe(win, tx, ty, 0, 3, func_0019BEF0((char *)text1), text1,
                       side[CUSTOM_DUEL_ADDR + 0xC] != 0 ? (s32)D_002BE944 : 0);
    tx = x + 0xB8;
    ty = y + 0x4D;
    id = SzDuel_DrawWindow_Font_Pipe(id, tx, ty, 0, 3, func_0019BEF0((char *)text2), text2,
                       side[CUSTOM_DUEL_ADDR + 0xC] != 0 ? 0 : (s32)D_002BE944);
    id = lSzDuel_DrawWindow_ExBoard_Pipe(id, (s32)side, x + 0x12, y + 0x7A, -0xF0, -0x34, -1, 0);
    id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290A58, x + 0x6FE, y + 0x7A1, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290A62, x + 0x70E, y + 0x7A1, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    tx = x + 0x4E;
    ty = y + 0x9C;
    id = SzDuel_DrawWindow_Font_Pipe(id, tx, ty, 1, 2, func_0019BEF0((char *)text3), text3,
                       hint != 0 ? (s32)D_002BE944 : 0);
    id = lSzDuel_DrawWindow_ExIcon_Pipe(id, &D_00290A6C, x + 0x742, y + 0x7A1, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
    tx = x + 0x8A;
    ty = y + 0x9C;
    return SzDuel_DrawWindow_Font_Pipe(id, tx, ty, 1, 2, func_0019BEF0((char *)text4), text4,
                         hint != 0 ? (s32)D_002BE944 : 0);
}

typedef struct {
    u16 count;
    u16 flags;
    u32 padding;
    u64 registers;
} Tag_001CA7C0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Color_001CA7C0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Vertex_001CA7C0;

typedef struct {
    Color_001CA7C0 color;
    Vertex_001CA7C0 xyz;
} Point_001CA7C0;

typedef struct {
    u64 tag[2];
    Point_001CA7C0 points[4];
    u64 end;
} Packet_001CA7C0;

typedef struct {
    u64 tag[2];
    Color_001CA7C0 color;
    Vertex_001CA7C0 xyz[2];
    u64 end;
} Rect_001CA7C0;

typedef struct {
    u8 b, g, r, a;
} Source_001CA7C0;

typedef struct {
    u8 pad[0xFEA3];
    u8 maps[5][7][7];
} Maps_001CA7C0;

/* Sets two vertex colours from `src`. */
static inline void set_color_001CA7C0(Color_001CA7C0 *a, Color_001CA7C0 *b,
                                      Source_001CA7C0 *src) {
    a->r = b->r = src->r;
    a->g = b->g = src->g;
    a->b = b->b = src->b;
    a->a = b->a = src->a;
    a->q = b->q = 1.0f;
}

/* Sets a screen vertex at (x, y) at the windows' depth. */
static inline void set_xyz_001CA7C0(Vertex_001CA7C0 *v, s32 x, s32 y, u8 *state) {
    v->x = x << 4;
    v->y = y << 4;
    v->z = *(s32 *)(state + 0xC58);
    v->fog = 0;
}

/* Sets one corner of a drawing rectangle. */
static inline void set_corner_001CA7C0(Vertex_001CA7C0 *v, s32 x, s32 y) {
    v->x = x << 4;
    v->y = y << 4;
    v->z = duelState.s.depth;
    v->fog = 0;
}
#pragma optimization_level 3

/* Draws the map-choice menu for `player`, with a small picture of each map. */
s32 lSzDuel_DrawCustomDuel_Menu_SelectMap_Pipe(s32 id, s32 player, s32 x, s32 y) {
    extern s32 *func_001FEAB0(s32);
    extern s32 func_001FE7D0(s32, s32, s32, s32, s32, void (*)(void));
    extern s32 func_001B6F70(s32, s32, s32, s32, s32, s32, s8 *, s32);
    extern s32 func_001B6EA0(s32, s32, s32, s32, s32, s32, s32);
    extern s32 func_001B65F0(s32, s32, s32, s32, s32, s32, s32, s32);
    extern s32 func_001B3CC0(s32, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
    extern u8 duelIcons[];
    extern u8 fieldColors[];
    extern u8 D_002CEE5C[][7][7];
    extern char D_002BF06E[];
    extern char D_002BEF93[];
    extern s32 D_00290828;
    extern s32 D_00290AA8;
    extern s32 D_00290832;
    extern s32 D_00290AB2;
    extern s32 D_002902C4;
    extern s32 D_00290256;
    extern s32 D_00290A58;
    extern s32 D_00290A62;
    extern s32 D_00290A6C;
    s32 ret;
    u8 *state = duelState.b;
    u8 *save = (u8 *)CUSTOM_DUEL_ADDR;
    Maps_001CA7C0 *maps;
    s8 *text1;
    s8 *text2;
    s32 sel;
    s32 hint = 0;
    s32 tx;
    s32 ty;
    s32 i;
    s32 last;
    s32 j;
    s32 row;
    s32 count;
    u16 entry;
    s32 n;
    u16 *p;
    s32 hl;
    u8 *board;
    s32 px;
    s32 py;
    s32 w;
    s32 h;
    Rect_001CA7C0 rect __attribute__((aligned(8)));
    Packet_001CA7C0 packet __attribute__((aligned(8)));

    text1 = D_002BF06E;
    text2 = D_002BEF93;
    sel = (*(u8 *)(CUSTOM_DUEL_ADDR + 0x89) + 2) % *(u8 *)(CUSTOM_DUEL_ADDR + 0x8A);
    id = func_001B4780(func_0020F290(func_001FD680(func_001FD680(func_001FD680(func_001FD680(id, 1, 0x89, 0, 0x16),
                                                                 2, 0x8B, 0, 0x2C),
                                                   3, 0x8C, 0, 0x42),
                                     4, 0x8A, 0, 0x58)),
                       0xC, 3, 4, x + 0xC9, y, -0xB2, -0x20, 1);
    id = func_001FE7D0(id, 1, x + 0x122 - (func_001FEAB0(1)[3] >> 1), y + 5, 0, SzMsg_DrawRect_Pipe);
    func_001FEAF0(1);
    py = y + 0x20;
    id = func_001B4780(id, player, -1, 0xB, x, py, -0x244, -0xAA, 1);
    py = y + 0x745;
    id = func_001B3CC0(id, &D_00290828, x + 0x71D, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    py = y + 0x747;
    id = func_001B3CC0(id, &D_00290AA8, x + 0x73D, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    py = y + 0x35;
    id = func_001B4780(id, 0xC, -1, 6, x + 0x5D, py, -0xEC, -0x7C, 1);
    px = x + 0x71D;
    py = y + 0x789;
    ((Tag_001CA7C0 *)rect.tag)->flags = 6;
    ((Tag_001CA7C0 *)rect.tag)->count = 3;
    ((Tag_001CA7C0 *)rect.tag)->registers = 0x441;
    ((Tag_001CA7C0 *)rect.tag)->padding = 0;
    rect.color.r = 0x80;
    rect.color.g = 0;
    rect.color.b = 0;
    rect.color.a = 0x80;
    rect.color.q = 1.0f;
    set_corner_001CA7C0(&rect.xyz[0], px, py);
    set_corner_001CA7C0(&rect.xyz[1], px + 0xF0, py + 0x18);
    id = func_00207650(id, (s32)rect.tag, 0, 0);
    py = y + 0x35;
    id = func_001B4780(id, -1, -1, 6, x + 0x5D, py, -0xEC, -0x7C, hint != 0 ? 0 : 1);
    for (i = 0; i < 5; i++) {
        hl = (i == 2) ? 0 : (s32)D_002BE944;
        p = (u16 *)(save + 0x18 + ((save[0x89] + i) % save[0x8A]) * 2);
        n = *p & 0xFF;
        id = func_001FE7D0(id, (*p >> 8) + 2, x + 0x69, y + 0x3A + i * 0x18, hl, SzMsg_DrawRect_Pipe);
        id = func_001B6CA0(id, x + 0x119, y + 0x3A + i * 0x18, 2, n, 0, 1, hl);
    }
    func_001FEAF0(2);
    func_001FEAF0(3);
    func_001FEAF0(4);
    py = y + 0x78D;
    id = func_001B3CC0(id, &D_002902C4, x + 0x71F, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    py = y + 0x78D;
    id = func_001B3CC0(id, &D_002902C4, x + 0x803, py, 0, 1, 0, 0, 1, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    py = y + 0x7D5;
    id = func_001B3CC0(id, &D_00290832, x + 0x71D, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    py = y + 0x7D7;
    id = func_001B3CC0(id, &D_00290AB2, x + 0x73D, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    p = &((u16 *)(CUSTOM_DUEL_ADDR + 0x18))[sel];
    switch (*p >> 8) {
        case 0:
            maps = func_002145E0(0);
            board = &maps->maps[*(u8 *)p][0][0];
            break;
        case 1:
            maps = func_002145E0(1);
            board = &maps->maps[*(u8 *)p][0][0];
            break;
        case 2:
            board = &D_002CEE5C[sel + 0x16][0][0];
            break;
    }
    px = x + 0x81C;
    py = y + 0x75C;
    for (i = 0; i < 7; i++) {
        for (j = 0; j < 7; j++) {
            last = func_001B3CC0(id, duelIcons + (board[i * 7 + j] + 0x10E) * 10, px + j * 16,
                               py + i * 16, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
            id = last;
        }
    }
    py = y + 0x35;
    id = func_001B4780(last, -1, 1, 1, x + 0x155, py, -0x76, -0x76, 1);
    py = y + 0x7C7;
    id = func_001B3CC0(id, &D_00290256, x + 0x834, py, 0, 1, 0, 0, 0, 1, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    for (row = 0; row < 10; row++) {
        count = 0;
        for (i = 0; i < 7; i++) {
            for (j = 0; j < 7; j++) {
                if (row == board[i * 7 + j]) {
                    count++;
                }
            }
        }
        id = func_001B3CC0(id, duelIcons + (row + 0x10E) * 10, x + 0x89B, y + 0x745 + row * 16, 0, 1, 0,
                           0, 0, 0, 1, 0, -1, 0x80);
        id = func_001B4780(id, 0xD, -1, 5, x + 0x1EB, y + 0x25 + row * 16, -0x54, -0x10, 1);
        px = x + 0x8AB;
        py = y + 0x745 + row * 16;
        w = (s32)((f32)count * 84.0f / 49.0f);
        h = 8;
        ((Tag_001CA7C0 *)packet.tag)->flags = 0x14;
        ((Tag_001CA7C0 *)packet.tag)->count = 8;
        ((Tag_001CA7C0 *)packet.tag)->registers = 0x41414141;
        ((Tag_001CA7C0 *)packet.tag)->padding = 0;
        set_color_001CA7C0(&packet.points[0].color, &packet.points[1].color, &((Source_001CA7C0 *)fieldColors)[row * 3]);
        set_color_001CA7C0(&packet.points[2].color, &packet.points[3].color, &((Source_001CA7C0 *)fieldColors)[row * 3 + 1]);
        set_xyz_001CA7C0(&packet.points[0].xyz, px, py, state);
        set_xyz_001CA7C0(&packet.points[1].xyz, px + w, py, state);
        set_xyz_001CA7C0(&packet.points[2].xyz, px, py + h, state);
        set_xyz_001CA7C0(&packet.points[3].xyz, px + w, py + h, state);
        id = func_00207650(id, (s32)packet.tag, 0, 0);
        set_color_001CA7C0(&packet.points[0].color, &packet.points[1].color, &((Source_001CA7C0 *)fieldColors)[row * 3 + 1]);
        set_color_001CA7C0(&packet.points[2].color, &packet.points[3].color, &((Source_001CA7C0 *)fieldColors)[row * 3 + 2]);
        set_xyz_001CA7C0(&packet.points[0].xyz, px, py + h, state);
        set_xyz_001CA7C0(&packet.points[1].xyz, px + w, py + h, state);
        set_xyz_001CA7C0(&packet.points[2].xyz, px, py + h * 2, state);
        set_xyz_001CA7C0(&packet.points[3].xyz, px + w, py + h * 2, state);
        id = func_00207650(id, (s32)packet.tag, 0, 0);
        id = func_001B4780(id, -1, -1, 5, x + 0x1EB, y + 0x25 + row * 16, -0x54, -0x10, 1);
        id = func_001B6EA0(id, x + 0x215, y + 0x27 + row * 16, 0, 2, 2, count);
    }
    id = func_001B65F0(id, player, x + 6, y + 0x26, -0x4E, -0x9E, -1, 0);
    py = y + 0x76E;
    id = func_001B3CC0(id, &D_00290A62, x + 0x6CE, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    py = y + 0x77E;
    ret = func_001B3CC0(id, &D_00290A58, x + 0x6CE, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    tx = x + 0x20;
    ty = y + 0x58;
    ret = func_001B6F70(ret, tx, ty, 1, 0, func_0019BEF0((char *)text1), text1,
                       hint != 0 ? (s32)D_002BE944 : 0);
    py = y + 0x7B7;
    ret = func_001B3CC0(ret, &D_00290A6C, x + 0x6CE, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    tx = x + 0x20;
    ty = y + 0x99;
    return func_001B6F70(ret, tx, ty, 1, 0, func_0019BEF0((char *)text2), text2,
                         hint != 0 ? (s32)D_002BE944 : 0);
}
#pragma optimization_level reset
