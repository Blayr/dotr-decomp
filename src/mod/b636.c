#include "common.h"

/* shape b008:01E00080, 273 insns, 45 copies: the 4-mode version of b003:01E00080 (texture coordinates of a
   sprite quad from a rectangle). Callers rely on it being static in their file. */

typedef struct Rect_b008_01E00080 {
    s16 x, y, w, h;
} Rect_b008_01E00080;

typedef struct Uv_b008_01E00080 {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad4;
    u64 xyz;
} Uv_b008_01E00080;

typedef struct Pk_b008_01E00080 {
    u8 pad0[0x18];
    Uv_b008_01E00080 c[4];
} Pk_b008_01E00080;

static void func_01E00080_b636(Pk_b008_01E00080 *p, Rect_b008_01E00080 *r, s32 mode) {
    if (mode == 0) {
        p->c[0].u = (r->x) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[1].u = (r->x + r->w) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[2].u = (r->x) << 4;
        p->c[2].v = (r->y + r->h) << 4;
        p->c[3].u = (r->x + r->w) << 4;
        p->c[3].v = (r->y + r->h) << 4;
    } else if (mode == 1) {
        p->c[0].u = (r->x) << 4;
        p->c[0].v = (r->y + r->h) << 4;
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y + r->h) << 4;
        p->c[3].u = (r->x + r->w) << 4;
        p->c[3].v = (r->y) << 4;
    } else if (mode == 2) {
        p->c[2].u = (r->x) << 4;
        p->c[2].v = (r->y) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y + r->h) << 4;
        p->c[1].u = (r->x + r->w) << 4;
        p->c[1].v = (r->y + r->h) << 4;
    } else {
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y + r->h) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y + r->h) << 4;
    }
}

/* shape b045:01E00E30, 224 insns: b018:01E005A0 with n taken as is, rot[1] = -(rot[1] / 180) instead of the
   object's rotation (no rotation for the world matrix), and func_00109100(m, rot, 0, self + 0xD8) per sprite; draws n textured sprites along a curve read from a per-frame table (three s8
   angle tables 0x64 apart), each scaled by obj->size. Calls the module's sprite-UV helper (shape
   b008:01E00080), included above as a static function: the call keeps pk in $a0 across it. */

typedef struct {
    f32 s;
    f32 t;
} St_b045_01E00E30;

typedef struct {
    s16 n;
    u16 nreg;
    s32 pad4;
    u64 regs;
    St_b045_01E00E30 st;
    u8 pad18[0xF];
    u8 q0;
    u8 pad28[0xF];
    u8 q1;
    u8 pad38[0xF];
    u8 q2;
    u8 pad48[0xF];
    u8 q3;
} Pk_b045_01E00E30;

typedef struct {
    s16 x, y, z;
    s16 pad6;
    s16 tab;
    s16 dy;
    s16 dz;
    s16 padE;
    s32 rx, ry, rz;
    u8 pad1C[0xC];
    u8 tex[8];
    s16 scale;
    u8 pad32[6];
    s16 size;
} Obj_b045_01E00E30;

