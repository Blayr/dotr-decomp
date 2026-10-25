#include "common.h"

/* shape b003:01E00080, 552 insns, 183 copies: the module's first function. Texture coordinates of a
   sprite quad from a rectangle, in one of 8 corner orders (flips and quarter turns). Callers in the same
   file rely on it leaving $a0 alone, so it must stay in their file. */

typedef struct Rect_b003_01E00080 {
    s16 x, y, w, h;
} Rect_b003_01E00080;

typedef struct Uv_b003_01E00080 {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad4;
    u64 xyz;
} Uv_b003_01E00080;

typedef struct Pk_b003_01E00080 {
    u8 pad0[0x18];
    Uv_b003_01E00080 c[4];
} Pk_b003_01E00080;


/* static in its module (callers that include this file #define OVL_LOCAL static first) */

static void func_01E00080_b570(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y) << 4;
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y + r->h) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y + r->h) << 4;
    } else if (mode == 2) {
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y + r->h) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y + r->h) << 4;
    } else if (mode == 3) {
        p->c[2].u = (r->x) << 4;
        p->c[2].v = (r->y) << 4;
        p->c[3].u = (r->x + r->w) << 4;
        p->c[3].v = (r->y) << 4;
        p->c[0].u = (r->x) << 4;
        p->c[0].v = (r->y + r->h) << 4;
        p->c[1].u = (r->x + r->w) << 4;
        p->c[1].v = (r->y + r->h) << 4;
    } else if (mode == 4) {
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[3].u = (r->x + r->w) << 4;
        p->c[3].v = (r->y) << 4;
        p->c[0].u = (r->x) << 4;
        p->c[0].v = (r->y + r->h) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y + r->h) << 4;
    } else if (mode == 5) {
        p->c[2].u = (r->x) << 4;
        p->c[2].v = (r->y) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y + r->h) << 4;
        p->c[1].u = (r->x + r->w) << 4;
        p->c[1].v = (r->y + r->h) << 4;
    } else if (mode == 6) {
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y) << 4;
        p->c[1].u = (r->x + r->w) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[2].u = (r->x) << 4;
        p->c[2].v = (r->y + r->h) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y + r->h) << 4;
    } else if (mode == 7) {
        p->c[0].u = (r->x) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y) << 4;
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y + r->h) << 4;
        p->c[3].u = (r->x + r->w) << 4;
        p->c[3].v = (r->y + r->h) << 4;
    }
}

/* shape b003:01E00920, 352 insns: b003:01E00EA0 placed at the def's s16 position instead of the object's; draws obj->count sprites along a curve read from three s8 tables
   (0x64 apart), each turned by the object's angles; mode (flags & 0xF) 0 = depth from the projection,
   1 = far z, 2 = -1. Calls the module's sprite-UV helper (shape b003:01E00080) as a static function. */

typedef struct {
    u8 pad0[0x20];
    Vec4f pos;
    u8 pad30[0x50];
    s32 f80;
    u8 pad84[4];
    void *f88;
    u8 pad8C[8];
    u8 f94[0x24];
    s16 count;
    u8 padBA[6];
    s16 fC0;
    u8 padC2[0x16];
    u8 fD8[4];
} Obj_b003_01E00920;

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 tab;
    u8 padA[0x1E];
    u8 tex[8];
    s16 scale;
    u8 pad32[6];
    s16 size;
    s16 angle;
} Def_b003_01E00920;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b003_01E00920;

typedef struct {
    f32 u, v;
} Uv_b003_01E00920;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b003_01E00920 uv;
    u64 pad18;
    Xyz_b003_01E00920 v[4];
    u64 pad60[6];
} Pk_b003_01E00920;

typedef struct {
    u64 tag;
    Pk_b003_01E00920 pk;
} Buf_b003_01E00920;

