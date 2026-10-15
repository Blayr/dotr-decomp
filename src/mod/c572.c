#include "common.h"

/* shape c572:01E00080, 92 insns: a camera move: with a code (ch | id << 8) it clears itself, takes the scene camera (func_001F5380), locks it and loads its start/end points for 30 ticks of 32; without one it eases the camera's eye and target 1/n of the way each tick and unlocks it at the end (returns 8) */

typedef struct {
    Vec4f eye;
    Vec4f at;
    Vec4f eye1;
    Vec4f at1;
    s32 n;
    s32 left;
    s32 tick;
    s32 pad4C;
    s32 ch;
    s32 id;
    s32 cam;
    u8 pad5C[4];
} Move_c572_01E00080;

static s32 func_01E00080_c572(s32 arg0, s32 code) {
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern s32 func_001F5380(void);
    extern void func_001F5970(s32, s32);
    extern void func_001E10F0(s32, s32, s32, void *);
    extern s32 func_001F5EC0(s32);
    extern void func_001F5F90(s32, void *);
    extern void func_00104490(void *, void *, s32);
    extern void func_001F5F00(s32, void *);
    extern s32 func_001F5AF0(s32);
    extern void func_001F5BD0(s32, void *);
    extern void func_001F5B70(s32, void *);

    Move_c572_01E00080 *m = (Move_c572_01E00080 *)arg0;

    func_00207500();
    if (code >= 0) {
        func_00195108(m, 0x60);
        m->pad4C = 0;
        m->left = 0x20;
        m->tick = 0;
        m->cam = func_001F5380();
        func_001F5970(m->cam, 1);
        m->n = 30;
        m->ch = code & 0xFF;
        m->id = code >> 8;
        func_001E10F0(m->ch, m->id, 0, &m->at1);
        func_001E10F0(m->ch, m->id, 0, &m->eye1);
        m->eye1.y = 50.0f;
        return 0;
    }
    if (func_001F5EC0(m->cam) != 0) {
        func_001F5F90(m->cam, &m->eye);
        func_00104490(&m->eye, &m->eye1, m->n);
        func_001F5F00(m->cam, &m->eye);
    }
    if (func_001F5AF0(m->cam) != 0) {
        func_001F5BD0(m->cam, &m->at);
        func_00104490(&m->at, &m->at1, m->n);
        func_001F5B70(m->cam, &m->at);
    }
    m->n--;
    m->tick++;
    m->left--;
    if (m->left <= 0) {
        func_001F5970(m->cam, 0);
        return 8;
    }
    return 0;
}
