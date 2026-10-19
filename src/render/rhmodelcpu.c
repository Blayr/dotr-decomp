/* Model drawing on the CPU and Z sorting (RhModelCpu_*, RhZSort_*). */

#include "common.h"

/* Draws a model part's translucent polygons on the CPU (sorted back to front) into the packet. */
u8 *RhModelCpu_DrawAlpha(u8 *packet, s32 data, s32 size, s32 global) {
    u8 *temp_s1;
    u8 *traceDynamicBlock;

    lRhModelCpu_SetupGlobal(global);
    *(s32 *)(packet + 0) = 0x10000002;
    *(s32 *)(packet + 4) = 0;
    *(s32 *)(packet + 8) = 0x11000000;
    *(s32 *)(packet + 0xC) = 0x51000002;
    *(s64 *)(packet + 0x10) = 0x1000000000008001LL;
    *(s64 *)(packet + 0x18) = 0xE;
    *(s64 *)(packet + 0x20) = 0x73;
    temp_s1 = packet + 0x30;
    *(s64 *)(packet + 0x28) = 0;
    traceDynamicBlock = lRhModelCpu_TraceDynamicBlock(temp_s1, data, size);
    if (traceDynamicBlock == NULL) {
        return packet;
    }
    lRhModelCpu_SortPolygon(temp_s1, traceDynamicBlock);
    lRhModelCpu_CleanupPacket(temp_s1, traceDynamicBlock);
    return traceDynamicBlock;
}

typedef struct Spr_002130A0 {
    f32 m[4][4];
    u8 pad40[0x1C];
    f32 f5C;
    u32 tag[8];
    u64 f80;
    u64 f88;
    u8 pad90[0x64];
    f32 fF4;
    f32 fF8;
    u8 padFC[8];
    s32 f104;
    u8 pad108[8];
    f32 f110;
    f32 f114;
} Spr_002130A0;

/* Sets up the CPU drawer's matrices and lights (`withLight`). */
s32 lRhModelCpu_SetupGlobal(s32 withLight) {
    Spr_002130A0 *spr = (Spr_002130A0 *)SCRATCHPAD_ADDR;
    u8 e[4];
    f32 near;
    f32 far;
    f32 c;
    f32 d;

    RhView_GetViewScreenMatrix(spr);
    {
        register u8 *m = (u8 *)SCRATCHPAD_ADDR;
        asm {
            lqc2 vf20, 0x0(m)
            lqc2 vf21, 0x10(m)
            lqc2 vf22, 0x20(m)
            lqc2 vf23, 0x30(m)
        }
    }
    spr->tag[0] = 0x10000000;
    spr->tag[1] = 0;
    spr->tag[2] = 0;
    spr->tag[3] = 0;
    spr->tag[4] = 0x10000006;
    spr->tag[5] = 0;
    spr->tag[6] = 0;
    spr->tag[7] = 0x51000006;
    spr->f80 = 0x3400000000008003;
    spr->f88 = 0x412;
    RhView_GetClipZ(&spr->fF4, &spr->fF8);
    spr->f104 = sceDmaGetChan(8);
    spr->f5C = 1.0f;
    RhView_GetFogParameter(&near, &far, &c, &d, e);
    if (withLight != 0) {
        spr->f110 = 255.0f * far / (far - near);
        spr->f114 = 255.0f / (far - near);
    } else {
        spr->f110 = 255.0f;
        spr->f114 = 0.0f;
    }
    return 1;
}

#define P_002131D0 ((u8 *)data)