static void func_01E00920_b570(Obj_b003_01E00920 *obj, Def_b003_01E00920 *def, s32 flags, s8 *base) {
    f32 m2[4][4];
    f32 d[4];
    Vec4f pos;
    Vec4f s;
    f32 out[4];
    f32 m[4][4];
    s32 rot[4];
    s32 rot2[4];
    Buf_b003_01E00920 buf;
    Uv_b003_01E00920 uv;
    s16 sel;
    s16 i;
    Pk_b003_01E00920 *p;
    s32 mode;
    s32 h;
    s8 *t;
    f32 f;
    f32 r;
    extern void func_00108EF0();
    extern void func_00108950();
    extern void func_00109100();

    func_00207500();
    p = &buf.pk;
    p->flags = 0x24;
    p->size = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad4 = 0;
    p->flags |= 0x800;
    sel = flags >> 4;
    if (sel == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((s64)sel << 2) | (((u64)0x80 << 32) | 0x40));
    }
    func_00107740(&uv, def->tex);
    p->uv = uv;
    func_00208700(p, obj->f88, 1);
    s.x = 0.1f;
    s.y = 0.1f;
    s.z = 0.1f;
    func_00205C40((s32)rot);
    rot[1] /= 180;
    rot[1] = -rot[1];
    rot[0] /= 180;
    rot[0] = -rot[0];
    rot2[2] = def->angle;
    pos.x = def->x;
    pos.y = def->y;
    pos.z = def->z;
    func_00108EF0(m, &s, NULL, &pos);
    mode = flags & 0xF;
    for (i = 0; i < obj->count; i++) {
        func_01E00080_b570((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fC0);
        r = def->size;
        func_00108CE0(m2, r, r);
        func_00109100(m2, rot, 1, obj->fD8);
        func_00109100(m2, rot, 0, obj->fD8);
        t = base + i;
        h = i >> 1;
        f = t[def->tab];
        f /= 20.0f;
        d[0] = f * (def->scale + h);
        f = t[def->tab + 100];
        f /= 20.0f;
        d[1] = f * (def->scale + h);
        func_00108950(d, rot2, 2, obj->fD8);
        m2[0][0] += d[0];
        m2[1][0] += d[0];
        m2[2][0] += d[0];
        m2[3][0] += d[0];
        m2[0][1] += d[1];
        m2[1][1] += d[1];
        m2[2][1] += d[1];
        m2[3][1] += d[1];
        f = t[def->tab + 180];
        f /= 20.0f;
        d[2] = f * (def->scale + h);
        m2[0][2] += d[2];
        m2[1][2] += d[2];
        m2[2][2] += d[2];
        m2[3][2] += d[2];
        if (mode == 0) {
            if (func_00205630((s32)m2, 0x70000000, (s32)m, (s32)p, out) != 0) {
                func_002075F0((s32)p, obj->f80, func_001A23B0(out[0]));
            }
        } else if (mode == 1) {
            if (func_00205630((s32)m2, 0x70000000, (s32)m, (s32)p, out) != 0) {
                p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
                func_002075F0((s32)p, obj->f80, 0);
            }
        } else if (mode == 2) {
            if (func_00205630((s32)m2, 0x70000000, (s32)m, (s32)p, out) != 0) {
                func_002075F0((s32)p, obj->f80, -1);
            }
        }
    }
}

/* shape b003:01E00EA0, 342 insns, 15 copies: draws obj->count sprites along a curve read from three s8 tables
   (0x64 apart), each turned by the object's angles; mode (flags & 0xF) 0 = depth from the projection,
   1 = far z, 2 = -1. Calls the module's sprite-UV helper (shape b003:01E00080) as a static function. */

typedef struct {
    u8 pad0[0x20];
    Vec4f pos;
    u8 pad30[0x50];
    s32 f80;
    u8 pad84[4];
    void *f88;
    u8 pad8C[8];
    u8 f94[0x24];
    s16 count;
    u8 padBA[6];
    s16 fC0;
    u8 padC2[0x16];
    u8 fD8[4];
} Obj_b003_01E00EA0;

typedef struct {
    u8 pad0[8];
    s16 tab;
    u8 padA[0x1E];
    u8 tex[8];
    s16 scale;
    u8 pad32[6];
    s16 size;
    s16 angle;
} Def_b003_01E00EA0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b003_01E00EA0;

typedef struct {
    f32 u, v;
} Uv_b003_01E00EA0;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b003_01E00EA0 uv;
    u64 pad18;
    Xyz_b003_01E00EA0 v[4];
    u64 pad60[6];
} Pk_b003_01E00EA0;

typedef struct {
    u64 tag;
    Pk_b003_01E00EA0 pk;
} Buf_b003_01E00EA0;

static void func_01E00EA0_b570(Obj_b003_01E00EA0 *obj, Def_b003_01E00EA0 *def, s32 flags, s8 *base) {
    f32 m2[4][4];
    f32 d[4];
    Vec4f pos;
    Vec4f s;
    f32 out[4];
    f32 m[4][4];
    s32 rot[4];
    s32 rot2[4];
    Buf_b003_01E00EA0 buf;
    Uv_b003_01E00EA0 uv;
    s16 sel;
    s16 i;
    Pk_b003_01E00EA0 *p;
    s32 mode;
    s32 h;
    s8 *t;
    f32 f;
    f32 r;
    extern void func_00108EF0();
    extern void func_00108950();
    extern void func_00109100();

    func_00207500();
    p = &buf.pk;
    p->flags = 0x24;
    p->size = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad4 = 0;
    p->flags |= 0x800;
    sel = flags >> 4;
    if (sel == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((s64)sel << 2) | (((u64)0x80 << 32) | 0x40));
    }
    func_00107740(&uv, def->tex);
    p->uv = uv;
    func_00208700(p, obj->f88, 1);
    s.x = 0.1f;
    s.y = 0.1f;
    s.z = 0.1f;
    func_00205C40((s32)rot);
    rot[1] /= 180;
    rot[1] = -rot[1];
    rot[0] /= 180;
    rot[0] = -rot[0];
    rot2[2] = def->angle;
    pos.x = obj->pos.x;
    pos.y = obj->pos.y;
    pos.z = obj->pos.z;
    func_00108EF0(m, &s, NULL, &pos);
    mode = flags & 0xF;
    for (i = 0; i < obj->count; i++) {
        func_01E00080_b570((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fC0);
        r = def->size;
        func_00108CE0(m2, r, r);
        func_00109100(m2, rot, 1, obj->fD8);
        func_00109100(m2, rot, 0, obj->fD8);
        t = base + i;
        h = i >> 1;
        f = t[def->tab];
        f /= 20.0f;
        d[0] = f * (def->scale + h);
        f = t[def->tab + 100];
        f /= 20.0f;
        d[1] = f * (def->scale + h);
        func_00108950(d, rot2, 2, obj->fD8);
        m2[0][0] += d[0];
        m2[1][0] += d[0];
        m2[2][0] += d[0];
        m2[3][0] += d[0];
        m2[0][1] += d[1];
        m2[1][1] += d[1];
        m2[2][1] += d[1];
        m2[3][1] += d[1];
        f = t[def->tab + 180];
        f /= 20.0f;
        d[2] = f * (def->scale + h);
        m2[0][2] += d[2];
        m2[1][2] += d[2];
        m2[2][2] += d[2];
        m2[3][2] += d[2];
        if (mode == 0) {
            if (func_00205630((s32)m2, 0x70000000, (s32)m, (s32)p, out) != 0) {
                func_002075F0((s32)p, obj->f80, func_001A23B0(out[0]));
            }
        } else if (mode == 1) {
            if (func_00205630((s32)m2, 0x70000000, (s32)m, (s32)p, out) != 0) {
                p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
                func_002075F0((s32)p, obj->f80, 0);
            }
        } else if (mode == 2) {
            if (func_00205630((s32)m2, 0x70000000, (s32)m, (s32)p, out) != 0) {
                func_002075F0((s32)p, obj->f80, -1);
            }
        }
    }
}

