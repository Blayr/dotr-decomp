#include "common.h"

/* shape b430:01E04470, 376 insns: B430PAINT_RAIN101: draws the jagged ring field (b430:01E04A50) as textured quads
   (rect 0x9C inset by 2, the object's colour, scene texture 0x40C): rings 1..18, 18 quads each (the last wrapping to
   column 0), up to the scene's quad count (ctx+0xEC0); each corner relative to the quad's first point, turned by the
   scene matrix (0x3B0), from scene tick 236 bent by the two per-quad angles (0x1734, 0x1A04), rotated by the scene
   turn (0xE10), moved back to the scaled point and up by the object's height; the point's height a fifth */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b430_01E04470;

typedef struct {
    Rgbaq_b430_01E04470 c;
    u64 st;
    u64 xyz;
} Vtx_b430_01E04470;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b430_01E04470 v[4];
} Pkt_b430_01E04470;

typedef struct {
    u8 pad0[0x28];
    u8 col[4];
    u8 pad2C[4];
    s16 h30;
} Obj_b430_01E04470;

typedef struct {
    u8 pad0[0x3A0];
    f32 sc[3];
    u8 pad3AC[4];
    u8 m[0x40];
    u8 pad3F0[0x1C];
    s32 tex;
    u8 pad410[0xE10 - 0x410];
    f32 turn[3];
    u8 padE1C[0xE8C - 0xE1C];
    s32 ot;
    u8 padE90[8];
    f32 depth;
    u8 padE9C[0x24];
    s16 count;
    u8 padEC2[0x1734 - 0xEC2];
    s16 a0[18 * 19];
    u8 pad19D8[0x1A04 - 0x19D8];
    s16 a1[18 * 19];
    u8 pad1CA8[0x1CD4 - 0x1CA8];
    f32 x[20][18];
    f32 z[20][18];
    f32 y[20][18];
    u8 pad2DB4[0x3358 - 0x2DB4];
    s16 timer;
    u8 pad335A[0x365C - 0x335A];
    u8 bend[4];
} Ctx_b430_01E04470;

static void func_01E04470_b430(Ctx_b430_01E04470 *g, Obj_b430_01E04470 *o, Pkt_b430_01E04470 *p) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern Rgbaq_b430_01E04470 func_00107740(void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5F90(s32, void *);
    extern void func_00106E90(void *, void *);
    extern void func_00108950(void *, void *, s32, void *);
    extern void func_00107070(void *, s32, f32);
    extern void func_00106B50(void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    s16 cnt;
    s32 i;
    s32 k;
    s32 j;
    Vec4f q[4];
    s16 rect[4];
    s32 iv[4];
    Vec4f a;
    Vec4f b;
    Vec4f c;

    cnt = 0;
    func_00106080(rect, 0x9C, 0, rect);
    rect[0] += 2;
    rect[1] += 2;
    rect[2] -= 2;
    rect[3] -= 2;
    func_00109270(p, 0, 0);
    p->v[0].c = func_00107740(o->col);
    p->v[1].c = func_00107740(o->col);
    p->v[2].c = func_00107740(o->col);
    p->v[3].c = func_00107740(o->col);
    func_00108500(p, rect, 0);
    func_00208700(p, g->tex, 1);
    func_001F5F90(func_001F53A0(), &a);
    func_001F5F90(func_001F5380(), &b);
    a.z = -(a.z - b.z) / 60.0f;
    for (i = 1; i < 19; i++) {
        k = (i - 1) * 18;
        for (j = 0; j < 18; j++) {
            c.x = g->x[i][j];
            c.y = g->z[i][j];
            c.z = g->y[i][j];
            if (cnt < g->count) {
                q[0].x = g->x[i][j] - c.x;
                q[0].z = g->y[i][j] - c.z;
                if (j == 17) {
                    q[1].x = g->x[i][0] - c.x;
                    q[1].z = g->y[i][0] - c.z;
                } else {
                    q[1].x = g->x[i][j + 1] - c.x;
                    q[1].z = g->y[i][j + 1] - c.z;
                }
                q[2].x = g->x[i + 1][j] - c.x;
                q[2].z = g->y[i + 1][j] - c.z;
                if (j == 17) {
                    q[3].x = g->x[i + 1][0] - c.x;
                    q[3].z = g->y[i + 1][0] - c.z;
                } else {
                    q[3].x = g->x[i + 1][j + 1] - c.x;
                    q[3].z = g->y[i + 1][j + 1] - c.z;
                }
                q[0].y = g->z[i][j] - c.y;
                if (j == 17) {
                    q[1].y = g->z[i][0] - c.y;
                } else {
                    q[1].y = g->z[i][j + 1] - c.y;
                }
                q[2].y = g->z[i + 1][j] - c.y;
                if (j == 17) {
                    q[3].y = g->z[i + 1][0] - c.y;
                } else {
                    q[3].y = g->z[i + 1][j + 1] - c.y;
                }
                c.x *= g->sc[0];
                c.y *= g->sc[1];
                c.z *= g->sc[2];
                func_00106E90(&q[0], g->m);
                func_00106E90(&q[1], g->m);
                func_00106E90(&q[2], g->m);
                func_00106E90(&q[3], g->m);
                if (g->timer >= 236) {
                    iv[1] = (f32)g->a0[k + j];
                    func_00108950(&q[0], iv, 0, g->bend);
                    func_00108950(&q[1], iv, 0, g->bend);
                    func_00108950(&q[2], iv, 0, g->bend);
                    func_00108950(&q[3], iv, 0, g->bend);
                    iv[0] = (f32)g->a1[k + j];
                    func_00108950(&q[0], iv, 1, g->bend);
                    func_00108950(&q[1], iv, 1, g->bend);
                    func_00108950(&q[2], iv, 1, g->bend);
                    func_00108950(&q[3], iv, 1, g->bend);
                }
                func_00107070(&q[0], 0, g->turn[0]);
                func_00107070(&q[0], 1, g->turn[1]);
                func_00107070(&q[0], 2, g->turn[2]);
                func_00106B50(&q[0], &c);
                func_00106B50(&q[1], &c);
                func_00106B50(&q[2], &c);
                func_00106B50(&q[3], &c);
                c.y /= 5.0f;
                func_00107070(&q[0], 0, c.x * o->h30);
                func_00107070(&q[0], 1, c.y * o->h30);
                func_00107070(&q[0], 2, c.z * o->h30);
                if (func_00205630(q, 0x70000000, 0, p, &g->depth) != 0) {
                    func_002075F0(p, g->ot, (u32)g->depth);
                }
            }
            cnt++;
        }
    }
}
