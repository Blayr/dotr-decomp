#include "common.h"

/* shape c507:01E01540, 307 insns, 1 copy: the module's main: with arg >= 0 it clears the scene, loads textures 15
   and 12, lays out 16 sparks (x +-10, y 5..20, each turned -3 more), sets both sprites and the two camera points
   (eye 120 up, target 20 lower and 10 back) and a 60-tick life; otherwise it turns the scene, draws the sprite while
   its state is 0 or 999, and while more than 20 ticks are left swings (+-0x800 every 4 ticks) and draws the sparks
   at scale 1.01, fading them after 40, else it spins down and fades out; ends with 2 at the 17th call or 8 */

typedef struct {
    f32 x, y, z;
    s16 h1C;
    s16 h1E;
} Spark_c507_01E01540;

typedef struct {
    u8 pad0[0x10];
    s32 rx;
    s32 ry;
    u8 pad18[8];
    Vec4f eye;
    u8 pad30[0x40];
    u8 sub70[0x20];
    Vec4f at;
    u8 padA0[0x40];
    s32 texE0;
    u8 padE4[4];
    f32 fE8;
    u8 colEC[4];
    f32 fF0;
    f32 fF4;
    f32 fF8;
    u8 padFC[4];
    s16 h100[8];
    u8 pad110[0x20];
    f32 f130;
    u8 col134[4];
    u32 flags;
    u8 pad13C[8];
    s32 f144;
    s16 h148;
    s16 h14A;
    s16 h14C;
    s16 h14E;
    s16 h150;
    s16 state;
    u8 pad154[0xC];
    s32 tex160;
    s32 f164;
    u8 col168[4];
    f32 f16C;
    f32 f170;
    f32 f174;
    f32 f178;
    f32 f17C;
    u8 pad180[4];
    s16 h184;
    s16 h186;
    s16 h188;
    s16 h18A;
    s16 h18C;
    s16 h18E;
    Spark_c507_01E01540 p[16];
    s16 n;
    u8 pad292[4];
    s16 h296;
    s16 h298;
    s16 h29A;
    s16 h29C;
    s16 h29E;
    s16 h2A0;
    u8 pad2A2[0xE];
    s32 t;
    s32 life;
    s32 calls;
    s32 arg;
    s32 f2C0;
} Scene_c507_01E01540;

static s32 func_01E01540_c507(s32 arg0, s32 arg) {
    Scene_c507_01E01540 *g = (Scene_c507_01E01540 *)arg0;
    extern void func_00195108(void *, s32);
    extern void func_00103890(void *);
    extern void func_00103260(void *, s32);
    extern void func_001F53B0(s32, void *);
    extern void func_001038D0(void *);
    extern void func_001039A0(void *);
    extern void c507_01E00120(s32, void *, void *, void *);
    extern void c507_01E009B0(s32, void *, void *, void *);
    extern s32 func_00103540(void *, f32, f32);
    extern s32 func_00103390(void *, f32, f32);
    extern void func_00103350(void *, s32, s32);
    extern void func_00103470(void *, s32, s32);
    extern void func_001032C0(void *, s32, s32);
    Vec4f s;
    s32 r[4];
    s32 tex[4];
    s32 ot;
    s32 i;

    ot = (s32)func_00207500();
    if (arg >= 0) {
        func_00195108(g, 0x2D0);
        g->f2C0 = 0;
        g->t = -4;
        g->life = 60;
        g->calls = 0;
        g->arg = arg;
        func_00103890(g);
        func_00103890(g->sub70);
        func_00103260(tex, 15);
        g->tex160 = tex[0];
        g->f164 = 0x85;
        g->f170 = 0.0f;
        g->f174 = 5.0f;
        g->f178 = 0.0f;
        g->f17C = 0.0f;
        g->h188 = 240;
        g->h18A = 0;
        g->h184 = 16;
        g->h186 = 16;
        g->h18C = 256;
        g->h18E = 256;
        g->f16C = 10.0f;
        g->n = 16;
        g->h29A = 3;
        g->h29C = 1;
        g->h2A0 = 8;
        g->h296 = 30;
        g->h298 = -10;
        g->col168[2] = 0x80;
        g->col168[1] = 0x80;
        g->col168[0] = 0x80;
        g->col168[3] = 0x50;
        for (i = 0; i < g->n; i++) {
            g->p[i].x = g->f170 + (func_0019A5C8() % 20 - 10);
            g->p[i].y = g->f174 + func_0019A5C8() % 16;
            g->p[i].z = g->f178;
            g->p[i].h1E = -g->h29A * i;
            g->p[i].h1C = 0;
            g->h29E = g->h2A0 - 1;
        }
        func_00103260(tex, 12);
        g->f130 = 1.0f;
        if (g->arg == 0) {
            g->flags = 0x80000001;
        } else {
            g->flags = 0x80000801;
        }
        g->h100[0] = 0;
        g->h100[1] = 0;
        g->h100[2] = 0x80;
        g->h100[3] = 0x40;
        g->h100[4] = 0;
        g->h100[5] = 0;
        g->h100[6] = 0x80;
        g->h100[7] = 0x40;
        g->f144 = -70;
        g->h148 = 0;
        g->h14A = 1;
        g->h14E = 1;
        g->state = 999;
        g->h150 = 0;
        g->h14C = g->h14E - 1;
        g->fF8 = 0.0f;
        g->fF4 = 0.0f;
        g->fF0 = 0.0f;
        g->fE8 = 30.0f;
        g->texE0 = tex[0];
        g->colEC[2] = 0x80;
        g->colEC[1] = 0x80;
        g->colEC[0] = 0x80;
        g->colEC[3] = 0x80;
        g->col134[2] = 0x80;
        g->col134[1] = 0x80;
        g->col134[0] = 0x80;
        g->col134[3] = 0;
        func_001F53B0(0, &g->eye);
        g->eye.y = 120.0f;
        g->fF4 -= 20.0f;
        g->fF0 -= 10.0f;
        func_001F53B0(0, &g->at);
        return 0;
    }
    func_00205C40((s32)r);
    g->ry = r[1] % 0x10000;
    func_001038D0(g);
    func_001039A0(g->sub70);
    if (g->state == 0 || g->state == 999) {
        c507_01E00120(ot, g->h100, &g->texE0, g);
    }
    if (g->life > 20) {
        if (func_00103540(&g->eye.y, 40.0f, 5.0f) == 0) {
            if (g->t < 0) {
                g->rx -= 0x400;
            } else if (g->t % 8 < 4) {
                g->rx += 0x800;
            } else {
                g->rx -= 0x800;
            }
            s.x = s.y = s.z = 1.01f;
            c507_01E009B0(ot, g->sub70, &g->tex160, &s);
            if (g->t >= 0 && g->t < 40) {
                func_00103470(&g->col168[3], 0, 2);
            }
            g->t++;
        }
        func_001032C0(&g->col134[3], 0x80, 8);
    } else {
        func_00103350(&g->rx, 0, 0x800);
        func_00103390(&g->eye.y, 100.0f, 5.0f);
        func_00103470(&g->col134[3], 0, 16);
    }
    g->calls++;
    g->life--;
    if (g->calls == 17) {
        return 2;
    }
    if (g->life <= 0) {
        return 8;
    }
    return 0;
}