/* shape b016:01E00ED0, 175 insns, 99 copies: draw one sprite quad (GS packet of 9 qwords) at an object's
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b570 in the
   same file and static (the original reuses $a0 across the call). The colour is passed by value. */

typedef struct Cam_b016_01E00ED0 {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[0x14];
    Vec4f pos;
    u8 pad30[0x30];
    Vec4f at;
} Cam_b016_01E00ED0;

typedef struct Obj_b016_01E00ED0 {
    u8 pad0[0x80];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    u8 f94[0x2A];
    s16 fBE;
} Obj_b016_01E00ED0;

typedef struct Xyz_b016_01E00ED0 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b016_01E00ED0;

typedef struct Uv_b016_01E00ED0 {
    f32 u, v;
} Uv_b016_01E00ED0;

typedef struct Pk_b016_01E00ED0 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b016_01E00ED0 uv;
    u64 pad18;
    Xyz_b016_01E00ED0 v[4];
    u64 pad60[6];
} Pk_b016_01E00ED0;

typedef struct Buf_b016_01E00ED0 {
    u64 tag;
    Pk_b016_01E00ED0 pk;
} Buf_b016_01E00ED0;

static void func_01E01400_b570(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
    extern void func_00108EF0();
    f32 view[4][4];
    Vec4f a;
    Vec4f s;
    f32 out[4];
    f32 m[4][4];
    Buf_b016_01E00ED0 buf;
    Uv_b016_01E00ED0 uv;
    s32 sel;
    s32 mode;
    Pk_b016_01E00ED0 *p = &buf.pk;

    sel = (flags >> 4) & 0xF;
    p->flags = 0x24;
    p->size = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad4 = 0;
    p->flags |= 0x800;
    if (sel == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((s64)sel << 2) | (((u64)0x80 << 32) | 0x40));
    }
    func_00107740(&uv, &cam->at);
    p->uv = uv;
    func_01E00080_b570((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
    func_00208700(p, (void *)obj->f88, 1);
    s.x = 0.1f;
    a.x = c.x;
    s.y = 0.1f;
    a.y = c.y;
    s.z = 0.1f;
    a.z = c.z;
    func_00108EF0(m, &s, &cam->pos, &a);
    func_00108CE0(view, cam->w, cam->h);
    if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, out) != 0) {
        mode = flags & 0xF;
        if (mode == 0) {
            func_002075F0((s32)p, obj->f80, func_001A23B0(out[0]));
        } else if (mode == 1) {
            p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
            func_002075F0((s32)p, obj->f80, 0);
        } else {
            func_002075F0((s32)p, obj->f80, -1);
        }
    }
}

/* shape b570:01E016C0, 348 insns: the b570 scene's script (scene colour red): on ticks 319..349 a 02680 at joint
   0x9F6E and that joint's point into the 200-step trail ring; on ticks 121..284 a puff (01C30) at joint 0x9F6C nudged
   4.5 along z by the side flag, with a 200-step ring index; on ticks 121..299 a 028B0 at joint 0x9F68 (2 up, 1 along
   z); before tick 250 a 020A0 halfway between joints 0x9F68 and 0x9F6A (variant 1 every fifth tick, else 2); on ticks
   191..349 except every seventh a 02280 at a random one of eight joints */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0x34A0 - 0x260];
    Vec4f trail[200];
    u8 pad4120[0x98F4 - 0x4120];
    u8 col[4];
    u8 pad98F8[0x9F68 - 0x98F8];
    s16 jC;
    s16 jD;
    s16 jB;
    s16 jA;
    u8 pad9F70[4];
    s16 jt[8];
    u8 pad9F84[4];
    s16 k;
    s16 m;
    u8 pad9F8C[4];
    s16 ring;
    u8 pad9F92[2];
    s16 flag;
    s16 tick;
} Ctx_b570_01E016C0;