static void func_01E004D0_b636(u8 *self, Obj_b045_01E00E30 *obj, Pk_b045_01E00E30 *pk, s8 *base) {
    extern void func_00108EF0();
    extern void func_00109100();
    f32 m[16];
    Vec4f pos;
    Vec4f scale;
    f32 depth[4];
    f32 world[16];
    s32 rot[4];
    St_b045_01E00E30 uv;
    s16 i;
    s16 n;
    s32 h;
    s8 *p;
    f32 r;
    f32 f;
    f32 fx;
    f32 fy;
    f32 fz;

    func_00207500();
    n = *(s16 *)(self + 0xB8);
    pk->nreg = 0x24;
    pk->n = 9;
    pk->regs = 0x24242421 | ((s64)4 << 32);
    pk->pad4 = 0;
    pk->nreg |= 0x800;
    func_002086D0(pk, 0x48 | ((s64)0x80 << 32));
    *(s32 *)&pk->st.t = 0;
    pk->q0 = 0;
    pk->q1 = 0;
    pk->q2 = 0;
    pk->q3 = 0;
    func_00107740(&uv, obj->tex);
    pk->st = uv;
    func_01E00080_b636((Pk_b008_01E00080 *)pk, (Rect_b008_01E00080 *)(self + 0x94), 0);
    func_00208700(pk, *(void **)(self + 0x88), 1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    rot[1] /= 180;
    rot[1] = -rot[1];
    fx = obj->tab;
    fy = obj->dy;
    fz = obj->dz;
    fx /= 10.0f;
    fy /= 10.0f;
    fz /= 10.0f;
    pos.x = obj->x + fx;
    pos.y = obj->y + fy;
    pos.z = obj->z + fz;
    func_00108EF0(world, &scale, 0, &pos);
    for (i = 0; i < n; i++) {
        r = obj->size;
        func_00108CE0(m, r, r);
        func_00109100(m, rot, 0, self + 0xD8);
        p = base + i;
        h = i >> 1;
        f = p[obj->tab];
        f /= 20.0f;
        func_00107070(m, 0, f * (obj->scale + h));
        f = p[obj->tab + 100];
        f /= 20.0f;
        func_00107070(m, 1, f * (obj->scale + h));
        f = p[obj->tab + 180];
        f /= 20.0f;
        func_00107070(m, 2, f * (obj->scale + h));
        if (func_00205630((s32)m, 0x70000000, (s32)world, (s32)pk, depth) != 0) {
            func_002075F0((s32)pk, *(s32 *)(self + 0x80), func_001A23B0(depth[0]));
        }
    }
}

/* shape b636:01E00850, 136 insns: scene spawn step: red scene colour; t++; frame 51 stores joint B's point; frames
   52..64 copy it into the spawn point (six times); before frame 106 one 0x1E00A70 a tick at joint A raised 1; frames
   107..304 one 0x1E00C50 at joint A raised 4, plus one 0x1E00E60 every fourth frame */

typedef struct {
    u8 pad0[0x2D0];
    Vec4f pos;
    u8 pad2E0[0x33E0];
    Vec4f pt;
    u8 pad36D0[0xD4];
    u8 col[4];
    u8 pad37A8[0x40];
    s16 ja;
    s16 jb;
    u8 pad37EC[0x12];
    s16 t;
} Scene_b636_01E00850;

static void func_01E00850_b636(Scene_b636_01E00850 *g) {
    extern void b636_01E00A70(void);
    extern void b636_01E00C50(void);
    extern void b636_01E00E60(void);
    extern void b636_01E01650(void *, void *, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    Vec4f v;
    s32 i;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->t++;
    if (g->t == 0x33) {
        func_001F5620(func_001F53A0(), g->jb, &g->pt);
    }
    if (g->t > 0x33 && g->t < 0x41) {
        func_001F5620(func_001F53A0(), g->jb, &v);
        for (i = 0; i < 6; i++) {
            g->pos.x = g->pt.x;
            g->pos.y = g->pt.y;
            g->pos.z = g->pt.z;
        }
    }
    if (g->t < 0x6A) {
        func_001F5620(func_001F53A0(), g->ja, &v);
        g->pos.x = v.x;
        g->pos.y = 1.0f + v.y;
        g->pos.z = v.z;
        b636_01E01650(g, b636_01E00A70, 0);
    }
    if (g->t > 0x6A && g->t < 0x131) {
        func_001F5620(func_001F53A0(), g->ja, &v);
        g->pos.x = v.x;
        g->pos.y = 4.0f + v.y;
        g->pos.z = v.z;
        b636_01E01650(g, b636_01E00C50, 0);
    }
    if (g->t % 4 == 1 && g->t > 0x6A && g->t < 0x131) {
        func_001F5620(func_001F53A0(), g->ja, &v);
        g->pos.x = v.x;
        g->pos.y = 4.0f + v.y;
        g->pos.z = v.z;
        b636_01E01650(g, b636_01E00E60, 0);
    }
}

/* func_001076F0 takes plain ints here (functions.h says s8): hide that prototype */

/* OVL_WARM */

/* shape b636:01E00A70, 119 insns: spark pinned to a scene object with random spin and life; bigger early in the scene */

typedef struct Sp_b636_01E00A70 {
    s16 x, y, z;
    s16 life;
    s16 h8;
    u8 padA[4];
    s16 spin;
    u8 pad10[4];
    s32 f14;
    u8 pad18[0x10];
    u8 c28[4];
    u8 c2C[4];
    s16 rot;
    s16 age;
    s16 h34;
    s16 state;
    s16 h38;
    s16 h3A;
} Sp_b636_01E00A70;

typedef struct Scn_b636_01E00A70 {
    u8 pad0[0x37E8];
    s16 id;
    u8 pad37EA[0x14];
    s16 timer;
} Scn_b636_01E00A70;

static s32 func_01E00A70_b636(Scn_b636_01E00A70 *w, Sp_b636_01E00A70 *o) {
    extern s32 func_001076F0();
    extern s32 func_001F53A0();
    extern void func_001F5620();
    Vec4f v;

    if (o->state == 1) {
        if (w->timer < 0x54) {
            o->h38 = 0x19;
        } else {
            o->h38 = 5;
        }
        o->h34 = func_0019A5C8() % 8;
        o->f14 = func_0019A5C8() % 0xFFFF;
        func_001076F0(o->c28, 0x30, 8, 0x80);
        o->rot = 0;
        o->h3A = func_0019A5C8() % 360;
        o->spin = func_0019A5C8() % 25 + 10;
        o->h8 = func_0019A5C8() % 10;
        o->life = func_0019A5C8() % 7 + 2;
        o->state = 2;
    }
    if (o->age < o->life) {
        if (o->c28[3] < 0x61) {
            o->c28[3] += 0x30;
        }
    } else if (o->c28[3] > 0x10) {
        o->c28[3] -= 0xA;
    } else {
        o->state = 0;
    }
    if (o->age != 0) {
        o->rot += o->spin;
    }
    o->age++;
    func_001F5620(func_001F53A0(), w->id, &v);
    o->x = (s32)v.x;
    o->y = (s32)v.y;
    o->z = (s32)v.z;
    return 0;
}

/* shape b636:01E00C50, 130 insns: a blue spark (size 100 growing 5, frame 0..7, random turn, f30 growing 10..34, f8 0..9) held 11..18 ticks (alpha up by 48), then down by 10; h4 sways by 5 x the sine of the model angle - 180 */

typedef struct {
    u8 pad0[0x3A04];
    u8 trig[1];
} Game_b636_01E00C50;

typedef struct {
    u8 pad0[4];
    s16 h4;
    s16 hold;
    s16 f8;
    u8 padA[4];
    s16 speed;
    u8 pad10[4];
    s32 rot;
    u8 pad18[0x10];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b636_01E00C50;

static s32 func_01E00C50_b636(Game_b636_01E00C50 *g, Fx_b636_01E00C50 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F6160(s32, void *);
    extern f32 func_00108030(void *, s32, s32);
    s32 ang[4];
    s32 d;

    if (o->mode == 1) {
        o->f38 = 100;
        o->f34 = func_0019A5C8() % 8;
        o->rot = func_0019A5C8() % 65535;
        func_001076F0(o->col, 0x30, 8, 0x80);
        o->f30 = 0;
        o->f3A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 25 + 10;
        o->f8 = func_0019A5C8() % 10;
        o->hold = func_0019A5C8() % 8 + 11;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] <= 0x60) {
            o->col[3] += 0x30;
        }
    } else if (o->col[3] > 16) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->f30 += o->speed;
    }
    o->tick++;
    func_001F6160(func_001F53A0(), ang);
    d = (s16)(5.0f * -func_00108030(g->trig, (s16)(ang[1] / 180.0f) - 180, 1));
    o->h4 += d;
    o->f38 += 5;
    return 0;
}

