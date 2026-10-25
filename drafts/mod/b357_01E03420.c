#include "common.h"

/* shape b357:01E03420, 267 insns: on start sits on the scene joint 0x38BA, life 5..9, size 5 + rand % the scene
   scale, and lays its slot's ten points (0xA0-byte slots at 0x2460) on three random sine turns stepping 18, at
   radius scale x (2..11), each jittered by -40..39; fades in by 0x60 for two ticks, then out by 0x27; blinks yellow
   (0xC0, 0xC0, 0x40) every third tick, else blue (0x40, 0x40, 0xC0) */

typedef struct {
    Vec4f p[10];
} Slot_b357_01E03420;

typedef struct {
    u8 pad0[0x2460];
    Slot_b357_01E03420 slot[1];
    u8 pad2500[0x38BA - 0x2500];
    s16 joint;
    u8 pad38BC[0x3AD4 - 0x38BC];
    u8 sin[4];
} Game_b357_01E03420;

typedef struct {
    s16 x, y, z;
    s16 life;
    s16 h8;
    s16 hA;
    s16 hC;
    u8 padE[0x1A];
    u8 col[4];
    u8 col2[4];
    s16 idx;
    s16 t;
    s16 h34;
    s16 mode;
    s16 size;
} Obj_b357_01E03420;

static s32 func_01E03420_b357(s32 arg0, s32 arg1) {
    Obj_b357_01E03420 *o = (Obj_b357_01E03420 *)arg1;
    Game_b357_01E03420 *g = (Game_b357_01E03420 *)arg0;
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    extern f32 func_001F5860(s32);
    Vec4f v;
    f32 sc;
    f32 r;
    s16 ra;
    s16 rb;
    s16 rc;
    s32 a;
    s32 b;
    s32 c;
    s16 i;

    if (o->mode == 1) {
        o->h34 = 0;
        o->mode = 2;
        o->h8 = 1;
        o->hA = 1;
        o->hC = 1;
        o->life = func_0019A5C8() % 5 + 5;
        func_001F5620(func_001F5380(), g->joint, &v);
        o->x = v.x;
        o->y = v.y;
        o->z = v.z;
        ra = func_0019A5C8() % 360;
        rb = func_0019A5C8() % 360;
        rc = func_0019A5C8() % 360;
        sc = func_001F5860(func_001F5380());
        o->size = func_0019A5C8() % (s16)sc + 5;
        a = ra;
        b = rb;
        c = rc;
        r = sc * (func_0019A5C8() % 10 + 2);
        for (i = 0; i < 10; i++) {
            g->slot[o->idx].p[i].y = r * func_00108030(g->sin, a, 1);
            g->slot[o->idx].p[i].z = r * func_00108030(g->sin, b, 0);
            g->slot[o->idx].p[i].x = r * func_00108030(g->sin, c, 0);
            g->slot[o->idx].p[i].x += func_0019A5C8() % 80 - 40;
            g->slot[o->idx].p[i].y += func_0019A5C8() % 80 - 40;
            a += 18;
            b += 18;
            c += 18;
            g->slot[o->idx].p[i].z += func_0019A5C8() % 80 - 40;
        }
    }
    if (o->t < 2) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x60;
        }
    } else if (o->col[3] > 0x28) {
        o->col[3] -= 0x27;
    } else {
        o->mode = 0;
    }
    if (o->t % 3 == 1) {
        func_001076F0(o->col, 0xC0, 0xC0, 0x40);
        func_001076F0(o->col2, 0xC0, 0xC0, 0x40);
    } else {
        func_001076F0(o->col, 0x40, 0x40, 0xC0);
        func_001076F0(o->col2, 0x40, 0x40, 0xC0);
    }
    o->t++;
    return 0;
}