static void func_01E016C0_b570(Ctx_b570_01E016C0 *g) {
    extern s32 b570_01E01C30();
    extern s32 b570_01E020A0();
    extern s32 b570_01E02280();
    extern s32 b570_01E02680();
    extern s32 b570_01E028B0();
    extern void b570_01E03B40(Ctx_b570_01E016C0 *, void *, s32);
    extern void b570_01E03CB0(Ctx_b570_01E016C0 *, void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    Vec4f a;
    Vec4f b;
    Vec4f *pb;
    s32 i;
    s32 r;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->tick++;
    if (g->tick > 318 && g->tick < 350) {
        func_001F5620(func_001F53A0(), g->jA, &a);
        g->pos.x = a.x;
        g->pos.y = a.y;
        g->pos.z = a.z;
        b570_01E03CB0(g, b570_01E02680, 0);
    }
    if (g->tick > 120 && g->tick < 285) {
        func_001F5620(func_001F53A0(), g->jB, &a);
        g->pos.x = a.x;
        g->pos.y = a.y;
        if (g->flag != 0) {
            g->pos.z = 4.5f + a.z;
        } else {
            g->pos.z = a.z - 4.5f;
        }
        g->ring = g->k;
        for (i = 0; i < 1; i++) {
            b570_01E03B40(g, b570_01E01C30, 0);
        }
        g->k++;
        if (g->k >= 200) {
            g->k = 0;
        }
    }
    if (g->tick > 120 && g->tick < 300) {
        func_001F5620(func_001F53A0(), g->jC, &a);
        g->pos.x = a.x;
        g->pos.y = 2.0f + a.y;
        if (g->flag != 0) {
            g->pos.z = a.z - 1.0f;
        } else {
            g->pos.z = 1.0f + a.z;
        }
        b570_01E03CB0(g, b570_01E028B0, 0);
    }
    if (g->tick < 250) {
        func_001F5620(func_001F53A0(), g->jC, &a);
        func_001F5620(func_001F53A0(), g->jD, pb = &b);
        pb->x = (pb->x - a.x) / 2.0f;
        b.y = (b.y - a.y) / 2.0f;
        b.z = (b.z - a.z) / 2.0f;
        g->pos.x = a.x + pb->x;
        g->pos.y = a.y + b.y;
        g->pos.z = a.z + b.z;
        if (g->tick % 5 == 1) {
            g->ring = 1;
        } else {
            g->ring = 2;
        }
        for (i = 0; i < 1; i++) {
            b570_01E03B40(g, b570_01E020A0, 0);
        }
    }
    if (g->tick > 318 && g->tick < 350) {
        func_001F5620(func_001F53A0(), g->jA, &g->trail[g->m]);
        g->ring = g->m;
        g->m++;
        if (g->m >= 200) {
            g->m = 0;
        }
    }
    if (g->tick > 190 && g->tick < 350 && g->tick % 7 != 1) {
        r = func_0019A5C8() % 8;
        func_001F5620(func_001F5380(), g->jt[r], &a);
        g->pos.x = a.x;
        g->pos.y = a.y;
        g->pos.z = a.z;
        b570_01E03B40(g, b570_01E02280, 0);
    }
}

/* shape b570:01E01C30, 284 insns: a magenta puff on the world's trail: on start a random size 12..23, colour 80/10/FF,
   claims trail point a30 at its spot (x less 0.7), random heading, speed 2..6, h8, life 37..61 and the reach between
   the two models' joints; fades in until its life (or tick 314), then out; follows the second model's depth and sinks
   0.02 a tick; frame and size climb every other tick, random spin, heading swings by the speed's parity */

typedef struct {
    u8 pad0[0x9914];
    f32 x[200];
    f32 y[204];
    s16 j0;
    s16 j1;
} World_b570_01E01C30;

typedef struct {
    u8 pad0[2];
    s16 x;
    s16 y;
    s16 life;
    s16 h8;
    s16 idx;
    s16 reach;
    s16 speed;
    s32 r10;
    s32 r14;
    s32 r18;
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 a30;
    s16 t;
    s16 frame;
    s16 state;
    s16 size;
    s16 ang;
} Puff_b570_01E01C30;

static s32 func_01E01C30_b570(World_b570_01E01C30 *w, Puff_b570_01E01C30 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F5380(void);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    Vec4f a;
    Vec4f b[2];
    Vec4f *pb;

    if (o->state == 1) {
        o->size = func_0019A5C8() % 12 + 12;
        o->frame = 0;
        func_001076F0(o->col, 0x80, 0x10, 0xFF);
        o->idx = o->a30;
        w->x[o->idx] = o->x;
        w->y[o->idx] = o->y;
        w->x[o->idx] -= 0.7f;
        o->a30 = 0;
        o->ang = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 5 + 2;
        o->h8 = func_0019A5C8() % 35;
        o->life = func_0019A5C8() % 25 + 37;
        func_001F5620(func_001F53A0(), w->j0, &a);
        func_001F5620(func_001F53A0(), w->j1, pb = b);
        o->reach = pb->x - a.x;
        o->state = 2;
    }
    if (o->t < o->life) {
        if (o->t < 314) {
            if (o->col[3] <= 0x80) {
                o->col[3] += 0x40;
            }
        }
    } else if (o->t < 314) {
        if (o->col[3] > 8) {
            o->col[3] -= 7;
        } else {
            o->state = 0;
        }
    }
    if (o->t > 314) {
        if (o->col[3] > 10) {
            o->col[3] -= 9;
        } else {
            o->state = 0;
        }
    }
    if (o->t != 0) {
        if (o->size < 60) {
            o->size += 2;
        }
    }
    func_001F5F90(func_001F5380(), &a);
    func_001F5F90(func_001F53A0(), b);
    if (o->t != 0) {
        a.z -= b[0].z;
        a.z /= 70.0f;
        w->y[o->idx] += a.z;
    }
    w->x[o->idx] -= 0.02f;
    if (o->t % 2 == 1) {
        if (o->frame < 5) {
            o->frame++;
        }
    }
    o->a30 += o->speed;
    if (o->t % 2 == 1) {
        o->size += 3;
    }
    o->r10 = func_0019A5C8() % 360;
    o->r14 = func_0019A5C8() % 360;
    if (o->speed % 2 == 1) {
        o->ang += 2;
    } else {
        o->ang -= 2;
    }
    o->r18 = func_0019A5C8() % 360;
    o->t++;
    return 0;
}

/* shape b570:01E020A0, 107 insns: on start 0x38 = 20, variant 0, colour 0x70 grey, 0xA keeps the old 0x30, 0x30 = 0, speed
   5..9 (0xE), 0x8 0..24, hold 30..39 (0x6), random 0x3A, 0xC = 0; alpha grows by 0x20 (below 0x40) during the
   hold, then fades by 9 and stops; the variant counts up to 5 every other tick; after the first tick 0x30 grows by
   the speed and 0x38 by 1 */

typedef struct {
    u8 pad0[2];
    s16 f2;
    u8 pad4[2];
    s16 hold;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 speed;
    u8 pad10[0x18];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b570_01E020A0;

static s32 func_01E020A0_b570(s32 arg0, Fx_b570_01E020A0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 20;
        o->f34 = 0;
        func_001076F0(o->col, 0x70, 0x70, 0x70);
        o->fA = o->f30;
        o->f30 = 0;
        o->speed = func_0019A5C8() % 5 + 5;
        o->f8 = func_0019A5C8() % 25;
        o->hold = func_0019A5C8() % 10 + 30;
        o->f3A = func_0019A5C8() % 360;
        o->fC = 0;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0x40) {
            o->col[3] += 0x20;
        }
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->tick % 2 == 1) {
        if (o->f34 < 5) {
            o->f34++;
        }
    }
    if (o->tick != 0) {
        o->f30 += o->speed;
    }
    if (o->tick != 0) {
        o->f38++;
    }
    o->tick++;
    return 0;
}