/* shape b636:01E00E60, 130 insns: b636:01E00C50 in red (size 110, held 12..19 ticks, sway 6) */

typedef struct {
    u8 pad0[0x3A04];
    u8 trig[1];
} Game_b636_01E00E60;

typedef struct {
    u8 pad0[4];
    s16 h4;
    s16 hold;
    s16 f8;
    u8 padA[4];
    s16 speed;
    u8 pad10[4];
    s32 rot;
    u8 pad18[0x10];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b636_01E00E60;

static s32 func_01E00E60_b636(Game_b636_01E00E60 *g, Fx_b636_01E00E60 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F6160(s32, void *);
    extern f32 func_00108030(void *, s32, s32);
    s32 ang[4];
    s32 d;

    if (o->mode == 1) {
        o->f38 = 110;
        o->f34 = func_0019A5C8() % 8;
        o->rot = func_0019A5C8() % 65535;
        func_001076F0(o->col, 0x80, 8, 0x30);
        o->f30 = 0;
        o->f3A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 25 + 10;
        o->f8 = func_0019A5C8() % 10;
        o->hold = func_0019A5C8() % 8 + 12;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] <= 0x60) {
            o->col[3] += 0x30;
        }
    } else if (o->col[3] > 16) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->f30 += o->speed;
    }
    o->tick++;
    func_001F6160(func_001F53A0(), ang);
    d = (s16)(6.0f * -func_00108030(g->trig, (s16)(ang[1] / 180.0f) - 180, 1));
    o->h4 += d;
    o->f38 += 5;
    return 0;
}

