#include "common.h"

INCLUDE_ASM("asm/nonmatchings/mod/c027", func_01E00080_c027);

/* shape c027:01E00290, 66 insns: 0x6A..0x6E = 360; while the game counter at 0x22D8 is below 6 both alphas fade by
   0x30 (the second ends it), otherwise both grow by 0x10 (below 0x80) and a full second alpha sets the game flag
   0x2368; after game step 0x235C passes 12 the game colour at 0x2372 dims by 10 (above 0x30), 0x2373 = 0 and 0x2374
   grows by 10 (below 0x50); the effect stops below counter 2 */

typedef struct {
    u8 pad0[0x22D8];
    s32 count;
    u8 pad22DC[0x80];
    s16 step;
    u8 pad235E[0xA];
    s16 flag;
    u8 pad236A[8];
    u8 c2372;
    u8 c2373;
    u8 c2374;
} Game_c027_01E00290;

typedef struct {
    u8 pad0[0x60];
    u8 col[4];
    u8 col2[4];
    s16 mode;
    s16 f6A;
    s16 f6C;
    s16 f6E;
} Fx_c027_01E00290;

static s32 func_01E00290_c027(Game_c027_01E00290 *g, Fx_c027_01E00290 *o) {
    o->f6A = 360;
    o->f6C = 360;
    o->f6E = 360;
    if (g->count < 6) {
        if (o->col[3] > 0x30) {
            o->col[3] -= 0x30;
        }
        if (o->col2[3] > 0x30) {
            o->col2[3] -= 0x30;
        } else {
            o->mode = 0;
        }
    } else {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x10;
        }
        if (o->col2[3] < 0x80) {
            o->col2[3] += 0x10;
        }
        if (o->col2[3] >= 0x80) {
            g->flag = 1;
        }
    }
    if (g->step > 0xC) {
        if (g->c2372 > 0x30) {
            g->c2372 -= 10;
        }
        g->c2373 = 0;
        if (g->c2374 < 0x50) {
            g->c2374 += 10;
        }
    }
    if (g->count < 2) {
        o->mode = 0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c027", func_01E003A0_c027);

INCLUDE_ASM("asm/nonmatchings/mod/c027", func_01E00660_c027);

INCLUDE_ASM("asm/nonmatchings/mod/c027", func_01E008B0_c027);

/* shape c027:01E00AA0, 105 insns: take the first free ribbon node of 70 (0x7C bytes at ctx+0xF0), mark it with its index + 1, colour it red (alpha 0), copy the scene point, link it after the scene's last node (starting from its position), give it the scene ids, three turns (fptosi of ctx+0x22F0..F8), handler shape c027:01E01930 and the argument */

typedef struct {
    f32 x, y, z, w;
} V4_c027_01E00AA0;

typedef struct Node_c027_01E00AA0 {
    f32 f0, f4, f8;
    u8 padC[4];
    f32 f10, f14, f18;
    u8 pad1C[4];
    V4_c027_01E00AA0 pos;
    u8 pad30[0x18];
    s32 w48;
    u8 pad4C[4];
    struct Node_c027_01E00AA0 *prev;
    struct Node_c027_01E00AA0 *next;
    s32 fn;
    s32 arg;
    u8 col[4];
    u8 col2[4];
    s16 used;
    u8 pad6A[6];
    s16 h70;
    s16 h72;
    s16 h74;
    s16 h76;
    s16 h78;
    s16 h7A;
} Node_c027_01E00AA0;

typedef struct {
    u8 pad0[0x80];
    V4_c027_01E00AA0 pos;
    u8 pad90[0x60];
    Node_c027_01E00AA0 node[70];
    u8 padEnd[0x22E8 - 0xF0 - 70 * 0x7C];
    Node_c027_01E00AA0 *head;
    u8 pad22EC[4];
    f32 rx, ry, rz;
    u8 pad22FC[0x52];
    s16 h234E;
    u8 pad2350[2];
    s16 h2352;
    u8 pad2354[2];
    s16 h2356;
} Ctx_c027_01E00AA0;

static void func_01E00AA0_c027(Ctx_c027_01E00AA0 *g, s32 arg) {
    extern void c027_01E01930();
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern s16 func_001A22C0(f32);
    s16 i;
    Node_c027_01E00AA0 *s;
    Node_c027_01E00AA0 *q;

    s = NULL;
    for (i = 0; i < 70; i++) {
        if (g->node[i].used == 0) {
            s = &g->node[i];
            func_00195108(s, 0x7C);
            g->node[i].used = i + 1;
            i = 70;
        }
    }
    if (s != NULL) {
        func_001076F0(s->col, 0x80, 0, 0);
        s->col[3] = 0;
        func_001076F0(s->col2, 0x80, 0, 0);
        s->col2[3] = 0;
        s->pos = g->pos;
        s->prev = g->head;
        q = s->prev;
        if (q != NULL) {
            q->next = s;
            s->f0 = s->f10 = q->f10;
            s->f4 = s->f14 = q->f14;
            s->f8 = s->f18 = q->f18;
        }
        s->w48 = g->h234E;
        s->h72 = func_001A22C0(g->rx);
        s->h74 = func_001A22C0(g->ry);
        s->h70 = func_001A22C0(g->rz);
        s->h76 = g->h2352;
        s->h7A = g->h2356;
        s->prev = g->head;
        s->h78 = 4;
        s->fn = (s32)c027_01E01930;
        s->arg = arg;
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/c027", func_01E00C50_c027);

INCLUDE_ASM("asm/nonmatchings/mod/c027", func_01E01930_c027);