/* shape b570:01E02250, 9 insns: hand the module's table at 0x01E03F00 to func_00199B50, return 0 */

extern u8 D_01E03F00_b570[];

static s32 func_01E02250_b570(void) {
    func_00199B50(D_01E03F00_b570);
    return 0;
}

/* shape b570:01E02280, 107 insns: on start 0x38 = 50, variant 0, colour white, 0xA keeps the old 0x30, 0x30 = 0, speed
   4 (0xE), 0x8 0..24, hold 0..14 (0x6), random 0x3A, 0xC = 0; alpha grows by 0x40 (below 0x80) during the hold, then
   fades by 13 and stops; after the first tick 0x38 grows by 2; the variant counts up to 3 every other tick; after the
   first tick 0x30 grows by the speed and 0x2 by 1 */

typedef struct {
    u8 pad0[2];
    s16 f2;
    u8 pad4[2];
    s16 hold;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 speed;
    u8 pad10[0x18];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b570_01E02280;

static s32 func_01E02280_b570(s32 arg0, Fx_b570_01E02280 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 50;
        o->f34 = 0;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->fA = o->f30;
        o->f30 = 0;
        o->speed = 4;
        o->f8 = func_0019A5C8() % 25;
        o->hold = func_0019A5C8() % 8 + 7;
        o->f3A = func_0019A5C8() % 360;
        o->fC = 0;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0xC) {
        o->col[3] -= 13;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->f38 += 2;
    }
    if (o->tick % 2 == 1) {
        if (o->f34 < 3) {
            o->f34++;
        }
    }
    if (o->tick != 0) {
        o->f30 += o->speed;
    }
    if (o->tick != 0) {
        o->f2++;
    }
    o->tick++;
    return 0;
}

