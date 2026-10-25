#include "common.h"

/* shape b491:01E02370, 296 insns, 1 copy (B491_OBJ_MOVE_3_): a white flare flying from the model to the camera's model
   over 45 ticks (sinking toward height 40 after tick 5): size 15 growing to 50, in by 42 up to 0x80, blinks; at tick 45
   it bursts into 7 scattered sparks (b491:01E02D00), 3 glows (b491:01E02810) and one b491:01E02EC0, then fades by 14 */

typedef struct {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[4];
    Vec4f pos;
    s32 rot[4];
    u8 pad30[0x24];
    s16 tick;
    s16 frame;
    s16 state;
    u8 pad5A[6];
    u8 col[4];
    u8 col2[4];
} Obj_b491_01E02370;

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0x4274];
    s16 joint;
} Scene_b491_01E02370;

static s32 func_01E02370_b491(Scene_b491_01E02370 *g, Obj_b491_01E02370 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, Vec4f *);
    extern void func_001F5F90(s32, Vec4f *);
    extern s32 func_01E03E70_b491();
    extern s32 func_01E02810_b491();
    extern s32 func_01E02D00_b491();
    extern s32 func_01E02EC0_b491();
    Vec4f a;
    Vec4f b;
    Vec4f c;
    s16 i;
    Vec4f *bp;

    func_001F5F90(func_001F5380(), &a);
    bp = &b;
    func_001F5F90(func_001F53A0(), bp);
    func_001F5620(func_001F53A0(), g->joint, &c);
    a.x = (a.x - bp->x) / 45.0f;
    a.y = (a.y - b.y) / 45.0f;
    a.z = (a.z - b.z) / 45.0f;
    c.y = (40.0f - c.y) / 65.0f;
    if (o->state == 1) {
        o->w = 15;
        o->h = 15;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0x80, 0x80, 0x80);
        o->state = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 45) {
        if (o->col[3] < 0x80) {
            o->col[3] += 42;
        }
        if (o->col2[3] < 0x80) {
            o->col2[3] += 42;
        }
    } else {
        if (o->col[3] > 15) {
            o->col[3] -= 14;
        } else {
            o->state = 0;
        }
        if (o->col[3] > 15) {
            o->col[3] -= 14;
        }
    }
    if (o->tick != 0) {
        if (o->w < 50) {
            o->w++;
        }
        if (o->h < 50) {
            o->h++;
        }
    }
    if (o->tick % 2 == 1) {
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
    } else {
        func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
    }
    if (o->tick < 45) {
        o->pos.x += a.x;
        o->pos.y += a.y;
        o->pos.z += a.z;
        if (o->tick > 5 && o->pos.y > 40.0f) {
            o->pos.y += c.y;
        }
    }
    if (o->tick == 45) {
        for (i = 0; i < 7; i++) {
            g->pos = o->pos;
            g->pos.x += func_0019A5C8() % 20 - 10;
            g->pos.y += func_0019A5C8() % 20 - 10;
            g->pos.z += func_0019A5C8() % 20 - 10;
            func_01E03E70_b491(g, func_01E02D00_b491, 0);
        }
    }
    if (o->tick == 45) {
        for (i = 0; i < 3; i++) {
            g->pos = o->pos;
            func_01E03E70_b491(g, func_01E02810_b491, 0);
        }
        func_01E03E70_b491(g, func_01E02EC0_b491, 0);
    }
    if (o->tick != 0) {
        o->frame++;
        if (o->frame > 7) {
            o->frame = 0;
        }
    }
    func_00205C40((s32)o->rot);
    o->tick++;
    return 0;
}
