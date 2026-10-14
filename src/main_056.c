#include "common.h"

void func_00206430(void *arg0, void *arg1, void *arg2, void *arg3) {
    f32 *plane = arg0;
    f32 *start = arg1;
    f32 *end = arg2;
    f32 *out = arg3;
    f32 numerator;
    f32 denominator;
    f32 magnitude;
    f32 t;

    numerator = -plane[3] - (plane[0] * start[0] + plane[1] * start[1] + plane[2] * start[2]);
    denominator = plane[0] * (end[0] - start[0]) + plane[1] * (end[1] - start[1]) + plane[2] * (end[2] - start[2]);
    magnitude = denominator >= 0.0f ? denominator : -denominator;
    if (magnitude < 0.000001f) {
        denominator = 0.000001f;
    }
    t = numerator / denominator;
    out[0] = start[0] + t * (end[0] - start[0]);
    out[1] = start[1] + t * (end[1] - start[1]);
    out[2] = start[2] + t * (end[2] - start[2]);
    out[3] = 1.0f;
}

typedef struct Vertex_00206530 {
    f32 position[4];
    u8 padding[8];
    u8 color[4];
    f32 weight;
    f32 uv[2];
} Vertex_00206530;

typedef struct PackedUV_00206530 {
    u16 u : 14;
    u16 flags_u : 2;
    u16 v : 14;
    u16 flags_v : 2;
} PackedUV_00206530;

void func_00206530(void *arg0, void *arg1, s32 flags, void *arg3, f32 factor) {
    ((Vertex_00206530 *)arg3)->position[0] = ((Vertex_00206530 *)arg0)->position[0] +
        factor * (((Vertex_00206530 *)arg1)->position[0] - ((Vertex_00206530 *)arg0)->position[0]);
    ((Vertex_00206530 *)arg3)->position[1] = ((Vertex_00206530 *)arg0)->position[1] +
        factor * (((Vertex_00206530 *)arg1)->position[1] - ((Vertex_00206530 *)arg0)->position[1]);
    ((Vertex_00206530 *)arg3)->position[2] = ((Vertex_00206530 *)arg0)->position[2] +
        factor * (((Vertex_00206530 *)arg1)->position[2] - ((Vertex_00206530 *)arg0)->position[2]);
    ((Vertex_00206530 *)arg3)->position[3] = ((Vertex_00206530 *)arg0)->position[3] +
        factor * (((Vertex_00206530 *)arg1)->position[3] - ((Vertex_00206530 *)arg0)->position[3]);
    if (flags & 1) {
        ((Vertex_00206530 *)arg3)->color[0] = func_001A23B0(
            (f32)(u32)((Vertex_00206530 *)arg0)->color[0] + factor *
            (s32)(((Vertex_00206530 *)arg1)->color[0] - ((Vertex_00206530 *)arg0)->color[0]));
        ((Vertex_00206530 *)arg3)->color[1] = func_001A23B0(
            (f32)(u32)((Vertex_00206530 *)arg0)->color[1] + factor *
            (s32)(((Vertex_00206530 *)arg1)->color[1] - ((Vertex_00206530 *)arg0)->color[1]));
        ((Vertex_00206530 *)arg3)->color[2] = func_001A23B0(
            (f32)(u32)((Vertex_00206530 *)arg0)->color[2] + factor *
            (s32)(((Vertex_00206530 *)arg1)->color[2] - ((Vertex_00206530 *)arg0)->color[2]));
        ((Vertex_00206530 *)arg3)->color[3] = func_001A23B0(
            (f32)(u32)((Vertex_00206530 *)arg0)->color[3] + factor *
            (s32)(((Vertex_00206530 *)arg1)->color[3] - ((Vertex_00206530 *)arg0)->color[3]));
        ((Vertex_00206530 *)arg3)->weight = ((Vertex_00206530 *)arg0)->weight +
            factor * (((Vertex_00206530 *)arg1)->weight - ((Vertex_00206530 *)arg0)->weight);
    }
    if (flags & 2) {
        ((Vertex_00206530 *)arg3)->uv[0] = ((Vertex_00206530 *)arg0)->uv[0] +
            factor * (((Vertex_00206530 *)arg1)->uv[0] - ((Vertex_00206530 *)arg0)->uv[0]);
        ((Vertex_00206530 *)arg3)->uv[1] = ((Vertex_00206530 *)arg0)->uv[1] +
            factor * (((Vertex_00206530 *)arg1)->uv[1] - ((Vertex_00206530 *)arg0)->uv[1]);
    }
    if (flags & 0x10) {
        PackedUV_00206530 *src0 = (PackedUV_00206530 *)((u8 *)arg0 + 0x20);
        PackedUV_00206530 *src1 = (PackedUV_00206530 *)((u8 *)arg1 + 0x20);
        PackedUV_00206530 *dst = (PackedUV_00206530 *)((u8 *)arg3 + 0x20);
        s32 u = src0->u;
        s32 v;

        dst->u = u + func_001A23B0(factor * (s32)(src1->u - u));
        v = src0->v;
        dst->v = v + func_001A23B0(factor * (s32)(src1->v - v));
    }
}

INCLUDE_ASM("asm/nonmatchings/main_056", func_00206830);

void func_00206D00(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_00206D30(6, D_00325CC0, arg0, arg1, arg2, arg3, arg4);
}

typedef union {
    f32 f[12];
    __int128 q[3];
} Vertex_00206D30;

typedef struct {
    f32 u;
    f32 v;
} UV_00206D30;