/* Transforms a model part's dynamic block on the CPU into `out`. */
u8 *lRhModelCpu_TraceDynamicBlock(u8 *out, s32 data, s32 size) {
    u8 *spr = (u8 *)SCRATCHPAD_ADDR;
    u32 cmd;

    size = data + size;
    while (P_002131D0 < (u8 *)size) {
        cmd = *(u32 *)P_002131D0;
        if (cmd == 0x10000008) {
            *(__int128 *)(spr + 0x60) = *(__int128 *)P_002131D0;
            *(u32 *)(spr + 0x60) = 0x30000008;
            *(u8 **)(spr + 0x64) = P_002131D0 + 0x10;
            data += 0x90;
        } else if (cmd == 0x10000000) {
            data += 0x10;
        } else if (cmd == 0x10000003) {
            u8 *q = P_002131D0;

            func_0020B380(spr, q, 4);
            *(u32 *)(spr + 0x100) = (u8)(u32)(*(f32 *)(spr + 0x20) / 2.0f + *(f32 *)(spr + 0x10));
            *(u32 *)(spr + 0x100) |= (u8)(u32)(*(f32 *)(spr + 0x24) / 2.0f + *(f32 *)(spr + 0x14)) << 8;
            *(u32 *)(spr + 0x100) |= (u8)(u32)(*(f32 *)(spr + 0x28) / 2.0f + *(f32 *)(spr + 0x18)) << 16;
            *(u32 *)(spr + 0x100) |= (u32)*(f32 *)(spr + 0x2C) << 24;
            data = (s32)(q + 0x40);
        } else if ((cmd & 0xF0000000) == 0x30000000) {
            s32 x = *(s32 *)(P_002131D0 + 0xC);

            if (x == 0) {
                u8 *q = P_002131D0;

                out = (u8 *)func_00213410((s32)out, (s32)*(u32 *)(q + 4), *(u16 *)q << 4);
                data = (s32)(q + 0x10);
            } else {
                register u8 *m;
                register u32 dst = x & 0x3FF;
                u8 *q = P_002131D0;

                data = (s32)(q + 0x10);
                m = *(u8 **)(q + 4);
                asm {
                    lqc2 vf16, 0x0(m)
                    lqc2 vf17, 0x10(m)
                    lqc2 vf18, 0x20(m)
                    lqc2 vf19, 0x30(m)
                    ctc2.ni dst, vi1
                    vmulax.xyzw ACC, vf20, vf16x
                    vmadday.xyzw ACC, vf21, vf16y
                    vmaddaz.xyzw ACC, vf22, vf16z
                    vmaddw.xyzw vf16, vf23, vf16w
                    vmulax.xyzw ACC, vf20, vf17x
                    vmadday.xyzw ACC, vf21, vf17y
                    vmaddaz.xyzw ACC, vf22, vf17z
                    vmaddw.xyzw vf17, vf23, vf17w
                    vmulax.xyzw ACC, vf20, vf18x
                    vmadday.xyzw ACC, vf21, vf18y
                    vmaddaz.xyzw ACC, vf22, vf18z
                    vmaddw.xyzw vf18, vf23, vf18w
                    vmulax.xyzw ACC, vf20, vf19x
                    vmadday.xyzw ACC, vf21, vf19y
                    vmaddaz.xyzw ACC, vf22, vf19z
                    vmaddw.xyzw vf19, vf23, vf19w
                    vsqi.xyzw vf16, (vi1++)
                    vsqi.xyzw vf17, (vi1++)
                    vsqi.xyzw vf18, (vi1++)
                    vsqi.xyzw vf19, (vi1++)
                }
            }
        } else {
            return NULL;
        }
    }
    return out;
}

#undef P_002131D0

/* Transforms a model part's static block on the CPU. */
s32 lRhModelCpu_TraceStaticBlock(s32 arg0, u32 cursor, s32 size) {
    u32 end = cursor + size;
    u32 *scratchpad = (u32 *)SCRATCHPAD_ADDR;
    u32 packet;

    if (cursor < end) {
        do {
        packet = cursor;
        if (!(*(u32 *)(cursor + 0xC) & 0x8000)) {
            arg0 = lRhModelCpu_CalcIndepStrip(arg0, (s32 *)cursor);
        } else {
            arg0 = lRhModelCpu_CalcSharedStrip(arg0, (s32 *)cursor);
        }
        cursor = scratchpad[0x3F];
        if (*(u32 *)(packet + 4) & 0x8000) {
            cursor += 4;
        }
        while (*(s32 *)cursor == 0) {
            cursor += 4;
        }
        } while (cursor < end);
    }
    return arg0;
}

typedef struct {
    u32 xy;
    u32 z : 24;
    u32 f : 8;
} Vert_002134D0;

