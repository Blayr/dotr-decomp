#include "common.h"

/* shape c027:01E00080, 129 insns: scene step: red scene colour, 0x2366 20, 0x236E 130; on the first frame it sets the
   scene colours, eight 160.0 widths and four corner points (+-100) and spawns the node chain (c027:01E008B0 with
   handler 0x1E00290); every third frame, once 0x22D8 passes 16 and 0x2368 is set, six ribbon nodes at the origin
   with random turns (c027:01E00AA0, handler 0x1E003A0) */

typedef struct {
    u8 pad0[0x80];
    Vec4f pos;
    u8 pad90[0x2248];
    s32 w22D8;
    u8 col[4];
    u8 pad22E0[8];
    s32 head;
    u8 pad22EC[4];
    s32 w22F0;
    u8 pad22F4[0x1C];
    f32 width[8];
    u8 pad2330[0x1E];
    s16 h234E;
    u8 pad2350[6];
    s16 corner;
    u8 pad2358[4];
    s16 t;
    u8 pad235E[8];
    s16 h2366;
    s16 h2368;
    u8 pad236A[4];
    s16 h236E;
    u8 pad2370[2];
    u8 c2372[3];
    u8 pad2375;
    u8 c2376[3];
} Scene_c027_01E00080;

static void func_01E00080_c027(Scene_c027_01E00080 *g) {
    extern void c027_01E00290();
    extern void c027_01E003A0();
    extern void c027_01E008B0(Scene_c027_01E00080 *, void *);
    extern void c027_01E00AA0(Scene_c027_01E00080 *, void *);
    extern void func_00106DD0(void *, f32, f32, f32);
    s32 i;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->h2366 = 20;
    g->h236E = 0x82;
    g->t++;
    if (g->t == 1) {
        g->h2368 = 0;
        g->c2372[0] = 0x40;
        g->c2372[1] = 0x20;
        g->c2372[2] = 0x30;
        g->c2376[0] = 0xC0;
        g->c2376[1] = 0;
        g->c2376[2] = 0;
        g->col[0] = 0x30;
        g->col[1] = 0x30;
        g->col[2] = 0x30;
        g->col[0] = 0x80;
        g->col[1] = 0;
        g->col[2] = 0;
        g->col[3] = 0;
        for (i = 0; i < 8; i++) {
            g->width[i] = 160.0f;
        }
        g->corner = 0;
        func_00106DD0(&g->pos, -100.0f, 100.0f, 0.0f);
        g->corner = 1;
        func_00106DD0(&g->pos, 100.0f, 100.0f, 0.0f);
        g->corner = 2;
        func_00106DD0(&g->pos, -100.0f, -100.0f, 0.0f);
        g->corner = 3;
        func_00106DD0(&g->pos, 100.0f, -100.0f, 0.0f);
        c027_01E008B0(g, c027_01E00290);
    }
    if (g->t % 3 == 1 && g->w22D8 > 16 && g->h2368 != 0) {
        for (i = 0; i < 6; i++) {
            g->head = 0;
            g->w22F0 = 0;
            g->h234E = func_0019A5C8() % 360;
            func_00106DD0(&g->pos, 0.0f, 0.0f, 0.0f);
            c027_01E00AA0(g, c027_01E003A0);
        }
    }
}

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

/* shape c027:01E008B0, 123 insns: take the first free node of 70 (0x7C bytes at ctx+0xF0), mark it with its index + 1,
   colour both from the scene colour at ctx+0x22DC, clear 0x72/0x74, random turns 0..179 and 0..359, three random
   +-30 speeds, handler shape c027:01E00C50 and the argument; the scene keeps it as its last node */

typedef struct {
    u8 pad0[0x30];
    f32 vx, vy, vz;
    u8 pad3C[0x1C];
    s32 fn;
    s32 arg;
    u8 col[4];
    u8 col2[4];
    s16 used;
    u8 pad6A[2];
    s16 h6C;
    s16 h6E;
    u8 pad70[2];
    s16 h72;
    s16 h74;
    u8 pad76[6];
} Node_c027_01E008B0;

typedef struct {
    u8 pad0[0xF0];
    Node_c027_01E008B0 node[70];
    u8 padEnd[0x22DC - 0xF0 - 70 * 0x7C];
    u8 col[4];
    u8 pad22E0[8];
    Node_c027_01E008B0 *head;
} Ctx_c027_01E008B0;

static void func_01E008B0_c027(Ctx_c027_01E008B0 *g, s32 arg) {
    extern void c027_01E00C50();
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    s16 i;
    Node_c027_01E008B0 *s;

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
        func_001076F0(s->col, g->col[0], g->col[1], g->col[2]);
        s->col[3] = g->col[3];
        func_001076F0(s->col2, g->col[0], g->col[1], g->col[2]);
        s->col2[3] = g->col[3];
        s->h72 = 0;
        s->h74 = 0;
        s->h6C = func_0019A5C8() % 180;
        s->h6E = func_0019A5C8() % 360;
        if (func_0019A5C8() % 2 == 0) {
            s->vx = 30.0f;
        } else {
            s->vx = -30.0f;
        }
        if (func_0019A5C8() % 2 == 0) {
            s->vy = 30.0f;
        } else {
            s->vy = -30.0f;
        }
        if (func_0019A5C8() % 2 == 0) {
            s->vz = 30.0f;
        } else {
            s->vz = -30.0f;
        }
        s->fn = (s32)c027_01E00C50;
        s->arg = arg;
        g->head = s;
    }
}

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