/* shape b003:01E01EC0, 146 insns, 4 copies: step of a rising puff: on state 1 sets a grey colour, random start, angle,
   size, layers and lifetime; fades in by 0x12, then out by 9 until it ends; grows, climbs and spins randomly. */

typedef struct {
    s16 x, y, z;
    s16 life;
    s16 h8;
    u8 padA[2];
    s16 layers;
    s16 speed;
    s32 rot[3];
    u8 pad1C[0xC];
    u8 c0[4];
    u8 pad2C[4];
    s16 pos;
    s16 t;
    s16 h34;
    s16 state;
    s16 size;
    s16 ang;
} Obj_b003_01E01EC0;

static s32 func_01E02430_b570(void *arg0, Obj_b003_01E01EC0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = 0x2D;
        o->h34 = 0;
        func_001076F0(o->c0, 0x20, 0x20, 0x20);
        o->pos = func_0019A5C8() % 300 + 130;
        o->ang = func_0019A5C8() % 360;
        o->speed = 0;
        o->h8 = func_0019A5C8() % 35;
        o->layers = func_0019A5C8() % 3 + 2;
        o->life = func_0019A5C8() % 10 + 15;
        o->state = 2;
    }
    if (o->t < o->life) {
        if (o->c0[3] <= 0x80) {
            o->c0[3] += 0x12;
        }
    } else if (o->c0[3] > 10) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        if (o->size < 0x5A) {
            o->size += 2;
        }
    }
    if (o->t % 2 == 1) {
        if (o->h34 < 5) {
            o->h34++;
        }
    }
    if (o->t != 0) {
        o->pos += o->speed;
    }
    if (o->t != 0) {
        o->size += 2;
    }
    o->y++;
    o->rot[0] = func_0019A5C8() % 360;
    o->rot[1] = func_0019A5C8() % 360;
    o->rot[2] = func_0019A5C8() % 360;
    o->t++;
    return 0;
}

/* shape b570:01E02680, 140 insns: b205:01E01900 family purple spark (size 2..4, frame 0..2, random spin) drifting x/y by (-50..49)/400 and sinking 0.09 per tick: alpha up by 64 to 0x80 for 90 ticks, then down by 9 */

typedef struct {
    s16 spin[3];
    u8 pad6[2];
    s16 w;
    s16 h;
    u8 padC[4];
    f32 pos[3];
    u8 pad1C[4];
    s32 rot[3];
    u8 pad2C[4];
    f32 vel[3];
    u8 pad3C[0x16];
    s16 f52;
    s16 tick;
    s16 kind;
    s16 mode;
    u8 pad5A[2];
    s16 dir;
    u8 pad5E[2];
    u8 col[4];
} Spark_b570_01E02680;

static s32 func_01E02680_b570(s32 arg0, Spark_b570_01E02680 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->w = func_0019A5C8() % 3 + 2;
        o->h = o->w;
        o->kind = (func_0019A5C8() >> 4) % 3;
        func_001076F0(o->col, 0x80, 0x20, 0xFF);
        o->mode = 2;
        o->vel[1] = func_0019A5C8() % 100 - 50;
        o->vel[0] = func_0019A5C8() % 100 - 50;
        o->vel[1] /= 400.0f;
        o->vel[0] /= 400.0f;
        o->dir = func_0019A5C8() % 360;
        func_00205C40((s32)o->rot);
        o->spin[2] = func_0019A5C8() % 0x800 - 0x400;
        o->spin[1] = func_0019A5C8() % 0x800 - 0x400;
        o->spin[0] = func_0019A5C8() % 0x800 - 0x400;
    }
    if (o->tick < 90) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->pos[0] += o->vel[0];
        o->pos[1] += o->vel[1] - 0.09f;
    }
    func_00205C40((s32)o->rot);
    o->tick++;
    return 0;
}

/* shape b570:01E028B0, 178 insns: a purple (0x80, 0x20, 0xFF) square spark 3..5, frame 0..2, drifting (-50..49)/400 in x/y and falling 0.29 a tick, with random spins; its z speed covers a tenth of the gap from the tracked point (ctx+0x9F6C) to the camera over 50..149 ticks; alpha up by 0x40 to 0x80 for 10 ticks, then down by 9 */

typedef struct {
    u8 pad0[0x9F6C];
    s16 id;
} Ctx_b570_01E028B0;

typedef struct {
    s16 spin[3];
    u8 pad6[2];
    s16 w;
    s16 h;
    u8 padC[4];
    f32 pos[3];
    u8 pad1C[4];
    s32 rot[3];
    u8 pad2C[4];
    f32 vel[3];
    u8 pad3C[0x16];
    s16 f52;
    s16 tick;
    s16 kind;
    s16 mode;
    u8 pad5A[2];
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
} Fx_b570_01E028B0;