typedef struct {
    u8 pad00[0x40];
    Vert_002134D0 v0;
    u8 pad48[0x10];
    Vert_002134D0 v1;
    u8 pad60[0x10];
    Vert_002134D0 v2;
    s32 f78;
    s32 depth;
} Prim_002134D0;

#define prim ((Prim_002134D0 *)arg0)

/* Transforms a strip of separate vertices on the CPU. */
s32 lRhModelCpu_CalcIndepStrip(s32 arg0, s32 *arg1) {
    u8 *scratch;
    u8 *var_s1;
    s32 i;
    s32 temp_s3;
    s32 var_s4;

    var_s1 = (u8 *)arg1 + 0x18;
    scratch = (u8 *)SCRATCHPAD_ADDR;
    var_s4 = 0;
    temp_s3 = arg1[1] & 0x7FFF;
    for (i = 0; i < temp_s3; i++) {
        register s32 base = arg1[4];
        asm {
            ctc2.ni base, vi1
            vlqi.xyzw vf16, (vi1++)
            vlqi.xyzw vf17, (vi1++)
            vlqi.xyzw vf18, (vi1++)
            vlqi.xyzw vf19, (vi1++)
        }
        scratch[0xF0 + var_s4] = lRhModelCpu_CalcIndepPoint((s32)(scratch + var_s4 * 0x18 + 0x90), (s32 *)var_s1);
        if (i >= 2) {
            if (scratch[0xF0] && scratch[0xF1] && scratch[0xF2]) {
                RhMem_CopyMemory16(prim, scratch + 0x60, 8);
                prim->f78 = 0;
                prim->depth = ((prim->v0.z > prim->v1.z ? prim->v0.z : prim->v1.z) > prim->v2.z)
                    ? (prim->v0.z > prim->v1.z ? prim->v0.z : prim->v1.z) : prim->v2.z;
                arg0 += sizeof(Prim_002134D0);
            }
        }
        var_s1 += 0x12;
        var_s4 = (var_s4 + 1) % 3;
    }
    *(u32 *)(scratch + 0xFC) = (u32)(var_s1 + 3) & ~3;
    return arg0;
}

#undef prim

typedef struct Spr_00213680 {
    u8 pad00[0x40];
    f32 res[4];
    f32 in[4];
    u8 pad60[0x98];
    f32 fF8;
    u8 padFC[4];
    u32 f100;
    u8 pad104[0xC];
    f32 f110;
    f32 f114;
} Spr_00213680;

typedef struct Out_00213680 {
    f32 s;
    f32 t;
    u32 color;
    f32 q;
    u16 x;
    u16 y;
    u32 z : 24;
    u32 fog : 8;
} Out_00213680;

typedef struct In_00213680 {
    s16 u;
    s16 v;
    u8 pad4[8];
    s16 x;
    s16 y;
    s16 z;
} In_00213680;

#define OUT_00213680 ((Out_00213680 *)arg0)
#define IN_00213680 ((In_00213680 *)arg1)

/* Transforms one separate vertex on the CPU. */
s8 lRhModelCpu_CalcIndepPoint(s32 arg0, s32 *arg1) {
    Spr_00213680 *spr = (Spr_00213680 *)SCRATCHPAD_ADDR;
    register f32 *src = spr->in;
    register f32 *dst = spr->res;
    f32 w;
    f32 fog;

    OUT_00213680->color = spr->f100;
    spr->in[0] = IN_00213680->x;
    spr->in[1] = IN_00213680->y;
    spr->in[2] = IN_00213680->z;
    asm {
        lqc2 vf1, 0x0(src)
        vmulax.xyzw ACC, vf16, vf1x
        vmadday.xyzw ACC, vf17, vf1y
        vmaddaz.xyzw ACC, vf18, vf1z
        vmaddw.xyzw vf1, vf19, vf1w
        vdiv Q, vf0w, vf1w
        vwaitq
        vmulq.xyz vf1, vf1, Q
        sqc2 vf1, 0x0(dst)
    }
    w = spr->res[3];
    if (w < 1.0f || !(w < spr->fF8) || spr->res[0] <= 1.0f || !(spr->res[0] < 4095.0f) || spr->res[1] <= 1.0f ||
        !(spr->res[1] < 4095.0f)) {
        return 0;
    }
    OUT_00213680->x = (u32)(16.0f * spr->res[0]);
    OUT_00213680->y = (u32)(16.0f * spr->res[1]);
    OUT_00213680->z = (u32)(spr->res[2]);
    fog = spr->f110 - spr->f114 * spr->res[3];
    if (fog <= 0.0f) {
        OUT_00213680->fog = 0;
    } else if (!(fog < 255.0f)) {
        OUT_00213680->fog = 0xFF;
    } else {
        OUT_00213680->fog = (u32)(fog);
    }
    OUT_00213680->s = IN_00213680->u / spr->res[3] / 4096.0f;
    OUT_00213680->t = IN_00213680->v / spr->res[3] / 4096.0f;
    OUT_00213680->q = 1.0f / spr->res[3];
    return 1;
}

