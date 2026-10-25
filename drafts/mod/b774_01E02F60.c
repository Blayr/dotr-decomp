/* OVL_WARM */
#include "common.h"

/* shape b774:01E02F60, 259 insns: two-pass ring (b053:01E02490's family): mode 0 sets the material (frame 0x97 at the
   object's page, its colour, scene texture 0x10C); other modes scale (0.8, 1, 0.8) at the object, then 12 quads
   30 apart between radius size and size - w (w = 3 while size < 10, else 10 before scene tick 140 and size after),
   the outer corners jittered by -10..9 when the matching scene slot runs callback 0x1E011C0 */

typedef struct {
    s16 x, y, z;
    u8 pad6[0xA];
    s32 rot[4];
    u8 pad20[8];
    u8 col[8];
    u8 pad30[4];
    s16 page;
    u8 pad36[2];
    s16 size;
    s16 ang;
} Obj_b774_01E02F60;

typedef struct {
    s32 pad0;
    void *cb;
    u8 pad8[0x38];
} Slot_b774_01E02F60;

typedef struct {
    u8 pad0[0x10C];
    void *tex;
    u8 pad110[0x680 - 0x110];
    Slot_b774_01E02F60 slot[12];
    u8 pad980[0x36DC - 0x980];
    s32 ot;
    u8 pad36E0[0x1C];
    f32 depth;
    u8 pad3700[0x1E];
    s16 tick;
    u8 pad3720[4];
    u8 tbl[1];
} Ctx_b774_01E02F60;

static void func_01E02F60_b774(Ctx_b774_01E02F60 *ctx, Obj_b774_01E02F60 *o, void *pkt, s32 mode) {
    extern void func_00106080(void *, s32, s16, void *);
    extern s32 func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00106DD0(void *, f32, f32, f32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_0019A5C8(void);
    extern void func_01E011C0_b774(void);
    Vec4f q[4];
    Vec4f pos;
    Vec4f sc;
    f32 m[16];
    u8 td[0x10];
    f32 w;
    s32 i;
    s16 a;
    s16 k;

    a = 0;
    if (mode == 0) {
        func_00106080(td, 0x97, o->page, td);
        func_00109270(pkt, 0, 0);
        func_00107790(pkt, o->col, 0);
        func_00108500(pkt, td, 0);
        func_00208700(pkt, ctx->tex, 1);
    } else {
        pos.x = o->x;
        pos.y = o->y;
        pos.z = o->z;
        func_00106DD0(&sc, 0.8f, 1.0f, 0.8f);
        func_00108EF0(m, &sc, o->rot, &pos);
        q[0].y = 0.0f;
        q[1].y = 0.0f;
        q[2].y = 0.0f;
        q[3].y = 0.0f;
        if (ctx->tick < 140) {
            if (o->size - 10 < 0) {
                w = 3.0f;
            } else {
                w = 10.0f;
            }
        } else {
            if (o->size - 10 < 0) {
                w = 3.0f;
            } else {
                w = o->size;
            }
        }
        for (i = 0; i < 12; i++) {
            k = o->ang + a;
            q[2].x = o->size * func_00108030(ctx->tbl, k, 1);
            q[2].z = o->size * func_00108030(ctx->tbl, k, 0);
            q[0].x = (o->size - w) * func_00108030(ctx->tbl, k, 1);
            q[0].z = (o->size - w) * func_00108030(ctx->tbl, k, 0);
            k = o->ang + 30 + a;
            q[3].x = o->size * func_00108030(ctx->tbl, k, 1);
            q[3].z = o->size * func_00108030(ctx->tbl, k, 0);
            q[1].x = (o->size - w) * func_00108030(ctx->tbl, k, 1);
            q[1].z = (o->size - w) * func_00108030(ctx->tbl, k, 0);
            if (ctx->slot[i].cb == func_01E011C0_b774) {
                q[2].y = func_0019A5C8() % 20 - 10;
                q[3].y = func_0019A5C8() % 20 - 10;
            }
            if (func_00205630((s32)q, 0x70000000, (s32)m, (s32)pkt, &ctx->depth) != 0) {
                func_002075F0((s32)pkt, ctx->ot, (u32)ctx->depth);
            }
            a += 30;
        }
    }
}