static s32 func_01E028B0_b570(Ctx_b570_01E028B0 *g, Fx_b570_01E028B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, f32 *);
    extern void func_001F5F90(s32, f32 *);
    f32 v[12];

    if (o->mode == 1) {
        o->w = func_0019A5C8() % 3 + 3;
        o->h = o->w;
        o->kind = (func_0019A5C8() >> 4) % 3;
        func_001076F0(o->col, 0x80, 0x20, 0xFF);
        o->mode = 2;
        o->vel[1] = func_0019A5C8() % 100 - 50;
        o->vel[0] = func_0019A5C8() % 100 - 50;
        o->vel[1] /= 400.0f;
        o->vel[0] /= 400.0f;
        o->f5C = func_0019A5C8() % 360;
        func_00205C40((s32)o->rot);
        o->spin[2] = func_0019A5C8() % 0x800 - 0x400;
        o->spin[1] = func_0019A5C8() % 0x800 - 0x400;
        o->spin[0] = func_0019A5C8() % 0x800 - 0x400;
        func_001F5620(func_001F53A0(), g->id, v);
        func_001F5F90(func_001F5380(), &v[4]);
        o->vel[2] = (v[6] - v[2]) / (func_0019A5C8() % 100 + 50);
        o->vel[2] /= 10.0f;
    }
    if (o->tick < 10) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->pos[2] += o->vel[2];
        o->pos[0] += o->vel[0];
        o->pos[1] += o->vel[1] - 0.29f;
    }
    func_00205C40((s32)o->rot);
    o->tick++;
    return 0;
}

/* shape b003:01E02110, 41 insns: a glow: colour (0x60,8,8) on start; alpha grows by 8 (up to 0x88) for 0x96 ticks,
   then fades out by 9 and stops */

typedef struct {
    u8 pad0[0x28];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
} Glow_b003_01E02110;