#undef OUT_00213680
#undef IN_00213680

typedef struct {
    u32 xy;
    u32 z : 24;
    u32 f : 8;
} Vert_002138D0;

typedef struct {
    u8 data[0x12];
} Item_002138D0;

typedef struct {
    u8 pad00[0x40];
    Vert_002138D0 v0;
    u8 pad48[0x10];
    Vert_002138D0 v1;
    u8 pad60[0x10];
    Vert_002138D0 v2;
    s32 f78;
    s32 depth;
} Prim_002138D0;
#pragma opt_lifetimes off

/* Transforms a strip of shared vertices on the CPU. */
s32 lRhModelCpu_CalcSharedStrip(s32 arg0, s32 *arg1) {
    extern s8 lRhModelCpu_CalcSharedPoint(s32, s32 *);
    u8 *scratch;
    u8 *var_s1;
    s32 i;
    s32 temp_s3;
    s32 var_s4;
    Prim_002138D0 *prim;
    u32 z0;
    u32 z1;

    var_s1 = (u8 *)arg1 + 0x14;
    prim = (Prim_002138D0 *)arg0;
    scratch = (u8 *)SCRATCHPAD_ADDR;
    var_s4 = 0;
    temp_s3 = arg1[1] & 0x7FFF;
    for (i = 0; i < temp_s3; i++) {
        scratch[0xF0 + var_s4] = lRhModelCpu_CalcSharedPoint((s32)(scratch + var_s4 * 0x18 + 0x90), (s32 *)var_s1);
        if (i >= 2) {
            if (scratch[0xF0] && scratch[0xF1] && scratch[0xF2]) {
                RhMem_CopyMemory16(prim, scratch + 0x60, 8);
                prim->f78 = 0;
                z0 = prim->v0.z;
                z1 = prim->v1.z;
                z0 = ((z0 > z1 ? z0 : z1) > prim->v2.z) ? (z0 > z1 ? z0 : z1) : prim->v2.z;
                prim->depth = z0;
                prim++;
            }
        }
        var_s1 = (u8 *)((Item_002138D0 *)(var_s1 + 6) + *(u16 *)(var_s1 + 4));
        var_s4 = (var_s4 + 1) % 3;
    }
    *(u32 *)(SCRATCHPAD_ADDR + 0xFC) = (u32)(var_s1 + 3) & ~3;
    return (s32)prim;
}

typedef struct Spr_00213A40 {
    u8 pad00[0x40];
    f32 res[4];
    f32 in[4];
    u8 pad60[0x98];
    f32 fF8;
    u8 padFC[4];
    u32 f100;
    u8 pad104[0xC];
    f32 f110;
    f32 f114;
} Spr_00213A40;

typedef struct Out_00213A40 {
    f32 s;
    f32 t;
    u32 color;
    f32 q;
    u16 x;
    u16 y;
    u32 z : 24;
    u32 fog : 8;
} Out_00213A40;

typedef struct Weight_00213A40 {
    u16 matrix;
    u16 weight;
    u8 pad4[8];
    s16 x;
    s16 y;
    s16 z;
} Weight_00213A40;

typedef struct In_00213A40 {
    s16 u;
    s16 v;
    u16 count;
    Weight_00213A40 w[1];
} In_00213A40;

#define OUT_00213A40 ((Out_00213A40 *)arg0)
#define IN_00213A40 ((In_00213A40 *)arg1)
#pragma opt_lifetimes reset