/* shape b636:01E01070, 41 insns: look up the textures: group 4 cells 0-2, group 4 cells 13-15, group 5
   cells 0-2 (variant of b205:01E02370) */

typedef struct {
    u8 pad0[0x340];
    s32 tex[16];
    u8 pad380[0x3400];
    s32 tex5[3];
} Scene_b636_01E01070;

static void func_01E01070_b636(s32 arg0, Scene_b636_01E01070 *o) {
    s32 i;

    for (i = 0; i < 3; i++) {
        o->tex[i] = func_00202BF0(4, i);
    }
    for (i = 13; i < 16; i++) {
        o->tex[i] = func_00202BF0(4, i);
    }
    for (i = 0; i < 3; i++) {
        o->tex5[i] = func_00202BF0(5, i);
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b636", func_01E01120_b636);

/* shape b636:01E01650, 72 insns: twin of b046:01E03E20: take the first free slot of the 200-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0x37FA and the two arguments; returns 1 if a
   slot was found */

typedef struct {
    u8 pad[0x20];
    s32 b;
    s32 a;
    u8 c0[4];
    u8 c1[4];
    s16 v;
    u8 pad32[0x4];
    s16 used;
    u8 pad38[0x8];
} Slot_b636_01E01650;

typedef struct {
    u8 pad[0x2D0];
    u8 m[0x1A8];
    Slot_b636_01E01650 s[200];
    u8 pad3678[0x12C];
    u8 r, g, b, a;
    u8 pad37A8[0x52];
    s16 v;
} Pool_b636_01E01650;

static s32 func_01E01650_b636(Pool_b636_01E01650 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b636_01E01650 *s = NULL;
    s16 i;
    s32 ret;

    for (i = 0; i < 200; i++) {
        if (o->s[i].used == 0) {
            func_00195108(&o->s[i], 0x40);
            o->s[i].used = 1;
            s = &o->s[i];
            i = 200;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c0, o->r, o->g, o->b);
        s->c0[3] = o->a;
        func_001076F0(s->c1, o->r, o->g, o->b);
        s->c1[3] = o->a;
        func_00106AB0(s, o->m, 0);
        ret = 1;
        s->v = o->v;
        s->b = b;
        s->a = a;
    } else {
        ret = 0;
    }
    return ret;
}