static s32 func_01E02B80_b570(s32 arg0, Glow_b003_01E02110 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        func_001076F0(o->col, 0x60, 8, 8);
        o->mode = 2;
    }
    if (o->tick < 0x96) {
        if (o->col[3] < 0x81) {
            o->col[3] += 8;
        }
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b257:01E031C0, 55 insns: a flash: on start f38 0x12C, colours (0xF0,0xF0,0xF0) and (0xF0,0xF0,0x10) with
   alpha 0x10, a random direction; alpha grows by 0x60 for the first 2 ticks, then fades out by 10 and stops */

typedef struct {
    u8 pad0[0x28];
    u8 col[4];
    u8 col2[4];
    u8 pad30[2];
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
    s16 dir;
} Flash_b257_01E031C0;

static s32 func_01E02C30_b570(s32 arg0, Flash_b257_01E031C0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 0x12C;
        func_001076F0(o->col, 0xF0, 0xF0, 0xF0);
        func_001076F0(o->col2, 0xF0, 0xF0, 0x10);
        o->dir = func_0019A5C8() % 360;
        o->mode = 2;
        o->col2[3] = 0x10;
    }
    if (o->tick < 2) {
        o->col[3] += 0x60;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b570:01E02D10, 119 insns: b582:01E03470 family scene light at ctx+0x98C0 (orange 4/2/0, height 70) at the object: rises 0.2 to 1, falls 0.1 and ends; applied while alive; ends at scene state 1 */

typedef struct {
    s16 x, y, z;
    u8 pad6[0x2A];
    s16 phase;
    u8 pad32[4];
    s16 mode;
} Obj_b570_01E02D10;

typedef struct {
    f32 w0;
    f32 r, g, b;
    f32 x, y, z;
    u8 pad1C[4];
    s32 w20;
    f32 h;
    f32 level;
    u8 pad2C[0x4];
    s32 state;
} Light_b570_01E02D10;

typedef struct {
    u8 pad[0x98C0];
    Light_b570_01E02D10 l;
} Game_b570_01E02D10;

static s32 func_01E02D10_b570(Game_b570_01E02D10 *g, Obj_b570_01E02D10 *o) {
    extern void func_001F6C10(void *);

    if (o->mode == 1) {
        g->l.w0 = 0.0f;
        g->l.r = 4.0f;
        g->l.g = 2.0f;
        g->l.b = 0.0f;
        g->l.w20 = 0;
        g->l.h = 70.0f;
        g->l.level = 0.0f;
        g->l.x = o->x;
        g->l.y = o->y;
        g->l.z = o->z;
        o->mode = 2;
        o->phase = 0;
    }
    if (o->phase == 0) {
        if (g->l.level < 1.0f) {
            g->l.level += 0.2f;
        } else {
            o->phase = 1;
        }
    } else if (g->l.level > 0.1f) {
        g->l.level -= 0.1f;
    } else {
        o->mode = 0;
    }
    if (o->mode == 0) {
        func_001F6C10(0);
    } else {
        func_001F6C10(&g->l);
    }
    if (g->l.state == 1) {
        o->mode = 0;
    }
    return 0;
}

/* shape b570:01E02F00, 51 insns: volume fade: starts at 0x80; while the game counter at 0x98F0 is over 0x1E it drops by
   10 to 0x30, otherwise it rises by 10 to 0x80; passed to func_001F6D00 (the same call either way) */

typedef struct {
    u8 pad0[0x98F0];
    s32 count;
} Game_b570_01E02F00;

typedef struct {
    u8 pad0[0x30];
    s16 v;
    u8 pad32[0x4];
    s16 mode;
} Fx_b570_01E02F00;

static s32 func_01E02F00_b570(Game_b570_01E02F00 *g, Fx_b570_01E02F00 *o) {
    extern void func_001F6D00(u8);

    if (o->mode == 1) {
        o->v = 0x80;
        o->mode = 2;
    }
    if (g->count > 0x1E) {
        if (o->v > 0x30) {
            o->v -= 10;
        } else {
            o->v = 0x30;
        }
    } else if (o->v < 0x80) {
        o->v += 10;
    } else {
        o->v = 0x80;
    }
    if (g->count == 1) {
        func_001F6D00(o->v);
    } else {
        func_001F6D00(o->v);
    }
    return 0;
}

/* shape b003:01E023F0: b018:01E02DB0 with other constants (chatG) */

extern f32 D_01E03E80_b570;
extern f32 D_01E03E88_b570;

static s32 func_01E02FD0_b570(void) {
    f32 a;
    f32 b;

    *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E03E80_b570;
    *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E03E88_b570;
    func_001F7170(1, 0, (s32)&a, (s32)&b, 1);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b570", func_01E03020_b570);

/* shape b570:01E03B40, 90 insns: take a free slot (0xC8 of 0x40 bytes at 0x2A0), clear it, colour both colours from
   the scene colour 0x98F4, attach it to the scene position 0x250, 0x30 from 0x9F90, store the two arguments; returns 1
   if a slot was found */

typedef struct {
    u8 pad0[0x20];
    s32 a2;
    s32 a1;
    u8 col[4];
    u8 col2[4];
    s16 f30;
    u8 pad32[4];
    s16 used;
    u8 pad38[8];
} Slot_b570_01E03B40;

typedef struct {
    u8 pad0[0x250];
    f32 pos[3];
    u8 pad25C[0x44];
    Slot_b570_01E03B40 slots[0xC8];
    u8 pad34A0[0x98F4 - 0x34A0];
    u8 rgba[4];
    u8 pad98F8[0x698];
    s16 f9F90;
} Scene_b570_01E03B40;

static s32 func_01E03B40_b570(Scene_b570_01E03B40 *g, s32 a1, s32 a2) {
    extern void func_00195108();
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b570_01E03B40 *s = NULL;
    s16 i;

    for (i = 0; i < 0xC8; i++) {
        if (g->slots[i].used == 0) {
            func_00195108(&g->slots[i], 0x40);
            g->slots[i].used = 1;
            s = &g->slots[i];
            i = 0xC8;
        }
    }
    if (s != NULL) {
        func_001076F0(s->col, g->rgba[0], g->rgba[1], g->rgba[2]);
        s->col[3] = g->rgba[3];
        func_001076F0(s->col2, g->rgba[0], g->rgba[1], g->rgba[2]);
        s->col2[3] = g->rgba[3];
        func_00106AB0(s, g->pos, 0);
        s->f30 = g->f9F90;
        s->a2 = a2;
        s->a1 = a1;
        return 1;
    }
    return 0;
}

/* shape b570:01E03CB0, 98 insns, 1 copies (b236:01E02330's code, generated by chatG/ovl/gen236.py): take a free effect slot (0xc8 of 0x70 bytes), clear it, colour it from the
   owner's colour, place it at the owner's position; returns 1, or 0 if every slot is in use */

typedef struct Slot_b570_01E03CB0 {
    u8 pad0[0x10];
    f32 pos[3];
    u8 pad1C[0x24];
    s32 f40;
    s32 f44;
    u8 pad48[8];
    s16 f50;
    u8 pad52[6];
    s16 used;
    u8 pad5A[6];
    u8 c60[4];
    u8 c64[4];
    u8 pad68[8];
} Slot_b570_01E03CB0;

typedef struct Obj_b570_01E03CB0 {
    u8 pad0[0x250];
    f32 pos[3];
    u8 padA[0x4120 - 0x250 - 12];
    Slot_b570_01E03CB0 slots[0xc8];
    u8 padB[0x98f4 - 0x4120 - 0xc8 * 0x70];
    u8 rgba[4];
    u8 padC[0x9f90 - 0x98f4 - 4];
    s16 fB2B0;
} Obj_b570_01E03CB0;

static s32 func_01E03CB0_b570(Obj_b570_01E03CB0 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b570_01E03CB0 *s = NULL;
    s16 i;

    for (i = 0; i < 0xc8; i++) {
        if (obj->slots[i].used == 0) {
            func_00195108(&obj->slots[i], 0x70);
            obj->slots[i].used = 1;
            s = &obj->slots[i];
            i = 0xc8;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c60, obj->rgba[0], obj->rgba[1], obj->rgba[2]);
        s->c60[3] = obj->rgba[3];
        func_001076F0(s->c64, obj->rgba[0], obj->rgba[1], obj->rgba[2]);
        s->c64[3] = obj->rgba[3];
        func_00106AB0(s, obj->pos, 0);
        s->pos[0] = obj->pos[0];
        s->pos[1] = obj->pos[1];
        s->pos[2] = obj->pos[2];
        s->f50 = obj->fB2B0;
        s->f40 = arg2;
        s->f44 = arg1;
        return 1;
    }
    return 0;
}