/* Transforms one shared vertex on the CPU. */
s8 lRhModelCpu_CalcSharedPoint(s32 arg0, s32 *arg1) {
    Spr_00213A40 *spr = (Spr_00213A40 *)SCRATCHPAD_ADDR;
    register Weight_00213A40 *rec;
    s32 i;
    s32 n;
    s32 last;
    register f32 *src;
    f32 w;
    f32 fog;

    asm {
        vsub.xyzw vf1, vf0, vf0
    }
    n = IN_00213A40->count;
    last = -1;
    rec = IN_00213A40->w;
    src = spr->in;
    for (i = 0; i < n; i++, rec++) {
        register u32 m = rec->matrix;
        register u32 wgt;
        if (last != m) {
            last = m;
            asm {
                ctc2.ni m, vi1
                vlqi.xyzw vf16, (vi1++)
                vlqi.xyzw vf17, (vi1++)
                vlqi.xyzw vf18, (vi1++)
                vlqi.xyzw vf19, (vi1++)
            }
        }
        spr->in[0] = rec->x;
        spr->in[1] = rec->y;
        spr->in[2] = rec->z;
        wgt = rec->weight;
        asm {
            qmtc2.ni wgt, vf4
            lqc2 vf2, 0x0(src)
            vitof12.x vf4, vf4
            vmulax.xyzw ACC, vf16, vf2x
            vmadday.xyzw ACC, vf17, vf2y
            vmaddaz.xyzw ACC, vf18, vf2z
            vmaddw.xyzw vf3, vf19, vf2w
            vmulx.xyzw vf2, vf3, vf4x
            vadd.xyzw vf1, vf1, vf2
        }
    }
    {
        register f32 *dst = spr->res;
        asm {
            vdiv Q, vf0w, vf1w
            vwaitq
            vmulq.xyz vf1, vf1, Q
            sqc2 vf1, 0x0(dst)
        }
    }
    w = spr->res[3];
    if (w < 1.0f || !(w < spr->fF8) || spr->res[0] <= 1.0f || !(spr->res[0] < 4095.0f) || spr->res[1] <= 1.0f ||
        !(spr->res[1] < 4095.0f)) {
        return 0;
    }
    OUT_00213A40->x = (u32)(16.0f * spr->res[0]);
    OUT_00213A40->y = (u32)(16.0f * spr->res[1]);
    OUT_00213A40->z = (u32)(spr->res[2]);
    fog = spr->f110 - spr->f114 * spr->res[3];
    if (fog <= 0.0f) {
        OUT_00213A40->fog = 0;
    } else if (!(fog < 255.0f)) {
        OUT_00213A40->fog = 0xFF;
    } else {
        OUT_00213A40->fog = (u32)(fog);
    }
    OUT_00213A40->color = spr->f100;
    OUT_00213A40->s = IN_00213A40->u / spr->res[3] / 4096.0f;
    OUT_00213A40->t = IN_00213A40->v / spr->res[3] / 4096.0f;
    OUT_00213A40->q = 1.0f / spr->res[3];
    return 1;
}

#undef OUT_00213A40
#undef IN_00213A40

/* From the dotr-decomp CC0 bundle (commit 88c32bb2), chatC/imp/conv.py. */

typedef int DotrWalkAddr;
struct DotrWalkPolygon {
    int unknown_00[31];
    unsigned int key;
};
struct DotrWalkSortPad {
    unsigned char unknown_000[0x120];
    struct DotrWalkPolygon temp;
};
#define DOTR_WALK_SORT_PAD ((struct DotrWalkSortPad *)SCRATCHPAD_ADDR)
#define DOTR_SORT_AT(i) (first + (i) - 1)
#define DOTR_SORT_COPY(k) ((struct DotrWalkPolygon *)(((k) << 7) + (DotrWalkAddr)first - 128))

