#include "common.h"

/* shape b262:01E00F50, 294 insns: lightning bolt update: on tick 0 lays count (<= 16) nodes evenly from p0 to p1,
   each jittered by +-jitter/10 (rand), and resets the three strand alphas; then grows the visible part one node
   per step ticks, builds the strands (module helpers 01E00280 / 01E00940), fades them, nudges each glow point by
   0x80, and restarts after fade + step * count ticks. */

typedef struct {
    u8 pad0[0x20];
    Vec4f pos;
    u8 pad30[0x40];
} Node_b262_01E00F50;

typedef struct {
    u8 pad0[7];
    u8 a;
    u8 pad8[8];
} Strand_b262_01E00F50;

typedef struct {
    s32 x, y, z, w;
} Pt_b262_01E00F50;

typedef struct {
    u8 pad0[0xB];
    u8 a;
    u8 padC[0x54];
    Pt_b262_01E00F50 v[64];
} Glow_b262_01E00F50;

typedef struct {
    u8 pad0[4];
    s32 flags;
    u8 pad8[4];
    s16 count;
    s16 jitter;
    u8 pad10[0x10];
    Node_b262_01E00F50 *nodes;
    Glow_b262_01E00F50 *glow;
    Strand_b262_01E00F50 *sa;
    Strand_b262_01E00F50 *sb;
    s16 tick;
    s16 step;
    s16 fade;
    u8 ac;
    u8 aa;
    u8 ab;
} Bolt_b262_01E00F50;

extern void b262_01E00280(s32, void *, void *);
extern void b262_01E00940(s32, void *, void *);

static s32 func_01E00F50_b262(s32 ot, Bolt_b262_01E00F50 *o, s32 unused, Vec4f *p0, Vec4f *p1) {
    extern s32 func_0019A5C8(void);
    extern void func_001039A0(void *);
    extern void func_00103470(void *, u32, s32);
    s32 fa;
    s32 fb;
    s32 fc;
    s32 i;
    s32 k;
    s32 n;
    f32 t;
    f32 dx;
    f32 dy;
    f32 dz;

    fa = (u8)(o->aa / o->fade);
    fb = (u8)(o->ab / o->fade);
    fc = (u8)(o->ac / o->fade);
    if (o->count > 16) {
        o->count = 16;
    }
    if (o->tick == 0) {
        dx = p1->x - p0->x;
        dy = p1->y - p0->y;
        dz = p1->z - p0->z;
        for (i = 0; i < o->count; i++) {
            t = (f32)(i + 1) / (f32)o->count;
            if (o->jitter != 0) {
                o->nodes[i].pos.x = p0->x + dx * t + 0.1f * (f32)(func_0019A5C8() % (o->jitter * 2) - o->jitter);
                o->nodes[i].pos.y = p0->y + dy * t + 0.1f * (f32)(func_0019A5C8() % (o->jitter * 2) - o->jitter);
                o->nodes[i].pos.z = p0->z + dz * t + 0.1f * (f32)(func_0019A5C8() % (o->jitter * 2) - o->jitter);
            } else {
                o->nodes[i].pos.x = p0->x + dx * t;
                o->nodes[i].pos.y = p0->y + dy * t;
                o->nodes[i].pos.z = p0->z + dz * t;
            }
            if (i == 0) {
                func_001039A0(o->nodes);
            }
            if (func_00104520(o->flags, 0x18) != 0) {
                o->sa[i].a = o->aa;
                o->sb[i].a = o->ab;
                o->glow[i].a = o->ac;
            }
        }
    }
    n = o->tick / o->step + 1;
    if (o->count < n) {
        n = o->count;
    }
    for (i = 0; i < n; i++) {
        b262_01E00280(ot, &o->sa[i], &o->nodes[i]);
        b262_01E00280(ot, &o->sb[i], &o->nodes[i]);
        b262_01E00940(ot, &o->glow[i], &o->nodes[i]);
        if (func_00104520(o->flags, 0x18) != 0) {
            func_00103470(&o->sa[i].a, 0, fa);
            func_00103470(&o->sb[i].a, 0, fb);
            func_00103470(&o->glow[i].a, 0, fc);
        }
        for (k = 0; k < 64; k++) {
            o->glow[i].v[k].x += 0x80;
            o->glow[i].v[k].y += 0x80;
            o->glow[i].v[k].z += 0x80;
        }
    }
    o->tick++;
    if (o->tick > o->fade + o->step * o->count) {
        o->tick = 0;
    }
    return 0;
}