s32 func_00206D30(s32 planeCount, void *planeArg, s32 count, s32 verticesArg,
                  s32 unused, s32 outputArg, s32 flags) {
    f32 *plane = planeArg;
    Vertex_00206D30 intersection;
    UV_00206D30 saved;
    s32 textured;
    s32 planeIndex;
    s32 i;
    u32 outputCount;

    if (count < 2) {
        return count;
    }
    textured = flags & 1;
    if (textured == 0) {
        saved = *(UV_00206D30 *)&((Vertex_00206D30 *)verticesArg)[0].f[6];
    }
    if ((u32)count > 0x155U) {
        count = 0x155;
    }

    for (planeIndex = 0; planeIndex < planeCount; planeIndex++, plane += 5) {
        outputCount = 0;
        for (i = 0; i < count; i++) {
            Vertex_00206D30 *current = &((Vertex_00206D30 *)verticesArg)[i];
            Vertex_00206D30 *next = &((Vertex_00206D30 *)verticesArg)[(i + 1) % count];
            f32 distance = (plane[3] + (plane[0] * current->f[0] +
                            plane[1] * current->f[1] + plane[2] * current->f[2])) / plane[4];
            f32 nextDistance = (plane[3] + (plane[0] * next->f[0] +
                                plane[1] * next->f[1] + plane[2] * next->f[2])) / plane[4];

            if (distance < 0.0f && nextDistance < 0.0f) {
                continue;
            }
            if (!(distance < 0.0f) && !(nextDistance < 0.0f)) {
                ((Vertex_00206D30 *)outputArg)[outputCount++] = *current;
            } else {
                func_00206530(current, next, flags, &intersection,
                    (distance >= 0.0f ? distance : -distance) /
                    ((distance >= 0.0f ? distance : -distance) +
                     (nextDistance >= 0.0f ? nextDistance : -nextDistance)));
                if (!(distance < 0.0f)) {
                    ((Vertex_00206D30 *)outputArg)[outputCount++] = *current;
                }
                ((Vertex_00206D30 *)outputArg)[outputCount++] = intersection;
            }
            if (outputCount >= 0x155U) {
                outputCount = 0x155;
                break;
            }
        }
        if (count < 3 && count < (s32)outputCount) {
            outputCount = count;
        }
        for (i = 0; i < (s32)outputCount; i++) {
            ((Vertex_00206D30 *)verticesArg)[i] = ((Vertex_00206D30 *)outputArg)[i];
        }
        count = outputCount;
    }
    if (textured == 0) {
        *(UV_00206D30 *)&((Vertex_00206D30 *)verticesArg)[0].f[6] = saved;
    }
    return count;
}

typedef struct Vertex_002070F0 {
    f32 position[4];
    u8 padding[0x20];
} Vertex_002070F0;

s32 func_002070F0(void *matrix, s32 count, void *vertices, s32 arg3, void *arg4, s32 flags, f32 *depth) {
    f32 identity[16];
    s32 result;
    s32 i;
    Vertex_002070F0 *vertex;
    f32 sum;

    sum = 0.0f;
    if (matrix == NULL) {
        func_0020EBA0(identity);
        matrix = identity;
    }
    func_0020BAF0((s32)matrix);
    vertex = vertices;
    for (i = 0; i < count; i++) {
        vertex[i].position[3] = 1.0f;
        func_0020CDD0(&vertex[i], NULL, &vertex[i]);
        sum += vertex[i].position[2];
    }
    func_0020BB50();
    if (flags >= 0) {
        result = func_00206D30(6, D_00325CC0, count, (s32)vertices, arg3, (s32)arg4, flags);
    }
    if (depth != NULL) {
        *depth = sum / (f32)result;
    }
    return result;
}

typedef union PackedXYZ_00207230 {
    struct {
        s16 x;
        s16 y;
        u8 depth[3];
        u8 flags;
    } components;
    struct {
        u64 xy : 32;
        u64 z : 24;
        u64 flags : 8;
    } bits;
} PackedXYZ_00207230;

typedef struct Vertex_00207230 {
    f32 position[4];
    PackedXYZ_00207230 xyz;
    u8 padding[0x18];
} Vertex_00207230;

void func_00207230(void *matrix, s32 count, void *vertices) {
    f32 identity[16];
    s32 i;
    PackedXYZ_00207230 *xyz;
    Vertex_00207230 *vertex;
    f32 reciprocal;

    vertex = vertices;
    if (matrix == NULL) {
        func_0020EC00(identity);
        matrix = identity;
    }
    func_0020BAF0((s32)matrix);
    for (i = 0; i < count; i++, vertex++) {
        xyz = &vertex->xyz;
        vertex->position[3] = 1.0f;
        func_0020CDD0(vertex, NULL, vertex);
        reciprocal = 1.0f / vertex->position[3];
        xyz->components.x = func_001A23B0(16.0f * (vertex->position[0] * reciprocal));
        xyz->components.y = func_001A23B0(16.0f * (vertex->position[1] * reciprocal));
        xyz->bits.z = (u32)func_001A23B0(vertex->position[2] * reciprocal);
        xyz->components.flags = 0;
    }
    func_0020BB50();
}

void func_00207360(void) {
    func_0020BAF0(0);
    func_002073D0(D_00325D38, 0x01E08000, 0xC);
}

void func_002073A0(void) {
    func_00207510(D_00325D38);
    func_0020BB50();
}

typedef struct Tag_002073D0 {
    u16 qwc;
    u8 pad2;
    u8 id;
    s32 next;
    u32 vif0;
    u32 vif1;
} Tag_002073D0;

typedef struct Node_002073D0 {
    u16 qwc;
    u16 mark;
    struct Node_002073D0 *next;
} Node_002073D0;

typedef struct Context_002073D0 {
    Node_002073D0 *table;
    Tag_002073D0 *start;
    Tag_002073D0 *head;
    s32 depth;
} Context_002073D0;