/* Sorts the CPU drawer's polygons back to front. */
void lRhModelCpu_SortPolygon(void *first_v, void *end_v)
{
    struct DotrWalkPolygon * first = first_v;
    struct DotrWalkPolygon * end = end_v;
    struct DotrWalkSortPad *scratch = DOTR_WALK_SORT_PAD;
    int k;
    int j;
    int i;
    int n = end - first;
    struct DotrWalkPolygon *p;

    i = n >> 1;
    if (i > 0) {
        p = DOTR_SORT_COPY(i);
        do {
            k = i;
            RhMem_CopyMemory16(&scratch->temp, p, 8);
            while ((j = k * 2) <= n) {
                if (j < n && DOTR_SORT_AT(j)->key < DOTR_SORT_AT(j + 1)->key) {
                    j++;
                }
                if (!(scratch->temp.key < DOTR_SORT_AT(j)->key)) {
                    break;
                }
                RhMem_CopyMemory16(DOTR_SORT_COPY(k), DOTR_SORT_COPY(j), 8);
                k = j;
            }
            RhMem_CopyMemory16(DOTR_SORT_COPY(k), &scratch->temp, 8);
            i--;
            p--;
        } while (i > 0);
    }
    if (n > 1) {
        p = DOTR_SORT_COPY(n);
        do {
            RhMem_CopyMemory16(&scratch->temp, p, 8);
            RhMem_CopyMemory16(p, first, 8);
            p--;
            n--;
            k = 1;
            while ((j = k * 2) <= n) {
                if (j < n && DOTR_SORT_AT(j)->key < DOTR_SORT_AT(j + 1)->key) {
                    j++;
                }
                if (!(scratch->temp.key < DOTR_SORT_AT(j)->key)) {
                    break;
                }
                RhMem_CopyMemory16(DOTR_SORT_COPY(k), DOTR_SORT_COPY(j), 8);
                k = j;
            }
            RhMem_CopyMemory16(DOTR_SORT_COPY(k), &scratch->temp, 8);
        } while (n > 1);
    }
}
#undef DOTR_WALK_SORT_PAD
#undef DOTR_SORT_AT
#undef DOTR_SORT_COPY

/* Finishes the CPU drawer's packet. */
void lRhModelCpu_CleanupPacket(u8 *start, u8 *end) {
    s32 *field;
    s32 previous;
    s32 value;
    u8 *cursor;

    cursor = start;
    previous = 0;
    if (cursor < end) {
        do {
            field = (s32 *)(cursor + 4);
            value = *field;
            if (value == previous) {
                *(s32 *)(cursor + 0) = 0x10000000;
                *field = 0;
                *(s32 *)(cursor + 8) = 0;
                *(s32 *)(cursor + 0xC) = 0;
            } else {
                previous = value;
            }
            cursor += 0x80;
        } while (cursor < end);
    }
}

/* Starts a depth-sorted polygon list at `list` with room for `count`. */
void RhZSort_Start(s32 list, s32 count) {
    zSortList = list;
    D_0032F784 = count;
    D_0032F78C = count;
    D_0032F788 = 1;
}

/* Sorts and sends the depth-sorted polygon list. */
void RhZSort_Finish(void) {
    RhBase_SetVifPacketArea(RhZSort_Finish_Pipe(RhBase_GetVifPacketArea()));
}

typedef struct {
    s32 key;
    s32 value;
} Record_00213FC0;

typedef struct {
    s32 *output;
    Record_00213FC0 *end;
    s32 ready;
    Record_00213FC0 *begin;
} State_00213FC0;

/* Sorts the depth-sorted polygon list and writes it into the packet. */
s32 RhZSort_Finish_Pipe(s32 packet) {
    State_00213FC0 *state = (State_00213FC0 *)&zSortList;
    s32 *output = (s32 *)packet;
    Record_00213FC0 *record;

    if (D_0032F78C == D_0032F784) {
        return packet;
    }

    RhMath_HeapSortStruct(state->begin, state->end - state->begin, 8, lRhZSort_ZCompare);
    for (record = state->begin; record < state->end; record++) {
        output[0] = 0x50000000;
        output[1] = record->value;
        output[2] = 0;
        output[3] = 0;
        output += 4;
    }

    state->output = output;
    state->begin = state->end;
    state->ready = 1;
    return (s32)output;
}

/* Compares two polygons by depth. */
s32 lRhZSort_ZCompare(s32 *a, s32 *b) {
    return *a - *b;
}
