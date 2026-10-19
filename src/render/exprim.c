/* Draw lists: primitives, sorting, dither, alpha, frame-buffer copies (Ex*). */

#include "common.h"

/* Starts the primitive system. */
void ExInitPrim(void) {
    RhGeom_PushMatrix(0);
    ExClearOt(mainDrawList, 0x01E08000, 0xC);
}

/* Ends the primitive system. */
void ExTermPrim(void) {
    ExBindPrim(mainDrawList);
    RhGeom_PopMatrix();
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

/* Starts draw list `ot` with a table of 2^`depth` depth slots at `table`, and the GS register set-up packet. */
void ExClearOt(u8 *ot, s32 table, s32 depth) {
    extern u8 gsRegisterSets[];
    s32 count;
    Node_002073D0 *node;
    u64 *packet;
    Context_002073D0 *ctx;

    packet = (u64 *)RhBase_GetVifPacketArea();
    count = 1 << depth;
    packet[1] = 0;
    packet[0] = 0;
    ctx = (Context_002073D0 *)ot;
    ctx->start = (Tag_002073D0 *)packet;
    packet[2] = 0x100000000000800EULL;
    packet[3] = 0xE;
    packet = RhMem_CopyMemory16(packet + 4, gsRegisterSets, 0xE);
    ctx->start->qwc = 0xF;
    ctx->start->id = 0x10;
    ctx->start->vif0 = 0x11000000;
    ctx->start->vif1 = ctx->start->qwc | 0x51000000;
    packet[1] = 0;
    packet[0] = 0;
    ctx->head = (Tag_002073D0 *)packet;
    ctx->head->id = 0x10;
    RhBase_SetVifPacketArea((s32)(packet + 2));
    ctx->depth = depth;
    ctx->table = (Node_002073D0 *)table;
    node = (Node_002073D0 *)table;
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

/* The current draw list. */
u8 *ExGetMyOT(void) {
    return mainDrawList;
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

/* Links the used depth slots of draw list `ot` into one DMA chain, back to front. */
void ExBindPrim(void *ot) {
    Node_00207510 *tail;
    Node_00207510 *node;
    Node_00207510 *next;
    Context_00207510 *ctx = ot;

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
        tail->next = (Node_00207510 *)RhBase_GetVifPacketArea();
    }
}

/* Adds primitive `prim` to draw list `ot` at depth `z`. */
void ExSortPrim(s32 prim, s32 ot, s32 z) {
    RhBase_SetVifPacketArea(ExSortPrim_Pipe(RhBase_GetVifPacketArea(), prim, ot, z));
}

typedef struct {
    u16 count;
    u16 flags;
    u32 padding;
    u64 registers;
    u64 data[1];
} Source_00207650;

typedef struct {
    u32 tag;
    void *next;
} Link_00207650;

typedef struct {
    Link_00207650 *links;
    u8 padding[8];
    s32 shift;
} Table_00207650;

typedef struct {
    u64 lower : 32;
    u64 enabled : 1;
    u64 upper : 31;
} Register_00207650;

typedef struct {
    u16 loops : 15;
    u16 end : 1;
} Tag_00207650;

/* Writes primitive `prim` into the packet at `cursor`, linked into draw list `ot` at depth `z` (or sent straight
   away for no list). */
s32 ExSortPrim_Pipe(s32 cursorIn, s32 prim, s32 ot, s32 z) {
    extern u8 gsRegisterSets[];
    u64 *cursor;
    u64 *start;
    u64 registers;
    s32 flags;
    s32 context;
    u64 *data;
    s32 replace;
    u16 count;
    s32 texture;
    s32 alpha;
    s32 alphaMask;
    s32 contextMask;
    u32 primitive;
    s32 restore;
    s32 i;
    u64 reg;
    u16 length;
    u64 prim64;
    Register_00207650 saved;

    cursor = (u64 *)cursorIn;
    start = cursor;
    registers = ((Source_00207650 *)prim)->registers;
    count = ((Source_00207650 *)prim)->count;
    data = ((Source_00207650 *)prim)->data;
    flags = ((Source_00207650 *)prim)->flags;
    alphaMask = flags & 0x200;
    contextMask = flags & 0x1000;
    if (alphaMask != 0) {
        alpha = 1;
    } else {
        alpha = 0;
    }
    if (contextMask != 0) {
        context = 1;
    } else {
        context = 0;
    }
    primitive = flags & 0xF;
    if (primitive == 7) {
        return cursorIn;
    }
    cursor[1] = 0;
    cursor[0] = 0;
    *((u8 *)cursor + 3) = 0x10;
    if (ot != 0) {
        Table_00207650 *table = (Table_00207650 *)ot;
        s32 limit = 1 << table->shift;
        if (flags & 0x8000) {
            z = limit - 1;
        } else if ((u32)(limit - 2) < (u32)z) {
            z = limit - 2;
        }
        *(void **)((u8 *)cursor + 4) =
            *(void **)((s32)table->links + z * 8 + 4);
        *(void **)((s32)table->links + z * 8 + 4) = cursor;
    }
    prim64 = primitive;
    cursor[2] = 0x1000000000008000ULL;
    cursor[3] = 0xE;
    texture = flags & 0x20;
    replace = flags & 0x800;
    cursor[4] = ((s64)((flags & 0x2000) ? 1 : 0) << 10) |
        (((s64)(contextMask ? 1 : 0) << 9) |
        (((s64)(replace ? 1 : 0) << 8) |
        (((s64)((flags & 0x400) ? 1 : 0) << 7) |
        (((s64)(alphaMask ? 1 : 0) << 6) |
        (((s64)((flags & 0x100) ? 1 : 0) << 5) |
        (prim64 |
        ((s64)((flags & 0x10) ? 1 : 0) * 8) |
        ((s64)(texture ? 1 : 0) * 16)))))));
    cursor[5] = 0;
    cursor[6] = (s64)(alpha ? 1 : 0) | 0x5000C;
    cursor[7] = (s64)(context + 0x47);
    cursor += 8;
    if (alphaMask != 0) {
        cursor[0] = data[(u16)count];
        cursor[1] = (s64)(context + 0x42);
        cursor += 2;
    }
    if (texture != 0) {
        u64 *extra = &data[(u16)count];
        cursor[0] = extra[1];
        cursor[1] = (s64)(context + 6);
        cursor[2] = extra[2];
        cursor[3] = (s64)(context + 0x14);
        cursor += 4;
        if (flags & 0x4000) {
            cursor[0] = extra[3];
            cursor[1] = (s64)(context + 8);
            cursor += 2;
        }
    }
    restore = flags & 0x8000;
    if (restore != 0) {
        RhBase_GetZBufInfo(&saved);
        saved.enabled = 0;
        cursor[0] = *(u64 *)&saved;
        cursor[1] = (s64)(context + 0x4E);
        cursor += 2;
    }
    for (i = 0; i < (u16)count; i++) {
        reg = registers & 0xF;
        if (replace != 0 && reg == 2) {
            reg = 3;
        }
        registers >>= 4;
        cursor[0] = *data;
        cursor[1] = reg;
        cursor += 2;
        data++;
    }
    if (texture != 0 && (flags & 0x4000)) {
        u64 *extra = (u64 *)(gsRegisterSets + context * 0x70);
        cursor[0] = extra[8];
        cursor[1] = extra[9];
        cursor += 2;
    }
    if (restore != 0) {
        saved.enabled = 1;
        cursor[0] = *(u64 *)&saved;
        cursor[1] = (s64)(context + 0x4E);
        cursor += 2;
    }
    length = ((cursor - start) >> 1) - 1;
    *(u16 *)start = length;
    *(u32 *)((u8 *)start + 8) = 0x11000000;
    *(u32 *)((u8 *)start + 0xC) = length | 0x51000000;
    ((Tag_00207650 *)((u8 *)start + 0x10))->loops = length - 1;
    return (s32)cursor;
}

typedef int DotrDrawWord;
struct DotrDrawPair {
    long unknown_00;
    long unknown_08;
};
extern struct DotrDrawPair D_00293D80_207aa0[][7];
struct DotrDrawFields {
    unsigned short low_9 : 9;
    unsigned short unknown_bits_9_15 : 7;
    unsigned char unknown_02;
    unsigned char low_4 : 4;
    unsigned char unknown_bits_4_7 : 4;
};
typedef struct DotrDrawSlot {
    int unknown_00;
    struct DotrDrawNode *head;
} DotrDrawSlot;
typedef struct DotrDrawNode {
    int unknown_00;
    struct DotrDrawNode *next;
} DotrDrawNode;
typedef struct DotrDrawChain {
    DotrDrawSlot *slots;
    int unknown_04;
    int unknown_08;
    int shift;
} DotrDrawChain;
struct DotrSortHeader {
    unsigned short count;
    unsigned short type;
    int unknown_04;
    unsigned long regs;
    unsigned long data[4];
};
struct DotrSortVertex {
    float unknown_00[3];
    float q;
    unsigned long xyz;
    unsigned long colour;
    unsigned long uv;
    unsigned long unknown_28;
};
struct DotrSortZBuf {
    struct DotrDrawFields fields;
    unsigned char mask : 1;
    unsigned char unknown_bits_1_7 : 7;
    unsigned char unknown_05[3];
};
struct DotrSortTag {
    unsigned short size;
    unsigned char unknown_02;
    unsigned char kind;
    int next;
    int unknown_08;
    int unknown_0c;
    unsigned short loops : 15;
    unsigned short end : 1;
};

/* Writes a node's `count` vertices as primitives into the packet, linked into a draw list at depth `z`. */
int ExSortNode_Pipe(int cursor, void *header_v, int count, s32 vertices_v, void *chain_v, int z)
{
    struct DotrSortHeader * header = header_v;
    struct DotrSortVertex * vertices = (struct DotrSortVertex *)vertices_v;
    DotrDrawChain * chain = chain_v;
    unsigned long *p = (unsigned long *)cursor;
    int type = header->type;
    struct DotrSortVertex *vertex = vertices;
    int textured = (type & 0x200) ? 1 : 0;
    int context = (type & 0x1000) ? 1 : 0;
    unsigned long *start = p;
    struct DotrSortZBuf zbuf;
    int depth;
    int i;
    int size;
    unsigned long *q;
    struct DotrDrawPair *row;

    if ((type & 0xf) == 7) {
        return cursor;
    }
    if (count <= 0) {
        return cursor;
    }
    p[1] = 0;
    p[0] = 0;
    ((struct DotrSortTag *)p)->kind = 0x10;
    if (chain) {
        size = 1 << chain->shift;
        if (type & 0x8000) {
            z = size - 1;
        } else if ((unsigned int)(size - 2) < (unsigned int)z) {
            z = size - 2;
        }
        
        z <<= 3;
        ((struct DotrSortTag *)p)->next = (int)(DotrDrawWord)((DotrDrawSlot *)((DotrDrawWord)chain->slots + z))->head;
        ((DotrDrawSlot *)((DotrDrawWord)chain->slots + z))->head = (DotrDrawNode *)p;
    }
    p[2] = 0x1000000000008000;
    p[3] = 0xe;
    p[4] = (unsigned int)(type & 0xf) | ((long)(int)((type & 0x10) ? 1 : 0) << 3) | ((long)(int)((type & 0x20) ? 1 : 0) << 4)
        | ((long)(int)((type & 0x100) ? 1 : 0) << 5) | ((long)(int)((type & 0x200) ? 1 : 0) << 6) | ((long)(int)((type & 0x400) ? 1 : 0) << 7)
        | ((long)(int)((type & 0x800) ? 1 : 0) << 8) | ((long)(int)((type & 0x1000) ? 1 : 0) << 9) | ((long)(int)((type & 0x2000) ? 1 : 0) << 10);
    p[5] = 0;
    p[6] = (long)(int)(textured ? 1 : 0) | 0x5000c;
    p[7] = context + 0x47;
    p += 8;
    if (type & 0x200) {
        p[0] = header->data[0];
        p[1] = context + 0x42;
        p += 2;
    }
    if (type & 0x20) {
        p[0] = header->data[1];
        p[1] = context + 6;
        p[2] = header->data[2];
        p[3] = context + 0x14;
        p += 4;
        if (type & 0x4000) {
            p[0] = header->data[3];
            p[1] = context + 8;
            p += 2;
        }
    }
    depth = type & 0x8000;
    if (depth) {
        RhBase_GetZBufInfo(&zbuf.fields);
        zbuf.mask = 0;
        p[0] = *(unsigned long *)&zbuf;
        p[1] = context + 0x4e;
        p += 2;
    }
    for (i = 0; i < count; i++, vertex++) {
        if (i == 0 || (type & 0x10)) {
            q = p;
            p[0] = vertex->colour;
            p[1] = 1;
            p += 2;
            if (type & 0x10) {
                ((float *)q)[1] = 1.0f / vertex->q;
            }
        }
        if (type & 0x20) {
            q = p;
            p[0] = vertex->uv;
            p[1] = (type & 0x800) ? 3 : 2;
            p += 2;
            if (!(type & 0x800) && (type & 0x10)) {
                ((float *)q)[0] /= vertex->q;
                ((float *)q)[1] /= vertex->q;
            }
        }
        p[0] = vertex->xyz;
        p[1] = 4;
        p += 2;
    }
    if ((type & 0x20) && (type & 0x4000)) {
        row = D_00293D80_207aa0[context];
        p[0] = row[4].unknown_00;
        p[1] = row[4].unknown_08;
        p += 2;
    }
    if (depth) {
        zbuf.mask = 1;
        p[0] = *(unsigned long *)&zbuf;
        p[1] = context + 0x4e;
        p += 2;
    }
    size = ((p - start) >> 1) - 1;
    ((struct DotrSortTag *)start)->size = size;
    ((struct DotrSortTag *)start)->unknown_08 = 0x11000000;
    ((struct DotrSortTag *)start)->unknown_0c = (size & 0xffff) | 0x51000000;
    ((struct DotrSortTag *)start)->loops = (size & 0xffff) - 1;
    return (DotrDrawWord)p;
}

/* Starts an anchor (a group of primitives sorted together). */
s32 ExSetAnchor(void) {
    s32 cursor;

    cursor = RhBase_GetVifPacketArea();
    RhBase_SetVifPacketArea(ExSetAnchor_Pipe(cursor));
    return cursor;
}

/* Writes an anchor's head into the packet at `cursor`. */
s32 ExSetAnchor_Pipe(s32 cursor) {
    ((s64 *)cursor)[3] = 0;
    ((s64 *)cursor)[2] = 0;
    ((s64 *)cursor)[1] = 0;
    ((s64 *)cursor)[0] = 0;
    ((s8 *)cursor)[3] = 0x50;
    ((s8 *)cursor)[0x13] = 0x20;
    return cursor + 0x20;
}

/* Links an anchor's group into draw list `ot` at depth `z`. */
void ExSortAnchor(s32 anchor, s32 ot, s32 z) {
    RhBase_SetVifPacketArea(ExSortAnchor_Pipe(RhBase_GetVifPacketArea(), anchor, ot, z));
}

/* Closes the anchor started at `anchor` and links its group into draw list `ot` at depth `z`. */
s32 ExSortAnchor_Pipe(s32 cursor, s32 anchor, s32 ot, s32 z) {
    s32 offset;
    u32 limit;

    limit = (1 << *(s32 *)(ot + 0xC)) - 2;
    if (limit < (u32) z) {
        z = limit;
    }
    offset = z * 8;
    *(s32 *)(anchor + 4) = *(s32 *)(*(s32 *)ot + offset + 4);
    *(s32 *)(*(s32 *)ot + offset + 4) = anchor;
    *(s64 *)(cursor + 8) = 0;
    *(s64 *)cursor = 0;
    *(s8 *)(cursor + 3) = 0x60;
    return cursor + 0x10;
}

/* Draws the frame buffer over itself (motion blur). */
void ExSortDispBlur(s32 ot, s32 z, s32 frame, s32 alpha, s32 color) {
    RhBase_SetVifPacketArea(ExSortDispBlur_Pipe(RhBase_GetVifPacketArea(), ot, z, frame, alpha, color));
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

/* Draws the frame buffer `frame` over the screen with `alpha` and `color` (motion blur). */
s32 ExSortDispBlur_Pipe(s32 cursor, s32 ot, s32 z, s32 frame, s32 alpha, s32 colorIn) {
    extern Color_00208110 D_00293ED0;
    extern s32 ExAssignAlpha();
    Color_00208110 def;
    Packet_00208110 packet;
    u8 *color;

    def = D_00293ED0;
    ((Header_00208110 *)&packet)->kind = 0x26;
    ((Header_00208110 *)&packet)->count = 5;
    ((Header_00208110 *)&packet)->regs = 0x42421;
    ((Header_00208110 *)&packet)->flags = 0;
    color = (u8 *)colorIn;
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
    ExAssignAlpha(&packet, alpha);
    ExAssignFrameBuffer(&packet, frame);
    return ExSortPrim_Pipe(cursor, (s32)&packet, ot, z);
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
    Regs_00208280 regs;             /* 0x40: TEX0/TEX1/CLAMP, the tail ExSortPrim_Pipe reads (flags 0x226) */
} Packet_00208280;

/* Draws a copy of the frame buffer `frame` moved by (dx, dy) over the screen in `color` (soft focus). */
s32 ExSortSoftFocus_Pipe(s32 cursor, s32 ot, s32 z, s32 frame, s32 dx, s32 dy, u8 *color) {
    extern Color_00208280 D_00293ED8;
    extern s32 ExFrameBuffer2Texture_Pipe();
    Color_00208280 def;
    Packet_00208280 packet;
    s32 obj;

    def = D_00293ED8;
    ((Header_00208280 *)&packet)->kind = 0x26;
    ((Header_00208280 *)&packet)->count = 5;
    ((Header_00208280 *)&packet)->regs = 0x42421;
    ((Header_00208280 *)&packet)->flags = 0;
    ExAssignAlpha(&packet, 0x44 | ((s64)0x80 << 32));
    if (color == NULL) {
        color = (u8 *)&def;
    }
    packet.r = color[2];
    packet.g = color[1];
    packet.b = color[0];
    packet.a = color[3];
    packet.q = 1.0f;
    packet.v0.x = dx + 0x6BF8;
    packet.v0.y = dy + 0x71F8;
    packet.v0.z = 0xFFFFFF;
    packet.v0.fog = 0;
    packet.v1.x = dx + 0x93F8;
    packet.v1.y = dy + 0x8DF8;
    packet.v1.z = 0xFFFFFF;
    packet.v1.fog = 0;
    packet.s0 = 0.0f;
    packet.t0 = 0.0f;
    packet.s1 = 0.625f;
    packet.t1 = 0.875f;
    cursor = RhText_SetTextureFlush(cursor);
    obj = RhText_SetTextureFlush(ExFrameBuffer2Texture_Pipe(cursor, RhBase_GetUserGsAddress(), frame, &packet.regs.tex0, &packet.regs.tex1));
    packet.regs.tex0.tcc = 1;
    return ExSortPrim_Pipe(obj, (s32)&packet, ot, z);
}

/* Flushes the GS texture cache. */
void ExFlushTexture(void) {
    RhBase_SetVifPacketArea(RhText_SetTextureFlush(RhBase_GetVifPacketArea()));
}

/* Turns the z-buffer test on or off. */
void ExZBufferMode(s32 on) {
    RhBase_SetVifPacketArea(RhBase_SetZBufferMode(RhBase_GetVifPacketArea(), on));
}

/* Sets the GS texture clamp register to `clamp`. */
s32 ExClampMode_Pipe(s32 cursor, s64 clamp) {
    *(s64 *)((u8 *)cursor + 8) = 0;
    *(s64 *)cursor = 0;
    *(s8 *)((u8 *)cursor + 3) = 0x10;
    *(s64 *)((u8 *)cursor + 0x10) = 0x1000000000008001LL;
    *(s64 *)((u8 *)cursor + 0x18) = 0xE;
    *(s64 *)((u8 *)cursor + 0x20) = clamp;
    *(s64 *)((u8 *)cursor + 0x28) = 8;
    *(s16 *)cursor = 2;
    *(s32 *)((u8 *)cursor + 8) = 0x11000000;
    *(s32 *)((u8 *)cursor + 0xC) = 0x51000002;
    return cursor + 0x30;
}

/* Turns GS dithering on or off. */
void *ExDitherMode_Pipe(void *cursor, s32 on) {
    *(s64 *)((u8 *)cursor + 8) = 0;
    *(s64 *)cursor = 0;
    *((u8 *)cursor + 3) = 0x10;
    *(u64 *)((u8 *)cursor + 0x10) = 0x1000000000008001ULL;
    *(s64 *)((u8 *)cursor + 0x18) = 0xE;
    *(s64 *)((u8 *)cursor + 0x20) = on;
    *(s64 *)((u8 *)cursor + 0x28) = 0x45;
    *(u16 *)cursor = 2;
    *(u32 *)((u8 *)cursor + 8) = 0x11000000;
    *(u32 *)((u8 *)cursor + 0xC) = 0x51000002;
    return (u8 *)cursor + 0x30;
}

/* Sets dither matrix `index` (0..3). */
void ExDitherMatrixEz(s32 index) {
    RhBase_SetVifPacketArea(ExDitherMatrixEz_Pipe(RhBase_GetVifPacketArea(), index));
}

/* Sets the GS dither matrix to built-in matrix `index` (0..3). */
s32 ExDitherMatrixEz_Pipe(s32 cursor, s32 index) {
    u64 value;

    if (index < 0 || index >= 4) {
        return cursor;
    }

    value = ditherMatrices[index];
    *(u64 *)(cursor + 8) = 0;
    *(u64 *)cursor = 0;
    *(u8 *)(cursor + 3) = 0x10;
    *(u64 *)(cursor + 0x10) = 0x1000000000008001ULL;
    *(u64 *)(cursor + 0x18) = 0xE;
    *(u64 *)(cursor + 0x20) = value;
    *(u64 *)(cursor + 0x28) = 0x44;
    *(u16 *)cursor = 2;
    *(u32 *)(cursor + 8) = 0x11000000;
    *(u32 *)(cursor + 0xC) = 0x51000002;
    return cursor + 0x30;
}

typedef struct {
    s64 value;
    s64 padding;
} Entry_00208680;

extern Entry_00208680 gsRegisterSets[][7]; /* original: gExPrim_aaRegs */

/* The value of GS register `reg` (0..6) of register set `set`. */
s64 ExGetRegVal(s32 set, s32 reg) {
    if (reg < 0 || reg >= 7) {
        return -1;
    }
    return gsRegisterSets[set][reg].value;
}

typedef struct {
    u16 index;
    u16 flags;
    u8 padding[0xC];
    s64 values[1];
} Buffer_002086D0;

/* Sets a primitive's alpha blend register. */
s32 ExAssignAlpha(void *prim, s64 alpha) {
    Buffer_002086D0 *buffer = prim;
    u16 index = buffer->index;
    s64 *values = (s64 *)((u8 *)prim + 0x10);

    buffer->flags |= 0x200;
    values[index] = alpha;
    return 1;
}

typedef struct {
    u64 reserved0 : 5;
    u64 flag : 1;
    u64 mode : 3;
    u64 reserved9 : 55;
} Flags_00208700;

/* Sets a primitive's texture registers from `texture` (`mode` the texture function). */
s32 ExAssignTexture(void *prim, void *texture, s32 mode) {
    u8 *base = (u8 *)prim + 0x10;
    u16 count = *(u16 *)prim;
    u64 *dst;

    if (!(*(u16 *)((u8 *)prim + 2) & 0x20)) {
        return 0;
    }
    if (texture == NULL) {
        return 0;
    }
    dst = (u64 *)(base + count * 8);
    dst[1] = *(u64 *)((u8 *)texture + 0x30);
    dst[2] = *(u64 *)((u8 *)texture + 0x40);
    ((Flags_00208700 *)(dst + 2))->flag = (((Flags_00208700 *)(dst + 2))->mode = mode);
    return 1;
}

typedef struct {
    u16 count;
    u16 flags;
    u8 padding[12];
    u8 data[1];
} Header_002087A0;

/* Sets a primitive's texture to frame buffer `frame`. */
s32 ExAssignFrameBuffer(void *prim, s32 frame) {
    Header_002087A0 *header = prim;
    u16 count = header->count;
    u8 *data = header->data;

    if (!(header->flags & 0x20)) {
        return 0;
    }
    ExFrameBuffer2Texture_Pipe(0, 0, frame, data + (count & 0xFFFF) * 8 + 8,
                 data + (count & 0xFFFF) * 8 + 0x10);
    return 1;
}

/* Uses part of the frame buffer as a texture. */
void ExFrameBuffer2Texture(s32 cursor, s32 address, s32 frame, s32 tex0) {
    extern s32 ExFrameBuffer2Texture_Pipe();

    RhBase_SetVifPacketArea(ExFrameBuffer2Texture_Pipe(RhBase_GetVifPacketArea(), cursor, address, frame, tex0));
}

typedef struct Tex0_00208870 {
    u64 tbp0 : 14;
    u64 tbw : 6;
    u64 psm : 6;
    u64 tw : 4;
    u64 th : 4;
    u64 tcc : 1;
    u64 tfx : 2;
    u64 cbp : 14;
    u64 cpsm : 4;
    u64 csm : 1;
    u64 csa : 5;
    u64 cld : 3;
} Tex0_00208870;

typedef struct Tex1_00208870 {
    u64 lcm : 1;
    u64 pad0 : 1;
    u64 mxl : 3;
    u64 mmag : 1;
    u64 mmin : 3;
    u64 mtba : 1;
    u64 pad1 : 9;
    u64 l : 2;
    u64 pad2 : 11;
    u64 k : 12;
    u64 pad3 : 20;
} Tex1_00208870;

/* Builds the texture registers that read frame buffer `frame` (copied to `address` if given) into `tex0` / `tex1`. */
s32 ExFrameBuffer2Texture_Pipe(s32 cursor, s32 address, s32 frame, void *tex0In, void *tex1In) {
    s32 widthIn;
    s32 height;
    s32 fbp;
    s32 psm;
    s32 tw;
    s32 th;
    Tex0_00208870 *tex0 = (Tex0_00208870 *)tex0In;
    Tex1_00208870 *tex1 = (Tex1_00208870 *)tex1In;
    s64 *packet = (s64 *)cursor;
    s64 *start = packet;

    RhBase_GetBufferFormatEx(address != 0 ? 1 : 0, &widthIn, &height, NULL);
    RhBase_GetScreenSize(&fbp, &psm);
    for (tw = 0; (1 << tw) < fbp; tw++) {
    }
    for (th = 0; (1 << th) < psm; th++) {
    }
    if (tex0 != NULL) {
        tex0->tbp0 = address > 0 ? address : widthIn;
        tex0->tbw = fbp >> 6;
        tex0->psm = height;
        tex0->tw = tw;
        tex0->th = th;
        tex0->tcc = 0;
        tex0->tfx = 0;
        tex0->cbp = 0;
        tex0->cpsm = 0;
        tex0->csm = 0;
        tex0->csa = 0;
        tex0->cld = 1;
    }
    if (tex1 != NULL) {
        tex1->lcm = 0;
        tex1->mxl = 0;
        tex1->mmag = frame;
        tex1->mmin = frame;
        tex1->mtba = 0;
        tex1->l = 0;
        tex1->k = 0;
    }
    if (address > 0) {
        s64 width;
        u16 count;

        packet[1] = 0;
        packet[0] = 0;
        ((u8 *)packet)[3] = 0x10;
        packet[2] = 0x1000000000008004LL;
        packet[3] = 0xE;
        width = fbp >> 6;
        packet[4] = ((s64)height << 56) | ((width << 48) | (((s64)address << 32) |
                    (((s64)height << 24) | (widthIn | (width << 16)))));
        packet[5] = 0x50;
        packet[6] = 0;
        packet[7] = 0x51;
        packet[8] = fbp | ((s64)psm << 32);
        packet[9] = 0x52;
        packet[10] = 2;
        packet[11] = 0x53;
        packet += 12;
        count = ((packet - start) >> 1) - 1;
        *(u16 *)start = count;
        ((s32 *)start)[2] = 0x11000000;
        ((s32 *)start)[3] = count | 0x51000000;
    }
    return (s32)packet;
}

typedef struct Buffer_00208CB0 {
    u16 index;
    u16 flags;
    u8 padding[0xC];
    s64 values[1];
} Buffer_00208CB0;

/* Sets a primitive's texture clamp register. */
s32 ExAssignClamp(void *prim, s64 clamp) {
    Buffer_00208CB0 *buffer = prim;
    u16 index = buffer->index;
    s64 *values = buffer->values;
    u16 *flags = &buffer->flags;

    if (!(*flags & 0x20)) {
        return 0;
    }
    *flags |= 0x4000;
    *(s64 *)((u8 *)values + (index & 0xFFFF) * 8 + 0x18) = clamp;
    return 1;
}

/* Alpha blend mode `mode` (0..3) as a GS register value. */
s64 ExGetAlphaVal(s32 mode) {
    s64 ret;

    if (mode < 0 || mode >= 4) {
        ret = 0;
    } else {
        ret = alphaBlendModes[mode];
    }
    return ret;
}