void func_002073D0(u8 *arg0, s32 arg1, s32 arg2) {
    extern u8 D_00293D80[];
    s32 count;
    Node_002073D0 *node;
    u64 *packet;
    Context_002073D0 *ctx;

    packet = (u64 *)func_00209D20();
    count = 1 << arg2;
    packet[1] = 0;
    packet[0] = 0;
    ctx = (Context_002073D0 *)arg0;
    ctx->start = (Tag_002073D0 *)packet;
    packet[2] = 0x100000000000800EULL;
    packet[3] = 0xE;
    packet = func_0020B380(packet + 4, D_00293D80, 0xE);
    ctx->start->qwc = 0xF;
    ctx->start->id = 0x10;
    ctx->start->vif0 = 0x11000000;
    ctx->start->vif1 = ctx->start->qwc | 0x51000000;
    packet[1] = 0;
    packet[0] = 0;
    ctx->head = (Tag_002073D0 *)packet;
    ctx->head->id = 0x10;
    func_00209D30((s32)(packet + 2));
    ctx->depth = arg2;
    ctx->table = (Node_002073D0 *)arg1;
    node = (Node_002073D0 *)arg1;
    node += count - 1;
    while (--count != 0) {
        node->next = node - 1;
        node->mark = 7;
        node->qwc = 0;
        node--;
    }
    node->next = (Node_002073D0 *)-1;
    node->mark = 7;
    node->qwc = 0;
}

u8 *func_00207500(void) {
    return D_00325D38;
}

typedef struct Node_00207510 {
    u16 unused0;
    u8 unused2;
    u8 tag;
    struct Node_00207510 *next;
} Node_00207510;

typedef struct Context_00207510 {
    Node_00207510 *table;
    s32 unused4;
    Node_00207510 *head;
    s32 depth;
} Context_00207510;

void func_00207510(void *arg0) {
    Node_00207510 *tail;
    Node_00207510 *node;
    Node_00207510 *next;
    Context_00207510 *ctx = arg0;

    tail = NULL;
    node = ctx->table + ((1 << ctx->depth) - 1);
    do {
        next = node->next;
        if (*(u16 *)((u8 *)node + 2) != 7) {
            if (tail != NULL) {
                if (tail->tag == 0x50) {
                    tail->next = (Node_00207510 *)((u8 *)tail + 0x20);
                    tail = (Node_00207510 *)((u8 *)tail + 0x10);
                }
                tail->tag = 0x20;
                tail->next = node;
            } else {
                ctx->head->tag = 0x20;
                ctx->head->next = node;
            }
            tail = node;
        }
        node = next;
    } while (next != (Node_00207510 *)-1);
    if (tail != NULL) {
        if (tail->tag == 0x50) {
            tail->next = (Node_00207510 *)((u8 *)tail + 0x20);
            tail = (Node_00207510 *)((u8 *)tail + 0x10);
        }
        tail->tag = 0x20;
        tail->next = (Node_00207510 *)func_00209D20();
    }
}

void func_002075F0(s32 arg0, s32 arg1, s32 arg2) {
    func_00209D30(func_00207650(func_00209D20(), arg0, arg1, arg2));
}

INCLUDE_ASM("asm/nonmatchings/main_056", func_00207650);

INCLUDE_ASM("asm/nonmatchings/main_056", func_00207AA0);

s32 func_00207F60(void) {
    s32 temp_v0;

    temp_v0 = func_00209D20();
    func_00209D30(func_00207FA0(temp_v0));
    return temp_v0;
}

s32 func_00207FA0(s32 arg0) {
    ((s64 *)arg0)[3] = 0;
    ((s64 *)arg0)[2] = 0;
    ((s64 *)arg0)[1] = 0;
    ((s64 *)arg0)[0] = 0;
    ((s8 *)arg0)[3] = 0x50;
    ((s8 *)arg0)[0x13] = 0x20;
    return arg0 + 0x20;
}

void func_00207FD0(s32 arg0, s32 arg1, s32 arg2) {
    func_00209D30(func_00208030(func_00209D20(), arg0, arg1, arg2));
}

s32 func_00208030(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 var_t0;
    u32 temp_v0;

    temp_v0 = (1 << *(s32 *)(arg2 + 0xC)) - 2;
    if (temp_v0 < (u32) arg3) {
        arg3 = temp_v0;
    }
    var_t0 = arg3 * 8;
    *(s32 *)(arg1 + 4) = *(s32 *)(*(s32 *)arg2 + var_t0 + 4);
    *(s32 *)(*(s32 *)arg2 + var_t0 + 4) = arg1;
    *(s64 *)(arg0 + 8) = 0;
    *(s64 *)arg0 = 0;
    *(s8 *)(arg0 + 3) = 0x60;
    return arg0 + 0x10;
}

void func_00208090(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_00209D30(func_00208110(func_00209D20(), arg0, arg1, arg2, arg3, arg4));
}

typedef struct {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Color_00208110;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Xyzf_00208110;

typedef struct {
    u16 count;
    u16 kind;
    u32 flags;
    u64 regs;
} Header_00208110;

typedef struct {
    Header_00208110 header;
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    f32 q;
    f32 s0;
    f32 t0;
    Xyzf_00208110 v0;
    f32 s1;
    f32 t1;
    Xyzf_00208110 v1;
    u64 extra[4];
} Packet_00208110;

s32 func_00208110(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    extern Color_00208110 D_00293ED0;
    extern s32 func_002086D0();
    Color_00208110 def;
    Packet_00208110 packet;
    u8 *color;

    def = D_00293ED0;
    ((Header_00208110 *)&packet)->kind = 0x26;
    ((Header_00208110 *)&packet)->count = 5;
    ((Header_00208110 *)&packet)->regs = 0x42421;
    ((Header_00208110 *)&packet)->flags = 0;
    color = (u8 *)arg5;
    if (color == NULL) {
        color = (u8 *)&def;
    }
    packet.r = color[2];
    packet.g = color[1];
    packet.b = color[0];
    packet.a = color[3];
    packet.q = 1.0f;
    packet.v0.x = 0x6BF8;
    packet.v0.y = 0x71F8;
    packet.v0.z = 0xFFFFF7;
    packet.v0.fog = 0;
    packet.v1.x = 0x93F8;
    packet.v1.y = 0x8DF8;
    packet.v1.z = 0xFFFFF7;
    packet.v1.fog = 0;
    packet.s0 = 0.0f;
    packet.t0 = 0.0f;
    packet.s1 = 0.625f;
    packet.t1 = 0.875f;
    func_002086D0(&packet, arg4);
    func_002087A0(&packet, arg3);
    return func_00207650(arg0, (s32)&packet, arg1, arg2);
}

typedef struct {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Color_00208280;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Xyzf_00208280;

typedef struct {
    u16 count;
    u16 kind;
    u32 flags;
    u64 regs;
} Header_00208280;

typedef struct {
    Header_00208280 header;
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    f32 q;
    f32 s0;
    f32 t0;
    Xyzf_00208280 v0;
    f32 s1;
    f32 t1;
    Xyzf_00208280 v1;
    u64 extra[1];
} Packet_00208280;

typedef struct {
    u8 pad0[4];
    u8 : 2;
    u8 tcc : 1;
    u8 : 5;
    u8 pad5[3];
} Tex0_00208280;

typedef struct {
    Tex0_00208280 tex0;
    u64 tex1;
    u64 clamp;
} Regs_00208280;

s32 func_00208280(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, u8 *arg6) {
    extern Color_00208280 D_00293ED8;
    extern s32 func_00208870();
    Color_00208280 def;
    Packet_00208280 packet;
    Regs_00208280 regs;
    s32 obj;

    def = D_00293ED8;
    ((Header_00208280 *)&packet)->kind = 0x26;
    ((Header_00208280 *)&packet)->count = 5;
    ((Header_00208280 *)&packet)->regs = 0x42421;
    ((Header_00208280 *)&packet)->flags = 0;
    func_002086D0(&packet, 0x44 | ((s64)0x80 << 32));
    if (arg6 == NULL) {
        arg6 = (u8 *)&def;
    }
    packet.r = arg6[2];
    packet.g = arg6[1];
    packet.b = arg6[0];
    packet.a = arg6[3];
    packet.q = 1.0f;
    packet.v0.x = arg4 + 0x6BF8;
    packet.v0.y = arg5 + 0x71F8;
    packet.v0.z = 0xFFFFFF;
    packet.v0.fog = 0;
    packet.v1.x = arg4 + 0x93F8;
    packet.v1.y = arg5 + 0x8DF8;
    packet.v1.z = 0xFFFFFF;
    packet.v1.fog = 0;
    packet.s0 = 0.0f;
    packet.t0 = 0.0f;
    packet.s1 = 0.625f;
    packet.t1 = 0.875f;
    arg0 = func_0020F290(arg0);
    obj = func_0020F290(func_00208870(arg0, func_00209E50(), arg3, &regs.tex0, &regs.tex1));
    regs.tex0.tcc = 1;
    return func_00207650(obj, (s32)&packet, arg1, arg2);
}

void func_00208460(void) {
    func_00209D30(func_0020F290(func_00209D20()));
}

void func_00208490(s32 arg0) {
    func_00209D30(func_0020A0B0(func_00209D20(), arg0));
}

s32 func_002084D0(s32 arg0, s64 arg1) {
    *(s64 *)((u8 *)arg0 + 8) = 0;
    *(s64 *)arg0 = 0;
    *(s8 *)((u8 *)arg0 + 3) = 0x10;
    *(s64 *)((u8 *)arg0 + 0x10) = 0x1000000000008001LL;
    *(s64 *)((u8 *)arg0 + 0x18) = 0xE;
    *(s64 *)((u8 *)arg0 + 0x20) = arg1;
    *(s64 *)((u8 *)arg0 + 0x28) = 8;
    *(s16 *)arg0 = 2;
    *(s32 *)((u8 *)arg0 + 8) = 0x11000000;
    *(s32 *)((u8 *)arg0 + 0xC) = 0x51000002;
    return arg0 + 0x30;
}

void *func_00208530(void *arg0, s32 arg1) {
    *(s64 *)((u8 *)arg0 + 8) = 0;
    *(s64 *)arg0 = 0;
    *((u8 *)arg0 + 3) = 0x10;
    *(u64 *)((u8 *)arg0 + 0x10) = 0x1000000000008001ULL;
    *(s64 *)((u8 *)arg0 + 0x18) = 0xE;
    *(s64 *)((u8 *)arg0 + 0x20) = arg1;
    *(s64 *)((u8 *)arg0 + 0x28) = 0x45;
    *(u16 *)arg0 = 2;
    *(u32 *)((u8 *)arg0 + 8) = 0x11000000;
    *(u32 *)((u8 *)arg0 + 0xC) = 0x51000002;
    return (u8 *)arg0 + 0x30;
}

void func_002085A0(s32 arg0) {
    func_00209D30(func_002085E0(func_00209D20(), arg0));
}

s32 func_002085E0(s32 arg0, s32 arg1) {
    u64 value;

    if (arg1 < 0 || arg1 >= 4) {
        return arg0;
    }

    value = D_00293EE0[arg1];
    *(u64 *)(arg0 + 8) = 0;
    *(u64 *)arg0 = 0;
    *(u8 *)(arg0 + 3) = 0x10;
    *(u64 *)(arg0 + 0x10) = 0x1000000000008001ULL;
    *(u64 *)(arg0 + 0x18) = 0xE;
    *(u64 *)(arg0 + 0x20) = value;
    *(u64 *)(arg0 + 0x28) = 0x44;
    *(u16 *)arg0 = 2;
    *(u32 *)(arg0 + 8) = 0x11000000;
    *(u32 *)(arg0 + 0xC) = 0x51000002;
    return arg0 + 0x30;
}

typedef struct {
    s64 value;
    s64 padding;
} Entry_00208680;

extern Entry_00208680 D_00293D80[][7];

s64 func_00208680(s32 arg0, s32 arg1) {
    if (arg1 < 0 || arg1 >= 7) {
        return -1;
    }
    return D_00293D80[arg0][arg1].value;
}

typedef struct {
    u16 index;
    u16 flags;
    u8 padding[0xC];
    s64 values[1];
} Buffer_002086D0;

s32 func_002086D0(void *arg0, s64 arg1) {
    Buffer_002086D0 *buffer = arg0;
    u16 index = buffer->index;
    s64 *values = (s64 *)((u8 *)arg0 + 0x10);

    buffer->flags |= 0x200;
    values[index] = arg1;
    return 1;
}

typedef struct {
    u64 reserved0 : 5;
    u64 flag : 1;
    u64 mode : 3;
    u64 reserved9 : 55;
} Flags_00208700;

s32 func_00208700(void *arg0, void *arg1, s32 arg2) {
    u8 *base = (u8 *)arg0 + 0x10;
    u16 count = *(u16 *)arg0;
    u64 *dst;

    if (!(*(u16 *)((u8 *)arg0 + 2) & 0x20)) {
        return 0;
    }
    if (arg1 == NULL) {
        return 0;
    }
    dst = (u64 *)(base + count * 8);
    dst[1] = *(u64 *)((u8 *)arg1 + 0x30);
    dst[2] = *(u64 *)((u8 *)arg1 + 0x40);
    ((Flags_00208700 *)(dst + 2))->flag = (((Flags_00208700 *)(dst + 2))->mode = arg2);
    return 1;
}

typedef struct {
    u16 count;
    u16 flags;
    u8 padding[12];
    u8 data[1];
} Header_002087A0;

void func_00208870(s32, s32, s32, void *, void *);

s32 func_002087A0(void *arg0, s32 arg1) {
    Header_002087A0 *header = arg0;
    u16 count = header->count;
    u8 *data = header->data;

    if (!(header->flags & 0x20)) {
        return 0;
    }
    func_00208870(0, 0, arg1, data + (count & 0xFFFF) * 8 + 8,
                 data + (count & 0xFFFF) * 8 + 0x10);
    return 1;
}

void func_00208800(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    extern s32 func_00208870();

    func_00209D30(func_00208870(func_00209D20(), arg0, arg1, arg2, arg3));
}

INCLUDE_ASM("asm/nonmatchings/main_056", func_00208870);

typedef struct Buffer_00208CB0 {
    u16 index;
    u16 flags;
    u8 padding[0xC];
    s64 values[1];
} Buffer_00208CB0;

s32 func_00208CB0(void *arg0, s64 arg1) {
    Buffer_00208CB0 *buffer = arg0;
    u16 index = buffer->index;
    s64 *values = buffer->values;
    u16 *flags = &buffer->flags;

    if (!(*flags & 0x20)) {
        return 0;
    }
    *flags |= 0x4000;
    *(s64 *)((u8 *)values + (index & 0xFFFF) * 8 + 0x18) = arg1;
    return 1;
}

s64 func_00208D00(s32 arg0) {
    s64 ret;

    if (arg0 < 0 || arg0 >= 4) {
        ret = 0;
    } else {
        ret = D_002D0830[arg0];
    }
    return ret;
}

void *func_00208D40(void *arg0, s32 arg1) {
    s32 *packet = arg0;

    packet[0] = 0x10000001;
    packet[1] = 0;
    packet[2] = 0x10000000;
    packet[3] = 0x68014000;
    if (!(arg1 & 2) || !D_00325E2C) {
        if (arg1 & 0x40) {
            if (arg1 & 0x20) {
                packet[4] = 0x274;
            } else if (arg1 & 0x10) {
                packet[4] = 0xE8;
            } else {
                packet[4] = 0xE8;
            }
        } else {
            if (arg1 & 0x20) {
                packet[4] = 0x1A4;
            } else if (arg1 & 0x10) {
                packet[4] = 0x30;
            } else {
                packet[4] = 0x30;
            }
        }
    } else {
        if (arg1 & 0x20) {
            packet[4] = 0x6D4;
        } else {
            packet[4] = 0x580;
        }
    }
    packet[5] = 0;
    packet[6] = 0;
    packet[7] = 0x10000000;
    D_00325DD0 = arg1;
    return packet + 8;
}

typedef struct {
    s32 flags;
    void *data;
    s32 field8;
    s32 fieldC;
} Header_00208E40;

void *func_00208E40(void *arg0) {
    Header_00208E40 *header = arg0;

    header->flags = 0x20000000;
    header->data = (u8 *)arg0 + 0x20;
    header->field8 = 0;
    header->fieldC = 0;
    return (u8 *)arg0 + 0x20;
}

void *func_00208E60(void *arg0, void *arg1) {
    ((u32 *)arg0)[0] = 0x10000004;
    ((u32 *)arg0)[1] = 0;
    ((u32 *)arg0)[2] = 0;
    ((u32 *)arg0)[3] = 0x6C040044;
    func_0020B380((u8 *)arg0 + 0x10, arg1, 4);
    return (u8 *)arg0 + 0x50;
}

void *func_00208EB0(void *arg0, void *arg1) {
    ((s32 *)arg0)[0] = 0x10000004;
    ((s32 *)arg0)[1] = 0;
    ((s32 *)arg0)[2] = 0;
    ((s32 *)arg0)[3] = 0x6C040056;
    func_0020B380((u8 *)arg0 + 0x10, arg1, 4);
    return (u8 *)arg0 + 0x50;
}

s32 func_00208F00(s32 packet, void *arg1, void *arg2, s32 arg3) {
    u8 buffer[0x50];
    s32 matrix;

    matrix = ((u32)buffer + 0xF) & ~0xF;
    if (arg3 >= 0 && arg3 < 3 && (arg1 == NULL || arg2 == NULL)) {
        return packet;
    }
    switch (arg3) {
    case 0:
        D_00325D90 = ((f32 *)arg1)[1];
        D_00325D94 = ((f32 *)arg1)[2];
        D_00325D98 = ((f32 *)arg1)[3];
        D_00325D50 = ((f32 *)arg2)[0];
        D_00325D60 = ((f32 *)arg2)[1];
        D_00325D70 = ((f32 *)arg2)[2];
        break;
    case 1:
        D_00325DA0 = ((f32 *)arg1)[1];
        D_00325DA4 = ((f32 *)arg1)[2];
        D_00325DA8 = ((f32 *)arg1)[3];
        D_00325D54 = ((f32 *)arg2)[0];
        D_00325D64 = ((f32 *)arg2)[1];
        D_00325D74 = ((f32 *)arg2)[2];
        break;
    case 2:
        D_00325DB0 = ((f32 *)arg1)[1];
        D_00325DB4 = ((f32 *)arg1)[2];
        D_00325DB8 = ((f32 *)arg1)[3];
        D_00325D58 = ((f32 *)arg2)[0];
        D_00325D68 = ((f32 *)arg2)[1];
        D_00325D78 = ((f32 *)arg2)[2];
        break;
    }
    if (packet != 0) {
        u32 *tag = (u32 *)packet;

        func_0020B380((void *)matrix, &D_00325D90, 4);
        func_0020BC00(matrix, &D_00325D50);
        tag[0] = 0x10000004;
        tag[1] = 0;
        tag[2] = 0;
        tag[3] = 0x6C04003F;
        func_0020B380((void *)(packet + 0x10), (void *)matrix, 4);
        packet = (s32)(tag + 4) + 0x40;
    } else if (arg3 < 0) {
        func_00198948(&D_00325D50, 0, 0x40);
        func_00198948(&D_00325D90, 0, 0x40);
    }
    return packet;
}

typedef struct Packet_00209110 {
    u32 header[4];
    f32 values[8];
} Packet_00209110;

s32 func_00209110(s32 arg0, void *arg1, void *arg2, f32 fparg0, f32 fparg1, f32 fparg2) {
    extern void func_0020B340(f32 *, void *, s32);
    extern f32 D_00325E00[4];
    extern f32 D_00325E10[4];
    extern f32 D_00325E20;
    extern f32 D_00325E24;
    extern f32 D_00325E28;
    Packet_00209110 *packet;
    f32 temp_f2;

    packet = (Packet_00209110 *)arg0;
    if ((arg1 == NULL) || (arg2 == NULL)) {
        packet->header[0] = 0x10000002;
        packet->header[1] = 0;
        packet->header[2] = 0x11000000;
        packet->header[3] = 0x6C020054;
        func_0020B440((s64 *)packet->values, 0, 4);
        packet++;
        D_00325E2C = 0;
    } else {
        packet->header[0] = 0x10000002;
        packet->header[1] = 0;
        temp_f2 = fparg1 - fparg0;
        packet->header[2] = 0x11000000;
        packet->header[3] = 0x6C020054;
        packet->values[0] = ((f32 *)arg1)[1];
        packet->values[1] = ((f32 *)arg1)[2];
        packet->values[2] = ((f32 *)arg1)[3];
        packet->values[3] = (fparg2 * fparg1) / temp_f2;
        packet->values[4] = ((f32 *)arg2)[0];
        packet->values[5] = ((f32 *)arg2)[1];
        packet->values[6] = ((f32 *)arg2)[2];
        packet->values[7] = fparg2 / temp_f2;
        packet++;
        func_0020B340(D_00325E00, arg1, 4);
        func_0020B340(D_00325E10, arg2, 4);
        D_00325E20 = fparg0;
        D_00325E24 = fparg1;
        D_00325E28 = fparg2;
        D_00325E2C = 1;
    }
    return (s32)packet;
}

typedef struct Vec4_00209270 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4_00209270;

extern Vec4_00209270 D_00325E00;
extern Vec4_00209270 D_00325E10;
extern f32 D_00325E20;
extern f32 D_00325E24;
extern f32 D_00325E28;
extern s32 D_00325E2C;

s32 func_00209270(void *arg0, void *arg1, f32 *arg2, f32 *arg3, f32 *arg4) {
    if (arg0 != NULL) {
        *(Vec4_00209270 *)arg0 = D_00325E00;
    }
    if (arg1 != NULL) {
        *(Vec4_00209270 *)arg1 = D_00325E10;
    }
    if (arg2 != NULL) {
        *arg2 = D_00325E20;
    }
    if (arg3 != NULL) {
        *arg3 = D_00325E24;
    }
    if (arg4 != NULL) {
        *arg4 = D_00325E28;
    }
    return D_00325E2C;
}

typedef struct Packet_00209320 {
    s32 tag0;
    s32 zero0;
    s32 zero1;
    s32 command0;
    f32 right;
    f32 left;
    f32 near_value;
    f32 far_value;
    s32 tag1;
    s32 zero2;
    s32 zero3;
    s32 command1;
    s32 enabled;
    s32 zero4;
    s32 zero5;
    s32 zero6;
} Packet_00209320;

void *func_00209320(void *arg0, s32 arg1, f32 fparg0, f32 fparg1, f32 fparg2) {
    f32 temp_f2;
    s32 enabled;
    Packet_00209320 *packet = arg0;

    packet->tag0 = 0x10000001;
    packet->zero0 = 0;
    packet->zero1 = 0;
    packet->command0 = 0x6C014052;
    temp_f2 = 2.0f * fparg0;
    packet->right = 645.0f / temp_f2;
    packet->left = -645.0f / temp_f2;
    packet->near_value = 0.01f + fparg1;
    packet->far_value = fparg2 - 0.01f;
    packet->tag1 = 0x10000001;
    packet->zero2 = 0;
    packet->zero3 = 0;
    packet->command1 = 0x6C01405A;
    if (arg1 == 1) {
        enabled = 1;
    } else {
        enabled = 0;
    }
    packet->enabled = enabled;
    packet->zero4 = 0;
    packet->zero5 = 0;
    packet->zero6 = 0;
    return (u8 *)arg0 + 0x40;
}

typedef struct Packet_002093E0 {
    s32 tag[4];
    f32 values[4];
} Packet_002093E0;

extern f32 D_00325DE0;
extern f32 D_00325DE4;
extern f32 D_00325DE8;
extern f32 D_00325DEC;
extern f32 D_00325DF0;
extern f32 D_00325DF4;
extern f32 D_00325DF8;
extern f32 D_00325DFC;

void *func_002093E0(void *arg0, f32 fparg0, f32 fparg1, f32 fparg2, f32 fparg3) {
    Packet_002093E0 *packet = arg0;
    f32 temp_f1;
    f32 temp_f2;

    packet->tag[0] = 0x10000001;
    packet->tag[1] = 0;
    packet->tag[2] = 0x10000000;
    temp_f2 = 255.0f / (fparg3 - fparg2);
    packet->tag[3] = 0x6C014053;
    packet->values[0] = temp_f2;
    temp_f1 = 255.0f / (fparg1 - fparg0);
    packet->values[1] = fparg2 * temp_f2;
    packet->values[2] = temp_f1;
    packet->values[3] = fparg1 * temp_f1;
    D_00325DE0 = packet->values[2];
    D_00325DE4 = packet->values[3];
    D_00325DE8 = packet->values[0];
    D_00325DEC = packet->values[1];
    D_00325DF0 = fparg0;
    D_00325DF4 = fparg1;
    D_00325DF8 = fparg2;
    D_00325DFC = fparg3;
    return packet + 1;
}

typedef struct {
    u32 header[4];
    f32 value_10;
    f32 value_14;
    f32 value_18;
    f32 value_1C;
} Packet_00209490;

extern f32 D_00325DE0;
extern f32 D_00325DE4;
extern f32 D_00325DE8;
extern f32 D_00325DEC;

void *func_00209490(void *arg0, s32 arg1, s32 arg2) {
    Packet_00209490 *packet = arg0;

    packet->header[0] = 0x10000001;
    packet->header[1] = 0;
    packet->header[2] = 0x10000000;
    packet->header[3] = 0x6C014053;
    if (arg1 != 0) {
        packet->value_18 = D_00325DE0;
        packet->value_1C = D_00325DE4;
    } else {
        packet->value_18 = 0.0f;
        packet->value_1C = 255.0f;
    }
    if (arg2 != 0) {
        packet->value_10 = D_00325DE8;
        packet->value_14 = D_00325DEC;
    } else {
        packet->value_10 = 0.0f;
        packet->value_14 = 0.0f;
    }
    return (u8 *)arg0 + 0x20;
}

typedef struct Flags_00209510 {
    u8 pad0 : 6;
    u8 enabled : 1;
    u8 pad7 : 1;
} Flags_00209510;

typedef struct State_00209510 {
    u8 pad0[0x274];
    u8 *decoder;
    s32 option;
    s32 base;
    s32 current;
    s32 size;
    s32 ready;
    s32 start;
    s32 end;
    s32 field294;
    s32 field298;
} State_00209510;

typedef struct Env_00209510 {
    u8 pad0[6];
    s16 field6;
    u8 pad8[20];
} Env_00209510;

typedef struct Mode_00209510 {
    u32 clock : 2;
    u32 gate : 1;
    u32 gate_source : 1;
    u32 gate_mode : 2;
    u32 zero_return : 1;
    u32 enable : 1;
    u32 compare_interrupt : 1;
    u32 overflow_interrupt : 1;
    u32 compare_flag : 1;
    u32 overflow_flag : 1;
    u32 reserved : 20;
} Mode_00209510;

s32 func_0017B770(s32, s32);
void func_001849B0(void);
s32 func_00186238(void *);
void func_00186470(u8 *, s32);
void func_00186BD0(void);
extern u8 D_00286980[];
extern u8 D_00293F10[];
extern u8 D_00293F14[];
extern u8 D_00293F18[];
extern s32 D_003261C8;

s32 func_00209510(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    Env_00209510 env;
    Mode_00209510 mode;
    State_00209510 *state = (State_00209510 *)D_00325F50;
    s32 *packet;

    func_00198948(D_00325F50, 0, 0x2A0);
    D_003261C8 = arg6;
    if (func_001FFFC0() == 0) {
        return 0;
    }
    func_00186FC8();
    func_00186BD0();
    func_001849B0();
    func_00186148(1);
    func_00186410(&env);
    env.field6 = 0x100;
    func_00186238(&env);
    func_00184810(0, *(s16 *)(D_00293F10 + arg0 * 0x28),
                    *(s16 *)(D_00293F14 + arg0 * 0x28),
                    *(s16 *)(D_00293F18 + arg0 * 0x28));
    state->decoder = (u8 *)func_00186120(1);
    ((Flags_00209510 *)state->decoder)->enabled = 1;
    func_0020AD10(state, arg0, arg1, arg2);
    mode.clock = 3;
    mode.gate = 0;
    mode.gate_source = 0;
    mode.gate_mode = 0;
    mode.zero_return = 0;
    mode.enable = 1;
    mode.compare_interrupt = 0;
    mode.overflow_interrupt = 0;
    mode.compare_flag = 0;
    mode.overflow_flag = 1;
    mode.reserved = 0;
    *(s32 *)0x10000810 = *(s32 *)&mode;
    *(s32 *)0x10000800 = 0;
    state->start = arg3;
    state->end = arg4;
    state->size = arg5;
    state->ready = 1;
    state->base = arg3;
    state->current = arg3;
    func_0017B770(func_0017B7D0(), 0x20);
    state->field294 = 0;
    state->field298 = 0;
    packet = (s32 *)func_0020B000(state->base);
    func_0020BA70();
    func_0020DDB0();
    func_002173D0();
    packet[0] = 0x70000000;
    packet[1] = 0;
    packet[2] = 0;
    packet[3] = 0;
    func_0017BB60(0);
    func_00185578(0, 0);
    func_00186470(state->decoder, state->base);
    func_00185578(0, 0);
    func_00186470(state->decoder, (s32)D_00286980);
    func_00185578(0, 0);
    func_00213F60(state->base, state->base + state->size);
    func_001854E0(0);
    return 1;
}

s32 func_00209870(void) {
    func_0020DEE0();
    func_00200210();
    func_0020BA80();
    func_002173F0();
    return 1;
}

void func_002098B0(s32 arg0) {
    extern void func_001869C0(u8 *, s32, s32);
    extern void func_001885C8(void);
    extern u8 D_00293F1C[];
    extern u8 D_00293F20[];
    extern u8 *D_003261C4;
    s32 *packet;

    func_001869C0(D_003261C4, 0, 0);
    func_00186148(1);
    func_00185578(0, 0);
    func_001849B0();
    func_001885C8();
    func_00184810(0, *(s16 *)(D_00293F10 + arg0 * 0x28),
                    *(s16 *)(D_00293F14 + arg0 * 0x28),
                    *(s16 *)(D_00293F18 + arg0 * 0x28));
    D_0032618C = *(s32 *)(D_00293F1C + arg0 * 0x28);
    D_00326190 = *(s32 *)(D_00293F20 + arg0 * 0x28);
    packet = (s32 *)func_0020B000(*(s32 *)0x003261CC);
    packet[0] = 0x70000000;
    packet[1] = 0;
    packet[2] = 0;
    packet[3] = 0;
    func_0017BB60(0);
    func_00185578(0, 0);
    func_00186470(D_003261C4, *(s32 *)0x003261CC);
    func_00185578(0, 0);
}

typedef struct State_002099D0 {
    u8 pad0[0x240];
    s32 width;
    u8 pad244[8];
    s32 display;
    u8 pad250[0x10];
    s16 x;
    u8 pad262[2];
    s16 y;
    u8 pad266[6];
    s32 frame;
    u8 pad270[0xC];
    s32 dmaAddress;
    s32 dmaBuffer;
    s32 dmaSize;
    s32 currentBuffer;
    s32 buffer0;
    s32 buffer1;
    void (*beforeDisplay)(void);
    void (*beforeWait)(void);
} State_002099D0;


s32 func_002099D0(void) {
    extern s32 func_00185578();
    extern s32 func_0020B1E0();
    extern u8 D_00293F14[];
    extern s32 D_00325E30;
    extern s32 D_00326188;
    State_002099D0 *state = (State_002099D0 *)D_00325F50;
    s32 result;
    s32 width;
    s32 period;
    s32 remaining;
    s32 *packet;
    u8 *display;

    func_00213F90();
    func_00200350();
    func_00217400();
    packet = (s32 *)D_003261D0;
    packet[0] = 0x70000000;
    packet[1] = 0;
    packet[2] = 0;
    packet[3] = 0;
    (void)*(volatile u32 *)0x10000800;
    if (func_00185578(0, 0) < 0) {
        func_002098B0(D_00326188);
    }
    if (state->beforeWait != NULL) {
        state->beforeWait();
    }
    remaining = D_00325E30;
    if (*(s32 *)(D_00293F14 + D_00326188 * 0x28) == 2) {
        width = 0x1C0;
        period = 0x208;
    } else {
        width = 0x200;
        period = 0x26C;
    }
    while (remaining-- >= 0) {
        result = func_001854E0(0);
        if (state->width == width) {
            if (result != 0) {
                result = func_001854E0(0);
            }
        }
        if (*(volatile u32 *)0x10000800 > (u32)(period * (D_00325E30 + 1))) {
            break;
        }
    }
    D_00325E30 = 0;
    if (state->beforeDisplay != NULL) {
        state->beforeDisplay();
    }
    if (state->display != 0) {
        if (state->frame & 1) {
            display = (u8 *)state + 0x150;
        } else {
            display = (u8 *)state + 0x60;
        }
        func_00186060(display, state->x, state->y, (s16)result);
    }
    func_0017BB60(0);
    func_00185480((u8 *)state, state->frame);
    if (func_001A86D0() != 0) {
        func_00100610(1);
    }
    func_00185578(0, 0);
    *(volatile s32 *)0x10009020 = 0;
    *(volatile s32 *)0x10009030 = (u32)state->dmaAddress & 0x0FFFFFFF;
    *(volatile s32 *)0x1000E010 = 2;
    func_0017BB60(0);
    *(volatile s32 *)0x10009000 = 0x145;
    if (state->currentBuffer != 0) {
        state->dmaAddress = state->buffer1;
        state->dmaBuffer = state->buffer1;
        state->currentBuffer = 0;
    } else {
        state->dmaAddress = state->buffer0;
        state->dmaBuffer = state->buffer0;
        state->currentBuffer = 1;
    }
    state->frame++;
    result = 1;
    if (*(s32 *)(D_00293F14 + D_00326188 * 0x28) == 2) {
        if (state->width == 0x1C0) {
            if (*(volatile u32 *)0x10000800 > 0x21C) {
                result = 2;
            }
        } else if (*(volatile u32 *)0x10000800 > 0x10E) {
            result = 2;
        }
    } else if (*(volatile u32 *)0x10000800 > 0x280) {
        result = 2;
    }
    *(volatile u32 *)0x10000800 = 0;
    func_00213F60(state->dmaAddress, state->dmaAddress + state->dmaSize);
    func_00209D30(func_0020B1E0(func_00209D20()));
    return result;
}
